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
    [CreateAssetMenu(menuName = "EasyAR/Settings")]
    public class EasyARSettings : ScriptableObject
    {
        [HideInInspector, SerializeField]
        [TextArea(1, 10)]
        public string LicenseKey;
        public TargetGizmoConfig GizmoConfig = new TargetGizmoConfig();
        public SparseSpatialMapWorkerFrameFilter.SpatialMapServiceConfig GlobalSpatialMapServiceConfig = new SparseSpatialMapWorkerFrameFilter.SpatialMapServiceConfig();
        public CloudRecognizerFrameFilter.CloudRecognizerServiceConfig GlobalCloudRecognizerServiceConfig = new CloudRecognizerFrameFilter.CloudRecognizerServiceConfig();
        public bool ARCoreSupport = true;

        [Serializable]
        public class TargetGizmoConfig
        {
            public ImageTargetConfig ImageTarget = new ImageTargetConfig();
            public ObjectTargetConfig ObjectTarget = new ObjectTargetConfig();

            [Serializable]
            public class ImageTargetConfig
            {
                public bool EnableImageFile = true;
                public bool EnableTargetDataFile = true;
                public bool EnableTarget = true;
            }

            [Serializable]
            public class ObjectTargetConfig
            {
                public bool Enable = true;
            }
        }
    }
}
