//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGEHELPER_H__
#define __EASYAR_IMAGEHELPER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Decodes a JPEG or PNG file.
/// </summary>
void easyar_ImageHelper_decode(easyar_Buffer * buffer, /* OUT */ easyar_OptionalOfImage * Return);

#ifdef __cplusplus
}
#endif

#endif
