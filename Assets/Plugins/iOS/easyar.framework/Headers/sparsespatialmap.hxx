//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SPARSESPATIALMAP_HXX__
#define __EASYAR_SPARSESPATIALMAP_HXX__

#include "easyar/types.hxx"
#include "easyar/frame.hxx"

namespace easyar {

/// <summary>
/// Describes the result of mapping and localization. Updated at the same frame rate with OutputFrame.
/// </summary>
class SparseSpatialMapResult : public FrameFilterResult
{
protected:
    easyar_SparseSpatialMapResult * cdata_ ;
    void init_cdata(easyar_SparseSpatialMapResult * cdata);
    virtual SparseSpatialMapResult & operator=(const SparseSpatialMapResult & data) { return *this; } //deleted
public:
    SparseSpatialMapResult(easyar_SparseSpatialMapResult * cdata);
    virtual ~SparseSpatialMapResult();

    SparseSpatialMapResult(const SparseSpatialMapResult & data);
    const easyar_SparseSpatialMapResult * get_cdata() const;
    easyar_SparseSpatialMapResult * get_cdata();

    /// <summary>
    /// Obtain motion tracking status.
    /// </summary>
    MotionTrackingStatus getMotionTrackingStatus();
    /// <summary>
    /// Returns pose of the origin of VIO system in camera coordinate system.
    /// </summary>
    OptionalOfMatrix44F getVioPose();
    /// <summary>
    /// Returns the pose of origin of the map in camera coordinate system, when localization is successful.
    /// Otherwise, returns pose of the origin of VIO system in camera coordinate system.
    /// </summary>
    OptionalOfMatrix44F getMapPose();
    /// <summary>
    /// Returns true if the system can reliablly locate the pose of the device with regard to the map.
    /// Once relocalization succeeds, relative pose can be updated by motion tracking module.
    /// As long as the motion tracking module returns normal tracking status, the localization status is also true.
    /// </summary>
    bool getLocalizationStatus();
    /// <summary>
    /// Returns current localized map ID.
    /// </summary>
    void getLocalizationMapID(/* OUT */ String * * Return);
    static void tryCastFromFrameFilterResult(FrameFilterResult * v, /* OUT */ SparseSpatialMapResult * * Return);
};

class PlaneData
{
protected:
    easyar_PlaneData * cdata_ ;
    void init_cdata(easyar_PlaneData * cdata);
    virtual PlaneData & operator=(const PlaneData & data) { return *this; } //deleted
public:
    PlaneData(easyar_PlaneData * cdata);
    virtual ~PlaneData();

    PlaneData(const PlaneData & data);
    const easyar_PlaneData * get_cdata() const;
    easyar_PlaneData * get_cdata();

    /// <summary>
    /// Constructor
    /// </summary>
    PlaneData();
    /// <summary>
    /// Returns the type of this plane.
    /// </summary>
    PlaneType getType();
    /// <summary>
    /// Returns the pose of the center of the detected plane.The pose&#39;s transformed +Y axis will be point normal out of the plane, with the +X and +Z axes orienting the extents of the bounding rectangle.
    /// </summary>
    Matrix44F getPose();
    /// <summary>
    /// Returns the length of this plane&#39;s bounding rectangle measured along the local X-axis of the coordinate space centered on the plane.
    /// </summary>
    float getExtentX();
    /// <summary>
    /// Returns the length of this plane&#39;s bounding rectangle measured along the local Z-axis of the coordinate frame centered on the plane.
    /// </summary>
    float getExtentZ();
};

/// <summary>
/// Configuration used to set the localization mode.
/// </summary>
class SparseSpatialMapConfig
{
protected:
    easyar_SparseSpatialMapConfig * cdata_ ;
    void init_cdata(easyar_SparseSpatialMapConfig * cdata);
    virtual SparseSpatialMapConfig & operator=(const SparseSpatialMapConfig & data) { return *this; } //deleted
public:
    SparseSpatialMapConfig(easyar_SparseSpatialMapConfig * cdata);
    virtual ~SparseSpatialMapConfig();

    SparseSpatialMapConfig(const SparseSpatialMapConfig & data);
    const easyar_SparseSpatialMapConfig * get_cdata() const;
    easyar_SparseSpatialMapConfig * get_cdata();

    /// <summary>
    /// Constructor
    /// </summary>
    SparseSpatialMapConfig();
    /// <summary>
    /// Sets localization configurations. See also `LocalizationMode`_.
    /// </summary>
    void setLocalizationMode(LocalizationMode _value);
    /// <summary>
    /// Returns localization configurations. See also `LocalizationMode`_.
    /// </summary>
    LocalizationMode getLocalizationMode();
};

/// <summary>
/// Provides core components for SparseSpatialMap, can be used for sparse spatial map building as well as localization using existing map. Also provides utilities for point cloud and plane access.
/// SparseSpatialMap occupies 2 buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
class SparseSpatialMap
{
protected:
    easyar_SparseSpatialMap * cdata_ ;
    void init_cdata(easyar_SparseSpatialMap * cdata);
    virtual SparseSpatialMap & operator=(const SparseSpatialMap & data) { return *this; } //deleted
public:
    SparseSpatialMap(easyar_SparseSpatialMap * cdata);
    virtual ~SparseSpatialMap();

    SparseSpatialMap(const SparseSpatialMap & data);
    const easyar_SparseSpatialMap * get_cdata() const;
    easyar_SparseSpatialMap * get_cdata();

    /// <summary>
    /// Check whether SparseSpatialMap is is available, always return true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Input port for input frame. For SparseSpatialMap to work, the inputFrame must include camera parameters, timestamp and spatial information. See also `InputFrameSink`_
    /// </summary>
    void inputFrameSink(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port for output frame. See also `OutputFrameSource`_
    /// </summary>
    void outputFrameSource(/* OUT */ OutputFrameSource * * Return);
    /// <summary>
    /// Construct SparseSpatialMap.
    /// </summary>
    static void create(/* OUT */ SparseSpatialMap * * Return);
    /// <summary>
    /// Start SparseSpatialMap system.
    /// </summary>
    bool start();
    /// <summary>
    /// Stop SparseSpatialMap from running。Can resume running by calling start().
    /// </summary>
    void stop();
    /// <summary>
    /// Close SparseSpatialMap. SparseSpatialMap can no longer be used.
    /// </summary>
    void close();
    /// <summary>
    /// Returns the buffer of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space, each of which takes 4 bytes.
    /// </summary>
    void getPointCloudBuffer(/* OUT */ Buffer * * Return);
    /// <summary>
    /// Returns detected planes in SparseSpatialMap.
    /// </summary>
    void getMapPlanes(/* OUT */ ListOfPlaneData * * Return);
    /// <summary>
    /// Perform hit test against the point cloud. The results are returned sorted by their distance to the camera in ascending order.
    /// </summary>
    void hitTestAgainstPointCloud(Vec2F cameraImagePoint, /* OUT */ ListOfVec3F * * Return);
    /// <summary>
    /// Performs ray cast from the user&#39;s device in the direction of given screen point.
    /// Intersections with detected planes are returned. 3D positions on physical planes are sorted by distance from the device in ascending order.
    /// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// The output point cloud coordinate is in the world coordinate system.
    /// </summary>
    void hitTestAgainstPlanes(Vec2F cameraImagePoint, /* OUT */ ListOfVec3F * * Return);
    /// <summary>
    /// Get the map data version of the current SparseSpatialMap.
    /// </summary>
    static void getMapVersion(/* OUT */ String * * Return);
    /// <summary>
    /// UnloadMap specified SparseSpatialMap data via callback function.The return value of callback indicates whether unload map succeeds (true) or fails (false).
    /// </summary>
    void unloadMap(String * mapID, CallbackScheduler * callbackScheduler, OptionalOfFunctorOfVoidFromBool resultCallBack);
    /// <summary>
    /// Set configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
    /// </summary>
    void setConfig(SparseSpatialMapConfig * config);
    /// <summary>
    /// Returns configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
    /// </summary>
    void getConfig(/* OUT */ SparseSpatialMapConfig * * Return);
    /// <summary>
    /// Start localization in loaded maps. Should set `LocalizationMode`_ first.
    /// </summary>
    bool startLocalization();
    /// <summary>
    /// Stop localization in loaded maps.
    /// </summary>
    void stopLocalization();
};

#ifndef __EASYAR_OPTIONALOFMATRIX__F__
#define __EASYAR_OPTIONALOFMATRIX__F__
struct OptionalOfMatrix44F
{
    bool has_value;
    Matrix44F value;
};
static inline easyar_OptionalOfMatrix44F OptionalOfMatrix44F_to_c(OptionalOfMatrix44F o);
#endif

#ifndef __EASYAR_LISTOFPLANEDATA__
#define __EASYAR_LISTOFPLANEDATA__
class ListOfPlaneData
{
private:
    easyar_ListOfPlaneData * cdata_;
    virtual ListOfPlaneData & operator=(const ListOfPlaneData & data) { return *this; } //deleted
public:
    ListOfPlaneData(easyar_ListOfPlaneData * cdata);
    virtual ~ListOfPlaneData();

    ListOfPlaneData(const ListOfPlaneData & data);
    const easyar_ListOfPlaneData * get_cdata() const;
    easyar_ListOfPlaneData * get_cdata();

    ListOfPlaneData(easyar_PlaneData * * begin, easyar_PlaneData * * end);
    int size() const;
    PlaneData * at(int index) const;
};
#endif

#ifndef __EASYAR_LISTOFVEC_F__
#define __EASYAR_LISTOFVEC_F__
class ListOfVec3F
{
private:
    easyar_ListOfVec3F * cdata_;
    virtual ListOfVec3F & operator=(const ListOfVec3F & data) { return *this; } //deleted
public:
    ListOfVec3F(easyar_ListOfVec3F * cdata);
    virtual ~ListOfVec3F();

    ListOfVec3F(const ListOfVec3F & data);
    const easyar_ListOfVec3F * get_cdata() const;
    easyar_ListOfVec3F * get_cdata();

    ListOfVec3F(easyar_Vec3F * begin, easyar_Vec3F * end);
    int size() const;
    Vec3F at(int index) const;
};
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMBOOL__
#define __EASYAR_FUNCTOROFVOIDFROMBOOL__
struct FunctorOfVoidFromBool
{
    void * _state;
    void (* func)(void * _state, bool);
    void (* destroy)(void * _state);
    FunctorOfVoidFromBool(void * _state, void (* func)(void * _state, bool), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromBool_func(void * _state, bool, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromBool_destroy(void * _state);
static inline easyar_FunctorOfVoidFromBool FunctorOfVoidFromBool_to_c(FunctorOfVoidFromBool f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMBOOL__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMBOOL__
struct OptionalOfFunctorOfVoidFromBool
{
    bool has_value;
    FunctorOfVoidFromBool value;
};
static inline easyar_OptionalOfFunctorOfVoidFromBool OptionalOfFunctorOfVoidFromBool_to_c(OptionalOfFunctorOfVoidFromBool o);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_SPARSESPATIALMAP_HXX__
#define __IMPLEMENTATION_EASYAR_SPARSESPATIALMAP_HXX__

#include "easyar/sparsespatialmap.h"
#include "easyar/frame.hxx"
#include "easyar/matrix.hxx"
#include "easyar/dataflow.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/callbackscheduler.hxx"

namespace easyar {

inline SparseSpatialMapResult::SparseSpatialMapResult(easyar_SparseSpatialMapResult * cdata)
    :
    FrameFilterResult(static_cast<easyar_FrameFilterResult *>(NULL)),
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SparseSpatialMapResult::~SparseSpatialMapResult()
{
    if (cdata_) {
        easyar_SparseSpatialMapResult__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SparseSpatialMapResult::SparseSpatialMapResult(const SparseSpatialMapResult & data)
    :
    FrameFilterResult(static_cast<easyar_FrameFilterResult *>(NULL)),
    cdata_(NULL)
{
    easyar_SparseSpatialMapResult * cdata = NULL;
    easyar_SparseSpatialMapResult__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SparseSpatialMapResult * SparseSpatialMapResult::get_cdata() const
{
    return cdata_;
}
inline easyar_SparseSpatialMapResult * SparseSpatialMapResult::get_cdata()
{
    return cdata_;
}
inline void SparseSpatialMapResult::init_cdata(easyar_SparseSpatialMapResult * cdata)
{
    cdata_ = cdata;
    {
        easyar_FrameFilterResult * cdata_inner = NULL;
        easyar_castSparseSpatialMapResultToFrameFilterResult(cdata, &cdata_inner);
        FrameFilterResult::init_cdata(cdata_inner);
    }
}
inline MotionTrackingStatus SparseSpatialMapResult::getMotionTrackingStatus()
{
    if (cdata_ == NULL) {
        return MotionTrackingStatus();
    }
    easyar_MotionTrackingStatus _return_value_ = easyar_SparseSpatialMapResult_getMotionTrackingStatus(cdata_);
    return static_cast<MotionTrackingStatus>(_return_value_);
}
inline OptionalOfMatrix44F SparseSpatialMapResult::getVioPose()
{
    if (cdata_ == NULL) {
        return {false, Matrix44F()};
    }
    easyar_OptionalOfMatrix44F _return_value_ = easyar_SparseSpatialMapResult_getVioPose(cdata_);
    return (_return_value_.has_value ? OptionalOfMatrix44F{true, Matrix44F(_return_value_.value.data[0], _return_value_.value.data[1], _return_value_.value.data[2], _return_value_.value.data[3], _return_value_.value.data[4], _return_value_.value.data[5], _return_value_.value.data[6], _return_value_.value.data[7], _return_value_.value.data[8], _return_value_.value.data[9], _return_value_.value.data[10], _return_value_.value.data[11], _return_value_.value.data[12], _return_value_.value.data[13], _return_value_.value.data[14], _return_value_.value.data[15])} : OptionalOfMatrix44F{false, {}});
}
inline OptionalOfMatrix44F SparseSpatialMapResult::getMapPose()
{
    if (cdata_ == NULL) {
        return {false, Matrix44F()};
    }
    easyar_OptionalOfMatrix44F _return_value_ = easyar_SparseSpatialMapResult_getMapPose(cdata_);
    return (_return_value_.has_value ? OptionalOfMatrix44F{true, Matrix44F(_return_value_.value.data[0], _return_value_.value.data[1], _return_value_.value.data[2], _return_value_.value.data[3], _return_value_.value.data[4], _return_value_.value.data[5], _return_value_.value.data[6], _return_value_.value.data[7], _return_value_.value.data[8], _return_value_.value.data[9], _return_value_.value.data[10], _return_value_.value.data[11], _return_value_.value.data[12], _return_value_.value.data[13], _return_value_.value.data[14], _return_value_.value.data[15])} : OptionalOfMatrix44F{false, {}});
}
inline bool SparseSpatialMapResult::getLocalizationStatus()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_SparseSpatialMapResult_getLocalizationStatus(cdata_);
    return _return_value_;
}
inline void SparseSpatialMapResult::getLocalizationMapID(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_SparseSpatialMapResult_getLocalizationMapID(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void SparseSpatialMapResult::tryCastFromFrameFilterResult(FrameFilterResult * v, /* OUT */ SparseSpatialMapResult * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_SparseSpatialMapResult * cdata = NULL;
    easyar_tryCastFrameFilterResultToSparseSpatialMapResult(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new SparseSpatialMapResult(cdata);
}

inline PlaneData::PlaneData(easyar_PlaneData * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline PlaneData::~PlaneData()
{
    if (cdata_) {
        easyar_PlaneData__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline PlaneData::PlaneData(const PlaneData & data)
    :
    cdata_(NULL)
{
    easyar_PlaneData * cdata = NULL;
    easyar_PlaneData__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_PlaneData * PlaneData::get_cdata() const
{
    return cdata_;
}
inline easyar_PlaneData * PlaneData::get_cdata()
{
    return cdata_;
}
inline void PlaneData::init_cdata(easyar_PlaneData * cdata)
{
    cdata_ = cdata;
}
inline PlaneData::PlaneData()
    :
    cdata_(NULL)
{
    easyar_PlaneData * _return_value_ = NULL;
    easyar_PlaneData__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline PlaneType PlaneData::getType()
{
    if (cdata_ == NULL) {
        return PlaneType();
    }
    easyar_PlaneType _return_value_ = easyar_PlaneData_getType(cdata_);
    return static_cast<PlaneType>(_return_value_);
}
inline Matrix44F PlaneData::getPose()
{
    if (cdata_ == NULL) {
        return Matrix44F();
    }
    easyar_Matrix44F _return_value_ = easyar_PlaneData_getPose(cdata_);
    return Matrix44F(_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]);
}
inline float PlaneData::getExtentX()
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_PlaneData_getExtentX(cdata_);
    return _return_value_;
}
inline float PlaneData::getExtentZ()
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_PlaneData_getExtentZ(cdata_);
    return _return_value_;
}

inline SparseSpatialMapConfig::SparseSpatialMapConfig(easyar_SparseSpatialMapConfig * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SparseSpatialMapConfig::~SparseSpatialMapConfig()
{
    if (cdata_) {
        easyar_SparseSpatialMapConfig__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SparseSpatialMapConfig::SparseSpatialMapConfig(const SparseSpatialMapConfig & data)
    :
    cdata_(NULL)
{
    easyar_SparseSpatialMapConfig * cdata = NULL;
    easyar_SparseSpatialMapConfig__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SparseSpatialMapConfig * SparseSpatialMapConfig::get_cdata() const
{
    return cdata_;
}
inline easyar_SparseSpatialMapConfig * SparseSpatialMapConfig::get_cdata()
{
    return cdata_;
}
inline void SparseSpatialMapConfig::init_cdata(easyar_SparseSpatialMapConfig * cdata)
{
    cdata_ = cdata;
}
inline SparseSpatialMapConfig::SparseSpatialMapConfig()
    :
    cdata_(NULL)
{
    easyar_SparseSpatialMapConfig * _return_value_ = NULL;
    easyar_SparseSpatialMapConfig__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline void SparseSpatialMapConfig::setLocalizationMode(LocalizationMode arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMapConfig_setLocalizationMode(cdata_, static_cast<easyar_LocalizationMode>(arg0));
}
inline LocalizationMode SparseSpatialMapConfig::getLocalizationMode()
{
    if (cdata_ == NULL) {
        return LocalizationMode();
    }
    easyar_LocalizationMode _return_value_ = easyar_SparseSpatialMapConfig_getLocalizationMode(cdata_);
    return static_cast<LocalizationMode>(_return_value_);
}

inline SparseSpatialMap::SparseSpatialMap(easyar_SparseSpatialMap * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SparseSpatialMap::~SparseSpatialMap()
{
    if (cdata_) {
        easyar_SparseSpatialMap__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SparseSpatialMap::SparseSpatialMap(const SparseSpatialMap & data)
    :
    cdata_(NULL)
{
    easyar_SparseSpatialMap * cdata = NULL;
    easyar_SparseSpatialMap__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SparseSpatialMap * SparseSpatialMap::get_cdata() const
{
    return cdata_;
}
inline easyar_SparseSpatialMap * SparseSpatialMap::get_cdata()
{
    return cdata_;
}
inline void SparseSpatialMap::init_cdata(easyar_SparseSpatialMap * cdata)
{
    cdata_ = cdata;
}
inline bool SparseSpatialMap::isAvailable()
{
    bool _return_value_ = easyar_SparseSpatialMap_isAvailable();
    return _return_value_;
}
inline void SparseSpatialMap::inputFrameSink(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_SparseSpatialMap_inputFrameSink(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline int SparseSpatialMap::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_SparseSpatialMap_bufferRequirement(cdata_);
    return _return_value_;
}
inline void SparseSpatialMap::outputFrameSource(/* OUT */ OutputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSource * _return_value_ = NULL;
    easyar_SparseSpatialMap_outputFrameSource(cdata_, &_return_value_);
    *Return = new OutputFrameSource(_return_value_);
}
inline void SparseSpatialMap::create(/* OUT */ SparseSpatialMap * * Return)
{
    easyar_SparseSpatialMap * _return_value_ = NULL;
    easyar_SparseSpatialMap_create(&_return_value_);
    *Return = new SparseSpatialMap(_return_value_);
}
inline bool SparseSpatialMap::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_SparseSpatialMap_start(cdata_);
    return _return_value_;
}
inline void SparseSpatialMap::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMap_stop(cdata_);
}
inline void SparseSpatialMap::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMap_close(cdata_);
}
inline void SparseSpatialMap::getPointCloudBuffer(/* OUT */ Buffer * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_Buffer * _return_value_ = NULL;
    easyar_SparseSpatialMap_getPointCloudBuffer(cdata_, &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void SparseSpatialMap::getMapPlanes(/* OUT */ ListOfPlaneData * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfPlaneData * _return_value_ = NULL;
    easyar_SparseSpatialMap_getMapPlanes(cdata_, &_return_value_);
    *Return = new ListOfPlaneData(_return_value_);
}
inline void SparseSpatialMap::hitTestAgainstPointCloud(Vec2F arg0, /* OUT */ ListOfVec3F * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfVec3F * _return_value_ = NULL;
    easyar_SparseSpatialMap_hitTestAgainstPointCloud(cdata_, arg0.get_cdata(), &_return_value_);
    *Return = new ListOfVec3F(_return_value_);
}
inline void SparseSpatialMap::hitTestAgainstPlanes(Vec2F arg0, /* OUT */ ListOfVec3F * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfVec3F * _return_value_ = NULL;
    easyar_SparseSpatialMap_hitTestAgainstPlanes(cdata_, arg0.get_cdata(), &_return_value_);
    *Return = new ListOfVec3F(_return_value_);
}
inline void SparseSpatialMap::getMapVersion(/* OUT */ String * * Return)
{
    easyar_String * _return_value_ = NULL;
    easyar_SparseSpatialMap_getMapVersion(&_return_value_);
    *Return = new String(_return_value_);
}
inline void SparseSpatialMap::unloadMap(String * arg0, CallbackScheduler * arg1, OptionalOfFunctorOfVoidFromBool arg2)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMap_unloadMap(cdata_, arg0->get_cdata(), arg1->get_cdata(), OptionalOfFunctorOfVoidFromBool_to_c(arg2));
}
inline void SparseSpatialMap::setConfig(SparseSpatialMapConfig * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMap_setConfig(cdata_, arg0->get_cdata());
}
inline void SparseSpatialMap::getConfig(/* OUT */ SparseSpatialMapConfig * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_SparseSpatialMapConfig * _return_value_ = NULL;
    easyar_SparseSpatialMap_getConfig(cdata_, &_return_value_);
    *Return = new SparseSpatialMapConfig(_return_value_);
}
inline bool SparseSpatialMap::startLocalization()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_SparseSpatialMap_startLocalization(cdata_);
    return _return_value_;
}
inline void SparseSpatialMap::stopLocalization()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMap_stopLocalization(cdata_);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFMATRIX__F__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFMATRIX__F__
static inline easyar_OptionalOfMatrix44F OptionalOfMatrix44F_to_c(OptionalOfMatrix44F o)
{
    if (o.has_value) {
        easyar_OptionalOfMatrix44F _return_value_ = {true, o.value.get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfMatrix44F _return_value_ = {false, easyar_Matrix44F()};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_LISTOFPLANEDATA__
#define __IMPLEMENTATION_EASYAR_LISTOFPLANEDATA__
inline ListOfPlaneData::ListOfPlaneData(easyar_ListOfPlaneData * cdata)
    : cdata_(cdata)
{
}
inline ListOfPlaneData::~ListOfPlaneData()
{
    if (cdata_) {
        easyar_ListOfPlaneData__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfPlaneData::ListOfPlaneData(const ListOfPlaneData & data)
    : cdata_(static_cast<easyar_ListOfPlaneData *>(NULL))
{
    easyar_ListOfPlaneData_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfPlaneData * ListOfPlaneData::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfPlaneData * ListOfPlaneData::get_cdata()
{
    return cdata_;
}

inline ListOfPlaneData::ListOfPlaneData(easyar_PlaneData * * begin, easyar_PlaneData * * end)
    : cdata_(static_cast<easyar_ListOfPlaneData *>(NULL))
{
    easyar_ListOfPlaneData__ctor(begin, end, &cdata_);
}
inline int ListOfPlaneData::size() const
{
    return easyar_ListOfPlaneData_size(cdata_);
}
inline PlaneData * ListOfPlaneData::at(int index) const
{
    easyar_PlaneData * _return_value_ = easyar_ListOfPlaneData_at(cdata_, index);
    easyar_PlaneData__retain(_return_value_, &_return_value_);
    return new PlaneData(_return_value_);
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_LISTOFVEC_F__
#define __IMPLEMENTATION_EASYAR_LISTOFVEC_F__
inline ListOfVec3F::ListOfVec3F(easyar_ListOfVec3F * cdata)
    : cdata_(cdata)
{
}
inline ListOfVec3F::~ListOfVec3F()
{
    if (cdata_) {
        easyar_ListOfVec3F__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfVec3F::ListOfVec3F(const ListOfVec3F & data)
    : cdata_(static_cast<easyar_ListOfVec3F *>(NULL))
{
    easyar_ListOfVec3F_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfVec3F * ListOfVec3F::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfVec3F * ListOfVec3F::get_cdata()
{
    return cdata_;
}

inline ListOfVec3F::ListOfVec3F(easyar_Vec3F * begin, easyar_Vec3F * end)
    : cdata_(static_cast<easyar_ListOfVec3F *>(NULL))
{
    easyar_ListOfVec3F__ctor(begin, end, &cdata_);
}
inline int ListOfVec3F::size() const
{
    return easyar_ListOfVec3F_size(cdata_);
}
inline Vec3F ListOfVec3F::at(int index) const
{
    easyar_Vec3F _return_value_ = easyar_ListOfVec3F_at(cdata_, index);
    return Vec3F(_return_value_.data[0], _return_value_.data[1], _return_value_.data[2]);
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMBOOL__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMBOOL__
static inline easyar_OptionalOfFunctorOfVoidFromBool OptionalOfFunctorOfVoidFromBool_to_c(OptionalOfFunctorOfVoidFromBool o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromBool _return_value_ = {true, FunctorOfVoidFromBool_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromBool _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMBOOL__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMBOOL__
inline FunctorOfVoidFromBool::FunctorOfVoidFromBool(void * _state, void (* func)(void * _state, bool), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromBool_func(void * _state, bool arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        bool cpparg0 = arg0;
        FunctorOfVoidFromBool * f = reinterpret_cast<FunctorOfVoidFromBool *>(_state);
        f->func(f->_state, cpparg0);
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromBool_destroy(void * _state)
{
    FunctorOfVoidFromBool * f = reinterpret_cast<FunctorOfVoidFromBool *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromBool FunctorOfVoidFromBool_to_c(FunctorOfVoidFromBool f)
{
    easyar_FunctorOfVoidFromBool _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromBool(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromBool_func;
    _return_value_.destroy = FunctorOfVoidFromBool_destroy;
    return _return_value_;
}
#endif

}

#endif
