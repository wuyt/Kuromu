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
/// VideoPlayer is the class for video playback.
/// EasyAR supports normal videos, transparent videos and streaming videos. The video content will be rendered into a texture passed into the player through setRenderTexture.
/// This class only supports OpenGLES2 texture.
/// Due to the dependency to OpenGLES, every method in this class (including the destructor) has to be called in a single thread containing an OpenGLES context.
/// Current version requires width and height being mutiples of 16.
///
/// Supported video file formats
/// Windows: Media Foundation-compatible formats, more can be supported via extra codecs. Please refer to `Supported Media Formats in Media Foundation &lt;https://docs.microsoft.com/en-us/windows/win32/medfound/supported-media-formats-in-media-foundation&gt;`__ . DirectShow is not supported.
/// Mac: Not supported.
/// Android: System supported formats. Please refer to `Supported media formats &lt;https://developer.android.com/guide/topics/media/media-formats&gt;`__ .
/// iOS: System supported formats. There is no reference in effect currently.
/// </summary>
@interface easyar_VideoPlayer : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_VideoPlayer *) create;
/// <summary>
/// Checks if the component is available. It returns true only on Windows, Android or iOS. It&#39;s not available on Mac.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Sets the video type. The type will default to normal video if not set manually. It should be called before open.
/// </summary>
- (void)setVideoType:(easyar_VideoType)videoType;
/// <summary>
/// Passes the texture to display video into player. It should be set before open.
/// </summary>
- (void)setRenderTexture:(easyar_TextureId *)texture;
/// <summary>
/// Opens a video from path.
/// path can be a local video file (path/to/video.mp4) or url (http://www.../.../video.mp4). storageType indicates the type of path. See `StorageType`_ for more description.
/// This method is an asynchronous method. Open may take some time to finish. If you want to know the open result or the play status while playing, you have to handle callback. The callback will be called from a different thread. You can check if the open finished successfully and start play after a successful open.
/// </summary>
- (void)open:(NSString *)path storageType:(easyar_StorageType)storageType callbackScheduler:(easyar_CallbackScheduler *)callbackScheduler callback:(void (^)(easyar_VideoStatus status))callback;
/// <summary>
/// Closes the video.
/// </summary>
- (void)close;
/// <summary>
/// Starts or continues to play video.
/// </summary>
- (bool)play;
/// <summary>
/// Stops the video playback.
/// </summary>
- (void)stop;
/// <summary>
/// Pauses the video playback.
/// </summary>
- (void)pause;
/// <summary>
/// Checks whether video texture is ready for render. Use this to check if texture passed into the player has been touched.
/// </summary>
- (bool)isRenderTextureAvailable;
/// <summary>
/// Updates texture data. This should be called in the renderer thread when isRenderTextureAvailable returns true.
/// </summary>
- (void)updateFrame;
/// <summary>
/// Returns the video duration. Use after a successful open.
/// </summary>
- (int)duration;
/// <summary>
/// Returns the current position of video. Use after a successful open.
/// </summary>
- (int)currentPosition;
/// <summary>
/// Seeks to play to position . Use after a successful open.
/// </summary>
- (bool)seek:(int)position;
/// <summary>
/// Returns the video size. Use after a successful open.
/// </summary>
- (easyar_Vec2I *)size;
/// <summary>
/// Returns current volume. Use after a successful open.
/// </summary>
- (float)volume;
/// <summary>
/// Sets volume of the video. Use after a successful open.
/// </summary>
- (bool)setVolume:(float)volume;

@end
