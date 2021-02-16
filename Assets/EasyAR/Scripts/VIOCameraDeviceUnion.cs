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
    /// <para xml:lang="en"><see cref="MonoBehaviour"/> which controls VIO camera device (<see cref="MotionTrackerCameraDevice"/>, <see cref="ARKitCameraDevice"/> or <see cref="ARCoreCameraDevice"/>) in the scene, providing a few extensions in the Unity environment. Use <see cref="Device"/> directly when necessary.</para>
    /// <para xml:lang="zh">在场景中控制VIO相机设备（<see cref="MotionTrackerCameraDevice"/>、<see cref="ARKitCameraDevice"/>、<see cref="ARCoreCameraDevice"/>）的<see cref="MonoBehaviour"/>，在Unity环境下提供功能扩展。如有需要可以直接使用<see cref="Device"/>。</para>
    /// </summary>
    public class VIOCameraDeviceUnion : CameraSource
    {
        /// <summary>
        /// <para xml:lang="en">EasyAR Sense API (Union). Accessible between <see cref="DeviceCreated"/> and <see cref="DeviceClosed"/> event if available.</para>
        /// <para xml:lang="zh">EasyAR Sense API (Union)，如果功能可以使用，可以在<see cref="DeviceCreated"/>和<see cref="DeviceClosed"/>事件之间访问。</para>
        /// </summary>
        public DeviceUnion Device { get; private set; }

        /// <summary>
        /// <para xml:lang="en">Strategy of choosing VIO device.</para>
        /// <para xml:lang="zh">选择VIO设备的策略。</para>
        /// </summary>
        public DeviceChooseStrategy DeviceStrategy;

        private Action deviceStart;
        private Action deviceStop;
        private Action deviceClose;
        private Action<int> deviceSetBufferCapacity;
        private Func<int> deviceGetBufferCapacity;
        private Action<InputFrameSink> deviceConnect;
        private bool willOpen;

        /// <summary>
        /// <para xml:lang="en">Event when <see cref="Device"/> created.</para>
        /// <para xml:lang="zh"><see cref="Device"/> 创建的事件。</para>
        /// </summary>
        public event Action DeviceCreated;
        /// <summary>
        /// <para xml:lang="en">Event when <see cref="Device"/> opened.</para>
        /// <para xml:lang="zh"><see cref="Device"/> 打开的事件。</para>
        /// </summary>
        public event Action DeviceOpened;
        /// <summary>
        /// <para xml:lang="en">Event when <see cref="Device"/> closed.</para>
        /// <para xml:lang="zh"><see cref="Device"/> 关闭的事件。</para>
        /// </summary>
        public event Action DeviceClosed;

        /// <summary>
        /// <para xml:lang="en">Strategy of choosing VIO device.</para>
        /// <para xml:lang="zh">选择VIO设备的策略。</para>
        /// </summary>
        public enum DeviceChooseStrategy
        {
            /// <summary>
            /// <para xml:lang="en">Choose VIO device based on system support，in the order of System VIO device (ARKit/ARCore) > EasyAR Motion Tracker.</para>
            /// <para xml:lang="zh">根据系统对VIO设备支持情况进行选择，优先顺序为 系统VIO设备 (ARKit/ARCore) > EasyAR Motion Tracker。</para>
            /// </summary>
            SystemVIOFirst,
            /// <summary>
            /// <para xml:lang="en">Choose VIO device based on system support，in the order of EasyAR Motion Tracker > System VIO device (ARKit/ARCore)。</para>
            /// <para xml:lang="zh">根据系统对VIO设备支持情况进行选择，优先顺序为 EasyAR Motion Tracker > 系统VIO设备 (ARKit/ARCore)。</para>
            /// </summary>
            EasyARMotionTrackerFirst,
            /// <summary>
            /// <para xml:lang="en">Choose only System VIO device (ARKit/ARCore), do not use EasyAR Motion Tracker.</para>
            /// <para xml:lang="zh">只选择系统VIO设备 (ARKit/ARCore)，不使用EasyAR Motion Tracker。</para>
            /// </summary>
            SystemVIOOnly,
            /// <summary>
            /// <para xml:lang="en">Choose only EasyAR Motion Tracker, do not use System VIO device (ARKit/ARCore).</para>
            /// <para xml:lang="zh">只选择EasyAR Motion Tracker，不使用系统VIO设备 (ARKit/ARCore)。</para>
            /// </summary>
            EasyARMotionTrackerOnly,
        }

        public override int BufferCapacity
        {
            get
            {
                if (deviceGetBufferCapacity != null)
                {
                    return deviceGetBufferCapacity();
                }
                return bufferCapacity;
            }
            set
            {
                bufferCapacity = value;
                if (deviceSetBufferCapacity != null)
                {
                    deviceSetBufferCapacity(value);
                }
            }
        }

        public override bool HasSpatialInformation
        {
            get { return true; }
        }

        /// <summary>
        /// MonoBehaviour OnEnable
        /// </summary>
        protected override void OnEnable()
        {
            base.OnEnable();
            if (deviceStart != null)
            {
                deviceStart();
            }
        }

        /// <summary>
        /// MonoBehaviour Start
        /// </summary>
        protected override void Start()
        {
            switch (DeviceStrategy)
            {
                case DeviceChooseStrategy.SystemVIOFirst:
                    var arcoreFail = CheckARCore();
                    if (!MotionTrackerCameraDevice.isAvailable() && !ARKitCameraDevice.isAvailable() && !ARCoreCameraDevice.isAvailable())
                    {
                        throw new UIPopupException("VIOCameraDevice not available");
                    }
                    if (arcoreFail)
                    {
                        GUIPopup.EnqueueMessage(typeof(MotionTrackerCameraDevice) + " selected", 3);
                    }
                    break;
                case DeviceChooseStrategy.EasyARMotionTrackerFirst:
                    if (!MotionTrackerCameraDevice.isAvailable())
                    {
                        CheckARCore();
                    }
                    if (!MotionTrackerCameraDevice.isAvailable() && !ARKitCameraDevice.isAvailable() && !ARCoreCameraDevice.isAvailable())
                    {
                        throw new UIPopupException("VIOCameraDevice not available");
                    }
                    break;
                case DeviceChooseStrategy.SystemVIOOnly:
                    CheckARCore();
                    if (!ARKitCameraDevice.isAvailable() && Application.platform == RuntimePlatform.IPhonePlayer)
                    {
                        throw new UIPopupException(typeof(ARKitCameraDevice) + " not available");
                    }
                    else if (!ARCoreCameraDevice.isAvailable() && Application.platform == RuntimePlatform.Android)
                    {
                        throw new UIPopupException(typeof(ARCoreCameraDevice) + " not available");
                    }
                    else if (!ARKitCameraDevice.isAvailable() && !ARCoreCameraDevice.isAvailable())
                    {
                        throw new UIPopupException("System VIO not available");
                    }
                    break;
                case DeviceChooseStrategy.EasyARMotionTrackerOnly:
                    if (!MotionTrackerCameraDevice.isAvailable())
                    {
                        throw new UIPopupException(typeof(MotionTrackerCameraDevice) + " not available");
                    }
                    break;
                default:
                    break;
            }

            base.Start();
        }

        /// <summary>
        /// MonoBehaviour OnDisable
        /// </summary>
        protected override void OnDisable()
        {
            base.OnDisable();
            if (deviceStop != null)
            {
                deviceStop();
            }
        }

        /// <summary>
        /// <para xml:lang="en">Performs ray cast from the user&#39;s device in the direction of given screen point. Intersections with horizontal plane is detected in real time in the current field of view,and return the 3D point nearest to ray on horizontal plane. <paramref name="pointInView"/> should be normalized to [0, 1]^2.</para>
        /// <para xml:lang="zh">在当前视野内实时检测到的水平面上进行Hit Test,点击到某个水平面后返回该平面上距离Hit Test射线最近的3D点的位置坐标。<paramref name="pointInView"/> 需要被归一化到[0, 1]^2。</para>
        /// </summary>
        public List<Vector3> HitTestAgainstHorizontalPlane(Vector2 pointInView)
        {
            var points = new List<Vector3>();
            if (Device == null || Device.Type() != typeof(MotionTrackerCameraDevice))
            {
                return points;
            }
            if (!arSession || arSession.FrameCameraParameters.OnNone || arSession.Assembly == null || !arSession.Assembly.Camera)
            {
                return points;
            }

            var coord = EasyARController.Instance.Display.ImageCoordinatesFromScreenCoordinates(pointInView, arSession.FrameCameraParameters.Value, arSession.Assembly.Camera);
            var hitPoints = Device.MotionTrackerCameraDevice.hitTestAgainstHorizontalPlane(coord.ToEasyARVector());

            foreach (var p in hitPoints)
            {
                points.Add(new Vector3(p.data_0, p.data_1, -p.data_2));
            }

            return points;
        }

        /// <summary>
        /// <para xml:lang="en">Perform hit test against the point cloud and return the nearest 3D point. <paramref name="pointInView"/> should be normalized to [0, 1]^2.</para>
        /// <para xml:lang="zh">在当前点云中进行Hit Test,得到距离相机从近到远一条射线上的最近的一个3D点位置坐标。<paramref name="pointInView"/> 需要被归一化到[0, 1]^2。</para>
        /// </summary>
        public List<Vector3> HitTestAgainstPointCloud(Vector2 pointInView)
        {
            var points = new List<Vector3>();
            if (Device == null || Device.Type() != typeof(MotionTrackerCameraDevice))
            {
                return points;
            }
            if (!arSession || arSession.FrameCameraParameters.OnNone || arSession.Assembly == null || !arSession.Assembly.Camera)
            {
                return points;
            }

            var coord = EasyARController.Instance.Display.ImageCoordinatesFromScreenCoordinates(pointInView, arSession.FrameCameraParameters.Value, arSession.Assembly.Camera);
            var hitPoints = Device.MotionTrackerCameraDevice.hitTestAgainstPointCloud(coord.ToEasyARVector());

            foreach (var p in hitPoints)
            {
                points.Add(new Vector3(p.data_0, p.data_1, -p.data_2));
            }

            return points;
        }

        public override void Open()
        {
            willOpen = true;
            CameraDevice.requestPermissions(EasyARController.Scheduler, (Action<PermissionStatus, string>)((status, msg) =>
            {
                if (!willOpen)
                {
                    return;
                }
                if (status != PermissionStatus.Granted)
                {
                    Debug.LogError("Camera permission not granted");
                    return;
                }

                Close();

                switch (DeviceStrategy)
                {
                    case DeviceChooseStrategy.SystemVIOFirst:
                        if (ARKitCameraDevice.isAvailable())
                        {
                            CreateARKitCameraDevice();
                        }
                        else if (ARCoreCameraDevice.isAvailable())
                        {
                            CreateARCoreCameraDevice();
                        }
                        else if (MotionTrackerCameraDevice.isAvailable())
                        {
                            CreateMotionTrackerCameraDevice();
                        }
                        break;
                    case DeviceChooseStrategy.EasyARMotionTrackerFirst:
                        if (MotionTrackerCameraDevice.isAvailable())
                        {
                            CreateMotionTrackerCameraDevice();
                        }
                        else if (ARKitCameraDevice.isAvailable())
                        {
                            CreateARKitCameraDevice();
                        }
                        else if (ARCoreCameraDevice.isAvailable())
                        {
                            CreateARCoreCameraDevice();
                        }
                        break;
                    case DeviceChooseStrategy.SystemVIOOnly:
                        if (ARKitCameraDevice.isAvailable())
                        {
                            CreateARKitCameraDevice();
                        }
                        else if (ARCoreCameraDevice.isAvailable())
                        {
                            CreateARCoreCameraDevice();
                        }
                        break;
                    case DeviceChooseStrategy.EasyARMotionTrackerOnly:
                        if (MotionTrackerCameraDevice.isAvailable())
                        {
                            CreateMotionTrackerCameraDevice();
                        }
                        break;
                    default:
                        break;
                }
                if (DeviceCreated != null)
                {
                    DeviceCreated();
                }

                if (bufferCapacity != 0)
                {
                    deviceSetBufferCapacity(bufferCapacity);
                }

                if (sink != null)
                    deviceConnect(sink);

                if (enabled)
                {
                    OnEnable();
                }

                if (DeviceOpened != null)
                {
                    DeviceOpened();
                }
            }));
        }

        public override void Close()
        {
            willOpen = false;
            if (deviceClose != null)
            {
                OnDisable();
                deviceClose();
                if (DeviceClosed != null)
                {
                    DeviceClosed();
                }

                Device = null;
                deviceStart = null;
                deviceStop = null;
                deviceClose = null;
                deviceSetBufferCapacity = null;
                deviceGetBufferCapacity = null;
                deviceConnect = null;
            }
        }

        public override void Connect(InputFrameSink val)
        {
            base.Connect(val);
            if (deviceConnect != null)
            {
                deviceConnect(val);
            }
        }

        private void CreateMotionTrackerCameraDevice()
        {
            var device = new MotionTrackerCameraDevice();
            deviceStart = () =>
            {
                device.start();
            };
            deviceStop = () =>
            {
                device.stop();
            };
            deviceClose = () =>
            {
                device.close();
                device.Dispose();
            };
            deviceSetBufferCapacity = (int capacity) =>
            {
                device.setBufferCapacity(capacity);
            };
            deviceGetBufferCapacity = () =>
            {
                return device.bufferCapacity();
            };
            deviceConnect = (InputFrameSink sink) =>
            {
                device.inputFrameSource().connect(sink);
            };
            Device = device;
        }

        private void CreateARKitCameraDevice()
        {
            var device = new ARKitCameraDevice();
            deviceStart = () =>
            {
                device.start();
            };
            deviceStop = () =>
            {
                device.stop();
            };
            deviceClose = () =>
            {
                device.close();
                device.Dispose();
            };
            deviceSetBufferCapacity = (int capacity) =>
            {
                device.setBufferCapacity(capacity);
            };
            deviceGetBufferCapacity = () =>
            {
                return device.bufferCapacity();
            };
            deviceConnect = (InputFrameSink sink) =>
            {
                device.inputFrameSource().connect(sink);
            };
            Device = device;
        }

        private void CreateARCoreCameraDevice()
        {
            var device = new ARCoreCameraDevice();
            deviceStart = () =>
            {
                device.start();
            };
            deviceStop = () =>
            {
                device.stop();
            };
            deviceClose = () =>
            {
                device.close();
                device.Dispose();
            };
            deviceSetBufferCapacity = (int capacity) =>
            {
                device.setBufferCapacity(capacity);
            };
            deviceGetBufferCapacity = () =>
            {
                return device.bufferCapacity();
            };
            deviceConnect = (InputFrameSink sink) =>
            {
                device.inputFrameSource().connect(sink);
            };
            Device = device;
        }

        private bool CheckARCore()
        {
            if (Application.platform == RuntimePlatform.Android && EasyARController.ARCoreLoadFailed)
            {
                GUIPopup.EnqueueMessage("Fail to load ARCore library: arcore_sdk_c.so not found" + Environment.NewLine +
                    "You can turn off ARCore support on <EasyAR Settings> Asset", 3);
                return true;
            }
            return false;
        }

        /// <summary>
        /// <para xml:lang="en">VIO device Union.</para>
        /// <para xml:lang="zh">VIO设备的集合。</para>
        /// </summary>
        public class DeviceUnion
        {
            private MotionTrackerCameraDevice motionTrackerCameraDevice;
            private ARKitCameraDevice arKitCameraDevice;
            private ARCoreCameraDevice arCoreCameraDevice;

            public DeviceUnion(MotionTrackerCameraDevice value) { motionTrackerCameraDevice = value; DeviceType = VIODeviceType.EasyARMotionTracker; }
            public DeviceUnion(ARKitCameraDevice value) { arKitCameraDevice = value; DeviceType = VIODeviceType.ARKit; }
            public DeviceUnion(ARCoreCameraDevice value) { arCoreCameraDevice = value; DeviceType = VIODeviceType.ARCore; }

            public enum VIODeviceType
            {
                EasyARMotionTracker,
                ARKit,
                ARCore,
            }

            public VIODeviceType DeviceType { get; private set; }

            public MotionTrackerCameraDevice MotionTrackerCameraDevice
            {
                get { if (DeviceType != VIODeviceType.EasyARMotionTracker) throw new InvalidCastException(); ; return motionTrackerCameraDevice; }
                set { motionTrackerCameraDevice = value; DeviceType = VIODeviceType.EasyARMotionTracker; }
            }

            public ARKitCameraDevice ARKitCameraDevice
            {
                get { if (DeviceType != VIODeviceType.ARKit) throw new InvalidCastException(); ; return arKitCameraDevice; }
                set { arKitCameraDevice = value; DeviceType = VIODeviceType.ARKit; }
            }

            public ARCoreCameraDevice ARCoreCameraDevice
            {
                get { if (DeviceType != VIODeviceType.ARCore) throw new InvalidCastException(); return arCoreCameraDevice; }
                set { arCoreCameraDevice = value; DeviceType = VIODeviceType.ARCore; }
            }

            public static explicit operator MotionTrackerCameraDevice(DeviceUnion value) { return value.MotionTrackerCameraDevice; }
            public static explicit operator ARKitCameraDevice(DeviceUnion value) { return value.ARKitCameraDevice; }
            public static explicit operator ARCoreCameraDevice(DeviceUnion value) { return value.ARCoreCameraDevice; }

            public static implicit operator DeviceUnion(MotionTrackerCameraDevice value) { return new DeviceUnion(value); }
            public static implicit operator DeviceUnion(ARKitCameraDevice value) { return new DeviceUnion(value); }
            public static implicit operator DeviceUnion(ARCoreCameraDevice value) { return new DeviceUnion(value); }

            public Type Type()
            {
                switch (DeviceType)
                {
                    case VIODeviceType.EasyARMotionTracker:
                        return typeof(MotionTrackerCameraDevice);
                    case VIODeviceType.ARKit:
                        return typeof(ARKitCameraDevice);
                    case VIODeviceType.ARCore:
                        return typeof(ARCoreCameraDevice);
                    default: return typeof(void);
                }
            }

            public override string ToString()
            {
                switch (DeviceType)
                {
                    case VIODeviceType.EasyARMotionTracker:
                        return motionTrackerCameraDevice.ToString();
                    case VIODeviceType.ARKit:
                        return arKitCameraDevice.ToString();
                    case VIODeviceType.ARCore:
                        return arCoreCameraDevice.ToString();
                    default:
                        return "void";
                }
            }
        }
    }
}
