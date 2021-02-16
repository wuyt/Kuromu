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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls EasyAR Sense initialization and some global settings.</para>
    /// <para xml:lang="zh">在场景中控制EasyAR Sense初始化以及一些全局设置的<see cref="MonoBehaviour"/>。</para>
    /// </summary>
    public class EasyARController : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">If popup message will be displayed. All popup message from EasyAR Sense Unity Plugin is controlled by this flag.</para>
        /// <para xml:lang="zh">是否显示弹出消息。所有EasyAR Sense Unity Plugin的弹出消息都又这个flag控制。</para>
        /// </summary>
        public bool ShowPopupMessage = true;

        private static EasyARSettings settings;

        /// <summary>
        /// <para xml:lang="en">Global <see cref="EasyARController"/>.</para>
        /// <para xml:lang="zh">全局<see cref="EasyARController"/>。</para>
        /// </summary>
        public static EasyARController Instance { get; private set; }

        /// <summary>
        /// <para xml:lang="en">EasyAR Sense initialize result, false if license key validation fails.</para>
        /// <para xml:lang="zh">EasyAR Sense初始化结果。如果license key验证失败会是false。</para>
        /// </summary>
        public static bool Initialized { get; private set; }

        /// <summary>
        /// <para xml:lang="en">If ARCore load fails.</para>
        /// <para xml:lang="zh">ARCore加载是否失败。</para>
        /// </summary>
        public static bool ARCoreLoadFailed { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Global Scheduler. Accessible after scene loaded.</para>
        /// <para xml:lang="zh">全局回调调度器。可以在场景加载之后访问。</para>
        /// </summary>
        public static DelayedCallbackScheduler Scheduler { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Global <see cref="EasyARSettings"/>.</para>
        /// <para xml:lang="zh">全局<see cref="EasyARSettings"/>。</para>
        /// </summary>
        public static EasyARSettings Settings
        {
            get
            {
                if (!settings)
                {
                    settings = Resources.Load<EasyARSettings>(settingsPath);
                }
                return settings;
            }
        }
        private static string settingsPath { get { return "EasyAR/Settings"; } }

        /// <summary>
        /// <para xml:lang="en">Thread worker. Accessible after Awake.</para>
        /// <para xml:lang="zh">线程工作器。可以在Awake之后访问。</para>
        /// </summary>
        public ThreadWorker Worker { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Display information. Accessible after Awake.</para>
        /// <para xml:lang="zh">显示设备信息。可以在Awake之后访问。</para>
        /// </summary>
        public Display Display { get; private set; }

        /// <summary>
        /// <para xml:lang="en">EasyAR Sense initialization, called before Unity load scenes.</para>
        /// <para xml:lang="zh">初始化EasyAR Sense，在Unity场景加载前调用。</para>
        /// </summary>
        [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.BeforeSceneLoad)]
        public static void GlobalInitialization()
        {
            Debug.Log("EasyAR Sense Unity Plugin Version " + EasyARVersion.FullVersion);
#if UNITY_EDITOR
            Log.setLogFunc((LogLevel, msg) =>
            {
                switch (LogLevel)
                {
                    case LogLevel.Error:
                        Debug.LogError(msg);
                        break;
                    case LogLevel.Warning:
                        Debug.LogWarning(msg);
                        break;
                    case LogLevel.Info:
                        Debug.Log(msg);
                        break;
                    default:
                        break;
                }
            });
            System.AppDomain.CurrentDomain.DomainUnload += (sender, e) =>
            {
                Log.resetLogFunc();
            };
#endif
#if UNITY_ANDROID && !UNITY_EDITOR
            if (Settings.ARCoreSupport)
            {
                try
                {
                    using (var systemClass = new AndroidJavaClass("java.lang.System"))
                    {
                        systemClass.CallStatic("loadLibrary", "arcore_sdk_c");
                    }
                }
                catch (AndroidJavaException)
                {
                    ARCoreLoadFailed = true;
                }
            }
#endif
            Initialized = false;
            Scheduler = new DelayedCallbackScheduler();
            var key = Settings.LicenseKey;
            System.AppDomain.CurrentDomain.DomainUnload += (sender, e) =>
            {
                if (Scheduler != null)
                {
                    Scheduler.Dispose();
                }
                settings = null;
            };
#if UNITY_ANDROID && !UNITY_EDITOR
            using (var unityPlayerClass = new AndroidJavaClass("com.unity3d.player.UnityPlayer"))
            using (var currentActivity = unityPlayerClass.GetStatic<AndroidJavaObject>("currentActivity"))
            using (var easyarEngineClass = new AndroidJavaClass("cn.easyar.Engine"))
            {
                var activityclassloader = currentActivity.Call<AndroidJavaObject>("getClass").Call<AndroidJavaObject>("getClassLoader");
                if (activityclassloader == null)
                {
                    Debug.Log("ActivityClassLoader is null");
                }
                easyarEngineClass.CallStatic("loadLibraries");
                if (!easyarEngineClass.CallStatic<bool>("setupActivity", currentActivity))
                {
                    Debug.LogError("EasyAR Sense Initialize Fail");
                    Initialized = false;
                    return;
                }
            }
#endif
            if (!Engine.initialize(key.Trim()))
            {
                Debug.LogError("EasyAR Sense Initialize Fail");
                Initialized = false;
                return;
            }
            else
            {
                Initialized = true;
            }
            System.AppDomain.CurrentDomain.UnhandledException += (sender, e) =>
            {
                Debug.Log("UnhandledException: " + e.ExceptionObject.ToString());
            };
        }

        /// <summary>
        /// MonoBehaviour Awake
        /// </summary>
        private void Awake()
        {
            Instance = this;
            Display = new Display();
            Worker = new ThreadWorker();
            if (!Initialized)
            {
                ShowErrorMessage();
            }
        }

        /// <summary>
        /// MonoBehaviour Update
        /// </summary>
        private void Update()
        {
            if (!Initialized)
            {
                return;
            }
            var error = Engine.errorMessage();
            if (!string.IsNullOrEmpty(error))
            {
                ShowErrorMessage();
                Initialized = false;
            }
            if (Scheduler != null)
            {
                while (Scheduler.runOne())
                {
                }
            }
        }

        /// <summary>
        /// MonoBehaviour OnApplicationPause
        /// </summary>
        private void OnApplicationPause(bool pause)
        {
            if (pause)
            {
                Engine.onPause();
            }
            else
            {
                Engine.onResume();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        private void OnDestroy()
        {
            Worker.Dispose();
            Display.Dispose();
        }

        private void ShowErrorMessage()
        {
            if (Application.isEditor || string.IsNullOrEmpty(Settings.LicenseKey))
            {
                GUIPopup.EnqueueMessage(Engine.errorMessage() + Environment.NewLine +
                    "Fill a valid Key in EasyAR Settings Asset" + Environment.NewLine +
                    "Menu entry: <EasyAR/Change License Key>" + Environment.NewLine +
                    "Asset Path: " + settingsPath + Environment.NewLine +
                    "Get from EasyAR Develop Center (www.easyar.com) -> SDK Authorization", 10000);
            }
            else
            {
                GUIPopup.EnqueueMessage(Engine.errorMessage() + Environment.NewLine +
                    "Get from EasyAR Develop Center (www.easyar.com) -> SDK Authorization", 10000);
            }
        }
    }
}
