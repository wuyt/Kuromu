//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_ARKITCAMERA_HXX__
#define __EASYAR_ARKITCAMERA_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// ARKitCameraDevice implements a camera device based on ARKit, which outputs `InputFrame`_ (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// After creation, start/stop can be invoked to start or stop data collection.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARKitCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
class ARKitCameraDevice
{
protected:
    easyar_ARKitCameraDevice * cdata_ ;
    void init_cdata(easyar_ARKitCameraDevice * cdata);
    virtual ARKitCameraDevice & operator=(const ARKitCameraDevice & data) { return *this; } //deleted
public:
    ARKitCameraDevice(easyar_ARKitCameraDevice * cdata);
    virtual ~ARKitCameraDevice();

    ARKitCameraDevice(const ARKitCameraDevice & data);
    const easyar_ARKitCameraDevice * get_cdata() const;
    easyar_ARKitCameraDevice * get_cdata();

    ARKitCameraDevice();
    /// <summary>
    /// Checks if the component is available. It returns true only on iOS 11 or later when ARKit is supported by hardware.
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

#ifndef __IMPLEMENTATION_EASYAR_ARKITCAMERA_HXX__
#define __IMPLEMENTATION_EASYAR_ARKITCAMERA_HXX__

#include "easyar/arkitcamera.h"
#include "easyar/dataflow.hxx"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"

namespace easyar {

inline ARKitCameraDevice::ARKitCameraDevice(easyar_ARKitCameraDevice * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ARKitCameraDevice::~ARKitCameraDevice()
{
    if (cdata_) {
        easyar_ARKitCameraDevice__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ARKitCameraDevice::ARKitCameraDevice(const ARKitCameraDevice & data)
    :
    cdata_(NULL)
{
    easyar_ARKitCameraDevice * cdata = NULL;
    easyar_ARKitCameraDevice__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ARKitCameraDevice * ARKitCameraDevice::get_cdata() const
{
    return cdata_;
}
inline easyar_ARKitCameraDevice * ARKitCameraDevice::get_cdata()
{
    return cdata_;
}
inline void ARKitCameraDevice::init_cdata(easyar_ARKitCameraDevice * cdata)
{
    cdata_ = cdata;
}
inline ARKitCameraDevice::ARKitCameraDevice()
    :
    cdata_(NULL)
{
    easyar_ARKitCameraDevice * _return_value_ = NULL;
    easyar_ARKitCameraDevice__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline bool ARKitCameraDevice::isAvailable()
{
    bool _return_value_ = easyar_ARKitCameraDevice_isAvailable();
    return _return_value_;
}
inline int ARKitCameraDevice::bufferCapacity()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_ARKitCameraDevice_bufferCapacity(cdata_);
    return _return_value_;
}
inline void ARKitCameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ARKitCameraDevice_setBufferCapacity(cdata_, arg0);
}
inline void ARKitCameraDevice::inputFrameSource(/* OUT */ InputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSource * _return_value_ = NULL;
    easyar_ARKitCameraDevice_inputFrameSource(cdata_, &_return_value_);
    *Return = new InputFrameSource(_return_value_);
}
inline bool ARKitCameraDevice::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_ARKitCameraDevice_start(cdata_);
    return _return_value_;
}
inline void ARKitCameraDevice::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ARKitCameraDevice_stop(cdata_);
}
inline void ARKitCameraDevice::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ARKitCameraDevice_close(cdata_);
}

}

#endif
