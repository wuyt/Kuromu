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
    /// <para xml:lang="en">Material to render camera image.</para>
    /// <para xml:lang="zh">用于渲染camera图像的材质。</para>
    /// </summary>
    internal class CameraImageMaterial : IDisposable
    {
        private static EasyARShaders shaders;
        private Material mat;
        private Texture2D[] textures = new Texture2D[0];
        private PixelFormat format;
        private int imageWidth;
        private int imageHeight;

        public CameraImageMaterial()
        {
            if (!shaders)
            {
                shaders = Resources.Load<EasyARShaders>("EasyAR/Shaders");
            }
        }

        ~CameraImageMaterial()
        {
            DisposeResources();
        }

        /// <summary>
        /// <para xml:lang="en">Dispose resources.</para>
        /// <para xml:lang="zh">销毁资源。</para>
        /// </summary>
        public void Dispose()
        {
            DisposeResources();
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// <para xml:lang="en">Update material using <paramref name="image"/>.</para>
        /// <para xml:lang="zh">使用<paramref name="image"/>更新材质。</para>
        /// </summary>
        public Material UpdateByImage(Image image)
        {
            var recreateMaterial = false;
            if (image.width() != imageWidth || image.height() != imageHeight || image.format() != format)
            {
                DisposeResources();
                imageWidth = image.width();
                imageHeight = image.height();
                format = image.format();
                recreateMaterial = true;
            }
            using (var buffer = image.buffer())
            {
                var ptr = buffer.data();
                var resolution = imageWidth * imageHeight;
                switch (format)
                {
                    case PixelFormat.Gray:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[1];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.Alpha8, false);
                            mat = new Material(shaders.GRAY);
                            mat.SetTexture("_grayTexture", textures[0]);
                        }
                        textures[0].LoadRawTextureData(ptr, resolution);
                        textures[0].Apply();
                        break;
                    case PixelFormat.YUV_NV21:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[2];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.Alpha8, false);
                            textures[1] = new Texture2D(imageWidth / 2, imageHeight / 2, TextureFormat.RGBA4444, false);
                            mat = new Material(shaders.YUV_NV21);
                            mat.SetTexture("_yTexture", textures[0]);
                            mat.SetTexture("_uvTexture", textures[1]);
                        }
                        textures[0].LoadRawTextureData(ptr, resolution);
                        textures[0].Apply();
                        textures[1].LoadRawTextureData(new IntPtr(ptr.ToInt64() + resolution), resolution);
                        textures[1].Apply();

                        break;
                    case PixelFormat.YUV_NV12:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[2];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.Alpha8, false);
                            textures[1] = new Texture2D(imageWidth / 2, imageHeight / 2, TextureFormat.RGBA4444, false);
                            mat = new Material(shaders.YUV_NV12);
                            mat.SetTexture("_yTexture", textures[0]);
                            mat.SetTexture("_uvTexture", textures[1]);
                        }
                        textures[0].LoadRawTextureData(ptr, resolution);
                        textures[0].Apply();
                        textures[1].LoadRawTextureData(new IntPtr(ptr.ToInt64() + resolution), resolution);
                        textures[1].Apply();
                        break;
                    case PixelFormat.YUV_I420:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[3];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.Alpha8, false);
                            textures[1] = new Texture2D(imageWidth / 2, imageHeight / 2, TextureFormat.Alpha8, false);
                            textures[2] = new Texture2D(imageWidth / 2, imageHeight / 2, TextureFormat.Alpha8, false);
                            mat = new Material(shaders.YUV_I420_YV12);
                            mat.SetTexture("_yTexture", textures[0]);
                            mat.SetTexture("_uTexture", textures[1]);
                            mat.SetTexture("_vTexture", textures[2]);
                        }
                        textures[0].LoadRawTextureData(new IntPtr(ptr.ToInt64()), resolution);
                        textures[0].Apply();
                        textures[1].LoadRawTextureData(new IntPtr(ptr.ToInt64() + resolution), resolution / 4);
                        textures[1].Apply();
                        textures[2].LoadRawTextureData(new IntPtr(ptr.ToInt64() + resolution + resolution / 4), resolution / 4);
                        textures[2].Apply();
                        break;
                    case PixelFormat.YUV_YV12:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[3];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.Alpha8, false);
                            textures[1] = new Texture2D(imageWidth / 2, imageHeight / 2, TextureFormat.Alpha8, false);
                            textures[2] = new Texture2D(imageWidth / 2, imageHeight / 2, TextureFormat.Alpha8, false);
                            mat = new Material(shaders.YUV_I420_YV12);
                            mat.SetTexture("_yTexture", textures[0]);
                            mat.SetTexture("_uTexture", textures[1]);
                            mat.SetTexture("_vTexture", textures[2]);
                        }
                        textures[0].LoadRawTextureData(new IntPtr(ptr.ToInt64()), resolution);
                        textures[0].Apply();
                        textures[1].LoadRawTextureData(new IntPtr(ptr.ToInt64() + resolution + resolution / 4), resolution / 4);
                        textures[1].Apply();
                        textures[2].LoadRawTextureData(new IntPtr(ptr.ToInt64() + resolution), resolution / 4);
                        textures[2].Apply();
                        break;
                    case PixelFormat.RGB888:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[1];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.RGB24, false);
                            mat = new Material(shaders.RGB);
                            mat.SetTexture("_MainTex", textures[0]);
                        }
                        textures[0].LoadRawTextureData(new IntPtr(ptr.ToInt64()), buffer.size());
                        textures[0].Apply();
                        break;
                    case PixelFormat.BGR888:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[1];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.RGB24, false);
                            mat = new Material(shaders.BGR);
                            mat.SetTexture("_MainTex", textures[0]);
                        }
                        textures[0].LoadRawTextureData(new IntPtr(ptr.ToInt64()), buffer.size());
                        textures[0].Apply();
                        break;
                    case PixelFormat.RGBA8888:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[1];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.RGBA32, false);
                            mat = new Material(shaders.RGB);
                            mat.SetTexture("_MainTex", textures[0]);
                        }
                        textures[0].LoadRawTextureData(new IntPtr(ptr.ToInt64()), buffer.size());
                        textures[0].Apply();
                        break;
                    case PixelFormat.BGRA8888:
                        if (recreateMaterial)
                        {
                            textures = new Texture2D[1];
                            textures[0] = new Texture2D(imageWidth, imageHeight, TextureFormat.RGBA32, false);
                            mat = new Material(shaders.BGR);
                            mat.SetTexture("_MainTex", textures[0]);
                        }
                        textures[0].LoadRawTextureData(new IntPtr(ptr.ToInt64()), buffer.size());
                        textures[0].Apply();
                        break;
                    default:
                        break;
                }
            }
            return mat;
        }

        private void DisposeResources()
        {
            if (mat)
            {
                UnityEngine.Object.Destroy(mat);
            }
            foreach(var texture in textures)
            {
                UnityEngine.Object.Destroy(texture);
            }
        }
    }
}
