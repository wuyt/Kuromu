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
/// CameraDevice implements a camera device, which outputs `InputFrame`_ (including image, camera paramters, and timestamp). It is available on Windows, Mac, Android and iOS.
/// After open, start/stop can be invoked to start or stop data collection. start/stop will not change previous set camera parameters.
/// When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
/// CameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview &lt;Overview.html&gt;`_ .
/// bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview &lt;Overview.html&gt;`_ .
/// </summary>
@interface easyar_CameraDevice : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (easyar_CameraDevice *) create;
/// <summary>
/// Checks if the component is available. It returns true only on Windows, Mac, Android or iOS.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Gets current camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
/// </summary>
- (easyar_AndroidCameraApiType)androidCameraApiType;
/// <summary>
/// Sets current camera API (camera1 or camera2) on Android. It must be called before calling openWithIndex, openWithSpecificType or openWithPreferredType, or it will not take effect.
/// It is recommended to use `CameraDeviceSelector`_ to create camera with camera API set to recommended based on primary algorithm to run.
/// </summary>
- (void)setAndroidCameraApiType:(easyar_AndroidCameraApiType)type;
/// <summary>
/// `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
- (int)bufferCapacity;
/// <summary>
/// Sets `InputFrame`_ buffer capacity.
/// </summary>
- (void)setBufferCapacity:(int)capacity;
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
- (easyar_InputFrameSource *)inputFrameSource;
/// <summary>
/// Sets callback on state change to notify state of camera disconnection or preemption. It is only available on Windows.
/// </summary>
- (void)setStateChangedCallback:(easyar_CallbackScheduler *)callbackScheduler stateChangedCallback:(void (^)(easyar_CameraState))stateChangedCallback;
/// <summary>
/// Requests camera permission from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
/// </summary>
+ (void)requestPermissions:(easyar_CallbackScheduler *)callbackScheduler permissionCallback:(void (^)(easyar_PermissionStatus status, NSString * value))permissionCallback;
/// <summary>
/// Gets count of cameras recognized by the operating system.
/// </summary>
+ (int)cameraCount;
/// <summary>
/// Opens a camera by index.
/// </summary>
- (bool)openWithIndex:(int)cameraIndex;
/// <summary>
/// Opens a camera by specific camera device type. If no camera is matched, false will be returned. On Mac, camera device types can not be distinguished.
/// </summary>
- (bool)openWithSpecificType:(easyar_CameraDeviceType)type;
/// <summary>
/// Opens a camera by camera device type. If no camera is matched, the first camera will be used.
/// </summary>
- (bool)openWithPreferredType:(easyar_CameraDeviceType)type;
/// <summary>
/// Starts video stream capture.
/// </summary>
- (bool)start;
/// <summary>
/// Stops video stream capture. It will only stop capture and will not change previous set camera parameters.
/// </summary>
- (void)stop;
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
- (void)close;
/// <summary>
/// Camera index.
/// </summary>
- (int)index;
/// <summary>
/// Camera type.
/// </summary>
- (easyar_CameraDeviceType)type;
/// <summary>
/// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation. Call after a successful open.
/// </summary>
- (easyar_CameraParameters *)cameraParameters;
/// <summary>
/// Sets camera parameters. Call after a successful open.
/// </summary>
- (void)setCameraParameters:(easyar_CameraParameters *)cameraParameters;
/// <summary>
/// Gets the current preview size. Call after a successful open.
/// </summary>
- (easyar_Vec2I *)size;
/// <summary>
/// Gets the number of supported preview sizes. Call after a successful open.
/// </summary>
- (int)supportedSizeCount;
/// <summary>
/// Gets the index-th supported preview size. It returns {0, 0} if index is out of range. Call after a successful open.
/// </summary>
- (easyar_Vec2I *)supportedSize:(int)index;
/// <summary>
/// Sets the preview size. The available nearest value will be selected. Call size to get the actual size. Call after a successful open. frameRateRange may change after calling setSize.
/// </summary>
- (bool)setSize:(easyar_Vec2I *)size;
/// <summary>
/// Gets the number of supported frame rate ranges. Call after a successful open.
/// </summary>
- (int)supportedFrameRateRangeCount;
/// <summary>
/// Gets range lower bound of the index-th supported frame rate range. Call after a successful open.
/// </summary>
- (float)supportedFrameRateRangeLower:(int)index;
/// <summary>
/// Gets range upper bound of the index-th supported frame rate range. Call after a successful open.
/// </summary>
- (float)supportedFrameRateRangeUpper:(int)index;
/// <summary>
/// Gets current index of frame rate range. Call after a successful open.
/// </summary>
- (int)frameRateRange;
/// <summary>
/// Sets current index of frame rate range. Call after a successful open.
/// </summary>
- (bool)setFrameRateRange:(int)index;
/// <summary>
/// Sets flash torch mode to on. Call after a successful open.
/// </summary>
- (bool)setFlashTorchMode:(bool)on;
/// <summary>
/// Sets focus mode to focusMode. Call after a successful open.
/// </summary>
- (bool)setFocusMode:(easyar_CameraDeviceFocusMode)focusMode;
/// <summary>
/// Does auto focus once. Call after start. It is only available when FocusMode is Normal or Macro.
/// </summary>
- (bool)autoFocus;

@end

/// <summary>
/// It is used for selecting camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
/// Different preferences will choose camera1 or camera2 based on usage.
/// </summary>
@interface easyar_CameraDeviceSelector : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Creates `CameraDevice`_ with a specified preference.
/// </summary>
+ (easyar_CameraDevice *)createCameraDevice:(easyar_CameraDevicePreference)preference;

@end
