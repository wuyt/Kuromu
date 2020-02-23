//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TYPES_H__
#define __EASYAR_TYPES_H__

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { char _placeHolder_; } easyar_String;
void easyar_String_from_utf8(const char * begin, const char * end, /* OUT */ easyar_String * * Return);
void easyar_String_from_utf8_begin(const char * begin, /* OUT */ easyar_String * * Return);
const char * easyar_String_begin(const easyar_String * This);
const char * easyar_String_end(const easyar_String * This);
void easyar_String_copy(const easyar_String * This, /* OUT */ easyar_String * * Return);
void easyar_String__dtor(easyar_String * This);

/// <summary>
/// class
/// ObjectTargetParameters represents the parameters to create a `ObjectTarget`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ObjectTargetParameters;

/// <summary>
/// class
/// extends Target
/// ObjectTarget represents 3d object targets that can be tracked by `ObjectTracker`_ .
/// The size of ObjectTarget is determined by the `obj` file. You can change it by changing the object `scale`, which is default to 1.
/// A ObjectTarget should be setup using setup before any value is valid. And ObjectTarget can be tracked by `ObjectTracker`_ after a successful load into the `ObjectTracker`_ using `ObjectTracker.loadTarget`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ObjectTarget;

/// <summary>
/// class
/// extends TargetTrackerResult
/// Result of `ObjectTracker`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ObjectTrackerResult;

/// <summary>
/// class
/// ObjectTracker implements 3D object target detection and tracking.
/// ObjectTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ObjectTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// Before a `Target`_ can be tracked by ObjectTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
/// </summary>
typedef struct { char _placeHolder_; } easyar_ObjectTracker;

typedef enum
{
    /// <summary>
    /// Targets are recognized.
    /// </summary>
    easyar_CloudStatus_FoundTargets = 0,
    /// <summary>
    /// No targets are recognized.
    /// </summary>
    easyar_CloudStatus_TargetsNotFound = 1,
    /// <summary>
    /// Connection broke and auto reconnecting
    /// </summary>
    easyar_CloudStatus_Reconnecting = 2,
    /// <summary>
    /// Protocol error
    /// </summary>
    easyar_CloudStatus_ProtocolError = 3,
} easyar_CloudStatus;

/// <summary>
/// class
/// CloudRecognizer implements cloud recognition. It can only be used after created a recognition image library on the cloud. Please refer to EasyAR CRS documentation.
/// CloudRecognizer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable running.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// CloudRecognizer inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// Before using a CloudRecognizer, an `ImageTracker`_ must be setup and prepared. Any target returned from cloud should be manually put into the `ImageTracker`_ using `ImageTracker.loadTarget`_ if it need to be tracked. Then the target can be used as same as a local target after loaded into the tracker. When a target is recognized, you can get it from callback, and you should use target uid to distinguish different targets. The target runtimeID is dynamically created and cannot be used as unique identifier in the cloud situation.
/// </summary>
typedef struct { char _placeHolder_; } easyar_CloudRecognizer;

/// <summary>
/// class
/// DenseSpatialMap is used to reconstruct the environment accurately and densely. The reconstructed model is represented by `triangle mesh`, which is denoted simply by `mesh`.
/// DenseSpatialMap occupies 1 buffers of camera.
/// </summary>
typedef struct { char _placeHolder_; } easyar_DenseSpatialMap;

/// <summary>
/// record
/// The dense reconstructed model is represented by triangle mesh, or simply denoted as mesh. Because mesh updates frequently, in order to ensure efficiency, the mesh of the whole reconstruction model is divided into many mesh blocks. A mesh block is composed of a cube about 1 meter long, with attributes such as vertices and indices.
///
/// BlockInfo is used to describe the content of a mesh block. (x, y, z) is the index of mesh block, the coordinates of a mesh block&#39;s origin in world coordinate system can be obtained by  multiplying (x, y, z) by the physical size of mesh block. You may filter the part you want to display in advance by the mesh block&#39;s world coordinates for the sake of saving rendering time.
/// </summary>
typedef struct
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
} easyar_BlockInfo;

/// <summary>
/// class
/// SceneMesh is used to manage and preserve the results of `DenseSpatialMap`_.
/// There are two kinds of meshes saved in SceneMesh, one is the mesh of the whole reconstructed scene, hereinafter referred to as `meshAll`, the other is the recently updated mesh, hereinafter referred to as `meshUpdated`. `meshAll` is a whole mesh, including all vertex data and index data, etc. `meshUpdated` is composed of several `mesh block` s, each `mesh block` is a cube, which contains the mesh formed by the object surface in the corresponding cube space.
/// `meshAll` is available only when the `DenseSpatialMap.updateSceneMesh`_ method is called specifying that all meshes need to be updated. If `meshAll` has been updated previously and not updated in recent times, the data in `meshAll` is remain the same.
/// </summary>
typedef struct { char _placeHolder_; } easyar_SceneMesh;

/// <summary>
/// class
/// extends FrameFilterResult
/// Result of `SurfaceTracker`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_SurfaceTrackerResult;

/// <summary>
/// class
/// SurfaceTracker implements tracking with environmental surfaces.
/// SurfaceTracker occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// SurfaceTracker inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_SurfaceTracker;

/// <summary>
/// class
/// MotionTrackerCameraDevice implements a camera device with metric-scale six degree-of-freedom motion tracking, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF pose and tracking status).
/// After creation, start/stop can be invoked to start or stop data flow.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// MotionTrackerCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for further use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_MotionTrackerCameraDevice;

/// <summary>
/// class
/// ImageTargetParameters represents the parameters to create a `ImageTarget`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ImageTargetParameters;

/// <summary>
/// class
/// extends Target
/// ImageTarget represents planar image targets that can be tracked by `ImageTracker`_ .
/// The fields of ImageTarget need to be filled with the create.../setupAll method before it can be read. And ImageTarget can be tracked by `ImageTracker`_ after a successful load into the `ImageTracker`_ using `ImageTracker.loadTarget`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ImageTarget;

typedef enum
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

/// <summary>
/// class
/// extends TargetTrackerResult
/// Result of `ImageTracker`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ImageTrackerResult;

/// <summary>
/// class
/// ImageTracker implements image target detection and tracking.
/// ImageTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ImageTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// Before a `Target`_ can be tracked by ImageTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
/// </summary>
typedef struct { char _placeHolder_; } easyar_ImageTracker;

/// <summary>
/// class
/// Recorder implements recording for current rendering screen.
/// Currently Recorder only works on Android (4.3 or later) and iOS with OpenGL ES 2.0 context.
/// Due to the dependency to OpenGLES, every method in this class (except requestPermissions, including the destructor) has to be called in a single thread containing an OpenGLES context.
/// **Unity Only** If in Unity, Multi-threaded rendering is enabled, scripting thread and rendering thread will be two separate threads, which makes it impossible to call updateFrame in the rendering thread. For this reason, to use Recorder, Multi-threaded rendering option shall be disabled.
/// </summary>
typedef struct { char _placeHolder_; } easyar_Recorder;

typedef enum
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

typedef enum
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

typedef enum
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

typedef enum
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

typedef enum
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

/// <summary>
/// class
/// RecorderConfiguration is startup configuration for `Recorder`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_RecorderConfiguration;

/// <summary>
/// class
/// extends FrameFilterResult
/// Describes the result of mapping and localization. Updated at the same frame rate with OutputFrame.
/// </summary>
typedef struct { char _placeHolder_; } easyar_SparseSpatialMapResult;

typedef enum
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

/// <summary>
/// class
/// </summary>
typedef struct { char _placeHolder_; } easyar_PlaneData;

typedef enum
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

/// <summary>
/// class
/// Configuration used to set the localization mode.
/// </summary>
typedef struct { char _placeHolder_; } easyar_SparseSpatialMapConfig;

/// <summary>
/// class
/// Provides core components for SparseSpatialMap, can be used for sparse spatial map building as well as localization using existing map. Also provides utilities for point cloud and plane access.
/// SparseSpatialMap occupies 2 buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_SparseSpatialMap;

/// <summary>
/// class
/// SparseSpatialMap manager class, for managing sharing.
/// </summary>
typedef struct { char _placeHolder_; } easyar_SparseSpatialMapManager;

/// <summary>
/// class
/// Image helper class.
/// </summary>
typedef struct { char _placeHolder_; } easyar_ImageHelper;

/// <summary>
/// class
/// ARCoreCameraDevice implements a camera device based on ARCore, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// Loading of libarcore_sdk_c.so with java.lang.System.loadLibrary is required.
/// After creation, start/stop can be invoked to start or stop video stream capture.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARCoreCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// Caution: Currently, ARCore(v1.13.0) has memory leaks on creating and destroying sessions. Repeated creations and destructions will cause an increasing and non-reclaimable memory footprint.
/// </summary>
typedef struct { char _placeHolder_; } easyar_ARCoreCameraDevice;

/// <summary>
/// class
/// ARKitCameraDevice implements a camera device based on ARKit, which outputs `InputFrame`_ (including image, camera parameters, timestamp, 6DOF location, and tracking status).
/// After creation, start/stop can be invoked to start or stop data collection.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// ARKitCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_ARKitCameraDevice;

/// <summary>
/// class
/// Callback scheduler.
/// There are two subclasses: `DelayedCallbackScheduler`_ and `ImmediateCallbackScheduler`_ .
/// `DelayedCallbackScheduler`_ is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// `ImmediateCallbackScheduler`_ is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// </summary>
typedef struct { char _placeHolder_; } easyar_CallbackScheduler;

/// <summary>
/// class
/// extends CallbackScheduler
/// Delayed callback scheduler.
/// It is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_DelayedCallbackScheduler;

/// <summary>
/// class
/// extends CallbackScheduler
/// Immediate callback scheduler.
/// It is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_ImmediateCallbackScheduler;

typedef enum
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

typedef enum
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

typedef enum
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

typedef enum
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

/// <summary>
/// class
/// CameraDevice implements a camera device, which outputs `InputFrame`_ (including image, camera paramters, and timestamp). It is available on Windows, Mac, Android and iOS.
/// After open, start/stop can be invoked to start or stop data collection. start/stop will not change previous set camera parameters.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// CameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_CameraDevice;

typedef enum
{
    /// <summary>
    /// Optimized for `ImageTracker`_ , `ObjectTracker`_ and `CloudRecognizer`_ .
    /// </summary>
    easyar_CameraDevicePreference_PreferObjectSensing = 0,
    /// <summary>
    /// Optimized for `SurfaceTracker`_ .
    /// </summary>
    easyar_CameraDevicePreference_PreferSurfaceTracking = 1,
} easyar_CameraDevicePreference;

/// <summary>
/// class
/// It is used for selecting camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
/// Different preferences will choose camera1 or camera2 based on usage.
/// </summary>
typedef struct { char _placeHolder_; } easyar_CameraDeviceSelector;

/// <summary>
/// class
/// Signal input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_SignalSink;

/// <summary>
/// class
/// Signal output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_SignalSource;

/// <summary>
/// class
/// Input frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrameSink;

/// <summary>
/// class
/// Input frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrameSource;

/// <summary>
/// class
/// Output frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_OutputFrameSink;

/// <summary>
/// class
/// Output frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_OutputFrameSource;

/// <summary>
/// class
/// Feedback frame input port.
/// It is used to expose input port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_FeedbackFrameSink;

/// <summary>
/// class
/// Feedback frame output port.
/// It is used to expose output port for a component.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_FeedbackFrameSource;

/// <summary>
/// class
/// Input frame fork.
/// It is used to branch and transfer input frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrameFork;

/// <summary>
/// class
/// Output frame fork.
/// It is used to branch and transfer output frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_OutputFrameFork;

/// <summary>
/// class
/// Output frame join.
/// It is used to aggregate output frame from multiple components in parallel.
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to the inputs shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
typedef struct { char _placeHolder_; } easyar_OutputFrameJoin;

/// <summary>
/// class
/// Feedback frame fork.
/// It is used to branch and transfer feedback frame to multiple components in parallel.
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_FeedbackFrameFork;

/// <summary>
/// class
/// Input frame throttler.
/// There is a input frame input port and a input frame output port. It can be used to prevent incoming frames from entering algorithm components when they have not finished handling previous workload.
/// InputFrameThrottler occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// All members of this class is thread-safe.
/// It shall be noticed that connections and disconnections to signalInput shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrameThrottler;

/// <summary>
/// class
/// Output frame buffer.
/// There is an output frame input port and output frame fetching function. It can be used to convert output frame fetching from asynchronous pattern to synchronous polling pattern, which fits frame by frame rendering.
/// OutputFrameBuffer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_OutputFrameBuffer;

/// <summary>
/// class
/// Input frame to output frame adapter.
/// There is an input frame input port and an output frame output port. It can be used to wrap an input frame into an output frame, which can be used for rendering without an algorithm component. Refer to `Overview &lt;Overview.html&gt;`_ .
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrameToOutputFrameAdapter;

/// <summary>
/// class
/// Input frame to feedback frame adapter.
/// There is an input frame input port, a historic output frame input port and a feedback frame output port. It can be used to combine an input frame and a historic output frame into a feedback frame, which is required by algorithm components such as `ImageTracker`_ .
/// On every input of an input frame, a feedback frame is generated with a previously input historic feedback frame. If there is no previously input historic feedback frame, it is null in the feedback frame.
/// InputFrameToFeedbackFrameAdapter occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview &lt;Overview.html&gt;`_ .
/// All members of this class is thread-safe.
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrameToFeedbackFrameAdapter;

/// <summary>
/// class
/// </summary>
typedef struct { char _placeHolder_; } easyar_Engine;

/// <summary>
/// class
/// Input frame.
/// It includes image, camera parameters, timestamp, camera transform matrix against world coordinate system, and tracking status,
/// among which, camera parameters, timestamp, camera transform matrix and tracking status are all optional, but specific algorithms may have special requirements on the input.
/// </summary>
typedef struct { char _placeHolder_; } easyar_InputFrame;

/// <summary>
/// class
/// FrameFilterResult is the base class for result classes of all synchronous algorithm components.
/// </summary>
typedef struct { char _placeHolder_; } easyar_FrameFilterResult;

/// <summary>
/// class
/// Output frame.
/// It includes input frame and results of synchronous components.
/// </summary>
typedef struct { char _placeHolder_; } easyar_OutputFrame;

/// <summary>
/// class
/// Feedback frame.
/// It includes an input frame and a historic output frame for use in feedback synchronous components such as `ImageTracker`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_FeedbackFrame;

typedef enum
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
typedef enum
{
    /// <summary>
    /// The app path.
    /// Android: the application&#39;s `persistent data directory &lt;https://developer.android.google.cn/reference/android/content/pm/ApplicationInfo.html#dataDir&gt;`_
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

/// <summary>
/// class
/// Target is the base class for all targets that can be tracked by `ImageTracker`_ or other algorithms inside EasyAR.
/// </summary>
typedef struct { char _placeHolder_; } easyar_Target;

typedef enum
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

/// <summary>
/// class
/// TargetInstance is the tracked target by trackers.
/// An TargetInstance contains a raw `Target`_ that is tracked and current status and pose of the `Target`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_TargetInstance;

/// <summary>
/// class
/// extends FrameFilterResult
/// TargetTrackerResult is the base class of `ImageTrackerResult`_ and `ObjectTrackerResult`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_TargetTrackerResult;

/// <summary>
/// class
/// TextureId encapsulates a texture object in rendering API.
/// For OpenGL/OpenGLES, getInt and fromInt shall be used. For Direct3D, getPointer and fromPointer shall be used.
/// </summary>
typedef struct { char _placeHolder_; } easyar_TextureId;

typedef enum
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

typedef enum
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

/// <summary>
/// class
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
typedef struct { char _placeHolder_; } easyar_VideoPlayer;

/// <summary>
/// class
/// Buffer stores a raw byte array, which can be used to access image data.
/// To access image data in Java API, get buffer from `Image`_ and copy to a Java byte array.
/// You can always access image data since the first version of EasyAR Sense. Refer to `Image`_ .
/// </summary>
typedef struct { char _placeHolder_; } easyar_Buffer;

/// <summary>
/// class
/// A mapping from file path to `Buffer`_ . It can be used to represent multiple files in the memory.
/// </summary>
typedef struct { char _placeHolder_; } easyar_BufferDictionary;

/// <summary>
/// class
/// BufferPool is a memory pool to reduce memory allocation time consumption for functionality like custom camera interoperability, which needs to allocate memory buffers of a fixed size repeatedly.
/// </summary>
typedef struct { char _placeHolder_; } easyar_BufferPool;

typedef enum
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
typedef enum
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

/// <summary>
/// class
/// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation.
/// </summary>
typedef struct { char _placeHolder_; } easyar_CameraParameters;

/// <summary>
/// PixelFormat represents the format of image pixel data. All formats follow the pixel direction from left to right and from top to bottom.
/// </summary>
typedef enum
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

/// <summary>
/// class
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
typedef struct { char _placeHolder_; } easyar_Image;

/// <summary>
/// class
/// JNI utility class.
/// It is used in Unity to wrap Java byte array and ByteBuffer.
/// It is not supported on iOS.
/// </summary>
typedef struct { char _placeHolder_; } easyar_JniUtility;

typedef enum
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

/// <summary>
/// class
/// Log class.
/// It is used to setup a custom log output function.
/// </summary>
typedef struct { char _placeHolder_; } easyar_Log;

/// <summary>
/// record
/// Square matrix of 4. The data arrangement is row-major.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of matrix.
    /// </summary>
    float data[16];
} easyar_Matrix44F;

/// <summary>
/// record
/// Square matrix of 3. The data arrangement is row-major.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of matrix.
    /// </summary>
    float data[9];
} easyar_Matrix33F;

/// <summary>
/// record
/// 4 dimensional vector of float.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    float data[4];
} easyar_Vec4F;

/// <summary>
/// record
/// 3 dimensional vector of float.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    float data[3];
} easyar_Vec3F;

/// <summary>
/// record
/// 2 dimensional vector of float.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    float data[2];
} easyar_Vec2F;

/// <summary>
/// record
/// 4 dimensional vector of int.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    int data[4];
} easyar_Vec4I;

/// <summary>
/// record
/// 2 dimensional vector of int.
/// </summary>
typedef struct
{
    /// <summary>
    /// The raw data of vector.
    /// </summary>
    int data[2];
} easyar_Vec2I;

typedef struct { bool has_value; easyar_Buffer * value; } easyar_OptionalOfBuffer;

typedef struct
{
    void * _state;
    void (* func)(void * _state, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoid;

typedef struct { bool has_value; easyar_ObjectTarget * value; } easyar_OptionalOfObjectTarget;

typedef struct { char _placeHolder_; } easyar_ListOfObjectTarget;

typedef struct { char _placeHolder_; } easyar_ListOfVec3F;

typedef struct { char _placeHolder_; } easyar_ListOfTargetInstance;

typedef struct { bool has_value; easyar_Target * value; } easyar_OptionalOfTarget;

typedef struct { bool has_value; easyar_OutputFrame * value; } easyar_OptionalOfOutputFrame;

typedef struct { bool has_value; easyar_FrameFilterResult * value; } easyar_OptionalOfFrameFilterResult;

typedef struct { char _placeHolder_; } easyar_ListOfOptionalOfFrameFilterResult;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_OutputFrame *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromOutputFrame;

typedef struct { bool has_value; easyar_FunctorOfVoidFromOutputFrame value; } easyar_OptionalOfFunctorOfVoidFromOutputFrame;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_Target *, bool, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromTargetAndBool;

typedef struct { char _placeHolder_; } easyar_ListOfTarget;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_CloudStatus, easyar_ListOfTarget *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromCloudStatusAndListOfTarget;

typedef struct { bool has_value; easyar_FunctorOfVoidFromCloudStatusAndListOfTarget value; } easyar_OptionalOfFunctorOfVoidFromCloudStatusAndListOfTarget;

typedef struct { char _placeHolder_; } easyar_ListOfBlockInfo;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_InputFrame *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromInputFrame;

typedef struct { bool has_value; easyar_FunctorOfVoidFromInputFrame value; } easyar_OptionalOfFunctorOfVoidFromInputFrame;

typedef struct { bool has_value; easyar_ImageTarget * value; } easyar_OptionalOfImageTarget;

typedef struct { char _placeHolder_; } easyar_ListOfImageTarget;

typedef struct { char _placeHolder_; } easyar_ListOfImage;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_PermissionStatus, easyar_String *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromPermissionStatusAndString;

typedef struct { bool has_value; easyar_FunctorOfVoidFromPermissionStatusAndString value; } easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_RecordStatus, easyar_String *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromRecordStatusAndString;

typedef struct { bool has_value; easyar_FunctorOfVoidFromRecordStatusAndString value; } easyar_OptionalOfFunctorOfVoidFromRecordStatusAndString;

typedef struct { bool has_value; easyar_Matrix44F value; } easyar_OptionalOfMatrix44F;

typedef struct { char _placeHolder_; } easyar_ListOfPlaneData;

typedef struct
{
    void * _state;
    void (* func)(void * _state, bool, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromBool;

typedef struct { bool has_value; easyar_FunctorOfVoidFromBool value; } easyar_OptionalOfFunctorOfVoidFromBool;

typedef struct { bool has_value; easyar_Image * value; } easyar_OptionalOfImage;

typedef struct
{
    void * _state;
    void (* func)(void * _state, bool, easyar_String *, easyar_String *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromBoolAndStringAndString;

typedef struct
{
    void * _state;
    void (* func)(void * _state, bool, easyar_String *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromBoolAndString;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_CameraState, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromCameraState;

typedef struct { bool has_value; easyar_FunctorOfVoidFromCameraState value; } easyar_OptionalOfFunctorOfVoidFromCameraState;

typedef struct { bool has_value; easyar_FunctorOfVoid value; } easyar_OptionalOfFunctorOfVoid;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_FeedbackFrame *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromFeedbackFrame;

typedef struct { bool has_value; easyar_FunctorOfVoidFromFeedbackFrame value; } easyar_OptionalOfFunctorOfVoidFromFeedbackFrame;

typedef struct { char _placeHolder_; } easyar_ListOfOutputFrame;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_ListOfOutputFrame *, /* OUT */ easyar_OutputFrame * *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfOutputFrameFromListOfOutputFrame;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_VideoStatus, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromVideoStatus;

typedef struct { bool has_value; easyar_FunctorOfVoidFromVideoStatus value; } easyar_OptionalOfFunctorOfVoidFromVideoStatus;

typedef struct
{
    void * _state;
    void (* func)(void * _state, easyar_LogLevel, easyar_String *, /* OUT */ easyar_String * * _exception);
    void (* destroy)(void * _state);
} easyar_FunctorOfVoidFromLogLevelAndString;

#ifdef __cplusplus
}
#endif

#endif
