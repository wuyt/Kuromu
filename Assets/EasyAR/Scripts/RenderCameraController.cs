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
    public class RenderCameraController : MonoBehaviour
    {
        public Camera TargetCamera;
        public RenderCameraParameters ExternalParameters;

        private CameraImageRenderer cameraRenderer;
        private Matrix4x4 currentDisplayCompensation = Matrix4x4.identity;
        private CameraParameters cameraParameters;
        private bool projectHFilp;
        private ARSession arSession;

        protected virtual void OnEnable()
        {
            if (arSession)
            {
                arSession.FrameChange += OnFrameChange;
                arSession.FrameUpdate += OnFrameUpdate;
            }
        }

        protected virtual void OnDisable()
        {
            if (arSession)
            {
                arSession.FrameChange -= OnFrameChange;
                arSession.FrameUpdate -= OnFrameUpdate;
            }
        }

        protected virtual void OnDestroy()
        {
            if (cameraParameters != null)
            {
                cameraParameters.Dispose();
            }
            if (ExternalParameters)
            {
                ExternalParameters.Dispose();
            }
        }

        internal void OnAssemble(ARSession session)
        {
            arSession = session;
            if (!TargetCamera)
            {
                TargetCamera = session.Assembly.Camera;
            }
            if (enabled)
            {
                arSession.FrameChange += OnFrameChange;
                arSession.FrameUpdate += OnFrameUpdate;
            }
            cameraRenderer = GetComponent<CameraImageRenderer>();
            if (cameraRenderer)
            {
                cameraRenderer.OnAssemble(session);
            }
        }

        internal void SetProjectHFlip(bool hFlip)
        {
            projectHFilp = hFlip;
        }

        internal void SetRenderImageHFilp(bool hFlip)
        {
            if (cameraRenderer)
            {
                cameraRenderer.SetHFilp(hFlip);
            }
        }

        private void OnFrameChange(OutputFrame outputFrame, Matrix4x4 displayCompensation)
        {
            if (outputFrame == null)
            {
                return;
            }
            currentDisplayCompensation = displayCompensation.inverse;

            using (var frame = outputFrame.inputFrame())
            {
                if (cameraParameters != null)
                {
                    cameraParameters.Dispose();
                }
                cameraParameters = frame.cameraParameters();
                if (ExternalParameters)
                {
                    ExternalParameters.Build(cameraParameters);
                }
            }
        }

        private void OnFrameUpdate(OutputFrame outputFrame)
        {
            var camParameters = ExternalParameters ? ExternalParameters.Parameters : cameraParameters;
            var projection = camParameters.projection(TargetCamera.nearClipPlane, TargetCamera.farClipPlane, TargetCamera.aspect, EasyARController.Instance.Display.Rotation, false, false).ToUnityMatrix();
            if (ExternalParameters)
            {
                projection *= ExternalParameters.Transform;
            }
            projection *= currentDisplayCompensation;
            if (projectHFilp)
            {
                var translateMatrix = Matrix4x4.identity;
                translateMatrix.m00 = -1;
                projection = translateMatrix * projection;
            }
            TargetCamera.projectionMatrix = projection;
            GL.invertCulling = projectHFilp;
        }
    }
}
