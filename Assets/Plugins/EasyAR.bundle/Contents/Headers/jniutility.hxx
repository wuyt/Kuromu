//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_JNIUTILITY_HXX__
#define __EASYAR_JNIUTILITY_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// JNI utility class.
/// It is used in Unity to wrap Java byte array and ByteBuffer.
/// It is not supported on iOS.
/// </summary>
class JniUtility
{
public:
    /// <summary>
    /// Wraps Java&#39;s byte[]。
    /// </summary>
    static void wrapByteArray(void * bytes, bool readOnly, FunctorOfVoid deleter, /* OUT */ Buffer * * Return);
    /// <summary>
    /// Wraps Java&#39;s java.nio.ByteBuffer, which must be a direct buffer.
    /// </summary>
    static void wrapBuffer(void * directBuffer, FunctorOfVoid deleter, /* OUT */ Buffer * * Return);
    /// <summary>
    /// Get the raw address of a direct buffer of java.nio.ByteBuffer by calling JNIEnv-&gt;GetDirectBufferAddress.
    /// </summary>
    static void * getDirectBufferAddress(void * directBuffer);
};

#ifndef __EASYAR_FUNCTOROFVOID__
#define __EASYAR_FUNCTOROFVOID__
struct FunctorOfVoid
{
    void * _state;
    void (* func)(void * _state);
    void (* destroy)(void * _state);
    FunctorOfVoid(void * _state, void (* func)(void * _state), void (* destroy)(void * _state));
};

static void FunctorOfVoid_func(void * _state, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoid_destroy(void * _state);
static inline easyar_FunctorOfVoid FunctorOfVoid_to_c(FunctorOfVoid f);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_JNIUTILITY_HXX__
#define __IMPLEMENTATION_EASYAR_JNIUTILITY_HXX__

#include "easyar/jniutility.h"
#include "easyar/buffer.hxx"

namespace easyar {

inline void JniUtility::wrapByteArray(void * arg0, bool arg1, FunctorOfVoid arg2, /* OUT */ Buffer * * Return)
{
    easyar_Buffer * _return_value_ = NULL;
    easyar_JniUtility_wrapByteArray(arg0, arg1, FunctorOfVoid_to_c(arg2), &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void JniUtility::wrapBuffer(void * arg0, FunctorOfVoid arg1, /* OUT */ Buffer * * Return)
{
    easyar_Buffer * _return_value_ = NULL;
    easyar_JniUtility_wrapBuffer(arg0, FunctorOfVoid_to_c(arg1), &_return_value_);
    *Return = new Buffer(_return_value_);
}
inline void * JniUtility::getDirectBufferAddress(void * arg0)
{
    void * _return_value_ = easyar_JniUtility_getDirectBufferAddress(arg0);
    return _return_value_;
}

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOID__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOID__
inline FunctorOfVoid::FunctorOfVoid(void * _state, void (* func)(void * _state), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoid_func(void * _state, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        FunctorOfVoid * f = reinterpret_cast<FunctorOfVoid *>(_state);
        f->func(f->_state);
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoid_destroy(void * _state)
{
    FunctorOfVoid * f = reinterpret_cast<FunctorOfVoid *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoid FunctorOfVoid_to_c(FunctorOfVoid f)
{
    easyar_FunctorOfVoid _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoid(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoid_func;
    _return_value_.destroy = FunctorOfVoid_destroy;
    return _return_value_;
}
#endif

}

#endif
