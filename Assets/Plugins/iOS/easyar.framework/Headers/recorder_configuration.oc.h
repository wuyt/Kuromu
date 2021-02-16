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
/// RecorderConfiguration is startup configuration for `Recorder`_ .
/// </summary>
@interface easyar_RecorderConfiguration : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_RecorderConfiguration *) create;
/// <summary>
/// Sets absolute path for output video file.
/// </summary>
- (void)setOutputFile:(NSString *)path;
/// <summary>
/// Sets recording profile. Default value is Quality_720P_Middle.
/// This is an all-in-one configuration, you can control in more advanced mode with other APIs.
/// </summary>
- (bool)setProfile:(easyar_RecordProfile)profile;
/// <summary>
/// Sets recording video size. Default value is Vid720p.
/// </summary>
- (void)setVideoSize:(easyar_RecordVideoSize)framesize;
/// <summary>
/// Sets recording video bit rate. Default value is 2500000.
/// </summary>
- (void)setVideoBitrate:(int)bitrate;
/// <summary>
/// Sets recording audio channel count. Default value is 1.
/// </summary>
- (void)setChannelCount:(int)count;
/// <summary>
/// Sets recording audio sample rate. Default value is 44100.
/// </summary>
- (void)setAudioSampleRate:(int)samplerate;
/// <summary>
/// Sets recording audio bit rate. Default value is 96000.
/// </summary>
- (void)setAudioBitrate:(int)bitrate;
/// <summary>
/// Sets recording video orientation. Default value is Landscape.
/// </summary>
- (void)setVideoOrientation:(easyar_RecordVideoOrientation)mode;
/// <summary>
/// Sets recording zoom mode. Default value is NoZoomAndClip.
/// </summary>
- (void)setZoomMode:(easyar_RecordZoomMode)mode;

@end
