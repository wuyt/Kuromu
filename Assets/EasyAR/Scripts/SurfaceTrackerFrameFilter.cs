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
    /// <summary>
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="SurfaceTracker"/> in the scene, providing a few extensions in the Unity environment. Use <see cref="Tracker"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="SurfaceTracker"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="Tracker"/>。</para>
    /// </summary>
    public class SurfaceTrackerFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.IOutputFrameSource
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after Awake if available.</para>
        /// <para xml:lang="zh">EasyAR Sense API，如果功能可以使用，可以在Awake之后访问。</para>
        /// </summary>
        public SurfaceTracker Tracker { get; private set; }

        private bool isStarted;

        public override int BufferRequirement
        {
            get { return Tracker.bufferRequirement(); }
        }

        /// <summary>
        /// MonoBehaviour Awake
        /// </summary>
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

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            if (Tracker != null && isStarted)
            {
                Tracker.start();
            }
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected virtual void Start()
        {
            isStarted = true;
            if (enabled)
            {
                OnEnable();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected virtual void OnDisable()
        {
            if (Tracker != null)
            {
                Tracker.stop();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
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

