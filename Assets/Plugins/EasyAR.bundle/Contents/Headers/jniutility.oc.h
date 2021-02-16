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
/// JNI utility class.
/// It is used in Unity to wrap Java byte array and ByteBuffer.
/// It is not supported on iOS.
/// </summary>
@interface easyar_JniUtility : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Wraps Java&#39;s byte[]。
/// </summary>
+ (easyar_Buffer *)wrapByteArray:(void *)bytes readOnly:(bool)readOnly deleter:(void (^)())deleter;
/// <summary>
/// Wraps Java&#39;s java.nio.ByteBuffer, which must be a direct buffer.
/// </summary>
+ (easyar_Buffer *)wrapBuffer:(void *)directBuffer deleter:(void (^)())deleter;
/// <summary>
/// Get the raw address of a direct buffer of java.nio.ByteBuffer by calling JNIEnv-&gt;GetDirectBufferAddress.
/// </summary>
+ (void *)getDirectBufferAddress:(void *)directBuffer;

@end
