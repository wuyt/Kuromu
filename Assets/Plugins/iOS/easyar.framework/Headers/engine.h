//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_ENGINE_H__
#define __EASYAR_ENGINE_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Gets the version schema hash, which can be used to ensure type declarations consistent with runtime library.
/// </summary>
int easyar_Engine_schemaHash(void);
bool easyar_Engine_initialize(easyar_String * key);
/// <summary>
/// Handles the app onPause, pauses internal tasks.
/// </summary>
void easyar_Engine_onPause(void);
/// <summary>
/// Handles the app onResume, resumes internal tasks.
/// </summary>
void easyar_Engine_onResume(void);
/// <summary>
/// Gets error message on initialization failure.
/// </summary>
void easyar_Engine_errorMessage(/* OUT */ easyar_String * * Return);
/// <summary>
/// Gets the version number of EasyARSense.
/// </summary>
void easyar_Engine_versionString(/* OUT */ easyar_String * * Return);
/// <summary>
/// Gets the product name of EasyARSense. (Including variant, operating system and CPU architecture.)
/// </summary>
void easyar_Engine_name(/* OUT */ easyar_String * * Return);

#ifdef __cplusplus
}
#endif

#endif
