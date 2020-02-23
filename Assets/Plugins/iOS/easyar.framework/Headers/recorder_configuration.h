//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_RECORDER_CONFIGURATION_H__
#define __EASYAR_RECORDER_CONFIGURATION_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_RecorderConfiguration__ctor(/* OUT */ easyar_RecorderConfiguration * * Return);
/// <summary>
/// Sets absolute path for output video file.
/// </summary>
void easyar_RecorderConfiguration_setOutputFile(easyar_RecorderConfiguration * This, easyar_String * path);
/// <summary>
/// Sets recording profile. Default value is Quality_720P_Middle.
/// This is an all-in-one configuration, you can control in more advanced mode with other APIs.
/// </summary>
bool easyar_RecorderConfiguration_setProfile(easyar_RecorderConfiguration * This, easyar_RecordProfile profile);
/// <summary>
/// Sets recording video size. Default value is Vid720p.
/// </summary>
void easyar_RecorderConfiguration_setVideoSize(easyar_RecorderConfiguration * This, easyar_RecordVideoSize framesize);
/// <summary>
/// Sets recording video bit rate. Default value is 2500000.
/// </summary>
void easyar_RecorderConfiguration_setVideoBitrate(easyar_RecorderConfiguration * This, int bitrate);
/// <summary>
/// Sets recording audio channel count. Default value is 1.
/// </summary>
void easyar_RecorderConfiguration_setChannelCount(easyar_RecorderConfiguration * This, int count);
/// <summary>
/// Sets recording audio sample rate. Default value is 44100.
/// </summary>
void easyar_RecorderConfiguration_setAudioSampleRate(easyar_RecorderConfiguration * This, int samplerate);
/// <summary>
/// Sets recording audio bit rate. Default value is 96000.
/// </summary>
void easyar_RecorderConfiguration_setAudioBitrate(easyar_RecorderConfiguration * This, int bitrate);
/// <summary>
/// Sets recording video orientation. Default value is Landscape.
/// </summary>
void easyar_RecorderConfiguration_setVideoOrientation(easyar_RecorderConfiguration * This, easyar_RecordVideoOrientation mode);
/// <summary>
/// Sets recording zoom mode. Default value is NoZoomAndClip.
/// </summary>
void easyar_RecorderConfiguration_setZoomMode(easyar_RecorderConfiguration * This, easyar_RecordZoomMode mode);
void easyar_RecorderConfiguration__dtor(easyar_RecorderConfiguration * This);
void easyar_RecorderConfiguration__retain(const easyar_RecorderConfiguration * This, /* OUT */ easyar_RecorderConfiguration * * Return);
const char * easyar_RecorderConfiguration__typeName(const easyar_RecorderConfiguration * This);

#ifdef __cplusplus
}
#endif

#endif
