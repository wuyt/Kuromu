//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SCENEMESH_HXX__
#define __EASYAR_SCENEMESH_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// record
/// The dense reconstructed model is represented by triangle mesh, or simply denoted as mesh. Because mesh updates frequently, in order to ensure efficiency, the mesh of the whole reconstruction model is divided into many mesh blocks. A mesh block is composed of a cube about 1 meter long, with attributes such as vertices and indices.
///
/// BlockInfo is used to describe the content of a mesh block. (x, y, z) is the index of mesh block, the coordinates of a mesh block&#39;s origin in world coordinate system can be obtained by  multiplying (x, y, z) by the physical size of mesh block. You may filter the part you want to display in advance by the mesh block&#39;s world coordinates for the sake of saving rendering time.
/// </summary>
struct BlockInfo
{
    /// <summary>
    /// x in index (x, y, z) of mesh block.
    /// </summary>
    int x;
    /// <summary>
    /// y in index (x, y, z) of mesh block.
    /// </summary>
    int y;
    /// <summary>
    /// z in index (x, y, z) of mesh block.
    /// </summary>
    int z;
    /// <summary>
    /// Number of vertices in a mesh block.
    /// </summary>
    int numOfVertex;
    /// <summary>
    /// startPointOfVertex is the starting position of the vertex data stored in the vertex buffer, indicating from where the stored vertices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of vertex buffer. The offset is startPointOfVertex*3*4 bytes.
    /// </summary>
    int startPointOfVertex;
    /// <summary>
    /// The number of indices in a mesh block. Each of three consecutive vertices form a triangle.
    /// </summary>
    int numOfIndex;
    /// <summary>
    /// Similar to startPointOfVertex. startPointOfIndex is the starting position of the index data stored in the index buffer, indicating from where the stored indices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of index buffer. The offset is startPointOfIndex*3*4 bytes.
    /// </summary>
    int startPointOfIndex;
    /// <summary>
    /// Version represents how many times the mesh block has updated. The larger the version, the newer the block. If the version of a mesh block increases after calling `DenseSpatialMap.updateSceneMesh`_ , it indicates that the mash block has changed.
    /// </summary>
    int version;

    BlockInfo();
    BlockInfo(int x, int y, int z, int numOfVertex, int startPointOfVertex, int numOfIndex, int startPointOfIndex, int version);
    easyar_BlockInfo get_cdata();
};

/// <summary>
/// SceneMesh is used to manage and preserve the results of `DenseSpatialMap`_.
/// There are two kinds of meshes saved in SceneMesh, one is the mesh of the whole reconstructed scene, hereinafter referred to as `meshAll`, the other is the recently updated mesh, hereinafter referred to as `meshUpdated`. `meshAll` is a whole mesh, including all vertex data and index data, etc. `meshUpdated` is composed of several `mesh block` s, each `mesh block` is a cube, which contains the mesh formed by the object surface in the corresponding cube space.
/// `meshAll` is available only when the `DenseSpatialMap.updateSceneMesh`_ method is called specifying that all meshes need to be updated. If `meshAll` has been updated previously and not updated in recent times, the data in `meshAll` is remain the same.
/// </summary>
class SceneMesh
{
protected:
    easyar_SceneMesh * cdata_ ;
    void init_cdata(easyar_SceneMesh * cdata);
    virtual SceneMesh & operator=(const SceneMesh & data) { return *this; } //deleted
public:
    SceneMesh(easyar_SceneMesh * cdata);
    virtual ~SceneMesh();

    SceneMesh(const SceneMesh & data);
    const easyar_SceneMesh * get_cdata() const;
    easyar_SceneMesh * get_cdata();

    /// <summary>
    /// Get the number of vertices in `meshAll`.
    /// </summary>
    int getNumOfVertexAll();
    /// <summary>
    /// Get the number of indices in `meshAll`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
    /// </summary>
    int getNumOfIndexAll();
    /// <summary>
    /// Get the position component of the vertices in `meshAll` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
    /// </summary>
    void getVerticesAll(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Get the normal component of vertices in `meshAll`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
    /// </summary>
    void getNormalsAll(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Get the index data in `meshAll`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
    /// </summary>
    void getIndicesAll(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Get the number of vertices in `meshUpdated`.
    /// </summary>
    int getNumOfVertexIncremental();
    /// <summary>
    /// Get the number of indices in `meshUpdated`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
    /// </summary>
    int getNumOfIndexIncremental();
    /// <summary>
    /// Get the position component of the vertices in `meshUpdated` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
    /// </summary>
    void getVerticesIncremental(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Get the normal component of vertices in `meshUpdated`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
    /// </summary>
    void getNormalsIncremental(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Get the index data in `meshUpdated`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
    /// </summary>
    void getIndicesIncremental(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Gets the description object of `mesh block` in `meshUpdate`. The return value is an array of `BlockInfo`_ elements, each of which is a detailed description of a `mesh block`.
    /// </summary>
    void getBlocksInfoIncremental(/* OUT */ ListOfBlockInfo * * Return);
    /// <summary>
    /// Get the edge length of a `mesh block` in meters.
    /// </summary>
    float getBlockDimensionInMeters();
};

#ifndef __EASYAR_LISTOFBLOCKINFO__
#define __EASYAR_LISTOFBLOCKINFO__
class ListOfBlockInfo
{
private:
    easyar_ListOfBlockInfo * cdata_;
    virtual ListOfBlockInfo & operator=(const ListOfBlockInfo & data) { return *this; } //deleted
public:
    ListOfBlockInfo(easyar_ListOfBlockInfo * cdata);
    virtual ~ListOfBlockInfo();

    ListOfBlockInfo(const ListOfBlockInfo & data);
    const easyar_ListOfBlockInfo * get_cdata() const;
    easyar_ListOfBlockInfo * get_cdata();

    ListOfBlockInfo(easyar_BlockInfo * begin, easyar_BlockInfo * end);
    int size() const;
    BlockInfo at(int index) const;
};
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_SCENEMESH_HXX__
#define __IMPLEMENTATION_EASYAR_SCENEMESH_HXX__

#include "easyar/scenemesh.h"
#include "easyar/buffer.hxx"

namespace easyar {

inline BlockInfo::BlockInfo()
{
    this->x = int();
    this->y = int();
    this->z = int();
    this->numOfVertex = int();
    this->startPointOfVertex = int();
    this->numOfIndex = int();
    this->startPointOfIndex = int();
    this->version = int();
}
inline BlockInfo::BlockInfo(int x, int y, int z, int numOfVertex, int startPointOfVertex, int numOfIndex, int startPointOfIndex, int version)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->numOfVertex = numOfVertex;
    this->startPointOfVertex = startPointOfVertex;
    this->numOfIndex = numOfIndex;
    this->startPointOfIndex = startPointOfIndex;
    this->version = version;
}
inline easyar_BlockInfo BlockInfo::get_cdata()
{
    easyar_BlockInfo _return_value_ = {x, y, z, numOfVertex, startPointOfVertex, numOfIndex, startPointOfIndex, version};
    return _return_value_;
}
inline SceneMesh::SceneMesh(easyar_SceneMesh * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SceneMesh::~SceneMesh()
{
    if (cdata_) {
        easyar_SceneMesh__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SceneMesh::SceneMesh(const SceneMesh & data)
    :
    cdata_(NULL)
{
    easyar_SceneMesh * cdata = NULL;
    easyar_SceneMesh__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SceneMesh * SceneMesh::get_cdata() const
{
    return cdata_;
}
inline easyar_SceneMesh * SceneMesh::get_cdata()
{
    return cdata_;
}
inline void SceneMesh::init_cdata(easyar_SceneMesh * cdata)
{
    cdata_ = cdata;
}
inline int SceneMesh::getNumOfVertexAll()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_SceneMesh_getNumOfVertexAll(cdata_);
    return _return_value_;
}
inline int SceneMesh::getNumOfIndexAll()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_SceneMesh_getNumOfIndexAll(cdata_);
    return _return_value_;
}
inline void SceneMesh::getVerticesAll(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SceneMesh_getVerticesAll(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void SceneMesh::getNormalsAll(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SceneMesh_getNormalsAll(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void SceneMesh::getIndicesAll(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SceneMesh_getIndicesAll(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline int SceneMesh::getNumOfVertexIncremental()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_SceneMesh_getNumOfVertexIncremental(cdata_);
    return _return_value_;
}
inline int SceneMesh::getNumOfIndexIncremental()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_SceneMesh_getNumOfIndexIncremental(cdata_);
    return _return_value_;
}
inline void SceneMesh::getVerticesIncremental(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SceneMesh_getVerticesIncremental(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void SceneMesh::getNormalsIncremental(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SceneMesh_getNormalsIncremental(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void SceneMesh::getIndicesIncremental(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SceneMesh_getIndicesIncremental(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void SceneMesh::getBlocksInfoIncremental(/* OUT */ ListOfBlockInfo * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfBlockInfo * _return_value_ = NULL;
    easyar_SceneMesh_getBlocksInfoIncremental(cdata_, &_return_value_);
    *Return = new ListOfBlockInfo(_return_value_);
}
inline float SceneMesh::getBlockDimensionInMeters()
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_SceneMesh_getBlockDimensionInMeters(cdata_);
    return _return_value_;
}

#ifndef __IMPLEMENTATION_EASYAR_LISTOFBLOCKINFO__
#define __IMPLEMENTATION_EASYAR_LISTOFBLOCKINFO__
inline ListOfBlockInfo::ListOfBlockInfo(easyar_ListOfBlockInfo * cdata)
    : cdata_(cdata)
{
}
inline ListOfBlockInfo::~ListOfBlockInfo()
{
    if (cdata_) {
        easyar_ListOfBlockInfo__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfBlockInfo::ListOfBlockInfo(const ListOfBlockInfo & data)
    : cdata_(static_cast<easyar_ListOfBlockInfo *>(NULL))
{
    easyar_ListOfBlockInfo_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfBlockInfo * ListOfBlockInfo::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfBlockInfo * ListOfBlockInfo::get_cdata()
{
    return cdata_;
}

inline ListOfBlockInfo::ListOfBlockInfo(easyar_BlockInfo * begin, easyar_BlockInfo * end)
    : cdata_(static_cast<easyar_ListOfBlockInfo *>(NULL))
{
    easyar_ListOfBlockInfo__ctor(begin, end, &cdata_);
}
inline int ListOfBlockInfo::size() const
{
    return easyar_ListOfBlockInfo_size(cdata_);
}
inline BlockInfo ListOfBlockInfo::at(int index) const
{
    easyar_BlockInfo _return_value_ = easyar_ListOfBlockInfo_at(cdata_, index);
    return BlockInfo(_return_value_.x, _return_value_.y, _return_value_.z, _return_value_.numOfVertex, _return_value_.startPointOfVertex, _return_value_.numOfIndex, _return_value_.startPointOfIndex, _return_value_.version);
}
#endif

}

#endif
