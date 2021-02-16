//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEngine;
using UnityEngine.Rendering;

namespace easyar
{
    /// <summary>
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls camera image rendering in the scene. Unity universal render pipeline (URP) is not supported yet, you can extend this class for URP support.</para>
    /// <para xml:lang="zh">在场景中控制camera图像渲染的<see cref="MonoBehaviour"/>，这个类目前不支持Unity universal render pipeline (URP) ，但你可以自行扩展这个类的实现来支持URP。</para>
    /// </summary>
    [RequireComponent(typeof(RenderCameraController))]
    public class CameraImageRenderer : MonoBehaviour
    {
        private RenderCameraController controller;
        private CommandBuffer commandBuffer;
        private CameraImageMaterial arMaterial;
        private Material material;
        private CameraParameters cameraParameters;
        private bool renderImageHFlip;
        private UserRequest request;

        /// <summary>
        /// <para xml:lang="en">Camera image rendering update event. This event will pass out the Material and texture size of current camera image rendering. This event only indicates a new render happens, while the camera image itself may not change.</para>
        /// <para xml:lang="zh">camera图像渲染更新的事件。这个事件会传出当前用于camera图像渲染的材质和贴图大小。当这个事件发生时，camera图像本身不一定有改变，它只表示一次渲染的发生。</para>
        /// </summary>
        public event Action<Material, Vector2> OnFrameRenderUpdate;
        private event Action<Camera, RenderTexture> TargetTextureChange;

        /// <summary>
        /// MonoBehaviour Awake
        /// </summary>
        protected virtual void Awake()
        {
            controller = GetComponent<RenderCameraController>();
            arMaterial = new CameraImageMaterial();
        }

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            UpdateCommandBuffer(controller ? controller.TargetCamera : null, material);
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected virtual void OnDisable()
        {
            RemoveCommandBuffer(controller ? controller.TargetCamera : null);
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            arMaterial.Dispose();
            if (request != null) { request.Dispose(); }
            if (cameraParameters != null) { cameraParameters.Dispose(); }
        }

        /// <summary>
        /// <para xml:lang="en">Get the <see cref="RenderTexture"/> of camera image.</para>
        /// <para xml:lang="en">The texture is a full sized image from <see cref="OutputFrame"/>, not cropped by the screen. The action <paramref name="targetTextureEventHandler"/> will pass out the <see cref="RenderTexture"/> and the <see cref="Camera"/> drawing the texture when the texture created or changed, will not call every frame or when the camera image data change. Calling this method will create external resources, and will trigger render when necessary, so make sure to release the resource using <see cref="DropTargetTexture"/> when not use.</para>
        /// <para xml:lang="zh">获取camera图像的<see cref="RenderTexture"/>。</para>
        /// <para xml:lang="zh">通过这个接口获取的texture是从<see cref="OutputFrame"/>获取的完整大小的图像，未经屏幕裁剪。<paramref name="targetTextureEventHandler"/> action会传出<see cref="RenderTexture"/>以及用于绘制texture的<see cref="Camera"/>。这个action不会每帧调用，也不会在camera图像数据发生变化的时候调用，它只会发生在texture本身创建或改变的时候。调用这个方法会创建额外的资源且会在必要时触发渲染，因此在不使用的时候需要调用<see cref="DropTargetTexture"/>释放资源。</para>
        /// </summary>
        public void RequestTargetTexture(Action<Camera, RenderTexture> targetTextureEventHandler)
        {
            if (request == null)
            {
                request = new UserRequest();
            }
            TargetTextureChange += targetTextureEventHandler;
            RenderTexture texture;
            request.UpdateTexture(controller ? controller.TargetCamera : null, material, out texture);
            if (TargetTextureChange != null && texture)
            {
                TargetTextureChange(controller.TargetCamera, texture);
            }
        }

        /// <summary>
        /// <para xml:lang="en">Release the <see cref="RenderTexture"/> of camera image. Internal resources will be released when all holders release.</para>
        /// <para xml:lang="zh">释放绘制camera图像的<see cref="RenderTexture"/>。内部资源将在所有持有者都释放后释放。</para>
        /// </summary>
        public void DropTargetTexture(Action<Camera, RenderTexture> targetTextureEventHandler)
        {
            if (controller)
            {
                targetTextureEventHandler(controller.TargetCamera, null);
            }
            TargetTextureChange -= targetTextureEventHandler;
            if (TargetTextureChange == null && request != null)
            {
                request.RemoveCommandBuffer(controller ? controller.TargetCamera : null);
                request.Dispose();
                request = null;
            }
        }

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Assemble response.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。组装响应方法。</para>
        /// </summary>
        public void OnAssemble(ARSession session)
        {
            session.FrameChange += OnFrameChange;
            session.FrameUpdate += OnFrameUpdate;
        }

        /// <summary>
        /// <para xml:lang="en">Set render image horizontal flip.</para>
        /// <para xml:lang="zh">设置渲染的图像的镜像翻转。</para>
        /// </summary>
        public void SetHFilp(bool hFlip)
        {
            renderImageHFlip = hFlip;
        }

        private void OnFrameChange(OutputFrame outputFrame, Matrix4x4 displayCompensation)
        {
            if (outputFrame == null)
            {
                material = null;
                UpdateCommandBuffer(controller ? controller.TargetCamera : null, material);
                if (request != null)
                {
                    request.UpdateCommandBuffer(controller ? controller.TargetCamera : null, material);
                    RenderTexture texture;
                    if (TargetTextureChange != null && request.UpdateTexture(controller.TargetCamera, material, out texture))
                    {
                        TargetTextureChange(controller.TargetCamera, texture);
                    }
                }
                return;
            }
            if (!enabled && request == null && OnFrameRenderUpdate == null)
            {
                return;
            }
            using (var frame = outputFrame.inputFrame())
            {
                using (var image = frame.image())
                {
                    var materialUpdated = arMaterial.UpdateByImage(image);
                    if (material != materialUpdated)
                    {
                        material = materialUpdated;
                        UpdateCommandBuffer(controller ? controller.TargetCamera : null, material);
                        if (request != null) { request.UpdateCommandBuffer(controller ? controller.TargetCamera : null, material); }
                    }
                }
                if (cameraParameters != null)
                {
                    cameraParameters.Dispose();
                }
                cameraParameters = frame.cameraParameters();
            }
        }

        private void OnFrameUpdate(OutputFrame outputFrame)
        {
            if (!controller || (!enabled && request == null && OnFrameRenderUpdate == null))
            {
                return;
            }

            if (request != null)
            {
                RenderTexture texture;
                if (TargetTextureChange != null && request.UpdateTexture(controller.TargetCamera, material, out texture))
                {
                    TargetTextureChange(controller.TargetCamera, texture);
                }
            }

            if (!material)
            {
                return;
            }

            bool cameraFront = cameraParameters.cameraDeviceType() == CameraDeviceType.Front ? true : false;
            var imageProjection = cameraParameters.imageProjection(controller.TargetCamera.aspect, EasyARController.Instance.Display.Rotation, false, cameraFront? !renderImageHFlip : renderImageHFlip).ToUnityMatrix();
            if (renderImageHFlip)
            {
                var translateMatrix = Matrix4x4.identity;
                translateMatrix.m00 = -1;
                imageProjection = translateMatrix * imageProjection;
            }
            material.SetMatrix("_TextureRotation", imageProjection);
            if (OnFrameRenderUpdate != null)
            {
                OnFrameRenderUpdate(material, new Vector2(Screen.width * controller.TargetCamera.rect.width, Screen.height * controller.TargetCamera.rect.height));
            }
        }

        private void UpdateCommandBuffer(Camera cam, Material material)
        {
            RemoveCommandBuffer(cam);
            if (!cam || !material)
            {
                return;
            }
            if (enabled)
            {
                commandBuffer = new CommandBuffer();
                commandBuffer.Blit(null, BuiltinRenderTextureType.CameraTarget, material);
                cam.AddCommandBuffer(CameraEvent.BeforeForwardOpaque, commandBuffer);
            }
        }

        private void RemoveCommandBuffer(Camera cam)
        {
            if (commandBuffer != null)
            {
                if (cam)
                {
                    cam.RemoveCommandBuffer(CameraEvent.BeforeForwardOpaque, commandBuffer);
                }
                commandBuffer.Dispose();
                commandBuffer = null;
            }
        }

        private class UserRequest : IDisposable
        {
            private RenderTexture texture;
            private CommandBuffer commandBuffer;

            ~UserRequest()
            {
                if (commandBuffer != null) { commandBuffer.Dispose(); }
                if (texture) { Destroy(texture); }
            }

            public void Dispose()
            {
                if (commandBuffer != null) { commandBuffer.Dispose(); }
                if (texture) { Destroy(texture); }
                GC.SuppressFinalize(this);
            }

            public bool UpdateTexture(Camera cam, Material material, out RenderTexture tex)
            {
                tex = texture;
                if (!cam || !material)
                {
                    if (texture)
                    {
                        Destroy(texture);
                        tex = texture = null;
                        return true;
                    }
                    return false;
                }
                int w = (int)(Screen.width * cam.rect.width);
                int h = (int)(Screen.height * cam.rect.height);
                if (texture && (texture.width != w || texture.height != h))
                {
                    Destroy(texture);
                }

                if (texture)
                {
                    return false;
                }
                else
                {
                    texture = new RenderTexture(w, h, 0);
                    UpdateCommandBuffer(cam, material);
                    tex = texture;
                    return true;
                }
            }

            public void UpdateCommandBuffer(Camera cam, Material material)
            {
                RemoveCommandBuffer(cam);
                if (!cam || !material)
                {
                    return;
                }
                if (texture)
                {
                    commandBuffer = new CommandBuffer();
                    commandBuffer.Blit(null, texture, material);
                    cam.AddCommandBuffer(CameraEvent.BeforeForwardOpaque, commandBuffer);
                }
            }

            public void RemoveCommandBuffer(Camera cam)
            {
                if (commandBuffer != null)
                {
                    if (cam)
                    {
                        cam.RemoveCommandBuffer(CameraEvent.BeforeForwardOpaque, commandBuffer);
                    }
                    commandBuffer.Dispose();
                    commandBuffer = null;
                }
            }
        }
    }
}
