//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SURFACETRACKER_HXX__
#define __EASYAR_SURFACETRACKER_HXX__

#include "easyar/types.hxx"
#include "easyar/frame.hxx"

namespace easyar {

/// <summary>
/// Result of `SurfaceTracker`_ .
/// </summary>
class SurfaceTrackerResult : public FrameFilterResult
{
protected:
    easyar_SurfaceTrackerResult * cdata_ ;
    void init_cdata(easyar_SurfaceTrackerResult * cdata);
    virtual SurfaceTrackerResult & operator=(const SurfaceTrackerResult & data) { return *this; } //deleted
public:
    SurfaceTrackerResult(easyar_SurfaceTrackerResult * cdata);
    virtual ~SurfaceTrackerResult();

    SurfaceTrackerResult(const SurfaceTrackerResult & data);
    const easyar_SurfaceTrackerResult * get_cdata() const;
    easyar_SurfaceTrackerResult * get_cdata();

    /// <summary>
    /// Camera transform against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) For the world coordinate system, y is up (to the opposite of gravity). The data arrangement is row-major, not like OpenGL&#39;s column-major.
    /// </summary>
    Matrix44F transform();
    static void tryCastFromFrameFilterResult(FrameFilterResult * v, /* OUT */ SurfaceTrackerResult * * Return);
};

/// <summary>
/// SurfaceTracker implements tracking with environmental surfaces.
/// SurfaceTracker occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// SurfaceTracker inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
class SurfaceTracker
{
protected:
    easyar_SurfaceTracker * cdata_ ;
    void init_cdata(easyar_SurfaceTracker * cdata);
    virtual SurfaceTracker & operator=(const SurfaceTracker & data) { return *this; } //deleted
public:
    SurfaceTracker(easyar_SurfaceTracker * cdata);
    virtual ~SurfaceTracker();

    SurfaceTracker(const SurfaceTracker & data);
    const easyar_SurfaceTracker * get_cdata() const;
    easyar_SurfaceTracker * get_cdata();

    /// <summary>
    /// Returns true only on Android or iOS when accelerometer and gyroscope are available.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `InputFrame`_ input port. InputFrame must have raw image, timestamp, and camera parameters.
    /// </summary>
    void inputFrameSink(/* OUT */ InputFrameSink * * Return);
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// `OutputFrame`_ output port.
    /// </summary>
    void outputFrameSource(/* OUT */ OutputFrameSource * * Return);
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(/* OUT */ SurfaceTracker * * Return);
    /// <summary>
    /// Starts the track algorithm.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops the track algorithm. Call start to start the track again.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Sets the tracking target to a point on camera image. For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// </summary>
    void alignTargetToCameraImagePoint(Vec2F cameraImagePoint);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_SURFACETRACKER_HXX__
#define __IMPLEMENTATION_EASYAR_SURFACETRACKER_HXX__

#include "easyar/surfacetracker.h"
#include "easyar/frame.hxx"
#include "easyar/matrix.hxx"
#include "easyar/dataflow.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"

namespace easyar {

inline SurfaceTrackerResult::SurfaceTrackerResult(easyar_SurfaceTrackerResult * cdata)
    :
    FrameFilterResult(static_cast<easyar_FrameFilterResult *>(NULL)),
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SurfaceTrackerResult::~SurfaceTrackerResult()
{
    if (cdata_) {
        easyar_SurfaceTrackerResult__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SurfaceTrackerResult::SurfaceTrackerResult(const SurfaceTrackerResult & data)
    :
    FrameFilterResult(static_cast<easyar_FrameFilterResult *>(NULL)),
    cdata_(NULL)
{
    easyar_SurfaceTrackerResult * cdata = NULL;
    easyar_SurfaceTrackerResult__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SurfaceTrackerResult * SurfaceTrackerResult::get_cdata() const
{
    return cdata_;
}
inline easyar_SurfaceTrackerResult * SurfaceTrackerResult::get_cdata()
{
    return cdata_;
}
inline void SurfaceTrackerResult::init_cdata(easyar_SurfaceTrackerResult * cdata)
{
    cdata_ = cdata;
    {
        easyar_FrameFilterResult * cdata_inner = NULL;
        easyar_castSurfaceTrackerResultToFrameFilterResult(cdata, &cdata_inner);
        FrameFilterResult::init_cdata(cdata_inner);
    }
}
inline Matrix44F SurfaceTrackerResult::transform()
{
    if (cdata_ == NULL) {
        return Matrix44F();
    }
    easyar_Matrix44F _return_value_ = easyar_SurfaceTrackerResult_transform(cdata_);
    return Matrix44F(_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]);
}
inline void SurfaceTrackerResult::tryCastFromFrameFilterResult(FrameFilterResult * v, /* OUT */ SurfaceTrackerResult * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_SurfaceTrackerResult * cdata = NULL;
    easyar_tryCastFrameFilterResultToSurfaceTrackerResult(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new SurfaceTrackerResult(cdata);
}

inline SurfaceTracker::SurfaceTracker(easyar_SurfaceTracker * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SurfaceTracker::~SurfaceTracker()
{
    if (cdata_) {
        easyar_SurfaceTracker__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SurfaceTracker::SurfaceTracker(const SurfaceTracker & data)
    :
    cdata_(NULL)
{
    easyar_SurfaceTracker * cdata = NULL;
    easyar_SurfaceTracker__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SurfaceTracker * SurfaceTracker::get_cdata() const
{
    return cdata_;
}
inline easyar_SurfaceTracker * SurfaceTracker::get_cdata()
{
    return cdata_;
}
inline void SurfaceTracker::init_cdata(easyar_SurfaceTracker * cdata)
{
    cdata_ = cdata;
}
inline bool SurfaceTracker::isAvailable()
{
    bool _return_value_ = easyar_SurfaceTracker_isAvailable();
    return _return_value_;
}
inline void SurfaceTracker::inputFrameSink(/* OUT */ InputFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSink * _return_value_ = NULL;
    easyar_SurfaceTracker_inputFrameSink(cdata_, &_return_value_);
    *Return = new InputFrameSink(_return_value_);
}
inline int SurfaceTracker::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_SurfaceTracker_bufferRequirement(cdata_);
    return _return_value_;
}
inline void SurfaceTracker::outputFrameSource(/* OUT */ OutputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSource * _return_value_ = NULL;
    easyar_SurfaceTracker_outputFrameSource(cdata_, &_return_value_);
    *Return = new OutputFrameSource(_return_value_);
}
inline void SurfaceTracker::create(/* OUT */ SurfaceTracker * * Return)
{
    easyar_SurfaceTracker * _return_value_ = NULL;
    easyar_SurfaceTracker_create(&_return_value_);
    *Return = new SurfaceTracker(_return_value_);
}
inline bool SurfaceTracker::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_SurfaceTracker_start(cdata_);
    return _return_value_;
}
inline void SurfaceTracker::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SurfaceTracker_stop(cdata_);
}
inline void SurfaceTracker::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SurfaceTracker_close(cdata_);
}
inline void SurfaceTracker::alignTargetToCameraImagePoint(Vec2F arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SurfaceTracker_alignTargetToCameraImagePoint(cdata_, arg0.get_cdata());
}

}

#endif
