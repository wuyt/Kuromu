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
/// Input frame recorder.
/// There is an input frame input port and an input frame output port. It can be used to record input frames into an EIF file. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFrameRecorder : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Input port.
/// </summary>
- (easyar_InputFrameSink *)input;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Output port.
/// </summary>
- (easyar_InputFrameSource *)output;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFrameRecorder *)create;
/// <summary>
/// Starts frame recording.
/// </summary>
- (bool)start:(NSString *)filePath;
/// <summary>
/// Stops frame recording. It will only stop recording and will not affect connection.
/// </summary>
- (void)stop;

@end

/// <summary>
/// Input frame player.
/// There is an input frame output port. It can be used to get input frame from an EIF file. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
@interface easyar_InputFramePlayer : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Output port.
/// </summary>
- (easyar_InputFrameSource *)output;
/// <summary>
/// Creates an instance.
/// </summary>
+ (easyar_InputFramePlayer *)create;
/// <summary>
/// Starts frame play.
/// </summary>
- (bool)start:(NSString *)filePath;
/// <summary>
/// Stops frame play.
/// </summary>
- (void)stop;

@end
