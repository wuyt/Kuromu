//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEngine;

namespace easyar
{
    [CreateAssetMenu(menuName = "EasyAR/Shaders")]
    public class EasyARShaders : ScriptableObject
    {
        public Shader BGR;
        public Shader GRAY;
        public Shader YUV_I420_YV12;
        public Shader YUV_NV12;
        public Shader YUV_NV21;
    }
}
