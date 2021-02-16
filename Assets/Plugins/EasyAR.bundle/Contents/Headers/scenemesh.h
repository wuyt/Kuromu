//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SCENEMESH_H__
#define __EASYAR_SCENEMESH_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Get the number of vertices in `meshAll`.
/// </summary>
int easyar_SceneMesh_getNumOfVertexAll(easyar_SceneMesh * This);
/// <summary>
/// Get the number of indices in `meshAll`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
/// </summary>
int easyar_SceneMesh_getNumOfIndexAll(easyar_SceneMesh * This);
/// <summary>
/// Get the position component of the vertices in `meshAll` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
/// </summary>
void easyar_SceneMesh_getVerticesAll(easyar_SceneMesh * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Get the normal component of vertices in `meshAll`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
/// </summary>
void easyar_SceneMesh_getNormalsAll(easyar_SceneMesh * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Get the index data in `meshAll`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
/// </summary>
void easyar_SceneMesh_getIndicesAll(easyar_SceneMesh * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Get the number of vertices in `meshUpdated`.
/// </summary>
int easyar_SceneMesh_getNumOfVertexIncremental(easyar_SceneMesh * This);
/// <summary>
/// Get the number of indices in `meshUpdated`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
/// </summary>
int easyar_SceneMesh_getNumOfIndexIncremental(easyar_SceneMesh * This);
/// <summary>
/// Get the position component of the vertices in `meshUpdated` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
/// </summary>
void easyar_SceneMesh_getVerticesIncremental(easyar_SceneMesh * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Get the normal component of vertices in `meshUpdated`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
/// </summary>
void easyar_SceneMesh_getNormalsIncremental(easyar_SceneMesh * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Get the index data in `meshUpdated`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
/// </summary>
void easyar_SceneMesh_getIndicesIncremental(easyar_SceneMesh * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Gets the description object of `mesh block` in `meshUpdate`. The return value is an array of `BlockInfo`_ elements, each of which is a detailed description of a `mesh block`.
/// </summary>
void easyar_SceneMesh_getBlocksInfoIncremental(easyar_SceneMesh * This, /* OUT */ easyar_ListOfBlockInfo * * Return);
/// <summary>
/// Get the edge length of a `mesh block` in meters.
/// </summary>
float easyar_SceneMesh_getBlockDimensionInMeters(easyar_SceneMesh * This);
void easyar_SceneMesh__dtor(easyar_SceneMesh * This);
void easyar_SceneMesh__retain(const easyar_SceneMesh * This, /* OUT */ easyar_SceneMesh * * Return);
const char * easyar_SceneMesh__typeName(const easyar_SceneMesh * This);

void easyar_ListOfBlockInfo__ctor(easyar_BlockInfo const * begin, easyar_BlockInfo const * end, /* OUT */ easyar_ListOfBlockInfo * * Return);
void easyar_ListOfBlockInfo__dtor(easyar_ListOfBlockInfo * This);
void easyar_ListOfBlockInfo_copy(const easyar_ListOfBlockInfo * This, /* OUT */ easyar_ListOfBlockInfo * * Return);
int easyar_ListOfBlockInfo_size(const easyar_ListOfBlockInfo * This);
easyar_BlockInfo easyar_ListOfBlockInfo_at(const easyar_ListOfBlockInfo * This, int index);

#ifdef __cplusplus
}
#endif

#endif
