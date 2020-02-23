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
/// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation.
/// </summary>
@interface easyar_CameraParameters : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_CameraParameters *) create:(easyar_Vec2I *)size focalLength:(easyar_Vec2F *)focalLength principalPoint:(easyar_Vec2F *)principalPoint cameraDeviceType:(easyar_CameraDeviceType)cameraDeviceType cameraOrientation:(int)cameraOrientation;
/// <summary>
/// Image size.
/// </summary>
- (easyar_Vec2I *)size;
/// <summary>
/// Focal length, the distance from effective optical center to CCD plane, divided by unit pixel density in width and height directions. The unit is pixel.
/// </summary>
- (easyar_Vec2F *)focalLength;
/// <summary>
/// Principal point, coordinates of the intersection point of principal axis on CCD plane against the left-top corner of the image. The unit is pixel.
/// </summary>
- (easyar_Vec2F *)principalPoint;
/// <summary>
/// Camera device type. Default, back or front camera. On desktop devices, there are only default cameras. On mobile devices, there is a differentiation between back and front cameras.
/// </summary>
- (easyar_CameraDeviceType)cameraDeviceType;
/// <summary>
/// Camera rotation against device natural orientation.
/// For Android phones and some Android tablets, this value is 90 degrees.
/// For Android eye-wear and some Android tablets, this value is 0 degrees.
/// For all current iOS devices, this value is 90 degrees.
/// </summary>
- (int)cameraOrientation;
/// <summary>
/// Creates CameraParameters with default camera intrinsics. Default intrinsics are calculated by image size, which is not very precise.
/// </summary>
+ (easyar_CameraParameters *)createWithDefaultIntrinsics:(easyar_Vec2I *)size cameraDeviceType:(easyar_CameraDeviceType)cameraDeviceType cameraOrientation:(int)cameraOrientation;
/// <summary>
/// Calculates the angle required to rotate the camera image clockwise to align it with the screen.
/// screenRotation is the angle of rotation of displaying screen image against device natural orientation in clockwise in degrees.
/// For iOS(UIInterfaceOrientationPortrait as natural orientation):
/// * UIInterfaceOrientationPortrait: rotation = 0
/// * UIInterfaceOrientationLandscapeRight: rotation = 90
/// * UIInterfaceOrientationPortraitUpsideDown: rotation = 180
/// * UIInterfaceOrientationLandscapeLeft: rotation = 270
/// For Android:
/// * Surface.ROTATION_0 = 0
/// * Surface.ROTATION_90 = 90
/// * Surface.ROTATION_180 = 180
/// * Surface.ROTATION_270 = 270
/// </summary>
- (int)imageOrientation:(int)screenRotation;
/// <summary>
/// Calculates whether the image needed to be flipped horizontally. The image is rotated, then flipped in rendering. When cameraDeviceType is front, a flip is automatically applied. Pass manualHorizontalFlip with true to add a manual flip.
/// </summary>
- (bool)imageHorizontalFlip:(bool)manualHorizontalFlip;
/// <summary>
/// Calculates the perspective projection matrix needed by virtual object rendering. The projection transforms points from camera coordinate system to clip coordinate system ([-1, 1]^4). The form of perspective projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
/// </summary>
- (easyar_Matrix44F *)projection:(float)nearPlane farPlane:(float)farPlane viewportAspectRatio:(float)viewportAspectRatio screenRotation:(int)screenRotation combiningFlip:(bool)combiningFlip manualHorizontalFlip:(bool)manualHorizontalFlip;
/// <summary>
/// Calculates the orthogonal projection matrix needed by camera background rendering. The projection transforms points from image quad coordinate system ([-1, 1]^2) to clip coordinate system ([-1, 1]^4), with the undefined two dimensions unchanged. The form of orthogonal projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
/// </summary>
- (easyar_Matrix44F *)imageProjection:(float)viewportAspectRatio screenRotation:(int)screenRotation combiningFlip:(bool)combiningFlip manualHorizontalFlip:(bool)manualHorizontalFlip;
/// <summary>
/// Transforms points from image coordinate system ([0, 1]^2) to screen coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
/// </summary>
- (easyar_Vec2F *)screenCoordinatesFromImageCoordinates:(float)viewportAspectRatio screenRotation:(int)screenRotation combiningFlip:(bool)combiningFlip manualHorizontalFlip:(bool)manualHorizontalFlip imageCoordinates:(easyar_Vec2F *)imageCoordinates;
/// <summary>
/// Transforms points from screen coordinate system ([0, 1]^2) to image coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
/// </summary>
- (easyar_Vec2F *)imageCoordinatesFromScreenCoordinates:(float)viewportAspectRatio screenRotation:(int)screenRotation combiningFlip:(bool)combiningFlip manualHorizontalFlip:(bool)manualHorizontalFlip screenCoordinates:(easyar_Vec2F *)screenCoordinates;
/// <summary>
/// Checks if two groups of parameters are equal.
/// </summary>
- (bool)equalsTo:(easyar_CameraParameters *)other;

@end
