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
/// Callback scheduler.
/// There are two subclasses: `DelayedCallbackScheduler`_ and `ImmediateCallbackScheduler`_ .
/// `DelayedCallbackScheduler`_ is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// `ImmediateCallbackScheduler`_ is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// </summary>
@interface easyar_CallbackScheduler : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

/// <summary>
/// Delayed callback scheduler.
/// It is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_DelayedCallbackScheduler : easyar_CallbackScheduler

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_DelayedCallbackScheduler *) create;
/// <summary>
/// Executes a callback. If there is no callback to execute, false is returned.
/// </summary>
- (bool)runOne;

@end

/// <summary>
/// Immediate callback scheduler.
/// It is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_ImmediateCallbackScheduler : easyar_CallbackScheduler

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Gets a default immediate callback scheduler.
/// </summary>
+ (easyar_ImmediateCallbackScheduler *)getDefault;

@end
