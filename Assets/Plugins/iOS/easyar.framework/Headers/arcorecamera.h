//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_ARCORECAMERA_H__
#define __EASYAR_ARCORECAMERA_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_ARCoreCameraDevice__ctor(/* OUT */ easyar_ARCoreCameraDevice * * Return);
/// <summary>
/// Checks if the component is available. It returns true only on Android when ARCore is installed.
/// If called with libarcore_sdk_c.so not loaded, it returns false.
/// Notice: If ARCore is not supported on the device but ARCore apk is installed via side-loading, it will return true, but ARCore will not function properly.
/// </summary>
bool easyar_ARCoreCameraDevice_isAvailable(void);
/// <summary>
/// `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
int easyar_ARCoreCameraDevice_bufferCapacity(const easyar_ARCoreCameraDevice * This);
/// <summary>
/// Sets `InputFrame`_ buffer capacity.
/// </summary>
void easyar_ARCoreCameraDevice_setBufferCapacity(easyar_ARCoreCameraDevice * This, int capacity);
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
void easyar_ARCoreCameraDevice_inputFrameSource(easyar_ARCoreCameraDevice * This, /* OUT */ easyar_InputFrameSource * * Return);
/// <summary>
/// Starts video stream capture.
/// </summary>
bool easyar_ARCoreCameraDevice_start(easyar_ARCoreCameraDevice * This);
/// <summary>
/// Stops video stream capture.
/// </summary>
void easyar_ARCoreCameraDevice_stop(easyar_ARCoreCameraDevice * This);
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
void easyar_ARCoreCameraDevice_close(easyar_ARCoreCameraDevice * This);
void easyar_ARCoreCameraDevice__dtor(easyar_ARCoreCameraDevice * This);
void easyar_ARCoreCameraDevice__retain(const easyar_ARCoreCameraDevice * This, /* OUT */ easyar_ARCoreCameraDevice * * Return);
const char * easyar_ARCoreCameraDevice__typeName(const easyar_ARCoreCameraDevice * This);

#ifdef __cplusplus
}
#endif

#endif
