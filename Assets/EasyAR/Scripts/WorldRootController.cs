//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEngine;

namespace easyar
{
    public class WorldRootController : MonoBehaviour
    {
        public ActiveControlStrategy ActiveControl;
        private bool trackingStarted;

        public event Action<MotionTrackingStatus> TrackingStatusChanged;

        public enum ActiveControlStrategy
        {
            HideWhenNotTracking,
            HideBeforeTrackingStart,
            None,
        }

        public MotionTrackingStatus TrackingStatus
        {
            get; private set;
        }

        protected virtual void Start()
        {
            if (TrackingStatus == MotionTrackingStatus.NotTracking && (ActiveControl == ActiveControlStrategy.HideBeforeTrackingStart || ActiveControl == ActiveControlStrategy.HideWhenNotTracking))
            {
                gameObject.SetActive(false);
            }
        }

        internal void OnTracking(MotionTrackingStatus status)
        {
            if (TrackingStatus != status)
            {
                if (ActiveControl == ActiveControlStrategy.HideWhenNotTracking || (ActiveControl == ActiveControlStrategy.HideBeforeTrackingStart && !trackingStarted))
                {
                    gameObject.SetActive(!(status == MotionTrackingStatus.NotTracking));
                }
                if (!trackingStarted && status != MotionTrackingStatus.NotTracking)
                {
                    trackingStarted = true;
                }
                if (TrackingStatusChanged != null)
                {
                    TrackingStatusChanged(status);
                }
                TrackingStatus = status;
            }
        }
    }
}
