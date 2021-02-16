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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls <see cref="ObjectTracker"/> in the scene, providing a few extensions in the Unity environment. Use <see cref="Tracker"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制<see cref="ObjectTracker"/>的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="Tracker"/>。</para>
    /// </summary>
    public class ObjectTrackerFrameFilter : FrameFilter, FrameFilter.IFeedbackFrameSink, FrameFilter.IOutputFrameSource
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API. Accessible after Awake if available.</para>
        /// <para xml:lang="zh">EasyAR Sense API，如果功能可以使用，可以在Awake之后访问。</para>
        /// </summary>
        public ObjectTracker Tracker { get; private set; }

        [HideInInspector, SerializeField]
        private int simultaneousNum = 1;
        private List<int> previousTargetIDs = new List<int>();
        private Dictionary<int, TargetController> allTargetController = new Dictionary<int, TargetController>();
        private bool isStarted;

        /// <summary>
        /// <para xml:lang="en">Target load finish event. The bool value indicates the load success or not.</para>
        /// <para xml:lang="zh">Target加载完成的事件。bool值表示加载是否成功。</para>
        /// </summary>
        public event Action<ObjectTargetController, Target, bool> TargetLoad;
        /// <summary>
        /// <para xml:lang="en">Target unload finish event. The bool value indicates the unload success or not.</para>
        /// <para xml:lang="zh">Target卸载完成的事件。bool值表示卸载是否成功。</para>
        /// </summary>
        public event Action<ObjectTargetController, Target, bool> TargetUnload;
        private event Action SimultaneousNumChanged;

        public override int BufferRequirement
        {
            get { return Tracker.bufferRequirement(); }
        }

        /// <summary>
        /// <para xml:lang="en">The max number of targets which will be the simultaneously tracked by the tracker. Modify at any time and takes effect immediately.</para>
        /// <para xml:lang="zh">最大可被tracker跟踪的目标个数。可随时修改，立即生效。</para>
        /// </summary>
        public int SimultaneousNum
        {
            get
            {
                if (Tracker == null)
                    return simultaneousNum;
                return Tracker.simultaneousNum();
            }
            set
            {
                if (Tracker == null)
                {
                    simultaneousNum = value;
                    return;
                }
                simultaneousNum = value;
                Tracker.setSimultaneousNum(simultaneousNum);
                if (SimultaneousNumChanged != null)
                {
                    SimultaneousNumChanged();
                }
            }
        }

        /// <summary>
        /// <para xml:lang="en"><see cref="TargetController"/> that has been loaded.</para>
        /// <para xml:lang="zh">已加载的<see cref="TargetController"/>。</para>
        /// </summary>
        public List<TargetController> TargetControllers
        {
            get
            {
                List<TargetController> list = new List<TargetController>();
                foreach (var value in allTargetController.Values)
                {
                    list.Add(value);
                }
                return list;
            }
            private set { }
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
            if (!ObjectTracker.isAvailable())
            {
                throw new UIPopupException(typeof(ObjectTracker) + " not available");
            }

            Tracker = ObjectTracker.create();
            Tracker.setSimultaneousNum(simultaneousNum);
        }

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected virtual void OnEnable()
        {
            if (Tracker != null && isStarted)
            {
                Tracker.start();
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
            if (Tracker != null)
            {
                Tracker.stop();
            }
        }

        /// <summary>
        /// MonoBehaviour OnDestroy
        /// </summary>
        protected virtual void OnDestroy()
        {
            if (Tracker != null)
            {
                Tracker.Dispose();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Load target.</para>
        /// <para xml:lang="zh">加载target。</para>
        /// </summary>
        public void LoadTarget(ObjectTargetController target)
        {
            if (target.Target != null && TryGetTargetController(target.Target.runtimeID()))
            {
                return;
            }
            target.Tracker = this;
        }

        /// <summary>
        /// <para xml:lang="en">Unload target.</para>
        /// <para xml:lang="zh">卸载target。</para>
        /// </summary>
        public void UnloadTarget(ObjectTargetController target)
        {
            if (target.Target != null && !TryGetTargetController(target.Target.runtimeID()))
            {
                return;
            }
            target.Tracker = null;
        }

        public FeedbackFrameSink FeedbackFrameSink()
        {
            if (Tracker != null)
            {
                return Tracker.feedbackFrameSink();
            }
            return null;
        }

        public OutputFrameSource OutputFrameSource()
        {
            if (Tracker != null)
            {
                return Tracker.outputFrameSource();
            }
            return null;
        }

        public override void OnAssemble(ARSession session)
        {
            SimultaneousNumChanged += session.Assembly.ResetBufferCapacity;
        }

        public List<KeyValuePair<Optional<TargetController>, Matrix44F>> OnResult(Optional<FrameFilterResult> frameFilterResult)
        {
            var resultControllers = new List<KeyValuePair<Optional<TargetController>, Matrix44F>>();
            var targetIDs = new List<int>();
            var lostIDs = new List<int>();

            if (frameFilterResult.OnSome)
            {
                var targetTrackerResult = frameFilterResult.Value as TargetTrackerResult;
                foreach (var targetInstance in targetTrackerResult.targetInstances())
                {
                    using (targetInstance)
                    {
                        if (targetInstance.status() != TargetStatus.Tracked)
                        {
                            continue;
                        }
                        var targetOptional = targetInstance.target();
                        if (targetOptional.OnNone)
                        {
                            continue;
                        }
                        using (var target = targetOptional.Value)
                        {
                            var controller = TryGetTargetController(target.runtimeID());
                            if (controller)
                            {
                                targetIDs.Add(target.runtimeID());
                                resultControllers.Add(new KeyValuePair<Optional<TargetController>, Matrix44F>(controller, targetInstance.pose()));
                            }
                        }
                    }
                }
            }

            foreach (var id in previousTargetIDs)
            {
                lostIDs.Add(id);
            }
            foreach (var id in targetIDs)
            {
                if (lostIDs.Contains(id))
                {
                    lostIDs.Remove(id);
                }
                var controller = TryGetTargetController(id);
                if (controller && controller.IsLoaded)
                {
                    controller.OnTracking(true);
                }
            }
            foreach (var id in lostIDs)
            {
                var controller = TryGetTargetController(id);
                if (controller)
                {
                    controller.OnTracking(false);
                }
            }
            previousTargetIDs = targetIDs;
            return resultControllers;
        }

        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void LoadObjectTarget(ObjectTargetController controller, Action<Target, bool> callback)
        {
            Tracker.loadTarget(controller.Target, EasyARController.Scheduler, (target, status) =>
            {
                if (TargetLoad != null)
                {
                    TargetLoad(controller, target, status);
                }
                if (callback != null)
                {
                    callback(target, status);
                }
            });
            allTargetController[controller.Target.runtimeID()] = controller;
        }

        /// <summary>
        /// <para xml:lang="en">Internal method, do not call directly.</para>
        /// <para xml:lang="zh">内部方法，不可直接调用。</para>
        /// </summary>
        internal void UnloadObjectTarget(ObjectTargetController controller, Action<Target, bool> callback)
        {
            if (allTargetController.Remove(controller.Target.runtimeID()))
            {
                controller.OnTracking(false);
                Tracker.unloadTarget(controller.Target, EasyARController.Scheduler, (target, status) =>
                {
                    if (TargetUnload != null)
                    {
                        TargetUnload(controller, target, status);
                    }
                    if (callback != null)
                    {
                        callback(target, status);
                    }
                });
            }
        }

        protected override void OnHFlipChange(bool hFlip)
        {
            foreach (var value in allTargetController.Values)
            {
                value.HorizontalFlip = hFlip;
            }
        }

        private TargetController TryGetTargetController(int runtimeID)
        {
            TargetController controller;
            if (allTargetController.TryGetValue(runtimeID, out controller))
                return controller;
            return null;
        }
    }
}
