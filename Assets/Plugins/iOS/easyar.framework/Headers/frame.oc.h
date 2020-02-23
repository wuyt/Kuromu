//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// Input frame.
/// It includes image, camera parameters, timestamp, camera transform matrix against world coordinate system, and tracking status,
/// among which, camera parameters, timestamp, camera transform matrix and tracking status are all optional, but specific algorithms may have special requirements on the input.
/// </summary>
@interface easyar_InputFrame : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Index, an automatic incremental value, which is different for every input frame.
/// </summary>
- (int)index;
/// <summary>
/// Gets image.
/// </summary>
- (easyar_Image *)image;
/// <summary>
/// Checks if there are camera parameters.
/// </summary>
- (bool)hasCameraParameters;
/// <summary>
/// Gets camera parameters.
/// </summary>
- (easyar_CameraParameters *)cameraParameters;
/// <summary>
/// Checks if there is temporal information (timestamp).
/// </summary>
- (bool)hasTemporalInformation;
/// <summary>
/// Timestamp.
/// </summary>
- (double)timestamp;
/// <summary>
/// Checks if there is spatial information (cameraTransform and trackingStatus).
/// </summary>
- (bool)hasSpatialInformation;
/// <summary>
/// Camera transform matrix against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL&#39;s column-major.
/// </summary>
- (easyar_Matrix44F *)cameraTransform;
/// <summary>
/// Gets device motion tracking status: `MotionTrackingStatus`_ .
/// </summary>
- (easyar_MotionTrackingStatus)trackingStatus;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFrame *)create:(easyar_Image *)image cameraParameters:(easyar_CameraParameters *)cameraParameters timestamp:(double)timestamp cameraTransform:(easyar_Matrix44F *)cameraTransform trackingStatus:(easyar_MotionTrackingStatus)trackingStatus;
/// <summary>
/// Creates an instance with image, camera parameters, and timestamp.
/// </summary>
+ (easyar_InputFrame *)createWithImageAndCameraParametersAndTemporal:(easyar_Image *)image cameraParameters:(easyar_CameraParameters *)cameraParameters timestamp:(double)timestamp;
/// <summary>
/// Creates an instance with image and camera parameters.
/// </summary>
+ (easyar_InputFrame *)createWithImageAndCameraParameters:(easyar_Image *)image cameraParameters:(easyar_CameraParameters *)cameraParameters;
/// <summary>
/// Creates an instance with image.
/// </summary>
+ (easyar_InputFrame *)createWithImage:(easyar_Image *)image;

@end

/// <summary>
/// FrameFilterResult is the base class for result classes of all synchronous algorithm components.
/// </summary>
@interface easyar_FrameFilterResult : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/// <summary>
/// Output frame.
/// It includes input frame and results of synchronous components.
/// </summary>
@interface easyar_OutputFrame : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_OutputFrame *) create:(easyar_InputFrame *)inputFrame results:(NSArray<easyar_FrameFilterResult *> *)results;
/// <summary>
/// Index, an automatic incremental value, which is different for every output frame.
/// </summary>
- (int)index;
/// <summary>
/// Corresponding input frame.
/// </summary>
- (easyar_InputFrame *)inputFrame;
/// <summary>
/// Results of synchronous components.
/// </summary>
- (NSArray<easyar_FrameFilterResult *> *)results;

@end

/// <summary>
/// Feedback frame.
/// It includes an input frame and a historic output frame for use in feedback synchronous components such as `ImageTracker`_ .
/// </summary>
@interface easyar_FeedbackFrame : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_FeedbackFrame *) create:(easyar_InputFrame *)inputFrame previousOutputFrame:(easyar_OutputFrame *)previousOutputFrame;
/// <summary>
/// Input frame.
/// </summary>
- (easyar_InputFrame *)inputFrame;
/// <summary>
/// Historic output frame.
/// </summary>
- (easyar_OutputFrame *)previousOutputFrame;

@end
