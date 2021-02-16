//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

/// <summary>
/// record
/// Square matrix of 4. The data arrangement is row-major.
/// </summary>
@interface easyar_Matrix44F : NSObject

/// <summary>
/// The raw data of matrix.
/// </summary>
@property (nonatomic) NSArray<NSNumber *> * data;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)create:(NSArray<NSNumber *> *)data;

@end

/// <summary>
/// record
/// Square matrix of 3. The data arrangement is row-major.
/// </summary>
@interface easyar_Matrix33F : NSObject

/// <summary>
/// The raw data of matrix.
/// </summary>
@property (nonatomic) NSArray<NSNumber *> * data;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)create:(NSArray<NSNumber *> *)data;

@end
