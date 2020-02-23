//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEngine;
using UnityEngine.Rendering;

namespace easyar
{
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

        public event Action<Material, Vector2> OnFrameRenderUpdate;
        private event Action<Camera, RenderTexture> TargetTextureChange;

        protected virtual void Awake()
        {
            controller = GetComponent<RenderCameraController>();
            arMaterial = new CameraImageMaterial();
        }

        protected virtual void OnEnable()
        {
            UpdateCommandBuffer(controller ? controller.TargetCamera : null, material);
        }

        protected virtual void OnDisable()
        {
            RemoveCommandBuffer(controller ? controller.TargetCamera : null);
        }

        protected virtual void OnDestroy()
        {
            arMaterial.Dispose();
            if (request != null) { request.Dispose(); }
            if (cameraParameters != null) { cameraParameters.Dispose(); }
        }

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

        public void OnAssemble(ARSession session)
        {
            session.FrameChange += OnFrameChange;
            session.FrameUpdate += OnFrameUpdate;
        }

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
