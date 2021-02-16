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
    /// <para xml:lang="en">Extend EasyAR Sense API and Unity API for convenience to do operations like data conversion.</para>
    /// <para xml:lang="zh">扩展EasyAR Sense API 及 Unity API，为数据转换等操作提供便利。</para>
    /// </summary>
    public static class APIExtend
    {
        /// <summary>
        /// <para xml:lang="en">Convert <see cref="Matrix44F"/> to <see cref="Matrix4x4"/>.</para>
        /// <para xml:lang="zh">将<see cref="Matrix44F"/>转成<see cref="Matrix4x4"/>。</para>
        /// </summary>
        public static Matrix4x4 ToUnityMatrix(this Matrix44F matrix44F)
        {
            var matrix4x4 = new Matrix4x4();
            matrix4x4.SetRow(0, new Vector4(matrix44F.data_0, matrix44F.data_1, matrix44F.data_2, matrix44F.data_3));
            matrix4x4.SetRow(1, new Vector4(matrix44F.data_4, matrix44F.data_5, matrix44F.data_6, matrix44F.data_7));
            matrix4x4.SetRow(2, new Vector4(matrix44F.data_8, matrix44F.data_9, matrix44F.data_10, matrix44F.data_11));
            matrix4x4.SetRow(3, new Vector4(matrix44F.data_12, matrix44F.data_13, matrix44F.data_14, matrix44F.data_15));
            return matrix4x4;
        }

        /// <summary>
        /// <para xml:lang="en">Convert <see cref="Vector2"/> to <see cref="Vec2F"/>.</para>
        /// <para xml:lang="zh">将<see cref="Vector2"/>转成<see cref="Vec2F"/>。</para>
        /// </summary>
        public static Vec2F ToEasyARVector(this Vector2 vec2)
        {
            return new Vec2F(vec2.x, vec2.y);
        }

        /// <summary>
        /// <para xml:lang="en">Convert <see cref="Vector3"/> to <see cref="Vec3F"/>.</para>
        /// <para xml:lang="zh">将<see cref="Vector3"/>转成<see cref="Vec3F"/>。</para>
        /// </summary>
        public static Vec3F ToEasyARVector(this Vector3 vec3)
        {
            return new Vec3F(vec3.x, vec3.y, vec3.z);
        }

        /// <summary>
        /// <para xml:lang="en">Convert <see cref="Vec2F"/> to <see cref="Vector2"/>.</para>
        /// <para xml:lang="zh">将<see cref="Vec2F"/>转成<see cref="Vector2"/>。</para>
        /// </summary>
        public static Vector2 ToUnityVector(this Vec2F vec2)
        {
            return new Vector2(vec2.data_0, vec2.data_1);
        }

        /// <summary>
        /// <para xml:lang="en">Convert <see cref="Vec3F"/> to <see cref="Vector3"/>.</para>
        /// <para xml:lang="zh">将<see cref="Vec3F"/>转成<see cref="Vector3"/>。</para>
        /// </summary>
        public static Vector3 ToUnityVector(this Vec3F vec3)
        {
            return new Vector3(vec3.data_0, vec3.data_1, vec3.data_2);
        }
    }
}
