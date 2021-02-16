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
/// MotionTrackerCameraDevice implements a camera device with metric-scale six degree-of-freedom motion tracking, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF pose and tracking status).
/// After creation, start/stop can be invoked to start or stop data flow.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// MotionTrackerCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for further use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
@interface easyar_MotionTrackerCameraDevice : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Create MotionTrackerCameraDevice object.
/// </summary>
+ (easyar_MotionTrackerCameraDevice *) create;
/// <summary>
/// Check if the devices supports motion tracking. Returns True if the device supports Motion Tracking, otherwise returns False.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Set `InputFrame`_ buffer capacity.
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is higher than this number, the device will not output new `InputFrame`_ until previous `InputFrame`_ has been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
- (void)setBufferCapacity:(int)capacity;
/// <summary>
/// Get `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
- (int)bufferCapacity;
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
- (easyar_InputFrameSource *)inputFrameSource;
/// <summary>
/// Start motion tracking or resume motion tracking after pause.
/// Notice: Calling start after pausing will trigger device relocalization. Tracking will resume when the relocalization process succeeds.
/// </summary>
- (bool)start;
/// <summary>
/// Pause motion tracking. Call `start` to trigger relocation, resume motion tracking if the relocation succeeds.
/// </summary>
- (void)stop;
/// <summary>
/// Close motion tracking. The component shall not be used after calling close.
/// </summary>
- (void)close;
/// <summary>
/// Perform hit test against the point cloud and return the nearest 3D point. The 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
/// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
/// </summary>
- (NSArray<easyar_Vec3F *> *)hitTestAgainstPointCloud:(easyar_Vec2F *)cameraImagePoint;
/// <summary>
/// Performs ray cast from the user&#39;s device in the direction of given screen point.
/// Intersections with horizontal plane is detected in real time in the current field of view,and return the 3D point nearest to ray on horizontal plane.
/// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
/// The output point cloud coordinate on Horizontal plane is in the world coordinate system. The 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
/// </summary>
- (NSArray<easyar_Vec3F *> *)hitTestAgainstHorizontalPlane:(easyar_Vec2F *)cameraImagePoint;
/// <summary>
/// Returns the vector of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
/// </summary>
- (NSArray<easyar_Vec3F *> *)getLocalPointsCloud;

@end
