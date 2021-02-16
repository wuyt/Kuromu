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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="easyar.CloudRecognizer"/> in the scene, providing a few extensions in the Unity environment. Use <see cref="CloudRecognizer"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="easyar.CloudRecognizer"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="CloudRecognizer"/>。</para>
    /// </summary>
    public class CloudRecognizerFrameFilter : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after Start if available.</para>
        /// <para xml:lang="zh">EasyAR Sense API，如果功能可以使用，可以在Start之后访问。</para>
        /// </summary>
        public CloudRecognizer CloudRecognizer { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Use global service config or not. The global service config can be changed on the inspector after click Unity menu EasyAR -> Change Global Cloud Recognizer Service Config.</para>
        /// <para xml:lang="zh">是否使用全局服务器配置。全局配置可以点击Unity菜单EasyAR -> Change Global Cloud Recognizer Service Config可以在属性面板里面进行填写。</para>
        /// </summary>
        public bool UseGlobalServiceConfig = true;

        /// <summary>
        /// <para xml:lang="en">Cloud recognizer key type.</para>
        /// <para xml:lang="zh">云识别服务密钥类型。</para>
        /// </summary>
        [HideInInspector]
        public KeyType ServerKeyType = KeyType.Public;

        /// <summary>
        /// <para xml:lang="en">Service config when <see cref="UseGlobalServiceConfig"/> == false, only valid for this object.</para>
        /// <para xml:lang="zh"><see cref="UseGlobalServiceConfig"/> == false时使用的服务器配置，只对该物体有效。</para>
        /// </summary>
        [HideInInspector, SerializeField]
        public CloudRecognizerServiceConfig ServiceConfig = new CloudRecognizerServiceConfig();

        /// <summary>
        /// <para xml:lang="en">Service config when <see cref="UseGlobalServiceConfig"/> == false, only valid for this object.</para>
        /// <para xml:lang="zh"><see cref="UseGlobalServiceConfig"/> == false时使用的服务器配置，只对该物体有效。</para>
        /// </summary>
        [HideInInspector, SerializeField]
        public PrivateCloudRecognizerServiceConfig PrivateServiceConfig = new PrivateCloudRecognizerServiceConfig();

        /// <summary>
        /// <para xml:lang="en">Cloud recognizer key type.</para>
        /// <para xml:lang="zh">云识别服务密钥类型。</para>
        /// </summary>
        public enum KeyType
        {
            Public,
            Private
        }

        private InputFrameSource source;
        private Action sourceAction;

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
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

            if (UseGlobalServiceConfig)
            {
                ServiceConfig = EasyARController.Settings.GlobalCloudRecognizerServiceConfig;
                NotifyEmptyConfig(ServiceConfig);
                CloudRecognizer = CloudRecognizer.create(ServiceConfig.ServerAddress, ServiceConfig.APIKey, ServiceConfig.APISecret, ServiceConfig.CloudRecognizerAppID);
            }
            else
            {
                if (ServerKeyType == KeyType.Public)
                {
                    NotifyEmptyConfig(ServiceConfig);
                    CloudRecognizer = CloudRecognizer.create(ServiceConfig.ServerAddress, ServiceConfig.APIKey, ServiceConfig.APISecret, ServiceConfig.CloudRecognizerAppID);

                }
                else if (ServerKeyType == KeyType.Private)
                {
                    NotifyEmptyPrivateConfig(PrivateServiceConfig);
                    CloudRecognizer = CloudRecognizer.createByCloudSecret(PrivateServiceConfig.ServerAddress, PrivateServiceConfig.CloudRecognitionServiceSecret, PrivateServiceConfig.CloudRecognizerAppID);
                }
            }
        }

        /// <summary>
        /// <para xml:lang="en">Send recognition request. The lowest available request interval is 300ms</para>
        /// <para xml:lang="zh">发送云识别请求。最低可用请求间隔是300ms。</para>
        /// </summary>
        public void Resolve(InputFrame iFrame, Action<CloudRecognizationResult> callback)
        {
            if (CloudRecognizer != null)
            {
                CloudRecognizer.resolve(iFrame, EasyARController.Scheduler, callback);
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            if (CloudRecognizer != null)
            {
                CloudRecognizer.Dispose();
            }
        }

        private void NotifyEmptyConfig(CloudRecognizerServiceConfig config)
        {
            if (string.IsNullOrEmpty(config.ServerAddress) ||
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

        private void NotifyEmptyPrivateConfig(PrivateCloudRecognizerServiceConfig config)
        {
            if (string.IsNullOrEmpty(config.ServerAddress) ||
                string.IsNullOrEmpty(config.CloudRecognitionServiceSecret) ||
                string.IsNullOrEmpty(config.CloudRecognizerAppID))
            {
                throw new UIPopupException(
                    "Service config (for authentication) NOT set, please set" + Environment.NewLine +
                    "globally on <EasyAR Settings> Asset or" + Environment.NewLine +
                    "locally on <CloudRecognizerFrameFilter> Component." + Environment.NewLine +
                    "Get from EasyAR Develop Center (www.easyar.com) -> CRS -> Database Details.");
            }
        }

        /// <summary>
        /// <para xml:lang="en">Service config for <see cref="easyar.CloudRecognizer"/>.</para>
        /// <para xml:lang="zh"><see cref="easyar.CloudRecognizer"/>服务器配置。</para>
        /// </summary>
        [Serializable]
        public class CloudRecognizerServiceConfig
        {
            /// <summary>
            /// <para xml:lang="en">Server Address, go to EasyAR Develop Center (https://www.easyar.com) for details.</para>
            /// <para xml:lang="zh">服务器地址，详见EasyAR开发中心（https://www.easyar.cn）。</para>
            /// </summary>
            public string ServerAddress = string.Empty;
            /// <summary>
            /// <para xml:lang="en">API Key, go to EasyAR Develop Center (https://www.easyar.com) for details.</para>
            /// <para xml:lang="zh">API Key，详见EasyAR开发中心（https://www.easyar.cn）。</para>
            /// </summary>
            public string APIKey = string.Empty;
            /// <summary>
            /// <para xml:lang="en">API Secret, go to EasyAR Develop Center (https://www.easyar.com) for details.</para>
            /// <para xml:lang="zh">API Secret，详见EasyAR开发中心（https://www.easyar.cn）。</para>
            /// </summary>
            public string APISecret = string.Empty;
            /// <summary>
            /// <para xml:lang="en">Cloud Recognizer AppID, go to EasyAR Develop Center (https://www.easyar.com) for details.</para>
            /// <para xml:lang="zh">云识别AppID，详见EasyAR开发中心（https://www.easyar.cn）。</para>
            /// </summary>
            public string CloudRecognizerAppID = string.Empty;
        }

        [Serializable]
        public class PrivateCloudRecognizerServiceConfig
        {
            public string ServerAddress = string.Empty;
            public string CloudRecognitionServiceSecret = string.Empty;
            public string CloudRecognizerAppID = string.Empty;
        }
    }
}
