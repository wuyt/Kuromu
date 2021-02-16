//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#pragma once

#include "easyar/types.h"
#include <cstddef>
#include <optional>
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <functional>
#include <stdexcept>
#include <type_traits>

#if defined(_DECLARATION_ONLY_) || defined(_IMPLEMENTATION_ONLY_)
#   define _INLINE_SPECIFIER_
#else
#   define _INLINE_SPECIFIER_ inline
#endif

#ifndef _IMPLEMENTATION_ONLY_

namespace easyar {

class ObjectTargetParameters;

class ObjectTarget;

class ObjectTrackerResult;

class ObjectTracker;

enum class CloudRecognizationStatus
{
    /// <summary>
    /// Unknown error
    /// </summary>
    UnknownError = 0,
    /// <summary>
    /// A target is recognized.
    /// </summary>
    FoundTarget = 1,
    /// <summary>
    /// No target is recognized.
    /// </summary>
    TargetNotFound = 2,
    /// <summary>
    /// Reached the access limit
    /// </summary>
    ReachedAccessLimit = 3,
    /// <summary>
    /// Request interval too low
    /// </summary>
    RequestIntervalTooLow = 4,
};

class CloudRecognizationResult;

class CloudRecognizer;

class Buffer;

class BufferDictionary;

class BufferPool;

enum class CameraDeviceType
{
    /// <summary>
    /// Unknown location
    /// </summary>
    Unknown = 0,
    /// <summary>
    /// Rear camera
    /// </summary>
    Back = 1,
    /// <summary>
    /// Front camera
    /// </summary>
    Front = 2,
};

/// <summary>
/// MotionTrackingStatus describes the quality of device motion tracking.
/// </summary>
enum class MotionTrackingStatus
{
    /// <summary>
    /// Result is not available and should not to be used to render virtual objects or do 3D reconstruction. This value occurs temporarily after initializing, tracking lost or relocalizing.
    /// </summary>
    NotTracking = 0,
    /// <summary>
    /// Tracking is available, but the quality of the result is not good enough. This value occurs temporarily due to weak texture or excessive movement. The result can be used to render virtual objects, but should generally not be used to do 3D reconstruction.
    /// </summary>
    Limited = 1,
    /// <summary>
    /// Tracking with a good quality. The result can be used to render virtual objects or do 3D reconstruction.
    /// </summary>
    Tracking = 2,
};

class CameraParameters;

/// <summary>
/// PixelFormat represents the format of image pixel data. All formats follow the pixel direction from left to right and from top to bottom.
/// </summary>
enum class PixelFormat
{
    /// <summary>
    /// Unknown
    /// </summary>
    Unknown = 0,
    /// <summary>
    /// 256 shades grayscale
    /// </summary>
    Gray = 1,
    /// <summary>
    /// YUV_NV21
    /// </summary>
    YUV_NV21 = 2,
    /// <summary>
    /// YUV_NV12
    /// </summary>
    YUV_NV12 = 3,
    /// <summary>
    /// YUV_I420
    /// </summary>
    YUV_I420 = 4,
    /// <summary>
    /// YUV_YV12
    /// </summary>
    YUV_YV12 = 5,
    /// <summary>
    /// RGB888
    /// </summary>
    RGB888 = 6,
    /// <summary>
    /// BGR888
    /// </summary>
    BGR888 = 7,
    /// <summary>
    /// RGBA8888
    /// </summary>
    RGBA8888 = 8,
    /// <summary>
    /// BGRA8888
    /// </summary>
    BGRA8888 = 9,
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

enum class CameraDeviceFocusMode
{
    /// <summary>
    /// Normal auto focus mode. You should call autoFocus to start the focus in this mode.
    /// </summary>
    Normal = 0,
    /// <summary>
    /// Continuous auto focus mode
    /// </summary>
    Continousauto = 2,
    /// <summary>
    /// Infinity focus mode
    /// </summary>
    Infinity = 3,
    /// <summary>
    /// Macro (close-up) focus mode. You should call autoFocus to start the focus in this mode.
    /// </summary>
    Macro = 4,
    /// <summary>
    /// Medium distance focus mode
    /// </summary>
    Medium = 5,
};

enum class AndroidCameraApiType
{
    /// <summary>
    /// Android Camera1
    /// </summary>
    Camera1 = 0,
    /// <summary>
    /// Android Camera2
    /// </summary>
    Camera2 = 1,
};

enum class CameraDevicePresetProfile
{
    /// <summary>
    /// The same as AVCaptureSessionPresetPhoto.
    /// </summary>
    Photo = 0,
    /// <summary>
    /// The same as AVCaptureSessionPresetHigh.
    /// </summary>
    High = 1,
    /// <summary>
    /// The same as AVCaptureSessionPresetMedium.
    /// </summary>
    Medium = 2,
    /// <summary>
    /// The same as AVCaptureSessionPresetLow.
    /// </summary>
    Low = 3,
};

enum class CameraState
{
    /// <summary>
    /// Unknown
    /// </summary>
    Unknown = 0x00000000,
    /// <summary>
    /// Disconnected
    /// </summary>
    Disconnected = 0x00000001,
    /// <summary>
    /// Preempted by another application.
    /// </summary>
    Preempted = 0x00000002,
};

class CameraDevice;

enum class CameraDevicePreference
{
    /// <summary>
    /// Optimized for `ImageTracker`_ , `ObjectTracker`_ and `CloudRecognizer`_ .
    /// </summary>
    PreferObjectSensing = 0,
    /// <summary>
    /// Optimized for `SurfaceTracker`_ .
    /// </summary>
    PreferSurfaceTracking = 1,
    /// <summary>
    /// Optimized for Motion Tracking .
    /// </summary>
    PreferMotionTracking = 2,
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

enum class LogLevel
{
    /// <summary>
    /// Error
    /// </summary>
    Error = 0,
    /// <summary>
    /// Warning
    /// </summary>
    Warning = 1,
    /// <summary>
    /// Information
    /// </summary>
    Info = 2,
};

class Log;

class ImageTargetParameters;

class ImageTarget;

enum class ImageTrackerMode
{
    /// <summary>
    /// Quality is preferred.
    /// </summary>
    PreferQuality = 0,
    /// <summary>
    /// Performance is preferred.
    /// </summary>
    PreferPerformance = 1,
};

class ImageTrackerResult;

class ImageTracker;

class Recorder;

enum class RecordProfile
{
    /// <summary>
    /// 1080P, low quality
    /// </summary>
    Quality_1080P_Low = 0x00000001,
    /// <summary>
    /// 1080P, middle quality
    /// </summary>
    Quality_1080P_Middle = 0x00000002,
    /// <summary>
    /// 1080P, high quality
    /// </summary>
    Quality_1080P_High = 0x00000004,
    /// <summary>
    /// 720P, low quality
    /// </summary>
    Quality_720P_Low = 0x00000008,
    /// <summary>
    /// 720P, middle quality
    /// </summary>
    Quality_720P_Middle = 0x00000010,
    /// <summary>
    /// 720P, high quality
    /// </summary>
    Quality_720P_High = 0x00000020,
    /// <summary>
    /// 480P, low quality
    /// </summary>
    Quality_480P_Low = 0x00000040,
    /// <summary>
    /// 480P, middle quality
    /// </summary>
    Quality_480P_Middle = 0x00000080,
    /// <summary>
    /// 480P, high quality
    /// </summary>
    Quality_480P_High = 0x00000100,
    /// <summary>
    /// default resolution and quality, same as `Quality_720P_Middle`
    /// </summary>
    Quality_Default = 0x00000010,
};

enum class RecordVideoSize
{
    /// <summary>
    /// 1080P
    /// </summary>
    Vid1080p = 0x00000002,
    /// <summary>
    /// 720P
    /// </summary>
    Vid720p = 0x00000010,
    /// <summary>
    /// 480P
    /// </summary>
    Vid480p = 0x00000080,
};

enum class RecordZoomMode
{
    /// <summary>
    /// If output aspect ratio does not fit input, content will be clipped to fit output aspect ratio.
    /// </summary>
    NoZoomAndClip = 0x00000000,
    /// <summary>
    /// If output aspect ratio does not fit input, content will not be clipped and there will be black borders in one dimension.
    /// </summary>
    ZoomInWithAllContent = 0x00000001,
};

enum class RecordVideoOrientation
{
    /// <summary>
    /// video recorded is landscape
    /// </summary>
    Landscape = 0x00000000,
    /// <summary>
    /// video recorded is portrait
    /// </summary>
    Portrait = 0x00000001,
};

enum class RecordStatus
{
    /// <summary>
    /// recording start
    /// </summary>
    OnStarted = 0x00000002,
    /// <summary>
    /// recording stopped
    /// </summary>
    OnStopped = 0x00000004,
    /// <summary>
    /// start fail
    /// </summary>
    FailedToStart = 0x00000202,
    /// <summary>
    /// file write succeed
    /// </summary>
    FileSucceeded = 0x00000400,
    /// <summary>
    /// file write fail
    /// </summary>
    FileFailed = 0x00000401,
    /// <summary>
    /// runtime info with description
    /// </summary>
    LogInfo = 0x00000800,
    /// <summary>
    /// runtime error with description
    /// </summary>
    LogError = 0x00001000,
};

class RecorderConfiguration;

class SparseSpatialMapResult;

enum class PlaneType
{
    /// <summary>
    /// Horizontal plane
    /// </summary>
    Horizontal = 0,
    /// <summary>
    /// Vertical plane
    /// </summary>
    Vertical = 1,
};

class PlaneData;

enum class LocalizationMode
{
    /// <summary>
    /// Attempt to perform localization in current SparseSpatialMap until success.
    /// </summary>
    UntilSuccess = 0,
    /// <summary>
    /// Perform localization only once
    /// </summary>
    Once = 1,
    /// <summary>
    /// Keep performing localization and adjust result on success
    /// </summary>
    KeepUpdate = 2,
    /// <summary>
    /// Keep performing localization and adjust localization result only when localization returns different map ID from previous results
    /// </summary>
    ContinousLocalize = 3,
};

class SparseSpatialMapConfig;

class SparseSpatialMap;

class SparseSpatialMapManager;

class Engine;

enum class VideoStatus
{
    /// <summary>
    /// Status to indicate something wrong happen in video open or play.
    /// </summary>
    Error = -1,
    /// <summary>
    /// Status to show video finished open and is ready for play.
    /// </summary>
    Ready = 0,
    /// <summary>
    /// Status to indicate video finished play and reached the end.
    /// </summary>
    Completed = 1,
};

enum class VideoType
{
    /// <summary>
    /// Normal video.
    /// </summary>
    Normal = 0,
    /// <summary>
    /// Transparent video, left half is the RGB channel and right half is alpha channel.
    /// </summary>
    TransparentSideBySide = 1,
    /// <summary>
    /// Transparent video, top half is the RGB channel and bottom half is alpha channel.
    /// </summary>
    TransparentTopAndBottom = 2,
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

enum class PermissionStatus
{
    /// <summary>
    /// Permission granted
    /// </summary>
    Granted = 0x00000000,
    /// <summary>
    /// Permission denied
    /// </summary>
    Denied = 0x00000001,
    /// <summary>
    /// A error happened while requesting permission.
    /// </summary>
    Error = 0x00000002,
};

/// <summary>
/// StorageType represents where the images, jsons, videos or other files are located.
/// StorageType specifies the root path, in all interfaces, you can use relative path relative to the root path.
/// </summary>
enum class StorageType
{
    /// <summary>
    /// The app path.
    /// Android: the application&#39;s `persistent data directory &lt;https://developer.android.google.cn/reference/android/content/pm/ApplicationInfo.html#dataDir&gt;`__
    /// iOS: the application&#39;s sandbox directory
    /// Windows: Windows: the application&#39;s executable directory
    /// Mac: the application’s executable directory (if app is a bundle, this path is inside the bundle)
    /// </summary>
    App = 0,
    /// <summary>
    /// The assets path.
    /// Android: assets directory (inside apk)
    /// iOS: the application&#39;s executable directory
    /// Windows: EasyAR.dll directory
    /// Mac: libEasyAR.dylib directory
    /// **Note:** *this path is different if you are using Unity3D. It will point to the StreamingAssets folder.*
    /// </summary>
    Assets = 1,
    /// <summary>
    /// The absolute path (json/image path or video path) or url (video only).
    /// </summary>
    Absolute = 2,
};

class Target;

enum class TargetStatus
{
    /// <summary>
    /// The status is unknown.
    /// </summary>
    Unknown = 0,
    /// <summary>
    /// The status is undefined.
    /// </summary>
    Undefined = 1,
    /// <summary>
    /// The target is detected.
    /// </summary>
    Detected = 2,
    /// <summary>
    /// The target is tracked.
    /// </summary>
    Tracked = 3,
};

class TargetInstance;

class TargetTrackerResult;

class TextureId;

/// <summary>
/// ObjectTargetParameters represents the parameters to create a `ObjectTarget`_ .
/// </summary>
class ObjectTargetParameters
{
protected:
    std::shared_ptr<easyar_ObjectTargetParameters> cdata_;
    void init_cdata(std::shared_ptr<easyar_ObjectTargetParameters> cdata);
    ObjectTargetParameters & operator=(const ObjectTargetParameters & data) = delete;
public:
    ObjectTargetParameters(std::shared_ptr<easyar_ObjectTargetParameters> cdata);
    virtual ~ObjectTargetParameters();

    std::shared_ptr<easyar_ObjectTargetParameters> get_cdata();
    static std::shared_ptr<ObjectTargetParameters> from_cdata(std::shared_ptr<easyar_ObjectTargetParameters> cdata);

    ObjectTargetParameters();
    /// <summary>
    /// Gets `Buffer`_ dictionary.
    /// </summary>
    std::shared_ptr<BufferDictionary> bufferDictionary();
    /// <summary>
    /// Sets `Buffer`_ dictionary. obj, mtl and jpg/png files shall be loaded into the dictionay, and be able to be located by relative or absolute paths.
    /// </summary>
    void setBufferDictionary(std::shared_ptr<BufferDictionary> bufferDictionary);
    /// <summary>
    /// Gets obj file path.
    /// </summary>
    std::string objPath();
    /// <summary>
    /// Sets obj file path.
    /// </summary>
    void setObjPath(std::string objPath);
    /// <summary>
    /// Gets target name. It can be used to distinguish targets.
    /// </summary>
    std::string name();
    /// <summary>
    /// Sets target name.
    /// </summary>
    void setName(std::string name);
    /// <summary>
    /// Gets the target uid. You can set this uid in the json config as a method to distinguish from targets.
    /// </summary>
    std::string uid();
    /// <summary>
    /// Sets target uid.
    /// </summary>
    void setUid(std::string uid);
    /// <summary>
    /// Gets meta data.
    /// </summary>
    std::string meta();
    /// <summary>
    /// Sets meta data。
    /// </summary>
    void setMeta(std::string meta);
    /// <summary>
    /// Gets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// </summary>
    float scale();
    /// <summary>
    /// Sets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// It is needed to set the model scale in rendering engine separately.
    /// </summary>
    void setScale(float size);
};

/// <summary>
/// Target is the base class for all targets that can be tracked by `ImageTracker`_ or other algorithms inside EasyAR.
/// </summary>
class Target
{
protected:
    std::shared_ptr<easyar_Target> cdata_;
    void init_cdata(std::shared_ptr<easyar_Target> cdata);
    Target & operator=(const Target & data) = delete;
public:
    Target(std::shared_ptr<easyar_Target> cdata);
    virtual ~Target();

    std::shared_ptr<easyar_Target> get_cdata();
    static std::shared_ptr<Target> from_cdata(std::shared_ptr<easyar_Target> cdata);

    /// <summary>
    /// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
    /// </summary>
    int runtimeID();
    /// <summary>
    /// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
    /// </summary>
    std::string uid();
    /// <summary>
    /// Returns the target name. Name is used to distinguish targets in a json file.
    /// </summary>
    std::string name();
    /// <summary>
    /// Set name. It will erase previously set data or data from cloud.
    /// </summary>
    void setName(std::string name);
    /// <summary>
    /// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
    /// </summary>
    std::string meta();
    /// <summary>
    /// Set meta data. It will erase previously set data or data from cloud.
    /// </summary>
    void setMeta(std::string data);
};

/// <summary>
/// ObjectTarget represents 3d object targets that can be tracked by `ObjectTracker`_ .
/// The size of ObjectTarget is determined by the `obj` file. You can change it by changing the object `scale`, which is default to 1.
/// A ObjectTarget can be tracked by `ObjectTracker`_ after a successful load into the `ObjectTracker`_ using `ObjectTracker.loadTarget`_ .
/// </summary>
class ObjectTarget : public Target
{
protected:
    std::shared_ptr<easyar_ObjectTarget> cdata_;
    void init_cdata(std::shared_ptr<easyar_ObjectTarget> cdata);
    ObjectTarget & operator=(const ObjectTarget & data) = delete;
public:
    ObjectTarget(std::shared_ptr<easyar_ObjectTarget> cdata);
    virtual ~ObjectTarget();

    std::shared_ptr<easyar_ObjectTarget> get_cdata();
    static std::shared_ptr<ObjectTarget> from_cdata(std::shared_ptr<easyar_ObjectTarget> cdata);

    ObjectTarget();
    /// <summary>
    /// Creates a target from parameters.
    /// </summary>
    static std::optional<std::shared_ptr<ObjectTarget>> createFromParameters(std::shared_ptr<ObjectTargetParameters> parameters);
    /// <summary>
    /// Creats a target from obj, mtl and jpg/png files.
    /// </summary>
    static std::optional<std::shared_ptr<ObjectTarget>> createFromObjectFile(std::string path, StorageType storageType, std::string name, std::string uid, std::string meta, float scale);
    /// <summary>
    /// The scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// </summary>
    float scale();
    /// <summary>
    /// The bounding box of object, it contains the 8 points of the box.
    /// Vertices&#39;s indices are defined and stored following the rule:
    /// ::
    ///
    ///       4-----7
    ///      /|    /|
    ///     5-----6 |    z
    ///     | |   | |    |
    ///     | 0---|-3    o---y
    ///     |/    |/    /
    ///     1-----2    x
    /// </summary>
    std::vector<Vec3F> boundingBox();
    /// <summary>
    /// Sets model target scale, this will overwrite the value set in the json file or the default value. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
    /// It is needed to set the model scale in rendering engine separately.
    /// It also should been done before loading ObjectTarget into  `ObjectTracker`_ using `ObjectTracker.loadTarget`_.
    /// </summary>
    bool setScale(float scale);
    /// <summary>
    /// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
    /// </summary>
    int runtimeID();
    /// <summary>
    /// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
    /// </summary>
    std::string uid();
    /// <summary>
    /// Returns the target name. Name is used to distinguish targets in a json file.
    /// </summary>
    std::string name();
    /// <summary>
    /// Set name. It will erase previously set data or data from cloud.
    /// </summary>
    void setName(std::string name);
    /// <summary>
    /// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
    /// </summary>
    std::string meta();
    /// <summary>
    /// Set meta data. It will erase previously set data or data from cloud.
    /// </summary>
    void setMeta(std::string data);
};

/// <summary>
/// FrameFilterResult is the base class for result classes of all synchronous algorithm components.
/// </summary>
class FrameFilterResult
{
protected:
    std::shared_ptr<easyar_FrameFilterResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_FrameFilterResult> cdata);
    FrameFilterResult & operator=(const FrameFilterResult & data) = delete;
public:
    FrameFilterResult(std::shared_ptr<easyar_FrameFilterResult> cdata);
    virtual ~FrameFilterResult();

    std::shared_ptr<easyar_FrameFilterResult> get_cdata();
    static std::shared_ptr<FrameFilterResult> from_cdata(std::shared_ptr<easyar_FrameFilterResult> cdata);

};

/// <summary>
/// TargetTrackerResult is the base class of `ImageTrackerResult`_ and `ObjectTrackerResult`_ .
/// </summary>
class TargetTrackerResult : public FrameFilterResult
{
protected:
    std::shared_ptr<easyar_TargetTrackerResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_TargetTrackerResult> cdata);
    TargetTrackerResult & operator=(const TargetTrackerResult & data) = delete;
public:
    TargetTrackerResult(std::shared_ptr<easyar_TargetTrackerResult> cdata);
    virtual ~TargetTrackerResult();

    std::shared_ptr<easyar_TargetTrackerResult> get_cdata();
    static std::shared_ptr<TargetTrackerResult> from_cdata(std::shared_ptr<easyar_TargetTrackerResult> cdata);

    /// <summary>
    /// Returns the list of `TargetInstance`_ contained in the result.
    /// </summary>
    std::vector<std::shared_ptr<TargetInstance>> targetInstances();
    /// <summary>
    /// Sets the list of `TargetInstance`_ contained in the result.
    /// </summary>
    void setTargetInstances(std::vector<std::shared_ptr<TargetInstance>> instances);
};

/// <summary>
/// Result of `ObjectTracker`_ .
/// </summary>
class ObjectTrackerResult : public TargetTrackerResult
{
protected:
    std::shared_ptr<easyar_ObjectTrackerResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_ObjectTrackerResult> cdata);
    ObjectTrackerResult & operator=(const ObjectTrackerResult & data) = delete;
public:
    ObjectTrackerResult(std::shared_ptr<easyar_ObjectTrackerResult> cdata);
    virtual ~ObjectTrackerResult();

    std::shared_ptr<easyar_ObjectTrackerResult> get_cdata();
    static std::shared_ptr<ObjectTrackerResult> from_cdata(std::shared_ptr<easyar_ObjectTrackerResult> cdata);

    /// <summary>
    /// Returns the list of `TargetInstance`_ contained in the result.
    /// </summary>
    std::vector<std::shared_ptr<TargetInstance>> targetInstances();
    /// <summary>
    /// Sets the list of `TargetInstance`_ contained in the result.
    /// </summary>
    void setTargetInstances(std::vector<std::shared_ptr<TargetInstance>> instances);
};

/// <summary>
/// ObjectTracker implements 3D object target detection and tracking.
/// ObjectTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ObjectTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// Before a `Target`_ can be tracked by ObjectTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
/// </summary>
class ObjectTracker
{
protected:
    std::shared_ptr<easyar_ObjectTracker> cdata_;
    void init_cdata(std::shared_ptr<easyar_ObjectTracker> cdata);
    ObjectTracker & operator=(const ObjectTracker & data) = delete;
public:
    ObjectTracker(std::shared_ptr<easyar_ObjectTracker> cdata);
    virtual ~ObjectTracker();

    std::shared_ptr<easyar_ObjectTracker> get_cdata();
    static std::shared_ptr<ObjectTracker> from_cdata(std::shared_ptr<easyar_ObjectTracker> cdata);

    /// <summary>
    /// Returns true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
    /// </summary>
    std::shared_ptr<FeedbackFrameSink> feedbackFrameSink();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// `OutputFrame`_ output port.
    /// </summary>
    std::shared_ptr<OutputFrameSource> outputFrameSource();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<ObjectTracker> create();
    /// <summary>
    /// Starts the track algorithm.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops the track algorithm. Call start to start the track again.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
    /// This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
    /// </summary>
    void loadTarget(std::shared_ptr<Target> target, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(std::shared_ptr<Target>, bool)> callback);
    /// <summary>
    /// Unload a `Target`_ from the tracker.
    /// This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
    /// </summary>
    void unloadTarget(std::shared_ptr<Target> target, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(std::shared_ptr<Target>, bool)> callback);
    /// <summary>
    /// Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
    /// </summary>
    std::vector<std::shared_ptr<Target>> targets();
    /// <summary>
    /// Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
    /// </summary>
    bool setSimultaneousNum(int num);
    /// <summary>
    /// Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
    /// </summary>
    int simultaneousNum();
};

class CloudRecognizationResult
{
protected:
    std::shared_ptr<easyar_CloudRecognizationResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_CloudRecognizationResult> cdata);
    CloudRecognizationResult & operator=(const CloudRecognizationResult & data) = delete;
public:
    CloudRecognizationResult(std::shared_ptr<easyar_CloudRecognizationResult> cdata);
    virtual ~CloudRecognizationResult();

    std::shared_ptr<easyar_CloudRecognizationResult> get_cdata();
    static std::shared_ptr<CloudRecognizationResult> from_cdata(std::shared_ptr<easyar_CloudRecognizationResult> cdata);

    /// <summary>
    /// Returns recognition status.
    /// </summary>
    CloudRecognizationStatus getStatus();
    /// <summary>
    /// Returns the recognized target when status is FoundTarget.
    /// </summary>
    std::optional<std::shared_ptr<ImageTarget>> getTarget();
    /// <summary>
    /// Returns the error message when status is UnknownError.
    /// </summary>
    std::optional<std::string> getUnknownErrorMessage();
};

/// <summary>
/// CloudRecognizer implements cloud recognition. It can only be used after created a recognition image library on the cloud. Please refer to EasyAR CRS documentation.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// Before using a CloudRecognizer, an `ImageTracker`_ must be setup and prepared. Any target returned from cloud should be manually put into the `ImageTracker`_ using `ImageTracker.loadTarget`_ if it need to be tracked. Then the target can be used as same as a local target after loaded into the tracker. When a target is recognized, you can get it from callback, and you should use target uid to distinguish different targets. The target runtimeID is dynamically created and cannot be used as unique identifier in the cloud situation.
/// </summary>
class CloudRecognizer
{
protected:
    std::shared_ptr<easyar_CloudRecognizer> cdata_;
    void init_cdata(std::shared_ptr<easyar_CloudRecognizer> cdata);
    CloudRecognizer & operator=(const CloudRecognizer & data) = delete;
public:
    CloudRecognizer(std::shared_ptr<easyar_CloudRecognizer> cdata);
    virtual ~CloudRecognizer();

    std::shared_ptr<easyar_CloudRecognizer> get_cdata();
    static std::shared_ptr<CloudRecognizer> from_cdata(std::shared_ptr<easyar_CloudRecognizer> cdata);

    /// <summary>
    /// Returns true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Creates an instance and connects to the server.
    /// </summary>
    static std::shared_ptr<CloudRecognizer> create(std::string cloudRecognitionServiceServerAddress, std::string apiKey, std::string apiSecret, std::string cloudRecognitionServiceAppId);
    /// <summary>
    /// Creates an instance and connects to the server with Cloud Secret.
    /// </summary>
    static std::shared_ptr<CloudRecognizer> createByCloudSecret(std::string cloudRecognitionServiceServerAddress, std::string cloudRecognitionServiceSecret, std::string cloudRecognitionServiceAppId);
    /// <summary>
    /// Send recognition request. The lowest available request interval is 300ms.
    /// </summary>
    void resolve(std::shared_ptr<InputFrame> inputFrame, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(std::shared_ptr<CloudRecognizationResult>)> callback);
    /// <summary>
    /// Stops the recognition and closes connection. The component shall not be used after calling close.
    /// </summary>
    void close();
};

/// <summary>
/// Buffer stores a raw byte array, which can be used to access image data.
/// To access image data in Java API, get buffer from `Image`_ and copy to a Java byte array.
/// You can always access image data since the first version of EasyAR Sense. Refer to `Image`_ .
/// </summary>
class Buffer
{
protected:
    std::shared_ptr<easyar_Buffer> cdata_;
    void init_cdata(std::shared_ptr<easyar_Buffer> cdata);
    Buffer & operator=(const Buffer & data) = delete;
public:
    Buffer(std::shared_ptr<easyar_Buffer> cdata);
    virtual ~Buffer();

    std::shared_ptr<easyar_Buffer> get_cdata();
    static std::shared_ptr<Buffer> from_cdata(std::shared_ptr<easyar_Buffer> cdata);

    /// <summary>
    /// Wraps a raw memory block. When Buffer is released by all holders, deleter callback will be invoked to execute user-defined memory destruction. deleter must be thread-safe.
    /// </summary>
    static std::shared_ptr<Buffer> wrap(void * ptr, int size, std::function<void()> deleter);
    /// <summary>
    /// Creates a Buffer of specified byte size.
    /// </summary>
    static std::shared_ptr<Buffer> create(int size);
    /// <summary>
    /// Returns raw data address.
    /// </summary>
    void * data();
    /// <summary>
    /// Byte size of raw data.
    /// </summary>
    int size();
    /// <summary>
    /// Copies raw memory. It can be used in languages or platforms without complete support for memory operations.
    /// </summary>
    static void memoryCopy(void * src, void * dest, int length);
    /// <summary>
    /// Tries to copy data from a raw memory address into Buffer. If copy succeeds, it returns true, or else it returns false. Possible failure causes includes: source or destination data range overflow.
    /// </summary>
    bool tryCopyFrom(void * src, int srcIndex, int index, int length);
    /// <summary>
    /// Copies buffer data to user array.
    /// </summary>
    bool tryCopyTo(int index, void * dest, int destIndex, int length);
    /// <summary>
    /// Creates a sub-buffer with a reference to the original Buffer. A Buffer will only be released after all its sub-buffers are released.
    /// </summary>
    std::shared_ptr<Buffer> partition(int index, int length);
};

/// <summary>
/// A mapping from file path to `Buffer`_ . It can be used to represent multiple files in the memory.
/// </summary>
class BufferDictionary
{
protected:
    std::shared_ptr<easyar_BufferDictionary> cdata_;
    void init_cdata(std::shared_ptr<easyar_BufferDictionary> cdata);
    BufferDictionary & operator=(const BufferDictionary & data) = delete;
public:
    BufferDictionary(std::shared_ptr<easyar_BufferDictionary> cdata);
    virtual ~BufferDictionary();

    std::shared_ptr<easyar_BufferDictionary> get_cdata();
    static std::shared_ptr<BufferDictionary> from_cdata(std::shared_ptr<easyar_BufferDictionary> cdata);

    BufferDictionary();
    /// <summary>
    /// Current file count.
    /// </summary>
    int count();
    /// <summary>
    /// Checks if a specified path is in the dictionary.
    /// </summary>
    bool contains(std::string path);
    /// <summary>
    /// Tries to get the corresponding `Buffer`_ for a specified path.
    /// </summary>
    std::optional<std::shared_ptr<Buffer>> tryGet(std::string path);
    /// <summary>
    /// Sets `Buffer`_ for a specified path.
    /// </summary>
    void set(std::string path, std::shared_ptr<Buffer> buffer);
    /// <summary>
    /// Removes a specified path.
    /// </summary>
    bool remove(std::string path);
    /// <summary>
    /// Clears the dictionary.
    /// </summary>
    void clear();
};

/// <summary>
/// BufferPool is a memory pool to reduce memory allocation time consumption for functionality like custom camera interoperability, which needs to allocate memory buffers of a fixed size repeatedly.
/// </summary>
class BufferPool
{
protected:
    std::shared_ptr<easyar_BufferPool> cdata_;
    void init_cdata(std::shared_ptr<easyar_BufferPool> cdata);
    BufferPool & operator=(const BufferPool & data) = delete;
public:
    BufferPool(std::shared_ptr<easyar_BufferPool> cdata);
    virtual ~BufferPool();

    std::shared_ptr<easyar_BufferPool> get_cdata();
    static std::shared_ptr<BufferPool> from_cdata(std::shared_ptr<easyar_BufferPool> cdata);

    /// <summary>
    /// block_size is the byte size of each `Buffer`_ .
    /// capacity is the maximum count of `Buffer`_ .
    /// </summary>
    BufferPool(int block_size, int capacity);
    /// <summary>
    /// The byte size of each `Buffer`_ .
    /// </summary>
    int block_size();
    /// <summary>
    /// The maximum count of `Buffer`_ .
    /// </summary>
    int capacity();
    /// <summary>
    /// Current acquired count of `Buffer`_ .
    /// </summary>
    int size();
    /// <summary>
    /// Tries to acquire a memory block. If current acquired count of `Buffer`_ does not reach maximum, a new `Buffer`_ is fetched or allocated, or else null is returned.
    /// </summary>
    std::optional<std::shared_ptr<Buffer>> tryAcquire();
};

/// <summary>
/// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation.
/// </summary>
class CameraParameters
{
protected:
    std::shared_ptr<easyar_CameraParameters> cdata_;
    void init_cdata(std::shared_ptr<easyar_CameraParameters> cdata);
    CameraParameters & operator=(const CameraParameters & data) = delete;
public:
    CameraParameters(std::shared_ptr<easyar_CameraParameters> cdata);
    virtual ~CameraParameters();

    std::shared_ptr<easyar_CameraParameters> get_cdata();
    static std::shared_ptr<CameraParameters> from_cdata(std::shared_ptr<easyar_CameraParameters> cdata);

    CameraParameters(Vec2I imageSize, Vec2F focalLength, Vec2F principalPoint, CameraDeviceType cameraDeviceType, int cameraOrientation);
    /// <summary>
    /// Image size.
    /// </summary>
    Vec2I size();
    /// <summary>
    /// Focal length, the distance from effective optical center to CCD plane, divided by unit pixel density in width and height directions. The unit is pixel.
    /// </summary>
    Vec2F focalLength();
    /// <summary>
    /// Principal point, coordinates of the intersection point of principal axis on CCD plane against the left-top corner of the image. The unit is pixel.
    /// </summary>
    Vec2F principalPoint();
    /// <summary>
    /// Camera device type. Default, back or front camera. On desktop devices, there are only default cameras. On mobile devices, there is a differentiation between back and front cameras.
    /// </summary>
    CameraDeviceType cameraDeviceType();
    /// <summary>
    /// Camera rotation against device natural orientation.
    /// For Android phones and some Android tablets, this value is 90 degrees.
    /// For Android eye-wear and some Android tablets, this value is 0 degrees.
    /// For all current iOS devices, this value is 90 degrees.
    /// </summary>
    int cameraOrientation();
    /// <summary>
    /// Creates CameraParameters with default camera intrinsics. Default intrinsics are calculated by image size, which is not very precise.
    /// </summary>
    static std::shared_ptr<CameraParameters> createWithDefaultIntrinsics(Vec2I imageSize, CameraDeviceType cameraDeviceType, int cameraOrientation);
    /// <summary>
    /// Get equivalent CameraParameters for a different camera image size.
    /// </summary>
    std::shared_ptr<CameraParameters> getResized(Vec2I imageSize);
    /// <summary>
    /// Calculates the angle required to rotate the camera image clockwise to align it with the screen.
    /// screenRotation is the angle of rotation of displaying screen image against device natural orientation in clockwise in degrees.
    /// For iOS(UIInterfaceOrientationPortrait as natural orientation):
    /// * UIInterfaceOrientationPortrait: rotation = 0
    /// * UIInterfaceOrientationLandscapeRight: rotation = 90
    /// * UIInterfaceOrientationPortraitUpsideDown: rotation = 180
    /// * UIInterfaceOrientationLandscapeLeft: rotation = 270
    /// For Android:
    /// * Surface.ROTATION_0 = 0
    /// * Surface.ROTATION_90 = 90
    /// * Surface.ROTATION_180 = 180
    /// * Surface.ROTATION_270 = 270
    /// </summary>
    int imageOrientation(int screenRotation);
    /// <summary>
    /// Calculates whether the image needed to be flipped horizontally. The image is rotated, then flipped in rendering. When cameraDeviceType is front, a flip is automatically applied. Pass manualHorizontalFlip with true to add a manual flip.
    /// </summary>
    bool imageHorizontalFlip(bool manualHorizontalFlip);
    /// <summary>
    /// Calculates the perspective projection matrix needed by virtual object rendering. The projection transforms points from camera coordinate system to clip coordinate system ([-1, 1]^4). The form of perspective projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
    /// </summary>
    Matrix44F projection(float nearPlane, float farPlane, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip);
    /// <summary>
    /// Calculates the orthogonal projection matrix needed by camera background rendering. The projection transforms points from image quad coordinate system ([-1, 1]^2) to clip coordinate system ([-1, 1]^4), with the undefined two dimensions unchanged. The form of orthogonal projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL&#39;s column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL&#39;s default.
    /// </summary>
    Matrix44F imageProjection(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip);
    /// <summary>
    /// Transforms points from image coordinate system ([0, 1]^2) to screen coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
    /// </summary>
    Vec2F screenCoordinatesFromImageCoordinates(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, Vec2F imageCoordinates);
    /// <summary>
    /// Transforms points from screen coordinate system ([0, 1]^2) to image coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
    /// </summary>
    Vec2F imageCoordinatesFromScreenCoordinates(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, Vec2F screenCoordinates);
    /// <summary>
    /// Checks if two groups of parameters are equal.
    /// </summary>
    bool equalsTo(std::shared_ptr<CameraParameters> other);
};

/// <summary>
/// Image stores an image data and represents an image in memory.
/// Image raw data can be accessed as byte array. The width/height/etc information are also accessible.
/// You can always access image data since the first version of EasyAR Sense.
///
/// You can do this in iOS
/// ::
///
///     #import &lt;easyar/buffer.oc.h&gt;
///     #import &lt;easyar/image.oc.h&gt;
///
///     easyar_OutputFrame * outputFrame = [outputFrameBuffer peek];
///     if (outputFrame != nil) {
///         easyar_Image * i = [[outputFrame inputFrame] image];
///         easyar_Buffer * b = [i buffer];
///         char * bytes = calloc([b size], 1);
///         memcpy(bytes, [b data], [b size]);
///         // use bytes here
///         free(bytes);
///     }
///
/// Or in Android
/// ::
///
///     import cn.easyar.*;
///
///     OutputFrame outputFrame = outputFrameBuffer.peek();
///     if (outputFrame != null) {
///         InputFrame inputFrame = outputFrame.inputFrame();
///         Image i = inputFrame.image();
///         Buffer b = i.buffer();
///         byte[] bytes = new byte[b.size()];
///         b.copyToByteArray(0, bytes, 0, bytes.length);
///         // use bytes here
///         b.dispose();
///         i.dispose();
///         inputFrame.dispose();
///         outputFrame.dispose();
///     }
/// </summary>
class Image
{
protected:
    std::shared_ptr<easyar_Image> cdata_;
    void init_cdata(std::shared_ptr<easyar_Image> cdata);
    Image & operator=(const Image & data) = delete;
public:
    Image(std::shared_ptr<easyar_Image> cdata);
    virtual ~Image();

    std::shared_ptr<easyar_Image> get_cdata();
    static std::shared_ptr<Image> from_cdata(std::shared_ptr<easyar_Image> cdata);

    Image(std::shared_ptr<Buffer> buffer, PixelFormat format, int width, int height);
    /// <summary>
    /// Returns buffer inside image. It can be used to access internal data of image. The content of `Buffer`_ shall not be modified, as they may be accessed from other threads.
    /// </summary>
    std::shared_ptr<Buffer> buffer();
    /// <summary>
    /// Returns image format.
    /// </summary>
    PixelFormat format();
    /// <summary>
    /// Returns image width.
    /// </summary>
    int width();
    /// <summary>
    /// Returns image height.
    /// </summary>
    int height();
};

/// <summary>
/// record
/// Square matrix of 4. The data arrangement is row-major.
/// </summary>
struct Matrix44F
{
    /// <summary>
    /// The raw data of matrix.
    /// </summary>
    std::array<float, 16> data;
};

/// <summary>
/// record
/// Square matrix of 3. The data arrangement is row-major.
/// </summary>
struct Matrix33F
{
    /// <summary>
    /// The raw data of matrix.
    /// </summary>
    std::array<float, 9> data;
};

/// <summary>
/// record
/// 4 dimensional vector of float.
/// </summary>
struct Vec4F
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    std::array<float, 4> data;
};

/// <summary>
/// record
/// 3 dimensional vector of float.
/// </summary>
struct Vec3F
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    std::array<float, 3> data;
};

/// <summary>
/// record
/// 2 dimensional vector of float.
/// </summary>
struct Vec2F
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    std::array<float, 2> data;
};

/// <summary>
/// record
/// 4 dimensional vector of int.
/// </summary>
struct Vec4I
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    std::array<int, 4> data;
};

/// <summary>
/// record
/// 2 dimensional vector of int.
/// </summary>
struct Vec2I
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    std::array<int, 2> data;
};

/// <summary>
/// DenseSpatialMap is used to reconstruct the environment accurately and densely. The reconstructed model is represented by `triangle mesh`, which is denoted simply by `mesh`.
/// DenseSpatialMap occupies 1 buffers of camera.
/// </summary>
class DenseSpatialMap
{
protected:
    std::shared_ptr<easyar_DenseSpatialMap> cdata_;
    void init_cdata(std::shared_ptr<easyar_DenseSpatialMap> cdata);
    DenseSpatialMap & operator=(const DenseSpatialMap & data) = delete;
public:
    DenseSpatialMap(std::shared_ptr<easyar_DenseSpatialMap> cdata);
    virtual ~DenseSpatialMap();

    std::shared_ptr<easyar_DenseSpatialMap> get_cdata();
    static std::shared_ptr<DenseSpatialMap> from_cdata(std::shared_ptr<easyar_DenseSpatialMap> cdata);

    /// <summary>
    /// Returns True when the device supports dense reconstruction, otherwise returns False.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Input port for input frame. For DenseSpatialMap to work, the inputFrame must include image and it&#39;s camera parameters and spatial information (cameraTransform and trackingStatus). See also `InputFrameSink`_ .
    /// </summary>
    std::shared_ptr<InputFrameSink> inputFrameSink();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Create `DenseSpatialMap`_ object.
    /// </summary>
    static std::shared_ptr<DenseSpatialMap> create();
    /// <summary>
    /// Start or continue runninng `DenseSpatialMap`_ algorithm.
    /// </summary>
    bool start();
    /// <summary>
    /// Pause the reconstruction algorithm. Call `start` to resume reconstruction.
    /// </summary>
    void stop();
    /// <summary>
    /// Close `DenseSpatialMap`_ algorithm.
    /// </summary>
    void close();
    /// <summary>
    /// Get the mesh management object of type `SceneMesh`_ . The contents will automatically update after calling the `DenseSpatialMap.updateSceneMesh`_ function.
    /// </summary>
    std::shared_ptr<SceneMesh> getMesh();
    /// <summary>
    /// Get the lastest updated mesh and save it to the `SceneMesh`_ object obtained by `DenseSpatialMap.getMesh`_ .
    /// The parameter `updateMeshAll` indicates whether to perform a `full update` or an `incremental update`. When `updateMeshAll` is True, `full update` is performed. All meshes are saved to `SceneMesh`_ . When `updateMeshAll` is False, `incremental update` is performed, and only the most recently updated mesh is saved to `SceneMesh`_ .
    /// `Full update` will take extra time and memory space, causing performance degradation.
    /// </summary>
    bool updateSceneMesh(bool updateMeshAll);
};

/// <summary>
/// record
/// The dense reconstructed model is represented by triangle mesh, or simply denoted as mesh. Because mesh updates frequently, in order to ensure efficiency, the mesh of the whole reconstruction model is divided into many mesh blocks. A mesh block is composed of a cube about 1 meter long, with attributes such as vertices and indices.
///
/// BlockInfo is used to describe the content of a mesh block. (x, y, z) is the index of mesh block, the coordinates of a mesh block&#39;s origin in world coordinate system can be obtained by  multiplying (x, y, z) by the physical size of mesh block. You may filter the part you want to display in advance by the mesh block&#39;s world coordinates for the sake of saving rendering time.
/// </summary>
struct BlockInfo
{
    /// <summary>
    /// x in index (x, y, z) of mesh block.
    /// </summary>
    int x;
    /// <summary>
    /// y in index (x, y, z) of mesh block.
    /// </summary>
    int y;
    /// <summary>
    /// z in index (x, y, z) of mesh block.
    /// </summary>
    int z;
    /// <summary>
    /// Number of vertices in a mesh block.
    /// </summary>
    int numOfVertex;
    /// <summary>
    /// startPointOfVertex is the starting position of the vertex data stored in the vertex buffer, indicating from where the stored vertices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of vertex buffer. The offset is startPointOfVertex*3*4 bytes.
    /// </summary>
    int startPointOfVertex;
    /// <summary>
    /// The number of indices in a mesh block. Each of three consecutive vertices form a triangle.
    /// </summary>
    int numOfIndex;
    /// <summary>
    /// Similar to startPointOfVertex. startPointOfIndex is the starting position of the index data stored in the index buffer, indicating from where the stored indices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of index buffer. The offset is startPointOfIndex*3*4 bytes.
    /// </summary>
    int startPointOfIndex;
    /// <summary>
    /// Version represents how many times the mesh block has updated. The larger the version, the newer the block. If the version of a mesh block increases after calling `DenseSpatialMap.updateSceneMesh`_ , it indicates that the mash block has changed.
    /// </summary>
    int version;
};

/// <summary>
/// SceneMesh is used to manage and preserve the results of `DenseSpatialMap`_.
/// There are two kinds of meshes saved in SceneMesh, one is the mesh of the whole reconstructed scene, hereinafter referred to as `meshAll`, the other is the recently updated mesh, hereinafter referred to as `meshUpdated`. `meshAll` is a whole mesh, including all vertex data and index data, etc. `meshUpdated` is composed of several `mesh block` s, each `mesh block` is a cube, which contains the mesh formed by the object surface in the corresponding cube space.
/// `meshAll` is available only when the `DenseSpatialMap.updateSceneMesh`_ method is called specifying that all meshes need to be updated. If `meshAll` has been updated previously and not updated in recent times, the data in `meshAll` is remain the same.
/// </summary>
class SceneMesh
{
protected:
    std::shared_ptr<easyar_SceneMesh> cdata_;
    void init_cdata(std::shared_ptr<easyar_SceneMesh> cdata);
    SceneMesh & operator=(const SceneMesh & data) = delete;
public:
    SceneMesh(std::shared_ptr<easyar_SceneMesh> cdata);
    virtual ~SceneMesh();

    std::shared_ptr<easyar_SceneMesh> get_cdata();
    static std::shared_ptr<SceneMesh> from_cdata(std::shared_ptr<easyar_SceneMesh> cdata);

    /// <summary>
    /// Get the number of vertices in `meshAll`.
    /// </summary>
    int getNumOfVertexAll();
    /// <summary>
    /// Get the number of indices in `meshAll`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
    /// </summary>
    int getNumOfIndexAll();
    /// <summary>
    /// Get the position component of the vertices in `meshAll` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
    /// </summary>
    std::shared_ptr<Buffer> getVerticesAll();
    /// <summary>
    /// Get the normal component of vertices in `meshAll`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
    /// </summary>
    std::shared_ptr<Buffer> getNormalsAll();
    /// <summary>
    /// Get the index data in `meshAll`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
    /// </summary>
    std::shared_ptr<Buffer> getIndicesAll();
    /// <summary>
    /// Get the number of vertices in `meshUpdated`.
    /// </summary>
    int getNumOfVertexIncremental();
    /// <summary>
    /// Get the number of indices in `meshUpdated`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
    /// </summary>
    int getNumOfIndexIncremental();
    /// <summary>
    /// Get the position component of the vertices in `meshUpdated` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
    /// </summary>
    std::shared_ptr<Buffer> getVerticesIncremental();
    /// <summary>
    /// Get the normal component of vertices in `meshUpdated`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
    /// </summary>
    std::shared_ptr<Buffer> getNormalsIncremental();
    /// <summary>
    /// Get the index data in `meshUpdated`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
    /// </summary>
    std::shared_ptr<Buffer> getIndicesIncremental();
    /// <summary>
    /// Gets the description object of `mesh block` in `meshUpdate`. The return value is an array of `BlockInfo`_ elements, each of which is a detailed description of a `mesh block`.
    /// </summary>
    std::vector<BlockInfo> getBlocksInfoIncremental();
    /// <summary>
    /// Get the edge length of a `mesh block` in meters.
    /// </summary>
    float getBlockDimensionInMeters();
};

/// <summary>
/// ARCoreCameraDevice implements a camera device based on ARCore, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// Loading of libarcore_sdk_c.so with java.lang.System.loadLibrary is required.
/// After creation, start/stop can be invoked to start or stop video stream capture.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARCoreCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
/// Caution: Currently, ARCore(v1.13.0) has memory leaks on creating and destroying sessions. Repeated creations and destructions will cause an increasing and non-reclaimable memory footprint.
/// </summary>
class ARCoreCameraDevice
{
protected:
    std::shared_ptr<easyar_ARCoreCameraDevice> cdata_;
    void init_cdata(std::shared_ptr<easyar_ARCoreCameraDevice> cdata);
    ARCoreCameraDevice & operator=(const ARCoreCameraDevice & data) = delete;
public:
    ARCoreCameraDevice(std::shared_ptr<easyar_ARCoreCameraDevice> cdata);
    virtual ~ARCoreCameraDevice();

    std::shared_ptr<easyar_ARCoreCameraDevice> get_cdata();
    static std::shared_ptr<ARCoreCameraDevice> from_cdata(std::shared_ptr<easyar_ARCoreCameraDevice> cdata);

    ARCoreCameraDevice();
    /// <summary>
    /// Checks if the component is available. It returns true only on Android when ARCore is installed.
    /// If called with libarcore_sdk_c.so not loaded, it returns false.
    /// Notice: If ARCore is not supported on the device but ARCore apk is installed via side-loading, it will return true, but ARCore will not function properly.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `InputFrame`_ buffer capacity. The default is 8.
    /// </summary>
    int bufferCapacity();
    /// <summary>
    /// Sets `InputFrame`_ buffer capacity.
    /// </summary>
    void setBufferCapacity(int capacity);
    /// <summary>
    /// `InputFrame`_ output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> inputFrameSource();
    /// <summary>
    /// Starts video stream capture.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops video stream capture.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
};

/// <summary>
/// ARKitCameraDevice implements a camera device based on ARKit, which outputs `InputFrame`_ (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// After creation, start/stop can be invoked to start or stop data collection.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARKitCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
class ARKitCameraDevice
{
protected:
    std::shared_ptr<easyar_ARKitCameraDevice> cdata_;
    void init_cdata(std::shared_ptr<easyar_ARKitCameraDevice> cdata);
    ARKitCameraDevice & operator=(const ARKitCameraDevice & data) = delete;
public:
    ARKitCameraDevice(std::shared_ptr<easyar_ARKitCameraDevice> cdata);
    virtual ~ARKitCameraDevice();

    std::shared_ptr<easyar_ARKitCameraDevice> get_cdata();
    static std::shared_ptr<ARKitCameraDevice> from_cdata(std::shared_ptr<easyar_ARKitCameraDevice> cdata);

    ARKitCameraDevice();
    /// <summary>
    /// Checks if the component is available. It returns true only on iOS 11 or later when ARKit is supported by hardware.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `InputFrame`_ buffer capacity. The default is 8.
    /// </summary>
    int bufferCapacity();
    /// <summary>
    /// Sets `InputFrame`_ buffer capacity.
    /// </summary>
    void setBufferCapacity(int capacity);
    /// <summary>
    /// `InputFrame`_ output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> inputFrameSource();
    /// <summary>
    /// Starts video stream capture.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops video stream capture.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
};

/// <summary>
/// CameraDevice implements a camera device, which outputs `InputFrame`_ (including image, camera paramters, and timestamp). It is available on Windows, Mac, Android and iOS.
/// After open, start/stop can be invoked to start or stop data collection. start/stop will not change previous set camera parameters.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// CameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
class CameraDevice
{
protected:
    std::shared_ptr<easyar_CameraDevice> cdata_;
    void init_cdata(std::shared_ptr<easyar_CameraDevice> cdata);
    CameraDevice & operator=(const CameraDevice & data) = delete;
public:
    CameraDevice(std::shared_ptr<easyar_CameraDevice> cdata);
    virtual ~CameraDevice();

    std::shared_ptr<easyar_CameraDevice> get_cdata();
    static std::shared_ptr<CameraDevice> from_cdata(std::shared_ptr<easyar_CameraDevice> cdata);

    CameraDevice();
    /// <summary>
    /// Checks if the component is available. It returns true only on Windows, Mac, Android or iOS.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Gets current camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
    /// </summary>
    AndroidCameraApiType androidCameraApiType();
    /// <summary>
    /// Sets current camera API (camera1 or camera2) on Android. It must be called before calling openWithIndex, openWithSpecificType or openWithPreferredType, or it will not take effect.
    /// It is recommended to use `CameraDeviceSelector`_ to create camera with camera API set to recommended based on primary algorithm to run.
    /// </summary>
    void setAndroidCameraApiType(AndroidCameraApiType type);
    /// <summary>
    /// `InputFrame`_ buffer capacity. The default is 8.
    /// </summary>
    int bufferCapacity();
    /// <summary>
    /// Sets `InputFrame`_ buffer capacity.
    /// </summary>
    void setBufferCapacity(int capacity);
    /// <summary>
    /// `InputFrame`_ output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> inputFrameSource();
    /// <summary>
    /// Sets callback on state change to notify state of camera disconnection or preemption. It is only available on Windows.
    /// </summary>
    void setStateChangedCallback(std::shared_ptr<CallbackScheduler> callbackScheduler, std::optional<std::function<void(CameraState)>> stateChangedCallback);
    /// <summary>
    /// Requests camera permission from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
    /// </summary>
    static void requestPermissions(std::shared_ptr<CallbackScheduler> callbackScheduler, std::optional<std::function<void(PermissionStatus, std::string)>> permissionCallback);
    /// <summary>
    /// Gets count of cameras recognized by the operating system.
    /// </summary>
    static int cameraCount();
    /// <summary>
    /// Opens a camera by index.
    /// </summary>
    bool openWithIndex(int cameraIndex);
    /// <summary>
    /// Opens a camera by specific camera device type. If no camera is matched, false will be returned. On Mac, camera device types can not be distinguished.
    /// </summary>
    bool openWithSpecificType(CameraDeviceType type);
    /// <summary>
    /// Opens a camera by camera device type. If no camera is matched, the first camera will be used.
    /// </summary>
    bool openWithPreferredType(CameraDeviceType type);
    /// <summary>
    /// Starts video stream capture.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops video stream capture. It will only stop capture and will not change previous set camera parameters and connection.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Camera index.
    /// </summary>
    int index();
    /// <summary>
    /// Camera type.
    /// </summary>
    CameraDeviceType type();
    /// <summary>
    /// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation. Call after a successful open.
    /// </summary>
    std::shared_ptr<CameraParameters> cameraParameters();
    /// <summary>
    /// Sets camera parameters. Call after a successful open.
    /// </summary>
    void setCameraParameters(std::shared_ptr<CameraParameters> cameraParameters);
    /// <summary>
    /// Gets the current preview size. Call after a successful open.
    /// </summary>
    Vec2I size();
    /// <summary>
    /// Gets the number of supported preview sizes. Call after a successful open.
    /// </summary>
    int supportedSizeCount();
    /// <summary>
    /// Gets the index-th supported preview size. It returns {0, 0} if index is out of range. Call after a successful open.
    /// </summary>
    Vec2I supportedSize(int index);
    /// <summary>
    /// Sets the preview size. The available nearest value will be selected. Call size to get the actual size. Call after a successful open. frameRateRange may change after calling setSize.
    /// </summary>
    bool setSize(Vec2I size);
    /// <summary>
    /// Gets the number of supported frame rate ranges. Call after a successful open.
    /// </summary>
    int supportedFrameRateRangeCount();
    /// <summary>
    /// Gets range lower bound of the index-th supported frame rate range. Call after a successful open.
    /// </summary>
    float supportedFrameRateRangeLower(int index);
    /// <summary>
    /// Gets range upper bound of the index-th supported frame rate range. Call after a successful open.
    /// </summary>
    float supportedFrameRateRangeUpper(int index);
    /// <summary>
    /// Gets current index of frame rate range. Call after a successful open.
    /// </summary>
    int frameRateRange();
    /// <summary>
    /// Sets current index of frame rate range. Call after a successful open.
    /// </summary>
    bool setFrameRateRange(int index);
    /// <summary>
    /// Sets flash torch mode to on. Call after a successful open.
    /// </summary>
    bool setFlashTorchMode(bool on);
    /// <summary>
    /// Sets focus mode to focusMode. Call after a successful open.
    /// </summary>
    bool setFocusMode(CameraDeviceFocusMode focusMode);
    /// <summary>
    /// Does auto focus once. Call after start. It is only available when FocusMode is Normal or Macro.
    /// </summary>
    bool autoFocus();
};

/// <summary>
/// It is used for selecting camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
/// Different preferences will choose camera1 or camera2 based on usage.
/// </summary>
class CameraDeviceSelector
{
public:
    /// <summary>
    /// Gets recommended Android Camera API type by a specified preference.
    /// </summary>
    static AndroidCameraApiType getAndroidCameraApiType(CameraDevicePreference preference);
    /// <summary>
    /// Creates `CameraDevice`_ by a specified preference.
    /// </summary>
    static std::shared_ptr<CameraDevice> createCameraDevice(CameraDevicePreference preference);
};

/// <summary>
/// Result of `SurfaceTracker`_ .
/// </summary>
class SurfaceTrackerResult : public FrameFilterResult
{
protected:
    std::shared_ptr<easyar_SurfaceTrackerResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_SurfaceTrackerResult> cdata);
    SurfaceTrackerResult & operator=(const SurfaceTrackerResult & data) = delete;
public:
    SurfaceTrackerResult(std::shared_ptr<easyar_SurfaceTrackerResult> cdata);
    virtual ~SurfaceTrackerResult();

    std::shared_ptr<easyar_SurfaceTrackerResult> get_cdata();
    static std::shared_ptr<SurfaceTrackerResult> from_cdata(std::shared_ptr<easyar_SurfaceTrackerResult> cdata);

    /// <summary>
    /// Camera transform against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) For the world coordinate system, y is up (to the opposite of gravity). The data arrangement is row-major, not like OpenGL&#39;s column-major.
    /// </summary>
    Matrix44F transform();
};

/// <summary>
/// SurfaceTracker implements tracking with environmental surfaces.
/// SurfaceTracker occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// SurfaceTracker inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
class SurfaceTracker
{
protected:
    std::shared_ptr<easyar_SurfaceTracker> cdata_;
    void init_cdata(std::shared_ptr<easyar_SurfaceTracker> cdata);
    SurfaceTracker & operator=(const SurfaceTracker & data) = delete;
public:
    SurfaceTracker(std::shared_ptr<easyar_SurfaceTracker> cdata);
    virtual ~SurfaceTracker();

    std::shared_ptr<easyar_SurfaceTracker> get_cdata();
    static std::shared_ptr<SurfaceTracker> from_cdata(std::shared_ptr<easyar_SurfaceTracker> cdata);

    /// <summary>
    /// Returns true only on Android or iOS when accelerometer and gyroscope are available.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `InputFrame`_ input port. InputFrame must have raw image, timestamp, and camera parameters.
    /// </summary>
    std::shared_ptr<InputFrameSink> inputFrameSink();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// `OutputFrame`_ output port.
    /// </summary>
    std::shared_ptr<OutputFrameSource> outputFrameSource();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<SurfaceTracker> create();
    /// <summary>
    /// Starts the track algorithm.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops the track algorithm. Call start to start the track again.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Sets the tracking target to a point on camera image. For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// </summary>
    void alignTargetToCameraImagePoint(Vec2F cameraImagePoint);
};

/// <summary>
/// MotionTrackerCameraDevice implements a camera device with metric-scale six degree-of-freedom motion tracking, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF pose and tracking status).
/// After creation, start/stop can be invoked to start or stop data flow.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// MotionTrackerCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for further use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
class MotionTrackerCameraDevice
{
protected:
    std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata_;
    void init_cdata(std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata);
    MotionTrackerCameraDevice & operator=(const MotionTrackerCameraDevice & data) = delete;
public:
    MotionTrackerCameraDevice(std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata);
    virtual ~MotionTrackerCameraDevice();

    std::shared_ptr<easyar_MotionTrackerCameraDevice> get_cdata();
    static std::shared_ptr<MotionTrackerCameraDevice> from_cdata(std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata);

    /// <summary>
    /// Create MotionTrackerCameraDevice object.
    /// </summary>
    MotionTrackerCameraDevice();
    /// <summary>
    /// Check if the devices supports motion tracking. Returns True if the device supports Motion Tracking, otherwise returns False.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Set `InputFrame`_ buffer capacity.
    /// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is higher than this number, the device will not output new `InputFrame`_ until previous `InputFrame`_ has been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`__ .
    /// </summary>
    void setBufferCapacity(int capacity);
    /// <summary>
    /// Get `InputFrame`_ buffer capacity. The default is 8.
    /// </summary>
    int bufferCapacity();
    /// <summary>
    /// `InputFrame`_ output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> inputFrameSource();
    /// <summary>
    /// Start motion tracking or resume motion tracking after pause.
    /// Notice: Calling start after pausing will trigger device relocalization. Tracking will resume when the relocalization process succeeds.
    /// </summary>
    bool start();
    /// <summary>
    /// Pause motion tracking. Call `start` to trigger relocation, resume motion tracking if the relocation succeeds.
    /// </summary>
    void stop();
    /// <summary>
    /// Close motion tracking. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Perform hit test against the point cloud and return the nearest 3D point. The 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
    /// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// </summary>
    std::vector<Vec3F> hitTestAgainstPointCloud(Vec2F cameraImagePoint);
    /// <summary>
    /// Performs ray cast from the user&#39;s device in the direction of given screen point.
    /// Intersections with horizontal plane is detected in real time in the current field of view,and return the 3D point nearest to ray on horizontal plane.
    /// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// The output point cloud coordinate on Horizontal plane is in the world coordinate system. The 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
    /// </summary>
    std::vector<Vec3F> hitTestAgainstHorizontalPlane(Vec2F cameraImagePoint);
    /// <summary>
    /// Returns the vector of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space.
    /// </summary>
    std::vector<Vec3F> getLocalPointsCloud();
};

/// <summary>
/// Input frame recorder.
/// There is an input frame input port and an input frame output port. It can be used to record input frames into an EIF file. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class InputFrameRecorder
{
protected:
    std::shared_ptr<easyar_InputFrameRecorder> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameRecorder> cdata);
    InputFrameRecorder & operator=(const InputFrameRecorder & data) = delete;
public:
    InputFrameRecorder(std::shared_ptr<easyar_InputFrameRecorder> cdata);
    virtual ~InputFrameRecorder();

    std::shared_ptr<easyar_InputFrameRecorder> get_cdata();
    static std::shared_ptr<InputFrameRecorder> from_cdata(std::shared_ptr<easyar_InputFrameRecorder> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<InputFrameSink> input();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> output();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFrameRecorder> create();
    /// <summary>
    /// Starts frame recording.
    /// </summary>
    bool start(std::string filePath);
    /// <summary>
    /// Stops frame recording. It will only stop recording and will not affect connection.
    /// </summary>
    void stop();
};

/// <summary>
/// Input frame player.
/// There is an input frame output port. It can be used to get input frame from an EIF file. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class InputFramePlayer
{
protected:
    std::shared_ptr<easyar_InputFramePlayer> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFramePlayer> cdata);
    InputFramePlayer & operator=(const InputFramePlayer & data) = delete;
public:
    InputFramePlayer(std::shared_ptr<easyar_InputFramePlayer> cdata);
    virtual ~InputFramePlayer();

    std::shared_ptr<easyar_InputFramePlayer> get_cdata();
    static std::shared_ptr<InputFramePlayer> from_cdata(std::shared_ptr<easyar_InputFramePlayer> cdata);

    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> output();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFramePlayer> create();
    /// <summary>
    /// Starts frame play.
    /// </summary>
    bool start(std::string filePath);
    /// <summary>
    /// Stops frame play.
    /// </summary>
    void stop();
};

/// <summary>
/// Callback scheduler.
/// There are two subclasses: `DelayedCallbackScheduler`_ and `ImmediateCallbackScheduler`_ .
/// `DelayedCallbackScheduler`_ is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// `ImmediateCallbackScheduler`_ is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// </summary>
class CallbackScheduler
{
protected:
    std::shared_ptr<easyar_CallbackScheduler> cdata_;
    void init_cdata(std::shared_ptr<easyar_CallbackScheduler> cdata);
    CallbackScheduler & operator=(const CallbackScheduler & data) = delete;
public:
    CallbackScheduler(std::shared_ptr<easyar_CallbackScheduler> cdata);
    virtual ~CallbackScheduler();

    std::shared_ptr<easyar_CallbackScheduler> get_cdata();
    static std::shared_ptr<CallbackScheduler> from_cdata(std::shared_ptr<easyar_CallbackScheduler> cdata);

};

/// <summary>
/// Delayed callback scheduler.
/// It is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// All members of this class is thread-safe.
/// </summary>
class DelayedCallbackScheduler : public CallbackScheduler
{
protected:
    std::shared_ptr<easyar_DelayedCallbackScheduler> cdata_;
    void init_cdata(std::shared_ptr<easyar_DelayedCallbackScheduler> cdata);
    DelayedCallbackScheduler & operator=(const DelayedCallbackScheduler & data) = delete;
public:
    DelayedCallbackScheduler(std::shared_ptr<easyar_DelayedCallbackScheduler> cdata);
    virtual ~DelayedCallbackScheduler();

    std::shared_ptr<easyar_DelayedCallbackScheduler> get_cdata();
    static std::shared_ptr<DelayedCallbackScheduler> from_cdata(std::shared_ptr<easyar_DelayedCallbackScheduler> cdata);

    DelayedCallbackScheduler();
    /// <summary>
    /// Executes a callback. If there is no callback to execute, false is returned.
    /// </summary>
    bool runOne();
};

/// <summary>
/// Immediate callback scheduler.
/// It is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// All members of this class is thread-safe.
/// </summary>
class ImmediateCallbackScheduler : public CallbackScheduler
{
protected:
    std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata_;
    void init_cdata(std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata);
    ImmediateCallbackScheduler & operator=(const ImmediateCallbackScheduler & data) = delete;
public:
    ImmediateCallbackScheduler(std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata);
    virtual ~ImmediateCallbackScheduler();

    std::shared_ptr<easyar_ImmediateCallbackScheduler> get_cdata();
    static std::shared_ptr<ImmediateCallbackScheduler> from_cdata(std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata);

    /// <summary>
    /// Gets a default immediate callback scheduler.
    /// </summary>
    static std::shared_ptr<ImmediateCallbackScheduler> getDefault();
};

/// <summary>
/// JNI utility class.
/// It is used in Unity to wrap Java byte array and ByteBuffer.
/// It is not supported on iOS.
/// </summary>
class JniUtility
{
public:
    /// <summary>
    /// Wraps Java&#39;s byte[]。
    /// </summary>
    static std::shared_ptr<Buffer> wrapByteArray(void * bytes, bool readOnly, std::function<void()> deleter);
    /// <summary>
    /// Wraps Java&#39;s java.nio.ByteBuffer, which must be a direct buffer.
    /// </summary>
    static std::shared_ptr<Buffer> wrapBuffer(void * directBuffer, std::function<void()> deleter);
    /// <summary>
    /// Get the raw address of a direct buffer of java.nio.ByteBuffer by calling JNIEnv-&gt;GetDirectBufferAddress.
    /// </summary>
    static void * getDirectBufferAddress(void * directBuffer);
};

/// <summary>
/// Log class.
/// It is used to setup a custom log output function.
/// </summary>
class Log
{
public:
    /// <summary>
    /// Sets custom log output function.
    /// </summary>
    static void setLogFunc(std::function<void(LogLevel, std::string)> func);
    /// <summary>
    /// Clears custom log output function and reverts to default log output function.
    /// </summary>
    static void resetLogFunc();
};

/// <summary>
/// ImageTargetParameters represents the parameters to create a `ImageTarget`_ .
/// </summary>
class ImageTargetParameters
{
protected:
    std::shared_ptr<easyar_ImageTargetParameters> cdata_;
    void init_cdata(std::shared_ptr<easyar_ImageTargetParameters> cdata);
    ImageTargetParameters & operator=(const ImageTargetParameters & data) = delete;
public:
    ImageTargetParameters(std::shared_ptr<easyar_ImageTargetParameters> cdata);
    virtual ~ImageTargetParameters();

    std::shared_ptr<easyar_ImageTargetParameters> get_cdata();
    static std::shared_ptr<ImageTargetParameters> from_cdata(std::shared_ptr<easyar_ImageTargetParameters> cdata);

    ImageTargetParameters();
    /// <summary>
    /// Gets image.
    /// </summary>
    std::shared_ptr<Image> image();
    /// <summary>
    /// Sets image.
    /// </summary>
    void setImage(std::shared_ptr<Image> image);
    /// <summary>
    /// Gets target name. It can be used to distinguish targets.
    /// </summary>
    std::string name();
    /// <summary>
    /// Sets target name.
    /// </summary>
    void setName(std::string name);
    /// <summary>
    /// Gets the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as an alternative method to distinguish from targets.
    /// </summary>
    std::string uid();
    /// <summary>
    /// Sets target uid.
    /// </summary>
    void setUid(std::string uid);
    /// <summary>
    /// Gets meta data.
    /// </summary>
    std::string meta();
    /// <summary>
    /// Sets meta data。
    /// </summary>
    void setMeta(std::string meta);
    /// <summary>
    /// Gets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
    /// </summary>
    float scale();
    /// <summary>
    /// Sets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
    /// It is needed to set the model scale in rendering engine separately.
    /// </summary>
    void setScale(float scale);
};

/// <summary>
/// ImageTarget represents planar image targets that can be tracked by `ImageTracker`_ .
/// The fields of ImageTarget need to be filled with the create... method before it can be read. And ImageTarget can be tracked by `ImageTracker`_ after a successful load into the `ImageTracker`_ using `ImageTracker.loadTarget`_ .
/// </summary>
class ImageTarget : public Target
{
protected:
    std::shared_ptr<easyar_ImageTarget> cdata_;
    void init_cdata(std::shared_ptr<easyar_ImageTarget> cdata);
    ImageTarget & operator=(const ImageTarget & data) = delete;
public:
    ImageTarget(std::shared_ptr<easyar_ImageTarget> cdata);
    virtual ~ImageTarget();

    std::shared_ptr<easyar_ImageTarget> get_cdata();
    static std::shared_ptr<ImageTarget> from_cdata(std::shared_ptr<easyar_ImageTarget> cdata);

    ImageTarget();
    /// <summary>
    /// Creates a target from parameters.
    /// </summary>
    static std::optional<std::shared_ptr<ImageTarget>> createFromParameters(std::shared_ptr<ImageTargetParameters> parameters);
    /// <summary>
    /// Creates a target from an etd file.
    /// </summary>
    static std::optional<std::shared_ptr<ImageTarget>> createFromTargetFile(std::string path, StorageType storageType);
    /// <summary>
    /// Creates a target from an etd data buffer.
    /// </summary>
    static std::optional<std::shared_ptr<ImageTarget>> createFromTargetData(std::shared_ptr<Buffer> buffer);
    /// <summary>
    /// Saves as an etd file.
    /// </summary>
    bool save(std::string path);
    /// <summary>
    /// Creates a target from an image file. If not needed, name, uid, meta can be passed with empty string, and scale can be passed with default value 1. Jpeg and png files are supported.
    /// </summary>
    static std::optional<std::shared_ptr<ImageTarget>> createFromImageFile(std::string path, StorageType storageType, std::string name, std::string uid, std::string meta, float scale);
    /// <summary>
    /// The scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
    /// </summary>
    float scale();
    /// <summary>
    /// The aspect ratio of image, width divided by height.
    /// </summary>
    float aspectRatio();
    /// <summary>
    /// Sets image target scale, this will overwrite the value set in the json file or the default value. The value is the physical image width divided by 1 meter. The default value is 1.
    /// It is needed to set the model scale in rendering engine separately.
    /// </summary>
    bool setScale(float scale);
    /// <summary>
    /// Returns a list of images that stored in the target. It is generally used to get image data from cloud returned target.
    /// </summary>
    std::vector<std::shared_ptr<Image>> images();
    /// <summary>
    /// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
    /// </summary>
    int runtimeID();
    /// <summary>
    /// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
    /// </summary>
    std::string uid();
    /// <summary>
    /// Returns the target name. Name is used to distinguish targets in a json file.
    /// </summary>
    std::string name();
    /// <summary>
    /// Set name. It will erase previously set data or data from cloud.
    /// </summary>
    void setName(std::string name);
    /// <summary>
    /// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
    /// </summary>
    std::string meta();
    /// <summary>
    /// Set meta data. It will erase previously set data or data from cloud.
    /// </summary>
    void setMeta(std::string data);
};

/// <summary>
/// Result of `ImageTracker`_ .
/// </summary>
class ImageTrackerResult : public TargetTrackerResult
{
protected:
    std::shared_ptr<easyar_ImageTrackerResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_ImageTrackerResult> cdata);
    ImageTrackerResult & operator=(const ImageTrackerResult & data) = delete;
public:
    ImageTrackerResult(std::shared_ptr<easyar_ImageTrackerResult> cdata);
    virtual ~ImageTrackerResult();

    std::shared_ptr<easyar_ImageTrackerResult> get_cdata();
    static std::shared_ptr<ImageTrackerResult> from_cdata(std::shared_ptr<easyar_ImageTrackerResult> cdata);

    /// <summary>
    /// Returns the list of `TargetInstance`_ contained in the result.
    /// </summary>
    std::vector<std::shared_ptr<TargetInstance>> targetInstances();
    /// <summary>
    /// Sets the list of `TargetInstance`_ contained in the result.
    /// </summary>
    void setTargetInstances(std::vector<std::shared_ptr<TargetInstance>> instances);
};

/// <summary>
/// ImageTracker implements image target detection and tracking.
/// ImageTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ImageTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`__ .
/// Before a `Target`_ can be tracked by ImageTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
/// </summary>
class ImageTracker
{
protected:
    std::shared_ptr<easyar_ImageTracker> cdata_;
    void init_cdata(std::shared_ptr<easyar_ImageTracker> cdata);
    ImageTracker & operator=(const ImageTracker & data) = delete;
public:
    ImageTracker(std::shared_ptr<easyar_ImageTracker> cdata);
    virtual ~ImageTracker();

    std::shared_ptr<easyar_ImageTracker> get_cdata();
    static std::shared_ptr<ImageTracker> from_cdata(std::shared_ptr<easyar_ImageTracker> cdata);

    /// <summary>
    /// Returns true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// `FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
    /// </summary>
    std::shared_ptr<FeedbackFrameSink> feedbackFrameSink();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// `OutputFrame`_ output port.
    /// </summary>
    std::shared_ptr<OutputFrameSource> outputFrameSource();
    /// <summary>
    /// Creates an instance. The default track mode is `ImageTrackerMode.PreferQuality`_ .
    /// </summary>
    static std::shared_ptr<ImageTracker> create();
    /// <summary>
    /// Creates an instance with a specified track mode. On lower-end phones, `ImageTrackerMode.PreferPerformance`_ can be used to keep a better performance with a little quality loss.
    /// </summary>
    static std::shared_ptr<ImageTracker> createWithMode(ImageTrackerMode trackMode);
    /// <summary>
    /// Starts the track algorithm.
    /// </summary>
    bool start();
    /// <summary>
    /// Stops the track algorithm. Call start to start the track again.
    /// </summary>
    void stop();
    /// <summary>
    /// Close. The component shall not be used after calling close.
    /// </summary>
    void close();
    /// <summary>
    /// Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
    /// This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
    /// </summary>
    void loadTarget(std::shared_ptr<Target> target, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(std::shared_ptr<Target>, bool)> callback);
    /// <summary>
    /// Unload a `Target`_ from the tracker.
    /// This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
    /// </summary>
    void unloadTarget(std::shared_ptr<Target> target, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(std::shared_ptr<Target>, bool)> callback);
    /// <summary>
    /// Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
    /// </summary>
    std::vector<std::shared_ptr<Target>> targets();
    /// <summary>
    /// Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
    /// </summary>
    bool setSimultaneousNum(int num);
    /// <summary>
    /// Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
    /// </summary>
    int simultaneousNum();
};

/// <summary>
/// Recorder implements recording for current rendering screen.
/// Currently Recorder only works on Android (4.3 or later) and iOS with OpenGL ES 2.0 context.
/// Due to the dependency to OpenGLES, every method in this class (except requestPermissions, including the destructor) has to be called in a single thread containing an OpenGLES context.
/// **Unity Only** If in Unity, Multi-threaded rendering is enabled, scripting thread and rendering thread will be two separate threads, which makes it impossible to call updateFrame in the rendering thread. For this reason, to use Recorder, Multi-threaded rendering option shall be disabled.
/// </summary>
class Recorder
{
protected:
    std::shared_ptr<easyar_Recorder> cdata_;
    void init_cdata(std::shared_ptr<easyar_Recorder> cdata);
    Recorder & operator=(const Recorder & data) = delete;
public:
    Recorder(std::shared_ptr<easyar_Recorder> cdata);
    virtual ~Recorder();

    std::shared_ptr<easyar_Recorder> get_cdata();
    static std::shared_ptr<Recorder> from_cdata(std::shared_ptr<easyar_Recorder> cdata);

    /// <summary>
    /// Returns true only on Android 4.3 or later, or on iOS.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Requests recording permissions from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
    /// </summary>
    static void requestPermissions(std::shared_ptr<CallbackScheduler> callbackScheduler, std::optional<std::function<void(PermissionStatus, std::string)>> permissionCallback);
    /// <summary>
    /// Creates an instance and initialize recording. statusCallback will dispatch event of status change and corresponding log.
    /// </summary>
    static std::shared_ptr<Recorder> create(std::shared_ptr<RecorderConfiguration> config, std::shared_ptr<CallbackScheduler> callbackScheduler, std::optional<std::function<void(RecordStatus, std::string)>> statusCallback);
    /// <summary>
    /// Start recording.
    /// </summary>
    void start();
    /// <summary>
    /// Update and record a frame using texture data.
    /// </summary>
    void updateFrame(std::shared_ptr<TextureId> texture, int width, int height);
    /// <summary>
    /// Stop recording. When calling stop, it will wait for file write to end and returns whether recording is successful.
    /// </summary>
    bool stop();
};

/// <summary>
/// RecorderConfiguration is startup configuration for `Recorder`_ .
/// </summary>
class RecorderConfiguration
{
protected:
    std::shared_ptr<easyar_RecorderConfiguration> cdata_;
    void init_cdata(std::shared_ptr<easyar_RecorderConfiguration> cdata);
    RecorderConfiguration & operator=(const RecorderConfiguration & data) = delete;
public:
    RecorderConfiguration(std::shared_ptr<easyar_RecorderConfiguration> cdata);
    virtual ~RecorderConfiguration();

    std::shared_ptr<easyar_RecorderConfiguration> get_cdata();
    static std::shared_ptr<RecorderConfiguration> from_cdata(std::shared_ptr<easyar_RecorderConfiguration> cdata);

    RecorderConfiguration();
    /// <summary>
    /// Sets absolute path for output video file.
    /// </summary>
    void setOutputFile(std::string path);
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

/// <summary>
/// Describes the result of mapping and localization. Updated at the same frame rate with OutputFrame.
/// </summary>
class SparseSpatialMapResult : public FrameFilterResult
{
protected:
    std::shared_ptr<easyar_SparseSpatialMapResult> cdata_;
    void init_cdata(std::shared_ptr<easyar_SparseSpatialMapResult> cdata);
    SparseSpatialMapResult & operator=(const SparseSpatialMapResult & data) = delete;
public:
    SparseSpatialMapResult(std::shared_ptr<easyar_SparseSpatialMapResult> cdata);
    virtual ~SparseSpatialMapResult();

    std::shared_ptr<easyar_SparseSpatialMapResult> get_cdata();
    static std::shared_ptr<SparseSpatialMapResult> from_cdata(std::shared_ptr<easyar_SparseSpatialMapResult> cdata);

    /// <summary>
    /// Obtain motion tracking status.
    /// </summary>
    MotionTrackingStatus getMotionTrackingStatus();
    /// <summary>
    /// Returns pose of the origin of VIO system in camera coordinate system.
    /// </summary>
    std::optional<Matrix44F> getVioPose();
    /// <summary>
    /// Returns the pose of origin of the map in camera coordinate system, when localization is successful.
    /// Otherwise, returns pose of the origin of VIO system in camera coordinate system.
    /// </summary>
    std::optional<Matrix44F> getMapPose();
    /// <summary>
    /// Returns true if the system can reliablly locate the pose of the device with regard to the map.
    /// Once relocalization succeeds, relative pose can be updated by motion tracking module.
    /// As long as the motion tracking module returns normal tracking status, the localization status is also true.
    /// </summary>
    bool getLocalizationStatus();
    /// <summary>
    /// Returns current localized map ID.
    /// </summary>
    std::string getLocalizationMapID();
};

class PlaneData
{
protected:
    std::shared_ptr<easyar_PlaneData> cdata_;
    void init_cdata(std::shared_ptr<easyar_PlaneData> cdata);
    PlaneData & operator=(const PlaneData & data) = delete;
public:
    PlaneData(std::shared_ptr<easyar_PlaneData> cdata);
    virtual ~PlaneData();

    std::shared_ptr<easyar_PlaneData> get_cdata();
    static std::shared_ptr<PlaneData> from_cdata(std::shared_ptr<easyar_PlaneData> cdata);

    /// <summary>
    /// Constructor
    /// </summary>
    PlaneData();
    /// <summary>
    /// Returns the type of this plane.
    /// </summary>
    PlaneType getType();
    /// <summary>
    /// Returns the pose of the center of the detected plane.The pose&#39;s transformed +Y axis will be point normal out of the plane, with the +X and +Z axes orienting the extents of the bounding rectangle.
    /// </summary>
    Matrix44F getPose();
    /// <summary>
    /// Returns the length of this plane&#39;s bounding rectangle measured along the local X-axis of the coordinate space centered on the plane.
    /// </summary>
    float getExtentX();
    /// <summary>
    /// Returns the length of this plane&#39;s bounding rectangle measured along the local Z-axis of the coordinate frame centered on the plane.
    /// </summary>
    float getExtentZ();
};

/// <summary>
/// Configuration used to set the localization mode.
/// </summary>
class SparseSpatialMapConfig
{
protected:
    std::shared_ptr<easyar_SparseSpatialMapConfig> cdata_;
    void init_cdata(std::shared_ptr<easyar_SparseSpatialMapConfig> cdata);
    SparseSpatialMapConfig & operator=(const SparseSpatialMapConfig & data) = delete;
public:
    SparseSpatialMapConfig(std::shared_ptr<easyar_SparseSpatialMapConfig> cdata);
    virtual ~SparseSpatialMapConfig();

    std::shared_ptr<easyar_SparseSpatialMapConfig> get_cdata();
    static std::shared_ptr<SparseSpatialMapConfig> from_cdata(std::shared_ptr<easyar_SparseSpatialMapConfig> cdata);

    /// <summary>
    /// Constructor
    /// </summary>
    SparseSpatialMapConfig();
    /// <summary>
    /// Sets localization configurations. See also `LocalizationMode`_.
    /// </summary>
    void setLocalizationMode(LocalizationMode _value);
    /// <summary>
    /// Returns localization configurations. See also `LocalizationMode`_.
    /// </summary>
    LocalizationMode getLocalizationMode();
};

/// <summary>
/// Provides core components for SparseSpatialMap, can be used for sparse spatial map building as well as localization using existing map. Also provides utilities for point cloud and plane access.
/// SparseSpatialMap occupies 2 buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// </summary>
class SparseSpatialMap
{
protected:
    std::shared_ptr<easyar_SparseSpatialMap> cdata_;
    void init_cdata(std::shared_ptr<easyar_SparseSpatialMap> cdata);
    SparseSpatialMap & operator=(const SparseSpatialMap & data) = delete;
public:
    SparseSpatialMap(std::shared_ptr<easyar_SparseSpatialMap> cdata);
    virtual ~SparseSpatialMap();

    std::shared_ptr<easyar_SparseSpatialMap> get_cdata();
    static std::shared_ptr<SparseSpatialMap> from_cdata(std::shared_ptr<easyar_SparseSpatialMap> cdata);

    /// <summary>
    /// Check whether SparseSpatialMap is is available, always return true.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Input port for input frame. For SparseSpatialMap to work, the inputFrame must include camera parameters, timestamp and spatial information. See also `InputFrameSink`_
    /// </summary>
    std::shared_ptr<InputFrameSink> inputFrameSink();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port for output frame. See also `OutputFrameSource`_
    /// </summary>
    std::shared_ptr<OutputFrameSource> outputFrameSource();
    /// <summary>
    /// Construct SparseSpatialMap.
    /// </summary>
    static std::shared_ptr<SparseSpatialMap> create();
    /// <summary>
    /// Start SparseSpatialMap system.
    /// </summary>
    bool start();
    /// <summary>
    /// Stop SparseSpatialMap from running。Can resume running by calling start().
    /// </summary>
    void stop();
    /// <summary>
    /// Close SparseSpatialMap. SparseSpatialMap can no longer be used.
    /// </summary>
    void close();
    /// <summary>
    /// Returns the buffer of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space, each of which takes 4 bytes.
    /// </summary>
    std::shared_ptr<Buffer> getPointCloudBuffer();
    /// <summary>
    /// Returns detected planes in SparseSpatialMap.
    /// </summary>
    std::vector<std::shared_ptr<PlaneData>> getMapPlanes();
    /// <summary>
    /// Perform hit test against the point cloud. The results are returned sorted by their distance to the camera in ascending order.
    /// </summary>
    std::vector<Vec3F> hitTestAgainstPointCloud(Vec2F cameraImagePoint);
    /// <summary>
    /// Performs ray cast from the user&#39;s device in the direction of given screen point.
    /// Intersections with detected planes are returned. 3D positions on physical planes are sorted by distance from the device in ascending order.
    /// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
    /// The output point cloud coordinate is in the world coordinate system.
    /// </summary>
    std::vector<Vec3F> hitTestAgainstPlanes(Vec2F cameraImagePoint);
    /// <summary>
    /// Get the map data version of the current SparseSpatialMap.
    /// </summary>
    static std::string getMapVersion();
    /// <summary>
    /// UnloadMap specified SparseSpatialMap data via callback function.The return value of callback indicates whether unload map succeeds (true) or fails (false).
    /// </summary>
    void unloadMap(std::string mapID, std::shared_ptr<CallbackScheduler> callbackScheduler, std::optional<std::function<void(bool)>> resultCallBack);
    /// <summary>
    /// Set configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
    /// </summary>
    void setConfig(std::shared_ptr<SparseSpatialMapConfig> config);
    /// <summary>
    /// Returns configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
    /// </summary>
    std::shared_ptr<SparseSpatialMapConfig> getConfig();
    /// <summary>
    /// Start localization in loaded maps. Should set `LocalizationMode`_ first.
    /// </summary>
    bool startLocalization();
    /// <summary>
    /// Stop localization in loaded maps.
    /// </summary>
    void stopLocalization();
};

/// <summary>
/// SparseSpatialMap manager class, for managing sharing.
/// </summary>
class SparseSpatialMapManager
{
protected:
    std::shared_ptr<easyar_SparseSpatialMapManager> cdata_;
    void init_cdata(std::shared_ptr<easyar_SparseSpatialMapManager> cdata);
    SparseSpatialMapManager & operator=(const SparseSpatialMapManager & data) = delete;
public:
    SparseSpatialMapManager(std::shared_ptr<easyar_SparseSpatialMapManager> cdata);
    virtual ~SparseSpatialMapManager();

    std::shared_ptr<easyar_SparseSpatialMapManager> get_cdata();
    static std::shared_ptr<SparseSpatialMapManager> from_cdata(std::shared_ptr<easyar_SparseSpatialMapManager> cdata);

    /// <summary>
    /// Check whether SparseSpatialMapManager is is available. It returns true when the operating system is Windows, Mac, iOS or Android.
    /// </summary>
    static bool isAvailable();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<SparseSpatialMapManager> create();
    /// <summary>
    /// Creates a map from `SparseSpatialMap`_ and upload it to EasyAR cloud servers. After completion, a serverMapId will be returned for loading map from EasyAR cloud servers.
    /// </summary>
    void host(std::shared_ptr<SparseSpatialMap> mapBuilder, std::string apiKey, std::string apiSecret, std::string sparseSpatialMapAppId, std::string name, std::optional<std::shared_ptr<Image>> preview, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(bool, std::string, std::string)> onCompleted);
    /// <summary>
    /// Loads a map from EasyAR cloud servers by serverMapId. To unload the map, call `SparseSpatialMap.unloadMap`_ with serverMapId.
    /// </summary>
    void load(std::shared_ptr<SparseSpatialMap> mapTracker, std::string serverMapId, std::string apiKey, std::string apiSecret, std::string sparseSpatialMapAppId, std::shared_ptr<CallbackScheduler> callbackScheduler, std::function<void(bool, std::string)> onCompleted);
    /// <summary>
    /// Clears allocated cache space.
    /// </summary>
    void clear();
};

class Engine
{
public:
    /// <summary>
    /// Gets the version schema hash, which can be used to ensure type declarations consistent with runtime library.
    /// </summary>
    static int schemaHash();
    static bool initialize(std::string key);
    /// <summary>
    /// Handles the app onPause, pauses internal tasks.
    /// </summary>
    static void onPause();
    /// <summary>
    /// Handles the app onResume, resumes internal tasks.
    /// </summary>
    static void onResume();
    /// <summary>
    /// Gets error message on initialization failure.
    /// </summary>
    static std::string errorMessage();
    /// <summary>
    /// Gets the version number of EasyARSense.
    /// </summary>
    static std::string versionString();
    /// <summary>
    /// Gets the product name of EasyARSense. (Including variant, operating system and CPU architecture.)
    /// </summary>
    static std::string name();
};

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
    std::shared_ptr<easyar_VideoPlayer> cdata_;
    void init_cdata(std::shared_ptr<easyar_VideoPlayer> cdata);
    VideoPlayer & operator=(const VideoPlayer & data) = delete;
public:
    VideoPlayer(std::shared_ptr<easyar_VideoPlayer> cdata);
    virtual ~VideoPlayer();

    std::shared_ptr<easyar_VideoPlayer> get_cdata();
    static std::shared_ptr<VideoPlayer> from_cdata(std::shared_ptr<easyar_VideoPlayer> cdata);

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
    void setRenderTexture(std::shared_ptr<TextureId> texture);
    /// <summary>
    /// Opens a video from path.
    /// path can be a local video file (path/to/video.mp4) or url (http://www.../.../video.mp4). storageType indicates the type of path. See `StorageType`_ for more description.
    /// This method is an asynchronous method. Open may take some time to finish. If you want to know the open result or the play status while playing, you have to handle callback. The callback will be called from a different thread. You can check if the open finished successfully and start play after a successful open.
    /// </summary>
    void open(std::string path, StorageType storageType, std::shared_ptr<CallbackScheduler> callbackScheduler, std::optional<std::function<void(VideoStatus)>> callback);
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

/// <summary>
/// Image helper class.
/// </summary>
class ImageHelper
{
public:
    /// <summary>
    /// Decodes a JPEG or PNG file.
    /// </summary>
    static std::optional<std::shared_ptr<Image>> decode(std::shared_ptr<Buffer> buffer);
};

/// <summary>
/// Signal input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class SignalSink
{
protected:
    std::shared_ptr<easyar_SignalSink> cdata_;
    void init_cdata(std::shared_ptr<easyar_SignalSink> cdata);
    SignalSink & operator=(const SignalSink & data) = delete;
public:
    SignalSink(std::shared_ptr<easyar_SignalSink> cdata);
    virtual ~SignalSink();

    std::shared_ptr<easyar_SignalSink> get_cdata();
    static std::shared_ptr<SignalSink> from_cdata(std::shared_ptr<easyar_SignalSink> cdata);

    /// <summary>
    /// Input data.
    /// </summary>
    void handle();
};

/// <summary>
/// Signal output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class SignalSource
{
protected:
    std::shared_ptr<easyar_SignalSource> cdata_;
    void init_cdata(std::shared_ptr<easyar_SignalSource> cdata);
    SignalSource & operator=(const SignalSource & data) = delete;
public:
    SignalSource(std::shared_ptr<easyar_SignalSource> cdata);
    virtual ~SignalSource();

    std::shared_ptr<easyar_SignalSource> get_cdata();
    static std::shared_ptr<SignalSource> from_cdata(std::shared_ptr<easyar_SignalSource> cdata);

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(std::optional<std::function<void()>> handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(std::shared_ptr<SignalSink> sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Input frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class InputFrameSink
{
protected:
    std::shared_ptr<easyar_InputFrameSink> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameSink> cdata);
    InputFrameSink & operator=(const InputFrameSink & data) = delete;
public:
    InputFrameSink(std::shared_ptr<easyar_InputFrameSink> cdata);
    virtual ~InputFrameSink();

    std::shared_ptr<easyar_InputFrameSink> get_cdata();
    static std::shared_ptr<InputFrameSink> from_cdata(std::shared_ptr<easyar_InputFrameSink> cdata);

    /// <summary>
    /// Input data.
    /// </summary>
    void handle(std::shared_ptr<InputFrame> inputData);
};

/// <summary>
/// Input frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class InputFrameSource
{
protected:
    std::shared_ptr<easyar_InputFrameSource> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameSource> cdata);
    InputFrameSource & operator=(const InputFrameSource & data) = delete;
public:
    InputFrameSource(std::shared_ptr<easyar_InputFrameSource> cdata);
    virtual ~InputFrameSource();

    std::shared_ptr<easyar_InputFrameSource> get_cdata();
    static std::shared_ptr<InputFrameSource> from_cdata(std::shared_ptr<easyar_InputFrameSource> cdata);

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(std::optional<std::function<void(std::shared_ptr<InputFrame>)>> handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(std::shared_ptr<InputFrameSink> sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Output frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameSink
{
protected:
    std::shared_ptr<easyar_OutputFrameSink> cdata_;
    void init_cdata(std::shared_ptr<easyar_OutputFrameSink> cdata);
    OutputFrameSink & operator=(const OutputFrameSink & data) = delete;
public:
    OutputFrameSink(std::shared_ptr<easyar_OutputFrameSink> cdata);
    virtual ~OutputFrameSink();

    std::shared_ptr<easyar_OutputFrameSink> get_cdata();
    static std::shared_ptr<OutputFrameSink> from_cdata(std::shared_ptr<easyar_OutputFrameSink> cdata);

    /// <summary>
    /// Input data.
    /// </summary>
    void handle(std::shared_ptr<OutputFrame> inputData);
};

/// <summary>
/// Output frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameSource
{
protected:
    std::shared_ptr<easyar_OutputFrameSource> cdata_;
    void init_cdata(std::shared_ptr<easyar_OutputFrameSource> cdata);
    OutputFrameSource & operator=(const OutputFrameSource & data) = delete;
public:
    OutputFrameSource(std::shared_ptr<easyar_OutputFrameSource> cdata);
    virtual ~OutputFrameSource();

    std::shared_ptr<easyar_OutputFrameSource> get_cdata();
    static std::shared_ptr<OutputFrameSource> from_cdata(std::shared_ptr<easyar_OutputFrameSource> cdata);

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(std::optional<std::function<void(std::shared_ptr<OutputFrame>)>> handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(std::shared_ptr<OutputFrameSink> sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Feedback frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
class FeedbackFrameSink
{
protected:
    std::shared_ptr<easyar_FeedbackFrameSink> cdata_;
    void init_cdata(std::shared_ptr<easyar_FeedbackFrameSink> cdata);
    FeedbackFrameSink & operator=(const FeedbackFrameSink & data) = delete;
public:
    FeedbackFrameSink(std::shared_ptr<easyar_FeedbackFrameSink> cdata);
    virtual ~FeedbackFrameSink();

    std::shared_ptr<easyar_FeedbackFrameSink> get_cdata();
    static std::shared_ptr<FeedbackFrameSink> from_cdata(std::shared_ptr<easyar_FeedbackFrameSink> cdata);

    /// <summary>
    /// Input data.
    /// </summary>
    void handle(std::shared_ptr<FeedbackFrame> inputData);
};

/// <summary>
/// Feedback frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
class FeedbackFrameSource
{
protected:
    std::shared_ptr<easyar_FeedbackFrameSource> cdata_;
    void init_cdata(std::shared_ptr<easyar_FeedbackFrameSource> cdata);
    FeedbackFrameSource & operator=(const FeedbackFrameSource & data) = delete;
public:
    FeedbackFrameSource(std::shared_ptr<easyar_FeedbackFrameSource> cdata);
    virtual ~FeedbackFrameSource();

    std::shared_ptr<easyar_FeedbackFrameSource> get_cdata();
    static std::shared_ptr<FeedbackFrameSource> from_cdata(std::shared_ptr<easyar_FeedbackFrameSource> cdata);

    /// <summary>
    /// Sets data handler.
    /// </summary>
    void setHandler(std::optional<std::function<void(std::shared_ptr<FeedbackFrame>)>> handler);
    /// <summary>
    /// Connects to input port.
    /// </summary>
    void connect(std::shared_ptr<FeedbackFrameSink> sink);
    /// <summary>
    /// Disconnects.
    /// </summary>
    void disconnect();
};

/// <summary>
/// Input frame fork.
/// It is used to branch and transfer input frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
class InputFrameFork
{
protected:
    std::shared_ptr<easyar_InputFrameFork> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameFork> cdata);
    InputFrameFork & operator=(const InputFrameFork & data) = delete;
public:
    InputFrameFork(std::shared_ptr<easyar_InputFrameFork> cdata);
    virtual ~InputFrameFork();

    std::shared_ptr<easyar_InputFrameFork> get_cdata();
    static std::shared_ptr<InputFrameFork> from_cdata(std::shared_ptr<easyar_InputFrameFork> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<InputFrameSink> input();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> output(int index);
    /// <summary>
    /// Output count.
    /// </summary>
    int outputCount();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFrameFork> create(int outputCount);
};

/// <summary>
/// Output frame fork.
/// It is used to branch and transfer output frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameFork
{
protected:
    std::shared_ptr<easyar_OutputFrameFork> cdata_;
    void init_cdata(std::shared_ptr<easyar_OutputFrameFork> cdata);
    OutputFrameFork & operator=(const OutputFrameFork & data) = delete;
public:
    OutputFrameFork(std::shared_ptr<easyar_OutputFrameFork> cdata);
    virtual ~OutputFrameFork();

    std::shared_ptr<easyar_OutputFrameFork> get_cdata();
    static std::shared_ptr<OutputFrameFork> from_cdata(std::shared_ptr<easyar_OutputFrameFork> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<OutputFrameSink> input();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<OutputFrameSource> output(int index);
    /// <summary>
    /// Output count.
    /// </summary>
    int outputCount();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<OutputFrameFork> create(int outputCount);
};

/// <summary>
/// Output frame join.
/// It is used to aggregate output frame from multiple components in parallel.
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to the inputs shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
class OutputFrameJoin
{
protected:
    std::shared_ptr<easyar_OutputFrameJoin> cdata_;
    void init_cdata(std::shared_ptr<easyar_OutputFrameJoin> cdata);
    OutputFrameJoin & operator=(const OutputFrameJoin & data) = delete;
public:
    OutputFrameJoin(std::shared_ptr<easyar_OutputFrameJoin> cdata);
    virtual ~OutputFrameJoin();

    std::shared_ptr<easyar_OutputFrameJoin> get_cdata();
    static std::shared_ptr<OutputFrameJoin> from_cdata(std::shared_ptr<easyar_OutputFrameJoin> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<OutputFrameSink> input(int index);
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<OutputFrameSource> output();
    /// <summary>
    /// Input count.
    /// </summary>
    int inputCount();
    /// <summary>
    /// Creates an instance. The default joiner will be used, which takes input frame from the first input and first result or null of each input. The first result of every input will be placed at the corresponding input index of results of the final output frame.
    /// </summary>
    static std::shared_ptr<OutputFrameJoin> create(int inputCount);
    /// <summary>
    /// Creates an instance. A custom joiner is specified.
    /// </summary>
    static std::shared_ptr<OutputFrameJoin> createWithJoiner(int inputCount, std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)> joiner);
};

/// <summary>
/// Feedback frame fork.
/// It is used to branch and transfer feedback frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
class FeedbackFrameFork
{
protected:
    std::shared_ptr<easyar_FeedbackFrameFork> cdata_;
    void init_cdata(std::shared_ptr<easyar_FeedbackFrameFork> cdata);
    FeedbackFrameFork & operator=(const FeedbackFrameFork & data) = delete;
public:
    FeedbackFrameFork(std::shared_ptr<easyar_FeedbackFrameFork> cdata);
    virtual ~FeedbackFrameFork();

    std::shared_ptr<easyar_FeedbackFrameFork> get_cdata();
    static std::shared_ptr<FeedbackFrameFork> from_cdata(std::shared_ptr<easyar_FeedbackFrameFork> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<FeedbackFrameSink> input();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<FeedbackFrameSource> output(int index);
    /// <summary>
    /// Output count.
    /// </summary>
    int outputCount();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<FeedbackFrameFork> create(int outputCount);
};

/// <summary>
/// Input frame throttler.
/// There is a input frame input port and a input frame output port. It can be used to prevent incoming frames from entering algorithm components when they have not finished handling previous workload.
/// InputFrameThrottler occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to signalInput shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
class InputFrameThrottler
{
protected:
    std::shared_ptr<easyar_InputFrameThrottler> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameThrottler> cdata);
    InputFrameThrottler & operator=(const InputFrameThrottler & data) = delete;
public:
    InputFrameThrottler(std::shared_ptr<easyar_InputFrameThrottler> cdata);
    virtual ~InputFrameThrottler();

    std::shared_ptr<easyar_InputFrameThrottler> get_cdata();
    static std::shared_ptr<InputFrameThrottler> from_cdata(std::shared_ptr<easyar_InputFrameThrottler> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<InputFrameSink> input();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<InputFrameSource> output();
    /// <summary>
    /// Input port for clearance signal.
    /// </summary>
    std::shared_ptr<SignalSink> signalInput();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFrameThrottler> create();
};

/// <summary>
/// Output frame buffer.
/// There is an output frame input port and output frame fetching function. It can be used to convert output frame fetching from asynchronous pattern to synchronous polling pattern, which fits frame by frame rendering.
/// OutputFrameBuffer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class OutputFrameBuffer
{
protected:
    std::shared_ptr<easyar_OutputFrameBuffer> cdata_;
    void init_cdata(std::shared_ptr<easyar_OutputFrameBuffer> cdata);
    OutputFrameBuffer & operator=(const OutputFrameBuffer & data) = delete;
public:
    OutputFrameBuffer(std::shared_ptr<easyar_OutputFrameBuffer> cdata);
    virtual ~OutputFrameBuffer();

    std::shared_ptr<easyar_OutputFrameBuffer> get_cdata();
    static std::shared_ptr<OutputFrameBuffer> from_cdata(std::shared_ptr<easyar_OutputFrameBuffer> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<OutputFrameSink> input();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Output port for frame arrival. It can be connected to `InputFrameThrottler.signalInput`_ .
    /// </summary>
    std::shared_ptr<SignalSource> signalOutput();
    /// <summary>
    /// Fetches the most recent `OutputFrame`_ .
    /// </summary>
    std::optional<std::shared_ptr<OutputFrame>> peek();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<OutputFrameBuffer> create();
    /// <summary>
    /// Pauses output of `OutputFrame`_ . After execution, all results of `OutputFrameBuffer.peek`_ will be empty. `OutputFrameBuffer.signalOutput`_  is not affected.
    /// </summary>
    void pause();
    /// <summary>
    /// Resumes output of `OutputFrame`_ .
    /// </summary>
    void resume();
};

/// <summary>
/// Input frame to output frame adapter.
/// There is an input frame input port and an output frame output port. It can be used to wrap an input frame into an output frame, which can be used for rendering without an algorithm component. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class InputFrameToOutputFrameAdapter
{
protected:
    std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata);
    InputFrameToOutputFrameAdapter & operator=(const InputFrameToOutputFrameAdapter & data) = delete;
public:
    InputFrameToOutputFrameAdapter(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata);
    virtual ~InputFrameToOutputFrameAdapter();

    std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> get_cdata();
    static std::shared_ptr<InputFrameToOutputFrameAdapter> from_cdata(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<InputFrameSink> input();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<OutputFrameSource> output();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFrameToOutputFrameAdapter> create();
};

/// <summary>
/// Input frame to feedback frame adapter.
/// There is an input frame input port, a historic output frame input port and a feedback frame output port. It can be used to combine an input frame and a historic output frame into a feedback frame, which is required by algorithm components such as `ImageTracker`_ .
/// On every input of an input frame, a feedback frame is generated with a previously input historic feedback frame. If there is no previously input historic feedback frame, it is null in the feedback frame.
/// InputFrameToFeedbackFrameAdapter occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`__ .
/// All members of this class is thread-safe.
/// </summary>
class InputFrameToFeedbackFrameAdapter
{
protected:
    std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata);
    InputFrameToFeedbackFrameAdapter & operator=(const InputFrameToFeedbackFrameAdapter & data) = delete;
public:
    InputFrameToFeedbackFrameAdapter(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata);
    virtual ~InputFrameToFeedbackFrameAdapter();

    std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> get_cdata();
    static std::shared_ptr<InputFrameToFeedbackFrameAdapter> from_cdata(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata);

    /// <summary>
    /// Input port.
    /// </summary>
    std::shared_ptr<InputFrameSink> input();
    /// <summary>
    /// Camera buffers occupied in this component.
    /// </summary>
    int bufferRequirement();
    /// <summary>
    /// Side input port for historic output frame input.
    /// </summary>
    std::shared_ptr<OutputFrameSink> sideInput();
    /// <summary>
    /// Output port.
    /// </summary>
    std::shared_ptr<FeedbackFrameSource> output();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFrameToFeedbackFrameAdapter> create();
};

/// <summary>
/// Input frame.
/// It includes image, camera parameters, timestamp, camera transform matrix against world coordinate system, and tracking status,
/// among which, camera parameters, timestamp, camera transform matrix and tracking status are all optional, but specific algorithms may have special requirements on the input.
/// </summary>
class InputFrame
{
protected:
    std::shared_ptr<easyar_InputFrame> cdata_;
    void init_cdata(std::shared_ptr<easyar_InputFrame> cdata);
    InputFrame & operator=(const InputFrame & data) = delete;
public:
    InputFrame(std::shared_ptr<easyar_InputFrame> cdata);
    virtual ~InputFrame();

    std::shared_ptr<easyar_InputFrame> get_cdata();
    static std::shared_ptr<InputFrame> from_cdata(std::shared_ptr<easyar_InputFrame> cdata);

    /// <summary>
    /// Index, an automatic incremental value, which is different for every input frame.
    /// </summary>
    int index();
    /// <summary>
    /// Gets image.
    /// </summary>
    std::shared_ptr<Image> image();
    /// <summary>
    /// Checks if there are camera parameters.
    /// </summary>
    bool hasCameraParameters();
    /// <summary>
    /// Gets camera parameters.
    /// </summary>
    std::shared_ptr<CameraParameters> cameraParameters();
    /// <summary>
    /// Checks if there is temporal information (timestamp).
    /// </summary>
    bool hasTemporalInformation();
    /// <summary>
    /// Timestamp. In seconds.
    /// </summary>
    double timestamp();
    /// <summary>
    /// Checks if there is spatial information (cameraTransform and trackingStatus).
    /// </summary>
    bool hasSpatialInformation();
    /// <summary>
    /// Camera transform matrix against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL&#39;s column-major.
    /// </summary>
    Matrix44F cameraTransform();
    /// <summary>
    /// Gets device motion tracking status: `MotionTrackingStatus`_ .
    /// </summary>
    MotionTrackingStatus trackingStatus();
    /// <summary>
    /// Creates an instance.
    /// </summary>
    static std::shared_ptr<InputFrame> create(std::shared_ptr<Image> image, std::shared_ptr<CameraParameters> cameraParameters, double timestamp, Matrix44F cameraTransform, MotionTrackingStatus trackingStatus);
    /// <summary>
    /// Creates an instance with image, camera parameters, and timestamp.
    /// </summary>
    static std::shared_ptr<InputFrame> createWithImageAndCameraParametersAndTemporal(std::shared_ptr<Image> image, std::shared_ptr<CameraParameters> cameraParameters, double timestamp);
    /// <summary>
    /// Creates an instance with image and camera parameters.
    /// </summary>
    static std::shared_ptr<InputFrame> createWithImageAndCameraParameters(std::shared_ptr<Image> image, std::shared_ptr<CameraParameters> cameraParameters);
    /// <summary>
    /// Creates an instance with image.
    /// </summary>
    static std::shared_ptr<InputFrame> createWithImage(std::shared_ptr<Image> image);
};

/// <summary>
/// Output frame.
/// It includes input frame and results of synchronous components.
/// </summary>
class OutputFrame
{
protected:
    std::shared_ptr<easyar_OutputFrame> cdata_;
    void init_cdata(std::shared_ptr<easyar_OutputFrame> cdata);
    OutputFrame & operator=(const OutputFrame & data) = delete;
public:
    OutputFrame(std::shared_ptr<easyar_OutputFrame> cdata);
    virtual ~OutputFrame();

    std::shared_ptr<easyar_OutputFrame> get_cdata();
    static std::shared_ptr<OutputFrame> from_cdata(std::shared_ptr<easyar_OutputFrame> cdata);

    OutputFrame(std::shared_ptr<InputFrame> inputFrame, std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> results);
    /// <summary>
    /// Index, an automatic incremental value, which is different for every output frame.
    /// </summary>
    int index();
    /// <summary>
    /// Corresponding input frame.
    /// </summary>
    std::shared_ptr<InputFrame> inputFrame();
    /// <summary>
    /// Results of synchronous components.
    /// </summary>
    std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> results();
};

/// <summary>
/// Feedback frame.
/// It includes an input frame and a historic output frame for use in feedback synchronous components such as `ImageTracker`_ .
/// </summary>
class FeedbackFrame
{
protected:
    std::shared_ptr<easyar_FeedbackFrame> cdata_;
    void init_cdata(std::shared_ptr<easyar_FeedbackFrame> cdata);
    FeedbackFrame & operator=(const FeedbackFrame & data) = delete;
public:
    FeedbackFrame(std::shared_ptr<easyar_FeedbackFrame> cdata);
    virtual ~FeedbackFrame();

    std::shared_ptr<easyar_FeedbackFrame> get_cdata();
    static std::shared_ptr<FeedbackFrame> from_cdata(std::shared_ptr<easyar_FeedbackFrame> cdata);

    FeedbackFrame(std::shared_ptr<InputFrame> inputFrame, std::optional<std::shared_ptr<OutputFrame>> previousOutputFrame);
    /// <summary>
    /// Input frame.
    /// </summary>
    std::shared_ptr<InputFrame> inputFrame();
    /// <summary>
    /// Historic output frame.
    /// </summary>
    std::optional<std::shared_ptr<OutputFrame>> previousOutputFrame();
};

/// <summary>
/// TargetInstance is the tracked target by trackers.
/// An TargetInstance contains a raw `Target`_ that is tracked and current status and pose of the `Target`_ .
/// </summary>
class TargetInstance
{
protected:
    std::shared_ptr<easyar_TargetInstance> cdata_;
    void init_cdata(std::shared_ptr<easyar_TargetInstance> cdata);
    TargetInstance & operator=(const TargetInstance & data) = delete;
public:
    TargetInstance(std::shared_ptr<easyar_TargetInstance> cdata);
    virtual ~TargetInstance();

    std::shared_ptr<easyar_TargetInstance> get_cdata();
    static std::shared_ptr<TargetInstance> from_cdata(std::shared_ptr<easyar_TargetInstance> cdata);

    TargetInstance();
    /// <summary>
    /// Returns current status of the tracked target. Usually you can check if the status equals `TargetStatus.Tracked` to determine current status of the target.
    /// </summary>
    TargetStatus status();
    /// <summary>
    /// Gets the raw target. It will return the same `Target`_ you loaded into a tracker if it was previously loaded into the tracker.
    /// </summary>
    std::optional<std::shared_ptr<Target>> target();
    /// <summary>
    /// Returns current pose of the tracked target. Camera coordinate system and target coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL&#39;s column-major.
    /// </summary>
    Matrix44F pose();
};

/// <summary>
/// TextureId encapsulates a texture object in rendering API.
/// For OpenGL/OpenGLES, getInt and fromInt shall be used. For Direct3D, getPointer and fromPointer shall be used.
/// </summary>
class TextureId
{
protected:
    std::shared_ptr<easyar_TextureId> cdata_;
    void init_cdata(std::shared_ptr<easyar_TextureId> cdata);
    TextureId & operator=(const TextureId & data) = delete;
public:
    TextureId(std::shared_ptr<easyar_TextureId> cdata);
    virtual ~TextureId();

    std::shared_ptr<easyar_TextureId> get_cdata();
    static std::shared_ptr<TextureId> from_cdata(std::shared_ptr<easyar_TextureId> cdata);

    /// <summary>
    /// Gets ID of an OpenGL/OpenGLES texture object.
    /// </summary>
    int getInt();
    /// <summary>
    /// Gets pointer of a Direct3D texture object.
    /// </summary>
    void * getPointer();
    /// <summary>
    /// Creates from ID of an OpenGL/OpenGLES texture object.
    /// </summary>
    static std::shared_ptr<TextureId> fromInt(int _value);
    /// <summary>
    /// Creates from pointer of a Direct3D texture object.
    /// </summary>
    static std::shared_ptr<TextureId> fromPointer(void * ptr);
};

}

#endif

#ifndef _DECLARATION_ONLY_

#include "easyar/objecttarget.h"
#include "easyar/objecttracker.h"
#include "easyar/cloudrecognizer.h"
#include "easyar/buffer.h"
#include "easyar/bufferpool.h"
#include "easyar/cameraparameters.h"
#include "easyar/image.h"
#include "easyar/densespatialmap.h"
#include "easyar/scenemesh.h"
#include "easyar/arcorecamera.h"
#include "easyar/arkitcamera.h"
#include "easyar/camera.h"
#include "easyar/surfacetracker.h"
#include "easyar/motiontracker.h"
#include "easyar/framerecorder.h"
#include "easyar/callbackscheduler.h"
#include "easyar/jniutility.h"
#include "easyar/log.h"
#include "easyar/imagetarget.h"
#include "easyar/imagetracker.h"
#include "easyar/recorder.h"
#include "easyar/recorder_configuration.h"
#include "easyar/sparsespatialmap.h"
#include "easyar/sparsespatialmapmanager.h"
#include "easyar/engine.h"
#include "easyar/videoplayer.h"
#include "easyar/imagehelper.h"
#include "easyar/dataflow.h"
#include "easyar/frame.h"
#include "easyar/target.h"
#include "easyar/texture.h"

namespace easyar {

static inline std::shared_ptr<easyar_String> std_string_to_easyar_String(std::string s)
{
    easyar_String * ptr;
    easyar_String_from_utf8(s.data(), s.data() + s.size(), &ptr);
    return std::shared_ptr<easyar_String>(ptr, [](easyar_String * ptr) { easyar_String__dtor(ptr); });
}
static inline std::string std_string_from_easyar_String(std::shared_ptr<easyar_String> s)
{
    return std::string(easyar_String_begin(s.get()), easyar_String_end(s.get()));
}

static void FunctorOfVoid_func(void * _state, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoid_destroy(void * _state);
static inline easyar_FunctorOfVoid FunctorOfVoid_to_c(std::function<void()> f);

static inline std::shared_ptr<easyar_ListOfVec3F> std_vector_to_easyar_ListOfVec3F(std::vector<Vec3F> l);
static inline std::vector<Vec3F> std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F> pl);
static inline bool easyar_ListOfVec3F_check_external_cpp(const std::vector<Vec3F> & l);

static inline std::shared_ptr<easyar_ListOfTargetInstance> std_vector_to_easyar_ListOfTargetInstance(std::vector<std::shared_ptr<TargetInstance>> l);
static inline std::vector<std::shared_ptr<TargetInstance>> std_vector_from_easyar_ListOfTargetInstance(std::shared_ptr<easyar_ListOfTargetInstance> pl);
static inline bool easyar_ListOfTargetInstance_check_external_cpp(const std::vector<std::shared_ptr<TargetInstance>> & l);

static inline std::shared_ptr<easyar_ListOfOptionalOfFrameFilterResult> std_vector_to_easyar_ListOfOptionalOfFrameFilterResult(std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> l);
static inline std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> std_vector_from_easyar_ListOfOptionalOfFrameFilterResult(std::shared_ptr<easyar_ListOfOptionalOfFrameFilterResult> pl);
static inline bool easyar_ListOfOptionalOfFrameFilterResult_check_external_cpp(const std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> & l);

static void FunctorOfVoidFromOutputFrame_func(void * _state, easyar_OutputFrame *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromOutputFrame_destroy(void * _state);
static inline easyar_FunctorOfVoidFromOutputFrame FunctorOfVoidFromOutputFrame_to_c(std::function<void(std::shared_ptr<OutputFrame>)> f);

static void FunctorOfVoidFromTargetAndBool_func(void * _state, easyar_Target *, bool, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromTargetAndBool_destroy(void * _state);
static inline easyar_FunctorOfVoidFromTargetAndBool FunctorOfVoidFromTargetAndBool_to_c(std::function<void(std::shared_ptr<Target>, bool)> f);

static inline std::shared_ptr<easyar_ListOfTarget> std_vector_to_easyar_ListOfTarget(std::vector<std::shared_ptr<Target>> l);
static inline std::vector<std::shared_ptr<Target>> std_vector_from_easyar_ListOfTarget(std::shared_ptr<easyar_ListOfTarget> pl);
static inline bool easyar_ListOfTarget_check_external_cpp(const std::vector<std::shared_ptr<Target>> & l);

static inline std::shared_ptr<easyar_ListOfImage> std_vector_to_easyar_ListOfImage(std::vector<std::shared_ptr<Image>> l);
static inline std::vector<std::shared_ptr<Image>> std_vector_from_easyar_ListOfImage(std::shared_ptr<easyar_ListOfImage> pl);
static inline bool easyar_ListOfImage_check_external_cpp(const std::vector<std::shared_ptr<Image>> & l);

static void FunctorOfVoidFromCloudRecognizationResult_func(void * _state, easyar_CloudRecognizationResult *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromCloudRecognizationResult_destroy(void * _state);
static inline easyar_FunctorOfVoidFromCloudRecognizationResult FunctorOfVoidFromCloudRecognizationResult_to_c(std::function<void(std::shared_ptr<CloudRecognizationResult>)> f);

static inline std::shared_ptr<easyar_ListOfBlockInfo> std_vector_to_easyar_ListOfBlockInfo(std::vector<BlockInfo> l);
static inline std::vector<BlockInfo> std_vector_from_easyar_ListOfBlockInfo(std::shared_ptr<easyar_ListOfBlockInfo> pl);
static inline bool easyar_ListOfBlockInfo_check_external_cpp(const std::vector<BlockInfo> & l);

static void FunctorOfVoidFromInputFrame_func(void * _state, easyar_InputFrame *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromInputFrame_destroy(void * _state);
static inline easyar_FunctorOfVoidFromInputFrame FunctorOfVoidFromInputFrame_to_c(std::function<void(std::shared_ptr<InputFrame>)> f);

static void FunctorOfVoidFromCameraState_func(void * _state, easyar_CameraState, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromCameraState_destroy(void * _state);
static inline easyar_FunctorOfVoidFromCameraState FunctorOfVoidFromCameraState_to_c(std::function<void(CameraState)> f);

static void FunctorOfVoidFromPermissionStatusAndString_func(void * _state, easyar_PermissionStatus, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromPermissionStatusAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromPermissionStatusAndString FunctorOfVoidFromPermissionStatusAndString_to_c(std::function<void(PermissionStatus, std::string)> f);

static void FunctorOfVoidFromLogLevelAndString_func(void * _state, easyar_LogLevel, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromLogLevelAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromLogLevelAndString FunctorOfVoidFromLogLevelAndString_to_c(std::function<void(LogLevel, std::string)> f);

static void FunctorOfVoidFromRecordStatusAndString_func(void * _state, easyar_RecordStatus, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromRecordStatusAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromRecordStatusAndString FunctorOfVoidFromRecordStatusAndString_to_c(std::function<void(RecordStatus, std::string)> f);

static inline std::shared_ptr<easyar_ListOfPlaneData> std_vector_to_easyar_ListOfPlaneData(std::vector<std::shared_ptr<PlaneData>> l);
static inline std::vector<std::shared_ptr<PlaneData>> std_vector_from_easyar_ListOfPlaneData(std::shared_ptr<easyar_ListOfPlaneData> pl);
static inline bool easyar_ListOfPlaneData_check_external_cpp(const std::vector<std::shared_ptr<PlaneData>> & l);

static void FunctorOfVoidFromBool_func(void * _state, bool, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromBool_destroy(void * _state);
static inline easyar_FunctorOfVoidFromBool FunctorOfVoidFromBool_to_c(std::function<void(bool)> f);

static void FunctorOfVoidFromBoolAndStringAndString_func(void * _state, bool, easyar_String *, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromBoolAndStringAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromBoolAndStringAndString FunctorOfVoidFromBoolAndStringAndString_to_c(std::function<void(bool, std::string, std::string)> f);

static void FunctorOfVoidFromBoolAndString_func(void * _state, bool, easyar_String *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromBoolAndString_destroy(void * _state);
static inline easyar_FunctorOfVoidFromBoolAndString FunctorOfVoidFromBoolAndString_to_c(std::function<void(bool, std::string)> f);

static void FunctorOfVoidFromVideoStatus_func(void * _state, easyar_VideoStatus, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromVideoStatus_destroy(void * _state);
static inline easyar_FunctorOfVoidFromVideoStatus FunctorOfVoidFromVideoStatus_to_c(std::function<void(VideoStatus)> f);

static void FunctorOfVoidFromFeedbackFrame_func(void * _state, easyar_FeedbackFrame *, /* OUT */ easyar_String * * _exception);
static void FunctorOfVoidFromFeedbackFrame_destroy(void * _state);
static inline easyar_FunctorOfVoidFromFeedbackFrame FunctorOfVoidFromFeedbackFrame_to_c(std::function<void(std::shared_ptr<FeedbackFrame>)> f);

static void FunctorOfOutputFrameFromListOfOutputFrame_func(void * _state, easyar_ListOfOutputFrame *, /* OUT */ easyar_OutputFrame * *, /* OUT */ easyar_String * * _exception);
static void FunctorOfOutputFrameFromListOfOutputFrame_destroy(void * _state);
static inline easyar_FunctorOfOutputFrameFromListOfOutputFrame FunctorOfOutputFrameFromListOfOutputFrame_to_c(std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)> f);

static inline std::shared_ptr<easyar_ListOfOutputFrame> std_vector_to_easyar_ListOfOutputFrame(std::vector<std::shared_ptr<OutputFrame>> l);
static inline std::vector<std::shared_ptr<OutputFrame>> std_vector_from_easyar_ListOfOutputFrame(std::shared_ptr<easyar_ListOfOutputFrame> pl);
static inline bool easyar_ListOfOutputFrame_check_external_cpp(const std::vector<std::shared_ptr<OutputFrame>> & l);

_INLINE_SPECIFIER_ ObjectTargetParameters::ObjectTargetParameters(std::shared_ptr<easyar_ObjectTargetParameters> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ObjectTargetParameters::~ObjectTargetParameters()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ObjectTargetParameters> ObjectTargetParameters::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::init_cdata(std::shared_ptr<easyar_ObjectTargetParameters> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<ObjectTargetParameters> ObjectTargetParameters::from_cdata(std::shared_ptr<easyar_ObjectTargetParameters> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ObjectTargetParameters>(cdata);
}
_INLINE_SPECIFIER_ ObjectTargetParameters::ObjectTargetParameters()
    :
    cdata_(nullptr)
{
    easyar_ObjectTargetParameters * _return_value_;
    easyar_ObjectTargetParameters__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_ObjectTargetParameters>(_return_value_, [](easyar_ObjectTargetParameters * ptr) { easyar_ObjectTargetParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<BufferDictionary> ObjectTargetParameters::bufferDictionary()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_BufferDictionary * _return_value_;
    easyar_ObjectTargetParameters_bufferDictionary(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return BufferDictionary::from_cdata(std::shared_ptr<easyar_BufferDictionary>(_return_value_, [](easyar_BufferDictionary * ptr) { easyar_BufferDictionary__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::setBufferDictionary(std::shared_ptr<BufferDictionary> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: bufferDictionary"); }
    easyar_ObjectTargetParameters_setBufferDictionary(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ std::string ObjectTargetParameters::objPath()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTargetParameters_objPath(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::setObjPath(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTargetParameters_setObjPath(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ObjectTargetParameters::name()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTargetParameters_name(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::setName(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTargetParameters_setName(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ObjectTargetParameters::uid()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTargetParameters_uid(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::setUid(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTargetParameters_setUid(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ObjectTargetParameters::meta()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTargetParameters_meta(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::setMeta(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTargetParameters_setMeta(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ float ObjectTargetParameters::scale()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTargetParameters_scale(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ObjectTargetParameters::setScale(float arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTargetParameters_setScale(cdata_.get(), arg0);
}

_INLINE_SPECIFIER_ ObjectTarget::ObjectTarget(std::shared_ptr<easyar_ObjectTarget> cdata)
    :
    Target(std::shared_ptr<easyar_Target>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ObjectTarget::~ObjectTarget()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ObjectTarget> ObjectTarget::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ObjectTarget::init_cdata(std::shared_ptr<easyar_ObjectTarget> cdata)
{
    cdata_ = cdata;
    {
        easyar_Target * ptr = nullptr;
        easyar_castObjectTargetToTarget(cdata_.get(), &ptr);
        Target::init_cdata(std::shared_ptr<easyar_Target>(ptr, [](easyar_Target * ptr) { easyar_Target__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<ObjectTarget> ObjectTarget::from_cdata(std::shared_ptr<easyar_ObjectTarget> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ObjectTarget>(cdata);
}
_INLINE_SPECIFIER_ ObjectTarget::ObjectTarget()
    :
    Target(std::shared_ptr<easyar_Target>(nullptr)),
    cdata_(nullptr)
{
    easyar_ObjectTarget * _return_value_;
    easyar_ObjectTarget__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_ObjectTarget>(_return_value_, [](easyar_ObjectTarget * ptr) { easyar_ObjectTarget__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ObjectTarget>> ObjectTarget::createFromParameters(std::shared_ptr<ObjectTargetParameters> arg0)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: parameters"); }
    easyar_OptionalOfObjectTarget _return_value_;
    easyar_ObjectTarget_createFromParameters(arg0->get_cdata().get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ObjectTarget::from_cdata(std::shared_ptr<easyar_ObjectTarget>(_return_value_.value, [](easyar_ObjectTarget * ptr) { easyar_ObjectTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ObjectTarget>>{});
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ObjectTarget>> ObjectTarget::createFromObjectFile(std::string arg0, StorageType arg1, std::string arg2, std::string arg3, std::string arg4, float arg5)
{
    easyar_OptionalOfObjectTarget _return_value_;
    easyar_ObjectTarget_createFromObjectFile(std_string_to_easyar_String(arg0).get(), static_cast<easyar_StorageType>(arg1), std_string_to_easyar_String(arg2).get(), std_string_to_easyar_String(arg3).get(), std_string_to_easyar_String(arg4).get(), arg5, &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ObjectTarget::from_cdata(std::shared_ptr<easyar_ObjectTarget>(_return_value_.value, [](easyar_ObjectTarget * ptr) { easyar_ObjectTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ObjectTarget>>{});
}
_INLINE_SPECIFIER_ float ObjectTarget::scale()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTarget_scale(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::vector<Vec3F> ObjectTarget::boundingBox()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfVec3F * _return_value_;
    easyar_ObjectTarget_boundingBox(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F>(_return_value_, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ObjectTarget::setScale(float arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTarget_setScale(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ int ObjectTarget::runtimeID()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTarget_runtimeID(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::string ObjectTarget::uid()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTarget_uid(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::string ObjectTarget::name()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTarget_name(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTarget::setName(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTarget_setName(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ObjectTarget::meta()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ObjectTarget_meta(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTarget::setMeta(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTarget_setMeta(cdata_.get(), std_string_to_easyar_String(arg0).get());
}

_INLINE_SPECIFIER_ ObjectTrackerResult::ObjectTrackerResult(std::shared_ptr<easyar_ObjectTrackerResult> cdata)
    :
    TargetTrackerResult(std::shared_ptr<easyar_TargetTrackerResult>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ObjectTrackerResult::~ObjectTrackerResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ObjectTrackerResult> ObjectTrackerResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ObjectTrackerResult::init_cdata(std::shared_ptr<easyar_ObjectTrackerResult> cdata)
{
    cdata_ = cdata;
    {
        easyar_TargetTrackerResult * ptr = nullptr;
        easyar_castObjectTrackerResultToTargetTrackerResult(cdata_.get(), &ptr);
        TargetTrackerResult::init_cdata(std::shared_ptr<easyar_TargetTrackerResult>(ptr, [](easyar_TargetTrackerResult * ptr) { easyar_TargetTrackerResult__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<ObjectTrackerResult> ObjectTrackerResult::from_cdata(std::shared_ptr<easyar_ObjectTrackerResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ObjectTrackerResult>(cdata);
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<TargetInstance>> ObjectTrackerResult::targetInstances()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfTargetInstance * _return_value_;
    easyar_ObjectTrackerResult_targetInstances(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfTargetInstance(std::shared_ptr<easyar_ListOfTargetInstance>(_return_value_, [](easyar_ListOfTargetInstance * ptr) { easyar_ListOfTargetInstance__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ObjectTrackerResult::setTargetInstances(std::vector<std::shared_ptr<TargetInstance>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!easyar_ListOfTargetInstance_check_external_cpp(arg0)) { throw std::runtime_error("InvalidArgument: instances"); }
    easyar_ObjectTrackerResult_setTargetInstances(cdata_.get(), std_vector_to_easyar_ListOfTargetInstance(arg0).get());
}

_INLINE_SPECIFIER_ ObjectTracker::ObjectTracker(std::shared_ptr<easyar_ObjectTracker> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ObjectTracker::~ObjectTracker()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ObjectTracker> ObjectTracker::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ObjectTracker::init_cdata(std::shared_ptr<easyar_ObjectTracker> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<ObjectTracker> ObjectTracker::from_cdata(std::shared_ptr<easyar_ObjectTracker> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ObjectTracker>(cdata);
}
_INLINE_SPECIFIER_ bool ObjectTracker::isAvailable()
{
    auto _return_value_ = easyar_ObjectTracker_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSink> ObjectTracker::feedbackFrameSink()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_FeedbackFrameSink * _return_value_;
    easyar_ObjectTracker_feedbackFrameSink(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return FeedbackFrameSink::from_cdata(std::shared_ptr<easyar_FeedbackFrameSink>(_return_value_, [](easyar_FeedbackFrameSink * ptr) { easyar_FeedbackFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int ObjectTracker::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTracker_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> ObjectTracker::outputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_ObjectTracker_outputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<ObjectTracker> ObjectTracker::create()
{
    easyar_ObjectTracker * _return_value_;
    easyar_ObjectTracker_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return ObjectTracker::from_cdata(std::shared_ptr<easyar_ObjectTracker>(_return_value_, [](easyar_ObjectTracker * ptr) { easyar_ObjectTracker__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ObjectTracker::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTracker_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ObjectTracker::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTracker_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void ObjectTracker::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ObjectTracker_close(cdata_.get());
}
_INLINE_SPECIFIER_ void ObjectTracker::loadTarget(std::shared_ptr<Target> arg0, std::shared_ptr<CallbackScheduler> arg1, std::function<void(std::shared_ptr<Target>, bool)> arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: target"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: callback"); }
    easyar_ObjectTracker_loadTarget(cdata_.get(), arg0->get_cdata().get(), arg1->get_cdata().get(), FunctorOfVoidFromTargetAndBool_to_c(arg2));
}
_INLINE_SPECIFIER_ void ObjectTracker::unloadTarget(std::shared_ptr<Target> arg0, std::shared_ptr<CallbackScheduler> arg1, std::function<void(std::shared_ptr<Target>, bool)> arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: target"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: callback"); }
    easyar_ObjectTracker_unloadTarget(cdata_.get(), arg0->get_cdata().get(), arg1->get_cdata().get(), FunctorOfVoidFromTargetAndBool_to_c(arg2));
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<Target>> ObjectTracker::targets()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfTarget * _return_value_;
    easyar_ObjectTracker_targets(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfTarget(std::shared_ptr<easyar_ListOfTarget>(_return_value_, [](easyar_ListOfTarget * ptr) { easyar_ListOfTarget__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ObjectTracker::setSimultaneousNum(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTracker_setSimultaneousNum(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ int ObjectTracker::simultaneousNum()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ObjectTracker_simultaneousNum(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ CloudRecognizationResult::CloudRecognizationResult(std::shared_ptr<easyar_CloudRecognizationResult> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ CloudRecognizationResult::~CloudRecognizationResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_CloudRecognizationResult> CloudRecognizationResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void CloudRecognizationResult::init_cdata(std::shared_ptr<easyar_CloudRecognizationResult> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<CloudRecognizationResult> CloudRecognizationResult::from_cdata(std::shared_ptr<easyar_CloudRecognizationResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<CloudRecognizationResult>(cdata);
}
_INLINE_SPECIFIER_ CloudRecognizationStatus CloudRecognizationResult::getStatus()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CloudRecognizationResult_getStatus(cdata_.get());
    return static_cast<CloudRecognizationStatus>(_return_value_);
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ImageTarget>> CloudRecognizationResult::getTarget()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfImageTarget _return_value_;
    easyar_CloudRecognizationResult_getTarget(cdata_.get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ImageTarget::from_cdata(std::shared_ptr<easyar_ImageTarget>(_return_value_.value, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ImageTarget>>{});
}
_INLINE_SPECIFIER_ std::optional<std::string> CloudRecognizationResult::getUnknownErrorMessage()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfString _return_value_;
    easyar_CloudRecognizationResult_getUnknownErrorMessage(cdata_.get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_.value, [](easyar_String * ptr) { easyar_String__dtor(ptr); })) : std::optional<std::string>{});
}

_INLINE_SPECIFIER_ CloudRecognizer::CloudRecognizer(std::shared_ptr<easyar_CloudRecognizer> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ CloudRecognizer::~CloudRecognizer()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_CloudRecognizer> CloudRecognizer::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void CloudRecognizer::init_cdata(std::shared_ptr<easyar_CloudRecognizer> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<CloudRecognizer> CloudRecognizer::from_cdata(std::shared_ptr<easyar_CloudRecognizer> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<CloudRecognizer>(cdata);
}
_INLINE_SPECIFIER_ bool CloudRecognizer::isAvailable()
{
    auto _return_value_ = easyar_CloudRecognizer_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<CloudRecognizer> CloudRecognizer::create(std::string arg0, std::string arg1, std::string arg2, std::string arg3)
{
    easyar_CloudRecognizer * _return_value_;
    easyar_CloudRecognizer_create(std_string_to_easyar_String(arg0).get(), std_string_to_easyar_String(arg1).get(), std_string_to_easyar_String(arg2).get(), std_string_to_easyar_String(arg3).get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CloudRecognizer::from_cdata(std::shared_ptr<easyar_CloudRecognizer>(_return_value_, [](easyar_CloudRecognizer * ptr) { easyar_CloudRecognizer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<CloudRecognizer> CloudRecognizer::createByCloudSecret(std::string arg0, std::string arg1, std::string arg2)
{
    easyar_CloudRecognizer * _return_value_;
    easyar_CloudRecognizer_createByCloudSecret(std_string_to_easyar_String(arg0).get(), std_string_to_easyar_String(arg1).get(), std_string_to_easyar_String(arg2).get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CloudRecognizer::from_cdata(std::shared_ptr<easyar_CloudRecognizer>(_return_value_, [](easyar_CloudRecognizer * ptr) { easyar_CloudRecognizer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void CloudRecognizer::resolve(std::shared_ptr<InputFrame> arg0, std::shared_ptr<CallbackScheduler> arg1, std::function<void(std::shared_ptr<CloudRecognizationResult>)> arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: inputFrame"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: callback"); }
    easyar_CloudRecognizer_resolve(cdata_.get(), arg0->get_cdata().get(), arg1->get_cdata().get(), FunctorOfVoidFromCloudRecognizationResult_to_c(arg2));
}
_INLINE_SPECIFIER_ void CloudRecognizer::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CloudRecognizer_close(cdata_.get());
}

_INLINE_SPECIFIER_ Buffer::Buffer(std::shared_ptr<easyar_Buffer> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ Buffer::~Buffer()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_Buffer> Buffer::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void Buffer::init_cdata(std::shared_ptr<easyar_Buffer> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> Buffer::from_cdata(std::shared_ptr<easyar_Buffer> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<Buffer>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> Buffer::wrap(void * arg0, int arg1, std::function<void()> arg2)
{
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: deleter"); }
    easyar_Buffer * _return_value_;
    easyar_Buffer_wrap(arg0, arg1, FunctorOfVoid_to_c(arg2), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> Buffer::create(int arg0)
{
    easyar_Buffer * _return_value_;
    easyar_Buffer_create(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void * Buffer::data()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Buffer_data(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int Buffer::size()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Buffer_size(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void Buffer::memoryCopy(void * arg0, void * arg1, int arg2)
{
    easyar_Buffer_memoryCopy(arg0, arg1, arg2);
}
_INLINE_SPECIFIER_ bool Buffer::tryCopyFrom(void * arg0, int arg1, int arg2, int arg3)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Buffer_tryCopyFrom(cdata_.get(), arg0, arg1, arg2, arg3);
    return _return_value_;
}
_INLINE_SPECIFIER_ bool Buffer::tryCopyTo(int arg0, void * arg1, int arg2, int arg3)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Buffer_tryCopyTo(cdata_.get(), arg0, arg1, arg2, arg3);
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> Buffer::partition(int arg0, int arg1)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_Buffer_partition(cdata_.get(), arg0, arg1, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}

_INLINE_SPECIFIER_ BufferDictionary::BufferDictionary(std::shared_ptr<easyar_BufferDictionary> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ BufferDictionary::~BufferDictionary()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_BufferDictionary> BufferDictionary::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void BufferDictionary::init_cdata(std::shared_ptr<easyar_BufferDictionary> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<BufferDictionary> BufferDictionary::from_cdata(std::shared_ptr<easyar_BufferDictionary> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<BufferDictionary>(cdata);
}
_INLINE_SPECIFIER_ BufferDictionary::BufferDictionary()
    :
    cdata_(nullptr)
{
    easyar_BufferDictionary * _return_value_;
    easyar_BufferDictionary__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_BufferDictionary>(_return_value_, [](easyar_BufferDictionary * ptr) { easyar_BufferDictionary__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int BufferDictionary::count()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_BufferDictionary_count(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ bool BufferDictionary::contains(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_BufferDictionary_contains(cdata_.get(), std_string_to_easyar_String(arg0).get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<Buffer>> BufferDictionary::tryGet(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfBuffer _return_value_;
    easyar_BufferDictionary_tryGet(cdata_.get(), std_string_to_easyar_String(arg0).get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_.value, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); })) : std::optional<std::shared_ptr<Buffer>>{});
}
_INLINE_SPECIFIER_ void BufferDictionary::set(std::string arg0, std::shared_ptr<Buffer> arg1)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: buffer"); }
    easyar_BufferDictionary_set(cdata_.get(), std_string_to_easyar_String(arg0).get(), arg1->get_cdata().get());
}
_INLINE_SPECIFIER_ bool BufferDictionary::remove(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_BufferDictionary_remove(cdata_.get(), std_string_to_easyar_String(arg0).get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void BufferDictionary::clear()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_BufferDictionary_clear(cdata_.get());
}

_INLINE_SPECIFIER_ BufferPool::BufferPool(std::shared_ptr<easyar_BufferPool> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ BufferPool::~BufferPool()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_BufferPool> BufferPool::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void BufferPool::init_cdata(std::shared_ptr<easyar_BufferPool> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<BufferPool> BufferPool::from_cdata(std::shared_ptr<easyar_BufferPool> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<BufferPool>(cdata);
}
_INLINE_SPECIFIER_ BufferPool::BufferPool(int arg0, int arg1)
    :
    cdata_(nullptr)
{
    easyar_BufferPool * _return_value_;
    easyar_BufferPool__ctor(arg0, arg1, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_BufferPool>(_return_value_, [](easyar_BufferPool * ptr) { easyar_BufferPool__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int BufferPool::block_size()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_BufferPool_block_size(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int BufferPool::capacity()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_BufferPool_capacity(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int BufferPool::size()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_BufferPool_size(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<Buffer>> BufferPool::tryAcquire()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfBuffer _return_value_;
    easyar_BufferPool_tryAcquire(cdata_.get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_.value, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); })) : std::optional<std::shared_ptr<Buffer>>{});
}

_INLINE_SPECIFIER_ CameraParameters::CameraParameters(std::shared_ptr<easyar_CameraParameters> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ CameraParameters::~CameraParameters()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_CameraParameters> CameraParameters::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void CameraParameters::init_cdata(std::shared_ptr<easyar_CameraParameters> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraParameters> CameraParameters::from_cdata(std::shared_ptr<easyar_CameraParameters> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<CameraParameters>(cdata);
}
_INLINE_SPECIFIER_ CameraParameters::CameraParameters(Vec2I arg0, Vec2F arg1, Vec2F arg2, CameraDeviceType arg3, int arg4)
    :
    cdata_(nullptr)
{
    easyar_CameraParameters * _return_value_;
    easyar_CameraParameters__ctor(easyar_Vec2I{{arg0.data[0], arg0.data[1]}}, easyar_Vec2F{{arg1.data[0], arg1.data[1]}}, easyar_Vec2F{{arg2.data[0], arg2.data[1]}}, static_cast<easyar_CameraDeviceType>(arg3), arg4, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_CameraParameters>(_return_value_, [](easyar_CameraParameters * ptr) { easyar_CameraParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ Vec2I CameraParameters::size()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_size(cdata_.get());
    return Vec2I{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ Vec2F CameraParameters::focalLength()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_focalLength(cdata_.get());
    return Vec2F{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ Vec2F CameraParameters::principalPoint()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_principalPoint(cdata_.get());
    return Vec2F{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ CameraDeviceType CameraParameters::cameraDeviceType()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_cameraDeviceType(cdata_.get());
    return static_cast<CameraDeviceType>(_return_value_);
}
_INLINE_SPECIFIER_ int CameraParameters::cameraOrientation()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_cameraOrientation(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraParameters> CameraParameters::createWithDefaultIntrinsics(Vec2I arg0, CameraDeviceType arg1, int arg2)
{
    easyar_CameraParameters * _return_value_;
    easyar_CameraParameters_createWithDefaultIntrinsics(easyar_Vec2I{{arg0.data[0], arg0.data[1]}}, static_cast<easyar_CameraDeviceType>(arg1), arg2, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CameraParameters::from_cdata(std::shared_ptr<easyar_CameraParameters>(_return_value_, [](easyar_CameraParameters * ptr) { easyar_CameraParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraParameters> CameraParameters::getResized(Vec2I arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraParameters * _return_value_;
    easyar_CameraParameters_getResized(cdata_.get(), easyar_Vec2I{{arg0.data[0], arg0.data[1]}}, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CameraParameters::from_cdata(std::shared_ptr<easyar_CameraParameters>(_return_value_, [](easyar_CameraParameters * ptr) { easyar_CameraParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int CameraParameters::imageOrientation(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_imageOrientation(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraParameters::imageHorizontalFlip(bool arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_imageHorizontalFlip(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ Matrix44F CameraParameters::projection(float arg0, float arg1, float arg2, int arg3, bool arg4, bool arg5)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_projection(cdata_.get(), arg0, arg1, arg2, arg3, arg4, arg5);
    return Matrix44F{{{_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]}}};
}
_INLINE_SPECIFIER_ Matrix44F CameraParameters::imageProjection(float arg0, int arg1, bool arg2, bool arg3)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_imageProjection(cdata_.get(), arg0, arg1, arg2, arg3);
    return Matrix44F{{{_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]}}};
}
_INLINE_SPECIFIER_ Vec2F CameraParameters::screenCoordinatesFromImageCoordinates(float arg0, int arg1, bool arg2, bool arg3, Vec2F arg4)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_screenCoordinatesFromImageCoordinates(cdata_.get(), arg0, arg1, arg2, arg3, easyar_Vec2F{{arg4.data[0], arg4.data[1]}});
    return Vec2F{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ Vec2F CameraParameters::imageCoordinatesFromScreenCoordinates(float arg0, int arg1, bool arg2, bool arg3, Vec2F arg4)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraParameters_imageCoordinatesFromScreenCoordinates(cdata_.get(), arg0, arg1, arg2, arg3, easyar_Vec2F{{arg4.data[0], arg4.data[1]}});
    return Vec2F{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ bool CameraParameters::equalsTo(std::shared_ptr<CameraParameters> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: other"); }
    auto _return_value_ = easyar_CameraParameters_equalsTo(cdata_.get(), arg0->get_cdata().get());
    return _return_value_;
}

_INLINE_SPECIFIER_ Image::Image(std::shared_ptr<easyar_Image> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ Image::~Image()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_Image> Image::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void Image::init_cdata(std::shared_ptr<easyar_Image> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<Image> Image::from_cdata(std::shared_ptr<easyar_Image> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<Image>(cdata);
}
_INLINE_SPECIFIER_ Image::Image(std::shared_ptr<Buffer> arg0, PixelFormat arg1, int arg2, int arg3)
    :
    cdata_(nullptr)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: buffer"); }
    easyar_Image * _return_value_;
    easyar_Image__ctor(arg0->get_cdata().get(), static_cast<easyar_PixelFormat>(arg1), arg2, arg3, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_Image>(_return_value_, [](easyar_Image * ptr) { easyar_Image__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> Image::buffer()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_Image_buffer(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ PixelFormat Image::format()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Image_format(cdata_.get());
    return static_cast<PixelFormat>(_return_value_);
}
_INLINE_SPECIFIER_ int Image::width()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Image_width(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int Image::height()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Image_height(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ DenseSpatialMap::DenseSpatialMap(std::shared_ptr<easyar_DenseSpatialMap> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ DenseSpatialMap::~DenseSpatialMap()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_DenseSpatialMap> DenseSpatialMap::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void DenseSpatialMap::init_cdata(std::shared_ptr<easyar_DenseSpatialMap> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<DenseSpatialMap> DenseSpatialMap::from_cdata(std::shared_ptr<easyar_DenseSpatialMap> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<DenseSpatialMap>(cdata);
}
_INLINE_SPECIFIER_ bool DenseSpatialMap::isAvailable()
{
    auto _return_value_ = easyar_DenseSpatialMap_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> DenseSpatialMap::inputFrameSink()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_DenseSpatialMap_inputFrameSink(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int DenseSpatialMap::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_DenseSpatialMap_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<DenseSpatialMap> DenseSpatialMap::create()
{
    easyar_DenseSpatialMap * _return_value_;
    easyar_DenseSpatialMap_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return DenseSpatialMap::from_cdata(std::shared_ptr<easyar_DenseSpatialMap>(_return_value_, [](easyar_DenseSpatialMap * ptr) { easyar_DenseSpatialMap__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool DenseSpatialMap::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_DenseSpatialMap_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void DenseSpatialMap::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_DenseSpatialMap_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void DenseSpatialMap::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_DenseSpatialMap_close(cdata_.get());
}
_INLINE_SPECIFIER_ std::shared_ptr<SceneMesh> DenseSpatialMap::getMesh()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SceneMesh * _return_value_;
    easyar_DenseSpatialMap_getMesh(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SceneMesh::from_cdata(std::shared_ptr<easyar_SceneMesh>(_return_value_, [](easyar_SceneMesh * ptr) { easyar_SceneMesh__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool DenseSpatialMap::updateSceneMesh(bool arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_DenseSpatialMap_updateSceneMesh(cdata_.get(), arg0);
    return _return_value_;
}

_INLINE_SPECIFIER_ SceneMesh::SceneMesh(std::shared_ptr<easyar_SceneMesh> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SceneMesh::~SceneMesh()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SceneMesh> SceneMesh::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SceneMesh::init_cdata(std::shared_ptr<easyar_SceneMesh> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SceneMesh> SceneMesh::from_cdata(std::shared_ptr<easyar_SceneMesh> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SceneMesh>(cdata);
}
_INLINE_SPECIFIER_ int SceneMesh::getNumOfVertexAll()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SceneMesh_getNumOfVertexAll(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int SceneMesh::getNumOfIndexAll()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SceneMesh_getNumOfIndexAll(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SceneMesh::getVerticesAll()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SceneMesh_getVerticesAll(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SceneMesh::getNormalsAll()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SceneMesh_getNormalsAll(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SceneMesh::getIndicesAll()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SceneMesh_getIndicesAll(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int SceneMesh::getNumOfVertexIncremental()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SceneMesh_getNumOfVertexIncremental(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int SceneMesh::getNumOfIndexIncremental()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SceneMesh_getNumOfIndexIncremental(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SceneMesh::getVerticesIncremental()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SceneMesh_getVerticesIncremental(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SceneMesh::getNormalsIncremental()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SceneMesh_getNormalsIncremental(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SceneMesh::getIndicesIncremental()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SceneMesh_getIndicesIncremental(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<BlockInfo> SceneMesh::getBlocksInfoIncremental()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfBlockInfo * _return_value_;
    easyar_SceneMesh_getBlocksInfoIncremental(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfBlockInfo(std::shared_ptr<easyar_ListOfBlockInfo>(_return_value_, [](easyar_ListOfBlockInfo * ptr) { easyar_ListOfBlockInfo__dtor(ptr); }));
}
_INLINE_SPECIFIER_ float SceneMesh::getBlockDimensionInMeters()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SceneMesh_getBlockDimensionInMeters(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ ARCoreCameraDevice::ARCoreCameraDevice(std::shared_ptr<easyar_ARCoreCameraDevice> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ARCoreCameraDevice::~ARCoreCameraDevice()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ARCoreCameraDevice> ARCoreCameraDevice::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ARCoreCameraDevice::init_cdata(std::shared_ptr<easyar_ARCoreCameraDevice> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<ARCoreCameraDevice> ARCoreCameraDevice::from_cdata(std::shared_ptr<easyar_ARCoreCameraDevice> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ARCoreCameraDevice>(cdata);
}
_INLINE_SPECIFIER_ ARCoreCameraDevice::ARCoreCameraDevice()
    :
    cdata_(nullptr)
{
    easyar_ARCoreCameraDevice * _return_value_;
    easyar_ARCoreCameraDevice__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_ARCoreCameraDevice>(_return_value_, [](easyar_ARCoreCameraDevice * ptr) { easyar_ARCoreCameraDevice__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ARCoreCameraDevice::isAvailable()
{
    auto _return_value_ = easyar_ARCoreCameraDevice_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ int ARCoreCameraDevice::bufferCapacity()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ARCoreCameraDevice_bufferCapacity(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ARCoreCameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ARCoreCameraDevice_setBufferCapacity(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> ARCoreCameraDevice::inputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_ARCoreCameraDevice_inputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ARCoreCameraDevice::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ARCoreCameraDevice_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ARCoreCameraDevice::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ARCoreCameraDevice_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void ARCoreCameraDevice::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ARCoreCameraDevice_close(cdata_.get());
}

_INLINE_SPECIFIER_ ARKitCameraDevice::ARKitCameraDevice(std::shared_ptr<easyar_ARKitCameraDevice> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ARKitCameraDevice::~ARKitCameraDevice()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ARKitCameraDevice> ARKitCameraDevice::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ARKitCameraDevice::init_cdata(std::shared_ptr<easyar_ARKitCameraDevice> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<ARKitCameraDevice> ARKitCameraDevice::from_cdata(std::shared_ptr<easyar_ARKitCameraDevice> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ARKitCameraDevice>(cdata);
}
_INLINE_SPECIFIER_ ARKitCameraDevice::ARKitCameraDevice()
    :
    cdata_(nullptr)
{
    easyar_ARKitCameraDevice * _return_value_;
    easyar_ARKitCameraDevice__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_ARKitCameraDevice>(_return_value_, [](easyar_ARKitCameraDevice * ptr) { easyar_ARKitCameraDevice__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ARKitCameraDevice::isAvailable()
{
    auto _return_value_ = easyar_ARKitCameraDevice_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ int ARKitCameraDevice::bufferCapacity()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ARKitCameraDevice_bufferCapacity(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ARKitCameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ARKitCameraDevice_setBufferCapacity(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> ARKitCameraDevice::inputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_ARKitCameraDevice_inputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ARKitCameraDevice::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ARKitCameraDevice_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ARKitCameraDevice::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ARKitCameraDevice_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void ARKitCameraDevice::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ARKitCameraDevice_close(cdata_.get());
}

_INLINE_SPECIFIER_ CameraDevice::CameraDevice(std::shared_ptr<easyar_CameraDevice> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ CameraDevice::~CameraDevice()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_CameraDevice> CameraDevice::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void CameraDevice::init_cdata(std::shared_ptr<easyar_CameraDevice> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraDevice> CameraDevice::from_cdata(std::shared_ptr<easyar_CameraDevice> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<CameraDevice>(cdata);
}
_INLINE_SPECIFIER_ CameraDevice::CameraDevice()
    :
    cdata_(nullptr)
{
    easyar_CameraDevice * _return_value_;
    easyar_CameraDevice__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_CameraDevice>(_return_value_, [](easyar_CameraDevice * ptr) { easyar_CameraDevice__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool CameraDevice::isAvailable()
{
    auto _return_value_ = easyar_CameraDevice_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ AndroidCameraApiType CameraDevice::androidCameraApiType()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_androidCameraApiType(cdata_.get());
    return static_cast<AndroidCameraApiType>(_return_value_);
}
_INLINE_SPECIFIER_ void CameraDevice::setAndroidCameraApiType(AndroidCameraApiType arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraDevice_setAndroidCameraApiType(cdata_.get(), static_cast<easyar_AndroidCameraApiType>(arg0));
}
_INLINE_SPECIFIER_ int CameraDevice::bufferCapacity()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_bufferCapacity(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void CameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraDevice_setBufferCapacity(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> CameraDevice::inputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_CameraDevice_inputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void CameraDevice::setStateChangedCallback(std::shared_ptr<CallbackScheduler> arg0, std::optional<std::function<void(CameraState)>> arg1)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(!arg1.has_value() || (arg1.value() != nullptr))) { throw std::runtime_error("InvalidArgument: stateChangedCallback"); }
    easyar_CameraDevice_setStateChangedCallback(cdata_.get(), arg0->get_cdata().get(), (arg1.has_value() ? easyar_OptionalOfFunctorOfVoidFromCameraState{true, FunctorOfVoidFromCameraState_to_c(arg1.value())} : easyar_OptionalOfFunctorOfVoidFromCameraState{false, {}}));
}
_INLINE_SPECIFIER_ void CameraDevice::requestPermissions(std::shared_ptr<CallbackScheduler> arg0, std::optional<std::function<void(PermissionStatus, std::string)>> arg1)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(!arg1.has_value() || (arg1.value() != nullptr))) { throw std::runtime_error("InvalidArgument: permissionCallback"); }
    easyar_CameraDevice_requestPermissions(arg0->get_cdata().get(), (arg1.has_value() ? easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString{true, FunctorOfVoidFromPermissionStatusAndString_to_c(arg1.value())} : easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString{false, {}}));
}
_INLINE_SPECIFIER_ int CameraDevice::cameraCount()
{
    auto _return_value_ = easyar_CameraDevice_cameraCount();
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::openWithIndex(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_openWithIndex(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::openWithSpecificType(CameraDeviceType arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_openWithSpecificType(cdata_.get(), static_cast<easyar_CameraDeviceType>(arg0));
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::openWithPreferredType(CameraDeviceType arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_openWithPreferredType(cdata_.get(), static_cast<easyar_CameraDeviceType>(arg0));
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void CameraDevice::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraDevice_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void CameraDevice::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraDevice_close(cdata_.get());
}
_INLINE_SPECIFIER_ int CameraDevice::index()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_index(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ CameraDeviceType CameraDevice::type()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_type(cdata_.get());
    return static_cast<CameraDeviceType>(_return_value_);
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraParameters> CameraDevice::cameraParameters()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraParameters * _return_value_;
    easyar_CameraDevice_cameraParameters(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CameraParameters::from_cdata(std::shared_ptr<easyar_CameraParameters>(_return_value_, [](easyar_CameraParameters * ptr) { easyar_CameraParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void CameraDevice::setCameraParameters(std::shared_ptr<CameraParameters> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: cameraParameters"); }
    easyar_CameraDevice_setCameraParameters(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ Vec2I CameraDevice::size()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_size(cdata_.get());
    return Vec2I{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ int CameraDevice::supportedSizeCount()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_supportedSizeCount(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ Vec2I CameraDevice::supportedSize(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_supportedSize(cdata_.get(), arg0);
    return Vec2I{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ bool CameraDevice::setSize(Vec2I arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_setSize(cdata_.get(), easyar_Vec2I{{arg0.data[0], arg0.data[1]}});
    return _return_value_;
}
_INLINE_SPECIFIER_ int CameraDevice::supportedFrameRateRangeCount()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_supportedFrameRateRangeCount(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ float CameraDevice::supportedFrameRateRangeLower(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_supportedFrameRateRangeLower(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ float CameraDevice::supportedFrameRateRangeUpper(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_supportedFrameRateRangeUpper(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ int CameraDevice::frameRateRange()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_frameRateRange(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::setFrameRateRange(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_setFrameRateRange(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::setFlashTorchMode(bool arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_setFlashTorchMode(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::setFocusMode(CameraDeviceFocusMode arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_setFocusMode(cdata_.get(), static_cast<easyar_CameraDeviceFocusMode>(arg0));
    return _return_value_;
}
_INLINE_SPECIFIER_ bool CameraDevice::autoFocus()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_CameraDevice_autoFocus(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ AndroidCameraApiType CameraDeviceSelector::getAndroidCameraApiType(CameraDevicePreference arg0)
{
    auto _return_value_ = easyar_CameraDeviceSelector_getAndroidCameraApiType(static_cast<easyar_CameraDevicePreference>(arg0));
    return static_cast<AndroidCameraApiType>(_return_value_);
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraDevice> CameraDeviceSelector::createCameraDevice(CameraDevicePreference arg0)
{
    easyar_CameraDevice * _return_value_;
    easyar_CameraDeviceSelector_createCameraDevice(static_cast<easyar_CameraDevicePreference>(arg0), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CameraDevice::from_cdata(std::shared_ptr<easyar_CameraDevice>(_return_value_, [](easyar_CameraDevice * ptr) { easyar_CameraDevice__dtor(ptr); }));
}

_INLINE_SPECIFIER_ SurfaceTrackerResult::SurfaceTrackerResult(std::shared_ptr<easyar_SurfaceTrackerResult> cdata)
    :
    FrameFilterResult(std::shared_ptr<easyar_FrameFilterResult>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SurfaceTrackerResult::~SurfaceTrackerResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SurfaceTrackerResult> SurfaceTrackerResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SurfaceTrackerResult::init_cdata(std::shared_ptr<easyar_SurfaceTrackerResult> cdata)
{
    cdata_ = cdata;
    {
        easyar_FrameFilterResult * ptr = nullptr;
        easyar_castSurfaceTrackerResultToFrameFilterResult(cdata_.get(), &ptr);
        FrameFilterResult::init_cdata(std::shared_ptr<easyar_FrameFilterResult>(ptr, [](easyar_FrameFilterResult * ptr) { easyar_FrameFilterResult__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<SurfaceTrackerResult> SurfaceTrackerResult::from_cdata(std::shared_ptr<easyar_SurfaceTrackerResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SurfaceTrackerResult>(cdata);
}
_INLINE_SPECIFIER_ Matrix44F SurfaceTrackerResult::transform()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SurfaceTrackerResult_transform(cdata_.get());
    return Matrix44F{{{_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]}}};
}

_INLINE_SPECIFIER_ SurfaceTracker::SurfaceTracker(std::shared_ptr<easyar_SurfaceTracker> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SurfaceTracker::~SurfaceTracker()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SurfaceTracker> SurfaceTracker::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SurfaceTracker::init_cdata(std::shared_ptr<easyar_SurfaceTracker> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SurfaceTracker> SurfaceTracker::from_cdata(std::shared_ptr<easyar_SurfaceTracker> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SurfaceTracker>(cdata);
}
_INLINE_SPECIFIER_ bool SurfaceTracker::isAvailable()
{
    auto _return_value_ = easyar_SurfaceTracker_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> SurfaceTracker::inputFrameSink()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_SurfaceTracker_inputFrameSink(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int SurfaceTracker::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SurfaceTracker_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> SurfaceTracker::outputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_SurfaceTracker_outputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<SurfaceTracker> SurfaceTracker::create()
{
    easyar_SurfaceTracker * _return_value_;
    easyar_SurfaceTracker_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SurfaceTracker::from_cdata(std::shared_ptr<easyar_SurfaceTracker>(_return_value_, [](easyar_SurfaceTracker * ptr) { easyar_SurfaceTracker__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool SurfaceTracker::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SurfaceTracker_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void SurfaceTracker::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SurfaceTracker_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void SurfaceTracker::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SurfaceTracker_close(cdata_.get());
}
_INLINE_SPECIFIER_ void SurfaceTracker::alignTargetToCameraImagePoint(Vec2F arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SurfaceTracker_alignTargetToCameraImagePoint(cdata_.get(), easyar_Vec2F{{arg0.data[0], arg0.data[1]}});
}

_INLINE_SPECIFIER_ MotionTrackerCameraDevice::MotionTrackerCameraDevice(std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ MotionTrackerCameraDevice::~MotionTrackerCameraDevice()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_MotionTrackerCameraDevice> MotionTrackerCameraDevice::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void MotionTrackerCameraDevice::init_cdata(std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<MotionTrackerCameraDevice> MotionTrackerCameraDevice::from_cdata(std::shared_ptr<easyar_MotionTrackerCameraDevice> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<MotionTrackerCameraDevice>(cdata);
}
_INLINE_SPECIFIER_ MotionTrackerCameraDevice::MotionTrackerCameraDevice()
    :
    cdata_(nullptr)
{
    easyar_MotionTrackerCameraDevice * _return_value_;
    easyar_MotionTrackerCameraDevice__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_MotionTrackerCameraDevice>(_return_value_, [](easyar_MotionTrackerCameraDevice * ptr) { easyar_MotionTrackerCameraDevice__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool MotionTrackerCameraDevice::isAvailable()
{
    auto _return_value_ = easyar_MotionTrackerCameraDevice_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ void MotionTrackerCameraDevice::setBufferCapacity(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_MotionTrackerCameraDevice_setBufferCapacity(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ int MotionTrackerCameraDevice::bufferCapacity()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_MotionTrackerCameraDevice_bufferCapacity(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> MotionTrackerCameraDevice::inputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_MotionTrackerCameraDevice_inputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool MotionTrackerCameraDevice::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_MotionTrackerCameraDevice_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void MotionTrackerCameraDevice::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_MotionTrackerCameraDevice_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void MotionTrackerCameraDevice::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_MotionTrackerCameraDevice_close(cdata_.get());
}
_INLINE_SPECIFIER_ std::vector<Vec3F> MotionTrackerCameraDevice::hitTestAgainstPointCloud(Vec2F arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfVec3F * _return_value_;
    easyar_MotionTrackerCameraDevice_hitTestAgainstPointCloud(cdata_.get(), easyar_Vec2F{{arg0.data[0], arg0.data[1]}}, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F>(_return_value_, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<Vec3F> MotionTrackerCameraDevice::hitTestAgainstHorizontalPlane(Vec2F arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfVec3F * _return_value_;
    easyar_MotionTrackerCameraDevice_hitTestAgainstHorizontalPlane(cdata_.get(), easyar_Vec2F{{arg0.data[0], arg0.data[1]}}, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F>(_return_value_, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<Vec3F> MotionTrackerCameraDevice::getLocalPointsCloud()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfVec3F * _return_value_;
    easyar_MotionTrackerCameraDevice_getLocalPointsCloud(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F>(_return_value_, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); }));
}

_INLINE_SPECIFIER_ InputFrameRecorder::InputFrameRecorder(std::shared_ptr<easyar_InputFrameRecorder> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameRecorder::~InputFrameRecorder()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameRecorder> InputFrameRecorder::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameRecorder::init_cdata(std::shared_ptr<easyar_InputFrameRecorder> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameRecorder> InputFrameRecorder::from_cdata(std::shared_ptr<easyar_InputFrameRecorder> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameRecorder>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> InputFrameRecorder::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_InputFrameRecorder_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int InputFrameRecorder::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrameRecorder_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> InputFrameRecorder::output()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_InputFrameRecorder_output(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameRecorder> InputFrameRecorder::create()
{
    easyar_InputFrameRecorder * _return_value_;
    easyar_InputFrameRecorder_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameRecorder::from_cdata(std::shared_ptr<easyar_InputFrameRecorder>(_return_value_, [](easyar_InputFrameRecorder * ptr) { easyar_InputFrameRecorder__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool InputFrameRecorder::start(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrameRecorder_start(cdata_.get(), std_string_to_easyar_String(arg0).get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void InputFrameRecorder::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameRecorder_stop(cdata_.get());
}

_INLINE_SPECIFIER_ InputFramePlayer::InputFramePlayer(std::shared_ptr<easyar_InputFramePlayer> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFramePlayer::~InputFramePlayer()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFramePlayer> InputFramePlayer::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFramePlayer::init_cdata(std::shared_ptr<easyar_InputFramePlayer> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFramePlayer> InputFramePlayer::from_cdata(std::shared_ptr<easyar_InputFramePlayer> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFramePlayer>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> InputFramePlayer::output()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_InputFramePlayer_output(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFramePlayer> InputFramePlayer::create()
{
    easyar_InputFramePlayer * _return_value_;
    easyar_InputFramePlayer_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFramePlayer::from_cdata(std::shared_ptr<easyar_InputFramePlayer>(_return_value_, [](easyar_InputFramePlayer * ptr) { easyar_InputFramePlayer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool InputFramePlayer::start(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFramePlayer_start(cdata_.get(), std_string_to_easyar_String(arg0).get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void InputFramePlayer::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFramePlayer_stop(cdata_.get());
}

_INLINE_SPECIFIER_ CallbackScheduler::CallbackScheduler(std::shared_ptr<easyar_CallbackScheduler> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ CallbackScheduler::~CallbackScheduler()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_CallbackScheduler> CallbackScheduler::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void CallbackScheduler::init_cdata(std::shared_ptr<easyar_CallbackScheduler> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<CallbackScheduler> CallbackScheduler::from_cdata(std::shared_ptr<easyar_CallbackScheduler> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    std::string typeName = easyar_CallbackScheduler__typeName(cdata.get());
    if (typeName == "DelayedCallbackScheduler") {
        easyar_DelayedCallbackScheduler * st_cdata;
        easyar_tryCastCallbackSchedulerToDelayedCallbackScheduler(cdata.get(), &st_cdata);
        return std::static_pointer_cast<CallbackScheduler>(std::make_shared<DelayedCallbackScheduler>(std::shared_ptr<easyar_DelayedCallbackScheduler>(st_cdata, [](easyar_DelayedCallbackScheduler * ptr) { easyar_DelayedCallbackScheduler__dtor(ptr); })));
    }
    if (typeName == "ImmediateCallbackScheduler") {
        easyar_ImmediateCallbackScheduler * st_cdata;
        easyar_tryCastCallbackSchedulerToImmediateCallbackScheduler(cdata.get(), &st_cdata);
        return std::static_pointer_cast<CallbackScheduler>(std::make_shared<ImmediateCallbackScheduler>(std::shared_ptr<easyar_ImmediateCallbackScheduler>(st_cdata, [](easyar_ImmediateCallbackScheduler * ptr) { easyar_ImmediateCallbackScheduler__dtor(ptr); })));
    }
    return std::make_shared<CallbackScheduler>(cdata);
}

_INLINE_SPECIFIER_ DelayedCallbackScheduler::DelayedCallbackScheduler(std::shared_ptr<easyar_DelayedCallbackScheduler> cdata)
    :
    CallbackScheduler(std::shared_ptr<easyar_CallbackScheduler>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ DelayedCallbackScheduler::~DelayedCallbackScheduler()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_DelayedCallbackScheduler> DelayedCallbackScheduler::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void DelayedCallbackScheduler::init_cdata(std::shared_ptr<easyar_DelayedCallbackScheduler> cdata)
{
    cdata_ = cdata;
    {
        easyar_CallbackScheduler * ptr = nullptr;
        easyar_castDelayedCallbackSchedulerToCallbackScheduler(cdata_.get(), &ptr);
        CallbackScheduler::init_cdata(std::shared_ptr<easyar_CallbackScheduler>(ptr, [](easyar_CallbackScheduler * ptr) { easyar_CallbackScheduler__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<DelayedCallbackScheduler> DelayedCallbackScheduler::from_cdata(std::shared_ptr<easyar_DelayedCallbackScheduler> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<DelayedCallbackScheduler>(cdata);
}
_INLINE_SPECIFIER_ DelayedCallbackScheduler::DelayedCallbackScheduler()
    :
    CallbackScheduler(std::shared_ptr<easyar_CallbackScheduler>(nullptr)),
    cdata_(nullptr)
{
    easyar_DelayedCallbackScheduler * _return_value_;
    easyar_DelayedCallbackScheduler__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_DelayedCallbackScheduler>(_return_value_, [](easyar_DelayedCallbackScheduler * ptr) { easyar_DelayedCallbackScheduler__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool DelayedCallbackScheduler::runOne()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_DelayedCallbackScheduler_runOne(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ ImmediateCallbackScheduler::ImmediateCallbackScheduler(std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata)
    :
    CallbackScheduler(std::shared_ptr<easyar_CallbackScheduler>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ImmediateCallbackScheduler::~ImmediateCallbackScheduler()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ImmediateCallbackScheduler> ImmediateCallbackScheduler::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ImmediateCallbackScheduler::init_cdata(std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata)
{
    cdata_ = cdata;
    {
        easyar_CallbackScheduler * ptr = nullptr;
        easyar_castImmediateCallbackSchedulerToCallbackScheduler(cdata_.get(), &ptr);
        CallbackScheduler::init_cdata(std::shared_ptr<easyar_CallbackScheduler>(ptr, [](easyar_CallbackScheduler * ptr) { easyar_CallbackScheduler__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<ImmediateCallbackScheduler> ImmediateCallbackScheduler::from_cdata(std::shared_ptr<easyar_ImmediateCallbackScheduler> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ImmediateCallbackScheduler>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<ImmediateCallbackScheduler> ImmediateCallbackScheduler::getDefault()
{
    easyar_ImmediateCallbackScheduler * _return_value_;
    easyar_ImmediateCallbackScheduler_getDefault(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return ImmediateCallbackScheduler::from_cdata(std::shared_ptr<easyar_ImmediateCallbackScheduler>(_return_value_, [](easyar_ImmediateCallbackScheduler * ptr) { easyar_ImmediateCallbackScheduler__dtor(ptr); }));
}

_INLINE_SPECIFIER_ std::shared_ptr<Buffer> JniUtility::wrapByteArray(void * arg0, bool arg1, std::function<void()> arg2)
{
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: deleter"); }
    easyar_Buffer * _return_value_;
    easyar_JniUtility_wrapByteArray(arg0, arg1, FunctorOfVoid_to_c(arg2), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> JniUtility::wrapBuffer(void * arg0, std::function<void()> arg1)
{
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: deleter"); }
    easyar_Buffer * _return_value_;
    easyar_JniUtility_wrapBuffer(arg0, FunctorOfVoid_to_c(arg1), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void * JniUtility::getDirectBufferAddress(void * arg0)
{
    auto _return_value_ = easyar_JniUtility_getDirectBufferAddress(arg0);
    return _return_value_;
}

_INLINE_SPECIFIER_ void Log::setLogFunc(std::function<void(LogLevel, std::string)> arg0)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: func"); }
    easyar_Log_setLogFunc(FunctorOfVoidFromLogLevelAndString_to_c(arg0));
}
_INLINE_SPECIFIER_ void Log::resetLogFunc()
{
    easyar_Log_resetLogFunc();
}

_INLINE_SPECIFIER_ ImageTargetParameters::ImageTargetParameters(std::shared_ptr<easyar_ImageTargetParameters> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ImageTargetParameters::~ImageTargetParameters()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ImageTargetParameters> ImageTargetParameters::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ImageTargetParameters::init_cdata(std::shared_ptr<easyar_ImageTargetParameters> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<ImageTargetParameters> ImageTargetParameters::from_cdata(std::shared_ptr<easyar_ImageTargetParameters> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ImageTargetParameters>(cdata);
}
_INLINE_SPECIFIER_ ImageTargetParameters::ImageTargetParameters()
    :
    cdata_(nullptr)
{
    easyar_ImageTargetParameters * _return_value_;
    easyar_ImageTargetParameters__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_ImageTargetParameters>(_return_value_, [](easyar_ImageTargetParameters * ptr) { easyar_ImageTargetParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<Image> ImageTargetParameters::image()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Image * _return_value_;
    easyar_ImageTargetParameters_image(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Image::from_cdata(std::shared_ptr<easyar_Image>(_return_value_, [](easyar_Image * ptr) { easyar_Image__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTargetParameters::setImage(std::shared_ptr<Image> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: image"); }
    easyar_ImageTargetParameters_setImage(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ std::string ImageTargetParameters::name()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ImageTargetParameters_name(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTargetParameters::setName(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTargetParameters_setName(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ImageTargetParameters::uid()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ImageTargetParameters_uid(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTargetParameters::setUid(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTargetParameters_setUid(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ImageTargetParameters::meta()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ImageTargetParameters_meta(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTargetParameters::setMeta(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTargetParameters_setMeta(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ float ImageTargetParameters::scale()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTargetParameters_scale(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ImageTargetParameters::setScale(float arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTargetParameters_setScale(cdata_.get(), arg0);
}

_INLINE_SPECIFIER_ ImageTarget::ImageTarget(std::shared_ptr<easyar_ImageTarget> cdata)
    :
    Target(std::shared_ptr<easyar_Target>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ImageTarget::~ImageTarget()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ImageTarget> ImageTarget::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ImageTarget::init_cdata(std::shared_ptr<easyar_ImageTarget> cdata)
{
    cdata_ = cdata;
    {
        easyar_Target * ptr = nullptr;
        easyar_castImageTargetToTarget(cdata_.get(), &ptr);
        Target::init_cdata(std::shared_ptr<easyar_Target>(ptr, [](easyar_Target * ptr) { easyar_Target__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<ImageTarget> ImageTarget::from_cdata(std::shared_ptr<easyar_ImageTarget> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ImageTarget>(cdata);
}
_INLINE_SPECIFIER_ ImageTarget::ImageTarget()
    :
    Target(std::shared_ptr<easyar_Target>(nullptr)),
    cdata_(nullptr)
{
    easyar_ImageTarget * _return_value_;
    easyar_ImageTarget__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_ImageTarget>(_return_value_, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ImageTarget>> ImageTarget::createFromParameters(std::shared_ptr<ImageTargetParameters> arg0)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: parameters"); }
    easyar_OptionalOfImageTarget _return_value_;
    easyar_ImageTarget_createFromParameters(arg0->get_cdata().get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ImageTarget::from_cdata(std::shared_ptr<easyar_ImageTarget>(_return_value_.value, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ImageTarget>>{});
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ImageTarget>> ImageTarget::createFromTargetFile(std::string arg0, StorageType arg1)
{
    easyar_OptionalOfImageTarget _return_value_;
    easyar_ImageTarget_createFromTargetFile(std_string_to_easyar_String(arg0).get(), static_cast<easyar_StorageType>(arg1), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ImageTarget::from_cdata(std::shared_ptr<easyar_ImageTarget>(_return_value_.value, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ImageTarget>>{});
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ImageTarget>> ImageTarget::createFromTargetData(std::shared_ptr<Buffer> arg0)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: buffer"); }
    easyar_OptionalOfImageTarget _return_value_;
    easyar_ImageTarget_createFromTargetData(arg0->get_cdata().get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ImageTarget::from_cdata(std::shared_ptr<easyar_ImageTarget>(_return_value_.value, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ImageTarget>>{});
}
_INLINE_SPECIFIER_ bool ImageTarget::save(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTarget_save(cdata_.get(), std_string_to_easyar_String(arg0).get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<ImageTarget>> ImageTarget::createFromImageFile(std::string arg0, StorageType arg1, std::string arg2, std::string arg3, std::string arg4, float arg5)
{
    easyar_OptionalOfImageTarget _return_value_;
    easyar_ImageTarget_createFromImageFile(std_string_to_easyar_String(arg0).get(), static_cast<easyar_StorageType>(arg1), std_string_to_easyar_String(arg2).get(), std_string_to_easyar_String(arg3).get(), std_string_to_easyar_String(arg4).get(), arg5, &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? ImageTarget::from_cdata(std::shared_ptr<easyar_ImageTarget>(_return_value_.value, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); })) : std::optional<std::shared_ptr<ImageTarget>>{});
}
_INLINE_SPECIFIER_ float ImageTarget::scale()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTarget_scale(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ float ImageTarget::aspectRatio()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTarget_aspectRatio(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ bool ImageTarget::setScale(float arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTarget_setScale(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<Image>> ImageTarget::images()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfImage * _return_value_;
    easyar_ImageTarget_images(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfImage(std::shared_ptr<easyar_ListOfImage>(_return_value_, [](easyar_ListOfImage * ptr) { easyar_ListOfImage__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int ImageTarget::runtimeID()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTarget_runtimeID(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::string ImageTarget::uid()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ImageTarget_uid(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::string ImageTarget::name()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ImageTarget_name(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTarget::setName(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTarget_setName(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string ImageTarget::meta()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_ImageTarget_meta(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTarget::setMeta(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTarget_setMeta(cdata_.get(), std_string_to_easyar_String(arg0).get());
}

_INLINE_SPECIFIER_ ImageTrackerResult::ImageTrackerResult(std::shared_ptr<easyar_ImageTrackerResult> cdata)
    :
    TargetTrackerResult(std::shared_ptr<easyar_TargetTrackerResult>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ImageTrackerResult::~ImageTrackerResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ImageTrackerResult> ImageTrackerResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ImageTrackerResult::init_cdata(std::shared_ptr<easyar_ImageTrackerResult> cdata)
{
    cdata_ = cdata;
    {
        easyar_TargetTrackerResult * ptr = nullptr;
        easyar_castImageTrackerResultToTargetTrackerResult(cdata_.get(), &ptr);
        TargetTrackerResult::init_cdata(std::shared_ptr<easyar_TargetTrackerResult>(ptr, [](easyar_TargetTrackerResult * ptr) { easyar_TargetTrackerResult__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<ImageTrackerResult> ImageTrackerResult::from_cdata(std::shared_ptr<easyar_ImageTrackerResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ImageTrackerResult>(cdata);
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<TargetInstance>> ImageTrackerResult::targetInstances()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfTargetInstance * _return_value_;
    easyar_ImageTrackerResult_targetInstances(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfTargetInstance(std::shared_ptr<easyar_ListOfTargetInstance>(_return_value_, [](easyar_ListOfTargetInstance * ptr) { easyar_ListOfTargetInstance__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void ImageTrackerResult::setTargetInstances(std::vector<std::shared_ptr<TargetInstance>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!easyar_ListOfTargetInstance_check_external_cpp(arg0)) { throw std::runtime_error("InvalidArgument: instances"); }
    easyar_ImageTrackerResult_setTargetInstances(cdata_.get(), std_vector_to_easyar_ListOfTargetInstance(arg0).get());
}

_INLINE_SPECIFIER_ ImageTracker::ImageTracker(std::shared_ptr<easyar_ImageTracker> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ ImageTracker::~ImageTracker()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_ImageTracker> ImageTracker::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void ImageTracker::init_cdata(std::shared_ptr<easyar_ImageTracker> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<ImageTracker> ImageTracker::from_cdata(std::shared_ptr<easyar_ImageTracker> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<ImageTracker>(cdata);
}
_INLINE_SPECIFIER_ bool ImageTracker::isAvailable()
{
    auto _return_value_ = easyar_ImageTracker_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSink> ImageTracker::feedbackFrameSink()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_FeedbackFrameSink * _return_value_;
    easyar_ImageTracker_feedbackFrameSink(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return FeedbackFrameSink::from_cdata(std::shared_ptr<easyar_FeedbackFrameSink>(_return_value_, [](easyar_FeedbackFrameSink * ptr) { easyar_FeedbackFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int ImageTracker::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTracker_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> ImageTracker::outputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_ImageTracker_outputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<ImageTracker> ImageTracker::create()
{
    easyar_ImageTracker * _return_value_;
    easyar_ImageTracker_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return ImageTracker::from_cdata(std::shared_ptr<easyar_ImageTracker>(_return_value_, [](easyar_ImageTracker * ptr) { easyar_ImageTracker__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<ImageTracker> ImageTracker::createWithMode(ImageTrackerMode arg0)
{
    easyar_ImageTracker * _return_value_;
    easyar_ImageTracker_createWithMode(static_cast<easyar_ImageTrackerMode>(arg0), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return ImageTracker::from_cdata(std::shared_ptr<easyar_ImageTracker>(_return_value_, [](easyar_ImageTracker * ptr) { easyar_ImageTracker__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ImageTracker::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTracker_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void ImageTracker::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTracker_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void ImageTracker::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ImageTracker_close(cdata_.get());
}
_INLINE_SPECIFIER_ void ImageTracker::loadTarget(std::shared_ptr<Target> arg0, std::shared_ptr<CallbackScheduler> arg1, std::function<void(std::shared_ptr<Target>, bool)> arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: target"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: callback"); }
    easyar_ImageTracker_loadTarget(cdata_.get(), arg0->get_cdata().get(), arg1->get_cdata().get(), FunctorOfVoidFromTargetAndBool_to_c(arg2));
}
_INLINE_SPECIFIER_ void ImageTracker::unloadTarget(std::shared_ptr<Target> arg0, std::shared_ptr<CallbackScheduler> arg1, std::function<void(std::shared_ptr<Target>, bool)> arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: target"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: callback"); }
    easyar_ImageTracker_unloadTarget(cdata_.get(), arg0->get_cdata().get(), arg1->get_cdata().get(), FunctorOfVoidFromTargetAndBool_to_c(arg2));
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<Target>> ImageTracker::targets()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfTarget * _return_value_;
    easyar_ImageTracker_targets(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfTarget(std::shared_ptr<easyar_ListOfTarget>(_return_value_, [](easyar_ListOfTarget * ptr) { easyar_ListOfTarget__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool ImageTracker::setSimultaneousNum(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTracker_setSimultaneousNum(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ int ImageTracker::simultaneousNum()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_ImageTracker_simultaneousNum(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ Recorder::Recorder(std::shared_ptr<easyar_Recorder> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ Recorder::~Recorder()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_Recorder> Recorder::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void Recorder::init_cdata(std::shared_ptr<easyar_Recorder> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<Recorder> Recorder::from_cdata(std::shared_ptr<easyar_Recorder> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<Recorder>(cdata);
}
_INLINE_SPECIFIER_ bool Recorder::isAvailable()
{
    auto _return_value_ = easyar_Recorder_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ void Recorder::requestPermissions(std::shared_ptr<CallbackScheduler> arg0, std::optional<std::function<void(PermissionStatus, std::string)>> arg1)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(!arg1.has_value() || (arg1.value() != nullptr))) { throw std::runtime_error("InvalidArgument: permissionCallback"); }
    easyar_Recorder_requestPermissions(arg0->get_cdata().get(), (arg1.has_value() ? easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString{true, FunctorOfVoidFromPermissionStatusAndString_to_c(arg1.value())} : easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString{false, {}}));
}
_INLINE_SPECIFIER_ std::shared_ptr<Recorder> Recorder::create(std::shared_ptr<RecorderConfiguration> arg0, std::shared_ptr<CallbackScheduler> arg1, std::optional<std::function<void(RecordStatus, std::string)>> arg2)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: config"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(!arg2.has_value() || (arg2.value() != nullptr))) { throw std::runtime_error("InvalidArgument: statusCallback"); }
    easyar_Recorder * _return_value_;
    easyar_Recorder_create(arg0->get_cdata().get(), arg1->get_cdata().get(), (arg2.has_value() ? easyar_OptionalOfFunctorOfVoidFromRecordStatusAndString{true, FunctorOfVoidFromRecordStatusAndString_to_c(arg2.value())} : easyar_OptionalOfFunctorOfVoidFromRecordStatusAndString{false, {}}), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Recorder::from_cdata(std::shared_ptr<easyar_Recorder>(_return_value_, [](easyar_Recorder * ptr) { easyar_Recorder__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void Recorder::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Recorder_start(cdata_.get());
}
_INLINE_SPECIFIER_ void Recorder::updateFrame(std::shared_ptr<TextureId> arg0, int arg1, int arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: texture"); }
    easyar_Recorder_updateFrame(cdata_.get(), arg0->get_cdata().get(), arg1, arg2);
}
_INLINE_SPECIFIER_ bool Recorder::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Recorder_stop(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ RecorderConfiguration::RecorderConfiguration(std::shared_ptr<easyar_RecorderConfiguration> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ RecorderConfiguration::~RecorderConfiguration()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_RecorderConfiguration> RecorderConfiguration::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void RecorderConfiguration::init_cdata(std::shared_ptr<easyar_RecorderConfiguration> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<RecorderConfiguration> RecorderConfiguration::from_cdata(std::shared_ptr<easyar_RecorderConfiguration> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<RecorderConfiguration>(cdata);
}
_INLINE_SPECIFIER_ RecorderConfiguration::RecorderConfiguration()
    :
    cdata_(nullptr)
{
    easyar_RecorderConfiguration * _return_value_;
    easyar_RecorderConfiguration__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_RecorderConfiguration>(_return_value_, [](easyar_RecorderConfiguration * ptr) { easyar_RecorderConfiguration__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setOutputFile(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setOutputFile(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ bool RecorderConfiguration::setProfile(RecordProfile arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_RecorderConfiguration_setProfile(cdata_.get(), static_cast<easyar_RecordProfile>(arg0));
    return _return_value_;
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setVideoSize(RecordVideoSize arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setVideoSize(cdata_.get(), static_cast<easyar_RecordVideoSize>(arg0));
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setVideoBitrate(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setVideoBitrate(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setChannelCount(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setChannelCount(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setAudioSampleRate(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setAudioSampleRate(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setAudioBitrate(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setAudioBitrate(cdata_.get(), arg0);
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setVideoOrientation(RecordVideoOrientation arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setVideoOrientation(cdata_.get(), static_cast<easyar_RecordVideoOrientation>(arg0));
}
_INLINE_SPECIFIER_ void RecorderConfiguration::setZoomMode(RecordZoomMode arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_RecorderConfiguration_setZoomMode(cdata_.get(), static_cast<easyar_RecordZoomMode>(arg0));
}

_INLINE_SPECIFIER_ SparseSpatialMapResult::SparseSpatialMapResult(std::shared_ptr<easyar_SparseSpatialMapResult> cdata)
    :
    FrameFilterResult(std::shared_ptr<easyar_FrameFilterResult>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SparseSpatialMapResult::~SparseSpatialMapResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SparseSpatialMapResult> SparseSpatialMapResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SparseSpatialMapResult::init_cdata(std::shared_ptr<easyar_SparseSpatialMapResult> cdata)
{
    cdata_ = cdata;
    {
        easyar_FrameFilterResult * ptr = nullptr;
        easyar_castSparseSpatialMapResultToFrameFilterResult(cdata_.get(), &ptr);
        FrameFilterResult::init_cdata(std::shared_ptr<easyar_FrameFilterResult>(ptr, [](easyar_FrameFilterResult * ptr) { easyar_FrameFilterResult__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMapResult> SparseSpatialMapResult::from_cdata(std::shared_ptr<easyar_SparseSpatialMapResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SparseSpatialMapResult>(cdata);
}
_INLINE_SPECIFIER_ MotionTrackingStatus SparseSpatialMapResult::getMotionTrackingStatus()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMapResult_getMotionTrackingStatus(cdata_.get());
    return static_cast<MotionTrackingStatus>(_return_value_);
}
_INLINE_SPECIFIER_ std::optional<Matrix44F> SparseSpatialMapResult::getVioPose()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMapResult_getVioPose(cdata_.get());
    return (_return_value_.has_value ? Matrix44F{{{_return_value_.value.data[0], _return_value_.value.data[1], _return_value_.value.data[2], _return_value_.value.data[3], _return_value_.value.data[4], _return_value_.value.data[5], _return_value_.value.data[6], _return_value_.value.data[7], _return_value_.value.data[8], _return_value_.value.data[9], _return_value_.value.data[10], _return_value_.value.data[11], _return_value_.value.data[12], _return_value_.value.data[13], _return_value_.value.data[14], _return_value_.value.data[15]}}} : std::optional<Matrix44F>{});
}
_INLINE_SPECIFIER_ std::optional<Matrix44F> SparseSpatialMapResult::getMapPose()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMapResult_getMapPose(cdata_.get());
    return (_return_value_.has_value ? Matrix44F{{{_return_value_.value.data[0], _return_value_.value.data[1], _return_value_.value.data[2], _return_value_.value.data[3], _return_value_.value.data[4], _return_value_.value.data[5], _return_value_.value.data[6], _return_value_.value.data[7], _return_value_.value.data[8], _return_value_.value.data[9], _return_value_.value.data[10], _return_value_.value.data[11], _return_value_.value.data[12], _return_value_.value.data[13], _return_value_.value.data[14], _return_value_.value.data[15]}}} : std::optional<Matrix44F>{});
}
_INLINE_SPECIFIER_ bool SparseSpatialMapResult::getLocalizationStatus()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMapResult_getLocalizationStatus(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::string SparseSpatialMapResult::getLocalizationMapID()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_SparseSpatialMapResult_getLocalizationMapID(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}

_INLINE_SPECIFIER_ PlaneData::PlaneData(std::shared_ptr<easyar_PlaneData> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ PlaneData::~PlaneData()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_PlaneData> PlaneData::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void PlaneData::init_cdata(std::shared_ptr<easyar_PlaneData> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<PlaneData> PlaneData::from_cdata(std::shared_ptr<easyar_PlaneData> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<PlaneData>(cdata);
}
_INLINE_SPECIFIER_ PlaneData::PlaneData()
    :
    cdata_(nullptr)
{
    easyar_PlaneData * _return_value_;
    easyar_PlaneData__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_PlaneData>(_return_value_, [](easyar_PlaneData * ptr) { easyar_PlaneData__dtor(ptr); }));
}
_INLINE_SPECIFIER_ PlaneType PlaneData::getType()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_PlaneData_getType(cdata_.get());
    return static_cast<PlaneType>(_return_value_);
}
_INLINE_SPECIFIER_ Matrix44F PlaneData::getPose()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_PlaneData_getPose(cdata_.get());
    return Matrix44F{{{_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]}}};
}
_INLINE_SPECIFIER_ float PlaneData::getExtentX()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_PlaneData_getExtentX(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ float PlaneData::getExtentZ()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_PlaneData_getExtentZ(cdata_.get());
    return _return_value_;
}

_INLINE_SPECIFIER_ SparseSpatialMapConfig::SparseSpatialMapConfig(std::shared_ptr<easyar_SparseSpatialMapConfig> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SparseSpatialMapConfig::~SparseSpatialMapConfig()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SparseSpatialMapConfig> SparseSpatialMapConfig::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SparseSpatialMapConfig::init_cdata(std::shared_ptr<easyar_SparseSpatialMapConfig> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMapConfig> SparseSpatialMapConfig::from_cdata(std::shared_ptr<easyar_SparseSpatialMapConfig> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SparseSpatialMapConfig>(cdata);
}
_INLINE_SPECIFIER_ SparseSpatialMapConfig::SparseSpatialMapConfig()
    :
    cdata_(nullptr)
{
    easyar_SparseSpatialMapConfig * _return_value_;
    easyar_SparseSpatialMapConfig__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_SparseSpatialMapConfig>(_return_value_, [](easyar_SparseSpatialMapConfig * ptr) { easyar_SparseSpatialMapConfig__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void SparseSpatialMapConfig::setLocalizationMode(LocalizationMode arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SparseSpatialMapConfig_setLocalizationMode(cdata_.get(), static_cast<easyar_LocalizationMode>(arg0));
}
_INLINE_SPECIFIER_ LocalizationMode SparseSpatialMapConfig::getLocalizationMode()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMapConfig_getLocalizationMode(cdata_.get());
    return static_cast<LocalizationMode>(_return_value_);
}

_INLINE_SPECIFIER_ SparseSpatialMap::SparseSpatialMap(std::shared_ptr<easyar_SparseSpatialMap> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SparseSpatialMap::~SparseSpatialMap()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SparseSpatialMap> SparseSpatialMap::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SparseSpatialMap::init_cdata(std::shared_ptr<easyar_SparseSpatialMap> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMap> SparseSpatialMap::from_cdata(std::shared_ptr<easyar_SparseSpatialMap> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SparseSpatialMap>(cdata);
}
_INLINE_SPECIFIER_ bool SparseSpatialMap::isAvailable()
{
    auto _return_value_ = easyar_SparseSpatialMap_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> SparseSpatialMap::inputFrameSink()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_SparseSpatialMap_inputFrameSink(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int SparseSpatialMap::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMap_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> SparseSpatialMap::outputFrameSource()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_SparseSpatialMap_outputFrameSource(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMap> SparseSpatialMap::create()
{
    easyar_SparseSpatialMap * _return_value_;
    easyar_SparseSpatialMap_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SparseSpatialMap::from_cdata(std::shared_ptr<easyar_SparseSpatialMap>(_return_value_, [](easyar_SparseSpatialMap * ptr) { easyar_SparseSpatialMap__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool SparseSpatialMap::start()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMap_start(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void SparseSpatialMap::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SparseSpatialMap_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void SparseSpatialMap::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SparseSpatialMap_close(cdata_.get());
}
_INLINE_SPECIFIER_ std::shared_ptr<Buffer> SparseSpatialMap::getPointCloudBuffer()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Buffer * _return_value_;
    easyar_SparseSpatialMap_getPointCloudBuffer(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Buffer::from_cdata(std::shared_ptr<easyar_Buffer>(_return_value_, [](easyar_Buffer * ptr) { easyar_Buffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<PlaneData>> SparseSpatialMap::getMapPlanes()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfPlaneData * _return_value_;
    easyar_SparseSpatialMap_getMapPlanes(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfPlaneData(std::shared_ptr<easyar_ListOfPlaneData>(_return_value_, [](easyar_ListOfPlaneData * ptr) { easyar_ListOfPlaneData__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<Vec3F> SparseSpatialMap::hitTestAgainstPointCloud(Vec2F arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfVec3F * _return_value_;
    easyar_SparseSpatialMap_hitTestAgainstPointCloud(cdata_.get(), easyar_Vec2F{{arg0.data[0], arg0.data[1]}}, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F>(_return_value_, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<Vec3F> SparseSpatialMap::hitTestAgainstPlanes(Vec2F arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfVec3F * _return_value_;
    easyar_SparseSpatialMap_hitTestAgainstPlanes(cdata_.get(), easyar_Vec2F{{arg0.data[0], arg0.data[1]}}, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F>(_return_value_, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::string SparseSpatialMap::getMapVersion()
{
    easyar_String * _return_value_;
    easyar_SparseSpatialMap_getMapVersion(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void SparseSpatialMap::unloadMap(std::string arg0, std::shared_ptr<CallbackScheduler> arg1, std::optional<std::function<void(bool)>> arg2)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(!arg2.has_value() || (arg2.value() != nullptr))) { throw std::runtime_error("InvalidArgument: resultCallBack"); }
    easyar_SparseSpatialMap_unloadMap(cdata_.get(), std_string_to_easyar_String(arg0).get(), arg1->get_cdata().get(), (arg2.has_value() ? easyar_OptionalOfFunctorOfVoidFromBool{true, FunctorOfVoidFromBool_to_c(arg2.value())} : easyar_OptionalOfFunctorOfVoidFromBool{false, {}}));
}
_INLINE_SPECIFIER_ void SparseSpatialMap::setConfig(std::shared_ptr<SparseSpatialMapConfig> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: config"); }
    easyar_SparseSpatialMap_setConfig(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMapConfig> SparseSpatialMap::getConfig()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SparseSpatialMapConfig * _return_value_;
    easyar_SparseSpatialMap_getConfig(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SparseSpatialMapConfig::from_cdata(std::shared_ptr<easyar_SparseSpatialMapConfig>(_return_value_, [](easyar_SparseSpatialMapConfig * ptr) { easyar_SparseSpatialMapConfig__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool SparseSpatialMap::startLocalization()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_SparseSpatialMap_startLocalization(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void SparseSpatialMap::stopLocalization()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SparseSpatialMap_stopLocalization(cdata_.get());
}

_INLINE_SPECIFIER_ SparseSpatialMapManager::SparseSpatialMapManager(std::shared_ptr<easyar_SparseSpatialMapManager> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SparseSpatialMapManager::~SparseSpatialMapManager()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SparseSpatialMapManager> SparseSpatialMapManager::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SparseSpatialMapManager::init_cdata(std::shared_ptr<easyar_SparseSpatialMapManager> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMapManager> SparseSpatialMapManager::from_cdata(std::shared_ptr<easyar_SparseSpatialMapManager> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SparseSpatialMapManager>(cdata);
}
_INLINE_SPECIFIER_ bool SparseSpatialMapManager::isAvailable()
{
    auto _return_value_ = easyar_SparseSpatialMapManager_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<SparseSpatialMapManager> SparseSpatialMapManager::create()
{
    easyar_SparseSpatialMapManager * _return_value_;
    easyar_SparseSpatialMapManager_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SparseSpatialMapManager::from_cdata(std::shared_ptr<easyar_SparseSpatialMapManager>(_return_value_, [](easyar_SparseSpatialMapManager * ptr) { easyar_SparseSpatialMapManager__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void SparseSpatialMapManager::host(std::shared_ptr<SparseSpatialMap> arg0, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::optional<std::shared_ptr<Image>> arg5, std::shared_ptr<CallbackScheduler> arg6, std::function<void(bool, std::string, std::string)> arg7)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: mapBuilder"); }
    if (!(!arg5.has_value() || (arg5.value() != nullptr))) { throw std::runtime_error("InvalidArgument: preview"); }
    if (!(arg6 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg7 != nullptr)) { throw std::runtime_error("InvalidArgument: onCompleted"); }
    easyar_SparseSpatialMapManager_host(cdata_.get(), arg0->get_cdata().get(), std_string_to_easyar_String(arg1).get(), std_string_to_easyar_String(arg2).get(), std_string_to_easyar_String(arg3).get(), std_string_to_easyar_String(arg4).get(), (arg5.has_value() ? easyar_OptionalOfImage{true, arg5.value()->get_cdata().get()} : easyar_OptionalOfImage{false, {}}), arg6->get_cdata().get(), FunctorOfVoidFromBoolAndStringAndString_to_c(arg7));
}
_INLINE_SPECIFIER_ void SparseSpatialMapManager::load(std::shared_ptr<SparseSpatialMap> arg0, std::string arg1, std::string arg2, std::string arg3, std::string arg4, std::shared_ptr<CallbackScheduler> arg5, std::function<void(bool, std::string)> arg6)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: mapTracker"); }
    if (!(arg5 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(arg6 != nullptr)) { throw std::runtime_error("InvalidArgument: onCompleted"); }
    easyar_SparseSpatialMapManager_load(cdata_.get(), arg0->get_cdata().get(), std_string_to_easyar_String(arg1).get(), std_string_to_easyar_String(arg2).get(), std_string_to_easyar_String(arg3).get(), std_string_to_easyar_String(arg4).get(), arg5->get_cdata().get(), FunctorOfVoidFromBoolAndString_to_c(arg6));
}
_INLINE_SPECIFIER_ void SparseSpatialMapManager::clear()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SparseSpatialMapManager_clear(cdata_.get());
}

_INLINE_SPECIFIER_ int Engine::schemaHash()
{
    auto _return_value_ = easyar_Engine_schemaHash();
    return _return_value_;
}
_INLINE_SPECIFIER_ bool Engine::initialize(std::string arg0)
{
    if (easyar_Engine_schemaHash() != 2058628672) {
        throw std::runtime_error("SchemaHashNotMatched");
    }
    auto _return_value_ = easyar_Engine_initialize(std_string_to_easyar_String(arg0).get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void Engine::onPause()
{
    easyar_Engine_onPause();
}
_INLINE_SPECIFIER_ void Engine::onResume()
{
    easyar_Engine_onResume();
}
_INLINE_SPECIFIER_ std::string Engine::errorMessage()
{
    easyar_String * _return_value_;
    easyar_Engine_errorMessage(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::string Engine::versionString()
{
    easyar_String * _return_value_;
    easyar_Engine_versionString(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::string Engine::name()
{
    easyar_String * _return_value_;
    easyar_Engine_name(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}

_INLINE_SPECIFIER_ VideoPlayer::VideoPlayer(std::shared_ptr<easyar_VideoPlayer> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ VideoPlayer::~VideoPlayer()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_VideoPlayer> VideoPlayer::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void VideoPlayer::init_cdata(std::shared_ptr<easyar_VideoPlayer> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<VideoPlayer> VideoPlayer::from_cdata(std::shared_ptr<easyar_VideoPlayer> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<VideoPlayer>(cdata);
}
_INLINE_SPECIFIER_ VideoPlayer::VideoPlayer()
    :
    cdata_(nullptr)
{
    easyar_VideoPlayer * _return_value_;
    easyar_VideoPlayer__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_VideoPlayer>(_return_value_, [](easyar_VideoPlayer * ptr) { easyar_VideoPlayer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool VideoPlayer::isAvailable()
{
    auto _return_value_ = easyar_VideoPlayer_isAvailable();
    return _return_value_;
}
_INLINE_SPECIFIER_ void VideoPlayer::setVideoType(VideoType arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_VideoPlayer_setVideoType(cdata_.get(), static_cast<easyar_VideoType>(arg0));
}
_INLINE_SPECIFIER_ void VideoPlayer::setRenderTexture(std::shared_ptr<TextureId> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: texture"); }
    easyar_VideoPlayer_setRenderTexture(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ void VideoPlayer::open(std::string arg0, StorageType arg1, std::shared_ptr<CallbackScheduler> arg2, std::optional<std::function<void(VideoStatus)>> arg3)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg2 != nullptr)) { throw std::runtime_error("InvalidArgument: callbackScheduler"); }
    if (!(!arg3.has_value() || (arg3.value() != nullptr))) { throw std::runtime_error("InvalidArgument: callback"); }
    easyar_VideoPlayer_open(cdata_.get(), std_string_to_easyar_String(arg0).get(), static_cast<easyar_StorageType>(arg1), arg2->get_cdata().get(), (arg3.has_value() ? easyar_OptionalOfFunctorOfVoidFromVideoStatus{true, FunctorOfVoidFromVideoStatus_to_c(arg3.value())} : easyar_OptionalOfFunctorOfVoidFromVideoStatus{false, {}}));
}
_INLINE_SPECIFIER_ void VideoPlayer::close()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_VideoPlayer_close(cdata_.get());
}
_INLINE_SPECIFIER_ bool VideoPlayer::play()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_play(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void VideoPlayer::stop()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_VideoPlayer_stop(cdata_.get());
}
_INLINE_SPECIFIER_ void VideoPlayer::pause()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_VideoPlayer_pause(cdata_.get());
}
_INLINE_SPECIFIER_ bool VideoPlayer::isRenderTextureAvailable()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_isRenderTextureAvailable(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void VideoPlayer::updateFrame()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_VideoPlayer_updateFrame(cdata_.get());
}
_INLINE_SPECIFIER_ int VideoPlayer::duration()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_duration(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ int VideoPlayer::currentPosition()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_currentPosition(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ bool VideoPlayer::seek(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_seek(cdata_.get(), arg0);
    return _return_value_;
}
_INLINE_SPECIFIER_ Vec2I VideoPlayer::size()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_size(cdata_.get());
    return Vec2I{{{_return_value_.data[0], _return_value_.data[1]}}};
}
_INLINE_SPECIFIER_ float VideoPlayer::volume()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_volume(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ bool VideoPlayer::setVolume(float arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_VideoPlayer_setVolume(cdata_.get(), arg0);
    return _return_value_;
}

_INLINE_SPECIFIER_ std::optional<std::shared_ptr<Image>> ImageHelper::decode(std::shared_ptr<Buffer> arg0)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: buffer"); }
    easyar_OptionalOfImage _return_value_;
    easyar_ImageHelper_decode(arg0->get_cdata().get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? Image::from_cdata(std::shared_ptr<easyar_Image>(_return_value_.value, [](easyar_Image * ptr) { easyar_Image__dtor(ptr); })) : std::optional<std::shared_ptr<Image>>{});
}

_INLINE_SPECIFIER_ SignalSink::SignalSink(std::shared_ptr<easyar_SignalSink> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SignalSink::~SignalSink()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SignalSink> SignalSink::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SignalSink::init_cdata(std::shared_ptr<easyar_SignalSink> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SignalSink> SignalSink::from_cdata(std::shared_ptr<easyar_SignalSink> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SignalSink>(cdata);
}
_INLINE_SPECIFIER_ void SignalSink::handle()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SignalSink_handle(cdata_.get());
}

_INLINE_SPECIFIER_ SignalSource::SignalSource(std::shared_ptr<easyar_SignalSource> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ SignalSource::~SignalSource()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_SignalSource> SignalSource::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void SignalSource::init_cdata(std::shared_ptr<easyar_SignalSource> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<SignalSource> SignalSource::from_cdata(std::shared_ptr<easyar_SignalSource> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<SignalSource>(cdata);
}
_INLINE_SPECIFIER_ void SignalSource::setHandler(std::optional<std::function<void()>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(!arg0.has_value() || (arg0.value() != nullptr))) { throw std::runtime_error("InvalidArgument: handler"); }
    easyar_SignalSource_setHandler(cdata_.get(), (arg0.has_value() ? easyar_OptionalOfFunctorOfVoid{true, FunctorOfVoid_to_c(arg0.value())} : easyar_OptionalOfFunctorOfVoid{false, {}}));
}
_INLINE_SPECIFIER_ void SignalSource::connect(std::shared_ptr<SignalSink> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: sink"); }
    easyar_SignalSource_connect(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ void SignalSource::disconnect()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SignalSource_disconnect(cdata_.get());
}

_INLINE_SPECIFIER_ InputFrameSink::InputFrameSink(std::shared_ptr<easyar_InputFrameSink> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameSink::~InputFrameSink()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameSink> InputFrameSink::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameSink::init_cdata(std::shared_ptr<easyar_InputFrameSink> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameSink>(cdata);
}
_INLINE_SPECIFIER_ void InputFrameSink::handle(std::shared_ptr<InputFrame> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: inputData"); }
    easyar_InputFrameSink_handle(cdata_.get(), arg0->get_cdata().get());
}

_INLINE_SPECIFIER_ InputFrameSource::InputFrameSource(std::shared_ptr<easyar_InputFrameSource> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameSource::~InputFrameSource()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameSource> InputFrameSource::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameSource::init_cdata(std::shared_ptr<easyar_InputFrameSource> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameSource>(cdata);
}
_INLINE_SPECIFIER_ void InputFrameSource::setHandler(std::optional<std::function<void(std::shared_ptr<InputFrame>)>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(!arg0.has_value() || (arg0.value() != nullptr))) { throw std::runtime_error("InvalidArgument: handler"); }
    easyar_InputFrameSource_setHandler(cdata_.get(), (arg0.has_value() ? easyar_OptionalOfFunctorOfVoidFromInputFrame{true, FunctorOfVoidFromInputFrame_to_c(arg0.value())} : easyar_OptionalOfFunctorOfVoidFromInputFrame{false, {}}));
}
_INLINE_SPECIFIER_ void InputFrameSource::connect(std::shared_ptr<InputFrameSink> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: sink"); }
    easyar_InputFrameSource_connect(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ void InputFrameSource::disconnect()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource_disconnect(cdata_.get());
}

_INLINE_SPECIFIER_ OutputFrameSink::OutputFrameSink(std::shared_ptr<easyar_OutputFrameSink> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ OutputFrameSink::~OutputFrameSink()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_OutputFrameSink> OutputFrameSink::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void OutputFrameSink::init_cdata(std::shared_ptr<easyar_OutputFrameSink> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSink> OutputFrameSink::from_cdata(std::shared_ptr<easyar_OutputFrameSink> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<OutputFrameSink>(cdata);
}
_INLINE_SPECIFIER_ void OutputFrameSink::handle(std::shared_ptr<OutputFrame> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: inputData"); }
    easyar_OutputFrameSink_handle(cdata_.get(), arg0->get_cdata().get());
}

_INLINE_SPECIFIER_ OutputFrameSource::OutputFrameSource(std::shared_ptr<easyar_OutputFrameSource> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ OutputFrameSource::~OutputFrameSource()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_OutputFrameSource> OutputFrameSource::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void OutputFrameSource::init_cdata(std::shared_ptr<easyar_OutputFrameSource> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<OutputFrameSource>(cdata);
}
_INLINE_SPECIFIER_ void OutputFrameSource::setHandler(std::optional<std::function<void(std::shared_ptr<OutputFrame>)>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(!arg0.has_value() || (arg0.value() != nullptr))) { throw std::runtime_error("InvalidArgument: handler"); }
    easyar_OutputFrameSource_setHandler(cdata_.get(), (arg0.has_value() ? easyar_OptionalOfFunctorOfVoidFromOutputFrame{true, FunctorOfVoidFromOutputFrame_to_c(arg0.value())} : easyar_OptionalOfFunctorOfVoidFromOutputFrame{false, {}}));
}
_INLINE_SPECIFIER_ void OutputFrameSource::connect(std::shared_ptr<OutputFrameSink> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: sink"); }
    easyar_OutputFrameSource_connect(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ void OutputFrameSource::disconnect()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource_disconnect(cdata_.get());
}

_INLINE_SPECIFIER_ FeedbackFrameSink::FeedbackFrameSink(std::shared_ptr<easyar_FeedbackFrameSink> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ FeedbackFrameSink::~FeedbackFrameSink()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_FeedbackFrameSink> FeedbackFrameSink::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void FeedbackFrameSink::init_cdata(std::shared_ptr<easyar_FeedbackFrameSink> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSink> FeedbackFrameSink::from_cdata(std::shared_ptr<easyar_FeedbackFrameSink> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<FeedbackFrameSink>(cdata);
}
_INLINE_SPECIFIER_ void FeedbackFrameSink::handle(std::shared_ptr<FeedbackFrame> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: inputData"); }
    easyar_FeedbackFrameSink_handle(cdata_.get(), arg0->get_cdata().get());
}

_INLINE_SPECIFIER_ FeedbackFrameSource::FeedbackFrameSource(std::shared_ptr<easyar_FeedbackFrameSource> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ FeedbackFrameSource::~FeedbackFrameSource()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_FeedbackFrameSource> FeedbackFrameSource::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void FeedbackFrameSource::init_cdata(std::shared_ptr<easyar_FeedbackFrameSource> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSource> FeedbackFrameSource::from_cdata(std::shared_ptr<easyar_FeedbackFrameSource> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<FeedbackFrameSource>(cdata);
}
_INLINE_SPECIFIER_ void FeedbackFrameSource::setHandler(std::optional<std::function<void(std::shared_ptr<FeedbackFrame>)>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(!arg0.has_value() || (arg0.value() != nullptr))) { throw std::runtime_error("InvalidArgument: handler"); }
    easyar_FeedbackFrameSource_setHandler(cdata_.get(), (arg0.has_value() ? easyar_OptionalOfFunctorOfVoidFromFeedbackFrame{true, FunctorOfVoidFromFeedbackFrame_to_c(arg0.value())} : easyar_OptionalOfFunctorOfVoidFromFeedbackFrame{false, {}}));
}
_INLINE_SPECIFIER_ void FeedbackFrameSource::connect(std::shared_ptr<FeedbackFrameSink> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: sink"); }
    easyar_FeedbackFrameSource_connect(cdata_.get(), arg0->get_cdata().get());
}
_INLINE_SPECIFIER_ void FeedbackFrameSource::disconnect()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_FeedbackFrameSource_disconnect(cdata_.get());
}

_INLINE_SPECIFIER_ InputFrameFork::InputFrameFork(std::shared_ptr<easyar_InputFrameFork> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameFork::~InputFrameFork()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameFork> InputFrameFork::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameFork::init_cdata(std::shared_ptr<easyar_InputFrameFork> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameFork> InputFrameFork::from_cdata(std::shared_ptr<easyar_InputFrameFork> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameFork>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> InputFrameFork::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_InputFrameFork_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> InputFrameFork::output(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_InputFrameFork_output(cdata_.get(), arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int InputFrameFork::outputCount()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrameFork_outputCount(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameFork> InputFrameFork::create(int arg0)
{
    easyar_InputFrameFork * _return_value_;
    easyar_InputFrameFork_create(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameFork::from_cdata(std::shared_ptr<easyar_InputFrameFork>(_return_value_, [](easyar_InputFrameFork * ptr) { easyar_InputFrameFork__dtor(ptr); }));
}

_INLINE_SPECIFIER_ OutputFrameFork::OutputFrameFork(std::shared_ptr<easyar_OutputFrameFork> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ OutputFrameFork::~OutputFrameFork()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_OutputFrameFork> OutputFrameFork::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void OutputFrameFork::init_cdata(std::shared_ptr<easyar_OutputFrameFork> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameFork> OutputFrameFork::from_cdata(std::shared_ptr<easyar_OutputFrameFork> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<OutputFrameFork>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSink> OutputFrameFork::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSink * _return_value_;
    easyar_OutputFrameFork_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSink::from_cdata(std::shared_ptr<easyar_OutputFrameSink>(_return_value_, [](easyar_OutputFrameSink * ptr) { easyar_OutputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> OutputFrameFork::output(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_OutputFrameFork_output(cdata_.get(), arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int OutputFrameFork::outputCount()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_OutputFrameFork_outputCount(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameFork> OutputFrameFork::create(int arg0)
{
    easyar_OutputFrameFork * _return_value_;
    easyar_OutputFrameFork_create(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameFork::from_cdata(std::shared_ptr<easyar_OutputFrameFork>(_return_value_, [](easyar_OutputFrameFork * ptr) { easyar_OutputFrameFork__dtor(ptr); }));
}

_INLINE_SPECIFIER_ OutputFrameJoin::OutputFrameJoin(std::shared_ptr<easyar_OutputFrameJoin> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ OutputFrameJoin::~OutputFrameJoin()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_OutputFrameJoin> OutputFrameJoin::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void OutputFrameJoin::init_cdata(std::shared_ptr<easyar_OutputFrameJoin> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameJoin> OutputFrameJoin::from_cdata(std::shared_ptr<easyar_OutputFrameJoin> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<OutputFrameJoin>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSink> OutputFrameJoin::input(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSink * _return_value_;
    easyar_OutputFrameJoin_input(cdata_.get(), arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSink::from_cdata(std::shared_ptr<easyar_OutputFrameSink>(_return_value_, [](easyar_OutputFrameSink * ptr) { easyar_OutputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> OutputFrameJoin::output()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_OutputFrameJoin_output(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int OutputFrameJoin::inputCount()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_OutputFrameJoin_inputCount(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameJoin> OutputFrameJoin::create(int arg0)
{
    easyar_OutputFrameJoin * _return_value_;
    easyar_OutputFrameJoin_create(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameJoin::from_cdata(std::shared_ptr<easyar_OutputFrameJoin>(_return_value_, [](easyar_OutputFrameJoin * ptr) { easyar_OutputFrameJoin__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameJoin> OutputFrameJoin::createWithJoiner(int arg0, std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)> arg1)
{
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: joiner"); }
    easyar_OutputFrameJoin * _return_value_;
    easyar_OutputFrameJoin_createWithJoiner(arg0, FunctorOfOutputFrameFromListOfOutputFrame_to_c(arg1), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameJoin::from_cdata(std::shared_ptr<easyar_OutputFrameJoin>(_return_value_, [](easyar_OutputFrameJoin * ptr) { easyar_OutputFrameJoin__dtor(ptr); }));
}

_INLINE_SPECIFIER_ FeedbackFrameFork::FeedbackFrameFork(std::shared_ptr<easyar_FeedbackFrameFork> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ FeedbackFrameFork::~FeedbackFrameFork()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_FeedbackFrameFork> FeedbackFrameFork::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void FeedbackFrameFork::init_cdata(std::shared_ptr<easyar_FeedbackFrameFork> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameFork> FeedbackFrameFork::from_cdata(std::shared_ptr<easyar_FeedbackFrameFork> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<FeedbackFrameFork>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSink> FeedbackFrameFork::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_FeedbackFrameSink * _return_value_;
    easyar_FeedbackFrameFork_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return FeedbackFrameSink::from_cdata(std::shared_ptr<easyar_FeedbackFrameSink>(_return_value_, [](easyar_FeedbackFrameSink * ptr) { easyar_FeedbackFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSource> FeedbackFrameFork::output(int arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_FeedbackFrameSource * _return_value_;
    easyar_FeedbackFrameFork_output(cdata_.get(), arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return FeedbackFrameSource::from_cdata(std::shared_ptr<easyar_FeedbackFrameSource>(_return_value_, [](easyar_FeedbackFrameSource * ptr) { easyar_FeedbackFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int FeedbackFrameFork::outputCount()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_FeedbackFrameFork_outputCount(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameFork> FeedbackFrameFork::create(int arg0)
{
    easyar_FeedbackFrameFork * _return_value_;
    easyar_FeedbackFrameFork_create(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return FeedbackFrameFork::from_cdata(std::shared_ptr<easyar_FeedbackFrameFork>(_return_value_, [](easyar_FeedbackFrameFork * ptr) { easyar_FeedbackFrameFork__dtor(ptr); }));
}

_INLINE_SPECIFIER_ InputFrameThrottler::InputFrameThrottler(std::shared_ptr<easyar_InputFrameThrottler> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameThrottler::~InputFrameThrottler()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameThrottler> InputFrameThrottler::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameThrottler::init_cdata(std::shared_ptr<easyar_InputFrameThrottler> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameThrottler> InputFrameThrottler::from_cdata(std::shared_ptr<easyar_InputFrameThrottler> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameThrottler>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> InputFrameThrottler::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_InputFrameThrottler_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int InputFrameThrottler::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrameThrottler_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSource> InputFrameThrottler::output()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSource * _return_value_;
    easyar_InputFrameThrottler_output(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSource::from_cdata(std::shared_ptr<easyar_InputFrameSource>(_return_value_, [](easyar_InputFrameSource * ptr) { easyar_InputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<SignalSink> InputFrameThrottler::signalInput()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SignalSink * _return_value_;
    easyar_InputFrameThrottler_signalInput(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SignalSink::from_cdata(std::shared_ptr<easyar_SignalSink>(_return_value_, [](easyar_SignalSink * ptr) { easyar_SignalSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameThrottler> InputFrameThrottler::create()
{
    easyar_InputFrameThrottler * _return_value_;
    easyar_InputFrameThrottler_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameThrottler::from_cdata(std::shared_ptr<easyar_InputFrameThrottler>(_return_value_, [](easyar_InputFrameThrottler * ptr) { easyar_InputFrameThrottler__dtor(ptr); }));
}

_INLINE_SPECIFIER_ OutputFrameBuffer::OutputFrameBuffer(std::shared_ptr<easyar_OutputFrameBuffer> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ OutputFrameBuffer::~OutputFrameBuffer()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_OutputFrameBuffer> OutputFrameBuffer::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void OutputFrameBuffer::init_cdata(std::shared_ptr<easyar_OutputFrameBuffer> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameBuffer> OutputFrameBuffer::from_cdata(std::shared_ptr<easyar_OutputFrameBuffer> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<OutputFrameBuffer>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSink> OutputFrameBuffer::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSink * _return_value_;
    easyar_OutputFrameBuffer_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSink::from_cdata(std::shared_ptr<easyar_OutputFrameSink>(_return_value_, [](easyar_OutputFrameSink * ptr) { easyar_OutputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int OutputFrameBuffer::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_OutputFrameBuffer_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<SignalSource> OutputFrameBuffer::signalOutput()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_SignalSource * _return_value_;
    easyar_OutputFrameBuffer_signalOutput(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return SignalSource::from_cdata(std::shared_ptr<easyar_SignalSource>(_return_value_, [](easyar_SignalSource * ptr) { easyar_SignalSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<OutputFrame>> OutputFrameBuffer::peek()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfOutputFrame _return_value_;
    easyar_OutputFrameBuffer_peek(cdata_.get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? OutputFrame::from_cdata(std::shared_ptr<easyar_OutputFrame>(_return_value_.value, [](easyar_OutputFrame * ptr) { easyar_OutputFrame__dtor(ptr); })) : std::optional<std::shared_ptr<OutputFrame>>{});
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameBuffer> OutputFrameBuffer::create()
{
    easyar_OutputFrameBuffer * _return_value_;
    easyar_OutputFrameBuffer_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameBuffer::from_cdata(std::shared_ptr<easyar_OutputFrameBuffer>(_return_value_, [](easyar_OutputFrameBuffer * ptr) { easyar_OutputFrameBuffer__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void OutputFrameBuffer::pause()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameBuffer_pause(cdata_.get());
}
_INLINE_SPECIFIER_ void OutputFrameBuffer::resume()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameBuffer_resume(cdata_.get());
}

_INLINE_SPECIFIER_ InputFrameToOutputFrameAdapter::InputFrameToOutputFrameAdapter(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameToOutputFrameAdapter::~InputFrameToOutputFrameAdapter()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> InputFrameToOutputFrameAdapter::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameToOutputFrameAdapter::init_cdata(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameToOutputFrameAdapter> InputFrameToOutputFrameAdapter::from_cdata(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameToOutputFrameAdapter>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> InputFrameToOutputFrameAdapter::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_InputFrameToOutputFrameAdapter_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSource> InputFrameToOutputFrameAdapter::output()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSource * _return_value_;
    easyar_InputFrameToOutputFrameAdapter_output(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSource::from_cdata(std::shared_ptr<easyar_OutputFrameSource>(_return_value_, [](easyar_OutputFrameSource * ptr) { easyar_OutputFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameToOutputFrameAdapter> InputFrameToOutputFrameAdapter::create()
{
    easyar_InputFrameToOutputFrameAdapter * _return_value_;
    easyar_InputFrameToOutputFrameAdapter_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameToOutputFrameAdapter::from_cdata(std::shared_ptr<easyar_InputFrameToOutputFrameAdapter>(_return_value_, [](easyar_InputFrameToOutputFrameAdapter * ptr) { easyar_InputFrameToOutputFrameAdapter__dtor(ptr); }));
}

_INLINE_SPECIFIER_ InputFrameToFeedbackFrameAdapter::InputFrameToFeedbackFrameAdapter(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrameToFeedbackFrameAdapter::~InputFrameToFeedbackFrameAdapter()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> InputFrameToFeedbackFrameAdapter::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrameToFeedbackFrameAdapter::init_cdata(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameToFeedbackFrameAdapter> InputFrameToFeedbackFrameAdapter::from_cdata(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrameToFeedbackFrameAdapter>(cdata);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameSink> InputFrameToFeedbackFrameAdapter::input()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrameSink * _return_value_;
    easyar_InputFrameToFeedbackFrameAdapter_input(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameSink::from_cdata(std::shared_ptr<easyar_InputFrameSink>(_return_value_, [](easyar_InputFrameSink * ptr) { easyar_InputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int InputFrameToFeedbackFrameAdapter::bufferRequirement()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrameToFeedbackFrameAdapter_bufferRequirement(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrameSink> InputFrameToFeedbackFrameAdapter::sideInput()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OutputFrameSink * _return_value_;
    easyar_InputFrameToFeedbackFrameAdapter_sideInput(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return OutputFrameSink::from_cdata(std::shared_ptr<easyar_OutputFrameSink>(_return_value_, [](easyar_OutputFrameSink * ptr) { easyar_OutputFrameSink__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrameSource> InputFrameToFeedbackFrameAdapter::output()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_FeedbackFrameSource * _return_value_;
    easyar_InputFrameToFeedbackFrameAdapter_output(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return FeedbackFrameSource::from_cdata(std::shared_ptr<easyar_FeedbackFrameSource>(_return_value_, [](easyar_FeedbackFrameSource * ptr) { easyar_FeedbackFrameSource__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrameToFeedbackFrameAdapter> InputFrameToFeedbackFrameAdapter::create()
{
    easyar_InputFrameToFeedbackFrameAdapter * _return_value_;
    easyar_InputFrameToFeedbackFrameAdapter_create(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrameToFeedbackFrameAdapter::from_cdata(std::shared_ptr<easyar_InputFrameToFeedbackFrameAdapter>(_return_value_, [](easyar_InputFrameToFeedbackFrameAdapter * ptr) { easyar_InputFrameToFeedbackFrameAdapter__dtor(ptr); }));
}

_INLINE_SPECIFIER_ InputFrame::InputFrame(std::shared_ptr<easyar_InputFrame> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ InputFrame::~InputFrame()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_InputFrame> InputFrame::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void InputFrame::init_cdata(std::shared_ptr<easyar_InputFrame> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<InputFrame>(cdata);
}
_INLINE_SPECIFIER_ int InputFrame::index()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_index(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<Image> InputFrame::image()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Image * _return_value_;
    easyar_InputFrame_image(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return Image::from_cdata(std::shared_ptr<easyar_Image>(_return_value_, [](easyar_Image * ptr) { easyar_Image__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool InputFrame::hasCameraParameters()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_hasCameraParameters(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<CameraParameters> InputFrame::cameraParameters()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_CameraParameters * _return_value_;
    easyar_InputFrame_cameraParameters(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return CameraParameters::from_cdata(std::shared_ptr<easyar_CameraParameters>(_return_value_, [](easyar_CameraParameters * ptr) { easyar_CameraParameters__dtor(ptr); }));
}
_INLINE_SPECIFIER_ bool InputFrame::hasTemporalInformation()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_hasTemporalInformation(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ double InputFrame::timestamp()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_timestamp(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ bool InputFrame::hasSpatialInformation()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_hasSpatialInformation(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ Matrix44F InputFrame::cameraTransform()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_cameraTransform(cdata_.get());
    return Matrix44F{{{_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]}}};
}
_INLINE_SPECIFIER_ MotionTrackingStatus InputFrame::trackingStatus()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_InputFrame_trackingStatus(cdata_.get());
    return static_cast<MotionTrackingStatus>(_return_value_);
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> InputFrame::create(std::shared_ptr<Image> arg0, std::shared_ptr<CameraParameters> arg1, double arg2, Matrix44F arg3, MotionTrackingStatus arg4)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: image"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: cameraParameters"); }
    easyar_InputFrame * _return_value_;
    easyar_InputFrame_create(arg0->get_cdata().get(), arg1->get_cdata().get(), arg2, easyar_Matrix44F{{arg3.data[0], arg3.data[1], arg3.data[2], arg3.data[3], arg3.data[4], arg3.data[5], arg3.data[6], arg3.data[7], arg3.data[8], arg3.data[9], arg3.data[10], arg3.data[11], arg3.data[12], arg3.data[13], arg3.data[14], arg3.data[15]}}, static_cast<easyar_MotionTrackingStatus>(arg4), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(_return_value_, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> InputFrame::createWithImageAndCameraParametersAndTemporal(std::shared_ptr<Image> arg0, std::shared_ptr<CameraParameters> arg1, double arg2)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: image"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: cameraParameters"); }
    easyar_InputFrame * _return_value_;
    easyar_InputFrame_createWithImageAndCameraParametersAndTemporal(arg0->get_cdata().get(), arg1->get_cdata().get(), arg2, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(_return_value_, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> InputFrame::createWithImageAndCameraParameters(std::shared_ptr<Image> arg0, std::shared_ptr<CameraParameters> arg1)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: image"); }
    if (!(arg1 != nullptr)) { throw std::runtime_error("InvalidArgument: cameraParameters"); }
    easyar_InputFrame * _return_value_;
    easyar_InputFrame_createWithImageAndCameraParameters(arg0->get_cdata().get(), arg1->get_cdata().get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(_return_value_, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> InputFrame::createWithImage(std::shared_ptr<Image> arg0)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: image"); }
    easyar_InputFrame * _return_value_;
    easyar_InputFrame_createWithImage(arg0->get_cdata().get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(_return_value_, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
}

_INLINE_SPECIFIER_ FrameFilterResult::FrameFilterResult(std::shared_ptr<easyar_FrameFilterResult> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ FrameFilterResult::~FrameFilterResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_FrameFilterResult> FrameFilterResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void FrameFilterResult::init_cdata(std::shared_ptr<easyar_FrameFilterResult> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<FrameFilterResult> FrameFilterResult::from_cdata(std::shared_ptr<easyar_FrameFilterResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    std::string typeName = easyar_FrameFilterResult__typeName(cdata.get());
    if (typeName == "ObjectTrackerResult") {
        easyar_ObjectTrackerResult * st_cdata;
        easyar_tryCastFrameFilterResultToObjectTrackerResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<FrameFilterResult>(std::make_shared<ObjectTrackerResult>(std::shared_ptr<easyar_ObjectTrackerResult>(st_cdata, [](easyar_ObjectTrackerResult * ptr) { easyar_ObjectTrackerResult__dtor(ptr); })));
    }
    if (typeName == "SurfaceTrackerResult") {
        easyar_SurfaceTrackerResult * st_cdata;
        easyar_tryCastFrameFilterResultToSurfaceTrackerResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<FrameFilterResult>(std::make_shared<SurfaceTrackerResult>(std::shared_ptr<easyar_SurfaceTrackerResult>(st_cdata, [](easyar_SurfaceTrackerResult * ptr) { easyar_SurfaceTrackerResult__dtor(ptr); })));
    }
    if (typeName == "ImageTrackerResult") {
        easyar_ImageTrackerResult * st_cdata;
        easyar_tryCastFrameFilterResultToImageTrackerResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<FrameFilterResult>(std::make_shared<ImageTrackerResult>(std::shared_ptr<easyar_ImageTrackerResult>(st_cdata, [](easyar_ImageTrackerResult * ptr) { easyar_ImageTrackerResult__dtor(ptr); })));
    }
    if (typeName == "SparseSpatialMapResult") {
        easyar_SparseSpatialMapResult * st_cdata;
        easyar_tryCastFrameFilterResultToSparseSpatialMapResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<FrameFilterResult>(std::make_shared<SparseSpatialMapResult>(std::shared_ptr<easyar_SparseSpatialMapResult>(st_cdata, [](easyar_SparseSpatialMapResult * ptr) { easyar_SparseSpatialMapResult__dtor(ptr); })));
    }
    if (typeName == "TargetTrackerResult") {
        easyar_TargetTrackerResult * st_cdata;
        easyar_tryCastFrameFilterResultToTargetTrackerResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<FrameFilterResult>(std::make_shared<TargetTrackerResult>(std::shared_ptr<easyar_TargetTrackerResult>(st_cdata, [](easyar_TargetTrackerResult * ptr) { easyar_TargetTrackerResult__dtor(ptr); })));
    }
    return std::make_shared<FrameFilterResult>(cdata);
}

_INLINE_SPECIFIER_ OutputFrame::OutputFrame(std::shared_ptr<easyar_OutputFrame> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ OutputFrame::~OutputFrame()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_OutputFrame> OutputFrame::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void OutputFrame::init_cdata(std::shared_ptr<easyar_OutputFrame> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<OutputFrame> OutputFrame::from_cdata(std::shared_ptr<easyar_OutputFrame> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<OutputFrame>(cdata);
}
_INLINE_SPECIFIER_ OutputFrame::OutputFrame(std::shared_ptr<InputFrame> arg0, std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> arg1)
    :
    cdata_(nullptr)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: inputFrame"); }
    if (!easyar_ListOfOptionalOfFrameFilterResult_check_external_cpp(arg1)) { throw std::runtime_error("InvalidArgument: results"); }
    easyar_OutputFrame * _return_value_;
    easyar_OutputFrame__ctor(arg0->get_cdata().get(), std_vector_to_easyar_ListOfOptionalOfFrameFilterResult(arg1).get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_OutputFrame>(_return_value_, [](easyar_OutputFrame * ptr) { easyar_OutputFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ int OutputFrame::index()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_OutputFrame_index(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> OutputFrame::inputFrame()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrame * _return_value_;
    easyar_OutputFrame_inputFrame(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(_return_value_, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> OutputFrame::results()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfOptionalOfFrameFilterResult * _return_value_;
    easyar_OutputFrame_results(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfOptionalOfFrameFilterResult(std::shared_ptr<easyar_ListOfOptionalOfFrameFilterResult>(_return_value_, [](easyar_ListOfOptionalOfFrameFilterResult * ptr) { easyar_ListOfOptionalOfFrameFilterResult__dtor(ptr); }));
}

_INLINE_SPECIFIER_ FeedbackFrame::FeedbackFrame(std::shared_ptr<easyar_FeedbackFrame> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ FeedbackFrame::~FeedbackFrame()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_FeedbackFrame> FeedbackFrame::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void FeedbackFrame::init_cdata(std::shared_ptr<easyar_FeedbackFrame> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<FeedbackFrame> FeedbackFrame::from_cdata(std::shared_ptr<easyar_FeedbackFrame> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<FeedbackFrame>(cdata);
}
_INLINE_SPECIFIER_ FeedbackFrame::FeedbackFrame(std::shared_ptr<InputFrame> arg0, std::optional<std::shared_ptr<OutputFrame>> arg1)
    :
    cdata_(nullptr)
{
    if (!(arg0 != nullptr)) { throw std::runtime_error("InvalidArgument: inputFrame"); }
    if (!(!arg1.has_value() || (arg1.value() != nullptr))) { throw std::runtime_error("InvalidArgument: previousOutputFrame"); }
    easyar_FeedbackFrame * _return_value_;
    easyar_FeedbackFrame__ctor(arg0->get_cdata().get(), (arg1.has_value() ? easyar_OptionalOfOutputFrame{true, arg1.value()->get_cdata().get()} : easyar_OptionalOfOutputFrame{false, {}}), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_FeedbackFrame>(_return_value_, [](easyar_FeedbackFrame * ptr) { easyar_FeedbackFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<InputFrame> FeedbackFrame::inputFrame()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_InputFrame * _return_value_;
    easyar_FeedbackFrame_inputFrame(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(_return_value_, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<OutputFrame>> FeedbackFrame::previousOutputFrame()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfOutputFrame _return_value_;
    easyar_FeedbackFrame_previousOutputFrame(cdata_.get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? OutputFrame::from_cdata(std::shared_ptr<easyar_OutputFrame>(_return_value_.value, [](easyar_OutputFrame * ptr) { easyar_OutputFrame__dtor(ptr); })) : std::optional<std::shared_ptr<OutputFrame>>{});
}

_INLINE_SPECIFIER_ Target::Target(std::shared_ptr<easyar_Target> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ Target::~Target()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_Target> Target::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void Target::init_cdata(std::shared_ptr<easyar_Target> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<Target> Target::from_cdata(std::shared_ptr<easyar_Target> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    std::string typeName = easyar_Target__typeName(cdata.get());
    if (typeName == "ObjectTarget") {
        easyar_ObjectTarget * st_cdata;
        easyar_tryCastTargetToObjectTarget(cdata.get(), &st_cdata);
        return std::static_pointer_cast<Target>(std::make_shared<ObjectTarget>(std::shared_ptr<easyar_ObjectTarget>(st_cdata, [](easyar_ObjectTarget * ptr) { easyar_ObjectTarget__dtor(ptr); })));
    }
    if (typeName == "ImageTarget") {
        easyar_ImageTarget * st_cdata;
        easyar_tryCastTargetToImageTarget(cdata.get(), &st_cdata);
        return std::static_pointer_cast<Target>(std::make_shared<ImageTarget>(std::shared_ptr<easyar_ImageTarget>(st_cdata, [](easyar_ImageTarget * ptr) { easyar_ImageTarget__dtor(ptr); })));
    }
    return std::make_shared<Target>(cdata);
}
_INLINE_SPECIFIER_ int Target::runtimeID()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_Target_runtimeID(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::string Target::uid()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_Target_uid(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::string Target::name()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_Target_name(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void Target::setName(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Target_setName(cdata_.get(), std_string_to_easyar_String(arg0).get());
}
_INLINE_SPECIFIER_ std::string Target::meta()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_String * _return_value_;
    easyar_Target_meta(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_string_from_easyar_String(std::shared_ptr<easyar_String>(_return_value_, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void Target::setMeta(std::string arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_Target_setMeta(cdata_.get(), std_string_to_easyar_String(arg0).get());
}

_INLINE_SPECIFIER_ TargetInstance::TargetInstance(std::shared_ptr<easyar_TargetInstance> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ TargetInstance::~TargetInstance()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_TargetInstance> TargetInstance::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void TargetInstance::init_cdata(std::shared_ptr<easyar_TargetInstance> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<TargetInstance> TargetInstance::from_cdata(std::shared_ptr<easyar_TargetInstance> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<TargetInstance>(cdata);
}
_INLINE_SPECIFIER_ TargetInstance::TargetInstance()
    :
    cdata_(nullptr)
{
    easyar_TargetInstance * _return_value_;
    easyar_TargetInstance__ctor(&_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); };
    init_cdata(std::shared_ptr<easyar_TargetInstance>(_return_value_, [](easyar_TargetInstance * ptr) { easyar_TargetInstance__dtor(ptr); }));
}
_INLINE_SPECIFIER_ TargetStatus TargetInstance::status()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_TargetInstance_status(cdata_.get());
    return static_cast<TargetStatus>(_return_value_);
}
_INLINE_SPECIFIER_ std::optional<std::shared_ptr<Target>> TargetInstance::target()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_OptionalOfTarget _return_value_;
    easyar_TargetInstance_target(cdata_.get(), &_return_value_);
    if (!(!_return_value_.has_value || (_return_value_.value != nullptr))) { throw std::runtime_error("InvalidReturnValue"); }
    return (_return_value_.has_value ? Target::from_cdata(std::shared_ptr<easyar_Target>(_return_value_.value, [](easyar_Target * ptr) { easyar_Target__dtor(ptr); })) : std::optional<std::shared_ptr<Target>>{});
}
_INLINE_SPECIFIER_ Matrix44F TargetInstance::pose()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_TargetInstance_pose(cdata_.get());
    return Matrix44F{{{_return_value_.data[0], _return_value_.data[1], _return_value_.data[2], _return_value_.data[3], _return_value_.data[4], _return_value_.data[5], _return_value_.data[6], _return_value_.data[7], _return_value_.data[8], _return_value_.data[9], _return_value_.data[10], _return_value_.data[11], _return_value_.data[12], _return_value_.data[13], _return_value_.data[14], _return_value_.data[15]}}};
}

_INLINE_SPECIFIER_ TargetTrackerResult::TargetTrackerResult(std::shared_ptr<easyar_TargetTrackerResult> cdata)
    :
    FrameFilterResult(std::shared_ptr<easyar_FrameFilterResult>(nullptr)),
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ TargetTrackerResult::~TargetTrackerResult()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_TargetTrackerResult> TargetTrackerResult::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void TargetTrackerResult::init_cdata(std::shared_ptr<easyar_TargetTrackerResult> cdata)
{
    cdata_ = cdata;
    {
        easyar_FrameFilterResult * ptr = nullptr;
        easyar_castTargetTrackerResultToFrameFilterResult(cdata_.get(), &ptr);
        FrameFilterResult::init_cdata(std::shared_ptr<easyar_FrameFilterResult>(ptr, [](easyar_FrameFilterResult * ptr) { easyar_FrameFilterResult__dtor(ptr); }));
    }
}
_INLINE_SPECIFIER_ std::shared_ptr<TargetTrackerResult> TargetTrackerResult::from_cdata(std::shared_ptr<easyar_TargetTrackerResult> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    std::string typeName = easyar_TargetTrackerResult__typeName(cdata.get());
    if (typeName == "ObjectTrackerResult") {
        easyar_ObjectTrackerResult * st_cdata;
        easyar_tryCastTargetTrackerResultToObjectTrackerResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<TargetTrackerResult>(std::make_shared<ObjectTrackerResult>(std::shared_ptr<easyar_ObjectTrackerResult>(st_cdata, [](easyar_ObjectTrackerResult * ptr) { easyar_ObjectTrackerResult__dtor(ptr); })));
    }
    if (typeName == "ImageTrackerResult") {
        easyar_ImageTrackerResult * st_cdata;
        easyar_tryCastTargetTrackerResultToImageTrackerResult(cdata.get(), &st_cdata);
        return std::static_pointer_cast<TargetTrackerResult>(std::make_shared<ImageTrackerResult>(std::shared_ptr<easyar_ImageTrackerResult>(st_cdata, [](easyar_ImageTrackerResult * ptr) { easyar_ImageTrackerResult__dtor(ptr); })));
    }
    return std::make_shared<TargetTrackerResult>(cdata);
}
_INLINE_SPECIFIER_ std::vector<std::shared_ptr<TargetInstance>> TargetTrackerResult::targetInstances()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    easyar_ListOfTargetInstance * _return_value_;
    easyar_TargetTrackerResult_targetInstances(cdata_.get(), &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return std_vector_from_easyar_ListOfTargetInstance(std::shared_ptr<easyar_ListOfTargetInstance>(_return_value_, [](easyar_ListOfTargetInstance * ptr) { easyar_ListOfTargetInstance__dtor(ptr); }));
}
_INLINE_SPECIFIER_ void TargetTrackerResult::setTargetInstances(std::vector<std::shared_ptr<TargetInstance>> arg0)
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    if (!easyar_ListOfTargetInstance_check_external_cpp(arg0)) { throw std::runtime_error("InvalidArgument: instances"); }
    easyar_TargetTrackerResult_setTargetInstances(cdata_.get(), std_vector_to_easyar_ListOfTargetInstance(arg0).get());
}

_INLINE_SPECIFIER_ TextureId::TextureId(std::shared_ptr<easyar_TextureId> cdata)
    :
    cdata_(nullptr)
{
    init_cdata(cdata);
}
_INLINE_SPECIFIER_ TextureId::~TextureId()
{
    cdata_ = nullptr;
}

_INLINE_SPECIFIER_ std::shared_ptr<easyar_TextureId> TextureId::get_cdata()
{
    return cdata_;
}
_INLINE_SPECIFIER_ void TextureId::init_cdata(std::shared_ptr<easyar_TextureId> cdata)
{
    cdata_ = cdata;
}
_INLINE_SPECIFIER_ std::shared_ptr<TextureId> TextureId::from_cdata(std::shared_ptr<easyar_TextureId> cdata)
{
    if (cdata == nullptr) {
        return nullptr;
    }
    return std::make_shared<TextureId>(cdata);
}
_INLINE_SPECIFIER_ int TextureId::getInt()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_TextureId_getInt(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ void * TextureId::getPointer()
{
    if (cdata_ == nullptr) { throw std::runtime_error("InvalidArgument: this"); }
    auto _return_value_ = easyar_TextureId_getPointer(cdata_.get());
    return _return_value_;
}
_INLINE_SPECIFIER_ std::shared_ptr<TextureId> TextureId::fromInt(int arg0)
{
    easyar_TextureId * _return_value_;
    easyar_TextureId_fromInt(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return TextureId::from_cdata(std::shared_ptr<easyar_TextureId>(_return_value_, [](easyar_TextureId * ptr) { easyar_TextureId__dtor(ptr); }));
}
_INLINE_SPECIFIER_ std::shared_ptr<TextureId> TextureId::fromPointer(void * arg0)
{
    easyar_TextureId * _return_value_;
    easyar_TextureId_fromPointer(arg0, &_return_value_);
    if (!(_return_value_ != nullptr)) { throw std::runtime_error("InvalidReturnValue"); }
    return TextureId::from_cdata(std::shared_ptr<easyar_TextureId>(_return_value_, [](easyar_TextureId * ptr) { easyar_TextureId__dtor(ptr); }));
}

static void FunctorOfVoid_func(void * _state, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        auto f = reinterpret_cast<std::function<void()> *>(_state);
        (*f)();
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoid_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void()> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoid FunctorOfVoid_to_c(std::function<void()> f)
{
    return easyar_FunctorOfVoid{new std::function<void()>(f), FunctorOfVoid_func, FunctorOfVoid_destroy};
}

static inline std::shared_ptr<easyar_ListOfVec3F> std_vector_to_easyar_ListOfVec3F(std::vector<Vec3F> l)
{
    std::vector<easyar_Vec3F> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = easyar_Vec3F{{v.data[0], v.data[1], v.data[2]}};
        values.push_back(cv);
    }
    easyar_ListOfVec3F * ptr;
    easyar_ListOfVec3F__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfVec3F>(ptr, [](easyar_ListOfVec3F * ptr) { easyar_ListOfVec3F__dtor(ptr); });
}
static inline std::vector<Vec3F> std_vector_from_easyar_ListOfVec3F(std::shared_ptr<easyar_ListOfVec3F> pl)
{
    auto size = easyar_ListOfVec3F_size(pl.get());
    std::vector<Vec3F> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfVec3F_at(pl.get(), k);
        values.push_back(Vec3F{{{v.data[0], v.data[1], v.data[2]}}});
    }
    return values;
}
static inline bool easyar_ListOfVec3F_check_external_cpp(const std::vector<Vec3F> & l)
{
    return true;
}

static inline std::shared_ptr<easyar_ListOfTargetInstance> std_vector_to_easyar_ListOfTargetInstance(std::vector<std::shared_ptr<TargetInstance>> l)
{
    std::vector<easyar_TargetInstance *> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = v->get_cdata().get();
        easyar_TargetInstance__retain(cv, &cv);
        values.push_back(cv);
    }
    easyar_ListOfTargetInstance * ptr;
    easyar_ListOfTargetInstance__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfTargetInstance>(ptr, [](easyar_ListOfTargetInstance * ptr) { easyar_ListOfTargetInstance__dtor(ptr); });
}
static inline std::vector<std::shared_ptr<TargetInstance>> std_vector_from_easyar_ListOfTargetInstance(std::shared_ptr<easyar_ListOfTargetInstance> pl)
{
    auto size = easyar_ListOfTargetInstance_size(pl.get());
    std::vector<std::shared_ptr<TargetInstance>> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfTargetInstance_at(pl.get(), k);
        easyar_TargetInstance__retain(v, &v);
        values.push_back(TargetInstance::from_cdata(std::shared_ptr<easyar_TargetInstance>(v, [](easyar_TargetInstance * ptr) { easyar_TargetInstance__dtor(ptr); })));
    }
    return values;
}
static inline bool easyar_ListOfTargetInstance_check_external_cpp(const std::vector<std::shared_ptr<TargetInstance>> & l)
{
    for (auto e : l) {
        if (!(e != nullptr)) { return false; }
    }
    return true;
}

static inline std::shared_ptr<easyar_ListOfOptionalOfFrameFilterResult> std_vector_to_easyar_ListOfOptionalOfFrameFilterResult(std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> l)
{
    std::vector<easyar_OptionalOfFrameFilterResult> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = (v.has_value() ? easyar_OptionalOfFrameFilterResult{true, v.value()->get_cdata().get()} : easyar_OptionalOfFrameFilterResult{false, {}});
        if (cv.has_value) { easyar_FrameFilterResult__retain(cv.value, &cv.value); }
        values.push_back(cv);
    }
    easyar_ListOfOptionalOfFrameFilterResult * ptr;
    easyar_ListOfOptionalOfFrameFilterResult__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfOptionalOfFrameFilterResult>(ptr, [](easyar_ListOfOptionalOfFrameFilterResult * ptr) { easyar_ListOfOptionalOfFrameFilterResult__dtor(ptr); });
}
static inline std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> std_vector_from_easyar_ListOfOptionalOfFrameFilterResult(std::shared_ptr<easyar_ListOfOptionalOfFrameFilterResult> pl)
{
    auto size = easyar_ListOfOptionalOfFrameFilterResult_size(pl.get());
    std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfOptionalOfFrameFilterResult_at(pl.get(), k);
        if (v.has_value) { easyar_FrameFilterResult__retain(v.value, &v.value); }
        values.push_back((v.has_value ? FrameFilterResult::from_cdata(std::shared_ptr<easyar_FrameFilterResult>(v.value, [](easyar_FrameFilterResult * ptr) { easyar_FrameFilterResult__dtor(ptr); })) : std::optional<std::shared_ptr<FrameFilterResult>>{}));
    }
    return values;
}
static inline bool easyar_ListOfOptionalOfFrameFilterResult_check_external_cpp(const std::vector<std::optional<std::shared_ptr<FrameFilterResult>>> & l)
{
    for (auto e : l) {
        if (!(!e.has_value() || (e.value() != nullptr))) { return false; }
    }
    return true;
}

static void FunctorOfVoidFromOutputFrame_func(void * _state, easyar_OutputFrame * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        easyar_OutputFrame__retain(arg0, &arg0);
        std::shared_ptr<OutputFrame> cpparg0 = OutputFrame::from_cdata(std::shared_ptr<easyar_OutputFrame>(arg0, [](easyar_OutputFrame * ptr) { easyar_OutputFrame__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(std::shared_ptr<OutputFrame>)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromOutputFrame_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(std::shared_ptr<OutputFrame>)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromOutputFrame FunctorOfVoidFromOutputFrame_to_c(std::function<void(std::shared_ptr<OutputFrame>)> f)
{
    return easyar_FunctorOfVoidFromOutputFrame{new std::function<void(std::shared_ptr<OutputFrame>)>(f), FunctorOfVoidFromOutputFrame_func, FunctorOfVoidFromOutputFrame_destroy};
}

static void FunctorOfVoidFromTargetAndBool_func(void * _state, easyar_Target * arg0, bool arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        easyar_Target__retain(arg0, &arg0);
        std::shared_ptr<Target> cpparg0 = Target::from_cdata(std::shared_ptr<easyar_Target>(arg0, [](easyar_Target * ptr) { easyar_Target__dtor(ptr); }));
        bool cpparg1 = arg1;
        auto f = reinterpret_cast<std::function<void(std::shared_ptr<Target>, bool)> *>(_state);
        (*f)(cpparg0, cpparg1);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromTargetAndBool_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(std::shared_ptr<Target>, bool)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromTargetAndBool FunctorOfVoidFromTargetAndBool_to_c(std::function<void(std::shared_ptr<Target>, bool)> f)
{
    return easyar_FunctorOfVoidFromTargetAndBool{new std::function<void(std::shared_ptr<Target>, bool)>(f), FunctorOfVoidFromTargetAndBool_func, FunctorOfVoidFromTargetAndBool_destroy};
}

static inline std::shared_ptr<easyar_ListOfTarget> std_vector_to_easyar_ListOfTarget(std::vector<std::shared_ptr<Target>> l)
{
    std::vector<easyar_Target *> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = v->get_cdata().get();
        easyar_Target__retain(cv, &cv);
        values.push_back(cv);
    }
    easyar_ListOfTarget * ptr;
    easyar_ListOfTarget__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfTarget>(ptr, [](easyar_ListOfTarget * ptr) { easyar_ListOfTarget__dtor(ptr); });
}
static inline std::vector<std::shared_ptr<Target>> std_vector_from_easyar_ListOfTarget(std::shared_ptr<easyar_ListOfTarget> pl)
{
    auto size = easyar_ListOfTarget_size(pl.get());
    std::vector<std::shared_ptr<Target>> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfTarget_at(pl.get(), k);
        easyar_Target__retain(v, &v);
        values.push_back(Target::from_cdata(std::shared_ptr<easyar_Target>(v, [](easyar_Target * ptr) { easyar_Target__dtor(ptr); })));
    }
    return values;
}
static inline bool easyar_ListOfTarget_check_external_cpp(const std::vector<std::shared_ptr<Target>> & l)
{
    for (auto e : l) {
        if (!(e != nullptr)) { return false; }
    }
    return true;
}

static inline std::shared_ptr<easyar_ListOfImage> std_vector_to_easyar_ListOfImage(std::vector<std::shared_ptr<Image>> l)
{
    std::vector<easyar_Image *> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = v->get_cdata().get();
        easyar_Image__retain(cv, &cv);
        values.push_back(cv);
    }
    easyar_ListOfImage * ptr;
    easyar_ListOfImage__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfImage>(ptr, [](easyar_ListOfImage * ptr) { easyar_ListOfImage__dtor(ptr); });
}
static inline std::vector<std::shared_ptr<Image>> std_vector_from_easyar_ListOfImage(std::shared_ptr<easyar_ListOfImage> pl)
{
    auto size = easyar_ListOfImage_size(pl.get());
    std::vector<std::shared_ptr<Image>> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfImage_at(pl.get(), k);
        easyar_Image__retain(v, &v);
        values.push_back(Image::from_cdata(std::shared_ptr<easyar_Image>(v, [](easyar_Image * ptr) { easyar_Image__dtor(ptr); })));
    }
    return values;
}
static inline bool easyar_ListOfImage_check_external_cpp(const std::vector<std::shared_ptr<Image>> & l)
{
    for (auto e : l) {
        if (!(e != nullptr)) { return false; }
    }
    return true;
}

static void FunctorOfVoidFromCloudRecognizationResult_func(void * _state, easyar_CloudRecognizationResult * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        easyar_CloudRecognizationResult__retain(arg0, &arg0);
        std::shared_ptr<CloudRecognizationResult> cpparg0 = CloudRecognizationResult::from_cdata(std::shared_ptr<easyar_CloudRecognizationResult>(arg0, [](easyar_CloudRecognizationResult * ptr) { easyar_CloudRecognizationResult__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(std::shared_ptr<CloudRecognizationResult>)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromCloudRecognizationResult_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(std::shared_ptr<CloudRecognizationResult>)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromCloudRecognizationResult FunctorOfVoidFromCloudRecognizationResult_to_c(std::function<void(std::shared_ptr<CloudRecognizationResult>)> f)
{
    return easyar_FunctorOfVoidFromCloudRecognizationResult{new std::function<void(std::shared_ptr<CloudRecognizationResult>)>(f), FunctorOfVoidFromCloudRecognizationResult_func, FunctorOfVoidFromCloudRecognizationResult_destroy};
}

static inline std::shared_ptr<easyar_ListOfBlockInfo> std_vector_to_easyar_ListOfBlockInfo(std::vector<BlockInfo> l)
{
    std::vector<easyar_BlockInfo> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = easyar_BlockInfo{v.x, v.y, v.z, v.numOfVertex, v.startPointOfVertex, v.numOfIndex, v.startPointOfIndex, v.version};
        values.push_back(cv);
    }
    easyar_ListOfBlockInfo * ptr;
    easyar_ListOfBlockInfo__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfBlockInfo>(ptr, [](easyar_ListOfBlockInfo * ptr) { easyar_ListOfBlockInfo__dtor(ptr); });
}
static inline std::vector<BlockInfo> std_vector_from_easyar_ListOfBlockInfo(std::shared_ptr<easyar_ListOfBlockInfo> pl)
{
    auto size = easyar_ListOfBlockInfo_size(pl.get());
    std::vector<BlockInfo> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfBlockInfo_at(pl.get(), k);
        values.push_back(BlockInfo{v.x, v.y, v.z, v.numOfVertex, v.startPointOfVertex, v.numOfIndex, v.startPointOfIndex, v.version});
    }
    return values;
}
static inline bool easyar_ListOfBlockInfo_check_external_cpp(const std::vector<BlockInfo> & l)
{
    return true;
}

static void FunctorOfVoidFromInputFrame_func(void * _state, easyar_InputFrame * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        easyar_InputFrame__retain(arg0, &arg0);
        std::shared_ptr<InputFrame> cpparg0 = InputFrame::from_cdata(std::shared_ptr<easyar_InputFrame>(arg0, [](easyar_InputFrame * ptr) { easyar_InputFrame__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(std::shared_ptr<InputFrame>)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromInputFrame_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(std::shared_ptr<InputFrame>)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromInputFrame FunctorOfVoidFromInputFrame_to_c(std::function<void(std::shared_ptr<InputFrame>)> f)
{
    return easyar_FunctorOfVoidFromInputFrame{new std::function<void(std::shared_ptr<InputFrame>)>(f), FunctorOfVoidFromInputFrame_func, FunctorOfVoidFromInputFrame_destroy};
}

static void FunctorOfVoidFromCameraState_func(void * _state, easyar_CameraState arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        CameraState cpparg0 = static_cast<CameraState>(arg0);
        auto f = reinterpret_cast<std::function<void(CameraState)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromCameraState_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(CameraState)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromCameraState FunctorOfVoidFromCameraState_to_c(std::function<void(CameraState)> f)
{
    return easyar_FunctorOfVoidFromCameraState{new std::function<void(CameraState)>(f), FunctorOfVoidFromCameraState_func, FunctorOfVoidFromCameraState_destroy};
}

static void FunctorOfVoidFromPermissionStatusAndString_func(void * _state, easyar_PermissionStatus arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        PermissionStatus cpparg0 = static_cast<PermissionStatus>(arg0);
        easyar_String_copy(arg1, &arg1);
        std::string cpparg1 = std_string_from_easyar_String(std::shared_ptr<easyar_String>(arg1, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(PermissionStatus, std::string)> *>(_state);
        (*f)(cpparg0, cpparg1);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromPermissionStatusAndString_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(PermissionStatus, std::string)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromPermissionStatusAndString FunctorOfVoidFromPermissionStatusAndString_to_c(std::function<void(PermissionStatus, std::string)> f)
{
    return easyar_FunctorOfVoidFromPermissionStatusAndString{new std::function<void(PermissionStatus, std::string)>(f), FunctorOfVoidFromPermissionStatusAndString_func, FunctorOfVoidFromPermissionStatusAndString_destroy};
}

static void FunctorOfVoidFromLogLevelAndString_func(void * _state, easyar_LogLevel arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        LogLevel cpparg0 = static_cast<LogLevel>(arg0);
        easyar_String_copy(arg1, &arg1);
        std::string cpparg1 = std_string_from_easyar_String(std::shared_ptr<easyar_String>(arg1, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(LogLevel, std::string)> *>(_state);
        (*f)(cpparg0, cpparg1);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromLogLevelAndString_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(LogLevel, std::string)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromLogLevelAndString FunctorOfVoidFromLogLevelAndString_to_c(std::function<void(LogLevel, std::string)> f)
{
    return easyar_FunctorOfVoidFromLogLevelAndString{new std::function<void(LogLevel, std::string)>(f), FunctorOfVoidFromLogLevelAndString_func, FunctorOfVoidFromLogLevelAndString_destroy};
}

static void FunctorOfVoidFromRecordStatusAndString_func(void * _state, easyar_RecordStatus arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        RecordStatus cpparg0 = static_cast<RecordStatus>(arg0);
        easyar_String_copy(arg1, &arg1);
        std::string cpparg1 = std_string_from_easyar_String(std::shared_ptr<easyar_String>(arg1, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(RecordStatus, std::string)> *>(_state);
        (*f)(cpparg0, cpparg1);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromRecordStatusAndString_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(RecordStatus, std::string)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromRecordStatusAndString FunctorOfVoidFromRecordStatusAndString_to_c(std::function<void(RecordStatus, std::string)> f)
{
    return easyar_FunctorOfVoidFromRecordStatusAndString{new std::function<void(RecordStatus, std::string)>(f), FunctorOfVoidFromRecordStatusAndString_func, FunctorOfVoidFromRecordStatusAndString_destroy};
}

static inline std::shared_ptr<easyar_ListOfPlaneData> std_vector_to_easyar_ListOfPlaneData(std::vector<std::shared_ptr<PlaneData>> l)
{
    std::vector<easyar_PlaneData *> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = v->get_cdata().get();
        easyar_PlaneData__retain(cv, &cv);
        values.push_back(cv);
    }
    easyar_ListOfPlaneData * ptr;
    easyar_ListOfPlaneData__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfPlaneData>(ptr, [](easyar_ListOfPlaneData * ptr) { easyar_ListOfPlaneData__dtor(ptr); });
}
static inline std::vector<std::shared_ptr<PlaneData>> std_vector_from_easyar_ListOfPlaneData(std::shared_ptr<easyar_ListOfPlaneData> pl)
{
    auto size = easyar_ListOfPlaneData_size(pl.get());
    std::vector<std::shared_ptr<PlaneData>> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfPlaneData_at(pl.get(), k);
        easyar_PlaneData__retain(v, &v);
        values.push_back(PlaneData::from_cdata(std::shared_ptr<easyar_PlaneData>(v, [](easyar_PlaneData * ptr) { easyar_PlaneData__dtor(ptr); })));
    }
    return values;
}
static inline bool easyar_ListOfPlaneData_check_external_cpp(const std::vector<std::shared_ptr<PlaneData>> & l)
{
    for (auto e : l) {
        if (!(e != nullptr)) { return false; }
    }
    return true;
}

static void FunctorOfVoidFromBool_func(void * _state, bool arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        bool cpparg0 = arg0;
        auto f = reinterpret_cast<std::function<void(bool)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromBool_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(bool)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromBool FunctorOfVoidFromBool_to_c(std::function<void(bool)> f)
{
    return easyar_FunctorOfVoidFromBool{new std::function<void(bool)>(f), FunctorOfVoidFromBool_func, FunctorOfVoidFromBool_destroy};
}

static void FunctorOfVoidFromBoolAndStringAndString_func(void * _state, bool arg0, easyar_String * arg1, easyar_String * arg2, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        bool cpparg0 = arg0;
        easyar_String_copy(arg1, &arg1);
        std::string cpparg1 = std_string_from_easyar_String(std::shared_ptr<easyar_String>(arg1, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
        easyar_String_copy(arg2, &arg2);
        std::string cpparg2 = std_string_from_easyar_String(std::shared_ptr<easyar_String>(arg2, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(bool, std::string, std::string)> *>(_state);
        (*f)(cpparg0, cpparg1, cpparg2);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromBoolAndStringAndString_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(bool, std::string, std::string)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromBoolAndStringAndString FunctorOfVoidFromBoolAndStringAndString_to_c(std::function<void(bool, std::string, std::string)> f)
{
    return easyar_FunctorOfVoidFromBoolAndStringAndString{new std::function<void(bool, std::string, std::string)>(f), FunctorOfVoidFromBoolAndStringAndString_func, FunctorOfVoidFromBoolAndStringAndString_destroy};
}

static void FunctorOfVoidFromBoolAndString_func(void * _state, bool arg0, easyar_String * arg1, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        bool cpparg0 = arg0;
        easyar_String_copy(arg1, &arg1);
        std::string cpparg1 = std_string_from_easyar_String(std::shared_ptr<easyar_String>(arg1, [](easyar_String * ptr) { easyar_String__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(bool, std::string)> *>(_state);
        (*f)(cpparg0, cpparg1);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromBoolAndString_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(bool, std::string)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromBoolAndString FunctorOfVoidFromBoolAndString_to_c(std::function<void(bool, std::string)> f)
{
    return easyar_FunctorOfVoidFromBoolAndString{new std::function<void(bool, std::string)>(f), FunctorOfVoidFromBoolAndString_func, FunctorOfVoidFromBoolAndString_destroy};
}

static void FunctorOfVoidFromVideoStatus_func(void * _state, easyar_VideoStatus arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        VideoStatus cpparg0 = static_cast<VideoStatus>(arg0);
        auto f = reinterpret_cast<std::function<void(VideoStatus)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromVideoStatus_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(VideoStatus)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromVideoStatus FunctorOfVoidFromVideoStatus_to_c(std::function<void(VideoStatus)> f)
{
    return easyar_FunctorOfVoidFromVideoStatus{new std::function<void(VideoStatus)>(f), FunctorOfVoidFromVideoStatus_func, FunctorOfVoidFromVideoStatus_destroy};
}

static void FunctorOfVoidFromFeedbackFrame_func(void * _state, easyar_FeedbackFrame * arg0, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        easyar_FeedbackFrame__retain(arg0, &arg0);
        std::shared_ptr<FeedbackFrame> cpparg0 = FeedbackFrame::from_cdata(std::shared_ptr<easyar_FeedbackFrame>(arg0, [](easyar_FeedbackFrame * ptr) { easyar_FeedbackFrame__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<void(std::shared_ptr<FeedbackFrame>)> *>(_state);
        (*f)(cpparg0);
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfVoidFromFeedbackFrame_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<void(std::shared_ptr<FeedbackFrame>)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfVoidFromFeedbackFrame FunctorOfVoidFromFeedbackFrame_to_c(std::function<void(std::shared_ptr<FeedbackFrame>)> f)
{
    return easyar_FunctorOfVoidFromFeedbackFrame{new std::function<void(std::shared_ptr<FeedbackFrame>)>(f), FunctorOfVoidFromFeedbackFrame_func, FunctorOfVoidFromFeedbackFrame_destroy};
}

static void FunctorOfOutputFrameFromListOfOutputFrame_func(void * _state, easyar_ListOfOutputFrame * arg0, /* OUT */ easyar_OutputFrame * * Return, /* OUT */ easyar_String * * _exception)
{
    *_exception = nullptr;
    try {
        easyar_ListOfOutputFrame_copy(arg0, &arg0);
        std::vector<std::shared_ptr<OutputFrame>> cpparg0 = std_vector_from_easyar_ListOfOutputFrame(std::shared_ptr<easyar_ListOfOutputFrame>(arg0, [](easyar_ListOfOutputFrame * ptr) { easyar_ListOfOutputFrame__dtor(ptr); }));
        auto f = reinterpret_cast<std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)> *>(_state);
        std::shared_ptr<OutputFrame> _return_value_ = (*f)(cpparg0);
        if (!(_return_value_ != nullptr)) {
            easyar_String_from_utf8_begin("InvalidReturnValue", _exception);
            return;
        }
        easyar_OutputFrame * _return_value_c_ = _return_value_->get_cdata().get();
        easyar_OutputFrame__retain(_return_value_c_, &_return_value_c_);
        *Return = _return_value_c_;
    } catch (std::exception & ex) {
        auto message = std::string() + typeid(*(&ex)).name() + u8"\n" + ex.what();
        easyar_String_from_utf8_begin(message.c_str(), _exception);
    }
}
static void FunctorOfOutputFrameFromListOfOutputFrame_destroy(void * _state)
{
    auto f = reinterpret_cast<std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)> *>(_state);
    delete f;
}
static inline easyar_FunctorOfOutputFrameFromListOfOutputFrame FunctorOfOutputFrameFromListOfOutputFrame_to_c(std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)> f)
{
    return easyar_FunctorOfOutputFrameFromListOfOutputFrame{new std::function<std::shared_ptr<OutputFrame>(std::vector<std::shared_ptr<OutputFrame>>)>(f), FunctorOfOutputFrameFromListOfOutputFrame_func, FunctorOfOutputFrameFromListOfOutputFrame_destroy};
}

static inline std::shared_ptr<easyar_ListOfOutputFrame> std_vector_to_easyar_ListOfOutputFrame(std::vector<std::shared_ptr<OutputFrame>> l)
{
    std::vector<easyar_OutputFrame *> values;
    values.reserve(l.size());
    for (auto v : l) {
        auto cv = v->get_cdata().get();
        easyar_OutputFrame__retain(cv, &cv);
        values.push_back(cv);
    }
    easyar_ListOfOutputFrame * ptr;
    easyar_ListOfOutputFrame__ctor(values.data(), values.data() + values.size(), &ptr);
    return std::shared_ptr<easyar_ListOfOutputFrame>(ptr, [](easyar_ListOfOutputFrame * ptr) { easyar_ListOfOutputFrame__dtor(ptr); });
}
static inline std::vector<std::shared_ptr<OutputFrame>> std_vector_from_easyar_ListOfOutputFrame(std::shared_ptr<easyar_ListOfOutputFrame> pl)
{
    auto size = easyar_ListOfOutputFrame_size(pl.get());
    std::vector<std::shared_ptr<OutputFrame>> values;
    values.reserve(size);
    for (int k = 0; k < size; k += 1) {
        auto v = easyar_ListOfOutputFrame_at(pl.get(), k);
        easyar_OutputFrame__retain(v, &v);
        values.push_back(OutputFrame::from_cdata(std::shared_ptr<easyar_OutputFrame>(v, [](easyar_OutputFrame * ptr) { easyar_OutputFrame__dtor(ptr); })));
    }
    return values;
}
static inline bool easyar_ListOfOutputFrame_check_external_cpp(const std::vector<std::shared_ptr<OutputFrame>> & l)
{
    for (auto e : l) {
        if (!(e != nullptr)) { return false; }
    }
    return true;
}

}

#endif

#undef _INLINE_SPECIFIER_
