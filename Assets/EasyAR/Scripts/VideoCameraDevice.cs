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
    public class VideoCameraDevice : CameraSource
    {
        /// <summary>
        /// EasyAR Sense API. Accessible between DeviceCreated and DeviceClosed event if available.
        /// </summary>
        public CameraDevice Device { get; private set; }

        public CameraDeviceFocusMode FocusMode = CameraDeviceFocusMode.Continousauto;
        public Vector2 CameraSize = new Vector2(1280, 960);
        public CameraDeviceOpenMethod CameraOpenMethod = CameraDeviceOpenMethod.DeviceType;
        [HideInInspector, SerializeField]
        public CameraDeviceType CameraType = CameraDeviceType.Back;
        [HideInInspector, SerializeField]
        public int CameraIndex = 0;

        [HideInInspector, SerializeField]
        private CameraDevicePreference cameraPreference = CameraDevicePreference.PreferObjectSensing;
        private CameraParameters parameters = null;
        private bool willOpen;

        public event Action DeviceCreated;
        public event Action DeviceOpened;
        public event Action DeviceClosed;

        public enum CameraDeviceOpenMethod
        {
            DeviceType,
            DeviceIndex,
        }

        public override int BufferCapacity
        {
            get
            {
                if (Device != null)
                {
                    return Device.bufferCapacity();
                }
                return bufferCapacity;
            }
            set
            {
                bufferCapacity = value;
                if (Device != null)
                {
                    Device.setBufferCapacity(value);
                }
            }
        }

        public override bool HasSpatialInformation
        {
            get { return false; }
        }

        public CameraDevicePreference CameraPreference
        {
            get { return cameraPreference; }

            // Switch to prefered FocusMode when switch CameraPreference.
            // You can set other FocusMode after this, but the tracking results may differ.
            set
            {
                cameraPreference = value;
                switch (cameraPreference)
                {
                    case CameraDevicePreference.PreferObjectSensing:
                        FocusMode = CameraDeviceFocusMode.Continousauto;
                        break;
                    case CameraDevicePreference.PreferSurfaceTracking:
                        FocusMode = CameraDeviceFocusMode.Medium;
                        break;
                    default:
                        break;
                }
            }
        }

        public CameraParameters Parameters
        {
            get
            {
                if (Device != null)
                {
                    return Device.cameraParameters();
                }
                return parameters;
            }
            set
            {
                parameters = value;
            }
        }

        protected override void OnEnable()
        {
            base.OnEnable();
            if (Device != null)
            {
                Device.start();
            }
        }

        protected override void Start()
        {
            if (!CameraDevice.isAvailable())
            {
                throw new UIPopupException(typeof(CameraDevice) + " not available");
            }

            base.Start();
        }

        protected override void OnDisable()
        {
            base.OnDisable();
            if (Device != null)
            {
                Device.stop();
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
                    throw new UIPopupException("Camera permission not granted");
                }

                Close();
                Device = CameraDeviceSelector.createCameraDevice(CameraPreference);
                if (DeviceCreated != null)
                {
                    DeviceCreated();
                }

                bool openResult = false;
                switch (CameraOpenMethod)
                {
                    case CameraDeviceOpenMethod.DeviceType:
                        openResult = Device.openWithPreferredType(CameraType);
                        break;
                    case CameraDeviceOpenMethod.DeviceIndex:
                        openResult = Device.openWithIndex(CameraIndex);
                        break;
                    default:
                        break;
                }
                if (!openResult)
                {
                    Debug.LogError("Camera open failed");
                    Device.Dispose();
                    Device = null;
                    return;
                }

                Device.setFocusMode(FocusMode);
                Device.setSize(new Vec2I((int)CameraSize.x, (int)CameraSize.y));
                if (parameters != null)
                {
                    Device.setCameraParameters(parameters);
                }
                if (bufferCapacity != 0)
                {
                    Device.setBufferCapacity(bufferCapacity);
                }

                if (sink != null)
                    Device.inputFrameSource().connect(sink);

                if (DeviceOpened != null)
                {
                    DeviceOpened();
                }

                if (enabled)
                {
                    OnEnable();
                }
            }));
        }

        public override void Close()
        {
            willOpen = false;
            if (Device != null)
            {
                OnDisable();
                Device.close();
                Device.Dispose();
                if (DeviceClosed != null)
                {
                    DeviceClosed();
                }
                Device = null;
            }
        }

        public override void Connect(InputFrameSink val)
        {
            base.Connect(val);
            if (Device != null)
            {
                Device.inputFrameSource().connect(val);
            }
        }
    }
}
