//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace easyar
{
    public class ObjectTargetController : TargetController
    {
        /// <summary>
        /// EasyAR Sense API. Accessible after TargetAvailable event.
        /// </summary>
        public ObjectTarget Target { get; private set; }

        public DataSource SourceType = DataSource.ObjFile;
        [HideInInspector, SerializeField]
        public ObjFileSourceData ObjFileSource = new ObjFileSourceData();
        public ObjectTarget TargetSource;

        [HideInInspector, SerializeField]
        private bool trackerHasSet;
        [HideInInspector, SerializeField]
        private ObjectTrackerFrameFilter tracker;
        private ObjectTrackerFrameFilter loader;
        private float scale = 1;
        private float scaleX = 1;
        private bool preHFlip;

        public event Action TargetAvailable;
        public event Action<Target, bool> TargetLoad;
        public event Action<Target, bool> TargetUnload;

        public enum DataSource
        {
            ObjFile,
            Target,
        }

        public ObjectTrackerFrameFilter Tracker
        {
            get
            {
                return tracker;
            }
            set
            {
                tracker = value;
                UpdateTargetInTracker();
            }
        }

        public List<Vector3> BoundingBox
        {
            get
            {
                var boundingBox = new List<Vector3>();
                if (Target == null)
                {
                    return boundingBox;
                }
                var boundingBoxVec3F = Target.boundingBox();
                foreach (var box in boundingBoxVec3F)
                {
                    boundingBox.Add(box.ToUnityVector());
                }
                return boundingBox;
            }
            private set { }
        }

        protected override void Start()
        {
            base.Start();
            if (!EasyARController.Initialized)
            {
                return;
            }

            switch (SourceType)
            {
                case DataSource.ObjFile:
                    LoadObjFile(new ObjFileSourceData()
                    {
                        PathType = ObjFileSource.PathType,
                        ObjPath = ObjFileSource.ObjPath,
                        ExtraFilePaths = ObjFileSource.ExtraFilePaths,
                        Name = ObjFileSource.Name,
                        Scale = ObjFileSource.Scale
                    });
                    break;
                case DataSource.Target:
                    LoadTarget(TargetSource);
                    break;
                default:
                    break;
            }
        }

        protected virtual void Update()
        {
            CheckScale();
        }

        protected virtual void OnDestroy()
        {
            if (tracker)
            {
                tracker = null;
                UpdateTargetInTracker();
            }
            if (Target != null)
            {
                Target.Dispose();
                Target = null;
            }
        }

        protected override void OnTracking()
        {
            CheckScale();
        }

        private void LoadObjFile(ObjFileSourceData source)
        {
            EasyARController.Instance.StartCoroutine(LoadObjFileFromSource(source));
        }

        private void LoadTarget(ObjectTarget source)
        {
            Target = source;
            if (Target != null && TargetAvailable != null)
            {
                TargetAvailable();
            }
            UpdateScale();
            UpdateTargetInTracker();
        }

        private IEnumerator LoadObjFileFromSource(ObjFileSourceData source)
        {
            using (var objBufferDic = new BufferDictionary())
            {
                yield return EasyARController.Instance.StartCoroutine(FileUtil.LoadFile(source.ObjPath, source.PathType, (Buffer buffer) =>
                {
                    objBufferDic.set(FileUtil.PathToUrl(source.ObjPath), buffer.Clone());
                }));
                foreach (var filePath in source.ExtraFilePaths)
                {
                    yield return EasyARController.Instance.StartCoroutine(FileUtil.LoadFile(filePath, source.PathType, (Buffer buffer) =>
                    {
                        objBufferDic.set(FileUtil.PathToUrl(filePath), buffer.Clone());
                    }));
                }

                using (var param = new ObjectTargetParameters())
                {
                    param.setBufferDictionary(objBufferDic);
                    param.setObjPath(FileUtil.PathToUrl(source.ObjPath));
                    param.setName(source.Name);
                    param.setScale(source.Scale);
                    param.setUid(Guid.NewGuid().ToString());
                    param.setMeta(string.Empty);

                    var targetOptional = ObjectTarget.createFromParameters(param);
                    if (targetOptional.OnSome)
                    {
                        Target = targetOptional.Value;
                        if (Target != null && TargetAvailable != null)
                        {
                            TargetAvailable();
                        }
                    }
                    else
                    {
                        throw new Exception("invalid parameter");
                    }
                }
            }
            UpdateTargetInTracker();
        }

        private void UpdateTargetInTracker()
        {
            if (Target == null)
            {
                return;
            }
            if (loader && loader != tracker)
            {
                loader.UnloadObjectTarget(this, (target, status) =>
                {
                    if (TargetUnload != null)
                    {
                        TargetUnload(target, status);
                    }
                });
                loader = null;
            }
            if (tracker && tracker != loader)
            {
                var trackerLoad = tracker;
                tracker.LoadObjectTarget(this, (target, status) =>
                {
                    if (trackerLoad == tracker && !status)
                    {
                        loader = null;
                    }
                    UpdateScale();
                    if (TargetLoad != null)
                    {
                        TargetLoad(target, status);
                    }
                });
                loader = tracker;
            }
        }

        private void UpdateScale()
        {
            if (Target == null)
                return;
            scale = Target.scale();
            var vec3Unit = Vector3.one;
            if (HorizontalFlip)
            {
                vec3Unit.x = -vec3Unit.x;
            }
            transform.localScale = vec3Unit * scale;
            scaleX = transform.localScale.x;
            preHFlip = HorizontalFlip;
        }

        private void CheckScale()
        {
            if (Target == null)
                return;
            if (scaleX != transform.localScale.x)
            {
                Target.setScale(Math.Abs(transform.localScale.x));
                UpdateScale();
            }
            else if (scale != transform.localScale.y)
            {
                Target.setScale(Math.Abs(transform.localScale.y));
                UpdateScale();
            }
            else if (scale != transform.localScale.z)
            {
                Target.setScale(Math.Abs(transform.localScale.z));
                UpdateScale();
            }
            else if (scale != Target.scale())
            {
                UpdateScale();
            }
            else if (preHFlip != HorizontalFlip)
            {
                UpdateScale();
            }
        }

        [Serializable]
        public class ObjFileSourceData
        {
            public PathType PathType = PathType.StreamingAssets;
            public string ObjPath = string.Empty;
            public List<string> ExtraFilePaths = new List<string>();
            public string Name = string.Empty;
            public float Scale = 1;
        }
    }
}
