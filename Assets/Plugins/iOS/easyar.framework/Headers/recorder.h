//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_RECORDER_H__
#define __EASYAR_RECORDER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Returns true only on Android 4.3 or later, or on iOS.
/// </summary>
bool easyar_Recorder_isAvailable(void);
/// <summary>
/// Requests recording permissions from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
/// </summary>
void easyar_Recorder_requestPermissions(easyar_CallbackScheduler * callbackScheduler, easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString permissionCallback);
/// <summary>
/// Creates an instance and initialize recording. statusCallback will dispatch event of status change and corresponding log.
/// </summary>
void easyar_Recorder_create(easyar_RecorderConfiguration * config, easyar_CallbackScheduler * callbackScheduler, easyar_OptionalOfFunctorOfVoidFromRecordStatusAndString statusCallback, /* OUT */ easyar_Recorder * * Return);
/// <summary>
/// Start recording.
/// </summary>
void easyar_Recorder_start(easyar_Recorder * This);
/// <summary>
/// Update and record a frame using texture data.
/// </summary>
void easyar_Recorder_updateFrame(easyar_Recorder * This, easyar_TextureId * texture, int width, int height);
/// <summary>
/// Stop recording. When calling stop, it will wait for file write to end and returns whether recording is successful.
/// </summary>
bool easyar_Recorder_stop(easyar_Recorder * This);
void easyar_Recorder__dtor(easyar_Recorder * This);
void easyar_Recorder__retain(const easyar_Recorder * This, /* OUT */ easyar_Recorder * * Return);
const char * easyar_Recorder__typeName(const easyar_Recorder * This);

#ifdef __cplusplus
}
#endif

#endif
