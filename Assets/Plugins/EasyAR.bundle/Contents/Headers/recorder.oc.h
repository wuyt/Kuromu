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
/// Recorder implements recording for current rendering screen.
/// Currently Recorder only works on Android (4.3 or later) and iOS with OpenGL ES 2.0 context.
/// Due to the dependency to OpenGLES, every method in this class (except requestPermissions, including the destructor) has to be called in a single thread containing an OpenGLES context.
/// **Unity Only** If in Unity, Multi-threaded rendering is enabled, scripting thread and rendering thread will be two separate threads, which makes it impossible to call updateFrame in the rendering thread. For this reason, to use Recorder, Multi-threaded rendering option shall be disabled.
/// </summary>
@interface easyar_Recorder : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns true only on Android 4.3 or later, or on iOS.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Requests recording permissions from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
/// </summary>
+ (void)requestPermissions:(easyar_CallbackScheduler *)callbackScheduler permissionCallback:(void (^)(easyar_PermissionStatus status, NSString * value))permissionCallback;
/// <summary>
/// Creates an instance and initialize recording. statusCallback will dispatch event of status change and corresponding log.
/// </summary>
+ (easyar_Recorder *)create:(easyar_RecorderConfiguration *)config callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler statusCallback:(void (^)(easyar_RecordStatus status, NSString * value))statusCallback;
/// <summary>
/// Start recording.
/// </summary>
- (void)start;
/// <summary>
/// Update and record a frame using texture data.
/// </summary>
- (void)updateFrame:(easyar_TextureId *)texture width:(int)width height:(int)height;
/// <summary>
/// Stop recording. When calling stop, it will wait for file write to end and returns whether recording is successful.
/// </summary>
- (bool)stop;

@end
