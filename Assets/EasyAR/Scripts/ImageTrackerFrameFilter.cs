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
    public class ImageTrackerFrameFilter : FrameFilter, FrameFilter.IFeedbackFrameSink, FrameFilter.IOutputFrameSource
    {
        /// <summary>
        /// EasyAR Sense API. Accessible after Awake if available.
        /// </summary>
        public ImageTracker Tracker { get; private set; }

        public ImageTrackerMode TrackerMode;

        [HideInInspector, SerializeField]
        private int simultaneousNum = 1;
        private List<int> previousTargetIDs = new List<int>();
        private Dictionary<int, TargetController> allTargetController = new Dictionary<int, TargetController>();
        private bool isStarted;

        public event Action<ImageTargetController, Target, bool> TargetLoad;
        public event Action<ImageTargetController, Target, bool> TargetUnload;
        private event Action SimultaneousNumChanged;

        public override int BufferRequirement
        {
            get { return Tracker.bufferRequirement(); }
        }

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

        protected virtual void Awake()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            if (!ImageTracker.isAvailable())
            {
                throw new UIPopupException(typeof(ImageTracker) + " not available");
            }

            Tracker = ImageTracker.createWithMode(TrackerMode);
            Tracker.setSimultaneousNum(simultaneousNum);
        }

        protected virtual void OnEnable()
        {
            if (Tracker != null && isStarted)
            {
                Tracker.start();
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
            if (Tracker != null)
            {
                Tracker.stop();
            }
        }

        protected virtual void OnDestroy()
        {
            if (Tracker != null)
            {
                Tracker.Dispose();
            }
        }

        public void LoadTarget(ImageTargetController target)
        {
            if (target.Target != null && TryGetTargetController(target.Target.runtimeID()))
            {
                return;
            }
            target.Tracker = this;
        }

        public void UnloadTarget(ImageTargetController target)
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
                if (controller)
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

        internal void LoadImageTarget(ImageTargetController controller, Action<Target, bool> callback)
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

        internal void UnloadImageTarget(ImageTargetController controller, Action<Target, bool> callback)
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
