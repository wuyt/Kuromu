//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// TextureId encapsulates a texture object in rendering API.
/// For OpenGL/OpenGLES, getInt and fromInt shall be used. For Direct3D, getPointer and fromPointer shall be used.
/// </summary>
@interface easyar_TextureId : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Gets ID of an OpenGL/OpenGLES texture object.
/// </summary>
- (int)getInt;
/// <summary>
/// Gets pointer of a Direct3D texture object.
/// </summary>
- (void *)getPointer;
/// <summary>
/// Creates from ID of an OpenGL/OpenGLES texture object.
/// </summary>
+ (easyar_TextureId *)fromInt:(int)_value;
/// <summary>
/// Creates from pointer of a Direct3D texture object.
/// </summary>
+ (easyar_TextureId *)fromPointer:(void *)ptr;

@end
