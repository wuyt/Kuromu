//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_MOTIONTRACKER_H__
#define __EASYAR_MOTIONTRACKER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Create MotionTrackerCameraDevice object.
/// </summary>
void easyar_MotionTrackerCameraDevice__ctor(/* OUT */ easyar_MotionTrackerCameraDevice * * Return);
/// <summary>
/// Check if the devices supports motion tracking. Returns True if the device supports Motion Tracking, otherwise returns False.
/// </summary>
bool easyar_MotionTrackerCameraDevice_isAvailable(void);
/// <summary>
/// Set `InputFrame`_ buffer capacity.
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is higher than this number, the device will not output new `InputFrame`_ until previous `InputFrame`_ has been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
void easyar_MotionTrackerCameraDevice_setBufferCapacity(easyar_MotionTrackerCameraDevice * This, int capacity);
/// <summary>
/// Get `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
int easyar_MotionTrackerCameraDevice_bufferCapacity(const easyar_MotionTrackerCameraDevice * This);
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
void easyar_MotionTrackerCameraDevice_inputFrameSource(easyar_MotionTrackerCameraDevice * This, /* OUT */ easyar_InputFrameSource * * Return);
/// <summary>
/// Start motion tracking or resume motion tracking after pause.
/// Notice: Calling start after pausing will trigger device relocalization. Tracking will resume when the relocalization process succeeds.
/// </summary>
bool easyar_MotionTrackerCameraDevice_start(easyar_MotionTrackerCameraDevice * This);
/// <summary>
/// Pause motion tracking. Call `start` to trigger relocation, resume motion tracking if the relocation succeeds.
/// </summary>
void easyar_MotionTrackerCameraDevice_stop(easyar_MotionTrackerCameraDevice * This);
/// <summary>
/// Close motion tracking. The component shall not be used after calling close.
/// </summary>
void easyar_MotionTrackerCameraDevice_close(easyar_MotionTrackerCameraDevice * This);
void easyar_MotionTrackerCameraDevice__dtor(easyar_MotionTrackerCameraDevice * This);
void easyar_MotionTrackerCameraDevice__retain(const easyar_MotionTrackerCameraDevice * This, /* OUT */ easyar_MotionTrackerCameraDevice * * Return);
const char * easyar_MotionTrackerCameraDevice__typeName(const easyar_MotionTrackerCameraDevice * This);

#ifdef __cplusplus
}
#endif

#endif
