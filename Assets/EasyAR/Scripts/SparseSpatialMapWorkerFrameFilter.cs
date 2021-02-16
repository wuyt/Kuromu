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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="SparseSpatialMap"/> in the scene, providing a few extensions in the Unity environment. Use <see cref="Builder"/>, <see cref="Localizer"/> or <see cref="Manager"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="SparseSpatialMap"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="Builder"/>、<see cref="Localizer"/>或<see cref="Manager"/>。</para>
    /// </summary>
    public class SparseSpatialMapWorkerFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.IOutputFrameSource, FrameFilter.ISpatialInformationSink
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible when building map after Awake if available.</para>
        /// <para xml:lang="en">Use when building a map (<see cref="WorkingMode"/> == <see cref="Mode.Build"/>).</para>
        /// <para xml:lang="zh">EasyAR Sense API，在地图构建时，如果功能可以使用，可以在Awake之后访问。</para>
        /// <para xml:lang="zh">在地图构建时（<see cref="WorkingMode"/> == <see cref="Mode.Build"/>）使用。</para>
        /// </summary>
        public SparseSpatialMap Builder { get; private set; }
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after Awake if available.</para>
        /// <para xml:lang="en">Use when localizing a map (<see cref="WorkingMode"/> == <see cref="Mode.Localize"/>).</para>
        /// <para xml:lang="zh">EasyAR Sense API，如果功能可以使用，可以在Awake之后访问。</para>
        /// <para xml:lang="zh">在地图定位时（<see cref="WorkingMode"/> == <see cref="Mode.Localize"/>）使用。</para>
        /// </summary>
        public SparseSpatialMap Localizer { get; private set; }
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after Awake if available.</para>
        /// <para xml:lang="en">Use when building and uploading a map.</para>
        /// <para xml:lang="zh">EasyAR Sense API，如果功能可以使用，可以在Awake之后访问。</para>
        /// <para xml:lang="zh">在地图构建和上传时使用。</para>
        /// </summary>
        public SparseSpatialMapManager Manager { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Map localizer config used before every start (<see cref="OnEnable"/>).</para>
        /// <para xml:lang="zh">地图定位配置，在每次启动（<see cref="OnEnable"/>）前使用。</para>
        /// </summary>
        public MapLocalizerConfig LocalizerConfig = new MapLocalizerConfig();

        /// <summary>
        /// <para xml:lang="en">Use global service config or not. The global service config can be changed on the inspector after click Unity menu EasyAR -> Change Global Spatial Map Service Config.</para>
        /// <para xml:lang="zh">是否使用全局服务器配置。全局配置可以点击Unity菜单EasyAR -> Change Global Spatial Map Service Config可以在属性面板里面进行填写。</para>
        /// </summary>
        public bool UseGlobalServiceConfig = true;

        /// <summary>
        /// <para xml:lang="en">Service config when <see cref="UseGlobalServiceConfig"/> == false, only valid for this object.</para>
        /// <para xml:lang="zh"><see cref="UseGlobalServiceConfig"/> == false时使用的服务器配置，只对该物体有效。</para>
        /// </summary>
        [HideInInspector, SerializeField]
        public SpatialMapServiceConfig ServiceConfig = new SpatialMapServiceConfig();

        internal ARSession Session;
        private GameObject mapRoot;
        private SparseSpatialMap sparseSpatialMapWorker;
        private string localizedMapID = string.Empty;
        private Dictionary<string, SparseSpatialMapController> mapControllers = new Dictionary<string, SparseSpatialMapController>();
        private bool isStarted;

        /// <summary>
        /// <para xml:lang="en">Map load finish event. The bool value indicates the load success or not. The string value is the error message when fail.</para>
        /// <para xml:lang="zh">Map加载完成的事件。bool值表示加载是否成功。string值表示出错时的错误信息。</para>
        /// </summary>
        public event Action<SparseSpatialMapController, SparseSpatialMapController.SparseSpatialMapInfo, bool, string> MapLoad;
        /// <summary>
        /// <para xml:lang="en">Map unload finish event. The bool value indicates the unload success or not. The string value is the error message when fail.</para>
        /// <para xml:lang="zh">Map卸载完成的事件。bool值表示卸载是否成功。string值表示出错时的错误信息。</para>
        /// </summary>
        public event Action<SparseSpatialMapController, SparseSpatialMapController.SparseSpatialMapInfo, bool, string> MapUnload;
        /// <summary>
        /// <para xml:lang="en">Map create and upload finish event. The bool value indicates the create and upload success or not. The string value is the error message when fail.</para>
        /// <para xml:lang="zh">Map创建及上传完成的事件。bool值表示创建及上传是否成功。string值表示出错时的错误信息。</para>
        /// </summary>
        public event Action<SparseSpatialMapController, SparseSpatialMapController.SparseSpatialMapInfo, bool, string> MapHost;

        /// <summary>
        /// <para xml:lang="en">Working mode.</para>
        /// <para xml:lang="zh">工作模式。</para>
        /// </summary>
        public enum Mode
        {
            /// <summary>
            /// <para xml:lang="en">Map building mode.</para>
            /// <para xml:lang="zh">建图模式。</para>
            /// </summary>
            Build,
            /// <summary>
            /// <para xml:lang="en">Map localizing mode.</para>
            /// <para xml:lang="zh">定位模式。</para>
            /// </summary>
            Localize,
        }

        public override int BufferRequirement
        {
            get { return sparseSpatialMapWorker.bufferRequirement(); }
        }

        public MotionTrackingStatus TrackingStatus { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Current working mode. The working mode start as <see cref="Mode.Build"/> and will change to <see cref="Mode.Localize"/> after a map load.</para>
        /// <para xml:lang="zh">当前工作模式。工作模式启动为<see cref="Mode.Build"/>，会在加载地图之后变成<see cref="Mode.Localize"/>。</para>
        /// </summary>
        public Mode WorkingMode { get; private set; }

        /// <summary>
        /// <para xml:lang="en">The map being localized.</para>
        /// <para xml:lang="zh">当前被定为的地图。</para>
        /// </summary>
        public SparseSpatialMapController LocalizedMap { get; private set; }
        /// <summary>
        /// <para xml:lang="en">The map controller for map building. To visualize the map building, <see cref="SparseSpatialMapController.SourceType"/> of one <see cref="SparseSpatialMapController"/> should be set to <see cref="SparseSpatialMapController.DataSource.MapBuilder"/> and the map should be loaded before building start.</para>
        /// <para xml:lang="zh">用于建图的map controller。如果想可视化地查看建图过程，需要在建图开始之前设置一个即将被加载的<see cref="SparseSpatialMapController"/>的<see cref="SparseSpatialMapController.SourceType"/>为<see cref="SparseSpatialMapController.DataSource.MapBuilder"/>。</para>
        /// </summary>
        public SparseSpatialMapController BuilderMapController { get; private set; }

        /// <summary>
        /// <para xml:lang="en"><see cref="SparseSpatialMapController"/> that has been loaded.</para>
        /// <para xml:lang="zh">已加载的<see cref="SparseSpatialMapController"/>。</para>
        /// </summary>
        public List<SparseSpatialMapController> MapControllers
        {
            get
            {
                List<SparseSpatialMapController> list = new List<SparseSpatialMapController>();
                foreach (var value in mapControllers.Values)
                {
                    list.Add(value);
                }
                return list;
            }
        }

        /// <summary>
        /// MonoBehaviour Awake
        /// </summary>
        protected virtual void Awake()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            if (!SparseSpatialMap.isAvailable())
            {
                throw new UIPopupException(typeof(SparseSpatialMap) + " not available");
            }
            if (!SparseSpatialMapManager.isAvailable())
            {
                throw new UIPopupException(typeof(SparseSpatialMapManager) + " not available");
            }

            mapRoot = new GameObject("SparseSpatialMapRoot");
            sparseSpatialMapWorker = SparseSpatialMap.create();
            Builder = sparseSpatialMapWorker;
            Localizer = sparseSpatialMapWorker;
            Manager = SparseSpatialMapManager.create();
        }

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            if (sparseSpatialMapWorker != null && isStarted)
            {
                using (var config = new SparseSpatialMapConfig())
                {
                    config.setLocalizationMode(LocalizerConfig.LocalizationMode);
                    sparseSpatialMapWorker.setConfig(config);
                }
                sparseSpatialMapWorker.start();
            }
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected virtual void Start()
        {
            isStarted = true;
            if (enabled)
            {
                OnEnable();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected virtual void OnDisable()
        {
            if (sparseSpatialMapWorker != null)
            {
                sparseSpatialMapWorker.stop();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            if (sparseSpatialMapWorker != null)
            {
                sparseSpatialMapWorker.Dispose();
            }
            if (Manager != null)
            {
                Manager.Dispose();
            }
            if (mapRoot)
            {
                Destroy(mapRoot);
            }
        }

        /// <summary>
        /// <para xml:lang="en">Load map.</para>
        /// <para xml:lang="zh">加载地图。</para>
        /// </summary>
        public void LoadMap(SparseSpatialMapController map)
        {
            if (TryGetMapController(map.MapInfo.ID) || BuilderMapController == map)
            {
                return;
            }
            map.MapWorker = this;
        }

        /// <summary>
        /// <para xml:lang="en">Unload map.</para>
        /// <para xml:lang="zh">卸载地图。</para>
        /// </summary>
        public void UnloadMap(SparseSpatialMapController map)
        {
            if (!TryGetMapController(map.MapInfo.ID) && BuilderMapController != map)
            {
                return;
            }
            map.MapWorker = null;
        }

        /// <summary>
        /// <para xml:lang="en">Create and upload map.</para>
        /// <para xml:lang="zh">创建并上传地图。</para>
        /// </summary>
        public void HostMap(SparseSpatialMapController map, string name, Optional<Image> preview)
        {
            map.Host(name, preview);
        }

        public InputFrameSink InputFrameSink()
        {
            if (sparseSpatialMapWorker != null)
            {
                return sparseSpatialMapWorker.inputFrameSink();
            }
            return null;
        }

        public OutputFrameSource OutputFrameSource()
        {
            if (sparseSpatialMapWorker != null)
            {
                return sparseSpatialMapWorker.outputFrameSource();
            }
            return null;
        }

        public void OnTracking(MotionTrackingStatus status)
        {
            TrackingStatus = status;
        }

        public override void OnAssemble(ARSession session)
        {
            Session = session;
            session.WorldRootChanged += (WorldRootController worldRoot) =>
            {
                mapRoot.transform.parent = worldRoot.transform;
            };
        }

        public List<KeyValuePair<Optional<TargetController>, Matrix44F>> OnResult(Optional<FrameFilterResult> frameFilterResult)
        {
            LocalizedMap = null;
            if (WorkingMode == Mode.Build)
            {
                if (BuilderMapController)
                {
                    if (frameFilterResult.OnSome)
                    {
                        LocalizedMap = BuilderMapController;
                        BuilderMapController.OnLocalization(true);
                        using (var cloudBuffer = sparseSpatialMapWorker.getPointCloudBuffer())
                        {
                            BuilderMapController.UpdatePointCloud(cloudBuffer);
                        }
                    }
                    else
                    {
                        BuilderMapController.OnLocalization(false);
                    }
                }
            }
            else
            {
                if (BuilderMapController)
                {
                    BuilderMapController.OnLocalization(false);
                    if (BuilderMapController.PointCloud.Count > 0)
                    {
                        BuilderMapController.ShowPointCloud = false;
                    }
                }

                string mapID = string.Empty;
                if (frameFilterResult.OnSome)
                {
                    var mapResult = frameFilterResult.Value as SparseSpatialMapResult;
                    if (mapResult.getLocalizationStatus())
                    {
                        mapID = mapResult.getLocalizationMapID();

                        var controller = TryGetMapController(mapID);
                        if (controller)
                        {
                            LocalizedMap = controller;
                            controller.OnLocalization(true);
                            if (controller.PointCloud.Count == 0)
                            {
                                using (var cloudBuffer = sparseSpatialMapWorker.getPointCloudBuffer())
                                {
                                    controller.UpdatePointCloud(cloudBuffer);
                                }
                            }

                            TransformUtil.SetMatrixOnTransform(controller.transform, mapResult.getVioPose().Value.ToUnityMatrix().inverse * mapResult.getMapPose().Value.ToUnityMatrix(), true);
                        }
                    }
                }

                if (localizedMapID != mapID && !string.IsNullOrEmpty(localizedMapID))
                {
                    mapControllers[localizedMapID].OnLocalization(false);
                }
                localizedMapID = mapID;
            }

            return new List<KeyValuePair<Optional<TargetController>, Matrix44F>>();
        }


        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void LoadSparseSpatialMap(SparseSpatialMapController controller, Action<SparseSpatialMapController.SparseSpatialMapInfo, bool, string> callback)
        {
            SpatialMapServiceConfig config;
            if (UseGlobalServiceConfig)
            {
                config = EasyARController.Settings.GlobalSpatialMapServiceConfig;
            }
            else
            {
                config = ServiceConfig;
            }
            NotifyEmptyConfig(config);

            var id = controller.MapInfo.ID;
            Manager.load(sparseSpatialMapWorker, id.Trim(), config.APIKey.Trim(), config.APISecret.Trim(), config.SparseSpatialMapAppID.Trim(), EasyARController.Scheduler, (status, error) =>
            {
                if (MapLoad != null)
                {
                    MapLoad(controller, controller.MapInfo, status, error);
                }
                if (callback != null)
                {
                    callback(controller.MapInfo, status, error);
                }
            });
            mapControllers[id] = controller;
            controller.transform.parent = mapRoot.transform;
            WorkingMode = Mode.Localize;
            Builder = null;
        }

        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void UnloadSparseSpatialMap(SparseSpatialMapController controller, Action<SparseSpatialMapController.SparseSpatialMapInfo, bool, string> callback)
        {
            var id = controller.MapInfo.ID;
            if (mapControllers.Remove(id))
            {
                controller.OnLocalization(false);
                sparseSpatialMapWorker.unloadMap(controller.MapInfo.ID, EasyARController.Scheduler, (Action<bool>)((status) =>
                {
                    if (MapUnload != null)
                    {
                        MapUnload(controller, controller.MapInfo, status, string.Empty);
                    }
                    if (callback != null)
                    {
                        callback(controller.MapInfo, status, string.Empty);
                    }
                }));
            }
        }

        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void HostSparseSpatialMap(SparseSpatialMapController controller, string name, Optional<Image> preview, Action<SparseSpatialMapController.SparseSpatialMapInfo, bool, string> callback)
        {
            SpatialMapServiceConfig config;
            if (UseGlobalServiceConfig)
            {
                config = EasyARController.Settings.GlobalSpatialMapServiceConfig;
            }
            else
            {
                config = ServiceConfig;
            }
            NotifyEmptyConfig(config);

            Manager.host(sparseSpatialMapWorker, config.APIKey.Trim(), config.APISecret.Trim(), config.SparseSpatialMapAppID.Trim(), name, preview, EasyARController.Scheduler, (status, id, error) =>
            {
                var mapInfo = new SparseSpatialMapController.SparseSpatialMapInfo() { Name = name, ID = id };
                if (MapHost != null)
                {
                    MapHost(controller, mapInfo, status, error);
                }
                if (callback != null)
                {
                    callback(mapInfo, status, error);
                }
            });
        }

        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void LoadSparseSpatialMapBuild(SparseSpatialMapController controller)
        {
            UnloadSparseSpatialMapBuild(BuilderMapController);
            BuilderMapController = controller;
            if (controller && mapRoot)
            {
                BuilderMapController.transform.parent = mapRoot.transform;
            }
        }

        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void UnloadSparseSpatialMapBuild(SparseSpatialMapController controller)
        {
            if (BuilderMapController == controller && controller)
            {
                BuilderMapController = null;
                controller.OnLocalization(false);
            }
        }

        private SparseSpatialMapController TryGetMapController(string id)
        {
            SparseSpatialMapController controller;
            if (mapControllers.TryGetValue(id, out controller))
                return controller;
            return null;
        }

        private void NotifyEmptyConfig(SpatialMapServiceConfig config)
        {
            if (string.IsNullOrEmpty(config.APIKey) ||
                string.IsNullOrEmpty(config.APISecret) ||
                string.IsNullOrEmpty(config.SparseSpatialMapAppID))
            {
                throw new UIPopupException(
                    "Service config (for authentication) NOT set, please set" + Environment.NewLine +
                    "globally on <EasyAR Settings> Asset or" + Environment.NewLine +
                    "locally on <SparseSpatialMapWorkerFrameFilter> Component." + Environment.NewLine +
                    "Get from EasyAR Develop Center (www.easyar.com) -> SpatialMap -> Database Details.");
            }
        }

        /// <summary>
        /// <para xml:lang="en">Map localizer config.</para>
        /// <para xml:lang="zh">地图定位配置。</para>
        /// </summary>
        [Serializable]
        public class MapLocalizerConfig
        {
            /// <summary>
            /// <para xml:lang="en">Localization mode.</para>
            /// <para xml:lang="zh">定位模式。</para>
            /// </summary>
            public LocalizationMode LocalizationMode;
        }

        /// <summary>
        /// <para xml:lang="en">Service config for <see cref="SparseSpatialMapManager"/>.</para>
        /// <para xml:lang="zh"><see cref="SparseSpatialMapManager"/>服务器配置。</para>
        /// </summary>
        [Serializable]
        public class SpatialMapServiceConfig
        {
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
            /// <para xml:lang="en">Spatial Map AppID, go to EasyAR Develop Center (https://www.easyar.com) for details.</para>
            /// <para xml:lang="zh">Spatial Map AppID，详见EasyAR开发中心（https://www.easyar.cn）。</para>
            /// </summary>
            public string SparseSpatialMapAppID = string.Empty;
        }
    }
}
