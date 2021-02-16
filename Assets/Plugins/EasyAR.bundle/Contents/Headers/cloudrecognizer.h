//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CLOUDRECOGNIZER_H__
#define __EASYAR_CLOUDRECOGNIZER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Returns recognition status.
/// </summary>
easyar_CloudRecognizationStatus easyar_CloudRecognizationResult_getStatus(const easyar_CloudRecognizationResult * This);
/// <summary>
/// Returns the recognized target when status is FoundTarget.
/// </summary>
void easyar_CloudRecognizationResult_getTarget(const easyar_CloudRecognizationResult * This, /* OUT */ easyar_OptionalOfImageTarget * Return);
/// <summary>
/// Returns the error message when status is UnknownError.
/// </summary>
void easyar_CloudRecognizationResult_getUnknownErrorMessage(const easyar_CloudRecognizationResult * This, /* OUT */ easyar_OptionalOfString * Return);
void easyar_CloudRecognizationResult__dtor(easyar_CloudRecognizationResult * This);
void easyar_CloudRecognizationResult__retain(const easyar_CloudRecognizationResult * This, /* OUT */ easyar_CloudRecognizationResult * * Return);
const char * easyar_CloudRecognizationResult__typeName(const easyar_CloudRecognizationResult * This);

/// <summary>
/// Returns true.
/// </summary>
bool easyar_CloudRecognizer_isAvailable(void);
/// <summary>
/// Creates an instance and connects to the server.
/// </summary>
void easyar_CloudRecognizer_create(easyar_String * cloudRecognitionServiceServerAddress, easyar_String * apiKey, easyar_String * apiSecret, easyar_String * cloudRecognitionServiceAppId, /* OUT */ easyar_CloudRecognizer * * Return);
/// <summary>
/// Creates an instance and connects to the server with Cloud Secret.
/// </summary>
void easyar_CloudRecognizer_createByCloudSecret(easyar_String * cloudRecognitionServiceServerAddress, easyar_String * cloudRecognitionServiceSecret, easyar_String * cloudRecognitionServiceAppId, /* OUT */ easyar_CloudRecognizer * * Return);
/// <summary>
/// Send recognition request. The lowest available request interval is 300ms.
/// </summary>
void easyar_CloudRecognizer_resolve(easyar_CloudRecognizer * This, easyar_InputFrame * inputFrame, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromCloudRecognizationResult callback);
/// <summary>
/// Stops the recognition and closes connection. The component shall not be used after calling close.
/// </summary>
void easyar_CloudRecognizer_close(easyar_CloudRecognizer * This);
void easyar_CloudRecognizer__dtor(easyar_CloudRecognizer * This);
void easyar_CloudRecognizer__retain(const easyar_CloudRecognizer * This, /* OUT */ easyar_CloudRecognizer * * Return);
const char * easyar_CloudRecognizer__typeName(const easyar_CloudRecognizer * This);

#ifdef __cplusplus
}
#endif

#endif
