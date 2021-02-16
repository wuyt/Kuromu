//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
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
    ///</remarks>

    /// <summary>
    /// <para xml:lang="en">Assembly of AR components. It implements one typical assemble strategy for all EasyAR Sense components. Inherit this class and override some methods can make a more customized assembly.</para>
    /// <para xml:lang="zh">AR组件的组装体。它实现了一种对所有EasyAR Sense组件的典型组装。继承这个类并重载部分可以实现更定制化的组装。</para>
    /// </summary>
    [Serializable]
    public class ARAssembly : IDisposable
    {
        /// <summary>
        /// <para xml:lang="en"><see cref="UnityEngine.Camera"/> in the virtual world in reflection of real world camera device, its projection matrix and transform will be set to reflect the real world camera.</para>
        /// <para xml:lang="en">It will be set to <see cref="Camera.main"/> when assembling if <see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>.</para>
        /// <para xml:lang="zh">现实环境中相机设备在虚拟世界中对应的<see cref="UnityEngine.Camera"/>，其投影矩阵和位置都将于真实相机对应。</para>
        /// <para xml:lang="zh">如果<see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>，在组装时会设为<see cref="Camera.main"/>。</para>
        /// </summary>
        public Camera Camera;

        /// <summary>
        /// <para xml:lang="en"><see cref="Transform"/> of root node of all <see cref="UnityEngine.Camera"/>s used for AR rendering.</para>
        /// <para xml:lang="en">It will be set to <see cref="Camera"/> <see cref="Transform"/> when assembling if <see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>.</para>
        /// <para xml:lang="zh">用于AR渲染的所有<see cref="UnityEngine.Camera"/>的根节点的<see cref="Transform"/>。</para>
        /// <para xml:lang="zh">如果<see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>，在组装时会设为<see cref="Camera"/>的<see cref="Transform"/>。</para>
        /// </summary>
        public Transform CameraRoot;

        /// <summary>
        /// <para xml:lang="en"><see cref="RenderCameraController"/> list.</para>
        /// <para xml:lang="en">It will be set to the list of <see cref="RenderCameraController"/> get from children of the <see cref="ARSession"/> <see cref="GameObject"/> when assembling if <see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>.</para>
        /// <para xml:lang="zh"><see cref="RenderCameraController"/>的列表。</para>
        /// <para xml:lang="zh">如果<see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>，在组装时会从<see cref="ARSession"/>的<see cref="GameObject"/>的所有子节点中寻找并获取<see cref="RenderCameraController"/>。</para>
        /// </summary>
        public List<RenderCameraController> RenderCameras = new List<RenderCameraController>();

        /// <summary>
        /// <para xml:lang="en">Frame source.</para>
        /// <para xml:lang="en">It will be set to <see cref="easyar.FrameSource"/> get from children of the <see cref="ARSession"/> <see cref="GameObject"/> when assembling if <see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>.</para>
        /// <para xml:lang="zh">Frame数据源。</para>
        /// <para xml:lang="zh">如果<see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>，在组装时会从<see cref="ARSession"/>的<see cref="GameObject"/>的所有子节点中寻找并获取<see cref="easyar.FrameSource"/>。</para>
        /// </summary>
        public FrameSource FrameSource;

        /// <summary>
        /// <para xml:lang="en"><see cref="FrameFilter"/> list.</para>
        /// <para xml:lang="en">It will be set to the list of <see cref="FrameFilter"/> get from children of the <see cref="ARSession"/> <see cref="GameObject"/> when assembling if <see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>.</para>
        /// <para xml:lang="zh"><see cref="FrameFilter"/>的列表。</para>
        /// <para xml:lang="zh">如果<see cref="ARSession.AssembleMode"/> == <see cref="AssembleMode.Auto"/>，在组装时会从<see cref="ARSession"/>的<see cref="GameObject"/>的所有子节点中寻找并获取<see cref="FrameFilter"/>。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Assemble mode.</para>
        /// <para xml:lang="zh">组装模式。</para>
        /// </summary>
        public enum AssembleMode
        {
            /// <summary>
            /// <para xml:lang="en">Auto assemble, components will be get from the children nodes.</para>
            /// <para xml:lang="zh">自动组装，此模式会自动获取子节点的组件进行装配。</para>
            /// </summary>
            Auto,
            /// <summary>
            /// <para xml:lang="en">Manual assemble.</para>
            /// <para xml:lang="zh">手动组装。</para>
            /// </summary>
            Manual,
        }

        /// <summary>
        /// <para xml:lang="en">The assembly can be used.</para>
        /// <para xml:lang="zh">组装体可以使用。</para>
        /// </summary>
        public bool Ready { get; private set; }

        /// <summary>
        /// <para xml:lang="en">If <see cref="WorldRootController"/> is required by the assembly.</para>
        /// <para xml:lang="zh">组装体是否需要<see cref="WorldRootController"/>。</para>
        /// </summary>
        public bool RequireWorldCenter { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Output frame.</para>
        /// <para xml:lang="zh">输出帧。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Dispose resources.</para>
        /// <para xml:lang="zh">销毁资源。</para>
        /// </summary>
        public virtual void Dispose()
        {
            DisposeAll();
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// <para xml:lang="en">Assemble AR components.</para>
        /// <para xml:lang="zh">组装AR组件。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Break the assembly. The assembly cannot be used once broken.</para>
        /// <para xml:lang="zh">破坏AR组件体。一旦破坏将无法再使用。</para>
        /// </summary>
        public void Break()
        {
            Ready = false;
        }

        /// <summary>
        /// <para xml:lang="en">Pause output.</para>
        /// <para xml:lang="zh">暂停输出。</para>
        /// </summary>
        public void Pause()
        {
            if (!Ready)
            {
                return;
            }
            oFrameBuffer.pause();
        }

        /// <summary>
        /// <para xml:lang="en">Resume output.</para>
        /// <para xml:lang="zh">继续输出。</para>
        /// </summary>
        public void Resume()
        {
            if (!Ready)
            {
                return;
            }
            oFrameBuffer.resume();
        }

        /// <summary>
        /// <para xml:lang="en">Reset buffer capacity.</para>
        /// <para xml:lang="zh">重置缓冲的容量。</para>
        /// </summary>
        public void ResetBufferCapacity()
        {
            if (FrameSource is CameraSource)
            {
                var cameraSource = FrameSource as CameraSource;
                cameraSource.BufferCapacity = GetBufferRequirement();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Get buffer requirement.</para>
        /// <para xml:lang="zh">获取当前需要的缓冲容量。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Get <see cref="FrameFilter"/> number of certain type.</para>
        /// <para xml:lang="zh">获取指定<see cref="FrameFilter"/>的数量。</para>
        /// </summary>
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
