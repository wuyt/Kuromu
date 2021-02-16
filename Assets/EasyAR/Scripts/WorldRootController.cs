//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEngine;

namespace easyar
{
    /// <summary>
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls the world root in the scene.</para>
    /// <para xml:lang="en">The world root is a virtual node, representing the relative node when the camera moves in a motion tracking system. It will be automatically generated to be the origin of the global coordinate system when needed if not manually set in the scene.</para>
    /// <para xml:lang="zh">在场景中控制世界根节点的<see cref="MonoBehaviour"/>。</para>
    /// <para xml:lang="zh">世界根节点是一个虚拟的节点，它表示在运动跟踪的系统中，camera移动的相对节点。如果场景中没有手动设置这个节点，它将在被需要的时候自动被设置为全局坐标系的原点。</para>
    /// </summary>
    public class WorldRootController : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">Strategy to control the <see cref="GameObject.active"/>. If you are willing to control <see cref="GameObject.active"/> or there are other components controlling <see cref="GameObject.active"/>, make sure to set it to <see cref="ActiveControlStrategy.None"/>.</para>
        /// <para xml:lang="zh"><see cref="GameObject.active"/>的控制策略。如果你打算自己控制<see cref="GameObject.active"/>或是有其它组件在控制<see cref="GameObject.active"/>，需要设为<see cref="ActiveControlStrategy.None"/>。</para>
        /// </summary>
        public ActiveControlStrategy ActiveControl;
        private bool trackingStarted;

        /// <summary>
        /// <para xml:lang="en">Motion tracking status change event.</para>
        /// <para xml:lang="zh">跟踪状态改变的事件。</para>
        /// </summary>
        public event Action<MotionTrackingStatus> TrackingStatusChanged;

        /// <summary>
        /// <para xml:lang="en">Strategy to control the <see cref="GameObject.active"/>.</para>
        /// <para xml:lang="zh"><see cref="GameObject.active"/>的控制策略。</para>
        /// </summary>
        public enum ActiveControlStrategy
        {
            /// <summary>
            /// <para xml:lang="en">Active is false when the motion tracking status is not tracking, true otherwise.</para>
            /// <para xml:lang="zh">当运动跟踪状态是未跟踪时Active为false，其它情况Active为true。</para>
            /// </summary>
            HideWhenNotTracking,
            /// <summary>
            /// <para xml:lang="en">False before the motion tracking status turns to a tracking status, then true.</para>
            /// <para xml:lang="zh">在运动跟踪状态第一次不是未跟踪前Active为false，之后为true。</para>
            /// </summary>
            HideBeforeTrackingStart,
            /// <summary>
            /// <para xml:lang="en">Do not control <see cref="GameObject.active"/>.</para>
            /// <para xml:lang="zh">不控制<see cref="GameObject.active"/>。</para>
            /// </summary>
            None,
        }

        /// <summary>
        /// <para xml:lang="en">Motion tracking status at the moment.</para>
        /// <para xml:lang="zh">当前运动跟踪状态。</para>
        /// </summary>
        public MotionTrackingStatus TrackingStatus
        {
            get; private set;
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected virtual void Start()
        {
            if (TrackingStatus == MotionTrackingStatus.NotTracking && (ActiveControl == ActiveControlStrategy.HideBeforeTrackingStart || ActiveControl == ActiveControlStrategy.HideWhenNotTracking))
            {
                gameObject.SetActive(false);
            }
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Process tracking event.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。处理跟踪事件。</para>
        /// </summary>
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
