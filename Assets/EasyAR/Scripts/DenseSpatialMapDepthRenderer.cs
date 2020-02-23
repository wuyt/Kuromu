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
    public class DenseSpatialMapDepthRenderer : MonoBehaviour
    {
        public Shader Shader;

        private RenderTexture depthTexture;

        public Camera RenderDepthCamera { get; set; }
        public Material MapMeshMaterial { get; set; }

        private void LateUpdate()
        {
            if (!RenderDepthCamera || !MapMeshMaterial)
            {
                return;
            }
            if (depthTexture && (depthTexture.width != Screen.width || depthTexture.height != Screen.height))
            {
                Destroy(depthTexture);
            }
            if (!depthTexture)
            {
                depthTexture = new RenderTexture(Screen.width, Screen.height, 24);
                MapMeshMaterial.SetTexture("_DepthTexture", depthTexture);
            }
            RenderDepthCamera.targetTexture = depthTexture;
            RenderDepthCamera.RenderWithShader(Shader, "Tag");
            RenderDepthCamera.targetTexture = null;
        }

        private void OnDestroy()
        {
            if (depthTexture)
            {
                Destroy(depthTexture);
            }
        }
    }
}
