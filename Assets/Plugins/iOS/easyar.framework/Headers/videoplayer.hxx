//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_VIDEOPLAYER_HXX__
#define __EASYAR_VIDEOPLAYER_HXX__

#include "easyar/types.hxx"

namespace easyar {

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
class VideoPlayer
{
protected:
    easyar_VideoPlayer * cdata_ ;
    void init_cdata(easyar_VideoPlayer * cdata);
    virtual VideoPlayer & operator=(const VideoPlayer & data) { return *this; } //deleted
public:
    VideoPlayer(easyar_VideoPlayer * cdata);
    virtual ~VideoPlayer();

    VideoPlayer(const VideoPlayer & data);
    const easyar_VideoPlayer * get_cdata() const;
    easyar_VideoPlayer * get_cdata();

    VideoPlayer();
    /// <summary>
    /// Checks if the component is available. It returns true only on Windows, Android or iOS. It&#39;s not available on Mac.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Sets the video type. The type will default to normal video if not set manually. It should be called before open.
    /// </summary>
    void setVideoType(VideoType videoType);
    /// <summary>
    /// Passes the texture to display video into player. It should be set before open.
    /// </summary>
    void setRenderTexture(TextureId * texture);
    /// <summary>
    /// Opens a video from path.
    /// path can be a local video file (path/to/video.mp4) or url (http://www.../.../video.mp4). storageType indicates the type of path. See `StorageType`_ for more description.
    /// This method is an asynchronous method. Open may take some time to finish. If you want to know the open result or the play status while playing, you have to handle callback. The callback will be called from a different thread. You can check if the open finished successfully and start play after a successful open.
    /// </summary>
    void open(String * path, StorageType storageType, CallbackScheduler * callbackScheduler, OptionalOfFunctorOfVoidFromVideoStatus callback);
    /// <summary>
    /// Closes the video.
    /// </summary>
    void close();
    /// <summary>
    /// Starts or continues to play video.
    /// </summary>
    bool play();
    /// <summary>
    /// Stops the video playback.
    /// </summary>
    void stop();
    /// <summary>
    /// Pauses the video playback.
    /// </summary>
    void pause();
    /// <summary>
    /// Checks whether video texture is ready for render. Use this to check if texture passed into the player has been touched.
    /// </summary>
    bool isRenderTextureAvailable();
    /// <summary>
    /// Updates texture data. This should be called in the renderer thread when isRenderTextureAvailable returns true.
    /// </summary>
    void updateFrame();
    /// <summary>
    /// Returns the video duration. Use after a successful open.
    /// </summary>
    int duration();
    /// <summary>
    /// Returns the current position of video. Use after a successful open.
    /// </summary>
    int currentPosition();
    /// <summary>
    /// Seeks to play to position . Use after a successful open.
    /// </summary>
    bool seek(int position);
    /// <summary>
    /// Returns the video size. Use after a successful open.
    /// </summary>
    Vec2I size();
    /// <summary>
    /// Returns current volume. Use after a successful open.
    /// </summary>
    float volume();
    /// <summary>
    /// Sets volume of the video. Use after a successful open.
    /// </summary>
    bool setVolume(float volume);
};

#ifndef __EASYAR_FUNCTOROFVOIDFROMVIDEOSTATUS__
#define __EASYAR_FUNCTOROFVOIDFROMVIDEOSTATUS__
struct FunctorOfVoidFromVideoStatus
{
    void * _state;
    void (* func)(void * _state, VideoStatus);
    void (* destroy)(void * _state);
    FunctorOfVoidFromVideoStatus(void * _state, void (* func)(void * _state, VideoStatus), void (* destroy)(void * _state));
};

static void FunctorOfVoidFromVideoStatus_func(void * _state, easyar_VideoStatus, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromVideoStatus_destroy(void * _state);
static inline easyar_FunctorOfVoidFromVideoStatus FunctorOfVoidFromVideoStatus_to_c(FunctorOfVoidFromVideoStatus f);
#endif

#ifndef __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMVIDEOSTATUS__
#define __EASYAR_OPTIONALOFFUNCTOROFVOIDFROMVIDEOSTATUS__
struct OptionalOfFunctorOfVoidFromVideoStatus
{
    bool has_value;
    FunctorOfVoidFromVideoStatus value;
};
static inline easyar_OptionalOfFunctorOfVoidFromVideoStatus OptionalOfFunctorOfVoidFromVideoStatus_to_c(OptionalOfFunctorOfVoidFromVideoStatus o);
#endif

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_VIDEOPLAYER_HXX__
#define __IMPLEMENTATION_EASYAR_VIDEOPLAYER_HXX__

#include "easyar/videoplayer.h"
#include "easyar/texture.hxx"
#include "easyar/callbackscheduler.hxx"
#include "easyar/vector.hxx"

namespace easyar {

inline VideoPlayer::VideoPlayer(easyar_VideoPlayer * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline VideoPlayer::~VideoPlayer()
{
    if (cdata_) {
        easyar_VideoPlayer__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline VideoPlayer::VideoPlayer(const VideoPlayer & data)
    :
    cdata_(NULL)
{
    easyar_VideoPlayer * cdata = NULL;
    easyar_VideoPlayer__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_VideoPlayer * VideoPlayer::get_cdata() const
{
    return cdata_;
}
inline easyar_VideoPlayer * VideoPlayer::get_cdata()
{
    return cdata_;
}
inline void VideoPlayer::init_cdata(easyar_VideoPlayer * cdata)
{
    cdata_ = cdata;
}
inline VideoPlayer::VideoPlayer()
    :
    cdata_(NULL)
{
    easyar_VideoPlayer * _return_value_ = NULL;
    easyar_VideoPlayer__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline bool VideoPlayer::isAvailable()
{
    bool _return_value_ = easyar_VideoPlayer_isAvailable();
    return _return_value_;
}
inline void VideoPlayer::setVideoType(VideoType arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_setVideoType(cdata_, static_cast<easyar_VideoType>(arg0));
}
inline void VideoPlayer::setRenderTexture(TextureId * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_setRenderTexture(cdata_, arg0->get_cdata());
}
inline void VideoPlayer::open(String * arg0, StorageType arg1, CallbackScheduler * arg2, OptionalOfFunctorOfVoidFromVideoStatus arg3)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_open(cdata_, arg0->get_cdata(), static_cast<easyar_StorageType>(arg1), arg2->get_cdata(), OptionalOfFunctorOfVoidFromVideoStatus_to_c(arg3));
}
inline void VideoPlayer::close()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_close(cdata_);
}
inline bool VideoPlayer::play()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_VideoPlayer_play(cdata_);
    return _return_value_;
}
inline void VideoPlayer::stop()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_stop(cdata_);
}
inline void VideoPlayer::pause()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_pause(cdata_);
}
inline bool VideoPlayer::isRenderTextureAvailable()
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_VideoPlayer_isRenderTextureAvailable(cdata_);
    return _return_value_;
}
inline void VideoPlayer::updateFrame()
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_VideoPlayer_updateFrame(cdata_);
}
inline int VideoPlayer::duration()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_VideoPlayer_duration(cdata_);
    return _return_value_;
}
inline int VideoPlayer::currentPosition()
{
    if (cdata_ == NULL) {
        return int();
    }
    int _return_value_ = easyar_VideoPlayer_currentPosition(cdata_);
    return _return_value_;
}
inline bool VideoPlayer::seek(int arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_VideoPlayer_seek(cdata_, arg0);
    return _return_value_;
}
inline Vec2I VideoPlayer::size()
{
    if (cdata_ == NULL) {
        return Vec2I();
    }
    easyar_Vec2I _return_value_ = easyar_VideoPlayer_size(cdata_);
    return Vec2I(_return_value_.data[0], _return_value_.data[1]);
}
inline float VideoPlayer::volume()
{
    if (cdata_ == NULL) {
        return float();
    }
    float _return_value_ = easyar_VideoPlayer_volume(cdata_);
    return _return_value_;
}
inline bool VideoPlayer::setVolume(float arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_VideoPlayer_setVolume(cdata_, arg0);
    return _return_value_;
}

#ifndef __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMVIDEOSTATUS__
#define __IMPLEMENTATION_EASYAR_OPTIONALOFFUNCTOROFVOIDFROMVIDEOSTATUS__
static inline easyar_OptionalOfFunctorOfVoidFromVideoStatus OptionalOfFunctorOfVoidFromVideoStatus_to_c(OptionalOfFunctorOfVoidFromVideoStatus o)
{
    if (o.has_value) {
        easyar_OptionalOfFunctorOfVoidFromVideoStatus _return_value_ = {true, FunctorOfVoidFromVideoStatus_to_c(o.value)};
        return _return_value_;
    } else {
        easyar_OptionalOfFunctorOfVoidFromVideoStatus _return_value_ = {false, {NULL, NULL, NULL}};
        return _return_value_;
    }
}
#endif

#ifndef __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMVIDEOSTATUS__
#define __IMPLEMENTATION_EASYAR_FUNCTOROFVOIDFROMVIDEOSTATUS__
inline FunctorOfVoidFromVideoStatus::FunctorOfVoidFromVideoStatus(void * _state, void (* func)(void * _state, VideoStatus), void (* destroy)(void * _state))
{
    this->_state = _state;
    this->func = func;
    this->destroy = destroy;
}
static void FunctorOfVoidFromVideoStatus_func(void * _state, easyar_VideoStatus arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = NULL;
    try {
        VideoStatus cpparg0 = static_cast<VideoStatus>(arg0);
        FunctorOfVoidFromVideoStatus * f = reinterpret_cast<FunctorOfVoidFromVideoStatus *>(_state);
        f->func(f->_state, cpparg0);
    } catch (std::exception & ex) {
        easyar_String_from_utf8_begin(ex.what(), _exception);
    }
}
static void FunctorOfVoidFromVideoStatus_destroy(void * _state)
{
    FunctorOfVoidFromVideoStatus * f = reinterpret_cast<FunctorOfVoidFromVideoStatus *>(_state);
    if (f->destroy) {
        f->destroy(f->_state);
    }
    delete f;
}
static inline easyar_FunctorOfVoidFromVideoStatus FunctorOfVoidFromVideoStatus_to_c(FunctorOfVoidFromVideoStatus f)
{
    easyar_FunctorOfVoidFromVideoStatus _return_value_ = {NULL, NULL, NULL};
    _return_value_._state = new FunctorOfVoidFromVideoStatus(f._state, f.func, f.destroy);
    _return_value_.func = FunctorOfVoidFromVideoStatus_func;
    _return_value_.destroy = FunctorOfVoidFromVideoStatus_destroy;
    return _return_value_;
}
#endif

}

#endif
