//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_MOTIONTRACKER_HXX__
#define __EASYAR_MOTIONTRACKER_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// MotionTrackerCameraDevice implements a camera device with metric-scale six degree-of-freedom motion tracking, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF pose and tracking status).
/// After creation, start/stop can be invoked to start or stop data flow.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// MotionTrackerCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for further use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
class MotionTrackerCameraDevice
{
protected:
    easyar_MotionTrackerCameraDevice * cdata_ ;
    void init_cdata(easyar_MotionTrackerCameraDevice * cdata);
    virtual MotionTrackerCameraDevice & operator=(const MotionTrackerCameraDevice & data) { return *this; } //deleted
public:
    MotionTrackerCameraDevice(easyar_MotionTrackerCameraDevice * cdata);
    virtual ~MotionTrackerCameraDevice();

    MotionTrackerCameraDevice(const MotionTrackerCameraDevice & data);
    const easyar_MotionTrackerCameraDevice * get_cdata() const;
    easyar_MotionTrackerCameraDevice * get_cdata();

    /// <summary>
    /// Create MotionTrackerCameraDevice object.
    /// </summary>
    MotionTrackerCameraDevice();
    /// <summary>
    /// Check if the devices supports motion tracking. Returns True if the device supports Motion Tracking, otherwise returns False.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Set `InputFrame`_ buffer capacity.
    /// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is higher than this number, the device will not output new `InputFrame`_ until previous `InputFrame`_ has been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
    /// </summary>
    void setBufferCapacity(int capacity);
    /// <summary>
    /// Get `InputFrame`_ buffer capacity. The default is 8.
    /// </summary>
    int bufferCapacity();
    /// <summary>
    /// `InputFrame`_ output port.
    /// </summary>
    void inputFrameSource(/* OUT */ InputFrameSource * * Return);
    /// <summary>
    /// Start motion tracking or resume motion tracking after pause.
    /// Notice: Calling start after pausing will trigger device relocalization. Tracking will resume when the relocalization process succeeds.
    /// </summary>
    bool start();
    /// <summary>
    /// Pause motion tracking. Call `start` to trigger relocation, resume motion tracking if the relocation succeeds.
    /// </summary>
    void stop();
    /// <summary>
    /// Close motion tracking. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Perform hit test against the point cloud and return the nearest 3D point. The 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
    /// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// </summary>
    void hitTestAgainstPointCloud(Vec2F cameraImagePoint, /* OUT */ ListOfVec3F * * Return);
    /// <summary>
    /// Performs ray cast from the user&#39;s device in the direction of given screen point.
    /// Intersections with horizontal plane is detected in real time in the current field of view,and return the 3D point nearest to ray on horizontal plane.
    /// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// The output point cloud coordinate on Horizontal plane is in the world coordinate system. The 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
    /// </summary>
    void hitTestAgainstHorizontalPlane(Vec2F cameraImagePoint, /* OUT */ ListOfVec3F * * Return);
    /// <summary>
    /// Returns the vector of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
    /// </summary>
    void getLocalPointsCloud(/* OUT */ ListOfVec3F * * Return);
};

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

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_MOTIONTRACKER_HXX__
#define __IMPLEMENTATION_EASYAR_MOTIONTRACKER_HXX__

#include "easyar/motiontracker.h"
#include "easyar/dataflow.hxx"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"

namespace easyar {

inline MotionTrackerCameraDevice::MotionTrackerCameraDevice(easyar_MotionTrackerCameraDevice * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline MotionTrackerCameraDevice::~MotionTrackerCameraDevice()
{
    if (cdata_) {
        easyar_MotionTrackerCameraDevice__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline MotionTrackerCameraDevice::MotionTrackerCameraDevice(const MotionTrackerCameraDevice & data)
    :
    cdata_(NULL)
{
    easyar_MotionTrackerCameraDevice * cdata = NULL;
    easyar_MotionTrackerCameraDevice__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_MotionTrackerCameraDevice * MotionTrackerCameraDevice::get_cdata() const
{
    return cdata_;
}
inline easyar_MotionTrackerCameraDevice * MotionTrackerCameraDevice::get_cdata()
{
    return cdata_;
}
inline void MotionTrackerCameraDevice::init_cdata(easyar_MotionTrackerCameraDevice * cdata)
{
    cdata_ = cdata;
}
inline MotionTrackerCameraDevice::MotionTrackerCameraDevice()
    :
    cdata_(NULL)
{
    easyar_MotionTrackerCameraDevice * _return_value_ = NULL;
    easyar_MotionTrackerCameraDevice__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline bool MotionTrackerCameraDevice::isAvailable()
{
    bool _return_value_ = easyar_MotionTrackerCameraDevice_isAvailable();
    return _return_value_;
}
inline void MotionTrackerCameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_MotionTrackerCameraDevice_setBufferCapacity(cdata_, arg0);
}
inline int MotionTrackerCameraDevice::bufferCapacity()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_MotionTrackerCameraDevice_bufferCapacity(cdata_);
    return _return_value_;
}
inline void MotionTrackerCameraDevice::inputFrameSource(/* OUT */ InputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSource * _return_value_ = NULL;
    easyar_MotionTrackerCameraDevice_inputFrameSource(cdata_, &_return_value_);
    *Return = new InputFrameSource(_return_value_);
}
inline bool MotionTrackerCameraDevice::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_MotionTrackerCameraDevice_start(cdata_);
    return _return_value_;
}
inline void MotionTrackerCameraDevice::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_MotionTrackerCameraDevice_stop(cdata_);
}
inline void MotionTrackerCameraDevice::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_MotionTrackerCameraDevice_close(cdata_);
}
inline void MotionTrackerCameraDevice::hitTestAgainstPointCloud(Vec2F arg0, /* OUT */ ListOfVec3F * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfVec3F * _return_value_ = NULL;
    easyar_MotionTrackerCameraDevice_hitTestAgainstPointCloud(cdata_, arg0.get_cdata(), &_return_value_);
    *Return = new ListOfVec3F(_return_value_);
}
inline void MotionTrackerCameraDevice::hitTestAgainstHorizontalPlane(Vec2F arg0, /* OUT */ ListOfVec3F * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfVec3F * _return_value_ = NULL;
    easyar_MotionTrackerCameraDevice_hitTestAgainstHorizontalPlane(cdata_, arg0.get_cdata(), &_return_value_);
    *Return = new ListOfVec3F(_return_value_);
}
inline void MotionTrackerCameraDevice::getLocalPointsCloud(/* OUT */ ListOfVec3F * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfVec3F * _return_value_ = NULL;
    easyar_MotionTrackerCameraDevice_getLocalPointsCloud(cdata_, &_return_value_);
    *Return = new ListOfVec3F(_return_value_);
}

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

}

#endif
