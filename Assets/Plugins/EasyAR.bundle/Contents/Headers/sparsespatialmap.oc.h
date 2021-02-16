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
/// Describes the result of mapping and localization. Updated at the same frame rate with OutputFrame.
/// </summary>
@interface easyar_SparseSpatialMapResult : easyar_FrameFilterResult

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Obtain motion tracking status.
/// </summary>
- (easyar_MotionTrackingStatus)getMotionTrackingStatus;
/// <summary>
/// Returns pose of the origin of VIO system in camera coordinate system.
/// </summary>
- (easyar_Matrix44F *)getVioPose;
/// <summary>
/// Returns the pose of origin of the map in camera coordinate system, when localization is successful.
/// Otherwise, returns pose of the origin of VIO system in camera coordinate system.
/// </summary>
- (easyar_Matrix44F *)getMapPose;
/// <summary>
/// Returns true if the system can reliablly locate the pose of the device with regard to the map.
/// Once relocalization succeeds, relative pose can be updated by motion tracking module.
/// As long as the motion tracking module returns normal tracking status, the localization status is also true.
/// </summary>
- (bool)getLocalizationStatus;
/// <summary>
/// Returns current localized map ID.
/// </summary>
- (NSString *)getLocalizationMapID;

@end

@interface easyar_PlaneData : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Constructor
/// </summary>
+ (easyar_PlaneData *) create;
/// <summary>
/// Returns the type of this plane.
/// </summary>
- (easyar_PlaneType)getType;
/// <summary>
/// Returns the pose of the center of the detected plane.The pose&#39;s transformed +Y axis will be point normal out of the plane, with the +X and +Z axes orienting the extents of the bounding rectangle.
/// </summary>
- (easyar_Matrix44F *)getPose;
/// <summary>
/// Returns the length of this plane&#39;s bounding rectangle measured along the local X-axis of the coordinate space centered on the plane.
/// </summary>
- (float)getExtentX;
/// <summary>
/// Returns the length of this plane&#39;s bounding rectangle measured along the local Z-axis of the coordinate frame centered on the plane.
/// </summary>
- (float)getExtentZ;

@end

/// <summary>
/// Configuration used to set the localization mode.
/// </summary>
@interface easyar_SparseSpatialMapConfig : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Constructor
/// </summary>
+ (easyar_SparseSpatialMapConfig *) create;
/// <summary>
/// Sets localization configurations. See also `LocalizationMode`_.
/// </summary>
- (void)setLocalizationMode:(easyar_LocalizationMode)_value;
/// <summary>
/// Returns localization configurations. See also `LocalizationMode`_.
/// </summary>
- (easyar_LocalizationMode)getLocalizationMode;

@end

/// <summary>
/// Provides core components for SparseSpatialMap, can be used for sparse spatial map building as well as localization using existing map. Also provides utilities for point cloud and plane access.
/// SparseSpatialMap occupies 2 buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
@interface easyar_SparseSpatialMap : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Check whether SparseSpatialMap is is available, always return true.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Input port for input frame. For SparseSpatialMap to work, the inputFrame must include camera parameters, timestamp and spatial information. See also `InputFrameSink`_
/// </summary>
- (easyar_InputFrameSink *)inputFrameSink;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Output port for output frame. See also `OutputFrameSource`_
/// </summary>
- (easyar_OutputFrameSource *)outputFrameSource;
/// <summary>
/// Construct SparseSpatialMap.
/// </summary>
+ (easyar_SparseSpatialMap *)create;
/// <summary>
/// Start SparseSpatialMap system.
/// </summary>
- (bool)start;
/// <summary>
/// Stop SparseSpatialMap from running。Can resume running by calling start().
/// </summary>
- (void)stop;
/// <summary>
/// Close SparseSpatialMap. SparseSpatialMap can no longer be used.
/// </summary>
- (void)close;
/// <summary>
/// Returns the buffer of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space, each of which takes 4 bytes.
/// </summary>
- (easyar_Buffer *)getPointCloudBuffer;
/// <summary>
/// Returns detected planes in SparseSpatialMap.
/// </summary>
- (NSArray<easyar_PlaneData *> *)getMapPlanes;
/// <summary>
/// Perform hit test against the point cloud. The results are returned sorted by their distance to the camera in ascending order.
/// </summary>
- (NSArray<easyar_Vec3F *> *)hitTestAgainstPointCloud:(easyar_Vec2F *)cameraImagePoint;
/// <summary>
/// Performs ray cast from the user&#39;s device in the direction of given screen point.
/// Intersections with detected planes are returned. 3D positions on physical planes are sorted by distance from the device in ascending order.
/// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
/// The output point cloud coordinate is in the world coordinate system.
/// </summary>
- (NSArray<easyar_Vec3F *> *)hitTestAgainstPlanes:(easyar_Vec2F *)cameraImagePoint;
/// <summary>
/// Get the map data version of the current SparseSpatialMap.
/// </summary>
+ (NSString *)getMapVersion;
/// <summary>
/// UnloadMap specified SparseSpatialMap data via callback function.The return value of callback indicates whether unload map succeeds (true) or fails (false).
/// </summary>
- (void)unloadMap:(NSString *)mapID callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler resultCallBack:(void (^)(bool))resultCallBack;
/// <summary>
/// Set configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
/// </summary>
- (void)setConfig:(easyar_SparseSpatialMapConfig *)config;
/// <summary>
/// Returns configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
/// </summary>
- (easyar_SparseSpatialMapConfig *)getConfig;
/// <summary>
/// Start localization in loaded maps. Should set `LocalizationMode`_ first.
/// </summary>
- (bool)startLocalization;
/// <summary>
/// Stop localization in loaded maps.
/// </summary>
- (void)stopLocalization;

@end
