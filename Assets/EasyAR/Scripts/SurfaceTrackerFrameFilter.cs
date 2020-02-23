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
    public class SurfaceTrackerFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.IOutputFrameSource
    {
        /// <summary>
        /// EasyAR Sense API. Accessible after Awake if available.
        /// </summary>
        public SurfaceTracker Tracker { get; private set; }

        private bool isStarted;

        public override int BufferRequirement
        {
            get { return Tracker.bufferRequirement(); }
        }

        protected virtual void Awake()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            if (!SurfaceTracker.isAvailable())
            {
                throw new UIPopupException(typeof(SurfaceTracker) + " not available");
            }

            Tracker = SurfaceTracker.create();
        }

        protected virtual void OnEnable()
        {
            if (Tracker != null && isStarted)
            {
                Tracker.start();
            }
        }

        protected virtual void Start()
        {
            isStarted = true;
            if (enabled)
            {
                OnEnable();
            }
        }

        protected virtual void OnDisable()
        {
            if (Tracker != null)
            {
                Tracker.stop();
            }
        }

        protected virtual void OnDestroy()
        {
            if (Tracker != null)
            {
                Tracker.Dispose();
            }
        }

        public InputFrameSink InputFrameSink()
        {
            if (Tracker != null)
            {
                return Tracker.inputFrameSink();
            }
            return null;
        }

        public OutputFrameSource OutputFrameSource()
        {
            if (Tracker != null)
            {
                return Tracker.outputFrameSource();
            }
            return null;
        }

        public List<KeyValuePair<Optional<TargetController>, Matrix44F>> OnResult(Optional<FrameFilterResult> frameFilterResult)
        {
            var list = new List<KeyValuePair<Optional<TargetController>, Matrix44F>>();
            if (frameFilterResult.OnSome)
            {
                var result = frameFilterResult.Value as SurfaceTrackerResult;
                list.Add(new KeyValuePair<Optional<TargetController>, Matrix44F>(null, result.transform()));
            }
            return list;
        }
    }
}

