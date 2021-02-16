//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_ARCORECAMERA_HXX__
#define __EASYAR_ARCORECAMERA_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// ARCoreCameraDevice implements a camera device based on ARCore, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// Loading of libarcore_sdk_c.so with java.lang.System.loadLibrary is required.
/// After creation, start/stop can be invoked to start or stop video stream capture.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARCoreCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
/// Caution: Currently, ARCore(v1.13.0) has memory leaks on creating and destroying sessions. Repeated creations and destructions will cause an increasing and non-reclaimable memory footprint.
/// </summary>
class ARCoreCameraDevice
{
protected:
    easyar_ARCoreCameraDevice * cdata_ ;
    void init_cdata(easyar_ARCoreCameraDevice * cdata);
    virtual ARCoreCameraDevice & operator=(const ARCoreCameraDevice & data) { return *this; } //deleted
public:
    ARCoreCameraDevice(easyar_ARCoreCameraDevice * cdata);
    virtual ~ARCoreCameraDevice();

    ARCoreCameraDevice(const ARCoreCameraDevice & data);
    const easyar_ARCoreCameraDevice * get_cdata() const;
    easyar_ARCoreCameraDevice * get_cdata();

    ARCoreCameraDevice();
    /// <summary>
    /// Checks if the component is available. It returns true only on Android when ARCore is installed.
    /// If called with libarcore_sdk_c.so not loaded, it returns false.
    /// Notice: If ARCore is not supported on the device but ARCore apk is installed via side-loading, it will return true, but ARCore will not function properly.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `InputFrame`_ buffer capacity. The default is 8.
    /// </summary>
    int bufferCapacity();
    /// <summary>
    /// Sets `InputFrame`_ buffer capacity.
    /// </summary>
    void setBufferCapacity(int capacity);
    /// <summary>
    /// `InputFrame`_ output port.
    /// </summary>
    void inputFrameSource(/* OUT */ InputFrameSource * * Return);
    /// <summary>
    /// Starts video stream capture.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops video stream capture.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_ARCORECAMERA_HXX__
#define __IMPLEMENTATION_EASYAR_ARCORECAMERA_HXX__

#include "easyar/arcorecamera.h"
#include "easyar/dataflow.hxx"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"

namespace easyar {

inline ARCoreCameraDevice::ARCoreCameraDevice(easyar_ARCoreCameraDevice * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ARCoreCameraDevice::~ARCoreCameraDevice()
{
    if (cdata_) {
        easyar_ARCoreCameraDevice__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ARCoreCameraDevice::ARCoreCameraDevice(const ARCoreCameraDevice & data)
    :
    cdata_(NULL)
{
    easyar_ARCoreCameraDevice * cdata = NULL;
    easyar_ARCoreCameraDevice__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ARCoreCameraDevice * ARCoreCameraDevice::get_cdata() const
{
    return cdata_;
}
inline easyar_ARCoreCameraDevice * ARCoreCameraDevice::get_cdata()
{
    return cdata_;
}
inline void ARCoreCameraDevice::init_cdata(easyar_ARCoreCameraDevice * cdata)
{
    cdata_ = cdata;
}
inline ARCoreCameraDevice::ARCoreCameraDevice()
    :
    cdata_(NULL)
{
    easyar_ARCoreCameraDevice * _return_value_ = NULL;
    easyar_ARCoreCameraDevice__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline bool ARCoreCameraDevice::isAvailable()
{
    bool _return_value_ = easyar_ARCoreCameraDevice_isAvailable();
    return _return_value_;
}
inline int ARCoreCameraDevice::bufferCapacity()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_ARCoreCameraDevice_bufferCapacity(cdata_);
    return _return_value_;
}
inline void ARCoreCameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ARCoreCameraDevice_setBufferCapacity(cdata_, arg0);
}
inline void ARCoreCameraDevice::inputFrameSource(/* OUT */ InputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSource * _return_value_ = NULL;
    easyar_ARCoreCameraDevice_inputFrameSource(cdata_, &_return_value_);
    *Return = new InputFrameSource(_return_value_);
}
inline bool ARCoreCameraDevice::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_ARCoreCameraDevice_start(cdata_);
    return _return_value_;
}
inline void ARCoreCameraDevice::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ARCoreCameraDevice_stop(cdata_);
}
inline void ARCoreCameraDevice::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ARCoreCameraDevice_close(cdata_);
}

}

#endif
