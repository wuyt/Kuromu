//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CLOUDRECOGNIZER_HXX__
#define __EASYAR_CLOUDRECOGNIZER_HXX__

#include "easyar/types.hxx"

namespace easyar {

class CloudRecognizationResult
{
protected:
    easyar_CloudRecognizationResult * cdata_ ;
    void init_cdata(easyar_CloudRecognizationResult * cdata);
    virtual CloudRecognizationResult & operator=(const CloudRecognizationResult & data) { return *this; } //deleted
public:
    CloudRecognizationResult(easyar_CloudRecognizationResult * cdata);
    virtual ~CloudRecognizationResult();

    CloudRecognizationResult(const CloudRecognizationResult & data);
    const easyar_CloudRecognizationResult * get_cdata() const;
    easyar_CloudRecognizationResult * get_cdata();

    /// <summary>
    /// Returns recognition status.
    /// </summary>
    CloudRecognizationStatus getStatus();
    /// <summary>
    /// Returns the recognized target when status is FoundTarget.
    /// </summary>
    void getTarget(/* OUT */ ImageTarget * * Return);
    /// <summary>
    /// Returns the error message when status is UnknownError.
    /// </summary>
    void getUnknownErrorMessage(/* OUT */ String * * Return);
};

/// <summary>
/// CloudRecognizer implements cloud recognition. It can only be used after created a recognition image library on the cloud. Please refer to EasyAR CRS documentation.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// Before using a CloudRecognizer, an `ImageTracker`_ must be setup and prepared. Any target returned from cloud should be manually put into the `ImageTracker`_ using `ImageTracker.loadTarget`_ if it need to be tracked. Then the target can be used as same as a local target after loaded into the tracker. When a target is recognized, you can get it from callback, and you should use target uid to distinguish different targets. The target runtimeID is dynamically created and cannot be used as unique identifier in the cloud situation.
/// </summary>
class CloudRecognizer
{
protected:
    easyar_CloudRecognizer * cdata_ ;
    void init_cdata(easyar_CloudRecognizer * cdata);
    virtual CloudRecognizer & operator=(const CloudRecognizer & data) { return *this; } //deleted
public:
    CloudRecognizer(easyar_CloudRecognizer * cdata);
    virtual ~CloudRecognizer();

    CloudRecognizer(const CloudRecognizer & data);
    const easyar_CloudRecognizer * get_cdata() const;
    easyar_CloudRecognizer * get_cdata();

    /// <summary>
    /// Returns true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Creates an instance and connects to the server.
    /// </summary>
    static void create(String * cloudRecognitionServiceServerAddress, String * apiKey, String * apiSecret, String * cloudRecognitionServiceAppId, /* OUT */ CloudRecognizer * * Return);
    /// <summary>
    /// Creates an instance and connects to the server with Cloud Secret.
    /// </summary>
    static void createByCloudSecret(String * cloudRecognitionServiceServerAddress, String * cloudRecognitionServiceSecret, String * cloudRecognitionServiceAppId, /* OUT */ CloudRecognizer * * Return);
    /// <summary>
    /// Send recognition request. The lowest available request interval is 300ms.
    /// </summary>
    void resolve(InputFrame * inputFrame, CallbackScheduler * callbackScheduler, FunctorOfVoidFromCloudRecognizationResult callback);
    /// <summary>
    /// Stops the recognition and closes connection. The component shall not be used after calling close.
    /// </summary>
    void close();
};

#ifndef __EASYAR_OPTIONALOFIMAGETARGET__
#define __EASYAR_OPTIONALOFIMAGETARGET__
struct OptionalOfImageTarget
{
    bool has_value;
    ImageTarget * value;
};
static inline easyar_OptionalOfImageTarget OptionalOfImageTarget_to_c(ImageTarget * o);
#endif

#ifndef __EASYAR_OPTIONALOFSTRING__
#define __EASYAR_OPTIONALOFSTRING__
struct OptionalOfString
{
    bool has_value;
    String * value;
};
static inline easyar_OptionalOfString OptionalOfString_to_c(String * o);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMCLOUDRECOGNIZATIONRESULT__
#define __EASYAR_FUNCTOROFVOIDFROMCLOUDRECOGNIZATIONRESULT__
struct FunctorOfVoidFromCloudRecognizationResult
{
    void * _state;
    void (* func)(void * _state, CloudRecognizationResult *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromCloudRecognizationResult(void * _state, void (* func)(void * _state, CloudRecognizationResult *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromCloudRecognizationResult_func(void * _state, easyar_CloudRecognizationResult *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromCloudRecognizationResult_destroy(void * _state);
static inline easyar_FunctorOfVoidFromCloudRecognizationResult FunctorOfVoidFromCloudRecognizationResult_to_c(FunctorOfVoidFromCloudRecognizationResult f);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_CLOUDRECOGNIZER_HXX__
#define __IMPLEMENTATION_EASYAR_CLOUDRECOGNIZER_HXX__

#include "easyar/cloudrecognizer.h"
#include "easyar/imagetarget.hxx"
#include "easyar/target.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/frame.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"
#include "easyar/callbackscheduler.hxx"

namespace easyar {

inline CloudRecognizationResult::CloudRecognizationResult(easyar_CloudRecognizationResult * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline CloudRecognizationResult::~CloudRecognizationResult()
{
    if (cdata_) {
        easyar_CloudRecognizationResult__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline CloudRecognizationResult::CloudRecognizationResult(const CloudRecognizationResult & data)
    :
    cdata_(NULL)
{
    easyar_CloudRecognizationResult * cdata = NULL;
    easyar_CloudRecognizationResult__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_CloudRecognizationResult * CloudRecognizationResult::get_cdata() const
{
    return cdata_;
}
inline easyar_CloudRecognizationResult * CloudRecognizationResult::get_cdata()
{
    return cdata_;
}
inline void CloudRecognizationResult::init_cdata(easyar_CloudRecognizationResult * cdata)
{
    cdata_ = cdata;
}
inline CloudRecognizationStatus CloudRecognizationResult::getStatus()
{
    if (cdata_ == NULL) {
        return CloudRecognizationStatus();
    }
    easyar_CloudRecognizationStatus _return_value_ = easyar_CloudRecognizationResult_getStatus(cdata_);
    return static_cast<CloudRecognizationStatus>(_return_value_);
}
inline void CloudRecognizationResult::getTarget(/* OUT */ ImageTarget * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OptionalOfImageTarget _return_value_ = {false, NULL};
    easyar_CloudRecognizationResult_getTarget(cdata_, &_return_value_);
    *Return = (_return_value_.has_value ? new ImageTarget(_return_value_.value) : NULL);
}
inline void CloudRecognizationResult::getUnknownErrorMessage(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OptionalOfString _return_value_ = {false, NULL};
    easyar_CloudRecognizationResult_getUnknownErrorMessage(cdata_, &_return_value_);
    *Return = (_return_value_.has_value ? new String(_return_value_.value) : NULL);
}

inline CloudRecognizer::CloudRecognizer(easyar_CloudRecognizer * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline CloudRecognizer::~CloudRecognizer()
{
    if (cdata_) {
        easyar_CloudRecognizer__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline CloudRecognizer::CloudRecognizer(const CloudRecognizer & data)
    :
    cdata_(NULL)
{
    easyar_CloudRecognizer * cdata = NULL;
    easyar_CloudRecognizer__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_CloudRecognizer * CloudRecognizer::get_cdata() const
{
    return cdata_;
}
inline easyar_CloudRecognizer * CloudRecognizer::get_cdata()
{
    return cdata_;
}
inline void CloudRecognizer::init_cdata(easyar_CloudRecognizer * cdata)
{
    cdata_ = cdata;
}
inline bool CloudRecognizer::isAvailable()
{
    bool _return_value_ = easyar_CloudRecognizer_isAvailable();
    return _return_value_;
}
inline void CloudRecognizer::create(String * arg0, String * arg1, String * arg2, String * arg3, /* OUT */ CloudRecognizer * * Return)
{
    easyar_CloudRecognizer * _return_value_ = NULL;
    easyar_CloudRecognizer_create(arg0->get_cdata(), arg1->get_cdata(), arg2->get_cdata(), arg3->get_cdata(), &_return_value_);
    *Return = new CloudRecognizer(_return_value_);
}
inline void CloudRecognizer::createByCloudSecret(String * arg0, String * arg1, String * arg2, /* OUT */ CloudRecognizer * * Return)
{
    easyar_CloudRecognizer * _return_value_ = NULL;
    easyar_CloudRecognizer_createByCloudSecret(arg0->get_cdata(), arg1->get_cdata(), arg2->get_cdata(), &_return_value_);
    *Return = new CloudRecognizer(_return_value_);
}
inline void CloudRecognizer::resolve(InputFrame * arg0, CallbackScheduler * arg1, FunctorOfVoidFromCloudRecognizationResult arg2)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CloudRecognizer_resolve(cdata_, arg0->get_cdata(), arg1->get_cdata(), FunctorOfVoidFromCloudRecognizationResult_to_c(arg2));
}
inline void CloudRecognizer::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_CloudRecognizer_close(cdata_);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFIMAGETARGET__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFIMAGETARGET__
static inline easyar_OptionalOfImageTarget OptionalOfImageTarget_to_c(ImageTarget * o)
{
    if (o != NULL) {
        easyar_OptionalOfImageTarget _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfImageTarget _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFSTRING__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFSTRING__
static inline easyar_OptionalOfString OptionalOfString_to_c(String * o)
{
    if (o != NULL) {
        easyar_OptionalOfString _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfString _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMCLOUDRECOGNIZATIONRESULT__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMCLOUDRECOGNIZATIONRESULT__
inline FunctorOfVoidFromCloudRecognizationResult::FunctorOfVoidFromCloudRecognizationResult(void * _state, void (* func)(void * _state, CloudRecognizationResult *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromCloudRecognizationResult_func(void * _state, easyar_CloudRecognizationResult * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        easyar_CloudRecognizationResult__retain(arg0, &arg0);
        CloudRecognizationResult * cpparg0 = new CloudRecognizationResult(arg0);
        FunctorOfVoidFromCloudRecognizationResult * f = reinterpret_cast<FunctorOfVoidFromCloudRecognizationResult *>(_state);
        f->func(f->_state, cpparg0);
        delete cpparg0;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromCloudRecognizationResult_destroy(void * _state)
{
    FunctorOfVoidFromCloudRecognizationResult * f = reinterpret_cast<FunctorOfVoidFromCloudRecognizationResult *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromCloudRecognizationResult FunctorOfVoidFromCloudRecognizationResult_to_c(FunctorOfVoidFromCloudRecognizationResult f)
{
    easyar_FunctorOfVoidFromCloudRecognizationResult _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromCloudRecognizationResult(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromCloudRecognizationResult_func;
    _return_value_.destroy = FunctorOfVoidFromCloudRecognizationResult_destroy;
    return _return_value_;
}
#endif

}

#endif
