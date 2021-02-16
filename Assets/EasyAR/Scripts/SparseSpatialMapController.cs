//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
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
    /// <summary>
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls the map generated from <see cref="SparseSpatialMap"/> in the scene.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="SparseSpatialMap"/>生成的的地图的<see cref="MonoBehaviour"/>。</para>
    /// </summary>
    public class SparseSpatialMapController : MonoBehaviour
    {
        /// <summary>
        /// <para xml:lang="en">Map information. Accessible after MapInfoAvailable event.</para>
        /// <para xml:lang="zh">地图信息。可以在MapInfoAvailable event之后访问。</para>
        /// </summary>
        public SparseSpatialMapInfo MapInfo { get; private set; }

        /// <summary>
        /// <para xml:lang="en">The <see cref="ParticleSystem"/> used for point cloud rendering.</para>
        /// <para xml:lang="zh">渲染点云的<see cref="ParticleSystem"/>。</para>
        /// </summary>
        public ParticleSystem PointCloudParticleSystem;
        /// <summary>
        /// <para xml:lang="en">Strategy to control the <see cref="GameObject.active"/>. If you are willing to control <see cref="GameObject.active"/> or there are other components controlling <see cref="GameObject.active"/>, make sure to set it to <see cref="ActiveControlStrategy.None"/>.</para>
        /// <para xml:lang="zh"><see cref="GameObject.active"/>的控制策略。如果你打算自己控制<see cref="GameObject.active"/>或是有其它组件在控制<see cref="GameObject.active"/>，需要设为<see cref="ActiveControlStrategy.None"/>。</para>
        /// </summary>
        public ActiveControlStrategy ActiveControl;

        /// <summary>
        /// <para xml:lang="en">Map data source.</para>
        /// <para xml:lang="zh">Map数据来源。</para>
        /// </summary>
        public DataSource SourceType;

        /// <summary>
        /// <para xml:lang="en">MapManager source for map creation. Valid when <see cref="SourceType"/> == <see cref="DataSource.MapManager"/>.</para>
        /// <para xml:lang="zh">创建map的MapManager来源。在<see cref="SourceType"/> == <see cref="DataSource.MapManager"/>的时候有效。</para>
        /// </summary>
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


        /// <summary>
        /// <para xml:lang="en">Event when <see cref="MapInfo"/> can be used.</para>
        /// <para xml:lang="zh"><see cref="MapInfo"/> 可以使用的事件。</para>
        /// </summary>
        public event Action MapInfoAvailable;
        /// <summary>
        /// <para xml:lang="en">Map localized event.</para>
        /// <para xml:lang="zh">Map 定位到的事件。</para>
        /// </summary>
        public event Action MapLocalized;
        /// <summary>
        /// <para xml:lang="en">Stop map localization event.</para>
        /// <para xml:lang="zh">Map停止定位的事件。</para>
        /// </summary>
        public event Action MapStopLocalize;
        /// <summary>
        /// <para xml:lang="en">Map load finish event. The bool value indicates the load success or not. The string value is the error message when fail.</para>
        /// <para xml:lang="zh">Map加载完成的事件。bool值表示加载是否成功。string值表示出错时的错误信息。</para>
        /// </summary>
        public event Action<SparseSpatialMapInfo, bool, string> MapLoad;
        /// <summary>
        /// <para xml:lang="en">Map unload finish event. The bool value indicates the unload success or not. The string value is the error message when fail.</para>
        /// <para xml:lang="zh">Map卸载完成的事件。bool值表示卸载是否成功。string值表示出错时的错误信息。</para>
        /// </summary>
        public event Action<SparseSpatialMapInfo, bool, string> MapUnload;
        /// <summary>
        /// <para xml:lang="en">Map finish create and upload event. The bool value indicates success or not. The string value is the error message when fail.</para>
        /// <para xml:lang="zh">Map创建上传完成的事件。bool值表示是否成功。string值表示出错时的错误信息。</para>
        /// </summary>
        public event Action<SparseSpatialMapInfo, bool, string> MapHost;

        /// <summary>
        /// <para xml:lang="en">Strategy to control the <see cref="GameObject.active"/>.</para>
        /// <para xml:lang="zh"><see cref="GameObject.active"/>的控制策略。</para>
        /// </summary>
        public enum ActiveControlStrategy
        {
            /// <summary>
            /// <para xml:lang="en">False before the fist <see cref="MapLocalized"/> event, then true.</para>
            /// <para xml:lang="zh">在第一次<see cref="MapLocalized"/>事件之前Active为false，之后为true。</para>
            /// </summary>
            HideBeforeLocalized,
            /// <summary>
            /// <para xml:lang="en">Active is true when the map is localized, false when not localized.</para>
            /// <para xml:lang="zh">当没有被定位到时Active为false，当被定位到时Active为true。</para>
            /// </summary>
            HideWhenNotLocalizing,
            /// <summary>
            /// <para xml:lang="en">Do not control <see cref="GameObject.active"/>.</para>
            /// <para xml:lang="zh">不控制<see cref="GameObject.active"/>。</para>
            /// </summary>
            None,
        }

        /// <summary>
        /// <para xml:lang="en">Map data source type.</para>
        /// <para xml:lang="zh">地图数据来源类型。</para>
        /// </summary>
        public enum DataSource
        {
            /// <summary>
            /// <para xml:lang="en"><see cref="SparseSpatialMap"/> MapBuilder.</para>
            /// <para xml:lang="zh"><see cref="SparseSpatialMap"/> MapBuilder。</para>
            /// </summary>
            MapBuilder,
            /// <summary>
            /// <para xml:lang="en"><see cref="SparseSpatialMapManager"/>.</para>
            /// <para xml:lang="zh"><see cref="SparseSpatialMapManager"/>。</para>
            /// </summary>
            MapManager,
        }

        /// <summary>
        /// <para xml:lang="en">The <see cref="SparseSpatialMapWorkerFrameFilter"/> which loads the map after <see cref="MapInfoAvailable"/>. When set to null, the map will be unloaded from MapWorker previously set. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh">在<see cref="MapInfoAvailable"/>之后加载target的<see cref="SparseSpatialMapWorkerFrameFilter"/>。如果设为null，map将会被从之前设置的MapWorker中卸载。可随时修改，立即生效。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Parameters for point cloud particles rendering.</para>
        /// <para xml:lang="zh">渲染点云粒子的参数。</para>
        /// </summary>
        public ParticleParameter PointCloudParticleParameter
        {
            get { return pointCloudParticleParameter; }
            set
            {
                pointCloudParticleParameter = value;
                UpdatePointCloud();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Point cloud data.</para>
        /// <para xml:lang="zh">点云数据。</para>
        /// </summary>
        public List<Vector3> PointCloud
        {
            get; private set;
        }

        /// <summary>
        /// <para xml:lang="en">Show or hide point cloud.</para>
        /// <para xml:lang="zh">显示或隐藏点云。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Is the map being localized at the moment.</para>
        /// <para xml:lang="zh">当前map是否在定位中。</para>
        /// </summary>
        public bool IsLocalizing
        {
            get; private set;
        }

        /// <summary>
        /// MonoBehaviour Awake
        /// </summary>
        protected virtual void Awake()
        {
            PointCloud = new List<Vector3>();
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
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

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Perform hit test against the point cloud. The results are returned sorted by their distance to the camera in ascending order. <paramref name="pointInView"/> should be normalized to [0, 1]^2.</para>
        /// <para xml:lang="zh">在当前点云中进行Hit Test，得到距离相机从近到远一条射线上的n（n>=0）个位置坐标。<paramref name="pointInView"/> 需要被归一化到[0, 1]^2。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Create and upload map. <paramref name="name"/> is the map name and <paramref name="preview"/> is the optional map preview image.</para>
        /// <para xml:lang="zh">创建和上传Map。<paramref name="name"/>为地图的名字，<paramref name="preview"/>是可选的map预览图 。</para>
        /// </summary>
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


        /// <summary>
        /// <para xml:lang="en">Usually only for internal assemble use. Process localization event.</para>
        /// <para xml:lang="zh">通常只在内部组装时使用。处理定位事件。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Update point cloud data. Internal method.</para>
        /// <para xml:lang="zh">更新点云数据。内部方法。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Sparse map information.</para>
        /// <para xml:lang="zh">稀疏地图信息。</para>
        /// </summary>
        public class SparseSpatialMapInfo
        {
            /// <summary>
            /// <para xml:lang="en">Sparse map ID.</para>
            /// <para xml:lang="zh">稀疏地图的ID。</para>
            /// </summary>
            public string ID = string.Empty;
            /// <summary>
            /// <para xml:lang="en">Sparse map name.</para>
            /// <para xml:lang="zh">稀疏地图的名字。</para>
            /// </summary>
            public string Name = string.Empty;
        }

        /// <summary>
        /// <para xml:lang="en">MapManager source for map creation.</para>
        /// <para xml:lang="zh">创建map的MapManager来源。</para>
        /// </summary>
        [Serializable]
        public class MapManagerSourceData
        {
            /// <summary>
            /// <para xml:lang="en">Sparse map ID.</para>
            /// <para xml:lang="zh">稀疏地图的ID。</para>
            /// </summary>
            public string ID = string.Empty;
            /// <summary>
            /// <para xml:lang="en">Sparse map name.</para>
            /// <para xml:lang="zh">稀疏地图的名字。</para>
            /// </summary>
            public string Name = string.Empty;
        }

        /// <summary>
        /// <para xml:lang="en">Parameters for point cloud particles rendering.</para>
        /// <para xml:lang="zh">渲染点云粒子的参数。</para>
        /// </summary>
        [Serializable]
        public class ParticleParameter
        {
            /// <summary>
            /// <para xml:lang="en">Particles start color.</para>
            /// <para xml:lang="zh">粒子初始颜色。</para>
            /// </summary>
            public Color32 StartColor = new Color32(11, 205, 255, 255);
            /// <summary>
            /// <para xml:lang="en">Particles start size.</para>
            /// <para xml:lang="zh">粒子初始大小。</para>
            /// </summary>
            public float StartSize = 0.015f;
            /// <summary>
            /// <para xml:lang="en">Particles start life time.</para>
            /// <para xml:lang="zh">粒子初始生存时间。</para>
            /// </summary>
            public float StartLifetime = float.MaxValue;
            /// <summary>
            /// <para xml:lang="en">Particles remaining life time.</para>
            /// <para xml:lang="zh">粒子剩余生存时间。</para>
            /// </summary>
            public float RemainingLifetime = float.MaxValue;
        }

    }
}
