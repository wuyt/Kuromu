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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls AR session in the scene. One session contains a set of components assembled as <see cref="ARAssembly"/> and controls data flow in the whole life cycle. This class is the entrance of AR, it is possible to create a new session class and replace this one in the scene to implement fully different AR workflow.</para>
    /// <para xml:lang="zh">在场景中控制AR会话的<see cref="MonoBehaviour"/>。一个会话包含一组组装成<see cref="ARAssembly"/>的组件，并控制整个生命周期的数据流。这个类是AR的入口，如果要实现完全不同的AR工作流可以创建一个新的会话类并在场景中替换这个类。</para>
    /// </summary>
    public class ARSession : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">AR center mode. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh">AR中心模式。可随时修改，立即生效。</para>
        /// </summary>
        public ARCenterMode CenterMode;

        /// <summary>
        /// <para xml:lang="en">AR center <see cref="Target"/> when <see cref="CenterMode"/> == <see cref="ARCenterMode.FirstTarget"/> or <see cref="CenterMode"/> == <see cref="ARCenterMode.SpecificTarget"/>. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh"><see cref="CenterMode"/> == <see cref="ARCenterMode.FirstTarget"/> 或 <see cref="CenterMode"/> == <see cref="ARCenterMode.SpecificTarget"/>时的AR中心<see cref="Target"/>。可随时修改，立即生效。</para>
        /// </summary>
        public TargetController CenterTarget;

        /// <summary>
        /// <para xml:lang="en">AR center <see cref="WorldRootController"/> when <see cref="CenterMode"/> == <see cref="ARCenterMode.WorldRoot"/>. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh"><see cref="CenterMode"/> == <see cref="ARCenterMode.WorldRoot"/>时的AR中心<see cref="WorldRootController"/>。可随时修改，立即生效。</para>
        /// </summary>
        public WorldRootController WorldRootController;

        /// <summary>
        /// <para xml:lang="en">Horizontal flip rendering mode for normal camera. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh">正常相机的水平镜像渲染模式。可随时修改，立即生效。</para>
        /// </summary>
        public ARHorizontalFlipMode HorizontalFlipNormal;

        /// <summary>
        /// <para xml:lang="en">Horizontal flip rendering mode for front camera. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh">前置相机的水平镜像渲染模式。可随时修改，立即生效。</para>
        /// </summary>
        public ARHorizontalFlipMode HorizontalFlipFront = ARHorizontalFlipMode.World;

        /// <summary>
        /// <para xml:lang="en">Assemble mode used in <see cref="ARAssembly.Assemble(ARSession)"/>.</para>
        /// <para xml:lang="zh">在<see cref="ARAssembly.Assemble(ARSession)"/>中使用的组装模式。</para>
        /// </summary>
        public ARAssembly.AssembleMode AssembleMode;

        /// <summary>
        /// <para xml:lang="en">Assembly of AR components.</para>
        /// <para xml:lang="zh">AR组件的组装体。</para>
        /// </summary>
        [HideInInspector, SerializeField]
        public ARAssembly Assembly = new ARAssembly();

        private WorldRootController previousWorldRootController;
        private int frameIndex = -1;
        private KeyValuePair<bool, bool> frameStatus = new KeyValuePair<bool, bool>();

        /// <summary>
        /// <para xml:lang="en">Output frame change event delegate.</para>
        /// <para xml:lang="zh">输出帧发生改变的委托。</para>
        /// </summary>
        public delegate void FrameChangeAction(OutputFrame outputFrame, Matrix4x4 displayCompensation);

        /// <summary>
        /// <para xml:lang="en">Output frame change event. It is triggered when the data itself changes, the frequency is affected by <see cref="FrameSource"/> data change (like <see cref="CameraDevice"/> FPS).</para>
        /// <para xml:lang="zh">输出帧发生改变的事件。该事件会在数据本身产生变化的时候发生，频率受<see cref="FrameSource"/>数据变化（比如<see cref="CameraDevice"/>帧率）影响。</para>
        /// </summary>
        public event FrameChangeAction FrameChange;

        /// <summary>
        /// <para xml:lang="en">Output frame update event. It has the same frequency as MonoBehaviour Update.</para>
        /// <para xml:lang="zh">输出帧更新事件，该更新频率和MonoBehaviour Update频率相同。</para>
        /// </summary>
        public event Action<OutputFrame> FrameUpdate;

        /// <summary>
        /// <para xml:lang="en"><see cref="WorldRootController"/> change event</para>
        /// <para xml:lang="zh"><see cref="WorldRootController"/>改变的事件。</para>
        /// </summary>
        public event Action<WorldRootController> WorldRootChanged;

        /// <summary>
        /// <para xml:lang="en">AR center mode.</para>
        /// <para xml:lang="zh">AR中心模式。</para>
        /// </summary>
        public enum ARCenterMode
        {
            /// <summary>
            /// <para xml:lang="en">The session will use the first tracked <see cref="Target"/> as center.</para>
            /// <para xml:lang="en">You can move or rotate the <see cref="Target"/> and the <see cref="UnityEngine.Camera"/> will follow. You cannot manually change the <see cref="UnityEngine.Camera"/>'s transform in this mode. The relative transform from <see cref="Target"/> to <see cref="UnityEngine.Camera"/> is controlled by <see cref="OnFrameUpdate"/> code according to <see cref="ARAssembly.OutputFrame"/> data every frame.</para>
            /// <para xml:lang="zh">当前session是以第一个跟踪到的<see cref="Target"/>为中心的。</para>
            /// <para xml:lang="zh">你可以移动或旋转<see cref="Target"/>，<see cref="UnityEngine.Camera"/>会跟着动。在这个模式下你将无法手动控制<see cref="UnityEngine.Camera"/>的transform。<see cref="Target"/>和<see cref="UnityEngine.Camera"/>的相对位置关系由<see cref="OnFrameUpdate"/>代码根据每帧<see cref="ARAssembly.OutputFrame"/>数据控制。</para>
            /// </summary>
            FirstTarget,

            /// <summary>
            /// <para xml:lang="en">The session is <see cref="UnityEngine.Camera"/> centered.</para>
            /// <para xml:lang="en">You can move or rotate the <see cref="UnityEngine.Camera"/> and the <see cref="Target"/> will follow. You cannot manually change the <see cref="Target"/>'s transform in this mode. The relative transform from <see cref="Target"/> to <see cref="UnityEngine.Camera"/> is controlled by <see cref="OnFrameUpdate"/> code according to <see cref="ARAssembly.OutputFrame"/> data every frame.</para>
            /// <para xml:lang="zh">当前session是以<see cref="UnityEngine.Camera"/>为中心的。</para>
            /// <para xml:lang="zh">你可以移动或旋转<see cref="UnityEngine.Camera"/>，<see cref="Target"/>会跟着动。在这个模式下你将无法手动控制<see cref="Target"/>的transform。<see cref="Target"/>和<see cref="UnityEngine.Camera"/>的相对位置关系由<see cref="OnFrameUpdate"/>代码根据每帧<see cref="ARAssembly.OutputFrame"/>数据控制。</para>
            /// </summary>
            Camera,

            /// <summary>
            /// <para xml:lang="en">The session will use the <see cref="Target"/> specified by <see cref="CenterTarget"/> as center.</para>
            /// <para xml:lang="en">If the specified <see cref="Target"/> is not found, will fall back to <see cref="UnityEngine.Camera"/> center mode. The relative transform from <see cref="Target"/> to <see cref="UnityEngine.Camera"/> is controlled by <see cref="OnFrameUpdate"/> code according to <see cref="ARAssembly.OutputFrame"/> data every frame.</para>
            /// <para xml:lang="zh">当前session是以<see cref="CenterTarget"/>所指定的<see cref="Target"/>为中心的。</para>
            /// <para xml:lang="zh">如果这个指定的<see cref="Target"/>没有被跟踪，将会回退到<see cref="UnityEngine.Camera"/>中心模式。<see cref="Target"/>和<see cref="UnityEngine.Camera"/>的相对位置关系由<see cref="OnFrameUpdate"/>代码根据每帧<see cref="ARAssembly.OutputFrame"/>数据控制。</para>
            /// </summary>
            SpecificTarget,

            /// <summary>
            /// <para xml:lang="en">The session will use <see cref="WorldRootController"/> as center.</para>
            /// <para xml:lang="en">You can move or rotate the <see cref="WorldRootController"/> and the <see cref="UnityEngine.Camera"/> will follow. You cannot manually change the <see cref="UnityEngine.Camera"/>'s transform in this mode. The relative transform from <see cref="WorldRootController"/> to <see cref="UnityEngine.Camera"/> is controlled by <see cref="OnFrameUpdate"/> code according to <see cref="ARAssembly.OutputFrame"/> data every frame.</para>
            /// <para xml:lang="zh">当前session是以<see cref="WorldRootController"/>为中心的。</para>
            /// <para xml:lang="zh">你可以移动或旋转<see cref="WorldRootController"/>，<see cref="UnityEngine.Camera"/>会跟着动。在这个模式下你将无法手动控制<see cref="UnityEngine.Camera"/>的transform。<see cref="WorldRootController"/>和<see cref="UnityEngine.Camera"/>的相对位置关系由<see cref="OnFrameUpdate"/>代码根据每帧<see cref="ARAssembly.OutputFrame"/>数据控制。</para>
            /// </summary>
            WorldRoot,

            /// <summary>
            /// <para xml:lang="en">The session will behave like <see cref="Camera"/> mode, it is a mode designed for docking another AR system, like an AR eyewear SDK which usually has its own control of the <see cref="UnityEngine.Camera"/> and other objects from the system.</para>
            /// <para xml:lang="en">Everything from <see cref="ARAssembly.OutputFrame"/> will be treated as camera centered, but the <see cref="UnityEngine.Camera"/> itself may be controlled by another system or code, while the whole system linked together may have another center.</para>
            /// <para xml:lang="en">You can move or rotate the <see cref="UnityEngine.Camera"/> and the <see cref="Target"/> will follow. You cannot manually change the <see cref="Target"/>'s transform in this mode. The relative transform from <see cref="Target"/> to <see cref="UnityEngine.Camera"/> is controlled by <see cref="OnFrameUpdate"/> code according to <see cref="ARAssembly.OutputFrame"/> data every frame.</para>
            /// <para xml:lang="zh">当前session与<see cref="Camera"/>模式行为相同。它被用来连接另一个AR系统，比如AR眼镜SDK（通常它有自己对<see cref="UnityEngine.Camera"/>和其它物体的控制策略）。</para>
            /// <para xml:lang="zh"><see cref="ARAssembly.OutputFrame"/>内所有物体都将被按照camera 中心来调整，但<see cref="UnityEngine.Camera"/>自身可能会由另一个系统或另一段代码来控制，而连接在一起的整个系统可能会有另一个中心。</para>
            /// <para xml:lang="zh">你可以移动或旋转<see cref="UnityEngine.Camera"/>，<see cref="Target"/>会跟着动。在这个模式下你将无法手动控制<see cref="Target"/>的transform。<see cref="Target"/>和<see cref="UnityEngine.Camera"/>的相对位置关系由<see cref="OnFrameUpdate"/>代码根据每帧<see cref="ARAssembly.OutputFrame"/>数据控制。</para>
            /// </summary>
            ExternalControl,
        }

        /// <summary>
        /// <para xml:lang="en">Horizontal flip rendering mode.</para>
        /// <para xml:lang="en">In a flip rendering mode, the camera image will be mirrored. And to display to tracked objects in the right way, it will affect the 3D object rendering as well, so there are two different ways of doing horizontal flip. Horizontal flip can only work in object sensing like image or object tracking algorithms.</para>
        /// <para xml:lang="zh">水平镜像渲染模式。</para>
        /// <para xml:lang="zh">在水平翻转状态下，相机图像将镜像显示，为确保物体跟踪正常，它同时会影响3D物体的渲染，因此提供两种不同的方式。水平翻转只能在物体感知（比如图像跟踪或物体跟踪）算法下工作。</para>
        /// </summary>
        public enum ARHorizontalFlipMode
        {
            /// <summary>
            /// <para xml:lang="en">No flip.</para>
            /// <para xml:lang="zh">不翻转。</para>
            /// </summary>
            None,
            /// <summary>
            /// <para xml:lang="en">Render with horizontal flip, the camera image will be flipped in rendering, the camera projection matrix will be changed to do flip rendering. Target scale will not change.</para>
            /// <para xml:lang="zh">水平镜像渲染，camera图像会镜像显示，camera投影矩阵会变化进行镜像渲染，target scale不会改变。</para>
            /// </summary>
            World,
            /// <summary>
            /// <para xml:lang="en">Render with horizontal flip, the camera image will be flipped in rendering, the target scale will be changed to do flip rendering. Camera projection matrix will not change.</para>
            /// <para xml:lang="zh">水平镜像渲染，camera图像会镜像显示，target scale会改变进行镜像渲染，camera投影矩阵不会改变。</para>
            /// </summary>
            Target,
        }

        /// <summary>
        /// <para xml:lang="en"><see cref="CameraParameters"/> from current frame.</para>
        /// <para xml:lang="zh">当前帧的<see cref="CameraParameters"/>。</para>
        /// </summary>
        public Optional<CameraParameters> FrameCameraParameters { get; private set; }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        private void Start()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            Assembly.Assemble(this);
            if (!WorldRootController) { WorldRootController = FindObjectOfType<WorldRootController>(); }
        }

        /// <summary>
        /// MonoBehaviour Update
        /// </summary>
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

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
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
