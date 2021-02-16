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
    /// <para xml:lang="en">Shaders to draw camera image.</para>
    /// <para xml:lang="zh">绘制camera图像的shader。</para>
    /// </summary>
    [CreateAssetMenu(menuName = "EasyAR/Shaders")]
    public class EasyARShaders : ScriptableObject
    {
        /// <summary>
        /// <para xml:lang="en"><see cref="Shader"/> to draw image of <see cref="PixelFormat.RGB888"/> or <see cref="PixelFormat.RGBA8888"/> format.</para>
        /// <para xml:lang="zh">处理图片数据格式为<see cref="PixelFormat.RGB888"/>或<see cref="PixelFormat.RGBA8888"/>的<see cref="Shader"/>。</para>
        /// </summary>
        public Shader RGB;
        /// <summary>
        /// <para xml:lang="en"><see cref="Shader"/> to draw image of <see cref="PixelFormat.BGR888"/> or <see cref="PixelFormat.BGRA8888"/> format.</para>
        /// <para xml:lang="zh">处理图片数据格式为<see cref="PixelFormat.BGR888"/>或<see cref="PixelFormat.BGRA8888"/>的<see cref="Shader"/>。</para>
        /// </summary>
        public Shader BGR;
        /// <summary>
        /// <para xml:lang="en"><see cref="Shader"/> to draw image of <see cref="PixelFormat.Gray"/> format.</para>
        /// <para xml:lang="zh">处理图片数据格式为<see cref="PixelFormat.Gray"/>的<see cref="Shader"/>。</para>
        /// </summary>
        public Shader GRAY;
        /// <summary>
        /// <para xml:lang="en"><see cref="Shader"/> to draw image of <see cref="PixelFormat.YUV_YV12"/> or <see cref="PixelFormat.YUV_I420"/> format.</para>
        /// <para xml:lang="zh">处理图片数据格式为<see cref="PixelFormat.YUV_YV12"/>或<see cref="PixelFormat.YUV_I420"/>的<see cref="Shader"/>。</para>
        /// </summary>
        public Shader YUV_I420_YV12;
        /// <summary>
        /// <para xml:lang="en"><see cref="Shader"/> to draw image of <see cref="PixelFormat.YUV_NV12"/> format.</para>
        /// <para xml:lang="zh">处理图片数据格式为<see cref="PixelFormat.YUV_NV12"/>的<see cref="Shader"/>。</para>
        /// </summary>
        public Shader YUV_NV12;
        /// <summary>
        /// <para xml:lang="en"><see cref="Shader"/> to draw image of <see cref="PixelFormat.YUV_NV21"/> format.</para>
        /// <para xml:lang="zh">处理图片数据格式为<see cref="PixelFormat.YUV_NV21"/>的<see cref="Shader"/>。</para>
        /// </summary>
        public Shader YUV_NV21;
    }
}
