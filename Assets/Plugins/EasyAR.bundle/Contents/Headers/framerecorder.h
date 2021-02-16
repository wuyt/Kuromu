//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_FRAMERECORDER_H__
#define __EASYAR_FRAMERECORDER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Input port.
/// </summary>
void easyar_InputFrameRecorder_input(easyar_InputFrameRecorder * This, /* OUT */ easyar_InputFrameSink * * Return);
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
int easyar_InputFrameRecorder_bufferRequirement(easyar_InputFrameRecorder * This);
/// <summary>
/// Output port.
/// </summary>
void easyar_InputFrameRecorder_output(easyar_InputFrameRecorder * This, /* OUT */ easyar_InputFrameSource * * Return);
/// <summary>
/// Creates an instance.
/// </summary>
void easyar_InputFrameRecorder_create(/* OUT */ easyar_InputFrameRecorder * * Return);
/// <summary>
/// Starts frame recording.
/// </summary>
bool easyar_InputFrameRecorder_start(easyar_InputFrameRecorder * This, easyar_String * filePath);
/// <summary>
/// Stops frame recording. It will only stop recording and will not affect connection.
/// </summary>
void easyar_InputFrameRecorder_stop(easyar_InputFrameRecorder * This);
void easyar_InputFrameRecorder__dtor(easyar_InputFrameRecorder * This);
void easyar_InputFrameRecorder__retain(const easyar_InputFrameRecorder * This, /* OUT */ easyar_InputFrameRecorder * * Return);
const char * easyar_InputFrameRecorder__typeName(const easyar_InputFrameRecorder * This);

/// <summary>
/// Output port.
/// </summary>
void easyar_InputFramePlayer_output(easyar_InputFramePlayer * This, /* OUT */ easyar_InputFrameSource * * Return);
/// <summary>
/// Creates an instance.
/// </summary>
void easyar_InputFramePlayer_create(/* OUT */ easyar_InputFramePlayer * * Return);
/// <summary>
/// Starts frame play.
/// </summary>
bool easyar_InputFramePlayer_start(easyar_InputFramePlayer * This, easyar_String * filePath);
/// <summary>
/// Stops frame play.
/// </summary>
void easyar_InputFramePlayer_stop(easyar_InputFramePlayer * This);
void easyar_InputFramePlayer__dtor(easyar_InputFramePlayer * This);
void easyar_InputFramePlayer__retain(const easyar_InputFramePlayer * This, /* OUT */ easyar_InputFramePlayer * * Return);
const char * easyar_InputFramePlayer__typeName(const easyar_InputFramePlayer * This);

#ifdef __cplusplus
}
#endif

#endif
