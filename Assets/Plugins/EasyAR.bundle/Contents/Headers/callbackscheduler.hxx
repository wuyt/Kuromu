//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CALLBACKSCHEDULER_HXX__
#define __EASYAR_CALLBACKSCHEDULER_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// Callback scheduler.
/// There are two subclasses: `DelayedCallbackScheduler`_ and `ImmediateCallbackScheduler`_ .
/// `DelayedCallbackScheduler`_ is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// `ImmediateCallbackScheduler`_ is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// </summary>
class CallbackScheduler
{
protected:
    easyar_CallbackScheduler * cdata_ ;
    void init_cdata(easyar_CallbackScheduler * cdata);
    virtual CallbackScheduler & operator=(const CallbackScheduler & data) { return *this; } //deleted
public:
    CallbackScheduler(easyar_CallbackScheduler * cdata);
    virtual ~CallbackScheduler();

    CallbackScheduler(const CallbackScheduler & data);
    const easyar_CallbackScheduler * get_cdata() const;
    easyar_CallbackScheduler * get_cdata();

};

/// <summary>
/// Delayed callback scheduler.
/// It is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// All members of this class is thread-safe.
/// </summary>
class DelayedCallbackScheduler : public CallbackScheduler
{
protected:
    easyar_DelayedCallbackScheduler * cdata_ ;
    void init_cdata(easyar_DelayedCallbackScheduler * cdata);
    virtual DelayedCallbackScheduler & operator=(const DelayedCallbackScheduler & data) { return *this; } //deleted
public:
    DelayedCallbackScheduler(easyar_DelayedCallbackScheduler * cdata);
    virtual ~DelayedCallbackScheduler();

    DelayedCallbackScheduler(const DelayedCallbackScheduler & data);
    const easyar_DelayedCallbackScheduler * get_cdata() const;
    easyar_DelayedCallbackScheduler * get_cdata();

    DelayedCallbackScheduler();
    /// <summary>
    /// Executes a callback. If there is no callback to execute, false is returned.
    /// </summary>
    bool runOne();
    static void tryCastFromCallbackScheduler(CallbackScheduler * v, /* OUT */ DelayedCallbackScheduler * * Return);
};

/// <summary>
/// Immediate callback scheduler.
/// It is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// All members of this class is thread-safe.
/// </summary>
class ImmediateCallbackScheduler : public CallbackScheduler
{
protected:
    easyar_ImmediateCallbackScheduler * cdata_ ;
    void init_cdata(easyar_ImmediateCallbackScheduler * cdata);
    virtual ImmediateCallbackScheduler & operator=(const ImmediateCallbackScheduler & data) { return *this; } //deleted
public:
    ImmediateCallbackScheduler(easyar_ImmediateCallbackScheduler * cdata);
    virtual ~ImmediateCallbackScheduler();

    ImmediateCallbackScheduler(const ImmediateCallbackScheduler & data);
    const easyar_ImmediateCallbackScheduler * get_cdata() const;
    easyar_ImmediateCallbackScheduler * get_cdata();

    /// <summary>
    /// Gets a default immediate callback scheduler.
    /// </summary>
    static void getDefault(/* OUT */ ImmediateCallbackScheduler * * Return);
    static void tryCastFromCallbackScheduler(CallbackScheduler * v, /* OUT */ ImmediateCallbackScheduler * * Return);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_CALLBACKSCHEDULER_HXX__
#define __IMPLEMENTATION_EASYAR_CALLBACKSCHEDULER_HXX__

#include "easyar/callbackscheduler.h"

namespace easyar {

inline CallbackScheduler::CallbackScheduler(easyar_CallbackScheduler * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline CallbackScheduler::~CallbackScheduler()
{
    if (cdata_) {
        easyar_CallbackScheduler__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline CallbackScheduler::CallbackScheduler(const CallbackScheduler & data)
    :
    cdata_(NULL)
{
    easyar_CallbackScheduler * cdata = NULL;
    easyar_CallbackScheduler__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_CallbackScheduler * CallbackScheduler::get_cdata() const
{
    return cdata_;
}
inline easyar_CallbackScheduler * CallbackScheduler::get_cdata()
{
    return cdata_;
}
inline void CallbackScheduler::init_cdata(easyar_CallbackScheduler * cdata)
{
    cdata_ = cdata;
}

inline DelayedCallbackScheduler::DelayedCallbackScheduler(easyar_DelayedCallbackScheduler * cdata)
    :
    CallbackScheduler(static_cast<easyar_CallbackScheduler *>(NULL)),
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline DelayedCallbackScheduler::~DelayedCallbackScheduler()
{
    if (cdata_) {
        easyar_DelayedCallbackScheduler__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline DelayedCallbackScheduler::DelayedCallbackScheduler(const DelayedCallbackScheduler & data)
    :
    CallbackScheduler(static_cast<easyar_CallbackScheduler *>(NULL)),
    cdata_(NULL)
{
    easyar_DelayedCallbackScheduler * cdata = NULL;
    easyar_DelayedCallbackScheduler__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_DelayedCallbackScheduler * DelayedCallbackScheduler::get_cdata() const
{
    return cdata_;
}
inline easyar_DelayedCallbackScheduler * DelayedCallbackScheduler::get_cdata()
{
    return cdata_;
}
inline void DelayedCallbackScheduler::init_cdata(easyar_DelayedCallbackScheduler * cdata)
{
    cdata_ = cdata;
    {
        easyar_CallbackScheduler * cdata_inner = NULL;
        easyar_castDelayedCallbackSchedulerToCallbackScheduler(cdata, &cdata_inner);
        CallbackScheduler::init_cdata(cdata_inner);
    }
}
inline DelayedCallbackScheduler::DelayedCallbackScheduler()
    :
    CallbackScheduler(static_cast<easyar_CallbackScheduler *>(NULL)),
    cdata_(NULL)
{
    easyar_DelayedCallbackScheduler * _return_value_ = NULL;
    easyar_DelayedCallbackScheduler__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline bool DelayedCallbackScheduler::runOne()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_DelayedCallbackScheduler_runOne(cdata_);
    return _return_value_;
}
inline void DelayedCallbackScheduler::tryCastFromCallbackScheduler(CallbackScheduler * v, /* OUT */ DelayedCallbackScheduler * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_DelayedCallbackScheduler * cdata = NULL;
    easyar_tryCastCallbackSchedulerToDelayedCallbackScheduler(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new DelayedCallbackScheduler(cdata);
}

inline ImmediateCallbackScheduler::ImmediateCallbackScheduler(easyar_ImmediateCallbackScheduler * cdata)
    :
    CallbackScheduler(static_cast<easyar_CallbackScheduler *>(NULL)),
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ImmediateCallbackScheduler::~ImmediateCallbackScheduler()
{
    if (cdata_) {
        easyar_ImmediateCallbackScheduler__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ImmediateCallbackScheduler::ImmediateCallbackScheduler(const ImmediateCallbackScheduler & data)
    :
    CallbackScheduler(static_cast<easyar_CallbackScheduler *>(NULL)),
    cdata_(NULL)
{
    easyar_ImmediateCallbackScheduler * cdata = NULL;
    easyar_ImmediateCallbackScheduler__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ImmediateCallbackScheduler * ImmediateCallbackScheduler::get_cdata() const
{
    return cdata_;
}
inline easyar_ImmediateCallbackScheduler * ImmediateCallbackScheduler::get_cdata()
{
    return cdata_;
}
inline void ImmediateCallbackScheduler::init_cdata(easyar_ImmediateCallbackScheduler * cdata)
{
    cdata_ = cdata;
    {
        easyar_CallbackScheduler * cdata_inner = NULL;
        easyar_castImmediateCallbackSchedulerToCallbackScheduler(cdata, &cdata_inner);
        CallbackScheduler::init_cdata(cdata_inner);
    }
}
inline void ImmediateCallbackScheduler::getDefault(/* OUT */ ImmediateCallbackScheduler * * Return)
{
    easyar_ImmediateCallbackScheduler * _return_value_ = NULL;
    easyar_ImmediateCallbackScheduler_getDefault(&_return_value_);
    *Return = new ImmediateCallbackScheduler(_return_value_);
}
inline void ImmediateCallbackScheduler::tryCastFromCallbackScheduler(CallbackScheduler * v, /* OUT */ ImmediateCallbackScheduler * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ImmediateCallbackScheduler * cdata = NULL;
    easyar_tryCastCallbackSchedulerToImmediateCallbackScheduler(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new ImmediateCallbackScheduler(cdata);
}

}

#endif
