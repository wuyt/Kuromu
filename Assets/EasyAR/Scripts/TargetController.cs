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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="Target"/> in the scene, providing a few extensions in the Unity environment.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="Target"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。</para>
    /// </summary>
    public abstract class TargetController : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">Strategy to control the <see cref="GameObject.active"/>. If you are willing to control <see cref="GameObject.active"/> or there are other components controlling <see cref="GameObject.active"/>, make sure to set it to <see cref="ActiveControlStrategy.None"/>.</para>
        /// <para xml:lang="zh"><see cref="GameObject.active"/>的控制策略。如果你打算自己控制<see cref="GameObject.active"/>或是有其它组件在控制<see cref="GameObject.active"/>，需要设为<see cref="ActiveControlStrategy.None"/>。</para>
        /// </summary>
        public ActiveControlStrategy ActiveControl;
        /// <summary>
        /// <para xml:lang="en">Horizontal flip control, usually for internal use.</para>
        /// <para xml:lang="zh">水平翻转控制，一般为内部使用。</para>
        /// </summary>
        public bool HorizontalFlip;

        private bool firstFound;

        /// <summary>
        /// <para xml:lang="en"><see cref="Target"/> found event.</para>
        /// <para xml:lang="zh"><see cref="Target"/>找到的事件。</para>
        /// </summary>
        public event Action TargetFound;
        /// <summary>
        /// <para xml:lang="en"><see cref="Target"/> lost event.</para>
        /// <para xml:lang="zh"><see cref="Target"/>丢失的事件。</para>
        /// </summary>
        public event Action TargetLost;

        /// <summary>
        /// <para xml:lang="en">Strategy to control the <see cref="GameObject.active"/>.</para>
        /// <para xml:lang="zh"><see cref="GameObject.active"/>的控制策略。</para>
        /// </summary>
        public enum ActiveControlStrategy
        {
            /// <summary>
            /// <para xml:lang="en">Active is true when the target is tracked, false when not tracked.</para>
            /// <para xml:lang="zh">当没有被识别跟踪时Active为false，当被跟踪识别时Active为true。</para>
            /// </summary>
            HideWhenNotTracking,
            /// <summary>
            /// <para xml:lang="en">False before the fist <see cref="TargetFound"/> event, then true.</para>
            /// <para xml:lang="zh">在第一次<see cref="TargetFound"/>事件之前Active为false，之后为true。</para>
            /// </summary>
            HideBeforeFirstFound,
            /// <summary>
            /// <para xml:lang="en">Do not control <see cref="GameObject.active"/>.</para>
            /// <para xml:lang="zh">不控制<see cref="GameObject.active"/>。</para>
            /// </summary>
            None,
        }

        /// <summary>
        /// <para xml:lang="en">Is the target being tracked at the moment.</para>
        /// <para xml:lang="zh">当前target是否被跟踪。</para>
        /// </summary>
        public bool IsTracked { get; private set; }
        /// <summary>
        /// <para xml:lang="en">Is the target loaded by a tracker.</para>
        /// <para xml:lang="zh">是否被一个trakcer加载。</para>
        /// </summary>
        public bool IsLoaded { get; protected set; }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected virtual void Start()
        {
            if (!IsTracked && (ActiveControl == ActiveControlStrategy.HideWhenNotTracking || ActiveControl == ActiveControlStrategy.HideBeforeFirstFound))
            {
                gameObject.SetActive(false);
            }
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Process tracking event.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。处理跟踪事件。</para>
        /// </summary>
        internal void OnTracking(bool status)
        {
            if (IsTracked != status)
            {
                if (status)
                {
                    if (ActiveControl == ActiveControlStrategy.HideWhenNotTracking || (ActiveControl == ActiveControlStrategy.HideBeforeFirstFound && !firstFound))
                    {
                        gameObject.SetActive(true);
                    }
                    firstFound = true;
                    if (TargetFound != null)
                    {
                        TargetFound();
                    }
                }
                else
                {
                    if (ActiveControl == ActiveControlStrategy.HideWhenNotTracking)
                    {
                        gameObject.SetActive(false);
                    }
                    if (TargetLost != null)
                    {
                        TargetLost();
                    }
                }
                IsTracked = status;
            }
            if (IsTracked)
            {
                OnTracking();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Process tracking event.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。处理跟踪事件。</para>
        /// </summary>
        protected abstract void OnTracking();
    }
}
