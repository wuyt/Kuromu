//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_LOG_HXX__
#define __EASYAR_LOG_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// Log class.
/// It is used to setup a custom log output function.
/// </summary>
class Log
{
public:
    /// <summary>
    /// Sets custom log output function.
    /// </summary>
    static void setLogFunc(FunctorOfVoidFromLogLevelAndString func);
    /// <summary>
    /// Clears custom log output function and reverts to default log output function.
    /// </summary>
    static void resetLogFunc();
};

#ifndef __EASYAR_FUNCTOROFVOIDFROMLOGLEVELANDSTRING__
#define __EASYAR_FUNCTOROFVOIDFROMLOGLEVELANDSTRING__
struct FunctorOfVoidFromLogLevelAndString
{
    void * _state;
    void (* func)(void * _state, LogLevel, String *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromLogLevelAndString(void * _state, void (* func)(void * _state, LogLevel, String *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromLogLevelAndString_func(void * _state, easyar_LogLevel, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromLogLevelAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromLogLevelAndString FunctorOfVoidFromLogLevelAndString_to_c(FunctorOfVoidFromLogLevelAndString f);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_LOG_HXX__
#define __IMPLEMENTATION_EASYAR_LOG_HXX__

#include "easyar/log.h"

namespace easyar {

inline void Log::setLogFunc(FunctorOfVoidFromLogLevelAndString arg0)
{
    easyar_Log_setLogFunc(FunctorOfVoidFromLogLevelAndString_to_c(arg0));
}
inline void Log::resetLogFunc()
{
    easyar_Log_resetLogFunc();
}

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMLOGLEVELANDSTRING__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMLOGLEVELANDSTRING__
inline FunctorOfVoidFromLogLevelAndString::FunctorOfVoidFromLogLevelAndString(void * _state, void (* func)(void * _state, LogLevel, String *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromLogLevelAndString_func(void * _state, easyar_LogLevel arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        LogLevel cpparg0 = static_cast<LogLevel>(arg0);
        easyar_String_copy(arg1, &arg1);
        String * cpparg1 = new String(arg1);
        FunctorOfVoidFromLogLevelAndString * f = reinterpret_cast<FunctorOfVoidFromLogLevelAndString *>(_state);
        f->func(f->_state, cpparg0, cpparg1);
        delete cpparg1;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromLogLevelAndString_destroy(void * _state)
{
    FunctorOfVoidFromLogLevelAndString * f = reinterpret_cast<FunctorOfVoidFromLogLevelAndString *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromLogLevelAndString FunctorOfVoidFromLogLevelAndString_to_c(FunctorOfVoidFromLogLevelAndString f)
{
    easyar_FunctorOfVoidFromLogLevelAndString _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromLogLevelAndString(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromLogLevelAndString_func;
    _return_value_.destroy = FunctorOfVoidFromLogLevelAndString_destroy;
    return _return_value_;
}
#endif

}

#endif
