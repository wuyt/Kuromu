//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.Collections.Generic;
using UnityEngine;

namespace easyar
{
    ///<remarks>
    ///                        +-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .-- .--+
    ///                        |                                                                                                                  .
    ///                        .                                 +---------------------------------------------------------------+                |
    ///                        |                                 |                                                               |                .
    ///                        .                                 |                       + -> ObjectTracker - - - - +            |                |
    ///                        |                                 v                       '                          '            |                .
    ///                        .                        +--> i2FAdapter --> fbFrameFork - - > ImageTracker - - - +  '            |                |
    ///                        |                        |                                                        '  '            |                .
    ///                        v                        |                                                        v  v            |                |
    ///  FrameSource --> iFrameThrottler --> iFrameFork --> i2OAdapter ------------------------------------> oFrameJoin --> oFrameFork --> oFrameBuffer ~~> o
    ///                                                 '                                                        ^  ^
    ///                                                 '                                                        '  '
    ///                                                 + - - - - - - - - - - - - - - - - - > SparseSpatialMap - +  '
    ///                                                 '                                                           '
    ///                                                 + - - - - - - - - - - - - - - - - - > SurfaceTracker - - - -+
    ///                                                 '
    ///                                                 '
    ///                                                 + - - - - - - - - - - - - - - - - - > DenseSpatialMap ~ ~ > o
    ///                                                 '
    ///                                                 + - - - - - - - - - - - - - - - - - > CloudRecognizer ~ ~ > o
    ///</remarks>
    [Serializable]
    public class ARAssembly : IDisposable
    {
        public Camera Camera;
        public Transform CameraRoot;
        public List<RenderCameraController> RenderCameras = new List<RenderCameraController>();
        public FrameSource FrameSource;
        public List<FrameFilter> FrameFilters = new List<FrameFilter>();

        protected InputFrameThrottler iFrameThrottler;
        protected InputFrameFork iFrameFork;
        protected InputFrameToOutputFrameAdapter i2OAdapter;
        protected InputFrameToFeedbackFrameAdapter i2FAdapter;
        protected FeedbackFrameFork fbFrameFork;
        protected OutputFrameJoin oFrameJoin;
        protected OutputFrameFork oFrameFork;
        protected OutputFrameBuffer oFrameBuffer;

        ~ARAssembly()
        {
            DisposeAll();
        }

        public enum AssembleMode
        {
            Auto,
            Manual,
        }

        public bool Ready { get; private set; }

        public bool RequireWorldCenter { get; private set; }

        public Optional<OutputFrame> OutputFrame
        {
            get
            {
                if (!Ready)
                {
                    return null;
                }
                return oFrameBuffer.peek();
            }
        }

        public virtual void Dispose()
        {
            DisposeAll();
            GC.SuppressFinalize(this);
        }

        public virtual void Assemble(ARSession session)
        {
            if (session.AssembleMode == AssembleMode.Auto)
            {
                Camera = Camera.main;
                CameraRoot = Camera.transform;
                RenderCameras = new List<RenderCameraController>(session.GetComponentsInChildren<RenderCameraController>());
                FrameSource = session.GetComponentInChildren<FrameSource>();
                FrameFilters = new List<FrameFilter>(session.GetComponentsInChildren<FrameFilter>());
            }

            foreach (var renderCamera in RenderCameras) { renderCamera.OnAssemble(session); }
            if (FrameSource) { FrameSource.OnAssemble(session); }
            foreach (var filter in FrameFilters) { filter.OnAssemble(session); }

            try
            {
                Assemble();
            }
            catch (Exception ex)
            {
                Debug.LogError("Fail to Assemble: " + ex.Message);
            }
        }

        public void Break()
        {
            Ready = false;
        }

        public void Pause()
        {
            if (!Ready)
            {
                return;
            }
            oFrameBuffer.pause();
        }

        public void Resume()
        {
            if (!Ready)
            {
                return;
            }
            oFrameBuffer.resume();
        }

        public void ResetBufferCapacity()
        {
            if (FrameSource is CameraSource)
            {
                var cameraSource = FrameSource as CameraSource;
                cameraSource.BufferCapacity = GetBufferRequirement();
            }
        }

        protected int GetBufferRequirement()
        {
            int count = 1; // for OutputFrameBuffer.peek
            if (FrameSource != null) { count += 1; }
            if (iFrameThrottler != null) { count += iFrameThrottler.bufferRequirement(); }
            if (i2FAdapter != null) { count += i2FAdapter.bufferRequirement(); }
            if (oFrameBuffer != null) { count += oFrameBuffer.bufferRequirement(); }
            foreach (var filter in FrameFilters)
            {
                if (filter != null) { count += filter.BufferRequirement; }
            }
            return count;
        }

        protected int GetFrameFilterCount<T>()
        {
            if (FrameFilters == null)
            {
                return 0;
            }
            int count = 0;
            foreach (var filter in FrameFilters)
            {
                if (filter is T)
                {
                    count++;
                }
            }
            return count;
        }

        private void Assemble()
        {
            // throttler
            iFrameThrottler = InputFrameThrottler.create();

            // fork input
            iFrameFork = InputFrameFork.create(2 + GetFrameFilterCount<FrameFilter.IInputFrameSink>());
            iFrameThrottler.output().connect(iFrameFork.input());
            var iFrameForkIndex = 0;
            i2OAdapter = InputFrameToOutputFrameAdapter.create();
            iFrameFork.output(iFrameForkIndex).connect(i2OAdapter.input());
            iFrameForkIndex++;
            i2FAdapter = InputFrameToFeedbackFrameAdapter.create();
            iFrameFork.output(iFrameForkIndex).connect(i2FAdapter.input());
            iFrameForkIndex++;
            foreach (var filter in FrameFilters)
            {
                if (filter is FrameFilter.IInputFrameSink)
                {
                    FrameFilter.IInputFrameSink unit = filter as FrameFilter.IInputFrameSink;
                    var sink = unit.InputFrameSink();
                    if (sink != null)
                    {
                        iFrameFork.output(iFrameForkIndex).connect(unit.InputFrameSink());
                    }
                    if (filter is FrameFilter.IInputFrameSinkDelayConnect)
                    {
                        var delayUnit = filter as FrameFilter.IInputFrameSinkDelayConnect;
                        delayUnit.ConnectedTo(iFrameFork.output(iFrameForkIndex), ResetBufferCapacity);
                    }
                    iFrameForkIndex++;
                }
            }

            // feedback
            fbFrameFork = FeedbackFrameFork.create(GetFrameFilterCount<FrameFilter.IFeedbackFrameSink>());
            i2FAdapter.output().connect(fbFrameFork.input());
            var fbFrameForkIndex = 0;
            foreach (var filter in FrameFilters)
            {
                if (filter is FrameFilter.IFeedbackFrameSink)
                {
                    FrameFilter.IFeedbackFrameSink unit = filter as FrameFilter.IFeedbackFrameSink;
                    fbFrameFork.output(fbFrameForkIndex).connect(unit.FeedbackFrameSink());
                    fbFrameForkIndex++;
                }
            }

            // join
            oFrameJoin = OutputFrameJoin.create(1 + GetFrameFilterCount<FrameFilter.IOutputFrameSource>());
            var joinIndex = 0;
            foreach (var filter in FrameFilters)
            {
                if (filter is FrameFilter.IOutputFrameSource)
                {
                    FrameFilter.IOutputFrameSource unit = filter as FrameFilter.IOutputFrameSource;
                    unit.OutputFrameSource().connect(oFrameJoin.input(joinIndex));
                    joinIndex++;
                }
            }
            i2OAdapter.output().connect(oFrameJoin.input(joinIndex));

            // fork output for feedback
            oFrameFork = OutputFrameFork.create(2);
            oFrameJoin.output().connect(oFrameFork.input());
            oFrameBuffer = OutputFrameBuffer.create();
            oFrameFork.output(0).connect(oFrameBuffer.input());
            oFrameFork.output(1).connect(i2FAdapter.sideInput());

            // signal throttler
            oFrameBuffer.signalOutput().connect(iFrameThrottler.signalInput());

            // connect source
            if (FrameSource != null)
            {
                FrameSource.Connect(iFrameThrottler.input());
            }

            // set BufferCapacity
            ResetBufferCapacity();

            if (FrameSource.HasSpatialInformation)
            {
                RequireWorldCenter = true;
            }
            foreach (var filter in FrameFilters)
            {
                if (filter is SurfaceTrackerFrameFilter)
                {
                    if (RequireWorldCenter)
                    {
                        throw new InvalidOperationException(typeof(SurfaceTracker) + " + VIOCameraDevice is not supported");
                    }
                    RequireWorldCenter = true;
                }
            }

            Ready = true;
        }

        private void DisposeAll()
        {
            if (iFrameThrottler != null) { iFrameThrottler.Dispose(); }
            if (iFrameFork != null) { iFrameFork.Dispose(); }
            if (i2OAdapter != null) { i2OAdapter.Dispose(); }
            if (i2FAdapter != null) { i2FAdapter.Dispose(); }
            if (fbFrameFork != null) { fbFrameFork.Dispose(); }
            if (oFrameJoin != null) { oFrameJoin.Dispose(); }
            if (oFrameFork != null) { oFrameFork.Dispose(); }
            if (oFrameBuffer != null) { oFrameBuffer.Dispose(); }
            Ready = false;
        }
    }
}
