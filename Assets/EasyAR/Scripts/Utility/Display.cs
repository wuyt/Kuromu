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
    /// <para xml:lang="en">Display device.</para>
    /// <para xml:lang="zh">显示设备。</para>
    /// </summary>
    public class Display : IDisposable
    {
        private Dictionary<int, int> rotations = new Dictionary<int, int>();
#if UNITY_ANDROID && !UNITY_EDITOR
        private static AndroidJavaObject defaultDisplay;
#endif

        public Display()
        {
            if (Application.platform == RuntimePlatform.Android)
            {
                InitializeAndroid();
            }
            else if (Application.platform == RuntimePlatform.IPhonePlayer)
            {
                InitializeIOS();
            }
        }

        ~Display()
        {
            DeleteAndroidJavaObjects();
        }

        /// <summary>
        /// <para xml:lang="en">Device rotation.</para>
        /// <para xml:lang="zh">设备旋转信息。</para>
        /// </summary>
        public int Rotation
        {
            get
            {
                if (Application.platform == RuntimePlatform.Android)
                {
#if UNITY_ANDROID && !UNITY_EDITOR
                    var rotation = defaultDisplay.Call<int>("getRotation");
                    return rotations[rotation];
#endif
                }
                else if (Application.platform == RuntimePlatform.IPhonePlayer)
                {
                    return rotations[(int)Screen.orientation];
                }
                return 0;
            }
        }

        /// <summary>
        /// <para xml:lang="en">Dispose resources.</para>
        /// <para xml:lang="zh">销毁资源。</para>
        /// </summary>
        public void Dispose()
        {
            DeleteAndroidJavaObjects();
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// <para xml:lang="en">Get compensation matrix using camera parameters <paramref name="camParams"/>.</para>
        /// <para xml:lang="zh">根据相机参数<paramref name="camParams"/>返回补偿矩阵。</para>
        /// </summary>
        public Matrix4x4 GetCompensation(CameraParameters camParams)
        {
            var screenRotation = Rotation;
            var imageRotation = camParams.imageOrientation(screenRotation) / 180f * Mathf.PI;
            Matrix4x4 rotationMatrix = Matrix4x4.identity;
            rotationMatrix.m00 = Mathf.Cos(-imageRotation);
            rotationMatrix.m01 = -Mathf.Sin(-imageRotation);
            rotationMatrix.m10 = Mathf.Sin(-imageRotation);
            rotationMatrix.m11 = Mathf.Cos(-imageRotation);
            return rotationMatrix;
        }

        /// <summary>
        /// <para xml:lang="en">Transforms points from screen coordinate system ([0, 1]^2) to image coordinate system ([0, 1]^2). <paramref name="pointInView"/> should be normalized to [0, 1]^2.</para>
        /// <para xml:lang="zh">从屏幕坐标系（[0, 1]^2）变换到图像坐标系（[0, 1]^2）。<paramref name="pointInView"/> 需要被归一化到[0, 1]^2。</para>
        /// </summary>
        public Vector2 ImageCoordinatesFromScreenCoordinates(Vector2 pointInView, CameraParameters cameraParameters, Camera camera)
        {
            return cameraParameters.imageCoordinatesFromScreenCoordinates(
                camera.aspect, Rotation, true, false, new Vec2F(pointInView.x, 1 - pointInView.y)).ToUnityVector();
        }

        private void InitializeIOS()
        {
            rotations[(int)ScreenOrientation.Portrait] = 0;
            rotations[(int)ScreenOrientation.LandscapeLeft] = 90;
            rotations[(int)ScreenOrientation.PortraitUpsideDown] = 180;
            rotations[(int)ScreenOrientation.LandscapeRight] = 270;
        }

        private void InitializeAndroid()
        {
#if UNITY_ANDROID && !UNITY_EDITOR
            using (var surfaceClass = new AndroidJavaClass("android.view.Surface"))
            using (var contextClass = new AndroidJavaClass("android.content.Context"))
            using (var windowService = contextClass.GetStatic<AndroidJavaObject>("WINDOW_SERVICE"))
            using (var unityPlayerClass = new AndroidJavaClass("com.unity3d.player.UnityPlayer"))
            using (var currentActivity = unityPlayerClass.GetStatic<AndroidJavaObject>("currentActivity"))
            using (var systemService = currentActivity.Call<AndroidJavaObject>("getSystemService", windowService))
            {
                defaultDisplay = systemService.Call<AndroidJavaObject>("getDefaultDisplay");
                rotations[surfaceClass.GetStatic<int>("ROTATION_0")] = 0;
                rotations[surfaceClass.GetStatic<int>("ROTATION_90")] = 90;
                rotations[surfaceClass.GetStatic<int>("ROTATION_180")] = 180;
                rotations[surfaceClass.GetStatic<int>("ROTATION_270")] = 270;
            }
#endif
        }

        private void DeleteAndroidJavaObjects()
        {
#if UNITY_ANDROID && !UNITY_EDITOR
            if (defaultDisplay != null) { defaultDisplay.Dispose(); }
#endif
        }
    }
}
