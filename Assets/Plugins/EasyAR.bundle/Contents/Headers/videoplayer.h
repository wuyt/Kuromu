//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_VIDEOPLAYER_H__
#define __EASYAR_VIDEOPLAYER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_VideoPlayer__ctor(/* OUT */ easyar_VideoPlayer * * Return);
/// <summary>
/// Checks if the component is available. It returns true only on Windows, Android or iOS. It&#39;s not available on Mac.
/// </summary>
bool easyar_VideoPlayer_isAvailable(void);
/// <summary>
/// Sets the video type. The type will default to normal video if not set manually. It should be called before open.
/// </summary>
void easyar_VideoPlayer_setVideoType(easyar_VideoPlayer * This, easyar_VideoType videoType);
/// <summary>
/// Passes the texture to display video into player. It should be set before open.
/// </summary>
void easyar_VideoPlayer_setRenderTexture(easyar_VideoPlayer * This, easyar_TextureId * texture);
/// <summary>
/// Opens a video from path.
/// path can be a local video file (path/to/video.mp4) or url (http://www.../.../video.mp4). storageType indicates the type of path. See `StorageType`_ for more description.
/// This method is an asynchronous method. Open may take some time to finish. If you want to know the open result or the play status while playing, you have to handle callback. The callback will be called from a different thread. You can check if the open finished successfully and start play after a successful open.
/// </summary>
void easyar_VideoPlayer_open(easyar_VideoPlayer * This, easyar_String * path, easyar_StorageType storageType, easyar_CallbackScheduler * callbackScheduler, easyar_OptionalOfFunctorOfVoidFromVideoStatus callback);
/// <summary>
/// Closes the video.
/// </summary>
void easyar_VideoPlayer_close(easyar_VideoPlayer * This);
/// <summary>
/// Starts or continues to play video.
/// </summary>
bool easyar_VideoPlayer_play(easyar_VideoPlayer * This);
/// <summary>
/// Stops the video playback.
/// </summary>
void easyar_VideoPlayer_stop(easyar_VideoPlayer * This);
/// <summary>
/// Pauses the video playback.
/// </summary>
void easyar_VideoPlayer_pause(easyar_VideoPlayer * This);
/// <summary>
/// Checks whether video texture is ready for render. Use this to check if texture passed into the player has been touched.
/// </summary>
bool easyar_VideoPlayer_isRenderTextureAvailable(easyar_VideoPlayer * This);
/// <summary>
/// Updates texture data. This should be called in the renderer thread when isRenderTextureAvailable returns true.
/// </summary>
void easyar_VideoPlayer_updateFrame(easyar_VideoPlayer * This);
/// <summary>
/// Returns the video duration. Use after a successful open.
/// </summary>
int easyar_VideoPlayer_duration(easyar_VideoPlayer * This);
/// <summary>
/// Returns the current position of video. Use after a successful open.
/// </summary>
int easyar_VideoPlayer_currentPosition(easyar_VideoPlayer * This);
/// <summary>
/// Seeks to play to position . Use after a successful open.
/// </summary>
bool easyar_VideoPlayer_seek(easyar_VideoPlayer * This, int position);
/// <summary>
/// Returns the video size. Use after a successful open.
/// </summary>
easyar_Vec2I easyar_VideoPlayer_size(easyar_VideoPlayer * This);
/// <summary>
/// Returns current volume. Use after a successful open.
/// </summary>
float easyar_VideoPlayer_volume(easyar_VideoPlayer * This);
/// <summary>
/// Sets volume of the video. Use after a successful open.
/// </summary>
bool easyar_VideoPlayer_setVolume(easyar_VideoPlayer * This, float volume);
void easyar_VideoPlayer__dtor(easyar_VideoPlayer * This);
void easyar_VideoPlayer__retain(const easyar_VideoPlayer * This, /* OUT */ easyar_VideoPlayer * * Return);
const char * easyar_VideoPlayer__typeName(const easyar_VideoPlayer * This);

#ifdef __cplusplus
}
#endif

#endif
