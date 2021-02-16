//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_JNIUTILITY_H__
#define __EASYAR_JNIUTILITY_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Wraps Java&#39;s byte[]。
/// </summary>
void easyar_JniUtility_wrapByteArray(void * bytes, bool readOnly, easyar_FunctorOfVoid deleter, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Wraps Java&#39;s java.nio.ByteBuffer, which must be a direct buffer.
/// </summary>
void easyar_JniUtility_wrapBuffer(void * directBuffer, easyar_FunctorOfVoid deleter, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Get the raw address of a direct buffer of java.nio.ByteBuffer by calling JNIEnv-&gt;GetDirectBufferAddress.
/// </summary>
void * easyar_JniUtility_getDirectBufferAddress(void * directBuffer);

#ifdef __cplusplus
}
#endif

#endif
