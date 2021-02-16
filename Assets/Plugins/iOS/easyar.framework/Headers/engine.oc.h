//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

@interface easyar_Engine : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Gets the version schema hash, which can be used to ensure type declarations consistent with runtime library.
/// </summary>
+ (int)schemaHash;
+ (bool)initialize:(NSString *)key;
/// <summary>
/// Handles the app onPause, pauses internal tasks.
/// </summary>
+ (void)onPause;
/// <summary>
/// Handles the app onResume, resumes internal tasks.
/// </summary>
+ (void)onResume;
/// <summary>
/// Gets error message on initialization failure.
/// </summary>
+ (NSString *)errorMessage;
/// <summary>
/// Gets the version number of EasyARSense.
/// </summary>
+ (NSString *)versionString;
/// <summary>
/// Gets the product name of EasyARSense. (Including variant, operating system and CPU architecture.)
/// </summary>
+ (NSString *)name;

@end
