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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="Recorder"/> in the scene, providing a few extensions in the Unity environment. There is no need to use <see cref="Recorder"/> directly.</para>
    /// <para xml:lang="en">You have full control of what is recorded. The recorder do not record the screen or the camera output silently, the video data being recorded should be passed in continuously using <see cref="RecordFrame"/></para>
    /// <para xml:lang="zh">在场景中控制<see cref="Recorder"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。不需要直接使用<see cref="Recorder"/>。</para>
    /// <para xml:lang="zh">用户对视频录制的内容有完全控制，录屏功能不会默默地录制屏幕或是camera输出，录制的视频数据需要通过<see cref="RecordFrame"/>不断传入。</para>
    /// </summary>
    public class VideoRecorder : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">Record profile used only when create.</para>
        /// <para xml:lang="zh">创建时使用的录屏配置，只在创建时使用。</para>
        /// </summary>
        public RecordProfile Profile = RecordProfile.Quality_Default;
        /// <summary>
        /// <para xml:lang="en">Record video orientation used only when create.</para>
        /// <para xml:lang="zh">创建时使用的录屏视频朝向，只在创建时使用。</para>
        /// </summary>
        public VideoOrientation Orientation = VideoOrientation.ScreenAdaptive;
        /// <summary>
        /// <para xml:lang="en">Record zoom mode used only when create.</para>
        /// <para xml:lang="zh">创建时使用的录屏缩放模式，只在创建时使用。</para>
        /// </summary>
        public RecordZoomMode RecordZoomMode;
        /// <summary>
        /// <para xml:lang="en">Record output file path type used only when create.</para>
        /// <para xml:lang="zh">创建时使用的录屏文件输出路径类型，只在创建时使用。</para>
        /// </summary>
        public OutputPathType FilePathType;
        /// <summary>
        /// <para xml:lang="en">Record output file path used only when create.</para>
        /// <para xml:lang="zh">创建时使用的录屏文件输出路径，只在创建时使用。</para>
        /// </summary>
        public string FilePath = string.Empty;

        private Recorder recorder;

        /// <summary>
        /// <para xml:lang="en">Event when record status changes.</para>
        /// <para xml:lang="zh">录屏状态变化的事件。</para>
        /// </summary>
        public event Action<RecordStatus, string> StatusUpdate;

        /// <summary>
        /// <para xml:lang="en">The recorder can be used. Recorder cannot work if permission not granted.</para>
        /// <para xml:lang="zh">录屏可以使用。如果权限未被允许录屏将无法使用。</para>
        /// </summary>
        public bool IsReady { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Output file path type.</para>
        /// <para xml:lang="zh">文件输出路径类型。</para>
        /// </summary>
        public enum OutputPathType
        {
            /// <summary>
            /// <para xml:lang="en">Absolute path.</para>
            /// <para xml:lang="zh">绝对路径。</para>
            /// </summary>
            Absolute,
            /// <summary>
            /// <para xml:lang="en">Unity persistent data path.</para>
            /// <para xml:lang="zh">Unity沙盒路径。</para>
            /// </summary>
            PersistentDataPath,
        }

        /// <summary>
        /// <para xml:lang="en">Record video orientation.</para>
        /// <para xml:lang="zh">录屏视频朝向。</para>
        /// </summary>
        public enum VideoOrientation
        {
            /// <summary>
            /// <para xml:lang="en">Video recorded is landscape.</para>
            /// <para xml:lang="zh">录制的视频是横向。</para>
            /// </summary>
            Landscape = RecordVideoOrientation.Landscape,
            /// <summary>
            /// <para xml:lang="en">Video recorded is portrait.</para>
            /// <para xml:lang="zh">录制的视频是竖向。</para>
            /// </summary>
            Portrait = RecordVideoOrientation.Portrait,
            /// <summary>
            /// <para xml:lang="en">Video orientation fit screen aspect ratio automatically.</para>
            /// <para xml:lang="zh">录制的视频朝向根据屏幕比例自动调整。</para>
            /// </summary>
            ScreenAdaptive,
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected virtual void Start()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            if (Application.platform != RuntimePlatform.Android && Application.platform != RuntimePlatform.IPhonePlayer)
            {
                throw new UIPopupException(typeof(Recorder) + " not available under " + Application.platform);
            }
            if (SystemInfo.graphicsDeviceType != GraphicsDeviceType.OpenGLES2 && SystemInfo.graphicsDeviceType != GraphicsDeviceType.OpenGLES3)
            {
                throw new UIPopupException(typeof(Recorder) + " not available under " + SystemInfo.graphicsDeviceType);
            }
            if (SystemInfo.graphicsDeviceType == GraphicsDeviceType.OpenGLES3 && Application.platform == RuntimePlatform.IPhonePlayer)
            {
                throw new UIPopupException(typeof(Recorder) + " not available under " + Application.platform + " with " +  SystemInfo.graphicsDeviceType);
            }
            if (SystemInfo.graphicsMultiThreaded)
            {
                throw new UIPopupException(typeof(Recorder) + " not available when using multi-thread rendering");
            }
            if (!Recorder.isAvailable())
            {
                throw new UIPopupException(typeof(Recorder) + " not available");
            }

            Recorder.requestPermissions(EasyARController.Scheduler, (Action<PermissionStatus, string>)((status, msg) =>
            {
                if (status != PermissionStatus.Granted)
                {
                    throw new UIPopupException("Recorder permission not granted");
                }
                IsReady = true;
            }));
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            StopRecording();
        }

        /// <summary>
        /// <para xml:lang="en">Start recording using configuration set in the component. The video data being recorded should be passed in continuously using <see cref="RecordFrame"/>。</para>
        /// <para xml:lang="zh">开始录屏，录屏中使用的配置使用组件内配置。录制的视频数据需要通过<see cref="RecordFrame"/>不断传入。</para>
        /// </summary>
        public bool StartRecording()
        {
            using (var configuration = new RecorderConfiguration())
            {
                var path = FilePath;
                if (FilePathType == OutputPathType.PersistentDataPath)
                {
                    path = Application.persistentDataPath + "/" + path;
                }
                configuration.setOutputFile(path);
                configuration.setProfile(Profile);
                configuration.setZoomMode(RecordZoomMode);

                RecordVideoOrientation orientation;
                switch (Orientation)
                {
                    case VideoOrientation.Portrait:
                        orientation = RecordVideoOrientation.Portrait;
                        break;
                    case VideoOrientation.Landscape:
                        orientation = RecordVideoOrientation.Landscape;
                        break;
                    default:
                        orientation = Screen.width > Screen.height ? RecordVideoOrientation.Landscape : RecordVideoOrientation.Portrait;
                        break;
                }
                configuration.setVideoOrientation(orientation);
                return StartRecording(configuration);
            }
        }

        /// <summary>
        /// <para xml:lang="en">Start recording using <paramref name="configuration"/>. The configuration set in the component will be ignored. The video data being recorded should be passed in continuously using <see cref="RecordFrame"/></para>
        /// <para xml:lang="zh">开始录屏，录屏中使用的配置使用<paramref name="configuration"/>。组件内配置将被忽略。录制的视频数据需要通过<see cref="RecordFrame"/>不断传入。</para>
        /// </summary>
        public bool StartRecording(RecorderConfiguration configuration)
        {
            if (!IsReady || recorder != null)
            {
                return false;
            }
            recorder = Recorder.create(configuration, EasyARController.Scheduler, (Action<RecordStatus, string>)((status, message) =>
            {
                if (StatusUpdate != null)
                {
                    StatusUpdate(status, message);
                }
            }));
            recorder.start();
            return true;
        }

        /// <summary>
        /// <para xml:lang="en">Stop recording.</para>
        /// <para xml:lang="zh">停止录屏。</para>
        /// </summary>
        public bool StopRecording()
        {
            if (recorder == null)
            {
                return false;
            }
            bool status = recorder.stop();
            recorder.Dispose();
            recorder = null;
            return status;
        }

        /// <summary>
        /// <para xml:lang="en">Record a frame using <paramref name="texture"/>.</para>
        /// <para xml:lang="zh">使用<paramref name="texture"/>录制一帧数据。</para>
        /// </summary>
        public bool RecordFrame(RenderTexture texture)
        {
            if (recorder == null)
            {
                return false;
            }
            using (var textureId = TextureId.fromInt(texture.GetNativeTexturePtr().ToInt32()))
            {
                recorder.updateFrame(textureId, texture.width, texture.height);
            }
            return true;
        }
    }
}
