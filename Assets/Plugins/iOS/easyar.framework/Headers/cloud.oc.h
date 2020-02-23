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
/// CloudRecognizer implements cloud recognition. It can only be used after created a recognition image library on the cloud. Please refer to EasyAR CRS documentation.
/// CloudRecognizer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable running.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// CloudRecognizer inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
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
/// `InputFrame`_ input port. Raw image and timestamp are essential.
/// </summary>
- (easyar_InputFrameSink *)inputFrameSink;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Creates an instance and connects to the server.
/// </summary>
+ (easyar_CloudRecognizer *)create:(NSString *)cloudRecognitionServiceServerAddress apiKey:(NSString *)apiKey apiSecret:(NSString *)apiSecret cloudRecognitionServiceAppId:(NSString *)cloudRecognitionServiceAppId callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler callback:(void (^)(easyar_CloudStatus status, NSArray<easyar_Target *> * targets))callback;
/// <summary>
/// Starts the recognition.
/// </summary>
- (bool)start;
/// <summary>
/// Stops the recognition.
/// </summary>
- (void)stop;
/// <summary>
/// Stops the recognition and closes connection. The component shall not be used after calling close.
/// </summary>
- (void)close;

@end
