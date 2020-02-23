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
    public class DenseSpatialMapBuilderFrameFilter : FrameFilter, FrameFilter.IInputFrameSink, FrameFilter.ISpatialInformationSink
    {
        /// <summary>
        /// EasyAR Sense API. Accessible after Awake if available.
        /// </summary>
        public DenseSpatialMap Builder { get; private set; }

        public Material MapMeshMaterial;
        public int BlockUpdateLimitation = 5;

        private Dictionary<Vector3, DenseSpatialMapBlockController> blocksDict = new Dictionary<Vector3, DenseSpatialMapBlockController>();
        private List<DenseSpatialMapBlockController> dirtyBlocks = new List<DenseSpatialMapBlockController>();
        private GameObject mapRoot;
        private bool isStarted;
        private bool renderMesh = true;
        private Material mapMaterial;
        private DenseSpatialMapDepthRenderer depthRenderer;

        public event Action<DenseSpatialMapBlockController> MapCreate;
        public event Action<List<DenseSpatialMapBlockController>> MapUpdate;

        public override int BufferRequirement
        {
            get { return Builder.bufferRequirement(); }
        }

        public MotionTrackingStatus TrackingStatus
        {
            get; private set;
        }

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

        protected virtual void OnEnable()
        {
            if (Builder != null && isStarted)
            {
                Builder.start();
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

        protected virtual void OnDisable()
        {
            if (Builder != null)
            {
                Builder.stop();
            }
        }

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
