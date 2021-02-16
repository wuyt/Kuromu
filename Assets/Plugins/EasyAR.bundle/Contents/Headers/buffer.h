//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_BUFFER_H__
#define __EASYAR_BUFFER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Wraps a raw memory block. When Buffer is released by all holders, deleter callback will be invoked to execute user-defined memory destruction. deleter must be thread-safe.
/// </summary>
void easyar_Buffer_wrap(void * ptr, int size, easyar_FunctorOfVoid deleter, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Creates a Buffer of specified byte size.
/// </summary>
void easyar_Buffer_create(int size, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Returns raw data address.
/// </summary>
void * easyar_Buffer_data(const easyar_Buffer * This);
/// <summary>
/// Byte size of raw data.
/// </summary>
int easyar_Buffer_size(const easyar_Buffer * This);
/// <summary>
/// Copies raw memory. It can be used in languages or platforms without complete support for memory operations.
/// </summary>
void easyar_Buffer_memoryCopy(void * src, void * dest, int length);
/// <summary>
/// Tries to copy data from a raw memory address into Buffer. If copy succeeds, it returns true, or else it returns false. Possible failure causes includes: source or destination data range overflow.
/// </summary>
bool easyar_Buffer_tryCopyFrom(easyar_Buffer * This, void * src, int srcIndex, int index, int length);
/// <summary>
/// Copies buffer data to user array.
/// </summary>
bool easyar_Buffer_tryCopyTo(easyar_Buffer * This, int index, void * dest, int destIndex, int length);
/// <summary>
/// Creates a sub-buffer with a reference to the original Buffer. A Buffer will only be released after all its sub-buffers are released.
/// </summary>
void easyar_Buffer_partition(easyar_Buffer * This, int index, int length, /* OUT */ easyar_Buffer * * Return);
void easyar_Buffer__dtor(easyar_Buffer * This);
void easyar_Buffer__retain(const easyar_Buffer * This, /* OUT */ easyar_Buffer * * Return);
const char * easyar_Buffer__typeName(const easyar_Buffer * This);

void easyar_BufferDictionary__ctor(/* OUT */ easyar_BufferDictionary * * Return);
/// <summary>
/// Current file count.
/// </summary>
int easyar_BufferDictionary_count(const easyar_BufferDictionary * This);
/// <summary>
/// Checks if a specified path is in the dictionary.
/// </summary>
bool easyar_BufferDictionary_contains(const easyar_BufferDictionary * This, easyar_String * path);
/// <summary>
/// Tries to get the corresponding `Buffer`_ for a specified path.
/// </summary>
void easyar_BufferDictionary_tryGet(const easyar_BufferDictionary * This, easyar_String * path, /* OUT */ easyar_OptionalOfBuffer * Return);
/// <summary>
/// Sets `Buffer`_ for a specified path.
/// </summary>
void easyar_BufferDictionary_set(easyar_BufferDictionary * This, easyar_String * path, easyar_Buffer * buffer);
/// <summary>
/// Removes a specified path.
/// </summary>
bool easyar_BufferDictionary_remove(easyar_BufferDictionary * This, easyar_String * path);
/// <summary>
/// Clears the dictionary.
/// </summary>
void easyar_BufferDictionary_clear(easyar_BufferDictionary * This);
void easyar_BufferDictionary__dtor(easyar_BufferDictionary * This);
void easyar_BufferDictionary__retain(const easyar_BufferDictionary * This, /* OUT */ easyar_BufferDictionary * * Return);
const char * easyar_BufferDictionary__typeName(const easyar_BufferDictionary * This);

#ifdef __cplusplus
}
#endif

#endif
