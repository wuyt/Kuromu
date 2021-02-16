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
    /// <para xml:lang="en">The render camera parameters. It is usually used when setting parameters of optical device, like "eye" from eyewears.</para>
    /// <para xml:lang="zh">相机渲染参数与配置。通常在设置类似眼镜的“眼睛”的光学设备参数时使用。</para>
    /// </summary>
    [CreateAssetMenu(menuName = "EasyAR/Render Camera Parameters")]
    public class RenderCameraParameters : ScriptableObject, IDisposable
    {
        /// <summary>
        /// <para xml:lang="en">Device model.</para>
        /// <para xml:lang="zh">设备型号。</para>
        /// </summary>
        public string DeviceModel;

        /// <summary>
        /// <para xml:lang="en">Position offset.</para>
        /// <para xml:lang="zh">位置偏移。</para>
        /// </summary>
        public Vector3 PositionOffset;
        /// <summary>
        /// <para xml:lang="en">Rotation offset.</para>
        /// <para xml:lang="zh">角度偏移。</para>
        /// </summary>
        public Vector3 RotationOffset;
        /// <summary>
        /// <para xml:lang="en">(Image) size.</para>
        /// <para xml:lang="zh">（图像）大小。</para>
        /// </summary>
        public Vector2 Size;

        /// <summary>
        /// <para xml:lang="en">Focal length.</para>
        /// <para xml:lang="zh">焦距。</para>
        /// </summary>
        public Vector2 FocalLength;
        /// <summary>
        /// <para xml:lang="en">Principal point.</para>
        /// <para xml:lang="zh">主点。</para>
        /// </summary>
        public Vector2 PrincipalPoint;

        private static Vector3 positionScale = new Vector3(1, -1, -1);

        ~RenderCameraParameters()
        {
            if (Parameters != null)
            {
                Parameters.Dispose();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Transform matrix.</para>
        /// <para xml:lang="zh">变换矩阵。</para>
        /// </summary>
        public Matrix4x4 Transform { get; private set; }
        /// <summary>
        /// <para xml:lang="en">The equivalent parameter of camera device.</para>
        /// <para xml:lang="zh">相机设备的等效参数。</para>
        /// </summary>
        public CameraParameters Parameters { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Build <see cref="Transform"/> and <see cref="Parameters"/>.</para>
        /// <para xml:lang="zh">生成<see cref="Transform"/>和<see cref="Parameters"/>。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Dispose resources.</para>
        /// <para xml:lang="zh">销毁资源。</para>
        /// </summary>
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
