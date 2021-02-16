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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="DenseSpatialMap"/> in the scene, providing a few extensions in the Unity environment. Use <see cref="Builder"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="DenseSpatialMap"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="Builder"/>。</para>
    /// </summary>
    public class DenseSpatialMapBuilderFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.ISpatialInformationSink
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after Awake if available.</para>
        /// <para xml:lang="zh">EasyAR Sense API，如果功能可以使用，可以在Awake之后访问。</para>
        /// </summary>
        public DenseSpatialMap Builder { get; private set; }

        /// <summary>
        /// <para xml:lang="en"><see cref="Material"/> for map mesh render.</para>
        /// <para xml:lang="zh">用于渲染Map网格的<see cref="Material"/>。</para>
        /// </summary>
        public Material MapMeshMaterial;

        /// <summary>
        /// <para xml:lang="en">The max number of mesh blocks to be updated each frame. Decrease this value if the mesh update slows rendering.</para>
        /// <para xml:lang="zh">每帧更新网格块的最大数量。如果网格更新使渲染变慢可以降低这个数值。</para>
        /// </summary>
        public int BlockUpdateLimitation = 5;


        private Dictionary<Vector3, DenseSpatialMapBlockController> blocksDict = new Dictionary<Vector3, DenseSpatialMapBlockController>();
        private List<DenseSpatialMapBlockController> dirtyBlocks = new List<DenseSpatialMapBlockController>();
        private GameObject mapRoot;
        private bool isStarted;
        private bool renderMesh = true;
        private Material mapMaterial;
        private DenseSpatialMapDepthRenderer depthRenderer;

        /// <summary>
        /// <para xml:lang="en">Event when a new mesh block created.</para>
        /// <para xml:lang="zh">新网格块创建的事件。</para>
        /// </summary>
        public event Action<DenseSpatialMapBlockController> MapCreate;
        /// <summary>
        /// <para xml:lang="en">Event when mesh block updates.</para>
        /// <para xml:lang="zh">网格块更新的事件。</para>
        /// </summary>
        public event Action<List<DenseSpatialMapBlockController>> MapUpdate;

        public override int BufferRequirement
        {
            get { return Builder.bufferRequirement(); }
        }

        public MotionTrackingStatus TrackingStatus
        {
            get; private set;
        }

        /// <summary>
        /// <para xml:lang="en">Mesh render on/off.</para>
        /// <para xml:lang="zh">是否渲染网格。</para>
        /// </summary>
        public bool RenderMesh
        {
            get { return renderMesh; }
            set
            {
                renderMesh = value;
                foreach (var block in blocksDict)
                {
                    block.Value.GetComponent<MeshRenderer>().enabled = renderMesh;
                    if (depthRenderer)
                    {
                        depthRenderer.enabled = renderMesh;
                    }
                }
            }
        }

        /// <summary>
        /// <para xml:lang="en">Mesh color.</para>
        /// <para xml:lang="zh">网格颜色。</para>
        /// </summary>
        public Color MeshColor
        {
            get
            {
                if (mapMaterial)
                {
                    return mapMaterial.color;
                }
                return Color.black;
            }
            set
            {
                if (mapMaterial)
                {
                    mapMaterial.color = value;
                }
            }
        }

        /// <summary>
        /// <para xml:lang="en">All mesh blocks.</para>
        /// <para xml:lang="zh">当前所有网格块。</para>
        /// </summary>
        public List<DenseSpatialMapBlockController> MeshBlocks
        {
            get
            {
                var list = new List<DenseSpatialMapBlockController>();
                foreach (var item in blocksDict)
                {
                    list.Add(item.Value);
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
            if (!DenseSpatialMap.isAvailable())
            {
                throw new UIPopupException(typeof(DenseSpatialMap) + " not available");
            }
            mapRoot = new GameObject("DenseSpatialMapRoot");
            Builder = DenseSpatialMap.create();
            depthRenderer = GetComponent<DenseSpatialMapDepthRenderer>();
            mapMaterial = Instantiate(MapMeshMaterial);

            if (depthRenderer && depthRenderer.enabled)
            {
                depthRenderer.MapMeshMaterial = mapMaterial;
            }
        }

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            if (Builder != null && isStarted)
            {
                Builder.start();
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
        /// MonoBehaviour Update
        /// </summary>
        protected virtual void Update()
        {
            if (dirtyBlocks.Count <= 0)
            {
                if (Builder.updateSceneMesh(false))
                {
                    using (var mesh = Builder.getMesh())
                    {
                        foreach (var blockInfo in mesh.getBlocksInfoIncremental())
                        {
                            DenseSpatialMapBlockController oldBlock;
                            blocksDict.TryGetValue(new Vector3(blockInfo.x, blockInfo.y, blockInfo.z), out oldBlock);
                            if (oldBlock == null)
                            {
                                var go = new GameObject("MeshBlock");
                                go.AddComponent<MeshCollider>();
                                go.AddComponent<MeshFilter>();
                                var renderer = go.AddComponent<MeshRenderer>();
                                renderer.material = mapMaterial;
                                renderer.enabled = RenderMesh;
                                var block = go.AddComponent<DenseSpatialMapBlockController>();
                                block.UpdateData(blockInfo, mesh);
                                go.transform.parent = mapRoot.transform;
                                blocksDict.Add(new Vector3(blockInfo.x, blockInfo.y, blockInfo.z), block);
                                dirtyBlocks.Add(block);
                                if (MapCreate != null)
                                {
                                    MapCreate(block);
                                }
                            }
                            else if (oldBlock.Info.version != blockInfo.version)
                            {
                                oldBlock.UpdateData(blockInfo, mesh);
                                if (!dirtyBlocks.Contains(oldBlock))
                                {
                                    dirtyBlocks.Add(oldBlock);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                var count = Math.Min(dirtyBlocks.Count, BlockUpdateLimitation);
                var blocks = dirtyBlocks.GetRange(0, count);
                foreach (var block in blocks)
                {
                    block.UpdateMesh();
                }
                dirtyBlocks.RemoveRange(0, count);
                if (MapUpdate != null)
                {
                    MapUpdate(blocks);
                }
            }
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected virtual void OnDisable()
        {
            if (Builder != null)
            {
                Builder.stop();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            if (Builder != null)
            {
                Builder.Dispose();
            }
            if (mapRoot)
            {
                Destroy(mapRoot);
            }
            if (mapMaterial)
            {
                Destroy(mapMaterial);
            }
        }

        public InputFrameSink InputFrameSink()
        {
            if (Builder != null)
            {
                return Builder.inputFrameSink();
            }
            return null;
        }

        public void OnTracking(MotionTrackingStatus status)
        {
            TrackingStatus = status;
        }

        public override void OnAssemble(ARSession session)
        {
            if (depthRenderer)
            {
                depthRenderer.RenderDepthCamera = session.Assembly.Camera;
            }
            session.WorldRootChanged += (WorldRootController worldRoot) =>
            {
                mapRoot.transform.parent = worldRoot.transform;
            };
        }
    }
}
