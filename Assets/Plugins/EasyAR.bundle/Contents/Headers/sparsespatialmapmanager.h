//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SPARSESPATIALMAPMANAGER_H__
#define __EASYAR_SPARSESPATIALMAPMANAGER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Check whether SparseSpatialMapManager is is available. It returns true when the operating system is Windows, Mac, iOS or Android.
/// </summary>
bool easyar_SparseSpatialMapManager_isAvailable(void);
/// <summary>
/// Creates an instance.
/// </summary>
void easyar_SparseSpatialMapManager_create(/* OUT */ easyar_SparseSpatialMapManager * * Return);
/// <summary>
/// Creates a map from `SparseSpatialMap`_ and upload it to EasyAR cloud servers. After completion, a serverMapId will be returned for loading map from EasyAR cloud servers.
/// </summary>
void easyar_SparseSpatialMapManager_host(easyar_SparseSpatialMapManager * This, easyar_SparseSpatialMap * mapBuilder, easyar_String * apiKey, easyar_String * apiSecret, easyar_String * sparseSpatialMapAppId, easyar_String * name, easyar_OptionalOfImage preview, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromBoolAndStringAndString onCompleted);
/// <summary>
/// Loads a map from EasyAR cloud servers by serverMapId. To unload the map, call `SparseSpatialMap.unloadMap`_ with serverMapId.
/// </summary>
void easyar_SparseSpatialMapManager_load(easyar_SparseSpatialMapManager * This, easyar_SparseSpatialMap * mapTracker, easyar_String * serverMapId, easyar_String * apiKey, easyar_String * apiSecret, easyar_String * sparseSpatialMapAppId, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromBoolAndString onCompleted);
/// <summary>
/// Clears allocated cache space.
/// </summary>
void easyar_SparseSpatialMapManager_clear(easyar_SparseSpatialMapManager * This);
void easyar_SparseSpatialMapManager__dtor(easyar_SparseSpatialMapManager * This);
void easyar_SparseSpatialMapManager__retain(const easyar_SparseSpatialMapManager * This, /* OUT */ easyar_SparseSpatialMapManager * * Return);
const char * easyar_SparseSpatialMapManager__typeName(const easyar_SparseSpatialMapManager * This);

#ifdef __cplusplus
}
#endif

#endif
