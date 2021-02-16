//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#import <Foundation/Foundation.h>

@interface easyar_RefBase : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

@class easyar_ObjectTargetParameters;

@class easyar_ObjectTarget;

@class easyar_ObjectTrackerResult;

@class easyar_ObjectTracker;

typedef enum easyar_CloudRecognizationStatus : NSInteger
{
    /// <summary>
    /// Unknown error
    /// </summary>
    easyar_CloudRecognizationStatus_UnknownError = 0,
    /// <summary>
    /// A target is recognized.
    /// </summary>
    easyar_CloudRecognizationStatus_FoundTarget = 1,
    /// <summary>
    /// No target is recognized.
    /// </summary>
    easyar_CloudRecognizationStatus_TargetNotFound = 2,
    /// <summary>
    /// Reached the access limit
    /// </summary>
    easyar_CloudRecognizationStatus_ReachedAccessLimit = 3,
    /// <summary>
    /// Request interval too low
    /// </summary>
    easyar_CloudRecognizationStatus_RequestIntervalTooLow = 4,
} easyar_CloudRecognizationStatus;

@class easyar_CloudRecognizationResult;

@class easyar_CloudRecognizer;

@class easyar_Buffer;

@class easyar_BufferDictionary;

@class easyar_BufferPool;

typedef enum easyar_CameraDeviceType : NSInteger
{
    /// <summary>
    /// Unknown location
    /// </summary>
    easyar_CameraDeviceType_Unknown = 0,
    /// <summary>
    /// Rear camera
    /// </summary>
    easyar_CameraDeviceType_Back = 1,
    /// <summary>
    /// Front camera
    /// </summary>
    easyar_CameraDeviceType_Front = 2,
} easyar_CameraDeviceType;

/// <summary>
/// MotionTrackingStatus describes the quality of device motion tracking.
/// </summary>
typedef enum easyar_MotionTrackingStatus : NSInteger
{
    /// <summary>
    /// Result is not available and should not to be used to render virtual objects or do 3D reconstruction. This value occurs temporarily after initializing, tracking lost or relocalizing.
    /// </summary>
    easyar_MotionTrackingStatus_NotTracking = 0,
    /// <summary>
    /// Tracking is available, but the quality of the result is not good enough. This value occurs temporarily due to weak texture or excessive movement. The result can be used to render virtual objects, but should generally not be used to do 3D reconstruction.
    /// </summary>
    easyar_MotionTrackingStatus_Limited = 1,
    /// <summary>
    /// Tracking with a good quality. The result can be used to render virtual objects or do 3D reconstruction.
    /// </summary>
    easyar_MotionTrackingStatus_Tracking = 2,
} easyar_MotionTrackingStatus;

@class easyar_CameraParameters;

/// <summary>
/// PixelFormat represents the format of image pixel data. All formats follow the pixel direction from left to right and from top to bottom.
/// </summary>
typedef enum easyar_PixelFormat : NSInteger
{
    /// <summary>
    /// Unknown
    /// </summary>
    easyar_PixelFormat_Unknown = 0,
    /// <summary>
    /// 256 shades grayscale
    /// </summary>
    easyar_PixelFormat_Gray = 1,
    /// <summary>
    /// YUV_NV21
    /// </summary>
    easyar_PixelFormat_YUV_NV21 = 2,
    /// <summary>
    /// YUV_NV12
    /// </summary>
    easyar_PixelFormat_YUV_NV12 = 3,
    /// <summary>
    /// YUV_I420
    /// </summary>
    easyar_PixelFormat_YUV_I420 = 4,
    /// <summary>
    /// YUV_YV12
    /// </summary>
    easyar_PixelFormat_YUV_YV12 = 5,
    /// <summary>
    /// RGB888
    /// </summary>
    easyar_PixelFormat_RGB888 = 6,
    /// <summary>
    /// BGR888
    /// </summary>
    easyar_PixelFormat_BGR888 = 7,
    /// <summary>
    /// RGBA8888
    /// </summary>
    easyar_PixelFormat_RGBA8888 = 8,
    /// <summary>
    /// BGRA8888
    /// </summary>
    easyar_PixelFormat_BGRA8888 = 9,
} easyar_PixelFormat;

@class easyar_Image;

@class easyar_Matrix44F;

@class easyar_Matrix33F;

@class easyar_Vec4F;

@class easyar_Vec3F;

@class easyar_Vec2F;

@class easyar_Vec4I;

@class easyar_Vec2I;

@class easyar_DenseSpatialMap;

@class easyar_BlockInfo;

@class easyar_SceneMesh;

@class easyar_ARCoreCameraDevice;

@class easyar_ARKitCameraDevice;

typedef enum easyar_CameraDeviceFocusMode : NSInteger
{
    /// <summary>
    /// Normal auto focus mode. You should call autoFocus to start the focus in this mode.
    /// </summary>
    easyar_CameraDeviceFocusMode_Normal = 0,
    /// <summary>
    /// Continuous auto focus mode
    /// </summary>
    easyar_CameraDeviceFocusMode_Continousauto = 2,
    /// <summary>
    /// Infinity focus mode
    /// </summary>
    easyar_CameraDeviceFocusMode_Infinity = 3,
    /// <summary>
    /// Macro (close-up) focus mode. You should call autoFocus to start the focus in this mode.
    /// </summary>
    easyar_CameraDeviceFocusMode_Macro = 4,
    /// <summary>
    /// Medium distance focus mode
    /// </summary>
    easyar_CameraDeviceFocusMode_Medium = 5,
} easyar_CameraDeviceFocusMode;

typedef enum easyar_AndroidCameraApiType : NSInteger
{
    /// <summary>
    /// Android Camera1
    /// </summary>
    easyar_AndroidCameraApiType_Camera1 = 0,
    /// <summary>
    /// Android Camera2
    /// </summary>
    easyar_AndroidCameraApiType_Camera2 = 1,
} easyar_AndroidCameraApiType;

typedef enum easyar_CameraDevicePresetProfile : NSInteger
{
    /// <summary>
    /// The same as AVCaptureSessionPresetPhoto.
    /// </summary>
    easyar_CameraDevicePresetProfile_Photo = 0,
    /// <summary>
    /// The same as AVCaptureSessionPresetHigh.
    /// </summary>
    easyar_CameraDevicePresetProfile_High = 1,
    /// <summary>
    /// The same as AVCaptureSessionPresetMedium.
    /// </summary>
    easyar_CameraDevicePresetProfile_Medium = 2,
    /// <summary>
    /// The same as AVCaptureSessionPresetLow.
    /// </summary>
    easyar_CameraDevicePresetProfile_Low = 3,
} easyar_CameraDevicePresetProfile;

typedef enum easyar_CameraState : NSInteger
{
    /// <summary>
    /// Unknown
    /// </summary>
    easyar_CameraState_Unknown = 0x00000000,
    /// <summary>
    /// Disconnected
    /// </summary>
    easyar_CameraState_Disconnected = 0x00000001,
    /// <summary>
    /// Preempted by another application.
    /// </summary>
    easyar_CameraState_Preempted = 0x00000002,
} easyar_CameraState;

@class easyar_CameraDevice;

typedef enum easyar_CameraDevicePreference : NSInteger
{
    /// <summary>
    /// Optimized for `ImageTracker`_ , `ObjectTracker`_ and `CloudRecognizer`_ .
    /// </summary>
    easyar_CameraDevicePreference_PreferObjectSensing = 0,
    /// <summary>
    /// Optimized for `SurfaceTracker`_ .
    /// </summary>
    easyar_CameraDevicePreference_PreferSurfaceTracking = 1,
    /// <summary>
    /// Optimized for Motion Tracking .
    /// </summary>
    easyar_CameraDevicePreference_PreferMotionTracking = 2,
} easyar_CameraDevicePreference;

@class easyar_CameraDeviceSelector;

@class easyar_SurfaceTrackerResult;

@class easyar_SurfaceTracker;

@class easyar_MotionTrackerCameraDevice;

@class easyar_InputFrameRecorder;

@class easyar_InputFramePlayer;

@class easyar_CallbackScheduler;

@class easyar_DelayedCallbackScheduler;

@class easyar_ImmediateCallbackScheduler;

@class easyar_JniUtility;

typedef enum easyar_LogLevel : NSInteger
{
    /// <summary>
    /// Error
    /// </summary>
    easyar_LogLevel_Error = 0,
    /// <summary>
    /// Warning
    /// </summary>
    easyar_LogLevel_Warning = 1,
    /// <summary>
    /// Information
    /// </summary>
    easyar_LogLevel_Info = 2,
} easyar_LogLevel;

@class easyar_Log;

@class easyar_ImageTargetParameters;

@class easyar_ImageTarget;

typedef enum easyar_ImageTrackerMode : NSInteger
{
    /// <summary>
    /// Quality is preferred.
    /// </summary>
    easyar_ImageTrackerMode_PreferQuality = 0,
    /// <summary>
    /// Performance is preferred.
    /// </summary>
    easyar_ImageTrackerMode_PreferPerformance = 1,
} easyar_ImageTrackerMode;

@class easyar_ImageTrackerResult;

@class easyar_ImageTracker;

@class easyar_Recorder;

typedef enum easyar_RecordProfile : NSInteger
{
    /// <summary>
    /// 1080P, low quality
    /// </summary>
    easyar_RecordProfile_Quality_1080P_Low = 0x00000001,
    /// <summary>
    /// 1080P, middle quality
    /// </summary>
    easyar_RecordProfile_Quality_1080P_Middle = 0x00000002,
    /// <summary>
    /// 1080P, high quality
    /// </summary>
    easyar_RecordProfile_Quality_1080P_High = 0x00000004,
    /// <summary>
    /// 720P, low quality
    /// </summary>
    easyar_RecordProfile_Quality_720P_Low = 0x00000008,
    /// <summary>
    /// 720P, middle quality
    /// </summary>
    easyar_RecordProfile_Quality_720P_Middle = 0x00000010,
    /// <summary>
    /// 720P, high quality
    /// </summary>
    easyar_RecordProfile_Quality_720P_High = 0x00000020,
    /// <summary>
    /// 480P, low quality
    /// </summary>
    easyar_RecordProfile_Quality_480P_Low = 0x00000040,
    /// <summary>
    /// 480P, middle quality
    /// </summary>
    easyar_RecordProfile_Quality_480P_Middle = 0x00000080,
    /// <summary>
    /// 480P, high quality
    /// </summary>
    easyar_RecordProfile_Quality_480P_High = 0x00000100,
    /// <summary>
    /// default resolution and quality, same as `Quality_720P_Middle`
    /// </summary>
    easyar_RecordProfile_Quality_Default = 0x00000010,
} easyar_RecordProfile;

typedef enum easyar_RecordVideoSize : NSInteger
{
    /// <summary>
    /// 1080P
    /// </summary>
    easyar_RecordVideoSize_Vid1080p = 0x00000002,
    /// <summary>
    /// 720P
    /// </summary>
    easyar_RecordVideoSize_Vid720p = 0x00000010,
    /// <summary>
    /// 480P
    /// </summary>
    easyar_RecordVideoSize_Vid480p = 0x00000080,
} easyar_RecordVideoSize;

typedef enum easyar_RecordZoomMode : NSInteger
{
    /// <summary>
    /// If output aspect ratio does not fit input, content will be clipped to fit output aspect ratio.
    /// </summary>
    easyar_RecordZoomMode_NoZoomAndClip = 0x00000000,
    /// <summary>
    /// If output aspect ratio does not fit input, content will not be clipped and there will be black borders in one dimension.
    /// </summary>
    easyar_RecordZoomMode_ZoomInWithAllContent = 0x00000001,
} easyar_RecordZoomMode;

typedef enum easyar_RecordVideoOrientation : NSInteger
{
    /// <summary>
    /// video recorded is landscape
    /// </summary>
    easyar_RecordVideoOrientation_Landscape = 0x00000000,
    /// <summary>
    /// video recorded is portrait
    /// </summary>
    easyar_RecordVideoOrientation_Portrait = 0x00000001,
} easyar_RecordVideoOrientation;

typedef enum easyar_RecordStatus : NSInteger
{
    /// <summary>
    /// recording start
    /// </summary>
    easyar_RecordStatus_OnStarted = 0x00000002,
    /// <summary>
    /// recording stopped
    /// </summary>
    easyar_RecordStatus_OnStopped = 0x00000004,
    /// <summary>
    /// start fail
    /// </summary>
    easyar_RecordStatus_FailedToStart = 0x00000202,
    /// <summary>
    /// file write succeed
    /// </summary>
    easyar_RecordStatus_FileSucceeded = 0x00000400,
    /// <summary>
    /// file write fail
    /// </summary>
    easyar_RecordStatus_FileFailed = 0x00000401,
    /// <summary>
    /// runtime info with description
    /// </summary>
    easyar_RecordStatus_LogInfo = 0x00000800,
    /// <summary>
    /// runtime error with description
    /// </summary>
    easyar_RecordStatus_LogError = 0x00001000,
} easyar_RecordStatus;

@class easyar_RecorderConfiguration;

@class easyar_SparseSpatialMapResult;

typedef enum easyar_PlaneType : NSInteger
{
    /// <summary>
    /// Horizontal plane
    /// </summary>
    easyar_PlaneType_Horizontal = 0,
    /// <summary>
    /// Vertical plane
    /// </summary>
    easyar_PlaneType_Vertical = 1,
} easyar_PlaneType;

@class easyar_PlaneData;

typedef enum easyar_LocalizationMode : NSInteger
{
    /// <summary>
    /// Attempt to perform localization in current SparseSpatialMap until success.
    /// </summary>
    easyar_LocalizationMode_UntilSuccess = 0,
    /// <summary>
    /// Perform localization only once
    /// </summary>
    easyar_LocalizationMode_Once = 1,
    /// <summary>
    /// Keep performing localization and adjust result on success
    /// </summary>
    easyar_LocalizationMode_KeepUpdate = 2,
    /// <summary>
    /// Keep performing localization and adjust localization result only when localization returns different map ID from previous results
    /// </summary>
    easyar_LocalizationMode_ContinousLocalize = 3,
} easyar_LocalizationMode;

@class easyar_SparseSpatialMapConfig;

@class easyar_SparseSpatialMap;

@class easyar_SparseSpatialMapManager;

@class easyar_Engine;

typedef enum easyar_VideoStatus : NSInteger
{
    /// <summary>
    /// Status to indicate something wrong happen in video open or play.
    /// </summary>
    easyar_VideoStatus_Error = -1,
    /// <summary>
    /// Status to show video finished open and is ready for play.
    /// </summary>
    easyar_VideoStatus_Ready = 0,
    /// <summary>
    /// Status to indicate video finished play and reached the end.
    /// </summary>
    easyar_VideoStatus_Completed = 1,
} easyar_VideoStatus;

typedef enum easyar_VideoType : NSInteger
{
    /// <summary>
    /// Normal video.
    /// </summary>
    easyar_VideoType_Normal = 0,
    /// <summary>
    /// Transparent video, left half is the RGB channel and right half is alpha channel.
    /// </summary>
    easyar_VideoType_TransparentSideBySide = 1,
    /// <summary>
    /// Transparent video, top half is the RGB channel and bottom half is alpha channel.
    /// </summary>
    easyar_VideoType_TransparentTopAndBottom = 2,
} easyar_VideoType;

@class easyar_VideoPlayer;

@class easyar_ImageHelper;

@class easyar_SignalSink;

@class easyar_SignalSource;

@class easyar_InputFrameSink;

@class easyar_InputFrameSource;

@class easyar_OutputFrameSink;

@class easyar_OutputFrameSource;

@class easyar_FeedbackFrameSink;

@class easyar_FeedbackFrameSource;

@class easyar_InputFrameFork;

@class easyar_OutputFrameFork;

@class easyar_OutputFrameJoin;

@class easyar_FeedbackFrameFork;

@class easyar_InputFrameThrottler;

@class easyar_OutputFrameBuffer;

@class easyar_InputFrameToOutputFrameAdapter;

@class easyar_InputFrameToFeedbackFrameAdapter;

@class easyar_InputFrame;

@class easyar_FrameFilterResult;

@class easyar_OutputFrame;

@class easyar_FeedbackFrame;

typedef enum easyar_PermissionStatus : NSInteger
{
    /// <summary>
    /// Permission granted
    /// </summary>
    easyar_PermissionStatus_Granted = 0x00000000,
    /// <summary>
    /// Permission denied
    /// </summary>
    easyar_PermissionStatus_Denied = 0x00000001,
    /// <summary>
    /// A error happened while requesting permission.
    /// </summary>
    easyar_PermissionStatus_Error = 0x00000002,
} easyar_PermissionStatus;

/// <summary>
/// StorageType represents where the images, jsons, videos or other files are located.
/// StorageType specifies the root path, in all interfaces, you can use relative path relative to the root path.
/// </summary>
typedef enum easyar_StorageType : NSInteger
{
    /// <summary>
    /// The app path.
    /// Android: the application&#39;s `persistent data directory &lt;https://developer.android.google.cn/reference/android/content/pm/ApplicationInfo.html#dataDir&gt;`__
    /// iOS: the application&#39;s sandbox directory
    /// Windows: Windows: the application&#39;s executable directory
    /// Mac: the application’s executable directory (if app is a bundle, this path is inside the bundle)
    /// </summary>
    easyar_StorageType_App = 0,
    /// <summary>
    /// The assets path.
    /// Android: assets directory (inside apk)
    /// iOS: the application&#39;s executable directory
    /// Windows: EasyAR.dll directory
    /// Mac: libEasyAR.dylib directory
    /// **Note:** *this path is different if you are using Unity3D. It will point to the StreamingAssets folder.*
    /// </summary>
    easyar_StorageType_Assets = 1,
    /// <summary>
    /// The absolute path (json/image path or video path) or url (video only).
    /// </summary>
    easyar_StorageType_Absolute = 2,
} easyar_StorageType;

@class easyar_Target;

typedef enum easyar_TargetStatus : NSInteger
{
    /// <summary>
    /// The status is unknown.
    /// </summary>
    easyar_TargetStatus_Unknown = 0,
    /// <summary>
    /// The status is undefined.
    /// </summary>
    easyar_TargetStatus_Undefined = 1,
    /// <summary>
    /// The target is detected.
    /// </summary>
    easyar_TargetStatus_Detected = 2,
    /// <summary>
    /// The target is tracked.
    /// </summary>
    easyar_TargetStatus_Tracked = 3,
} easyar_TargetStatus;

@class easyar_TargetInstance;

@class easyar_TargetTrackerResult;

@class easyar_TextureId;
