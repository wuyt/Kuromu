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
/// Log class.
/// It is used to setup a custom log output function.
/// </summary>
@interface easyar_Log : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Sets custom log output function.
/// </summary>
+ (void)setLogFunc:(void (^)(easyar_LogLevel level, NSString * message))func;
/// <summary>
/// Clears custom log output function and reverts to default log output function.
/// </summary>
+ (void)resetLogFunc;

@end
