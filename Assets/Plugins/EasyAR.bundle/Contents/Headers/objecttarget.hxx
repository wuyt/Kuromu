//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_OBJECTTARGET_HXX__
#define __EASYAR_OBJECTTARGET_HXX__

#include "easyar/types.hxx"
#include "easyar/target.hxx"

namespace easyar {

/// <summary>
/// ObjectTargetParameters represents the parameters to create a `ObjectTarget`_ .
/// </summary>
class ObjectTargetParameters
{
protected:
    easyar_ObjectTargetParameters * cdata_ ;
    void init_cdata(easyar_ObjectTargetParameters * cdata);
    virtual ObjectTargetParameters & operator=(const ObjectTargetParameters & data) { return *this; } //deleted
public:
    ObjectTargetParameters(easyar_ObjectTargetParameters * cdata);
    virtual ~ObjectTargetParameters();

    ObjectTargetParameters(const ObjectTargetParameters & data);
    const easyar_ObjectTargetParameters * get_cdata() const;
    easyar_ObjectTargetParameters * get_cdata();

    ObjectTargetParameters();
    /// <summary>
    /// Gets `Buffer`_ dictionary.
    /// </summary>
    void bufferDictionary(/* OUT */ BufferDictionary * * Return);
    /// <summary>
    /// Sets `Buffer`_ dictionary. obj, mtl and jpg/png files shall be loaded into the dictionay, and be able to be located by relative or absolute paths.
    /// </summary>
    void setBufferDictionary(BufferDictionary * bufferDictionary);
    /// <summary>
    /// Gets obj file path.
    /// </summary>
    void objPath(/* OUT */ String * * Return);
    /// <summary>
    /// Sets obj file path.
    /// </summary>
    void setObjPath(String * objPath);
    /// <summary>
    /// Gets target name. It can be used to distinguish targets.
    /// </summary>
    void name(/* OUT */ String * * Return);
    /// <summary>
    /// Sets target name.
    /// </summary>
    void setName(String * name);
    /// <summary>
    /// Gets the target uid. You can set this uid in the json config as a method to distinguish from targets.
    /// </summary>
    void uid(/* OUT */ String * * Return);
    /// <summary>
    /// Sets target uid.
    /// </summary>
    void setUid(String * uid);
    /// <summary>
    /// Gets meta data.
    /// </summary>
    void meta(/* OUT */ String * * Return);
    /// <summary>
    /// Sets meta data。
    /// </summary>
    void setMeta(String * meta);
    /// <summary>
    /// Gets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// </summary>
    float scale();
    /// <summary>
    /// Sets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// It is needed to set the model scale in rendering engine separately.
    /// </summary>
    void setScale(float size);
};

/// <summary>
/// ObjectTarget represents 3d object targets that can be tracked by `ObjectTracker`_ .
/// The size of ObjectTarget is determined by the `obj` file. You can change it by changing the object `scale`, which is default to 1.
/// A ObjectTarget should be setup using setup before any value is valid. And ObjectTarget can be tracked by `ObjectTracker`_ after a successful load into the `ObjectTracker`_ using `ObjectTracker.loadTarget`_ .
/// </summary>
class ObjectTarget : public Target
{
protected:
    easyar_ObjectTarget * cdata_ ;
    void init_cdata(easyar_ObjectTarget * cdata);
    virtual ObjectTarget & operator=(const ObjectTarget & data) { return *this; } //deleted
public:
    ObjectTarget(easyar_ObjectTarget * cdata);
    virtual ~ObjectTarget();

    ObjectTarget(const ObjectTarget & data);
    const easyar_ObjectTarget * get_cdata() const;
    easyar_ObjectTarget * get_cdata();

    ObjectTarget();
    /// <summary>
    /// Creates a target from parameters.
    /// </summary>
    static void createFromParameters(ObjectTargetParameters * parameters, /* OUT */ ObjectTarget * * Return);
    /// <summary>
    /// Creats a target from obj, mtl and jpg/png files.
    /// </summary>
    static void createFromObjectFile(String * path, StorageType storageType, String * name, String * uid, String * meta, float scale, /* OUT */ ObjectTarget * * Return);
    /// <summary>
    /// Setup all targets listed in the json file or json string from path with storageType. This method only parses the json file or string.
    /// If path is json file path, storageType should be `App` or `Assets` or `Absolute` indicating the path type. Paths inside json files should be absolute path or relative path to the json file.
    /// See `StorageType`_ for more descriptions.
    /// </summary>
    static void setupAll(String * path, StorageType storageType, /* OUT */ ListOfObjectTarget * * Return);
    /// <summary>
    /// The scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// </summary>
    float scale();
    /// <summary>
    /// The bounding box of object, it contains the 8 points of the box.
    /// Vertices&#39;s indices are defined and stored following the rule:
    /// ::
    ///
    ///       4-----7
    ///      /|    /|
    ///     5-----6 |    z
    ///     | |   | |    |
    ///     | 0---|-3    o---y
    ///     |/    |/    /
    ///     1-----2    x
    /// </summary>
    void boundingBox(/* OUT */ ListOfVec3F * * Return);
    /// <summary>
    /// Sets model target scale, this will overwrite the value set in the json file or the default value. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// It is needed to set the model scale in rendering engine separately.
    /// It also should been done before loading ObjectTarget into  `ObjectTracker`_ using `ObjectTracker.loadTarget`_.
    /// </summary>
    bool setScale(float scale);
    /// <summary>
    /// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
    /// </summary>
    int runtimeID();
    /// <summary>
    /// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
    /// </summary>
    void uid(/* OUT */ String * * Return);
    /// <summary>
    /// Returns the target name. Name is used to distinguish targets in a json file.
    /// </summary>
    void name(/* OUT */ String * * Return);
    /// <summary>
    /// Set name. It will erase previously set data or data from cloud.
    /// </summary>
    void setName(String * name);
    /// <summary>
    /// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
    /// </summary>
    void meta(/* OUT */ String * * Return);
    /// <summary>
    /// Set meta data. It will erase previously set data or data from cloud.
    /// </summary>
    void setMeta(String * data);
    static void tryCastFromTarget(Target * v, /* OUT */ ObjectTarget * * Return);
};

#ifndef __EASYAR_OPTIONALOFOBJECTTARGET__
#define __EASYAR_OPTIONALOFOBJECTTARGET__
struct OptionalOfObjectTarget
{
    bool has_value;
    ObjectTarget * value;
};
static inline easyar_OptionalOfObjectTarget OptionalOfObjectTarget_to_c(ObjectTarget * o);
#endif

#ifndef __EASYAR_LISTOFOBJECTTARGET__
#define __EASYAR_LISTOFOBJECTTARGET__
class ListOfObjectTarget
{
private:
    easyar_ListOfObjectTarget * cdata_;
    virtual ListOfObjectTarget & operator=(const ListOfObjectTarget & data) { return *this; } //deleted
public:
    ListOfObjectTarget(easyar_ListOfObjectTarget * cdata);
    virtual ~ListOfObjectTarget();

    ListOfObjectTarget(const ListOfObjectTarget & data);
    const easyar_ListOfObjectTarget * get_cdata() const;
    easyar_ListOfObjectTarget * get_cdata();

    ListOfObjectTarget(easyar_ObjectTarget * * begin, easyar_ObjectTarget * * end);
    int size() const;
    ObjectTarget * at(int index) const;
};
#endif

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

#ifndef __IMPLEMENTATION_EASYAR_OBJECTTARGET_HXX__
#define __IMPLEMENTATION_EASYAR_OBJECTTARGET_HXX__

#include "easyar/objecttarget.h"
#include "easyar/buffer.hxx"
#include "easyar/target.hxx"
#include "easyar/vector.hxx"

namespace easyar {

inline ObjectTargetParameters::ObjectTargetParameters(easyar_ObjectTargetParameters * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ObjectTargetParameters::~ObjectTargetParameters()
{
    if (cdata_) {
        easyar_ObjectTargetParameters__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ObjectTargetParameters::ObjectTargetParameters(const ObjectTargetParameters & data)
    :
    cdata_(NULL)
{
    easyar_ObjectTargetParameters * cdata = NULL;
    easyar_ObjectTargetParameters__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ObjectTargetParameters * ObjectTargetParameters::get_cdata() const
{
    return cdata_;
}
inline easyar_ObjectTargetParameters * ObjectTargetParameters::get_cdata()
{
    return cdata_;
}
inline void ObjectTargetParameters::init_cdata(easyar_ObjectTargetParameters * cdata)
{
    cdata_ = cdata;
}
inline ObjectTargetParameters::ObjectTargetParameters()
    :
    cdata_(NULL)
{
    easyar_ObjectTargetParameters * _return_value_ = NULL;
    easyar_ObjectTargetParameters__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline void ObjectTargetParameters::bufferDictionary(/* OUT */ BufferDictionary * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_BufferDictionary * _return_value_ = NULL;
    easyar_ObjectTargetParameters_bufferDictionary(cdata_, &_return_value_);
    *Return = new BufferDictionary(_return_value_);
}
inline void ObjectTargetParameters::setBufferDictionary(BufferDictionary * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTargetParameters_setBufferDictionary(cdata_, arg0->get_cdata());
}
inline void ObjectTargetParameters::objPath(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTargetParameters_objPath(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTargetParameters::setObjPath(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTargetParameters_setObjPath(cdata_, arg0->get_cdata());
}
inline void ObjectTargetParameters::name(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTargetParameters_name(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTargetParameters::setName(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTargetParameters_setName(cdata_, arg0->get_cdata());
}
inline void ObjectTargetParameters::uid(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTargetParameters_uid(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTargetParameters::setUid(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTargetParameters_setUid(cdata_, arg0->get_cdata());
}
inline void ObjectTargetParameters::meta(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTargetParameters_meta(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTargetParameters::setMeta(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTargetParameters_setMeta(cdata_, arg0->get_cdata());
}
inline float ObjectTargetParameters::scale()
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_ObjectTargetParameters_scale(cdata_);
    return _return_value_;
}
inline void ObjectTargetParameters::setScale(float arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTargetParameters_setScale(cdata_, arg0);
}

inline ObjectTarget::ObjectTarget(easyar_ObjectTarget * cdata)
    :
    Target(static_cast<easyar_Target *>(NULL)),
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline ObjectTarget::~ObjectTarget()
{
    if (cdata_) {
        easyar_ObjectTarget__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ObjectTarget::ObjectTarget(const ObjectTarget & data)
    :
    Target(static_cast<easyar_Target *>(NULL)),
    cdata_(NULL)
{
    easyar_ObjectTarget * cdata = NULL;
    easyar_ObjectTarget__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_ObjectTarget * ObjectTarget::get_cdata() const
{
    return cdata_;
}
inline easyar_ObjectTarget * ObjectTarget::get_cdata()
{
    return cdata_;
}
inline void ObjectTarget::init_cdata(easyar_ObjectTarget * cdata)
{
    cdata_ = cdata;
    {
        easyar_Target * cdata_inner = NULL;
        easyar_castObjectTargetToTarget(cdata, &cdata_inner);
        Target::init_cdata(cdata_inner);
    }
}
inline ObjectTarget::ObjectTarget()
    :
    Target(static_cast<easyar_Target *>(NULL)),
    cdata_(NULL)
{
    easyar_ObjectTarget * _return_value_ = NULL;
    easyar_ObjectTarget__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline void ObjectTarget::createFromParameters(ObjectTargetParameters * arg0, /* OUT */ ObjectTarget * * Return)
{
    easyar_OptionalOfObjectTarget _return_value_ = {false, NULL};
    easyar_ObjectTarget_createFromParameters(arg0->get_cdata(), &_return_value_);
    *Return = (_return_value_.has_value ? new ObjectTarget(_return_value_.value) : NULL);
}
inline void ObjectTarget::createFromObjectFile(String * arg0, StorageType arg1, String * arg2, String * arg3, String * arg4, float arg5, /* OUT */ ObjectTarget * * Return)
{
    easyar_OptionalOfObjectTarget _return_value_ = {false, NULL};
    easyar_ObjectTarget_createFromObjectFile(arg0->get_cdata(), static_cast<easyar_StorageType>(arg1), arg2->get_cdata(), arg3->get_cdata(), arg4->get_cdata(), arg5, &_return_value_);
    *Return = (_return_value_.has_value ? new ObjectTarget(_return_value_.value) : NULL);
}
inline void ObjectTarget::setupAll(String * arg0, StorageType arg1, /* OUT */ ListOfObjectTarget * * Return)
{
    easyar_ListOfObjectTarget * _return_value_ = NULL;
    easyar_ObjectTarget_setupAll(arg0->get_cdata(), static_cast<easyar_StorageType>(arg1), &_return_value_);
    *Return = new ListOfObjectTarget(_return_value_);
}
inline float ObjectTarget::scale()
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_ObjectTarget_scale(cdata_);
    return _return_value_;
}
inline void ObjectTarget::boundingBox(/* OUT */ ListOfVec3F * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ListOfVec3F * _return_value_ = NULL;
    easyar_ObjectTarget_boundingBox(cdata_, &_return_value_);
    *Return = new ListOfVec3F(_return_value_);
}
inline bool ObjectTarget::setScale(float arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_ObjectTarget_setScale(cdata_, arg0);
    return _return_value_;
}
inline int ObjectTarget::runtimeID()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_ObjectTarget_runtimeID(cdata_);
    return _return_value_;
}
inline void ObjectTarget::uid(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTarget_uid(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTarget::name(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTarget_name(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTarget::setName(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTarget_setName(cdata_, arg0->get_cdata());
}
inline void ObjectTarget::meta(/* OUT */ String * * Return)
{
    if (cdata_ == NULL) {
        *Return = NULL;
        return;
    }
    easyar_String * _return_value_ = NULL;
    easyar_ObjectTarget_meta(cdata_, &_return_value_);
    *Return = new String(_return_value_);
}
inline void ObjectTarget::setMeta(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_ObjectTarget_setMeta(cdata_, arg0->get_cdata());
}
inline void ObjectTarget::tryCastFromTarget(Target * v, /* OUT */ ObjectTarget * * Return)
{
    if (v == NULL) {
        *Return = NULL;
        return;
    }
    easyar_ObjectTarget * cdata = NULL;
    easyar_tryCastTargetToObjectTarget(v->get_cdata(), &cdata);
    if (cdata == NULL) {
        *Return = NULL;
        return;
    }
    *Return = new ObjectTarget(cdata);
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFOBJECTTARGET__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFOBJECTTARGET__
static inline easyar_OptionalOfObjectTarget OptionalOfObjectTarget_to_c(ObjectTarget * o)
{
    if (o != NULL) {
        easyar_OptionalOfObjectTarget _return_value_ = {true, o->get_cdata()};
        return _return_value_;
    } else {
        easyar_OptionalOfObjectTarget _return_value_ = {false, NULL};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_LISTOFOBJECTTARGET__
#define __IMPLEMENTATION_EASYAR_LISTOFOBJECTTARGET__
inline ListOfObjectTarget::ListOfObjectTarget(easyar_ListOfObjectTarget * cdata)
    : cdata_(cdata)
{
}
inline ListOfObjectTarget::~ListOfObjectTarget()
{
    if (cdata_) {
        easyar_ListOfObjectTarget__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline ListOfObjectTarget::ListOfObjectTarget(const ListOfObjectTarget & data)
    : cdata_(static_cast<easyar_ListOfObjectTarget *>(NULL))
{
    easyar_ListOfObjectTarget_copy(data.cdata_, &cdata_);
}
inline const easyar_ListOfObjectTarget * ListOfObjectTarget::get_cdata() const
{
    return cdata_;
}
inline easyar_ListOfObjectTarget * ListOfObjectTarget::get_cdata()
{
    return cdata_;
}

inline ListOfObjectTarget::ListOfObjectTarget(easyar_ObjectTarget * * begin, easyar_ObjectTarget * * end)
    : cdata_(static_cast<easyar_ListOfObjectTarget *>(NULL))
{
    easyar_ListOfObjectTarget__ctor(begin, end, &cdata_);
}
inline int ListOfObjectTarget::size() const
{
    return easyar_ListOfObjectTarget_size(cdata_);
}
inline ObjectTarget * ListOfObjectTarget::at(int index) const
{
    easyar_ObjectTarget * _return_value_ = easyar_ListOfObjectTarget_at(cdata_, index);
    easyar_ObjectTarget__retain(_return_value_, &_return_value_);
    return new ObjectTarget(_return_value_);
}
#endif

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
