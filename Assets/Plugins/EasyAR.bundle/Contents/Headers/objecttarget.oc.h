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
/// ObjectTargetParameters represents the parameters to create a `ObjectTarget`_ .
/// </summary>
@interface easyar_ObjectTargetParameters : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_ObjectTargetParameters *) create;
/// <summary>
/// Gets `Buffer`_ dictionary.
/// </summary>
- (easyar_BufferDictionary *)bufferDictionary;
/// <summary>
/// Sets `Buffer`_ dictionary. obj, mtl and jpg/png files shall be loaded into the dictionay, and be able to be located by relative or absolute paths.
/// </summary>
- (void)setBufferDictionary:(easyar_BufferDictionary *)bufferDictionary;
/// <summary>
/// Gets obj file path.
/// </summary>
- (NSString *)objPath;
/// <summary>
/// Sets obj file path.
/// </summary>
- (void)setObjPath:(NSString *)objPath;
/// <summary>
/// Gets target name. It can be used to distinguish targets.
/// </summary>
- (NSString *)name;
/// <summary>
/// Sets target name.
/// </summary>
- (void)setName:(NSString *)name;
/// <summary>
/// Gets the target uid. You can set this uid in the json config as a method to distinguish from targets.
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
/// Gets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// </summary>
- (float)scale;
/// <summary>
/// Sets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// It is needed to set the model scale in rendering engine separately.
/// </summary>
- (void)setScale:(float)size;

@end

/// <summary>
/// ObjectTarget represents 3d object targets that can be tracked by `ObjectTracker`_ .
/// The size of ObjectTarget is determined by the `obj` file. You can change it by changing the object `scale`, which is default to 1.
/// A ObjectTarget can be tracked by `ObjectTracker`_ after a successful load into the `ObjectTracker`_ using `ObjectTracker.loadTarget`_ .
/// </summary>
@interface easyar_ObjectTarget : easyar_Target

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_ObjectTarget *) create;
/// <summary>
/// Creates a target from parameters.
/// </summary>
+ (easyar_ObjectTarget *)createFromParameters:(easyar_ObjectTargetParameters *)parameters;
/// <summary>
/// Creats a target from obj, mtl and jpg/png files.
/// </summary>
+ (easyar_ObjectTarget *)createFromObjectFile:(NSString *)path storageType:(easyar_StorageType)storageType name:(NSString *)name uid:(NSString *)uid meta:(NSString *)meta scale:(float)scale;
/// <summary>
/// The scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// </summary>
- (float)scale;
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
- (NSArray<easyar_Vec3F *> *)boundingBox;
/// <summary>
/// Sets model target scale, this will overwrite the value set in the json file or the default value. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
/// It is needed to set the model scale in rendering engine separately.
/// It also should been done before loading ObjectTarget into  `ObjectTracker`_ using `ObjectTracker.loadTarget`_.
/// </summary>
- (bool)setScale:(float)scale;
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
