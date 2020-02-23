//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using UnityEngine;

namespace easyar
{
    public class SparseSpatialMapController : MonoBehaviour
    {
        /// <summary>
        /// Accessible after MapInfoAvailable event.
        /// </summary>
        public SparseSpatialMapInfo MapInfo { get; private set; }

        public ParticleSystem PointCloudParticleSystem;
        public ActiveControlStrategy ActiveControl;
        public DataSource SourceType;
        [HideInInspector, SerializeField]
        public MapManagerSourceData MapManagerSource = new MapManagerSourceData();

        [HideInInspector, SerializeField]
        private bool showPointCloud = true;
        [HideInInspector, SerializeField]
        private ParticleParameter pointCloudParticleParameter = new ParticleParameter();
        [HideInInspector, SerializeField]
        private bool mapWorkerHasSet;
        [HideInInspector, SerializeField]
        private SparseSpatialMapWorkerFrameFilter mapWorker;
        private SparseSpatialMapWorkerFrameFilter loader;
        private bool localized;

        public event Action MapInfoAvailable;
        public event Action MapLocalized;
        public event Action MapStopLocalize;
        public event Action<SparseSpatialMapInfo, bool, string> MapLoad;
        public event Action<SparseSpatialMapInfo, bool, string> MapUnload;
        public event Action<SparseSpatialMapInfo, bool, string> MapHost;

        public enum ActiveControlStrategy
        {
            HideBeforeLocalized,
            HideWhenNotLocalizing,
            None,
        }

        public enum DataSource
        {
            MapBuilder,
            MapManager,
        }

        public SparseSpatialMapWorkerFrameFilter MapWorker
        {
            get
            {
                return mapWorker;
            }
            set
            {
                mapWorker = value;
                UpdateMapInLocalizer();
            }
        }

        public ParticleParameter PointCloudParticleParameter
        {
            get { return pointCloudParticleParameter; }
            set
            {
                pointCloudParticleParameter = value;
                UpdatePointCloud();
            }
        }

        public List<Vector3> PointCloud
        {
            get; private set;
        }

        public bool ShowPointCloud
        {
            get
            {
                return showPointCloud;
            }
            set
            {
                showPointCloud = value;
                UpdatePointCloud();
            }
        }

        public bool IsLocalizing
        {
            get; private set;
        }

        protected virtual void Awake()
        {
            PointCloud = new List<Vector3>();
        }

        protected virtual void Start()
        {
            if (!IsLocalizing && (ActiveControl == ActiveControlStrategy.HideBeforeLocalized || ActiveControl == ActiveControlStrategy.HideWhenNotLocalizing))
            {
                gameObject.SetActive(false);
            }

            switch (SourceType)
            {
                case DataSource.MapBuilder:
                    LoadMapBuilderInfo();
                    break;
                case DataSource.MapManager:
                    LoadMapManagerInfo(new MapManagerSourceData()
                    {
                        ID = MapManagerSource.ID,
                        Name = MapManagerSource.Name,
                    });
                    break;
                default:
                    break;
            }
        }

        protected virtual void OnDestroy()
        {
            if (mapWorker)
            {
                mapWorker = null;
                UpdateMapInLocalizer();
            }
            if (MapInfo != null)
            {
                MapInfo = null;
            }
        }

        // pointInView should be normalized to [0, 1]
        public List<Vector3> HitTest(Vector2 pointInView)
        {
            var points = new List<Vector3>();
            if (!IsLocalizing || !mapWorker || mapWorker.Localizer == null)
            {
                return points;
            }

            var session = mapWorker.Session;
            if (!session || session.FrameCameraParameters.OnNone || session.Assembly == null || !session.Assembly.Camera)
            {
                return points;
            }

            var coord = EasyARController.Instance.Display.ImageCoordinatesFromScreenCoordinates(pointInView, session.FrameCameraParameters.Value, session.Assembly.Camera);
            var hitPoints = mapWorker.Localizer.hitTestAgainstPointCloud(coord.ToEasyARVector());
            foreach (var p in hitPoints)
            {
                points.Add(new Vector3(p.data_0, p.data_1, -p.data_2));
            }
            return points;
        }


        public void Host(string name, Optional<Image> preview)
        {
            if (SourceType != DataSource.MapBuilder || MapInfo == null || !string.IsNullOrEmpty(MapInfo.ID) || !mapWorker || mapWorker.Builder == null)
            {
                throw new Exception("Map Unhostable");
            }
            mapWorker.HostSparseSpatialMap(this, name, preview, (map, status, error) =>
            {
                if (MapHost != null)
                {
                    MapHost(map, status, error);
                }
            });
        }

        internal void OnLocalization(bool status)
        {
            if (IsLocalizing != status)
            {
                if (status)
                {
                    if (ActiveControl == ActiveControlStrategy.HideWhenNotLocalizing || (ActiveControl == ActiveControlStrategy.HideBeforeLocalized && !localized))
                    {
                        gameObject.SetActive(true);
                    }
                    localized = true;
                    if (MapLocalized != null)
                    {
                        MapLocalized();
                    }
                }
                else
                {
                    if (ActiveControl == ActiveControlStrategy.HideWhenNotLocalizing)
                    {
                        gameObject.SetActive(false);
                    }
                    if (MapStopLocalize != null)
                    {
                        MapStopLocalize();
                    }
                }
                IsLocalizing = status;
            }
        }

        internal void UpdatePointCloud(Buffer buffer)
        {
            var bufferFloat = new float[buffer.size() / 4];

            if (buffer.size() > 0)
            {
                Marshal.Copy(buffer.data(), bufferFloat, 0, bufferFloat.Length);
            }
            PointCloud = Enumerable.Range(0, bufferFloat.Length / 3).Select(k =>
            {
                return new Vector3(bufferFloat[k * 3], bufferFloat[k * 3 + 1], -bufferFloat[k * 3 + 2]);
            }).ToList();

            UpdatePointCloud();
        }

        private void UpdatePointCloud()
        {
            if (!PointCloudParticleSystem)
            {
                return;
            }

            if (!ShowPointCloud || PointCloud == null)
            {
                PointCloudParticleSystem.Clear();
                return;
            }

            var particles = PointCloud.Select(p =>
            {
                var particle = new ParticleSystem.Particle();
                particle.position = p;
                particle.startLifetime = pointCloudParticleParameter.StartLifetime;
                particle.remainingLifetime = pointCloudParticleParameter.RemainingLifetime;
                particle.startSize = pointCloudParticleParameter.StartSize;
                particle.startColor = pointCloudParticleParameter.StartColor;
                return particle;
            }).ToArray();
            PointCloudParticleSystem.SetParticles(particles, particles.Length);
        }

        private void LoadMapBuilderInfo()
        {
            MapInfo = new SparseSpatialMapInfo();
            if (MapInfoAvailable != null)
            {
                MapInfoAvailable();
            }
            UpdateMapInLocalizer();
        }

        private void LoadMapManagerInfo(MapManagerSourceData source)
        {
            if (!string.IsNullOrEmpty(source.ID))
            {
                MapInfo = new SparseSpatialMapInfo() { ID = source.ID, Name = source.Name };
                if (MapInfoAvailable != null)
                {
                    MapInfoAvailable();
                }
                UpdateMapInLocalizer();
            }
        }

        private void UpdateMapInLocalizer()
        {
            if (MapInfo == null)
            {
                return;
            }
            if ((SourceType == DataSource.MapBuilder && !string.IsNullOrEmpty(MapInfo.ID)) ||
                (SourceType != DataSource.MapBuilder && string.IsNullOrEmpty(MapInfo.ID)))
            {
                return;
            }
            if (loader && loader != mapWorker)
            {
                switch (SourceType)
                {
                    case DataSource.MapBuilder:
                        loader.UnloadSparseSpatialMapBuild(this);
                        loader = null;
                        break;
                    case DataSource.MapManager:
                        loader.UnloadSparseSpatialMap(this, (map, status, error) =>
                        {
                            if (MapUnload != null)
                            {
                                MapUnload(map, status, error);
                            }
                        });
                        loader = null;
                        break;
                    default:
                        break;
                }
            }
            if (mapWorker && mapWorker != loader)
            {
                var worker = mapWorker;
                switch (SourceType)
                {
                    case DataSource.MapBuilder:
                        mapWorker.LoadSparseSpatialMapBuild(this);
                        loader = mapWorker;
                        break;
                    case DataSource.MapManager:
                        mapWorker.LoadSparseSpatialMap(this, (map, status, error) =>
                        {
                            if (worker == mapWorker && !status)
                            {
                                loader = null;
                            }
                            if (MapLoad != null)
                            {
                                MapLoad(map, status, error);
                            }
                        });
                        loader = mapWorker;
                        break;
                    default:
                        break;
                }
            }
        }

        public class SparseSpatialMapInfo
        {
            public string ID = string.Empty;
            public string Name = string.Empty;
        }

        [Serializable]
        public class MapManagerSourceData
        {
            public string ID = string.Empty;
            public string Name = string.Empty;
        }

        [Serializable]
        public class ParticleParameter
        {
            public Color32 StartColor = new Color32(11, 205, 255, 255);
            public float StartSize = 0.015f;
            public float StartLifetime = float.MaxValue;
            public float RemainingLifetime = float.MaxValue;
        }
    }
}
