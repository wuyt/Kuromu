//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import "easyar/types.oc.h"

@interface easyar_CloudRecognizationResult : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns recognition status.
/// </summary>
- (easyar_CloudRecognizationStatus)getStatus;
/// <summary>
/// Returns the recognized target when status is FoundTarget.
/// </summary>
- (easyar_ImageTarget *)getTarget;
/// <summary>
/// Returns the error message when status is UnknownError.
/// </summary>
- (NSString *)getUnknownErrorMessage;

@end

/// <summary>
/// CloudRecognizer implements cloud recognition. It can only be used after created a recognition image library on the cloud. Please refer to EasyAR CRS documentation.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// Before using a CloudRecognizer, an `ImageTracker`_ must be setup and prepared. Any target returned from cloud should be manually put into the `ImageTracker`_ using `ImageTracker.loadTarget`_ if it need to be tracked. Then the target can be used as same as a local target after loaded into the tracker. When a target is recognized, you can get it from callback, and you should use target uid to distinguish different targets. The target runtimeID is dynamically created and cannot be used as unique identifier in the cloud situation.
/// </summary>
@interface easyar_CloudRecognizer : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns true.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Creates an instance and connects to the server.
/// </summary>
+ (easyar_CloudRecognizer *)create:(NSString *)cloudRecognitionServiceServerAddress apiKey:(NSString *)apiKey apiSecret:(NSString *)apiSecret cloudRecognitionServiceAppId:(NSString *)cloudRecognitionServiceAppId;
/// <summary>
/// Creates an instance and connects to the server with Cloud Secret.
/// </summary>
+ (easyar_CloudRecognizer *)createByCloudSecret:(NSString *)cloudRecognitionServiceServerAddress cloudRecognitionServiceSecret:(NSString *)cloudRecognitionServiceSecret cloudRecognitionServiceAppId:(NSString *)cloudRecognitionServiceAppId;
/// <summary>
/// Send recognition request. The lowest available request interval is 300ms.
/// </summary>
- (void)resolve:(easyar_InputFrame *)inputFrame callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler callback:(void (^)(easyar_CloudRecognizationResult * result))callback;
/// <summary>
/// Stops the recognition and closes connection. The component shall not be used after calling close.
/// </summary>
- (void)close;

@end
