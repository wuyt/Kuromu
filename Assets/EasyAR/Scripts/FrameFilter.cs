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
    public abstract class FrameFilter : MonoBehaviour
    {
        private bool horizontalFlip;

        public abstract int BufferRequirement
        {
            get;
        }

        public virtual void OnAssemble(ARSession session)
        {
        }

        public void SetHFlip(bool hFlip)
        {
            if (horizontalFlip != hFlip)
            {
                horizontalFlip = hFlip;
                OnHFlipChange(horizontalFlip);
            }
        }

        protected virtual void OnHFlipChange(bool hFlip)
        {
        }

        public interface IFeedbackFrameSink
        {
            FeedbackFrameSink FeedbackFrameSink();
        }

        public interface IInputFrameSink
        {
            InputFrameSink InputFrameSink();
        }

        public interface IInputFrameSinkDelayConnect
        {
            void ConnectedTo(InputFrameSource val, Action action);
        }

        public interface IOutputFrameSource
        {
            OutputFrameSource OutputFrameSource();
            List<KeyValuePair<Optional<TargetController>, Matrix44F>> OnResult(Optional<FrameFilterResult> frameFilterResult);
        }

        public interface ISpatialInformationSink
        {
            MotionTrackingStatus TrackingStatus
            {
                get;
            }
            void OnTracking(MotionTrackingStatus status);
        }
    }
}
