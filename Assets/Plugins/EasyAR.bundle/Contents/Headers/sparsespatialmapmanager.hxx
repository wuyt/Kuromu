//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SPARSESPATIALMAPMANAGER_HXX__
#define __EASYAR_SPARSESPATIALMAPMANAGER_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// SparseSpatialMap manager class, for managing sharing.
/// </summary>
class SparseSpatialMapManager
{
protected:
    easyar_SparseSpatialMapManager * cdata_ ;
    void init_cdata(easyar_SparseSpatialMapManager * cdata);
    virtual SparseSpatialMapManager & operator=(const SparseSpatialMapManager & data) { return *this; } //deleted
public:
    SparseSpatialMapManager(easyar_SparseSpatialMapManager * cdata);
    virtual ~SparseSpatialMapManager();

    SparseSpatialMapManager(const SparseSpatialMapManager & data);
    const easyar_SparseSpatialMapManager * get_cdata() const;
    easyar_SparseSpatialMapManager * get_cdata();

    /// <summary>
    /// Check whether SparseSpatialMapManager is is available. It returns true when the operating system is Mac, iOS or Android.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static void create(/* OUT */ SparseSpatialMapManager * * Return);
    /// <summary>
    /// Creates a map from `SparseSpatialMap`_ and upload it to EasyAR cloud servers. After completion, a serverMapId will be returned for loading map from EasyAR cloud servers.
    /// </summary>
    void host(SparseSpatialMap * mapBuilder, String * apiKey, String * apiSecret, String * sparseSpatialMapAppId, String * name, Image * preview, CallbackScheduler * callbackScheduler, FunctorOfVoidFromBoolAndStringAndString onCompleted);
    /// <summary>
    /// Loads a map from EasyAR cloud servers by serverMapId. To unload the map, call `SparseSpatialMap.unloadMap`_ with serverMapId.
    /// </summary>
    void load(SparseSpatialMap * mapTracker, String * serverMapId, String * apiKey, String * apiSecret, String * sparseSpatialMapAppId, CallbackScheduler * callbackScheduler, FunctorOfVoidFromBoolAndString onCompleted);
    /// <summary>
    /// Clears allocated cache space.
    /// </summary>
    void clear();
};

#ifndef __EASYAR_OPTIONALOFIMAGE__
#define __EASYAR_OPTIONALOFIMAGE__
struct OptionalOfImage
{
    bool has_value;
    Image * value;
};
static inline easyar_OptionalOfImage OptionalOfImage_to_c(Image * o);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRINGANDSTRING__
#define __EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRINGANDSTRING__
struct FunctorOfVoidFromBoolAndStringAndString
{
    void * _state;
    void (* func)(void * _state, bool, String *, String *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromBoolAndStringAndString(void * _state, void (* func)(void * _state, bool, String *, String *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromBoolAndStringAndString_func(void * _state, bool, easyar_String *, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromBoolAndStringAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromBoolAndStringAndString FunctorOfVoidFromBoolAndStringAndString_to_c(FunctorOfVoidFromBoolAndStringAndString f);
#endif

#ifndef __EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRING__
#define __EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRING__
struct FunctorOfVoidFromBoolAndString
{
    void * _state;
    void (* func)(void * _state, bool, String *);
    void (* destroy)(void * _state);
    FunctorOfVoidFromBoolAndString(void * _state, void (* func)(void * _state, bool, String *), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromBoolAndString_func(void * _state, bool, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromBoolAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromBoolAndString FunctorOfVoidFromBoolAndString_to_c(FunctorOfVoidFromBoolAndString f);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_SPARSESPATIALMAPMANAGER_HXX__
#define __IMPLEMENTATION_EASYAR_SPARSESPATIALMAPMANAGER_HXX__

#include "easyar/sparsespatialmapmanager.h"
#include "easyar/sparsespatialmap.hxx"
#include "easyar/dataflow.hxx"
#include "easyar/frame.hxx"
#include "easyar/image.hxx"
#include "easyar/buffer.hxx"
#include "easyar/cameraparameters.hxx"
#include "easyar/vector.hxx"
#include "easyar/matrix.hxx"
#include "easyar/callbackscheduler.hxx"

namespace easyar {

inline SparseSpatialMapManager::SparseSpatialMapManager(easyar_SparseSpatialMapManager * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline SparseSpatialMapManager::~SparseSpatialMapManager()
{
    if (cdata_) {
        easyar_SparseSpatialMapManager__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline SparseSpatialMapManager::SparseSpatialMapManager(const SparseSpatialMapManager & data)
    :
    cdata_(NULL)
{
    easyar_SparseSpatialMapManager * cdata = NULL;
    easyar_SparseSpatialMapManager__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_SparseSpatialMapManager * SparseSpatialMapManager::get_cdata() const
{
    return cdata_;
}
inline easyar_SparseSpatialMapManager * SparseSpatialMapManager::get_cdata()
{
    return cdata_;
}
inline void SparseSpatialMapManager::init_cdata(easyar_SparseSpatialMapManager * cdata)
{
    cdata_ = cdata;
}
inline bool SparseSpatialMapManager::isAvailable()
{
    bool _return_value_ = easyar_SparseSpatialMapManager_isAvailable();
    return _return_value_;
}
inline void SparseSpatialMapManager::create(/* OUT */ SparseSpatialMapManager * * Return)
{
    easyar_SparseSpatialMapManager * _return_value_ = NULL;
    easyar_SparseSpatialMapManager_create(&_return_value_);
    *Return = new SparseSpatialMapManager(_return_value_);
}
inline void SparseSpatialMapManager::host(SparseSpatialMap * arg0, String * arg1, String * arg2, String * arg3, String * arg4, Image * arg5, CallbackScheduler * arg6, FunctorOfVoidFromBoolAndStringAndString arg7)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMapManager_host(cdata_, arg0->get_cdata(), arg1->get_cdata(), arg2->get_cdata(), arg3->get_cdata(), arg4->get_cdata(), OptionalOfImage_to_c(arg5), arg6->get_cdata(), FunctorOfVoidFromBoolAndStringAndString_to_c(arg7));
}
inline void SparseSpatialMapManager::load(SparseSpatialMap * arg0, String * arg1, String * arg2, String * arg3, String * arg4, CallbackScheduler * arg5, FunctorOfVoidFromBoolAndString arg6)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMapManager_load(cdata_, arg0->get_cdata(), arg1->get_cdata(), arg2->get_cdata(), arg3->get_cdata(), arg4->get_cdata(), arg5->get_cdata(), FunctorOfVoidFromBoolAndString_to_c(arg6));
}
inline void SparseSpatialMapManager::clear()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_SparseSpatialMapManager_clear(cdata_);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFIMAGE__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFIMAGE__
static inline easyar_OptionalOfImage OptionalOfImage_to_c(Image * o)
{
    if (o != NULL) {
        easyar_OptionalOfImage _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfImage _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRINGANDSTRING__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRINGANDSTRING__
inline FunctorOfVoidFromBoolAndStringAndString::FunctorOfVoidFromBoolAndStringAndString(void * _state, void (* func)(void * _state, bool, String *, String *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromBoolAndStringAndString_func(void * _state, bool arg0, easyar_String * arg1, easyar_String * arg2, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        bool cpparg0 = arg0;
        easyar_String_copy(arg1, &arg1);
        String * cpparg1 = new String(arg1);
        easyar_String_copy(arg2, &arg2);
        String * cpparg2 = new String(arg2);
        FunctorOfVoidFromBoolAndStringAndString * f = reinterpret_cast<FunctorOfVoidFromBoolAndStringAndString *>(_state);
        f->func(f->_state, cpparg0, cpparg1, cpparg2);
        delete cpparg1;
        delete cpparg2;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromBoolAndStringAndString_destroy(void * _state)
{
    FunctorOfVoidFromBoolAndStringAndString * f = reinterpret_cast<FunctorOfVoidFromBoolAndStringAndString *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromBoolAndStringAndString FunctorOfVoidFromBoolAndStringAndString_to_c(FunctorOfVoidFromBoolAndStringAndString f)
{
    easyar_FunctorOfVoidFromBoolAndStringAndString _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromBoolAndStringAndString(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromBoolAndStringAndString_func;
    _return_value_.destroy = FunctorOfVoidFromBoolAndStringAndString_destroy;
    return _return_value_;
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRING__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMBOOLANDSTRING__
inline FunctorOfVoidFromBoolAndString::FunctorOfVoidFromBoolAndString(void * _state, void (* func)(void * _state, bool, String *), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromBoolAndString_func(void * _state, bool arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        bool cpparg0 = arg0;
        easyar_String_copy(arg1, &arg1);
        String * cpparg1 = new String(arg1);
        FunctorOfVoidFromBoolAndString * f = reinterpret_cast<FunctorOfVoidFromBoolAndString *>(_state);
        f->func(f->_state, cpparg0, cpparg1);
        delete cpparg1;
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromBoolAndString_destroy(void * _state)
{
    FunctorOfVoidFromBoolAndString * f = reinterpret_cast<FunctorOfVoidFromBoolAndString *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromBoolAndString FunctorOfVoidFromBoolAndString_to_c(FunctorOfVoidFromBoolAndString f)
{
    easyar_FunctorOfVoidFromBoolAndString _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromBoolAndString(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromBoolAndString_func;
    _return_value_.destroy = FunctorOfVoidFromBoolAndString_destroy;
    return _return_value_;
}
#endif

}

#endif
