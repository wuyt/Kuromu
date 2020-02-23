//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TEXTURE_H__
#define __EASYAR_TEXTURE_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Gets ID of an OpenGL/OpenGLES texture object.
/// </summary>
int easyar_TextureId_getInt(easyar_TextureId * This);
/// <summary>
/// Gets pointer of a Direct3D texture object.
/// </summary>
void * easyar_TextureId_getPointer(easyar_TextureId * This);
/// <summary>
/// Creates from ID of an OpenGL/OpenGLES texture object.
/// </summary>
void easyar_TextureId_fromInt(int _value, /* OUT */ easyar_TextureId * * Return);
/// <summary>
/// Creates from pointer of a Direct3D texture object.
/// </summary>
void easyar_TextureId_fromPointer(void * ptr, /* OUT */ easyar_TextureId * * Return);
void easyar_TextureId__dtor(easyar_TextureId * This);
void easyar_TextureId__retain(const easyar_TextureId * This, /* OUT */ easyar_TextureId * * Return);
const char * easyar_TextureId__typeName(const easyar_TextureId * This);

#ifdef __cplusplus
}
#endif

#endif
