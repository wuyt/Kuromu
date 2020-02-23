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
    public class CloudRecognizerFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.IInputFrameSinkDelayConnect
    {
        /// <summary>
        /// EasyAR Sense API. Accessible after Start if available.
        /// </summary>
        public CloudRecognizer CloudRecognizer { get; private set; }

        public bool UseGlobalServiceConfig = true;
        [HideInInspector, SerializeField]
        public CloudRecognizerServiceConfig ServiceConfig = new CloudRecognizerServiceConfig();

        private InputFrameSource source;
        private Action sourceAction;

        public event Action<CloudStatus, List<Target>> CloudUpdate;

        public override int BufferRequirement
        {
            get
            {
                if (CloudRecognizer == null)
                {
                    return 0;
                }
                return CloudRecognizer.bufferRequirement();
            }
        }

        protected virtual void OnEnable()
        {
            if (CloudRecognizer != null)
            {
                CloudRecognizer.start();
            }
        }

        protected virtual void Start()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            if (!CloudRecognizer.isAvailable())
            {
                throw new UIPopupException(typeof(CloudRecognizer) + " not available");
            }

            CloudRecognizerServiceConfig config;
            if (UseGlobalServiceConfig)
            {
                config = EasyARController.Settings.GlobalCloudRecognizerServiceConfig;
            }
            else
            {
                config = ServiceConfig;
            }
            NotifyEmptyConfig(config);

            CloudRecognizer = CloudRecognizer.create(config.ServerAddress.Trim(), config.APIKey.Trim(), config.APISecret.Trim(), config.CloudRecognizerAppID.Trim(), EasyARController.Scheduler,
            (Action<CloudStatus, List<Target>>)((status, targets) =>
            {
                if (CloudUpdate != null)
                {
                    CloudUpdate(status, targets);
                }
            }));
            if (source != null)
            {
                source.connect(InputFrameSink());
                if (sourceAction != null)
                {
                    sourceAction();
                }
            }
            if (enabled)
            {
                CloudRecognizer.start();
            }
        }

        protected virtual void OnDisable()
        {
            if (CloudRecognizer != null)
            {
                CloudRecognizer.stop();
            }
        }

        protected virtual void OnDestroy()
        {
            if (CloudRecognizer != null)
            {
                CloudRecognizer.Dispose();
            }
        }

        public InputFrameSink InputFrameSink()
        {
            if (CloudRecognizer != null)
            {
                return CloudRecognizer.inputFrameSink();
            }
            return null;
        }

        public void ConnectedTo(InputFrameSource val, Action action)
        {
            source = val;
            sourceAction = action;
        }

        private void NotifyEmptyConfig(CloudRecognizerServiceConfig config)
        {
            if (string.IsNullOrEmpty(config.ServerAddress)||
                string.IsNullOrEmpty(config.APIKey) ||
                string.IsNullOrEmpty(config.APISecret) ||
                string.IsNullOrEmpty(config.CloudRecognizerAppID))
            {
                throw new UIPopupException(
                    "Service config (for authentication) NOT set, please set" + Environment.NewLine +
                    "globally on <EasyAR Settings> Asset or" + Environment.NewLine +
                    "locally on <CloudRecognizerFrameFilter> Component." + Environment.NewLine +
                    "Get from EasyAR Develop Center (www.easyar.com) -> CRS -> Database Details.");
            }
        }

        [Serializable]
        public class CloudRecognizerServiceConfig
        {
            public string ServerAddress = string.Empty;
            public string APIKey = string.Empty;
            public string APISecret = string.Empty;
            public string CloudRecognizerAppID = string.Empty;
        }
    }
}
