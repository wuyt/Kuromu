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
/// Target is the base class for all targets that can be tracked by `ImageTracker`_ or other algorithms inside EasyAR.
/// </summary>
@interface easyar_Target : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
/// </summary>
- (int)runtimeID;
/// <summary>
/// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
/// </summary>
- (NSString *)uid;
/// <summary>
/// Returns the target name. Name is used to distinguish targets in a json file.
/// </summary>
- (NSString *)name;
/// <summary>
/// Set name. It will erase previously set data or data from cloud.
/// </summary>
- (void)setName:(NSString *)name;
/// <summary>
/// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
/// </summary>
- (NSString *)meta;
/// <summary>
/// Set meta data. It will erase previously set data or data from cloud.
/// </summary>
- (void)setMeta:(NSString *)data;

@end

/// <summary>
/// TargetInstance is the tracked target by trackers.
/// An TargetInstance contains a raw `Target`_ that is tracked and current status and pose of the `Target`_ .
/// </summary>
@interface easyar_TargetInstance : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_TargetInstance *) create;
/// <summary>
/// Returns current status of the tracked target. Usually you can check if the status equals `TargetStatus.Tracked` to determine current status of the target.
/// </summary>
- (easyar_TargetStatus)status;
/// <summary>
/// Gets the raw target. It will return the same `Target`_ you loaded into a tracker if it was previously loaded into the tracker.
/// </summary>
- (easyar_Target *)target;
/// <summary>
/// Returns current pose of the tracked target. Camera coordinate system and target coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL&#39;s column-major.
/// </summary>
- (easyar_Matrix44F *)pose;

@end

/// <summary>
/// TargetTrackerResult is the base class of `ImageTrackerResult`_ and `ObjectTrackerResult`_ .
/// </summary>
@interface easyar_TargetTrackerResult : easyar_FrameFilterResult

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns the list of `TargetInstance`_ contained in the result.
/// </summary>
- (NSArray<easyar_TargetInstance *> *)targetInstances;
/// <summary>
/// Sets the list of `TargetInstance`_ contained in the result.
/// </summary>
- (void)setTargetInstances:(NSArray<easyar_TargetInstance *> *)instances;

@end
