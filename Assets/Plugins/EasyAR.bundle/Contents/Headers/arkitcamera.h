//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_ARKITCAMERA_H__
#define __EASYAR_ARKITCAMERA_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_ARKitCameraDevice__ctor(/* OUT */ easyar_ARKitCameraDevice * * Return);
/// <summary>
/// Checks if the component is available. It returns true only on iOS 11 or later when ARKit is supported by hardware.
/// </summary>
bool easyar_ARKitCameraDevice_isAvailable(void);
/// <summary>
/// `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
int easyar_ARKitCameraDevice_bufferCapacity(const easyar_ARKitCameraDevice * This);
/// <summary>
/// Sets `InputFrame`_ buffer capacity.
/// </summary>
void easyar_ARKitCameraDevice_setBufferCapacity(easyar_ARKitCameraDevice * This, int capacity);
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
void easyar_ARKitCameraDevice_inputFrameSource(easyar_ARKitCameraDevice * This, /* OUT */ easyar_InputFrameSource * * Return);
/// <summary>
/// Starts video stream capture.
/// </summary>
bool easyar_ARKitCameraDevice_start(easyar_ARKitCameraDevice * This);
/// <summary>
/// Stops video stream capture.
/// </summary>
void easyar_ARKitCameraDevice_stop(easyar_ARKitCameraDevice * This);
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
void easyar_ARKitCameraDevice_close(easyar_ARKitCameraDevice * This);
void easyar_ARKitCameraDevice__dtor(easyar_ARKitCameraDevice * This);
void easyar_ARKitCameraDevice__retain(const easyar_ARKitCameraDevice * This, /* OUT */ easyar_ARKitCameraDevice * * Return);
const char * easyar_ARKitCameraDevice__typeName(const easyar_ARKitCameraDevice * This);

#ifdef __cplusplus
}
#endif

#endif
