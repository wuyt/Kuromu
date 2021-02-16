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
    /// <para xml:lang="en">Transform utility.</para>
    /// <para xml:lang="zh">Transform工具。</para>
    /// </summary>
    public static class TransformUtil
    {
        /// <summary>
        /// <para xml:lang="en">Calculate and set <see cref="Camera"/> transform using <see cref="Camera"/> <paramref name="pose"/>, to express the relation of <see cref="Camera"/> and <see cref="WorldRootController"/> in 3D space which is known in <see cref="Camera"/> <paramref name="pose"/>.</para>
        /// <para xml:lang="zh">已知<see cref="Camera"/>与<see cref="WorldRootController"/>的相对关系，通过<see cref="Camera"/>的<paramref name="pose"/>计算并设置<see cref="Camera"/>的Transform，以便在三维空间中将这个关系表达出来。</para>
        /// </summary>
        public static void SetCameraPoseOnCamera(Transform camera, WorldRootController controller, Matrix44F pose, Matrix4x4 displayCompensation, bool manualHorizontalFlip = false)
        {
            SetPoseOnTransform(camera.transform, controller.transform, pose, displayCompensation, true, true, manualHorizontalFlip);
        }

        /// <summary>
        /// <para xml:lang="en">Calculate and set <see cref="WorldRootController"/> transform using <see cref="Camera"/> <paramref name="pose"/>, to express the relation of <see cref="Camera"/> and <see cref="WorldRootController"/> in 3D space which is known in <see cref="Camera"/> <paramref name="pose"/>.</para>
        /// <para xml:lang="zh">已知<see cref="Camera"/>与<see cref="WorldRootController"/>的相对关系，通过<see cref="Camera"/>的<paramref name="pose"/>计算并设置<see cref="WorldRootController"/>的Transform，以便在三维空间中将这个关系表达出来。</para>
        /// </summary>
        public static void SetCameraPoseOnWorldRoot(Transform camera, WorldRootController controller, Matrix44F pose, Matrix4x4 displayCompensation, bool manualHorizontalFlip = false)
        {
            SetPoseOnTransform(controller.transform, camera.transform, pose, displayCompensation, true, false, manualHorizontalFlip);
        }

        /// <summary>
        /// <para xml:lang="en">Calculate and set <see cref="Camera"/> transform using <see cref="Target"/> <paramref name="pose"/>, to express the relation of <see cref="Camera"/> and <see cref="Target"/> in 3D space which is known in <see cref="Target"/> <paramref name="pose"/>.</para>
        /// <para xml:lang="zh">已知<see cref="Camera"/>与<see cref="Target"/>的相对关系，通过<see cref="Target"/>的<paramref name="pose"/>计算并设置<see cref="Camera"/>的Transform，以便在三维空间中将这个关系表达出来。</para>
        /// </summary>
        public static void SetTargetPoseOnCamera(Transform camera, TargetController controller, Matrix44F pose, Matrix4x4 displayCompensation, bool manualHorizontalFlip = false)
        {
            SetPoseOnTransform(camera.transform, controller.transform, pose, displayCompensation, false, true, manualHorizontalFlip);
        }

        /// <summary>
        /// <para xml:lang="en">Calculate and set <see cref="Target"/> transform using <see cref="Target"/> <paramref name="pose"/>, to express the relation of <see cref="Camera"/> and <see cref="Target"/> in 3D space which is known in <see cref="Target"/> <paramref name="pose"/>.</para>
        /// <para xml:lang="zh">已知<see cref="Camera"/>与<see cref="Target"/>的相对关系，通过<see cref="Target"/>的<paramref name="pose"/>计算并设置<see cref="Target"/>的Transform，以便在三维空间中将这个关系表达出来。</para>
        /// </summary>
        public static void SetTargetPoseOnTarget(Transform camera, TargetController controller, Matrix44F pose, Matrix4x4 displayCompensation, bool manualHorizontalFlip = false)
        {
            SetPoseOnTransform(controller.transform, camera.transform, pose, displayCompensation, false, false, manualHorizontalFlip);
        }

        /// <summary>
        /// <para xml:lang="en">Set transform <paramref name="t"/> using the matrix <paramref name="mat"/> in EasyAR coordinates.</para>
        /// <para xml:lang="zh">使用EasyAR坐标系矩阵<paramref name="mat"/>设置transform <paramref name="t"/>。</para>
        /// </summary>
        public static void SetMatrixOnTransform(Transform t, Matrix4x4 mat, bool keepScale)
        {
            Vector3 scaleKept = Vector3.zero;
            if (keepScale)
            {
                scaleKept = t.localScale;
            }
            //Notice: assume no reflection
            var scale = new Vector3 { x = Mathf.Sqrt(mat.GetColumn(0).sqrMagnitude), y = Mathf.Sqrt(mat.GetColumn(1).sqrMagnitude), z = Mathf.Sqrt(mat.GetColumn(2).sqrMagnitude) };
            var m = new Matrix4x4();
            m.SetColumn(0, mat.GetColumn(0) / scale.x);
            m.SetColumn(1, mat.GetColumn(1) / scale.y);
            m.SetColumn(2, mat.GetColumn(2) / scale.z);
            m.SetColumn(3, mat.GetColumn(3));

            var q = new Quaternion
            {
                w = Mathf.Sqrt(Mathf.Max(0, 1 + m[0, 0] + m[1, 1] + m[2, 2])) / 2,
                x = Mathf.Sqrt(Mathf.Max(0, 1 + m[0, 0] - m[1, 1] - m[2, 2])) / 2,
                y = Mathf.Sqrt(Mathf.Max(0, 1 - m[0, 0] + m[1, 1] - m[2, 2])) / 2,
                z = Mathf.Sqrt(Mathf.Max(0, 1 - m[0, 0] - m[1, 1] + m[2, 2])) / 2
            };

            q.x *= Mathf.Sign(q.x * (m[2, 1] - m[1, 2]));
            q.y *= Mathf.Sign(q.y * (m[0, 2] - m[2, 0]));
            q.z *= Mathf.Sign(q.z * (m[1, 0] - m[0, 1]));

            var translation = m.GetColumn(3);

            t.localRotation = new Quaternion { w = q.w, x = -q.x, y = -q.y, z = q.z };
            t.localPosition = new Vector3 { x = translation.x, y = translation.y, z = -translation.z };
            t.localScale = scale;
            if (keepScale)
            {
                t.localScale = scaleKept;
            }
        }

        /// <summary>
        /// <para xml:lang="en">Calculate and set the transform <paramref name="t"/> of one object using <paramref name="pose"/> and the other object's transform <paramref name="centerT"/>, to express the relation of the two objects in 3D space which is known in <paramref name="pose"/>.</para>
        /// <para xml:lang="zh">已知两个物体的的相对关系，通过<paramref name="pose"/>以及一个物体的transform <paramref name="centerT"/>计算并设置另一个物体的transform <paramref name="t"/>，以便在三维空间中将这个关系表达出来。</para>
        /// </summary>
        public static void SetPoseOnTransform(Transform t, Transform centerT, Matrix44F pose, Matrix4x4 displayCompensation, bool isCamera, bool onCamera, bool manualHorizontalFlip = false)
        {
            Matrix4x4 translateMatrix = Matrix4x4.identity;
            translateMatrix.m22 = -1;
            var translateTransform = translateMatrix * Matrix4x4.TRS(centerT.position, centerT.rotation, Vector3.one) * translateMatrix;

            var willSetPose = pose.ToUnityMatrix();

            if (onCamera)
            {
                Matrix4x4 cameraTransform;
                if (isCamera)
                {
                    cameraTransform = willSetPose;
                }
                else
                {
                    cameraTransform = willSetPose.inverse;
                }

                willSetPose = cameraTransform * displayCompensation.inverse;
            }
            else
            {
                Matrix4x4 targetTransform;
                if (isCamera)
                {
                    targetTransform = willSetPose.inverse;
                }
                else
                {
                    targetTransform = willSetPose;
                }
                willSetPose = displayCompensation * targetTransform;
            }

            if (manualHorizontalFlip)
            {
                Matrix4x4 hFlipTranslateMatrix = Matrix4x4.identity;
                hFlipTranslateMatrix.m00 = -1;
                willSetPose = hFlipTranslateMatrix * willSetPose * hFlipTranslateMatrix;
            }

            willSetPose = translateTransform * willSetPose;

            SetMatrixOnTransform(t, willSetPose, true);
        }
    }
}
