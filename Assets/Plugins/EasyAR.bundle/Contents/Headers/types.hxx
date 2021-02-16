//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TYPES_HXX__
#define __EASYAR_TYPES_HXX__

#include "easyar/types.h"
#include <cstddef>
#include <stdexcept>

namespace easyar {

class String
{
private:
    easyar_String * cdata_;
    virtual String & operator=(const String & data) { return *this; } //deleted
public:
    String(easyar_String * cdata)
        : cdata_(cdata)
    {
    }
    virtual ~String()
    {
        if (cdata_) {
            easyar_String__dtor(cdata_);
            cdata_ = NULL;
        }
    }

    String(const String & data)
        : cdata_(static_cast<easyar_String *>(NULL))
    {
        easyar_String_copy(data.cdata_, &cdata_);
    }
    const easyar_String * get_cdata() const
    {
        return cdata_;
    }
    easyar_String * get_cdata()
    {
        return cdata_;
    }

    static void from_utf8(const char * begin, const char * end, /* OUT */ String * * Return)
    {
        easyar_String * _return_value_ = NULL;
        easyar_String_from_utf8(begin, end, &_return_value_);
        *Return = _return_value_ == NULL ? NULL : new String(_return_value_);
    }
    static void from_utf8_begin(const char * begin, /* OUT */ String * * Return)
    {
        easyar_String * _return_value_ = NULL;
        easyar_String_from_utf8_begin(begin, &_return_value_);
        *Return = _return_value_ == NULL ? NULL : new String(_return_value_);
    }
    const char * begin()
    {
        return easyar_String_begin(cdata_);
    }
    const char * end()
    {
        return easyar_String_end(cdata_);
    }
};

class ObjectTargetParameters;

class ObjectTarget;

class ObjectTrackerResult;

class ObjectTracker;

enum CloudRecognizationStatus
{
    /// <summary>
    /// Unknown error
    /// </summary>
    CloudRecognizationStatus_UnknownError = 0,
    /// <summary>
    /// A target is recognized.
    /// </summary>
    CloudRecognizationStatus_FoundTarget = 1,
    /// <summary>
    /// No target is recognized.
    /// </summary>
    CloudRecognizationStatus_TargetNotFound = 2,
    /// <summary>
    /// Reached the access limit
    /// </summary>
    CloudRecognizationStatus_ReachedAccessLimit = 3,
    /// <summary>
    /// Request interval too low
    /// </summary>
    CloudRecognizationStatus_RequestIntervalTooLow = 4,
};

class CloudRecognizationResult;

class CloudRecognizer;

class Buffer;

class BufferDictionary;

class BufferPool;

enum CameraDeviceType
{
    /// <summary>
    /// Unknown location
    /// </summary>
    CameraDeviceType_Unknown = 0,
    /// <summary>
    /// Rear camera
    /// </summary>
    CameraDeviceType_Back = 1,
    /// <summary>
    /// Front camera
    /// </summary>
    CameraDeviceType_Front = 2,
};

/// <summary>
/// MotionTrackingStatus describes the quality of device motion tracking.
/// </summary>
enum MotionTrackingStatus
{
    /// <summary>
    /// Result is not available and should not to be used to render virtual objects or do 3D reconstruction. This value occurs temporarily after initializing, tracking lost or relocalizing.
    /// </summary>
    MotionTrackingStatus_NotTracking = 0,
    /// <summary>
    /// Tracking is available, but the quality of the result is not good enough. This value occurs temporarily due to weak texture or excessive movement. The result can be used to render virtual objects, but should generally not be used to do 3D reconstruction.
    /// </summary>
    MotionTrackingStatus_Limited = 1,
    /// <summary>
    /// Tracking with a good quality. The result can be used to render virtual objects or do 3D reconstruction.
    /// </summary>
    MotionTrackingStatus_Tracking = 2,
};

class CameraParameters;

/// <summary>
/// PixelFormat represents the format of image pixel data. All formats follow the pixel direction from left to right and from top to bottom.
/// </summary>
enum PixelFormat
{
    /// <summary>
    /// Unknown
    /// </summary>
    PixelFormat_Unknown = 0,
    /// <summary>
    /// 256 shades grayscale
    /// </summary>
    PixelFormat_Gray = 1,
    /// <summary>
    /// YUV_NV21
    /// </summary>
    PixelFormat_YUV_NV21 = 2,
    /// <summary>
    /// YUV_NV12
    /// </summary>
    PixelFormat_YUV_NV12 = 3,
    /// <summary>
    /// YUV_I420
    /// </summary>
    PixelFormat_YUV_I420 = 4,
    /// <summary>
    /// YUV_YV12
    /// </summary>
    PixelFormat_YUV_YV12 = 5,
    /// <summary>
    /// RGB888
    /// </summary>
    PixelFormat_RGB888 = 6,
    /// <summary>
    /// BGR888
    /// </summary>
    PixelFormat_BGR888 = 7,
    /// <summary>
    /// RGBA8888
    /// </summary>
    PixelFormat_RGBA8888 = 8,
    /// <summary>
    /// BGRA8888
    /// </summary>
    PixelFormat_BGRA8888 = 9,
};

class Image;

struct Matrix44F;

struct Matrix33F;

struct Vec4F;

struct Vec3F;

struct Vec2F;

struct Vec4I;

struct Vec2I;

class DenseSpatialMap;

struct BlockInfo;

class SceneMesh;

class ARCoreCameraDevice;

class ARKitCameraDevice;

enum CameraDeviceFocusMode
{
    /// <summary>
    /// Normal auto focus mode. You should call autoFocus to start the focus in this mode.
    /// </summary>
    CameraDeviceFocusMode_Normal = 0,
    /// <summary>
    /// Continuous auto focus mode
    /// </summary>
    CameraDeviceFocusMode_Continousauto = 2,
    /// <summary>
    /// Infinity focus mode
    /// </summary>
    CameraDeviceFocusMode_Infinity = 3,
    /// <summary>
    /// Macro (close-up) focus mode. You should call autoFocus to start the focus in this mode.
    /// </summary>
    CameraDeviceFocusMode_Macro = 4,
    /// <summary>
    /// Medium distance focus mode
    /// </summary>
    CameraDeviceFocusMode_Medium = 5,
};

enum AndroidCameraApiType
{
    /// <summary>
    /// Android Camera1
    /// </summary>
    AndroidCameraApiType_Camera1 = 0,
    /// <summary>
    /// Android Camera2
    /// </summary>
    AndroidCameraApiType_Camera2 = 1,
};

enum CameraDevicePresetProfile
{
    /// <summary>
    /// The same as AVCaptureSessionPresetPhoto.
    /// </summary>
    CameraDevicePresetProfile_Photo = 0,
    /// <summary>
    /// The same as AVCaptureSessionPresetHigh.
    /// </summary>
    CameraDevicePresetProfile_High = 1,
    /// <summary>
    /// The same as AVCaptureSessionPresetMedium.
    /// </summary>
    CameraDevicePresetProfile_Medium = 2,
    /// <summary>
    /// The same as AVCaptureSessionPresetLow.
    /// </summary>
    CameraDevicePresetProfile_Low = 3,
};

enum CameraState
{
    /// <summary>
    /// Unknown
    /// </summary>
    CameraState_Unknown = 0x00000000,
    /// <summary>
    /// Disconnected
    /// </summary>
    CameraState_Disconnected = 0x00000001,
    /// <summary>
    /// Preempted by another application.
    /// </summary>
    CameraState_Preempted = 0x00000002,
};

class CameraDevice;

enum CameraDevicePreference
{
    /// <summary>
    /// Optimized for `ImageTracker`_ , `ObjectTracker`_ and `CloudRecognizer`_ .
    /// </summary>
    CameraDevicePreference_PreferObjectSensing = 0,
    /// <summary>
    /// Optimized for `SurfaceTracker`_ .
    /// </summary>
    CameraDevicePreference_PreferSurfaceTracking = 1,
    /// <summary>
    /// Optimized for Motion Tracking .
    /// </summary>
    CameraDevicePreference_PreferMotionTracking = 2,
};

class CameraDeviceSelector;

class SurfaceTrackerResult;

class SurfaceTracker;

class MotionTrackerCameraDevice;

class InputFrameRecorder;

class InputFramePlayer;

class CallbackScheduler;

class DelayedCallbackScheduler;

class ImmediateCallbackScheduler;

class JniUtility;

enum LogLevel
{
    /// <summary>
    /// Error
    /// </summary>
    LogLevel_Error = 0,
    /// <summary>
    /// Warning
    /// </summary>
    LogLevel_Warning = 1,
    /// <summary>
    /// Information
    /// </summary>
    LogLevel_Info = 2,
};

class Log;

class ImageTargetParameters;

class ImageTarget;

enum ImageTrackerMode
{
    /// <summary>
    /// Quality is preferred.
    /// </summary>
    ImageTrackerMode_PreferQuality = 0,
    /// <summary>
    /// Performance is preferred.
    /// </summary>
    ImageTrackerMode_PreferPerformance = 1,
};

class ImageTrackerResult;

class ImageTracker;

class Recorder;

enum RecordProfile
{
    /// <summary>
    /// 1080P, low quality
    /// </summary>
    RecordProfile_Quality_1080P_Low = 0x00000001,
    /// <summary>
    /// 1080P, middle quality
    /// </summary>
    RecordProfile_Quality_1080P_Middle = 0x00000002,
    /// <summary>
    /// 1080P, high quality
    /// </summary>
    RecordProfile_Quality_1080P_High = 0x00000004,
    /// <summary>
    /// 720P, low quality
    /// </summary>
    RecordProfile_Quality_720P_Low = 0x00000008,
    /// <summary>
    /// 720P, middle quality
    /// </summary>
    RecordProfile_Quality_720P_Middle = 0x00000010,
    /// <summary>
    /// 720P, high quality
    /// </summary>
    RecordProfile_Quality_720P_High = 0x00000020,
    /// <summary>
    /// 480P, low quality
    /// </summary>
    RecordProfile_Quality_480P_Low = 0x00000040,
    /// <summary>
    /// 480P, middle quality
    /// </summary>
    RecordProfile_Quality_480P_Middle = 0x00000080,
    /// <summary>
    /// 480P, high quality
    /// </summary>
    RecordProfile_Quality_480P_High = 0x00000100,
    /// <summary>
    /// default resolution and quality, same as `Quality_720P_Middle`
    /// </summary>
    RecordProfile_Quality_Default = 0x00000010,
};

enum RecordVideoSize
{
    /// <summary>
    /// 1080P
    /// </summary>
    RecordVideoSize_Vid1080p = 0x00000002,
    /// <summary>
    /// 720P
    /// </summary>
    RecordVideoSize_Vid720p = 0x00000010,
    /// <summary>
    /// 480P
    /// </summary>
    RecordVideoSize_Vid480p = 0x00000080,
};

enum RecordZoomMode
{
    /// <summary>
    /// If output aspect ratio does not fit input, content will be clipped to fit output aspect ratio.
    /// </summary>
    RecordZoomMode_NoZoomAndClip = 0x00000000,
    /// <summary>
    /// If output aspect ratio does not fit input, content will not be clipped and there will be black borders in one dimension.
    /// </summary>
    RecordZoomMode_ZoomInWithAllContent = 0x00000001,
};

enum RecordVideoOrientation
{
    /// <summary>
    /// video recorded is landscape
    /// </summary>
    RecordVideoOrientation_Landscape = 0x00000000,
    /// <summary>
    /// video recorded is portrait
    /// </summary>
    RecordVideoOrientation_Portrait = 0x00000001,
};

enum RecordStatus
{
    /// <summary>
    /// recording start
    /// </summary>
    RecordStatus_OnStarted = 0x00000002,
    /// <summary>
    /// recording stopped
    /// </summary>
    RecordStatus_OnStopped = 0x00000004,
    /// <summary>
    /// start fail
    /// </summary>
    RecordStatus_FailedToStart = 0x00000202,
    /// <summary>
    /// file write succeed
    /// </summary>
    RecordStatus_FileSucceeded = 0x00000400,
    /// <summary>
    /// file write fail
    /// </summary>
    RecordStatus_FileFailed = 0x00000401,
    /// <summary>
    /// runtime info with description
    /// </summary>
    RecordStatus_LogInfo = 0x00000800,
    /// <summary>
    /// runtime error with description
    /// </summary>
    RecordStatus_LogError = 0x00001000,
};

class RecorderConfiguration;

class SparseSpatialMapResult;

enum PlaneType
{
    /// <summary>
    /// Horizontal plane
    /// </summary>
    PlaneType_Horizontal = 0,
    /// <summary>
    /// Vertical plane
    /// </summary>
    PlaneType_Vertical = 1,
};

class PlaneData;

enum LocalizationMode
{
    /// <summary>
    /// Attempt to perform localization in current SparseSpatialMap until success.
    /// </summary>
    LocalizationMode_UntilSuccess = 0,
    /// <summary>
    /// Perform localization only once
    /// </summary>
    LocalizationMode_Once = 1,
    /// <summary>
    /// Keep performing localization and adjust result on success
    /// </summary>
    LocalizationMode_KeepUpdate = 2,
    /// <summary>
    /// Keep performing localization and adjust localization result only when localization returns different map ID from previous results
    /// </summary>
    LocalizationMode_ContinousLocalize = 3,
};

class SparseSpatialMapConfig;

class SparseSpatialMap;

class SparseSpatialMapManager;

class Engine;

enum VideoStatus
{
    /// <summary>
    /// Status to indicate something wrong happen in video open or play.
    /// </summary>
    VideoStatus_Error = -1,
    /// <summary>
    /// Status to show video finished open and is ready for play.
    /// </summary>
    VideoStatus_Ready = 0,
    /// <summary>
    /// Status to indicate video finished play and reached the end.
    /// </summary>
    VideoStatus_Completed = 1,
};

enum VideoType
{
    /// <summary>
    /// Normal video.
    /// </summary>
    VideoType_Normal = 0,
    /// <summary>
    /// Transparent video, left half is the RGB channel and right half is alpha channel.
    /// </summary>
    VideoType_TransparentSideBySide = 1,
    /// <summary>
    /// Transparent video, top half is the RGB channel and bottom half is alpha channel.
    /// </summary>
    VideoType_TransparentTopAndBottom = 2,
};

class VideoPlayer;

class ImageHelper;

class SignalSink;

class SignalSource;

class InputFrameSink;

class InputFrameSource;

class OutputFrameSink;

class OutputFrameSource;

class FeedbackFrameSink;

class FeedbackFrameSource;

class InputFrameFork;

class OutputFrameFork;

class OutputFrameJoin;

class FeedbackFrameFork;

class InputFrameThrottler;

class OutputFrameBuffer;

class InputFrameToOutputFrameAdapter;

class InputFrameToFeedbackFrameAdapter;

class InputFrame;

class FrameFilterResult;

class OutputFrame;

class FeedbackFrame;

enum PermissionStatus
{
    /// <summary>
    /// Permission granted
    /// </summary>
    PermissionStatus_Granted = 0x00000000,
    /// <summary>
    /// Permission denied
    /// </summary>
    PermissionStatus_Denied = 0x00000001,
    /// <summary>
    /// A error happened while requesting permission.
    /// </summary>
    PermissionStatus_Error = 0x00000002,
};

/// <summary>
/// StorageType represents where the images, jsons, videos or other files are located.
/// StorageType specifies the root path, in all interfaces, you can use relative path relative to the root path.
/// </summary>
enum StorageType
{
    /// <summary>
    /// The app path.
    /// Android: the application&#39;s `persistent data directory &lt;https://developer.android.google.cn/reference/android/content/pm/ApplicationInfo.html#dataDir&gt;`__
    /// iOS: the application&#39;s sandbox directory
    /// Windows: Windows: the application&#39;s executable directory
    /// Mac: the application’s executable directory (if app is a bundle, this path is inside the bundle)
    /// </summary>
    StorageType_App = 0,
    /// <summary>
    /// The assets path.
    /// Android: assets directory (inside apk)
    /// iOS: the application&#39;s executable directory
    /// Windows: EasyAR.dll directory
    /// Mac: libEasyAR.dylib directory
    /// **Note:** *this path is different if you are using Unity3D. It will point to the StreamingAssets folder.*
    /// </summary>
    StorageType_Assets = 1,
    /// <summary>
    /// The absolute path (json/image path or video path) or url (video only).
    /// </summary>
    StorageType_Absolute = 2,
};

class Target;

enum TargetStatus
{
    /// <summary>
    /// The status is unknown.
    /// </summary>
    TargetStatus_Unknown = 0,
    /// <summary>
    /// The status is undefined.
    /// </summary>
    TargetStatus_Undefined = 1,
    /// <summary>
    /// The target is detected.
    /// </summary>
    TargetStatus_Detected = 2,
    /// <summary>
    /// The target is tracked.
    /// </summary>
    TargetStatus_Tracked = 3,
};

class TargetInstance;

class TargetTrackerResult;

class TextureId;

struct OptionalOfBuffer;

struct FunctorOfVoid;

struct OptionalOfObjectTarget;

class ListOfVec3F;

class ListOfTargetInstance;

struct OptionalOfTarget;

struct OptionalOfOutputFrame;

class ListOfOptionalOfFrameFilterResult;

struct OptionalOfFrameFilterResult;

struct OptionalOfFunctorOfVoidFromOutputFrame;

struct FunctorOfVoidFromOutputFrame;

struct FunctorOfVoidFromTargetAndBool;

class ListOfTarget;

struct OptionalOfImageTarget;

class ListOfImage;

struct OptionalOfString;

struct FunctorOfVoidFromCloudRecognizationResult;

class ListOfBlockInfo;

struct OptionalOfFunctorOfVoidFromInputFrame;

struct FunctorOfVoidFromInputFrame;

struct OptionalOfFunctorOfVoidFromCameraState;

struct FunctorOfVoidFromCameraState;

struct OptionalOfFunctorOfVoidFromPermissionStatusAndString;

struct FunctorOfVoidFromPermissionStatusAndString;

struct FunctorOfVoidFromLogLevelAndString;

struct OptionalOfFunctorOfVoidFromRecordStatusAndString;

struct FunctorOfVoidFromRecordStatusAndString;

struct OptionalOfMatrix44F;

class ListOfPlaneData;

struct OptionalOfFunctorOfVoidFromBool;

struct FunctorOfVoidFromBool;

struct OptionalOfImage;

struct FunctorOfVoidFromBoolAndStringAndString;

struct FunctorOfVoidFromBoolAndString;

struct OptionalOfFunctorOfVoidFromVideoStatus;

struct FunctorOfVoidFromVideoStatus;

struct OptionalOfFunctorOfVoid;

struct OptionalOfFunctorOfVoidFromFeedbackFrame;

struct FunctorOfVoidFromFeedbackFrame;

struct FunctorOfOutputFrameFromListOfOutputFrame;

class ListOfOutputFrame;

}

#endif
