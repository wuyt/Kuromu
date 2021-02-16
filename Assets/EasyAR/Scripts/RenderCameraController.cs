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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="Camera"/> in the scene. The <see cref="Camera"/> projection is set to fit real world <see cref="CameraDevice"/> or other optical device.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="Camera"/>的<see cref="MonoBehaviour"/>，<see cref="Camera"/> 投影矩阵会反映现实世界中的<see cref="CameraDevice"/>或其它光学设备。</para>
    /// </summary>
    public class RenderCameraController : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">The <see cref="Camera"/> representing real world <see cref="CameraDevice"/> or "eye" when using eyewears. It will be automatically set to the camera from <see cref="ARSession.Assembly"/> when assemble if not manually assigned.</para>
        /// <para xml:lang="zh">代表现实世界中<see cref="CameraDevice"/>或使用眼镜时的“眼睛”的<see cref="Camera"/>。如果未手动指定，它将在组装时被自动设为<see cref="ARSession.Assembly"/>中的camera。</para>
        /// </summary>
        public Camera TargetCamera;
        /// <summary>
        /// <para xml:lang="en">The external <see cref="CameraParameters"/> used to set <see cref="Camera"/> projection. It is used when the <see cref="Camera"/> is not representing the <see cref="CameraDevice"/> but other optical device, like "eye" from eyewears.</para>
        /// <para xml:lang="zh">用于设置<see cref="Camera"/>投影矩阵的外部<see cref="CameraParameters"/>。它通常在<see cref="Camera"/>不代表<see cref="CameraDevice"/>而是类似眼镜的“眼睛”的光学设备时使用。</para>
        /// </summary>
        public RenderCameraParameters ExternalParameters;

        private CameraImageRenderer cameraRenderer;
        private Matrix4x4 currentDisplayCompensation = Matrix4x4.identity;
        private CameraParameters cameraParameters;
        private bool projectHFilp;
        private ARSession arSession;
        private CameraRenderEvent renderEvent;

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            if (arSession)
            {
                arSession.FrameChange += OnFrameChange;
                arSession.FrameUpdate += OnFrameUpdate;
            }
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected virtual void OnDisable()
        {
            if (arSession)
            {
                arSession.FrameChange -= OnFrameChange;
                arSession.FrameUpdate -= OnFrameUpdate;
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Assemble response.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。组装响应方法。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Set projection horizontal flip when using <see cref="ARSession.ARHorizontalFlipMode.World"/> mode.</para>
        /// <para xml:lang="zh">在<see cref="ARSession.ARHorizontalFlipMode.World"/>模式下设置投影矩阵镜像翻转。</para>
        /// </summary>
        internal void SetProjectHFlip(bool hFlip)
        {
            projectHFilp = hFlip;
        }

        /// <summary>
        /// <para xml:lang="en">Set render image horizontal flip.</para>
        /// <para xml:lang="zh">设置渲染的图像的镜像翻转。</para>
        /// </summary>
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

            if (renderEvent == null)
            {
                if (TargetCamera)
                {
                    renderEvent = TargetCamera.gameObject.AddComponent<CameraRenderEvent>();
                    renderEvent.PreRender += () => { GL.invertCulling = projectHFilp; };
                    renderEvent.PostRender += () => { if (projectHFilp) { GL.invertCulling = false; } };
                }
            }
            else
            {
                if (!TargetCamera)
                {
                    Destroy(renderEvent);
                }
            }
        }
    }
}
