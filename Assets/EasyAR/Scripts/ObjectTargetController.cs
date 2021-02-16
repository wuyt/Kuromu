//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
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
    /// <summary>
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="ObjectTarget"/> in the scene, providing a few extensions in the Unity environment. Use <see cref="Target"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="ObjectTarget"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="Target"/>。</para>
    /// </summary>
    public class ObjectTargetController : TargetController
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after TargetAvailable event.</para>
        /// <para xml:lang="zh">EasyAR Sense API，可以在TargetAvailable event之后访问。</para>
        /// </summary>
        public ObjectTarget Target { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Target data source.</para>
        /// <para xml:lang="zh">Target数据来源。</para>
        /// </summary>
        public DataSource SourceType = DataSource.ObjFile;
        /// <summary>
        /// <para xml:lang="en">Obj file data source for target creation. Valid when <see cref="SourceType"/> == <see cref="DataSource.ObjFile"/>.</para>
        /// <para xml:lang="zh">创建target的obj文件数据来源。在<see cref="SourceType"/> == <see cref="DataSource.ObjFile"/>的时候有效。</para>
        /// </summary>
        [HideInInspector, SerializeField]
        public ObjFileSourceData ObjFileSource = new ObjFileSourceData();
        /// <summary>
        /// <para xml:lang="en">Target source when using a target already created. Valid when <see cref="SourceType"/> == <see cref="DataSource.Target"/>.</para>
        /// <para xml:lang="zh">直接使用创建好的target时的target来源。在<see cref="SourceType"/> == <see cref="DataSource.Target"/>的时候有效。</para>
        /// </summary>
        public ObjectTarget TargetSource;

        [HideInInspector, SerializeField]
        private bool trackerHasSet;
        [HideInInspector, SerializeField]
        private ObjectTrackerFrameFilter tracker;
        private ObjectTrackerFrameFilter loader;
        private float scale = 1;
        private float scaleX = 1;
        private bool preHFlip;

        /// <summary>
        /// <para xml:lang="en">Event when <see cref="Target"/> can be used.</para>
        /// <para xml:lang="zh"><see cref="Target"/> 可以使用的事件。</para>
        /// </summary>
        public event Action TargetAvailable;
        /// <summary>
        /// <para xml:lang="en">Target load finish event. The bool value indicates the load success or not.</para>
        /// <para xml:lang="zh">Target加载完成的事件。bool值表示加载是否成功。</para>
        /// </summary>
        public event Action<Target, bool> TargetLoad;
        /// <summary>
        /// <para xml:lang="en">Target unload finish event. The bool value indicates the unload success or not.</para>
        /// <para xml:lang="zh">Target卸载完成的事件。bool值表示卸载是否成功。</para>
        /// </summary>
        public event Action<Target, bool> TargetUnload;

        /// <summary>
        /// <para xml:lang="en">Target data source type.</para>
        /// <para xml:lang="zh">Target数据来源类型。</para>
        /// </summary>
        public enum DataSource
        {
            /// <summary>
            /// <para xml:lang="en">Obj file and other files related.</para>
            /// <para xml:lang="zh">obj模型文件及相关其它文件。</para>
            /// </summary>
            ObjFile,
            /// <summary>
            /// <para xml:lang="en"><see cref="ImageTarget"/> object.</para>
            /// <para xml:lang="zh"><see cref="ImageTarget"/>对象。</para>
            /// </summary>
            Target,
        }

        /// <summary>
        /// <para xml:lang="en">The <see cref="ImageTrackerFrameFilter"/> which loads the target after <see cref="TargetAvailable"/>. When set to null, the target will be unloaded from tracker previously set. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh">在<see cref="TargetAvailable"/>之后加载target的<see cref="ImageTrackerFrameFilter"/>。如果设为null，target将会被从之前设置的tracker中卸载。可随时修改，立即生效。</para>
        /// </summary>
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

        /// <summary>
        /// <para xml:lang="en">Bounding box of the target.</para>
        /// <para xml:lang="zh">Target的包围盒。</para>
        /// </summary>
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

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
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

        /// <summary>
        /// MonoBehaviour Update
        /// </summary>
        protected virtual void Update()
        {
            CheckScale();
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
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
                    if (status)
                    {
                        IsLoaded = false;
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
                    IsLoaded = status;
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

        /// <summary>
        /// <para xml:lang="en">Obj file data for target creation.</para>
        /// <para xml:lang="zh">创建target的obj文件数据。</para>
        /// </summary>
        [Serializable]
        public class ObjFileSourceData
        {
            /// <summary>
            /// <para xml:lang="en">File path type.</para>
            /// <para xml:lang="zh">文件路径类型。</para>
            /// </summary>
            public PathType PathType = PathType.StreamingAssets;
            /// <summary>
            /// <para xml:lang="en">Obj file path.</para>
            /// <para xml:lang="zh">Obj文件路径。</para>
            /// </summary>
            public string ObjPath = string.Empty;
            /// <summary>
            /// <para xml:lang="en">extra file paths referenced in obj file and other files, like *.mtl, *jpg, *.png. These files are usually multiple textures and mtl files.</para>
            /// <para xml:lang="zh">Obj文件及其它文件中引用的额外文件路径，如：*.mtl, *.jpg, *.png等。这些文件一般由多个贴图文件，和mtl组成。</para>
            /// </summary>
            public List<string> ExtraFilePaths = new List<string>();
            /// <summary>
            /// <para xml:lang="en">Target name.</para>
            /// <para xml:lang="zh">Target名字。</para>
            /// </summary>
            public string Name = string.Empty;
            /// <summary>
            /// <para xml:lang="en">Target scale in meter. Reference <see cref="ObjectTarget.scale"/>.</para>
            /// <para xml:lang="zh">Target的缩放比例，单位为米。参考<see cref="ObjectTarget.scale"/>。</para>
            /// </summary>
            public float Scale = 1;
        }
    }
}
