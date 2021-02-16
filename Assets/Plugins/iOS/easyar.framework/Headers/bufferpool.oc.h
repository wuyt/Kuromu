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
/// BufferPool is a memory pool to reduce memory allocation time consumption for functionality like custom camera interoperability, which needs to allocate memory buffers of a fixed size repeatedly.
/// </summary>
@interface easyar_BufferPool : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// block_size is the byte size of each `Buffer`_ .
/// capacity is the maximum count of `Buffer`_ .
/// </summary>
+ (easyar_BufferPool *) create:(int)block_size capacity:(int)capacity;
/// <summary>
/// The byte size of each `Buffer`_ .
/// </summary>
- (int)block_size;
/// <summary>
/// The maximum count of `Buffer`_ .
/// </summary>
- (int)capacity;
/// <summary>
/// Current acquired count of `Buffer`_ .
/// </summary>
- (int)size;
/// <summary>
/// Tries to acquire a memory block. If current acquired count of `Buffer`_ does not reach maximum, a new `Buffer`_ is fetched or allocated, or else null is returned.
/// </summary>
- (easyar_Buffer *)tryAcquire;

@end
