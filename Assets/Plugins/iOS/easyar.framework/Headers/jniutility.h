//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
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

#ifdef __cplusplus
}
#endif

#endif
