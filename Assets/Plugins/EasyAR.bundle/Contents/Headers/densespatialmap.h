//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_DENSESPATIALMAP_H__
#define __EASYAR_DENSESPATIALMAP_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Returns True when the device supports dense reconstruction, otherwise returns False.
/// </summary>
bool easyar_DenseSpatialMap_isAvailable(void);
/// <summary>
/// Input port for input frame. For DenseSpatialMap to work, the inputFrame must include image and it&#39;s camera parameters and spatial information (cameraTransform and trackingStatus). See also `InputFrameSink`_ .
/// </summary>
void easyar_DenseSpatialMap_inputFrameSink(easyar_DenseSpatialMap * This, /* OUT */ easyar_InputFrameSink * * Return);
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
int easyar_DenseSpatialMap_bufferRequirement(easyar_DenseSpatialMap * This);
/// <summary>
/// Create `DenseSpatialMap`_ object.
/// </summary>
void easyar_DenseSpatialMap_create(/* OUT */ easyar_DenseSpatialMap * * Return);
/// <summary>
/// Start or continue runninng `DenseSpatialMap`_ algorithm.
/// </summary>
bool easyar_DenseSpatialMap_start(easyar_DenseSpatialMap * This);
/// <summary>
/// Pause the reconstruction algorithm. Call `start` to resume reconstruction.
/// </summary>
void easyar_DenseSpatialMap_stop(easyar_DenseSpatialMap * This);
/// <summary>
/// Close `DenseSpatialMap`_ algorithm.
/// </summary>
void easyar_DenseSpatialMap_close(easyar_DenseSpatialMap * This);
/// <summary>
/// Get the mesh management object of type `SceneMesh`_ . The contents will automatically update after calling the `DenseSpatialMap.updateSceneMesh`_ function.
/// </summary>
void easyar_DenseSpatialMap_getMesh(easyar_DenseSpatialMap * This, /* OUT */ easyar_SceneMesh * * Return);
/// <summary>
/// Get the lastest updated mesh and save it to the `SceneMesh`_ object obtained by `DenseSpatialMap.getMesh`_ .
/// The parameter `updateMeshAll` indicates whether to perform a `full update` or an `incremental update`. When `updateMeshAll` is True, `full update` is performed. All meshes are saved to `SceneMesh`_ . When `updateMeshAll` is False, `incremental update` is performed, and only the most recently updated mesh is saved to `SceneMesh`_ .
/// `Full update` will take extra time and memory space, causing performance degradation.
/// </summary>
bool easyar_DenseSpatialMap_updateSceneMesh(easyar_DenseSpatialMap * This, bool updateMeshAll);
void easyar_DenseSpatialMap__dtor(easyar_DenseSpatialMap * This);
void easyar_DenseSpatialMap__retain(const easyar_DenseSpatialMap * This, /* OUT */ easyar_DenseSpatialMap * * Return);
const char * easyar_DenseSpatialMap__typeName(const easyar_DenseSpatialMap * This);

#ifdef __cplusplus
}
#endif

#endif
