//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGETARGET_H__
#define __EASYAR_IMAGETARGET_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_ImageTargetParameters__ctor(/* OUT */ easyar_ImageTargetParameters * * Return);
/// <summary>
/// Gets image.
/// </summary>
void easyar_ImageTargetParameters_image(easyar_ImageTargetParameters * This, /* OUT */ easyar_Image * * Return);
/// <summary>
/// Sets image.
/// </summary>
void easyar_ImageTargetParameters_setImage(easyar_ImageTargetParameters * This, easyar_Image * image);
/// <summary>
/// Gets target name. It can be used to distinguish targets.
/// </summary>
void easyar_ImageTargetParameters_name(easyar_ImageTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets target name.
/// </summary>
void easyar_ImageTargetParameters_setName(easyar_ImageTargetParameters * This, easyar_String * name);
/// <summary>
/// Gets the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as an alternative method to distinguish from targets.
/// </summary>
void easyar_ImageTargetParameters_uid(easyar_ImageTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets target uid.
/// </summary>
void easyar_ImageTargetParameters_setUid(easyar_ImageTargetParameters * This, easyar_String * uid);
/// <summary>
/// Gets meta data.
/// </summary>
void easyar_ImageTargetParameters_meta(easyar_ImageTargetParameters * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Sets meta data。
/// </summary>
void easyar_ImageTargetParameters_setMeta(easyar_ImageTargetParameters * This, easyar_String * meta);
/// <summary>
/// Gets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
/// </summary>
float easyar_ImageTargetParameters_scale(easyar_ImageTargetParameters * This);
/// <summary>
/// Sets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
/// It is needed to set the model scale in rendering engine separately.
/// </summary>
void easyar_ImageTargetParameters_setScale(easyar_ImageTargetParameters * This, float scale);
void easyar_ImageTargetParameters__dtor(easyar_ImageTargetParameters * This);
void easyar_ImageTargetParameters__retain(const easyar_ImageTargetParameters * This, /* OUT */ easyar_ImageTargetParameters * * Return);
const char * easyar_ImageTargetParameters__typeName(const easyar_ImageTargetParameters * This);

void easyar_ImageTarget__ctor(/* OUT */ easyar_ImageTarget * * Return);
/// <summary>
/// Creates a target from parameters.
/// </summary>
void easyar_ImageTarget_createFromParameters(easyar_ImageTargetParameters * parameters, /* OUT */ easyar_OptionalOfImageTarget * Return);
/// <summary>
/// Creates a target from an etd file.
/// </summary>
void easyar_ImageTarget_createFromTargetFile(easyar_String * path, easyar_StorageType storageType, /* OUT */ easyar_OptionalOfImageTarget * Return);
/// <summary>
/// Creates a target from an etd data buffer.
/// </summary>
void easyar_ImageTarget_createFromTargetData(easyar_Buffer * buffer, /* OUT */ easyar_OptionalOfImageTarget * Return);
/// <summary>
/// Saves as an etd file.
/// </summary>
bool easyar_ImageTarget_save(easyar_ImageTarget * This, easyar_String * path);
/// <summary>
/// Creates a target from an image file. If not needed, name, uid, meta can be passed with empty string, and scale can be passed with default value 1.
/// </summary>
void easyar_ImageTarget_createFromImageFile(easyar_String * path, easyar_StorageType storageType, easyar_String * name, easyar_String * uid, easyar_String * meta, float scale, /* OUT */ easyar_OptionalOfImageTarget * Return);
/// <summary>
/// Setup all targets listed in the json file or json string from path with storageType. This method only parses the json file or string.
/// If path is json file path, storageType should be `App` or `Assets` or `Absolute` indicating the path type. Paths inside json files should be absolute path or relative path to the json file.
/// See `StorageType`_ for more descriptions.
/// </summary>
void easyar_ImageTarget_setupAll(easyar_String * path, easyar_StorageType storageType, /* OUT */ easyar_ListOfImageTarget * * Return);
/// <summary>
/// The scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
/// </summary>
float easyar_ImageTarget_scale(const easyar_ImageTarget * This);
/// <summary>
/// The aspect ratio of image, width divided by height.
/// </summary>
float easyar_ImageTarget_aspectRatio(const easyar_ImageTarget * This);
/// <summary>
/// Sets image target scale, this will overwrite the value set in the json file or the default value. The value is the physical image width divided by 1 meter. The default value is 1.
/// It is needed to set the model scale in rendering engine separately.
/// </summary>
bool easyar_ImageTarget_setScale(easyar_ImageTarget * This, float scale);
/// <summary>
/// Returns a list of images that stored in the target. It is generally used to get image data from cloud returned target.
/// </summary>
void easyar_ImageTarget_images(easyar_ImageTarget * This, /* OUT */ easyar_ListOfImage * * Return);
/// <summary>
/// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
/// </summary>
int easyar_ImageTarget_runtimeID(const easyar_ImageTarget * This);
/// <summary>
/// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
/// </summary>
void easyar_ImageTarget_uid(const easyar_ImageTarget * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Returns the target name. Name is used to distinguish targets in a json file.
/// </summary>
void easyar_ImageTarget_name(const easyar_ImageTarget * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Set name. It will erase previously set data or data from cloud.
/// </summary>
void easyar_ImageTarget_setName(easyar_ImageTarget * This, easyar_String * name);
/// <summary>
/// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
/// </summary>
void easyar_ImageTarget_meta(const easyar_ImageTarget * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Set meta data. It will erase previously set data or data from cloud.
/// </summary>
void easyar_ImageTarget_setMeta(easyar_ImageTarget * This, easyar_String * data);
void easyar_ImageTarget__dtor(easyar_ImageTarget * This);
void easyar_ImageTarget__retain(const easyar_ImageTarget * This, /* OUT */ easyar_ImageTarget * * Return);
const char * easyar_ImageTarget__typeName(const easyar_ImageTarget * This);
void easyar_castImageTargetToTarget(const easyar_ImageTarget * This, /* OUT */ easyar_Target * * Return);
void easyar_tryCastTargetToImageTarget(const easyar_Target * This, /* OUT */ easyar_ImageTarget * * Return);

void easyar_ListOfImageTarget__ctor(easyar_ImageTarget * const * begin, easyar_ImageTarget * const * end, /* OUT */ easyar_ListOfImageTarget * * Return);
void easyar_ListOfImageTarget__dtor(easyar_ListOfImageTarget * This);
void easyar_ListOfImageTarget_copy(const easyar_ListOfImageTarget * This, /* OUT */ easyar_ListOfImageTarget * * Return);
int easyar_ListOfImageTarget_size(const easyar_ListOfImageTarget * This);
easyar_ImageTarget * easyar_ListOfImageTarget_at(const easyar_ListOfImageTarget * This, int index);

void easyar_ListOfImage__ctor(easyar_Image * const * begin, easyar_Image * const * end, /* OUT */ easyar_ListOfImage * * Return);
void easyar_ListOfImage__dtor(easyar_ListOfImage * This);
void easyar_ListOfImage_copy(const easyar_ListOfImage * This, /* OUT */ easyar_ListOfImage * * Return);
int easyar_ListOfImage_size(const easyar_ListOfImage * This);
easyar_Image * easyar_ListOfImage_at(const easyar_ListOfImage * This, int index);

#ifdef __cplusplus
}
#endif

#endif
