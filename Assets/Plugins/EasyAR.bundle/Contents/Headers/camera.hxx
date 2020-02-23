//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CAMERA_HXX__
#define __EASYAR_CAMERA_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// CameraDevice implements a camera device, which outputs `InputFrame`_ (including image, camera paramters, and timestamp). It is available on Windows, Mac, Android and iOS.
/// After open, start/stop can be invoked to start or stop data collection. start/stop will not change previous set camera parameters.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// CameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
class CameraDevice
{
protected:
    easyar_CameraDevice * cdata_ ;
    void init_cdata(easyar_CameraDevice * cdata);
    virtual CameraDevice & operator=(const CameraDevice & data) { return *this; } //deleted
public:
    CameraDevice(easyar_CameraDevice * cdata);
    virtual ~CameraDevice();

    CameraDevice(const CameraDevice & data);
    const easyar_CameraDevice * get_cdata() const;
    easyar_CameraDevice * get_cdata();

    CameraDevice();
    /// <summary>
    /// Checks if the component is available. It returns true only on Windows, Mac, Android or iOS.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Gets current camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
    /// </summary>
    AndroidCameraApiType androidCameraApiType();
    /// <summary>
    /// Sets current camera API (camera1 or camera2) on Android. It must be called before calling openWithIndex, openWithSpecificType or openWithPreferredType, or it will not take effect.
    /// It is recommended to use `CameraDeviceSelector`_ to create camera with camera API set to recommended based on primary algorithm to run.
    /// </summary>
    void setAndroidCameraApiType(AndroidCameraApiType type);
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
    /// Sets callback on state change to notify state of camera disconnection or preemption. It is only available on Windows.
    /// </summary>
    void setStateChangedCallback(CallbackScheduler * callbackScheduler, OptionalOfFunctorOfVoidFromCameraState stateChangedCallback);
    /// <summary>
    /// Requests camera permission from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
    /// </summary>
    static void requestPermissions(CallbackScheduler * callbackScheduler, OptionalOfFunctorOfVoidFromPermissionStatusAndString permissionCallback);
    /// <summary>
    /// Gets count of cameras recognized by the operating system.
    /// </summary>
    static int cameraCount();
    /// <summary>
    /// Opens a camera by index.
    /// </summary>
    bool openWithIndex(int cameraIndex);
    /// <summary>
    /// Opens a camera by specific camera device type. If no camera is matched, false will be returned. On Mac, camera device types can not be distinguished.
    /// </summary>
    bool openWithSpecificType(CameraDeviceType type);
    /// <summary>
    /// Opens a camera by camera device type. If no camera is matched, the first camera will be used.
    /// </summary>
    bool openWithPreferredType(CameraDeviceType type);
    /// <summary>
    /// Starts video stream capture.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops video stream capture. It will only stop capture and will not change previous set camera parameters.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Camera index.
    /// </summary>
    int index();
    /// <summary>
    /// Camera type.
    /// </summary>
    CameraDeviceType type();
    /// <summary>
    /// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation. Call after a successful open.
    /// </summary>
    void cameraParameters(/* OUT */ CameraParameters * * Return);
    /// <summary>
    /// Sets camera parameters. Call after a successful open.
    /// </summary>
    void setCameraParameters(CameraParameters * cameraParameters);
    /// <summary>
    /// Gets the current preview size. Call after a successful open.
    /// </summary>
    Vec2I size();
    /// <summary>
    /// Gets the number of supported preview sizes. Call after a successful open.
    /// </summary>
    int supportedSizeCount();
    /// <summary>
    /// Gets the index-th supported preview size. It returns {0, 0} if index is out of range. Call after a successful open.
    /// </summary>
    Vec2I supportedSize(int index);
    /// <summary>
    /// Sets the preview size. The available nearest value will be selected. Call size to get the actual size. Call after a successful open. frameRateRange may change after calling setSize.
    /// </summary>
    bool setSize(Vec2I size);
    /// <summary>
    /// Gets the number of supported frame rate ranges. Call after a successful open.
    /// </summary>
    int supportedFrameRateRangeCount();
    /// <summary>
    /// Gets range lower bound of the index-th supported frame rate range. Call after a successful open.
    /// </summary>
    float supportedFrameRateRangeLower(int index);
    /// <summary>
    /// Gets range upper bound of the index-th supported frame rate range. Call after a successful open.
    /// </summary>
    float supportedFrameRateRangeUpper(int index);
    /// <summary>
    /// Gets current index of frame rate range. Call after a successful open.
    /// </summary>
    int frameRateRange();
    /// <summary>
    /// Sets current index of frame rate range. Call after a successful open.
    /// </summary>
    bool setFrameRateRange(int index);
    /// <summary>
    /// Sets flash torch mode to on. Call after a successful open.
    /// </summary>
    bool setFlashTorchMode(bool on);
    /// <summary>
    /// Sets focus mode to focusMode. Call after a successful open.
    /// </summary>
    bool setFocusMode(CameraDeviceFocusMode focusMode);
    /// <summary>
    /// Does auto focus once. Call after start. It is only available when FocusMode is Normal or Macro.
    /// </summary>
    bool autoFocus();
};

/// <summary>
/// It is used for selecting camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
/// Different preferences will choose camera1 or camera2 based on usage.
/// </summary>
class CameraDeviceSelector
{
public:
    /// <summary>
    /// Creates `CameraDevice`_ with a specified preference.
    /// </summary>
    static void createCameraDevice(CameraDevicePreference preference, /* OUT */ CameraDevice * * Return);
};

#ifndef __EASYAR_FUNCTOROFVOIDFROMCAMERASTATE__
#define __EASYAR_FUNCTOROFVOIDFROMCAMERASTATE__
struct FunctorOfVoidFromCameraState
{
    void * _state;
    void (* func)(void * _state, CameraState);
    void (* destroy)(void * _state);
    FunctorOfVoidFromCameraState(void * _state, void (* func)(void * _state, CameraState), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromCameraState_func(void * _state, easyar_CameraState, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromCameraState_destroy(void * _state);
static inline easyar_FunctorOfVoidFromCameraState FunctorOfVoidFromCameraState_to_c(FunctorOfVoidFromCameraState f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMCAMERASTATE__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMCAMERASTATE__
struct OptionalOfFunctorOfVoidFromCameraState
{
    bool has_value;
    FunctorOfVoidFromCameraState value;
};
static inline easyar_OptionalOfFunctorOfVoidFromCameraState OptionalOfFunctorOfVoidFromCameraState_to_c(OptionalOfFunctorOfVoidFromCameraState o);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
#define __EASYAR_FUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
struct FunctorOfVoidFromPermissionStatusAndString
{
    void * _state;
    void (* func)(void * _state, PermissionStatus, String *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromPermissionStatusAndString(void * _state, void (* func)(void * _state, PermissionStatus, String *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromPermissionStatusAndString_func(void * _state, easyar_PermissionStatus, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromPermissionStatusAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromPermissionStatusAndString FunctorOfVoidFromPermissionStatusAndString_to_c(FunctorOfVoidFromPermissionStatusAndString f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
struct OptionalOfFunctorOfVoidFromPermissionStatusAndString
{
    bool has_value;
    FunctorOfVoidFromPermissionStatusAndString value;
};
static inline easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString OptionalOfFunctorOfVoidFromPermissionStatusAndString_to_c(OptionalOfFunctorOfVoidFromPermissionStatusAndString o);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_CAMERA_HXX__
#define __IMPLEMENTATION_EASYAR_CAMERA_HXX__

#include "easyar/camera.h"
#include "easyar/dataflow.hxx"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"
#include "easyar/callbackscheduler.hxx"

namespace easyar {

inline CameraDevice::CameraDevice(easyar_CameraDevice * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline CameraDevice::~CameraDevice()
{
    if (cdata_) {
        easyar_CameraDevice__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline CameraDevice::CameraDevice(const CameraDevice & data)
    :
    cdata_(NULL)
{
    easyar_CameraDevice * cdata = NULL;
    easyar_CameraDevice__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_CameraDevice * CameraDevice::get_cdata() const
{
    return cdata_;
}
inline easyar_CameraDevice * CameraDevice::get_cdata()
{
    return cdata_;
}
inline void CameraDevice::init_cdata(easyar_CameraDevice * cdata)
{
    cdata_ = cdata;
}
inline CameraDevice::CameraDevice()
    :
    cdata_(NULL)
{
    easyar_CameraDevice * _return_value_ = NULL;
    easyar_CameraDevice__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline bool CameraDevice::isAvailable()
{
    bool _return_value_ = easyar_CameraDevice_isAvailable();
    return _return_value_;
}
inline AndroidCameraApiType CameraDevice::androidCameraApiType()
{
    if (cdata_ == NULL) {
        return AndroidCameraApiType();
    }
    easyar_AndroidCameraApiType _return_value_ = easyar_CameraDevice_androidCameraApiType(cdata_);
    return static_cast<AndroidCameraApiType>(_return_value_);
}
inline void CameraDevice::setAndroidCameraApiType(AndroidCameraApiType arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CameraDevice_setAndroidCameraApiType(cdata_, static_cast<easyar_AndroidCameraApiType>(arg0));
}
inline int CameraDevice::bufferCapacity()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraDevice_bufferCapacity(cdata_);
    return _return_value_;
}
inline void CameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CameraDevice_setBufferCapacity(cdata_, arg0);
}
inline void CameraDevice::inputFrameSource(/* OUT */ InputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_InputFrameSource * _return_value_ = NULL;
    easyar_CameraDevice_inputFrameSource(cdata_, &_return_value_);
    *Return = new InputFrameSource(_return_value_);
}
inline void CameraDevice::setStateChangedCallback(CallbackScheduler * arg0, OptionalOfFunctorOfVoidFromCameraState arg1)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CameraDevice_setStateChangedCallback(cdata_, arg0->get_cdata(), OptionalOfFunctorOfVoidFromCameraState_to_c(arg1));
}
inline void CameraDevice::requestPermissions(CallbackScheduler * arg0, OptionalOfFunctorOfVoidFromPermissionStatusAndString arg1)
{
    easyar_CameraDevice_requestPermissions(arg0->get_cdata(), OptionalOfFunctorOfVoidFromPermissionStatusAndString_to_c(arg1));
}
inline int CameraDevice::cameraCount()
{
    int _return_value_ = easyar_CameraDevice_cameraCount();
    return _return_value_;
}
inline bool CameraDevice::openWithIndex(int arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_openWithIndex(cdata_, arg0);
    return _return_value_;
}
inline bool CameraDevice::openWithSpecificType(CameraDeviceType arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_openWithSpecificType(cdata_, static_cast<easyar_CameraDeviceType>(arg0));
    return _return_value_;
}
inline bool CameraDevice::openWithPreferredType(CameraDeviceType arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_openWithPreferredType(cdata_, static_cast<easyar_CameraDeviceType>(arg0));
    return _return_value_;
}
inline bool CameraDevice::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_start(cdata_);
    return _return_value_;
}
inline void CameraDevice::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CameraDevice_stop(cdata_);
}
inline void CameraDevice::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CameraDevice_close(cdata_);
}
inline int CameraDevice::index()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraDevice_index(cdata_);
    return _return_value_;
}
inline CameraDeviceType CameraDevice::type()
{
    if (cdata_ == NULL) {
        return CameraDeviceType();
    }
    easyar_CameraDeviceType _return_value_ = easyar_CameraDevice_type(cdata_);
    return static_cast<CameraDeviceType>(_return_value_);
}
inline void CameraDevice::cameraParameters(/* OUT */ CameraParameters * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_CameraParameters * _return_value_ = NULL;
    easyar_CameraDevice_cameraParameters(cdata_, &_return_value_);
    *Return = new CameraParameters(_return_value_);
}
inline void CameraDevice::setCameraParameters(CameraParameters * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CameraDevice_setCameraParameters(cdata_, arg0->get_cdata());
}
inline Vec2I CameraDevice::size()
{
    if (cdata_ == NULL) {
        return Vec2I();
    }
    easyar_Vec2I _return_value_ = easyar_CameraDevice_size(cdata_);
    return Vec2I(_return_value_.data[0], _return_value_.data[1]);
}
inline int CameraDevice::supportedSizeCount()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraDevice_supportedSizeCount(cdata_);
    return _return_value_;
}
inline Vec2I CameraDevice::supportedSize(int arg0)
{
    if (cdata_ == NULL) {
        return Vec2I();
    }
    easyar_Vec2I _return_value_ = easyar_CameraDevice_supportedSize(cdata_, arg0);
    return Vec2I(_return_value_.data[0], _return_value_.data[1]);
}
inline bool CameraDevice::setSize(Vec2I arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_setSize(cdata_, arg0.get_cdata());
    return _return_value_;
}
inline int CameraDevice::supportedFrameRateRangeCount()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraDevice_supportedFrameRateRangeCount(cdata_);
    return _return_value_;
}
inline float CameraDevice::supportedFrameRateRangeLower(int arg0)
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_CameraDevice_supportedFrameRateRangeLower(cdata_, arg0);
    return _return_value_;
}
inline float CameraDevice::supportedFrameRateRangeUpper(int arg0)
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_CameraDevice_supportedFrameRateRangeUpper(cdata_, arg0);
    return _return_value_;
}
inline int CameraDevice::frameRateRange()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_CameraDevice_frameRateRange(cdata_);
    return _return_value_;
}
inline bool CameraDevice::setFrameRateRange(int arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_setFrameRateRange(cdata_, arg0);
    return _return_value_;
}
inline bool CameraDevice::setFlashTorchMode(bool arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_setFlashTorchMode(cdata_, arg0);
    return _return_value_;
}
inline bool CameraDevice::setFocusMode(CameraDeviceFocusMode arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_setFocusMode(cdata_, static_cast<easyar_CameraDeviceFocusMode>(arg0));
    return _return_value_;
}
inline bool CameraDevice::autoFocus()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_CameraDevice_autoFocus(cdata_);
    return _return_value_;
}

inline void CameraDeviceSelector::createCameraDevice(CameraDevicePreference arg0, /* OUT */ CameraDevice * * Return)
{
    easyar_CameraDevice * _return_value_ = NULL;
    easyar_CameraDeviceSelector_createCameraDevice(static_cast<easyar_CameraDevicePreference>(arg0), &_return_value_);
    *Return = new CameraDevice(_return_value_);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMCAMERASTATE__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMCAMERASTATE__
static inline easyar_OptionalOfFunctorOfVoidFromCameraState OptionalOfFunctorOfVoidFromCameraState_to_c(OptionalOfFunctorOfVoidFromCameraState o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromCameraState _return_value_ = {true, FunctorOfVoidFromCameraState_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromCameraState _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMCAMERASTATE__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMCAMERASTATE__
inline FunctorOfVoidFromCameraState::FunctorOfVoidFromCameraState(void * _state, void (* func)(void * _state, CameraState), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromCameraState_func(void * _state, easyar_CameraState arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        CameraState cpparg0 = static_cast<CameraState>(arg0);
        FunctorOfVoidFromCameraState * f = reinterpret_cast<FunctorOfVoidFromCameraState *>(_state);
        f->func(f->_state, cpparg0);
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromCameraState_destroy(void * _state)
{
    FunctorOfVoidFromCameraState * f = reinterpret_cast<FunctorOfVoidFromCameraState *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromCameraState FunctorOfVoidFromCameraState_to_c(FunctorOfVoidFromCameraState f)
{
    easyar_FunctorOfVoidFromCameraState _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromCameraState(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromCameraState_func;
    _return_value_.destroy = FunctorOfVoidFromCameraState_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
static inline easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString OptionalOfFunctorOfVoidFromPermissionStatusAndString_to_c(OptionalOfFunctorOfVoidFromPermissionStatusAndString o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString _return_value_ = {true, FunctorOfVoidFromPermissionStatusAndString_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMPERMISSIONSTATUSANDSTRING__
inline FunctorOfVoidFromPermissionStatusAndString::FunctorOfVoidFromPermissionStatusAndString(void * _state, void (* func)(void * _state, PermissionStatus, String *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromPermissionStatusAndString_func(void * _state, easyar_PermissionStatus arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        PermissionStatus cpparg0 = static_cast<PermissionStatus>(arg0);
        easyar_String_copy(arg1, &arg1);
        String * cpparg1 = new String(arg1);
        FunctorOfVoidFromPermissionStatusAndString * f = reinterpret_cast<FunctorOfVoidFromPermissionStatusAndString *>(_state);
        f->func(f->_state, cpparg0, cpparg1);
        delete cpparg1;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromPermissionStatusAndString_destroy(void * _state)
{
    FunctorOfVoidFromPermissionStatusAndString * f = reinterpret_cast<FunctorOfVoidFromPermissionStatusAndString *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromPermissionStatusAndString FunctorOfVoidFromPermissionStatusAndString_to_c(FunctorOfVoidFromPermissionStatusAndString f)
{
    easyar_FunctorOfVoidFromPermissionStatusAndString _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromPermissionStatusAndString(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromPermissionStatusAndString_func;
    _return_value_.destroy = FunctorOfVoidFromPermissionStatusAndString_destroy;
    return _return_value_;
}
#endif

}

#endif
