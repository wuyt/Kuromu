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
    public class VideoRecorder : MonoBehaviour
    {
        public RecordProfile Profile = RecordProfile.Quality_Default;
        public VideoOrientation Orientation = VideoOrientation.ScreenAdaptive;
        public RecordZoomMode RecordZoomMode;
        public OutputPathType FilePathType;
        public string FilePath = string.Empty;

        private Recorder recorder;

        public event Action<RecordStatus, string> StatusUpdate;

        public bool IsReady { get; private set; }

        public enum OutputPathType
        {
            Absolute,
            PersistentDataPath,
        }

        public enum VideoOrientation
        {
            Landscape = RecordVideoOrientation.Landscape,
            Portrait = RecordVideoOrientation.Portrait,
            ScreenAdaptive,
        }

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

        protected virtual void OnDestroy()
        {
            StopRecording();
        }

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
