//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.Collections.Generic;
using UnityEngine;

namespace easyar
{
    public class ARSession : MonoBehaviour
    {
        public ARCenterMode CenterMode;
        public TargetController CenterTarget;
        public WorldRootController WorldRootController;
        public ARHorizontalFlipMode HorizontalFlipNormal;
        // default horizontal flip for front camera
        public ARHorizontalFlipMode HorizontalFlipFront = ARHorizontalFlipMode.World;
        public ARAssembly.AssembleMode AssembleMode;
        [HideInInspector, SerializeField]
        public ARAssembly Assembly = new ARAssembly();

        private WorldRootController previousWorldRootController;
        private int frameIndex = -1;
        private KeyValuePair<bool, bool> frameStatus = new KeyValuePair<bool, bool>();

        public delegate void FrameChangeAction(OutputFrame outputFrame, Matrix4x4 displayCompensation);

        public event FrameChangeAction FrameChange;
        public event Action<OutputFrame> FrameUpdate;
        public event Action<WorldRootController> WorldRootChanged;

        public enum ARCenterMode
        {
            FirstTarget,
            Camera,
            SpecificTarget,
            WorldRoot,
            ExternalControl,
        }

        public enum ARHorizontalFlipMode
        {
            None,
            World,
            Target,
        }

        public Optional<CameraParameters> FrameCameraParameters { get; private set; }

        private void Start()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            Assembly.Assemble(this);
            if (!WorldRootController) { WorldRootController = FindObjectOfType<WorldRootController>(); }
        }

        private void Update()
        {
            if (!Assembly.Ready)
            {
                OnEmptyFrame();
                return;
            }
            if (WorldRootController != previousWorldRootController)
            {
                if (WorldRootChanged != null)
                {
                    WorldRootChanged(WorldRootController);
                }
                previousWorldRootController = WorldRootController;
            }
            var oFrame = Assembly.OutputFrame;
            if (oFrame.OnNone)
            {
                OnEmptyFrame();
                return;
            }

            using (var outputFrame = oFrame.Value)
            using (var iFrame = outputFrame.inputFrame())
            {
                if (FrameCameraParameters.OnSome)
                {
                    FrameCameraParameters.Value.Dispose();
                }
                FrameCameraParameters = iFrame.cameraParameters();
                var displayCompensation = EasyARController.Instance.Display.GetCompensation(FrameCameraParameters.Value);
                var index = iFrame.index();
                if (frameIndex != index && FrameChange != null)
                {
                    FrameChange(outputFrame, displayCompensation);
                }
                frameIndex = index;
                // update self first, some flags will pass down to other components
                OnFrameUpdate(outputFrame, iFrame, displayCompensation);
                if (FrameUpdate != null)
                {
                    FrameUpdate(outputFrame);
                }
            }
        }

        private void OnDestroy()
        {
            Assembly.Dispose();
            if (FrameCameraParameters.OnSome)
            {
                FrameCameraParameters.Value.Dispose();
            }
        }

        private void OnFrameUpdate(OutputFrame outputFrame, InputFrame inputFrame, Matrix4x4 displayCompensation)
        {
            // world root
            if (Assembly.RequireWorldCenter && !WorldRootController)
            {
                Debug.Log("WorldRoot not found, create from " + typeof(ARSession));
                var gameObject = new GameObject("WorldRoot");
                WorldRootController = gameObject.AddComponent<WorldRootController>();
                if (WorldRootChanged != null)
                {
                    WorldRootChanged(WorldRootController);
                }
                previousWorldRootController = WorldRootController;
            }
            if (!Assembly.RequireWorldCenter && CenterMode == ARCenterMode.WorldRoot)
            {
                Debug.LogWarning("ARCenterMode.WorldRoot not available for target only tracking");
                CenterMode = ARCenterMode.FirstTarget;
            }

            // horizontal flip
            var hflip = HorizontalFlipNormal;
            using (var cameraParameters = inputFrame.cameraParameters())
            {
                if (cameraParameters.cameraDeviceType() == CameraDeviceType.Front)
                {
                    hflip = HorizontalFlipFront;
                }
            }
            var worldHFlip = false;
            var targetHFlip = false;
            switch (hflip)
            {
                case ARHorizontalFlipMode.World:
                    worldHFlip = true;
                    targetHFlip = false;
                    break;
                case ARHorizontalFlipMode.Target:
                    worldHFlip = false;
                    targetHFlip = true;
                    break;
                default:
                    break;
            }
            foreach (var renderCamera in Assembly.RenderCameras)
            {
                renderCamera.SetProjectHFlip(worldHFlip);
                renderCamera.SetRenderImageHFilp(worldHFlip || targetHFlip);
            }
            foreach (var filter in Assembly.FrameFilters)
            {
                filter.SetHFlip(targetHFlip);
            }

            // dispatch results
            var results = outputFrame.results();
            var motionTrackingStatus = Optional<MotionTrackingStatus>.CreateNone();
            if (inputFrame.hasSpatialInformation())
            {
                motionTrackingStatus = inputFrame.trackingStatus();
            }
            var resultControllers = DispatchResults(results, motionTrackingStatus);

            // get camera pose if available
            var cameraPose = Optional<Matrix44F>.Empty;
            if (Assembly.RequireWorldCenter)
            {
                if (motionTrackingStatus.OnSome)
                {
                    if (motionTrackingStatus.Value != MotionTrackingStatus.NotTracking)
                    {
                        cameraPose = inputFrame.cameraTransform();
                    }
                }
                else
                {
                    foreach (var result in resultControllers)
                    {
                        if (result.Key.OnNone)
                        {
                            cameraPose = result.Value;
                            break;
                        }
                    }
                }
            }

            // get center target pose if available
            var centerTargetPose = Optional<Matrix44F>.Empty;

            if (CenterMode == ARCenterMode.FirstTarget || CenterMode == ARCenterMode.SpecificTarget)
            {
                foreach (var result in resultControllers)
                {
                    if (!CenterTarget)
                        break;
                    if (result.Key.OnNone)
                        continue;
                    if (result.Key == CenterTarget)
                    {
                        centerTargetPose = result.Value;
                        break;
                    }
                }

                if (CenterMode == ARCenterMode.FirstTarget && centerTargetPose.OnNone)
                {
                    foreach (var result in resultControllers)
                    {
                        if (result.Key.OnNone)
                            continue;
                        CenterTarget = result.Key.Value;
                        centerTargetPose = result.Value;
                        break;
                    }
                }
            }
            else
            {
                CenterTarget = null;
            }

            // set camera transform first
            if (CenterMode == ARCenterMode.FirstTarget || CenterMode == ARCenterMode.SpecificTarget)
            {
                if (CenterTarget && centerTargetPose.OnSome)
                {
                    TransformUtil.SetTargetPoseOnCamera(Assembly.CameraRoot, CenterTarget, centerTargetPose.Value, displayCompensation, targetHFlip);
                }
            }
            else if (CenterMode == ARCenterMode.WorldRoot)
            {
                if (WorldRootController && cameraPose.OnSome)
                {
                    TransformUtil.SetCameraPoseOnCamera(Assembly.CameraRoot, WorldRootController, cameraPose.Value, displayCompensation, targetHFlip);
                }
            }

            // set target and world root transform
            if (CenterMode == ARCenterMode.Camera)
            {
                foreach (var result in resultControllers)
                {
                    if (result.Key.OnSome)
                    {
                        TransformUtil.SetTargetPoseOnTarget(Assembly.CameraRoot, result.Key.Value, result.Value, displayCompensation, targetHFlip);
                    }
                }
                if (WorldRootController && cameraPose.OnSome)
                {
                    TransformUtil.SetCameraPoseOnWorldRoot(Assembly.CameraRoot, WorldRootController, cameraPose.Value, displayCompensation, targetHFlip);
                }
            }
            else if (CenterMode == ARCenterMode.WorldRoot)
            {
                foreach (var result in resultControllers)
                {
                    if (result.Key.OnSome)
                    {
                        TransformUtil.SetTargetPoseOnTarget(Assembly.CameraRoot, result.Key.Value, result.Value, displayCompensation, targetHFlip);
                    }
                }
            }
            else if (CenterMode == ARCenterMode.FirstTarget || CenterMode == ARCenterMode.SpecificTarget)
            {
                foreach (var result in resultControllers)
                {
                    if (result.Key.OnSome && result.Key.Value != CenterTarget)
                    {
                        TransformUtil.SetTargetPoseOnTarget(Assembly.CameraRoot, result.Key.Value, result.Value, displayCompensation, targetHFlip);
                    }
                }
                if (WorldRootController && cameraPose.OnSome)
                {
                    TransformUtil.SetCameraPoseOnWorldRoot(Assembly.CameraRoot, WorldRootController, cameraPose.Value, displayCompensation, targetHFlip);
                }
            }
            else if (CenterMode == ARCenterMode.ExternalControl)
            {
                foreach (var result in resultControllers)
                {
                    if (result.Key.OnSome)
                    {
                        TransformUtil.SetTargetPoseOnTarget(Assembly.CameraRoot, result.Key.Value, result.Value, displayCompensation, targetHFlip);
                    }
                }
            }

            // dispose results
            foreach (var result in results)
            {
                if (result.OnSome)
                {
                    result.Value.Dispose();
                }
            }
        }

        private void OnEmptyFrame()
        {
            if (frameStatus.Key)
            {
                if (FrameChange != null)
                {
                    FrameChange(null, Matrix4x4.identity);
                }
                DispatchResults(null, frameStatus.Value ? MotionTrackingStatus.NotTracking : Optional<MotionTrackingStatus>.CreateNone());
            }
            if (FrameCameraParameters.OnSome)
            {
                FrameCameraParameters.Value.Dispose();
                FrameCameraParameters = Optional<CameraParameters>.CreateNone();
            }
        }

        private List<KeyValuePair<Optional<TargetController>, Matrix44F>> DispatchResults(Optional<List<Optional<FrameFilterResult>>> results, Optional<MotionTrackingStatus> motionTrackingStatus)
        {
            var resultControllers = new List<KeyValuePair<Optional<TargetController>, Matrix44F>>();
            var joinIndex = 0;
            foreach (var filter in Assembly.FrameFilters)
            {
                if (!filter)
                {
                    Assembly.Break();
                }
                if (filter is FrameFilter.IOutputFrameSource)
                {
                    var outputFrameSource = filter as FrameFilter.IOutputFrameSource;
                    var list = outputFrameSource.OnResult(results.OnSome ? results.Value[joinIndex] : null);
                    if (list != null)
                    {
                        resultControllers.AddRange(list);
                    }
                    joinIndex++;
                }
                if (motionTrackingStatus.OnSome && filter is FrameFilter.ISpatialInformationSink)
                {
                    (filter as FrameFilter.ISpatialInformationSink).OnTracking(motionTrackingStatus.Value);
                }
            }

            if (Assembly.RequireWorldCenter)
            {
                if (motionTrackingStatus.OnSome)
                {
                    WorldRootController.OnTracking(motionTrackingStatus.Value);
                }
                else
                {
                    var trackingStatus = MotionTrackingStatus.NotTracking;
                    foreach (var result in resultControllers)
                    {
                        if (result.Key.OnNone)
                        {
                            trackingStatus = MotionTrackingStatus.Tracking;
                            break;
                        }
                    }
                    WorldRootController.OnTracking(trackingStatus);
                }
            }
            frameStatus = new KeyValuePair<bool, bool>(results.OnSome, motionTrackingStatus.OnSome);
            return resultControllers;
        }
    }
}
