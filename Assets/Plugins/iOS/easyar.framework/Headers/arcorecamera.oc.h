//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// ARCoreCameraDevice implements a camera device based on ARCore, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// Loading of libarcore_sdk_c.so with java.lang.System.loadLibrary is required.
/// After creation, start/stop can be invoked to start or stop video stream capture.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARCoreCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
/// Caution: Currently, ARCore(v1.13.0) has memory leaks on creating and destroying sessions. Repeated creations and destructions will cause an increasing and non-reclaimable memory footprint.
/// </summary>
@interface easyar_ARCoreCameraDevice : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_ARCoreCameraDevice *) create;
/// <summary>
/// Checks if the component is available. It returns true only on Android when ARCore is installed.
/// If called with libarcore_sdk_c.so not loaded, it returns false.
/// Notice: If ARCore is not supported on the device but ARCore apk is installed via side-loading, it will return true, but ARCore will not function properly.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
- (int)bufferCapacity;
/// <summary>
/// Sets `InputFrame`_ buffer capacity.
/// </summary>
- (void)setBufferCapacity:(int)capacity;
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
- (easyar_InputFrameSource *)inputFrameSource;
/// <summary>
/// Starts video stream capture.
/// </summary>
- (bool)start;
/// <summary>
/// Stops video stream capture.
/// </summary>
- (void)stop;
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
- (void)close;

@end
