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
    [CreateAssetMenu(menuName = "EasyAR/Render Camera Parameters")]
    public class RenderCameraParameters : ScriptableObject, IDisposable
    {
        public string DeviceModel;
        public Vector3 PositionOffset;
        public Vector3 RotationOffset;
        public Vector2 Size;
        public Vector2 FocalLength;
        public Vector2 PrincipalPoint;

        private static Vector3 positionScale = new Vector3(1, -1, -1);

        ~RenderCameraParameters()
        {
            if (Parameters != null)
            {
                Parameters.Dispose();
            }
        }

        public Matrix4x4 Transform { get; private set; }
        public CameraParameters Parameters { get; private set; }

        public void Build(CameraParameters cameraParameters)
        {
            Transform = Matrix4x4.TRS(Vector3.Scale(PositionOffset, positionScale), Quaternion.Euler(RotationOffset), Vector3.one);
            if (Parameters != null)
            {
                Parameters.Dispose();
            }
            Parameters = new CameraParameters(new Vec2I((int)Size.x, (int)Size.y), new Vec2F(FocalLength.x, FocalLength.y), new Vec2F(PrincipalPoint.x, PrincipalPoint.y),
                cameraParameters.cameraDeviceType(), cameraParameters.cameraOrientation());
        }

        public void Dispose()
        {
            if (Parameters != null)
            {
                Parameters.Dispose();
            }
            GC.SuppressFinalize(this);
        }
    }
}
