//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_OBJECTTARGET_H__
#define __EASYAR_OBJECTTARGET_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_ObjectTargetParameters__ctor(/* OUT */ easyar_ObjectTargetParameters * * Return);
/// <summary>
/// Gets `Buffer`_ dictionary.
/// </summary>
void easyar_ObjectTargetParameters_bufferDictionary(easyar_ObjectTargetParameters * This, /* OUT */ easyar_BufferDictionary * * Return);
/// <summary>
/// Sets `Buffer`_ dictionary. obj, mtl and jpg/png files shall be loaded into the dictionay, and be able to be located by relative or absolute paths.
/// </summary>
void easyar_ObjectTargetParameters_setBufferDictionary(easyar_ObjectTargetParameters * This, easyar_BufferDictionary * bufferDictionary);
/// <summary>
/// Gets obj file path.
/// </summary>
void easyar_ObjectTargetParameters_objPath(easyar_ObjectTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets obj file path.
/// </summary>
void easyar_ObjectTargetParameters_setObjPath(easyar_ObjectTargetParameters * This, easyar_String * objPath);
/// <summary>
/// Gets target name. It can be used to distinguish targets.
/// </summary>
void easyar_ObjectTargetParameters_name(easyar_ObjectTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets target name.
/// </summary>
void easyar_ObjectTargetParameters_setName(easyar_ObjectTargetParameters * This, easyar_String * name);
/// <summary>
/// Gets the target uid. You can set this uid in the json config as a method to distinguish from targets.
/// </summary>
void easyar_ObjectTargetParameters_uid(easyar_ObjectTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets target uid.
/// </summary>
void easyar_ObjectTargetParameters_setUid(easyar_ObjectTargetParameters * This, easyar_String * uid);
/// <summary>
/// Gets meta data.
/// </summary>
void easyar_ObjectTargetParameters_meta(easyar_ObjectTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets meta data。
/// </summary>
void easyar_ObjectTargetParameters_setMeta(easyar_ObjectTargetParameters * This, easyar_String * meta);
/// <summary>
/// Gets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// </summary>
float easyar_ObjectTargetParameters_scale(easyar_ObjectTargetParameters * This);
/// <summary>
/// Sets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// It is needed to set the model scale in rendering engine separately.
/// </summary>
void easyar_ObjectTargetParameters_setScale(easyar_ObjectTargetParameters * This, float size);
void easyar_ObjectTargetParameters__dtor(easyar_ObjectTargetParameters * This);
void easyar_ObjectTargetParameters__retain(const easyar_ObjectTargetParameters * This, /* OUT */ easyar_ObjectTargetParameters * * Return);
const char * easyar_ObjectTargetParameters__typeName(const easyar_ObjectTargetParameters * This);

void easyar_ObjectTarget__ctor(/* OUT */ easyar_ObjectTarget * * Return);
/// <summary>
/// Creates a target from parameters.
/// </summary>
void easyar_ObjectTarget_createFromParameters(easyar_ObjectTargetParameters * parameters, /* OUT */ easyar_OptionalOfObjectTarget * Return);
/// <summary>
/// Creats a target from obj, mtl and jpg/png files.
/// </summary>
void easyar_ObjectTarget_createFromObjectFile(easyar_String * path, easyar_StorageType storageType, easyar_String * name, easyar_String * uid, easyar_String * meta, float scale, /* OUT */ easyar_OptionalOfObjectTarget * Return);
/// <summary>
/// The scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// </summary>
float easyar_ObjectTarget_scale(const easyar_ObjectTarget * This);
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
void easyar_ObjectTarget_boundingBox(easyar_ObjectTarget * This, /* OUT */ easyar_ListOfVec3F * * Return);
/// <summary>
/// Sets model target scale, this will overwrite the value set in the json file or the default value. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// It is needed to set the model scale in rendering engine separately.
/// It also should been done before loading ObjectTarget into  `ObjectTracker`_ using `ObjectTracker.loadTarget`_.
/// </summary>
bool easyar_ObjectTarget_setScale(easyar_ObjectTarget * This, float scale);
/// <summary>
/// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
/// </summary>
int easyar_ObjectTarget_runtimeID(const easyar_ObjectTarget * This);
/// <summary>
/// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
/// </summary>
void easyar_ObjectTarget_uid(const easyar_ObjectTarget * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Returns the target name. Name is used to distinguish targets in a json file.
/// </summary>
void easyar_ObjectTarget_name(const easyar_ObjectTarget * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Set name. It will erase previously set data or data from cloud.
/// </summary>
void easyar_ObjectTarget_setName(easyar_ObjectTarget * This, easyar_String * name);
/// <summary>
/// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
/// </summary>
void easyar_ObjectTarget_meta(const easyar_ObjectTarget * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Set meta data. It will erase previously set data or data from cloud.
/// </summary>
void easyar_ObjectTarget_setMeta(easyar_ObjectTarget * This, easyar_String * data);
void easyar_ObjectTarget__dtor(easyar_ObjectTarget * This);
void easyar_ObjectTarget__retain(const easyar_ObjectTarget * This, /* OUT */ easyar_ObjectTarget * * Return);
const char * easyar_ObjectTarget__typeName(const easyar_ObjectTarget * This);
void easyar_castObjectTargetToTarget(const easyar_ObjectTarget * This, /* OUT */ easyar_Target * * Return);
void easyar_tryCastTargetToObjectTarget(const easyar_Target * This, /* OUT */ easyar_ObjectTarget * * Return);

void easyar_ListOfVec3F__ctor(easyar_Vec3F const * begin, easyar_Vec3F const * end, /* OUT */ easyar_ListOfVec3F * * Return);
void easyar_ListOfVec3F__dtor(easyar_ListOfVec3F * This);
void easyar_ListOfVec3F_copy(const easyar_ListOfVec3F * This, /* OUT */ easyar_ListOfVec3F * * Return);
int easyar_ListOfVec3F_size(const easyar_ListOfVec3F * This);
easyar_Vec3F easyar_ListOfVec3F_at(const easyar_ListOfVec3F * This, int index);

#ifdef __cplusplus
}
#endif

#endif
