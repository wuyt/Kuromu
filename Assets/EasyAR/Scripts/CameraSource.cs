//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

namespace easyar
{
    /// <summary>
    /// <para xml:lang="en">Abstracts camera device as frame source, used when assemble, to provide input frame data to the algorithms.</para>
    /// <para xml:lang="zh">抽象作为frame源的Camera设备，在组装时使用，提供算法所需的frame输入数据。</para>
    /// </summary>
    public abstract class CameraSource : FrameSource
    {
        protected int bufferCapacity;

        /// <summary>
        /// <para xml:lang="en">Device buffer capacity.</para>
        /// <para xml:lang="zh">设备缓冲容量。</para>
        /// </summary>
        public virtual int BufferCapacity
        {
            get
            {
                return bufferCapacity;
            }
            set
            {
                bufferCapacity = value;
            }
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected virtual void Start()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            Open();
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            Close();
        }

        /// <summary>
        /// <para xml:lang="en">Open camera</para>
        /// <para xml:lang="zh">开启Camera。</para>
        /// </summary>
        public abstract void Open();
        /// <summary>
        /// <para xml:lang="en">Close camera</para>
        /// <para xml:lang="zh">关闭Camera。</para>
        /// </summary>
        public abstract void Close();
    }
}
