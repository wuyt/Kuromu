//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SURFACETRACKER_H__
#define __EASYAR_SURFACETRACKER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Camera transform against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) For the world coordinate system, y is up (to the opposite of gravity). The data arrangement is row-major, not like OpenGL&#39;s column-major.
/// </summary>
easyar_Matrix44F easyar_SurfaceTrackerResult_transform(const easyar_SurfaceTrackerResult * This);
void easyar_SurfaceTrackerResult__dtor(easyar_SurfaceTrackerResult * This);
void easyar_SurfaceTrackerResult__retain(const easyar_SurfaceTrackerResult * This, /* OUT */ easyar_SurfaceTrackerResult * * Return);
const char * easyar_SurfaceTrackerResult__typeName(const easyar_SurfaceTrackerResult * This);
void easyar_castSurfaceTrackerResultToFrameFilterResult(const easyar_SurfaceTrackerResult * This, /* OUT */ easyar_FrameFilterResult * * Return);
void easyar_tryCastFrameFilterResultToSurfaceTrackerResult(const easyar_FrameFilterResult * This, /* OUT */ easyar_SurfaceTrackerResult * * Return);

/// <summary>
/// Returns true only on Android or iOS when accelerometer and gyroscope are available.
/// </summary>
bool easyar_SurfaceTracker_isAvailable(void);
/// <summary>
/// `InputFrame`_ input port. InputFrame must have raw image, timestamp, and camera parameters.
/// </summary>
void easyar_SurfaceTracker_inputFrameSink(easyar_SurfaceTracker * This, /* OUT */ easyar_InputFrameSink * * Return);
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
int easyar_SurfaceTracker_bufferRequirement(easyar_SurfaceTracker * This);
/// <summary>
/// `OutputFrame`_ output port.
/// </summary>
void easyar_SurfaceTracker_outputFrameSource(easyar_SurfaceTracker * This, /* OUT */ easyar_OutputFrameSource * * Return);
/// <summary>
/// Creates an instance.
/// </summary>
void easyar_SurfaceTracker_create(/* OUT */ easyar_SurfaceTracker * * Return);
/// <summary>
/// Starts the track algorithm.
/// </summary>
bool easyar_SurfaceTracker_start(easyar_SurfaceTracker * This);
/// <summary>
/// Stops the track algorithm. Call start to start the track again.
/// </summary>
void easyar_SurfaceTracker_stop(easyar_SurfaceTracker * This);
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
void easyar_SurfaceTracker_close(easyar_SurfaceTracker * This);
/// <summary>
/// Sets the tracking target to a point on camera image. For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
/// </summary>
void easyar_SurfaceTracker_alignTargetToCameraImagePoint(easyar_SurfaceTracker * This, easyar_Vec2F cameraImagePoint);
void easyar_SurfaceTracker__dtor(easyar_SurfaceTracker * This);
void easyar_SurfaceTracker__retain(const easyar_SurfaceTracker * This, /* OUT */ easyar_SurfaceTracker * * Return);
const char * easyar_SurfaceTracker__typeName(const easyar_SurfaceTracker * This);

#ifdef __cplusplus
}
#endif

#endif
