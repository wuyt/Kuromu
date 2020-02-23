//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_OBJECTTRACKER_HXX__
#define __EASYAR_OBJECTTRACKER_HXX__

#include "easyar/types.hxx"
#include "easyar/target.hxx"

namespace easyar {

/// <summary>
/// Result of `ObjectTracker`_ .
/// </summary>
class ObjectTrackerResult : public TargetTrackerResult
{
protected:
    easyar_ObjectTrackerResult * cdata_ ;
    void init_cdata(easyar_ObjectTrackerResult * cdata);
    virtual ObjectTrackerResult & operator=(const ObjectTrackerResult & data) { return *this; } //deleted
public:
    ObjectTrackerResult(easyar_ObjectTrackerResult * cdata);
    virtual ~ObjectTrackerResult();

    ObjectTrackerResult(const ObjectTrackerResult & data);
    const easyar_ObjectTrackerResult * get_cdata() const;
    easyar_ObjectTrackerResult * get_cdata();

    /// <summary>
    /// Returns the list of `TargetInstance`_ contained in the result.
    /// </summary>
    void targetInstances(/* OUT */ ListOfTargetInstance * * Return);
    /// <summary>
    /// Sets the list of `TargetInstance`_ contained in the result.
    /// </summary>
    void setTargetInstances(ListOfTargetInstance * instances);
    static void tryCastFromFrameFilterResult(FrameFilterResult * v, /* OUT */ ObjectTrackerResult * * Return);
    static void tryCastFromTargetTrackerResult(TargetTrackerResult * v, /* OUT */ ObjectTrackerResult * * Return);
};

/// <summary>
/// ObjectTracker implements 3D object target detection and tracking.
/// ObjectTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ObjectTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// Before a `Target`_ can be tracked by ObjectTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
/// </summary>
class ObjectTracker
{
protected:
    easyar_ObjectTracker * cdata_ ;
    void init_cdata(easyar_ObjectTracker * cdata);
    virtual ObjectTracker & operator=(const ObjectTracker & data) { return *this; } //deleted
public:
    ObjectTracker(easyar_ObjectTracker * cdata);
    virtual ~ObjectTracker();

    ObjectTracker(const ObjectTracker & data);
    const easyar_ObjectTracker * get_cdata() const;
    easyar_ObjectTracker * get_cdata();

    /// <summary>
    /// Returns true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
    /// </summary>
    void feedbackFrameSink(/* OUT */ FeedbackFrameSink * * Return);
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
    static void create(/* OUT */ ObjectTracker * * Return);
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
    /// Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
    /// This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
    /// </summary>
    void loadTarget(Target * target, CallbackScheduler * callbackScheduler, FunctorOfVoidFromTargetAndBool callback);
    /// <summary>
    /// Unload a `Target`_ from the tracker.
    /// This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
    /// </summary>
    void unloadTarget(Target * target, CallbackScheduler * callbackScheduler, FunctorOfVoidFromTargetAndBool callback);
    /// <summary>
    /// Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
    /// </summary>
    void targets(/* OUT */ ListOfTarget * * Return);
    /// <summary>
    /// Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
    /// </summary>
    bool setSimultaneousNum(int num);
    /// <summary>
    /// Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
    /// </summary>
    int simultaneousNum();
};

#ifndef __EASYAR_LISTOFTARGETINSTANCE__
#define __EASYAR_LISTOFTARGETINSTANCE__
class ListOfTargetInstance
{
private:
    easyar_ListOfTargetInstance * cdata_;
    virtual ListOfTargetInstance & operator=(const ListOfTargetInstance & data) { return *this; } //deleted
public:
    ListOfTargetInstance(easyar_ListOfTargetInstance * cdata);
    virtual ~ListOfTargetInstance();

    ListOfTargetInstance(const ListOfTargetInstance & data);
    const easyar_ListOfTargetInstance * get_cdata() const;
    easyar_ListOfTargetInstance * get_cdata();

    ListOfTargetInstance(easyar_TargetInstance * * begin, easyar_TargetInstance * * end);
    int size() const;
    TargetInstance * at(int index) const;
};
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMTARGETANDBOOL__
#define __EASYAR_FUNCTOROFVOIDFROMTARGETANDBOOL__
struct FunctorOfVoidFromTargetAndBool
{
    void * _state;
    void (* func)(void * _state, Target *, bool);
    void (* destroy)(void * _state);
    FunctorOfVoidFromTargetAndBool(void * _state, void (* func)(void * _state, Target *, bool), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromTargetAndBool_func(void * _state, easyar_Target *, bool, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromTargetAndBool_destroy(void * _state);
static inline easyar_FunctorOfVoidFromTargetAndBool FunctorOfVoidFromTargetAndBool_to_c(FunctorOfVoidFromTargetAndBool f);
#endif

#ifndef __EASYAR_LISTOFTARGET__
#define __EASYAR_LISTOFTARGET__
class ListOfTarget
{
private:
    easyar_ListOfTarget * cdata_;
    virtual ListOfTarget & operator=(const ListOfTarget & data) { return *this; } //deleted
public:
    ListOfTarget(easyar_ListOfTarget * cdata);
    virtual ~ListOfTarget();

    ListOfTarget(const ListOfTarget & data);
    const easyar_ListOfTarget * get_cdata() const;
    easyar_ListOfTarget * get_cdata();

    ListOfTarget(easyar_Target * * begin, easyar_Target * * end);
    int size() const;
    Target * at(int index) const;
};
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_OBJECTTRACKER_HXX__
#define __IMPLEMENTATION_EASYAR_OBJECTTRACKER_HXX__

#include "easyar/objecttracker.h"
#include "easyar/target.hxx"
#include "easyar/frame.hxx"
#include "easyar/matrix.hxx"
#include "easyar/dataflow.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/callbackscheduler.hxx"

namespace easyar {

inline ObjectTrackerResult::ObjectTrackerResult(easyar_ObjectTrackerResult * cdata)
    :
    TargetTrackerResult(static_cast<easyar_TargetTrackerResult *>(NULL)),
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ObjectTrackerResult::~ObjectTrackerResult()
{
    if (cdata_) {
        easyar_ObjectTrackerResult__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ObjectTrackerResult::ObjectTrackerResult(const ObjectTrackerResult & data)
    :
    TargetTrackerResult(static_cast<easyar_TargetTrackerResult *>(NULL)),
    cdata_(NULL)
{
    easyar_ObjectTrackerResult * cdata = NULL;
    easyar_ObjectTrackerResult__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ObjectTrackerResult * ObjectTrackerResult::get_cdata() const
{
    return cdata_;
}
inline easyar_ObjectTrackerResult * ObjectTrackerResult::get_cdata()
{
    return cdata_;
}
inline void ObjectTrackerResult::init_cdata(easyar_ObjectTrackerResult * cdata)
{
    cdata_ = cdata;
    {
        easyar_TargetTrackerResult * cdata_inner = NULL;
        easyar_castObjectTrackerResultToTargetTrackerResult(cdata, &cdata_inner);
        TargetTrackerResult::init_cdata(cdata_inner);
    }
}
inline void ObjectTrackerResult::targetInstances(/* OUT */ ListOfTargetInstance * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfTargetInstance * _return_value_ = NULL;
    easyar_ObjectTrackerResult_targetInstances(cdata_, &_return_value_);
    *Return = new ListOfTargetInstance(_return_value_);
}
inline void ObjectTrackerResult::setTargetInstances(ListOfTargetInstance * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTrackerResult_setTargetInstances(cdata_, arg0->get_cdata());
}
inline void ObjectTrackerResult::tryCastFromFrameFilterResult(FrameFilterResult * v, /* OUT */ ObjectTrackerResult * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ObjectTrackerResult * cdata = NULL;
    easyar_tryCastFrameFilterResultToObjectTrackerResult(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new ObjectTrackerResult(cdata);
}
inline void ObjectTrackerResult::tryCastFromTargetTrackerResult(TargetTrackerResult * v, /* OUT */ ObjectTrackerResult * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ObjectTrackerResult * cdata = NULL;
    easyar_tryCastTargetTrackerResultToObjectTrackerResult(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new ObjectTrackerResult(cdata);
}

inline ObjectTracker::ObjectTracker(easyar_ObjectTracker * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ObjectTracker::~ObjectTracker()
{
    if (cdata_) {
        easyar_ObjectTracker__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ObjectTracker::ObjectTracker(const ObjectTracker & data)
    :
    cdata_(NULL)
{
    easyar_ObjectTracker * cdata = NULL;
    easyar_ObjectTracker__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ObjectTracker * ObjectTracker::get_cdata() const
{
    return cdata_;
}
inline easyar_ObjectTracker * ObjectTracker::get_cdata()
{
    return cdata_;
}
inline void ObjectTracker::init_cdata(easyar_ObjectTracker * cdata)
{
    cdata_ = cdata;
}
inline bool ObjectTracker::isAvailable()
{
    bool _return_value_ = easyar_ObjectTracker_isAvailable();
    return _return_value_;
}
inline void ObjectTracker::feedbackFrameSink(/* OUT */ FeedbackFrameSink * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_FeedbackFrameSink * _return_value_ = NULL;
    easyar_ObjectTracker_feedbackFrameSink(cdata_, &_return_value_);
    *Return = new FeedbackFrameSink(_return_value_);
}
inline int ObjectTracker::bufferRequirement()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_ObjectTracker_bufferRequirement(cdata_);
    return _return_value_;
}
inline void ObjectTracker::outputFrameSource(/* OUT */ OutputFrameSource * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_OutputFrameSource * _return_value_ = NULL;
    easyar_ObjectTracker_outputFrameSource(cdata_, &_return_value_);
    *Return = new OutputFrameSource(_return_value_);
}
inline void ObjectTracker::create(/* OUT */ ObjectTracker * * Return)
{
    easyar_ObjectTracker * _return_value_ = NULL;
    easyar_ObjectTracker_create(&_return_value_);
    *Return = new ObjectTracker(_return_value_);
}
inline bool ObjectTracker::start()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_ObjectTracker_start(cdata_);
    return _return_value_;
}
inline void ObjectTracker::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTracker_stop(cdata_);
}
inline void ObjectTracker::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTracker_close(cdata_);
}
inline void ObjectTracker::loadTarget(Target * arg0, CallbackScheduler * arg1, FunctorOfVoidFromTargetAndBool arg2)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTracker_loadTarget(cdata_, arg0->get_cdata(), arg1->get_cdata(), FunctorOfVoidFromTargetAndBool_to_c(arg2));
}
inline void ObjectTracker::unloadTarget(Target * arg0, CallbackScheduler * arg1, FunctorOfVoidFromTargetAndBool arg2)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTracker_unloadTarget(cdata_, arg0->get_cdata(), arg1->get_cdata(), FunctorOfVoidFromTargetAndBool_to_c(arg2));
}
inline void ObjectTracker::targets(/* OUT */ ListOfTarget * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfTarget * _return_value_ = NULL;
    easyar_ObjectTracker_targets(cdata_, &_return_value_);
    *Return = new ListOfTarget(_return_value_);
}
inline bool ObjectTracker::setSimultaneousNum(int arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_ObjectTracker_setSimultaneousNum(cdata_, arg0);
    return _return_value_;
}
inline int ObjectTracker::simultaneousNum()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_ObjectTracker_simultaneousNum(cdata_);
    return _return_value_;
}

#ifndef __IMPLEMENTATION_EASYAR_LISTOFTARGETINSTANCE__
#define __IMPLEMENTATION_EASYAR_LISTOFTARGETINSTANCE__
inline ListOfTargetInstance::ListOfTargetInstance(easyar_ListOfTargetInstance * cdata)
    : cdata_(cdata)
{
}
inline ListOfTargetInstance::~ListOfTargetInstance()
{
    if (cdata_) {
        easyar_ListOfTargetInstance__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfTargetInstance::ListOfTargetInstance(const ListOfTargetInstance & data)
    : cdata_(static_cast<easyar_ListOfTargetInstance *>(NULL))
{
    easyar_ListOfTargetInstance_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfTargetInstance * ListOfTargetInstance::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfTargetInstance * ListOfTargetInstance::get_cdata()
{
    return cdata_;
}

inline ListOfTargetInstance::ListOfTargetInstance(easyar_TargetInstance * * begin, easyar_TargetInstance * * end)
    : cdata_(static_cast<easyar_ListOfTargetInstance *>(NULL))
{
    easyar_ListOfTargetInstance__ctor(begin, end, &cdata_);
}
inline int ListOfTargetInstance::size() const
{
    return easyar_ListOfTargetInstance_size(cdata_);
}
inline TargetInstance * ListOfTargetInstance::at(int index) const
{
    easyar_TargetInstance * _return_value_ = easyar_ListOfTargetInstance_at(cdata_, index);
    easyar_TargetInstance__retain(_return_value_, &_return_value_);
    return new TargetInstance(_return_value_);
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMTARGETANDBOOL__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMTARGETANDBOOL__
inline FunctorOfVoidFromTargetAndBool::FunctorOfVoidFromTargetAndBool(void * _state, void (* func)(void * _state, Target *, bool), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromTargetAndBool_func(void * _state, easyar_Target * arg0, bool arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        easyar_Target__retain(arg0, &arg0);
        Target * cpparg0 = new Target(arg0);
        bool cpparg1 = arg1;
        FunctorOfVoidFromTargetAndBool * f = reinterpret_cast<FunctorOfVoidFromTargetAndBool *>(_state);
        f->func(f->_state, cpparg0, cpparg1);
        delete cpparg0;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromTargetAndBool_destroy(void * _state)
{
    FunctorOfVoidFromTargetAndBool * f = reinterpret_cast<FunctorOfVoidFromTargetAndBool *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromTargetAndBool FunctorOfVoidFromTargetAndBool_to_c(FunctorOfVoidFromTargetAndBool f)
{
    easyar_FunctorOfVoidFromTargetAndBool _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromTargetAndBool(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromTargetAndBool_func;
    _return_value_.destroy = FunctorOfVoidFromTargetAndBool_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_LISTOFTARGET__
#define __IMPLEMENTATION_EASYAR_LISTOFTARGET__
inline ListOfTarget::ListOfTarget(easyar_ListOfTarget * cdata)
    : cdata_(cdata)
{
}
inline ListOfTarget::~ListOfTarget()
{
    if (cdata_) {
        easyar_ListOfTarget__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfTarget::ListOfTarget(const ListOfTarget & data)
    : cdata_(static_cast<easyar_ListOfTarget *>(NULL))
{
    easyar_ListOfTarget_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfTarget * ListOfTarget::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfTarget * ListOfTarget::get_cdata()
{
    return cdata_;
}

inline ListOfTarget::ListOfTarget(easyar_Target * * begin, easyar_Target * * end)
    : cdata_(static_cast<easyar_ListOfTarget *>(NULL))
{
    easyar_ListOfTarget__ctor(begin, end, &cdata_);
}
inline int ListOfTarget::size() const
{
    return easyar_ListOfTarget_size(cdata_);
}
inline Target * ListOfTarget::at(int index) const
{
    easyar_Target * _return_value_ = easyar_ListOfTarget_at(cdata_, index);
    easyar_Target__retain(_return_value_, &_return_value_);
    return new Target(_return_value_);
}
#endif

}

#endif
