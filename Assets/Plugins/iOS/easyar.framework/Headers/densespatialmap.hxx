//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_DENSESPATIALMAP_HXX__
#define __EASYAR_DENSESPATIALMAP_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// DenseSpatialMap is used to reconstruct the environment accurately and densely. The reconstructed model is represented by `triangle mesh`, which is denoted simply by `mesh`.
/// DenseSpatialMap occupies 1 buffers of camera.
/// </summary>
class DenseSpatialMap
{
protected:
    easyar_DenseSpatialMap * cdata_ ;
    void init_cdata(easyar_DenseSpatialMap * cdata);
    virtual DenseSpatialMap & operator=(const DenseSpatialMap & data) { return *this; } //deleted
public:
    DenseSpatialMap(easyar_DenseSpatialMap * cdata);
    virtual ~DenseSpatialMap();

    DenseSpatialMap(const DenseSpatialMap & data);
    const easyar_DenseSpatialMap * get_cdata() const;
    easyar_DenseSpatialMap * get_cdata();

    /// <summary>
    /// Returns True when the device supports dense reconstruction, otherwise returns False.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Input port for input frame. For DenseSpatialMap to work, the inputFrame must include image and it&#39;s camera parameters and spatial information (cameraTransform and trackingStatus). See also `InputFrameSink`_ .
    /// </summary>
    void inputFrameSink(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Create `DenseSpatialMap`_ object.
    /// </summary>
    static void create(/* OUT */ DenseSpatialMap * * Return);
    /// <summary>
    /// Start or continue runninng `DenseSpatialMap`_ algorithm.
    /// </summary>
    bool start();
    /// <summary>
    /// Pause the reconstruction algorithm. Call `start` to resume reconstruction.
    /// </summary>
    void stop();
    /// <summary>
    /// Close `DenseSpatialMap`_ algorithm.
    /// </summary>
    void close();
    /// <summary>
    /// Get the mesh management object of type `SceneMesh`_ . The contents will automatically update after calling the `DenseSpatialMap.updateSceneMesh`_ function.
    /// </summary>
    void getMesh(/* OUT */ SceneMesh * * Return);
    /// <summary>
    /// Get the lastest updated mesh and save it to the `SceneMesh`_ object obtained by `DenseSpatialMap.getMesh`_ .
    /// The parameter `updateMeshAll` indicates whether to perform a `full update` or an `incremental update`. When `updateMeshAll` is True, `full update` is performed. All meshes are saved to `SceneMesh`_ . When `updateMeshAll` is False, `incremental update` is performed, and only the most recently updated mesh is saved to `SceneMesh`_ .
    /// `Full update` will take extra time and memory space, causing performance degradation.
    /// </summary>
    bool updateSceneMesh(bool updateMeshAll);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_DENSESPATIALMAP_HXX__
#define __IMPLEMENTATION_EASYAR_DENSESPATIALMAP_HXX__

#include "easyar/densespatialmap.h"
#include "easyar/dataflow.hxx"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"
#include "easyar/scenemesh.hxx"

namespace easyar {

inline DenseSpatialMap::DenseSpatialMap(easyar_DenseSpatialMap * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline DenseSpatialMap::~DenseSpatialMap()
{
    if (cdata_) {
        easyar_DenseSpatialMap__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline DenseSpatialMap::DenseSpatialMap(const DenseSpatialMap & data)
    :
    cdata_(NULL)
{
    easyar_DenseSpatialMap * cdata = NULL;
    easyar_DenseSpatialMap__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_DenseSpatialMap * DenseSpatialMap::get_cdata() const
{
    return cdata_;
}
inline easyar_DenseSpatialMap * DenseSpatialMap::get_cdata()
{
    return cdata_;
}
inline void DenseSpatialMap::init_cdata(easyar_DenseSpatialMap * cdata)
{
    cdata_ = cdata;
}
inline bool DenseSpatialMap::isAvailable()
{
    bool _return_value_ = easyar_DenseSpatialMap_isAvailable();
    return _return_value_;
}
inline void DenseSpatialMap::inputFrameSink(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_DenseSpatialMap_inputFrameSink(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline int DenseSpatialMap::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_DenseSpatialMap_bufferRequirement(cdata_);
    return _return_value_;
}
inline void DenseSpatialMap::create(/* OUT */ DenseSpatialMap * * Return)
{
    easyar_DenseSpatialMap * _return_value_ = NULL;
    easyar_DenseSpatialMap_create(&_return_value_);
    *Return = new DenseSpatialMap(_return_value_);
}
inline bool DenseSpatialMap::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_DenseSpatialMap_start(cdata_);
    return _return_value_;
}
inline void DenseSpatialMap::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_DenseSpatialMap_stop(cdata_);
}
inline void DenseSpatialMap::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_DenseSpatialMap_close(cdata_);
}
inline void DenseSpatialMap::getMesh(/* OUT */ SceneMesh * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_SceneMesh * _return_value_ = NULL;
    easyar_DenseSpatialMap_getMesh(cdata_, &_return_value_);
    *Return = new SceneMesh(_return_value_);
}
inline bool DenseSpatialMap::updateSceneMesh(bool arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_DenseSpatialMap_updateSceneMesh(cdata_, arg0);
    return _return_value_;
}

}

#endif
