//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"
#import "easyar/target.oc.h"

/// <summary>
/// ImageTargetParameters represents the parameters to create a `ImageTarget`_ .
/// </summary>
@interface easyar_ImageTargetParameters : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_ImageTargetParameters *) create;
/// <summary>
/// Gets image.
/// </summary>
- (easyar_Image *)image;
/// <summary>
/// Sets image.
/// </summary>
- (void)setImage:(easyar_Image *)image;
/// <summary>
/// Gets target name. It can be used to distinguish targets.
/// </summary>
- (NSString *)name;
/// <summary>
/// Sets target name.
/// </summary>
- (void)setName:(NSString *)name;
/// <summary>
/// Gets the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as an alternative method to distinguish from targets.
/// </summary>
- (NSString *)uid;
/// <summary>
/// Sets target uid.
/// </summary>
- (void)setUid:(NSString *)uid;
/// <summary>
/// Gets meta data.
/// </summary>
- (NSString *)meta;
/// <summary>
/// Sets meta data。
/// </summary>
- (void)setMeta:(NSString *)meta;
/// <summary>
/// Gets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
/// </summary>
- (float)scale;
/// <summary>
/// Sets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
/// It is needed to set the model scale in rendering engine separately.
/// </summary>
- (void)setScale:(float)scale;

@end

/// <summary>
/// ImageTarget represents planar image targets that can be tracked by `ImageTracker`_ .
/// The fields of ImageTarget need to be filled with the create... method before it can be read. And ImageTarget can be tracked by `ImageTracker`_ after a successful load into the `ImageTracker`_ using `ImageTracker.loadTarget`_ .
/// </summary>
@interface easyar_ImageTarget : easyar_Target

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_ImageTarget *) create;
/// <summary>
/// Creates a target from parameters.
/// </summary>
+ (easyar_ImageTarget *)createFromParameters:(easyar_ImageTargetParameters *)parameters;
/// <summary>
/// Creates a target from an etd file.
/// </summary>
+ (easyar_ImageTarget *)createFromTargetFile:(NSString *)path storageType:(easyar_StorageType)storageType;
/// <summary>
/// Creates a target from an etd data buffer.
/// </summary>
+ (easyar_ImageTarget *)createFromTargetData:(easyar_Buffer *)buffer;
/// <summary>
/// Saves as an etd file.
/// </summary>
- (bool)save:(NSString *)path;
/// <summary>
/// Creates a target from an image file. If not needed, name, uid, meta can be passed with empty string, and scale can be passed with default value 1. Jpeg and png files are supported.
/// </summary>
+ (easyar_ImageTarget *)createFromImageFile:(NSString *)path storageType:(easyar_StorageType)storageType name:(NSString *)name uid:(NSString *)uid meta:(NSString *)meta scale:(float)scale;
/// <summary>
/// The scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
/// </summary>
- (float)scale;
/// <summary>
/// The aspect ratio of image, width divided by height.
/// </summary>
- (float)aspectRatio;
/// <summary>
/// Sets image target scale, this will overwrite the value set in the json file or the default value. The value is the physical image width divided by 1 meter. The default value is 1.
/// It is needed to set the model scale in rendering engine separately.
/// </summary>
- (bool)setScale:(float)scale;
/// <summary>
/// Returns a list of images that stored in the target. It is generally used to get image data from cloud returned target.
/// </summary>
- (NSArray<easyar_Image *> *)images;
/// <summary>
/// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
/// </summary>
- (int)runtimeID;
/// <summary>
/// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
/// </summary>
- (NSString *)uid;
/// <summary>
/// Returns the target name. Name is used to distinguish targets in a json file.
/// </summary>
- (NSString *)name;
/// <summary>
/// Set name. It will erase previously set data or data from cloud.
/// </summary>
- (void)setName:(NSString *)name;
/// <summary>
/// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
/// </summary>
- (NSString *)meta;
/// <summary>
/// Set meta data. It will erase previously set data or data from cloud.
/// </summary>
- (void)setMeta:(NSString *)data;

@end
