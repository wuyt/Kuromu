//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_RECORDER_CONFIGURATION_HXX__
#define __EASYAR_RECORDER_CONFIGURATION_HXX__

#include "easyar/types.hxx"

namespace easyar {

/// <summary>
/// RecorderConfiguration is startup configuration for `Recorder`_ .
/// </summary>
class RecorderConfiguration
{
protected:
    easyar_RecorderConfiguration * cdata_ ;
    void init_cdata(easyar_RecorderConfiguration * cdata);
    virtual RecorderConfiguration & operator=(const RecorderConfiguration & data) { return *this; } //deleted
public:
    RecorderConfiguration(easyar_RecorderConfiguration * cdata);
    virtual ~RecorderConfiguration();

    RecorderConfiguration(const RecorderConfiguration & data);
    const easyar_RecorderConfiguration * get_cdata() const;
    easyar_RecorderConfiguration * get_cdata();

    RecorderConfiguration();
    /// <summary>
    /// Sets absolute path for output video file.
    /// </summary>
    void setOutputFile(String * path);
    /// <summary>
    /// Sets recording profile. Default value is Quality_720P_Middle.
    /// This is an all-in-one configuration, you can control in more advanced mode with other APIs.
    /// </summary>
    bool setProfile(RecordProfile profile);
    /// <summary>
    /// Sets recording video size. Default value is Vid720p.
    /// </summary>
    void setVideoSize(RecordVideoSize framesize);
    /// <summary>
    /// Sets recording video bit rate. Default value is 2500000.
    /// </summary>
    void setVideoBitrate(int bitrate);
    /// <summary>
    /// Sets recording audio channel count. Default value is 1.
    /// </summary>
    void setChannelCount(int count);
    /// <summary>
    /// Sets recording audio sample rate. Default value is 44100.
    /// </summary>
    void setAudioSampleRate(int samplerate);
    /// <summary>
    /// Sets recording audio bit rate. Default value is 96000.
    /// </summary>
    void setAudioBitrate(int bitrate);
    /// <summary>
    /// Sets recording video orientation. Default value is Landscape.
    /// </summary>
    void setVideoOrientation(RecordVideoOrientation mode);
    /// <summary>
    /// Sets recording zoom mode. Default value is NoZoomAndClip.
    /// </summary>
    void setZoomMode(RecordZoomMode mode);
};

}

#endif

#ifndef __IMPLEMENTATION_EASYAR_RECORDER_CONFIGURATION_HXX__
#define __IMPLEMENTATION_EASYAR_RECORDER_CONFIGURATION_HXX__

#include "easyar/recorder_configuration.h"

namespace easyar {

inline RecorderConfiguration::RecorderConfiguration(easyar_RecorderConfiguration * cdata)
    :
    cdata_(NULL)
{
    init_cdata(cdata);
}
inline RecorderConfiguration::~RecorderConfiguration()
{
    if (cdata_) {
        easyar_RecorderConfiguration__dtor(cdata_);
        cdata_ = NULL;
    }
}

inline RecorderConfiguration::RecorderConfiguration(const RecorderConfiguration & data)
    :
    cdata_(NULL)
{
    easyar_RecorderConfiguration * cdata = NULL;
    easyar_RecorderConfiguration__retain(data.cdata_, &cdata);
    init_cdata(cdata);
}
inline const easyar_RecorderConfiguration * RecorderConfiguration::get_cdata() const
{
    return cdata_;
}
inline easyar_RecorderConfiguration * RecorderConfiguration::get_cdata()
{
    return cdata_;
}
inline void RecorderConfiguration::init_cdata(easyar_RecorderConfiguration * cdata)
{
    cdata_ = cdata;
}
inline RecorderConfiguration::RecorderConfiguration()
    :
    cdata_(NULL)
{
    easyar_RecorderConfiguration * _return_value_ = NULL;
    easyar_RecorderConfiguration__ctor(&_return_value_);
    init_cdata(_return_value_);
}
inline void RecorderConfiguration::setOutputFile(String * arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setOutputFile(cdata_, arg0->get_cdata());
}
inline bool RecorderConfiguration::setProfile(RecordProfile arg0)
{
    if (cdata_ == NULL) {
        return bool();
    }
    bool _return_value_ = easyar_RecorderConfiguration_setProfile(cdata_, static_cast<easyar_RecordProfile>(arg0));
    return _return_value_;
}
inline void RecorderConfiguration::setVideoSize(RecordVideoSize arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setVideoSize(cdata_, static_cast<easyar_RecordVideoSize>(arg0));
}
inline void RecorderConfiguration::setVideoBitrate(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setVideoBitrate(cdata_, arg0);
}
inline void RecorderConfiguration::setChannelCount(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setChannelCount(cdata_, arg0);
}
inline void RecorderConfiguration::setAudioSampleRate(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setAudioSampleRate(cdata_, arg0);
}
inline void RecorderConfiguration::setAudioBitrate(int arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setAudioBitrate(cdata_, arg0);
}
inline void RecorderConfiguration::setVideoOrientation(RecordVideoOrientation arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setVideoOrientation(cdata_, static_cast<easyar_RecordVideoOrientation>(arg0));
}
inline void RecorderConfiguration::setZoomMode(RecordZoomMode arg0)
{
    if (cdata_ == NULL) {
        return;
    }
    easyar_RecorderConfiguration_setZoomMode(cdata_, static_cast<easyar_RecordZoomMode>(arg0));
}

}

#endif
