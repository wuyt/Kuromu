//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// SparseSpatialMap manager class, for managing sharing.
/// </summary>
@interface easyar_SparseSpatialMapManager : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Check whether SparseSpatialMapManager is is available. It returns true when the operating system is Mac, iOS or Android.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_SparseSpatialMapManager *)create;
/// <summary>
/// Creates a map from `SparseSpatialMap`_ and upload it to EasyAR cloud servers. After completion, a serverMapId will be returned for loading map from EasyAR cloud servers.
/// </summary>
- (void)host:(easyar_SparseSpatialMap *)mapBuilder apiKey:(NSString *)apiKey apiSecret:(NSString *)apiSecret sparseSpatialMapAppId:(NSString *)sparseSpatialMapAppId name:(NSString *)name preview:(easyar_Image *)preview callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler onCompleted:(void (^)(bool isSuccessful, NSString * serverMapId, NSString * error))onCompleted;
/// <summary>
/// Loads a map from EasyAR cloud servers by serverMapId. To unload the map, call `SparseSpatialMap.unloadMap`_ with serverMapId.
/// </summary>
- (void)load:(easyar_SparseSpatialMap *)mapTracker serverMapId:(NSString *)serverMapId apiKey:(NSString *)apiKey apiSecret:(NSString *)apiSecret sparseSpatialMapAppId:(NSString *)sparseSpatialMapAppId callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler onCompleted:(void (^)(bool isSuccessful, NSString * error))onCompleted;
/// <summary>
/// Clears allocated cache space.
/// </summary>
- (void)clear;

@end
