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
/// record
/// The dense reconstructed model is represented by triangle mesh, or simply denoted as mesh. Because mesh updates frequently, in order to ensure efficiency, the mesh of the whole reconstruction model is divided into many mesh blocks. A mesh block is composed of a cube about 1 meter long, with attributes such as vertices and indices.
///
/// BlockInfo is used to describe the content of a mesh block. (x, y, z) is the index of mesh block, the coordinates of a mesh block&#39;s origin in world coordinate system can be obtained by  multiplying (x, y, z) by the physical size of mesh block. You may filter the part you want to display in advance by the mesh block&#39;s world coordinates for the sake of saving rendering time.
/// </summary>
@interface easyar_BlockInfo : NSObject

/// <summary>
/// x in index (x, y, z) of mesh block.
/// </summary>
@property (nonatomic) int x;
/// <summary>
/// y in index (x, y, z) of mesh block.
/// </summary>
@property (nonatomic) int y;
/// <summary>
/// z in index (x, y, z) of mesh block.
/// </summary>
@property (nonatomic) int z;
/// <summary>
/// Number of vertices in a mesh block.
/// </summary>
@property (nonatomic) int numOfVertex;
/// <summary>
/// startPointOfVertex is the starting position of the vertex data stored in the vertex buffer, indicating from where the stored vertices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of vertex buffer. The offset is startPointOfVertex*3*4 bytes.
/// </summary>
@property (nonatomic) int startPointOfVertex;
/// <summary>
/// The number of indices in a mesh block. Each of three consecutive vertices form a triangle.
/// </summary>
@property (nonatomic) int numOfIndex;
/// <summary>
/// Similar to startPointOfVertex. startPointOfIndex is the starting position of the index data stored in the index buffer, indicating from where the stored indices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of index buffer. The offset is startPointOfIndex*3*4 bytes.
/// </summary>
@property (nonatomic) int startPointOfIndex;
/// <summary>
/// Version represents how many times the mesh block has updated. The larger the version, the newer the block. If the version of a mesh block increases after calling `DenseSpatialMap.updateSceneMesh`_ , it indicates that the mash block has changed.
/// </summary>
@property (nonatomic) int version;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)create:(int)x y:(int)y z:(int)z numOfVertex:(int)numOfVertex startPointOfVertex:(int)startPointOfVertex numOfIndex:(int)numOfIndex startPointOfIndex:(int)startPointOfIndex version:(int)version;

@end

/// <summary>
/// SceneMesh is used to manage and preserve the results of `DenseSpatialMap`_.
/// There are two kinds of meshes saved in SceneMesh, one is the mesh of the whole reconstructed scene, hereinafter referred to as `meshAll`, the other is the recently updated mesh, hereinafter referred to as `meshUpdated`. `meshAll` is a whole mesh, including all vertex data and index data, etc. `meshUpdated` is composed of several `mesh block` s, each `mesh block` is a cube, which contains the mesh formed by the object surface in the corresponding cube space.
/// `meshAll` is available only when the `DenseSpatialMap.updateSceneMesh`_ method is called specifying that all meshes need to be updated. If `meshAll` has been updated previously and not updated in recent times, the data in `meshAll` is remain the same.
/// </summary>
@interface easyar_SceneMesh : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Get the number of vertices in `meshAll`.
/// </summary>
- (int)getNumOfVertexAll;
/// <summary>
/// Get the number of indices in `meshAll`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
/// </summary>
- (int)getNumOfIndexAll;
/// <summary>
/// Get the position component of the vertices in `meshAll` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
/// </summary>
- (easyar_Buffer *)getVerticesAll;
/// <summary>
/// Get the normal component of vertices in `meshAll`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
/// </summary>
- (easyar_Buffer *)getNormalsAll;
/// <summary>
/// Get the index data in `meshAll`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
/// </summary>
- (easyar_Buffer *)getIndicesAll;
/// <summary>
/// Get the number of vertices in `meshUpdated`.
/// </summary>
- (int)getNumOfVertexIncremental;
/// <summary>
/// Get the number of indices in `meshUpdated`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
/// </summary>
- (int)getNumOfIndexIncremental;
/// <summary>
/// Get the position component of the vertices in `meshUpdated` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
/// </summary>
- (easyar_Buffer *)getVerticesIncremental;
/// <summary>
/// Get the normal component of vertices in `meshUpdated`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
/// </summary>
- (easyar_Buffer *)getNormalsIncremental;
/// <summary>
/// Get the index data in `meshUpdated`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
/// </summary>
- (easyar_Buffer *)getIndicesIncremental;
/// <summary>
/// Gets the description object of `mesh block` in `meshUpdate`. The return value is an array of `BlockInfo`_ elements, each of which is a detailed description of a `mesh block`.
/// </summary>
- (NSArray<easyar_BlockInfo *> *)getBlocksInfoIncremental;
/// <summary>
/// Get the edge length of a `mesh block` in meters.
/// </summary>
- (float)getBlockDimensionInMeters;

@end
