//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEngine;

namespace easyar
{
    public class VIOCameraDeviceUnion : CameraSource
    {
        /// <summary>
        /// EasyAR Sense API (Unioned). Accessible between DeviceCreated and DeviceClosed event if available.
        /// </summary>
        public DeviceUnion Device { get; private set; }

        public DeviceChooseStrategy DeviceStrategy;

        private Action deviceStart;
        private Action deviceStop;
        private Action deviceClose;
        private Action<int> deviceSetBufferCapacity;
        private Func<int> deviceGetBufferCapacity;
        private Action<InputFrameSink> deviceConnect;
        private bool willOpen;

        public event Action DeviceCreated;
        public event Action DeviceOpened;
        public event Action DeviceClosed;

        public enum DeviceChooseStrategy
        {
            SystemVIOFirst,
            EasyARMotionTrackerFirst,
            SystemVIOOnly,
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

        protected override void OnEnable()
        {
            base.OnEnable();
            if (deviceStart != null)
            {
                deviceStart();
            }
        }

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

        protected override void OnDisable()
        {
            base.OnDisable();
            if (deviceStop != null)
            {
                deviceStop();
            }
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
