//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// Buffer stores a raw byte array, which can be used to access image data.
/// To access image data in Java API, get buffer from `Image`_ and copy to a Java byte array.
/// You can always access image data since the first version of EasyAR Sense. Refer to `Image`_ .
/// </summary>
@interface easyar_Buffer : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Wraps a raw memory block. When Buffer is released by all holders, deleter callback will be invoked to execute user-defined memory destruction. deleter must be thread-safe.
/// </summary>
+ (easyar_Buffer *)wrap:(void *)ptr size:(int)size deleter:(void (^)())deleter;
/// <summary>
/// Creates a Buffer of specified byte size.
/// </summary>
+ (easyar_Buffer *)create:(int)size;
/// <summary>
/// Returns raw data address.
/// </summary>
- (void *)data;
/// <summary>
/// Byte size of raw data.
/// </summary>
- (int)size;
/// <summary>
/// Copies raw memory. It can be used in languages or platforms without complete support for memory operations.
/// </summary>
+ (void)memoryCopy:(void *)src dest:(void *)dest length:(int)length;
/// <summary>
/// Tries to copy data from a raw memory address into Buffer. If copy succeeds, it returns true, or else it returns false. Possible failure causes includes: source or destination data range overflow.
/// </summary>
- (bool)tryCopyFrom:(void *)src srcIndex:(int)srcIndex index:(int)index length:(int)length;
/// <summary>
/// Copies buffer data to user array.
/// </summary>
- (bool)tryCopyTo:(int)index dest:(void *)dest destIndex:(int)destIndex length:(int)length;
/// <summary>
/// Creates a sub-buffer with a reference to the original Buffer. A Buffer will only be released after all its sub-buffers are released.
/// </summary>
- (easyar_Buffer *)partition:(int)index length:(int)length;

@end

/// <summary>
/// A mapping from file path to `Buffer`_ . It can be used to represent multiple files in the memory.
/// </summary>
@interface easyar_BufferDictionary : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_BufferDictionary *) create;
/// <summary>
/// Current file count.
/// </summary>
- (int)count;
/// <summary>
/// Checks if a specified path is in the dictionary.
/// </summary>
- (bool)contains:(NSString *)path;
/// <summary>
/// Tries to get the corresponding `Buffer`_ for a specified path.
/// </summary>
- (easyar_Buffer *)tryGet:(NSString *)path;
/// <summary>
/// Sets `Buffer`_ for a specified path.
/// </summary>
- (void)set:(NSString *)path buffer:(easyar_Buffer *)buffer;
/// <summary>
/// Removes a specified path.
/// </summary>
- (bool)remove:(NSString *)path;
/// <summary>
/// Clears the dictionary.
/// </summary>
- (void)clear;

@end
