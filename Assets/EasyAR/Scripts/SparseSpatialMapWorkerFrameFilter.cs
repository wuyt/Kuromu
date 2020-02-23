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
    public class SparseSpatialMapWorkerFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.IOutputFrameSource, FrameFilter.ISpatialInformationSink
    {
        /// <summary>
        /// EasyAR Sense API. Accessible when (WorkingMode == Mode.Build) after Awake if available.
        /// </summary>
        public SparseSpatialMap Builder { get; private set; }
        /// <summary>
        /// EasyAR Sense API. Accessible after Awake if available.
        /// </summary>
        public SparseSpatialMap Localizer { get; private set; }
        /// <summary>
        /// EasyAR Sense API. Accessible after Awake if available.
        /// </summary>
        public SparseSpatialMapManager Manager { get; private set; }

        public MapLocalizerConfig LocalizerConfig = new MapLocalizerConfig();
        public bool UseGlobalServiceConfig = true;
        [HideInInspector, SerializeField]
        public SpatialMapServiceConfig ServiceConfig = new SpatialMapServiceConfig();

        internal ARSession Session;
        private GameObject mapRoot;
        private SparseSpatialMap sparseSpatialMapWorker;
        private string localizedMapID = string.Empty;
        private Dictionary<string, SparseSpatialMapController> mapControllers = new Dictionary<string, SparseSpatialMapController>();
        private bool isStarted;

        public event Action<SparseSpatialMapController, SparseSpatialMapController.SparseSpatialMapInfo, bool, string> MapLoad;
        public event Action<SparseSpatialMapController, SparseSpatialMapController.SparseSpatialMapInfo, bool, string> MapUnload;
        public event Action<SparseSpatialMapController, SparseSpatialMapController.SparseSpatialMapInfo, bool, string> MapHost;

        public enum Mode
        {
            Build,
            Localize,
        }

        public override int BufferRequirement
        {
            get { return sparseSpatialMapWorker.bufferRequirement(); }
        }

        public MotionTrackingStatus TrackingStatus { get; private set; }
        public Mode WorkingMode { get; private set; }
        public SparseSpatialMapController LocalizedMap { get; private set; }
        public SparseSpatialMapController BuilderMapController { get; private set; }

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

        protected virtual void Start()
        {
            isStarted = true;
            if (enabled)
            {
                OnEnable();
            }
        }

        protected virtual void OnDisable()
        {
            if (sparseSpatialMapWorker != null)
            {
                sparseSpatialMapWorker.stop();
            }
        }

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

        public void LoadMap(SparseSpatialMapController map)
        {
            if (TryGetMapController(map.MapInfo.ID) || BuilderMapController == map)
            {
                return;
            }
            map.MapWorker = this;
        }

        public void UnloadMap(SparseSpatialMapController map)
        {
            if (!TryGetMapController(map.MapInfo.ID) && BuilderMapController != map)
            {
                return;
            }
            map.MapWorker = null;
        }

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

        internal void LoadSparseSpatialMapBuild(SparseSpatialMapController controller)
        {
            UnloadSparseSpatialMapBuild(BuilderMapController);
            BuilderMapController = controller;
            if (controller && mapRoot)
            {
                BuilderMapController.transform.parent = mapRoot.transform;
            }
        }

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

        [Serializable]
        public class MapLocalizerConfig
        {
            public LocalizationMode LocalizationMode;
        }

        [Serializable]
        public class SpatialMapServiceConfig
        {
            public string APIKey = string.Empty;
            public string APISecret = string.Empty;
            public string SparseSpatialMapAppID = string.Empty;
        }
    }
}
