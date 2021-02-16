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
    /// <para xml:lang="en">Abstracts frame filter, used when assemble, to run algorithms using input frame data.</para>
    /// <para xml:lang="zh">抽象frame filter，在组装时使用，使用frame输入数据运行算法。</para>
    /// </summary>
    public abstract class FrameFilter : MonoBehaviour
    {
        private bool horizontalFlip;

        /// <summary>
        /// <para xml:lang="en">Camera buffers occupied in this component.</para>
        /// <para xml:lang="zh">当前组件占用camera buffer的数量。</para>
        /// </summary>
        public abstract int BufferRequirement
        {
            get;
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Assemble response.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。组装响应方法。</para>
        /// </summary>
        public virtual void OnAssemble(ARSession session)
        {
        }

        /// <summary>
        /// <para xml:lang="en">Set horizontal flip when using <see cref="ARSession.ARHorizontalFlipMode.Target"/> mode.</para>
        /// <para xml:lang="zh">在<see cref="ARSession.ARHorizontalFlipMode.Target"/>模式下设置镜像翻转。</para>
        /// </summary>
        public void SetHFlip(bool hFlip)
        {
            if (horizontalFlip != hFlip)
            {
                horizontalFlip = hFlip;
                OnHFlipChange(horizontalFlip);
            }
        }

        /// <summary>
        /// <para xml:lang="en">Horizontal flip response.</para>
        /// <para xml:lang="zh">水平翻转响应方法。</para>
        /// </summary>
        protected virtual void OnHFlipChange(bool hFlip)
        {
        }

        /// <summary>
        /// <para xml:lang="en">Interface for feedback frame input port.</para>
        /// <para xml:lang="zh">反馈帧输入端口接口。</para>
        /// </summary>
        public interface IFeedbackFrameSink
        {
            /// <summary>
            /// <para xml:lang="en">Usually only for internal assemble use. Feedback frame input port.</para>
            /// <para xml:lang="zh">通常只在内部组装时使用。反馈帧输入端口。</para>
            /// </summary>
            FeedbackFrameSink FeedbackFrameSink();
        }

        /// <summary>
        /// <para xml:lang="en">Interface for input frame input port.</para>
        /// <para xml:lang="zh">输入帧输入端口接口。</para>
        /// </summary>
        public interface IInputFrameSink
        {
            /// <summary>
            /// <para xml:lang="en">Usually only for internal assemble use. Input frame input port.</para>
            /// <para xml:lang="zh">通常只在内部组装时使用。输入帧输入端口。</para>
            /// </summary>
            InputFrameSink InputFrameSink();
        }

        /// <summary>
        /// <para xml:lang="en">Interface for input frame input port using delayed connect.</para>
        /// <para xml:lang="zh">延迟连接的输入帧输入端口接口。</para>
        /// </summary>
        public interface IInputFrameSinkDelayConnect
        {
            /// <summary>
            /// <para xml:lang="en">Usually only for internal assemble use. Delay connect to input frame output port, and run <paramref name="action"/> when connect happens.</para>
            /// <para xml:lang="zh">通常只在内部组装时使用。延迟连接输入帧输出端口，并在连接时执行<paramref name="action"/>。</para>
            /// </summary>
            void ConnectedTo(InputFrameSource val, Action action);
        }

        /// <summary>
        /// <para xml:lang="en">Interface for output frame output port.</para>
        /// <para xml:lang="zh">输出帧输出端口接口。</para>
        /// </summary>
        public interface IOutputFrameSource
        {
            /// <summary>
            /// <para xml:lang="en">Usually only for internal assemble use. Output frame output port.</para>
            /// <para xml:lang="zh">通常只在内部组装时使用。输出帧输出端口。</para>
            /// </summary>
            OutputFrameSource OutputFrameSource();
            /// <summary>
            /// <para xml:lang="en">Usually only for internal assemble use. Process tracking results.</para>
            /// <para xml:lang="zh">通常只在内部组装时使用。处理跟踪结果。</para>
            /// </summary>
            List<KeyValuePair<Optional<TargetController>, Matrix44F>> OnResult(Optional<FrameFilterResult> frameFilterResult);
        }

        /// <summary>
        /// <para xml:lang="en">Interface for spatial information input port.</para>
        /// <para xml:lang="zh">空间信息输入端口接口。</para>
        /// </summary>
        public interface ISpatialInformationSink
        {
            /// <summary>
            /// <para xml:lang="en">Tracking status.</para>
            /// <para xml:lang="zh">跟踪状态。</para>
            /// </summary>
            MotionTrackingStatus TrackingStatus
            {
                get;
            }
            /// <summary>
            /// <para xml:lang="en">Usually only for internal assemble use. Process tracking results.</para>
            /// <para xml:lang="zh">通常只在内部组装时使用。处理跟踪结果。</para>
            /// </summary>
            void OnTracking(MotionTrackingStatus status);
        }
    }
}
