//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEngine;

namespace easyar
{
    /// <summary>
    /// <para xml:lang="en">Abstracts frame source, used when assemble, to provide input frame data to the algorithms.</para>
    /// <para xml:lang="zh">抽象frame源，在组装时使用，提供算法所需的frame输入数据。</para>
    /// </summary>
    public abstract class FrameSource : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">Input port connected.</para>
        /// <para xml:lang="zh">连接着的输入端口。</para>
        /// </summary>
        protected InputFrameSink sink;
        /// <summary>
        /// <para xml:lang="en">Current connected ARSession.</para>
        /// <para xml:lang="zh">当前连接的ARSession。</para>
        /// </summary>
        protected ARSession arSession;

        /// <summary>
        /// <para xml:lang="en">Whether spatial information can be provided by the source.</para>
        /// <para xml:lang="zh">源是否含有空间定位信息。</para>
        /// </summary>
        public abstract bool HasSpatialInformation
        {
            get;
        }

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            if (arSession)
            {
                arSession.Assembly.Resume();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected virtual void OnDisable()
        {
            if (arSession)
            {
                arSession.Assembly.Pause();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Connect input port.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。连接输入端口。</para>
        /// </summary>
        public virtual void Connect(InputFrameSink val)
        {
            sink = val;
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Assemble response.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。组装响应方法。</para>
        /// </summary>
        public virtual void OnAssemble(ARSession session)
        {
            arSession = session;
        }
    }
}
