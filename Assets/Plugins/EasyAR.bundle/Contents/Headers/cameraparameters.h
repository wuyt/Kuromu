//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CAMERAPARAMETERS_H__
#define __EASYAR_CAMERAPARAMETERS_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_CameraParameters__ctor(easyar_Vec2I size, easyar_Vec2F focalLength, easyar_Vec2F principalPoint, easyar_CameraDeviceType cameraDeviceType, int cameraOrientation, /* OUT */ easyar_CameraParameters * * Return);
/// <summary>
/// Image size.
/// </summary>
easyar_Vec2I easyar_CameraParameters_size(const easyar_CameraParameters * This);
/// <summary>
/// Focal length, the distance from effective optical center to CCD plane, divided by unit pixel density in width and height directions. The unit is pixel.
/// </summary>
easyar_Vec2F easyar_CameraParameters_focalLength(const easyar_CameraParameters * This);
/// <summary>
/// Principal point, coordinates of the intersection point of principal axis on CCD plane against the left-top corner of the image. The unit is pixel.
/// </summary>
easyar_Vec2F easyar_CameraParameters_principalPoint(const easyar_CameraParameters * This);
/// <summary>
/// Camera device type. Default, back or front camera. On desktop devices, there are only default cameras. On mobile devices, there is a differentiation between back and front cameras.
/// </summary>
easyar_CameraDeviceType easyar_CameraParameters_cameraDeviceType(const easyar_CameraParameters * This);
/// <summary>
/// Camera rotation against device natural orientation.
/// For Android phones and some Android tablets, this value is 90 degrees.
/// For Android eye-wear and some Android tablets, this value is 0 degrees.
/// For all current iOS devices, this value is 90 degrees.
/// </summary>
int easyar_CameraParameters_cameraOrientation(const easyar_CameraParameters * This);
/// <summary>
/// Creates CameraParameters with default camera intrinsics. Default intrinsics are calculated by image size, which is not very precise.
/// </summary>
void easyar_CameraParameters_createWithDefaultIntrinsics(easyar_Vec2I size, easyar_CameraDeviceType cameraDeviceType, int cameraOrientation, /* OUT */ easyar_CameraParameters * * Return);
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
int easyar_CameraParameters_imageOrientation(const easyar_CameraParameters * This, int screenRotation);
/// <summary>
/// Calculates whether the image needed to be flipped horizontally. The image is rotated, then flipped in rendering. When cameraDeviceType is front, a flip is automatically applied. Pass manualHorizontalFlip with true to add a manual flip.
/// </summary>
bool easyar_CameraParameters_imageHorizontalFlip(const easyar_CameraParameters * This, bool manualHorizontalFlip);
/// <summary>
/// Calculates the perspective projection matrix needed by virtual object rendering. The projection transforms points from camera coordinate system to clip coordinate system ([-1, 1]^4). The form of perspective projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
/// </summary>
easyar_Matrix44F easyar_CameraParameters_projection(const easyar_CameraParameters * This, float nearPlane, float farPlane, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip);
/// <summary>
/// Calculates the orthogonal projection matrix needed by camera background rendering. The projection transforms points from image quad coordinate system ([-1, 1]^2) to clip coordinate system ([-1, 1]^4), with the undefined two dimensions unchanged. The form of orthogonal projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
/// </summary>
easyar_Matrix44F easyar_CameraParameters_imageProjection(const easyar_CameraParameters * This, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip);
/// <summary>
/// Transforms points from image coordinate system ([0, 1]^2) to screen coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
/// </summary>
easyar_Vec2F easyar_CameraParameters_screenCoordinatesFromImageCoordinates(const easyar_CameraParameters * This, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, easyar_Vec2F imageCoordinates);
/// <summary>
/// Transforms points from screen coordinate system ([0, 1]^2) to image coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
/// </summary>
easyar_Vec2F easyar_CameraParameters_imageCoordinatesFromScreenCoordinates(const easyar_CameraParameters * This, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, easyar_Vec2F screenCoordinates);
/// <summary>
/// Checks if two groups of parameters are equal.
/// </summary>
bool easyar_CameraParameters_equalsTo(const easyar_CameraParameters * This, easyar_CameraParameters * other);
void easyar_CameraParameters__dtor(easyar_CameraParameters * This);
void easyar_CameraParameters__retain(const easyar_CameraParameters * This, /* OUT */ easyar_CameraParameters * * Return);
const char * easyar_CameraParameters__typeName(const easyar_CameraParameters * This);

#ifdef __cplusplus
}
#endif

#endif
