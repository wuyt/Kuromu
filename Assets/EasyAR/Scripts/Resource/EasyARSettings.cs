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
    /// <para xml:lang="en">EasyAR Sense settings.</para>
    /// <para xml:lang="zh">EasyAR Sense的配置信息。</para>
    /// </summary>
    [CreateAssetMenu(menuName = "EasyAR/Settings")]
    public class EasyARSettings : ScriptableObject
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense License Key。Used for validation of EasyAR Sense functions. Please visit https://www.easyar.com for more details.</para>
        /// <para xml:lang="zh">EasyAR Sense License Key。用于验证EasyAR Sense内部各种功能是否可用。详见 https://www.easyar.cn 。</para>
        /// </summary>
        [HideInInspector, SerializeField]
        [TextArea(1, 10)]
        public string LicenseKey;
        /// <summary>
        /// <para xml:lang="en"><see cref="Gizmos"/> configuration for <see cref="ImageTarget"/> and <see cref="ObjectTarget"/>.</para>
        /// <para xml:lang="zh"><see cref="ImageTarget"/> 和 <see cref="ObjectTarget"/>的<see cref="Gizmos"/>配置。</para>
        /// </summary>
        public TargetGizmoConfig GizmoConfig = new TargetGizmoConfig();
        /// <summary>
        /// <para xml:lang="en">Global spatial map service config.</para>
        /// <para xml:lang="zh">全局稀疏地图服务器配置。</para>
        /// </summary>
        public SparseSpatialMapWorkerFrameFilter.SpatialMapServiceConfig GlobalSpatialMapServiceConfig = new SparseSpatialMapWorkerFrameFilter.SpatialMapServiceConfig();
        /// <summary>
        /// <para xml:lang="en">Global cloud recognizer service config.</para>
        /// <para xml:lang="zh">全局云识别服务器配置。</para>
        /// </summary>
        public CloudRecognizerFrameFilter.CloudRecognizerServiceConfig GlobalCloudRecognizerServiceConfig = new CloudRecognizerFrameFilter.CloudRecognizerServiceConfig();
        /// <summary>
        /// <para xml:lang="en">ARCore support (will load arcore lib).</para>
        /// <para xml:lang="zh">添加ARCore支持（将会加载ARCore库）。</para>
        /// </summary>
        public bool ARCoreSupport = true;

        /// <summary>
        /// <para xml:lang="en"><see cref="Gizmos"/> configuration for target.</para>
        /// <para xml:lang="zh">Target的<see cref="Gizmos"/>配置。</para>
        /// </summary>
        [Serializable]
        public class TargetGizmoConfig
        {
            /// <summary>
            /// <para xml:lang="en"><see cref="Gizmos"/> configuration for <see cref="easyar.ImageTarget"/>.</para>
            /// <para xml:lang="zh"><see cref="easyar.ImageTarget"/>的<see cref="Gizmos"/>配置。</para>
            /// </summary>
            public ImageTargetConfig ImageTarget = new ImageTargetConfig();
            /// <summary>
            /// <para xml:lang="en"><see cref="Gizmos"/> configuration for <see cref="easyar.ObjectTarget"/>.</para>
            /// <para xml:lang="zh"><see cref="easyar.ObjectTarget"/>的<see cref="Gizmos"/>配置。</para>
            /// </summary>
            public ObjectTargetConfig ObjectTarget = new ObjectTargetConfig();

            /// <summary>
            /// <para xml:lang="en"><see cref="Gizmos"/> configuration for <see cref="easyar.ImageTarget"/>.</para>
            /// <para xml:lang="zh"><see cref="easyar.ImageTarget"/>的<see cref="Gizmos"/>配置。</para>
            /// </summary>
            [Serializable]
            public class ImageTargetConfig
            {
                /// <summary>
                /// <para xml:lang="en">Enable <see cref="Gizmos"/> of target which <see cref="ImageTargetController.SourceType"/> equals to <see cref="ImageTargetController.DataSource.ImageFile"/>. Enable this option will load image file and display gizmo in Unity Editor, the startup performance of the Editor will be affected if there are too much target of this kind in the scene, but the Unity runtime will not be affected when running on devices.</para>
                /// <para xml:lang="zh">开启<see cref="ImageTargetController.SourceType"/>类型为<see cref="ImageTargetController.DataSource.ImageFile"/>的target的<see cref="Gizmos"/>。打开这个将会在Unity Editor中加载图像文件并显示对应gizmo，如果场景中该类target过多，可能会影响编辑器中的启动性能。在设备上运行时，Unity运行时的性能不会受到影响。</para>
                /// </summary>
                public bool EnableImageFile = true;
                /// <summary>
                /// <para xml:lang="en">Enable <see cref="Gizmos"/> of target which <see cref="ImageTargetController.SourceType"/> equals to <see cref="ImageTargetController.DataSource.TargetDataFile"/>. Enable this option will target data file and display gizmo in Unity Editor, the startup performance of the Editor will be affected if there are too much target of this kind in the scene, but the Unity runtime will not be affected when running on devices.</para>
                /// <para xml:lang="zh">开启<see cref="ImageTargetController.SourceType"/>类型为<see cref="ImageTargetController.DataSource.TargetDataFile"/>的target的<see cref="Gizmos"/>。打开这个将会在Unity Editor中加载target数据文件并显示显示对应gizmo，如果场景中该类target过多，可能会影响编辑器中的启动性能。在设备上运行时，Unity运行时的性能不会受到影响。</para>
                /// </summary>
                public bool EnableTargetDataFile = true;
                /// <summary>
                /// <para xml:lang="en">Enable <see cref="Gizmos"/> of target which <see cref="ImageTargetController.SourceType"/> equals to <see cref="ImageTargetController.DataSource.Target"/>. Enable this option will display gizmo in Unity Editor, the startup performance of the Editor will be affected if there are too much target of this kind in the scene, but the Unity runtime will not be affected when running on devices.</para>
                /// <para xml:lang="zh">开启<see cref="ImageTargetController.SourceType"/>类型为<see cref="ImageTargetController.DataSource.Target"/>的target的<see cref="Gizmos"/>。打开这个将会在Unity Editor中显示对应gizmo，如果场景中该类target过多，可能会影响编辑器中的启动性能。在设备上运行时，Unity运行时的性能不会受到影响。</para>
                /// </summary>
                public bool EnableTarget = true;
            }

            /// <summary>
            /// <para xml:lang="en"><see cref="Gizmos"/> configuration for <see cref="easyar.ObjectTarget"/>.</para>
            /// <para xml:lang="zh"><see cref="easyar.ObjectTarget"/>的<see cref="Gizmos"/>配置。</para>
            /// </summary>
            [Serializable]
            public class ObjectTargetConfig
            {
                /// <summary>
                /// <para xml:lang="en">Enable <see cref="Gizmos"/>.</para>
                /// <para xml:lang="zh">开启<see cref="Gizmos"/>。</para>
                /// </summary>
                public bool Enable = true;
            }
        }
    }
}
