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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which provides <see cref="Camera"/> rendering events.</para>
    /// <para xml:lang="cn">提供<see cref="Camera"/>渲染事件的<see cref="MonoBehaviour"/>。</para>
    /// </summary>
    internal class CameraRenderEvent : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">PreRender is called before a <see cref="Camera"/>  starts rendering the Scene.</para>
        /// <para xml:lang="cn">PreRender <see cref="Camera">渲染场景的之前触发。</para>
        /// </summary>
        public event Action PreRender;

        /// <summary>
        /// <para xml:lang="en">PostRender is called after a <see cref="Camera"/>  finished rendering the Scene.</para>
        /// <para xml:lang="cn">PostRender <see cref="Camera">结束场景渲染之后触发。</para>
        /// </summary>
        public event Action PostRender;

        private void OnPreRender()
        {
            if (PreRender != null)
            {
                PreRender();
            }
        }

        private void OnPostRender()
        {
            if (PostRender != null)
            {
                PostRender();
            }
        }
    }
}
