//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"
#import "easyar/frame.oc.h"

/// <summary>
/// Result of `SurfaceTracker`_ .
/// </summary>
@interface easyar_SurfaceTrackerResult : easyar_FrameFilterResult

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Camera transform against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) For the world coordinate system, y is up (to the opposite of gravity). The data arrangement is row-major, not like OpenGL&#39;s column-major.
/// </summary>
- (easyar_Matrix44F *)transform;

@end

/// <summary>
/// SurfaceTracker implements tracking with environmental surfaces.
/// SurfaceTracker occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// SurfaceTracker inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
@interface easyar_SurfaceTracker : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns true only on Android or iOS when accelerometer and gyroscope are available.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// `InputFrame`_ input port. InputFrame must have raw image, timestamp, and camera parameters.
/// </summary>
- (easyar_InputFrameSink *)inputFrameSink;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// `OutputFrame`_ output port.
/// </summary>
- (easyar_OutputFrameSource *)outputFrameSource;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_SurfaceTracker *)create;
/// <summary>
/// Starts the track algorithm.
/// </summary>
- (bool)start;
/// <summary>
/// Stops the track algorithm. Call start to start the track again.
/// </summary>
- (void)stop;
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
- (void)close;
/// <summary>
/// Sets the tracking target to a point on camera image. For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
/// </summary>
- (void)alignTargetToCameraImagePoint:(easyar_Vec2F *)cameraImagePoint;

@end
