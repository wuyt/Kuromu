//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CAMERA_H__
#define __EASYAR_CAMERA_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_CameraDevice__ctor(/* OUT */ easyar_CameraDevice * * Return);
/// <summary>
/// Checks if the component is available. It returns true only on Windows, Mac, Android or iOS.
/// </summary>
bool easyar_CameraDevice_isAvailable(void);
/// <summary>
/// Gets current camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
/// </summary>
easyar_AndroidCameraApiType easyar_CameraDevice_androidCameraApiType(easyar_CameraDevice * This);
/// <summary>
/// Sets current camera API (camera1 or camera2) on Android. It must be called before calling openWithIndex, openWithSpecificType or openWithPreferredType, or it will not take effect.
/// It is recommended to use `CameraDeviceSelector`_ to create camera with camera API set to recommended based on primary algorithm to run.
/// </summary>
void easyar_CameraDevice_setAndroidCameraApiType(easyar_CameraDevice * This, easyar_AndroidCameraApiType type);
/// <summary>
/// `InputFrame`_ buffer capacity. The default is 8.
/// </summary>
int easyar_CameraDevice_bufferCapacity(const easyar_CameraDevice * This);
/// <summary>
/// Sets `InputFrame`_ buffer capacity.
/// </summary>
void easyar_CameraDevice_setBufferCapacity(easyar_CameraDevice * This, int capacity);
/// <summary>
/// `InputFrame`_ output port.
/// </summary>
void easyar_CameraDevice_inputFrameSource(easyar_CameraDevice * This, /* OUT */ easyar_InputFrameSource * * Return);
/// <summary>
/// Sets callback on state change to notify state of camera disconnection or preemption. It is only available on Windows.
/// </summary>
void easyar_CameraDevice_setStateChangedCallback(easyar_CameraDevice * This, easyar_CallbackScheduler * callbackScheduler, easyar_OptionalOfFunctorOfVoidFromCameraState stateChangedCallback);
/// <summary>
/// Requests camera permission from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
/// </summary>
void easyar_CameraDevice_requestPermissions(easyar_CallbackScheduler * callbackScheduler, easyar_OptionalOfFunctorOfVoidFromPermissionStatusAndString permissionCallback);
/// <summary>
/// Gets count of cameras recognized by the operating system.
/// </summary>
int easyar_CameraDevice_cameraCount(void);
/// <summary>
/// Opens a camera by index.
/// </summary>
bool easyar_CameraDevice_openWithIndex(easyar_CameraDevice * This, int cameraIndex);
/// <summary>
/// Opens a camera by specific camera device type. If no camera is matched, false will be returned. On Mac, camera device types can not be distinguished.
/// </summary>
bool easyar_CameraDevice_openWithSpecificType(easyar_CameraDevice * This, easyar_CameraDeviceType type);
/// <summary>
/// Opens a camera by camera device type. If no camera is matched, the first camera will be used.
/// </summary>
bool easyar_CameraDevice_openWithPreferredType(easyar_CameraDevice * This, easyar_CameraDeviceType type);
/// <summary>
/// Starts video stream capture.
/// </summary>
bool easyar_CameraDevice_start(easyar_CameraDevice * This);
/// <summary>
/// Stops video stream capture. It will only stop capture and will not change previous set camera parameters and connection.
/// </summary>
void easyar_CameraDevice_stop(easyar_CameraDevice * This);
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
void easyar_CameraDevice_close(easyar_CameraDevice * This);
/// <summary>
/// Camera index.
/// </summary>
int easyar_CameraDevice_index(const easyar_CameraDevice * This);
/// <summary>
/// Camera type.
/// </summary>
easyar_CameraDeviceType easyar_CameraDevice_type(const easyar_CameraDevice * This);
/// <summary>
/// Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation. Call after a successful open.
/// </summary>
void easyar_CameraDevice_cameraParameters(easyar_CameraDevice * This, /* OUT */ easyar_CameraParameters * * Return);
/// <summary>
/// Sets camera parameters. Call after a successful open.
/// </summary>
void easyar_CameraDevice_setCameraParameters(easyar_CameraDevice * This, easyar_CameraParameters * cameraParameters);
/// <summary>
/// Gets the current preview size. Call after a successful open.
/// </summary>
easyar_Vec2I easyar_CameraDevice_size(const easyar_CameraDevice * This);
/// <summary>
/// Gets the number of supported preview sizes. Call after a successful open.
/// </summary>
int easyar_CameraDevice_supportedSizeCount(const easyar_CameraDevice * This);
/// <summary>
/// Gets the index-th supported preview size. It returns {0, 0} if index is out of range. Call after a successful open.
/// </summary>
easyar_Vec2I easyar_CameraDevice_supportedSize(const easyar_CameraDevice * This, int index);
/// <summary>
/// Sets the preview size. The available nearest value will be selected. Call size to get the actual size. Call after a successful open. frameRateRange may change after calling setSize.
/// </summary>
bool easyar_CameraDevice_setSize(easyar_CameraDevice * This, easyar_Vec2I size);
/// <summary>
/// Gets the number of supported frame rate ranges. Call after a successful open.
/// </summary>
int easyar_CameraDevice_supportedFrameRateRangeCount(const easyar_CameraDevice * This);
/// <summary>
/// Gets range lower bound of the index-th supported frame rate range. Call after a successful open.
/// </summary>
float easyar_CameraDevice_supportedFrameRateRangeLower(const easyar_CameraDevice * This, int index);
/// <summary>
/// Gets range upper bound of the index-th supported frame rate range. Call after a successful open.
/// </summary>
float easyar_CameraDevice_supportedFrameRateRangeUpper(const easyar_CameraDevice * This, int index);
/// <summary>
/// Gets current index of frame rate range. Call after a successful open.
/// </summary>
int easyar_CameraDevice_frameRateRange(const easyar_CameraDevice * This);
/// <summary>
/// Sets current index of frame rate range. Call after a successful open.
/// </summary>
bool easyar_CameraDevice_setFrameRateRange(easyar_CameraDevice * This, int index);
/// <summary>
/// Sets flash torch mode to on. Call after a successful open.
/// </summary>
bool easyar_CameraDevice_setFlashTorchMode(easyar_CameraDevice * This, bool on);
/// <summary>
/// Sets focus mode to focusMode. Call after a successful open.
/// </summary>
bool easyar_CameraDevice_setFocusMode(easyar_CameraDevice * This, easyar_CameraDeviceFocusMode focusMode);
/// <summary>
/// Does auto focus once. Call after start. It is only available when FocusMode is Normal or Macro.
/// </summary>
bool easyar_CameraDevice_autoFocus(easyar_CameraDevice * This);
void easyar_CameraDevice__dtor(easyar_CameraDevice * This);
void easyar_CameraDevice__retain(const easyar_CameraDevice * This, /* OUT */ easyar_CameraDevice * * Return);
const char * easyar_CameraDevice__typeName(const easyar_CameraDevice * This);

/// <summary>
/// Gets recommended Android Camera API type by a specified preference.
/// </summary>
easyar_AndroidCameraApiType easyar_CameraDeviceSelector_getAndroidCameraApiType(easyar_CameraDevicePreference preference);
/// <summary>
/// Creates `CameraDevice`_ by a specified preference.
/// </summary>
void easyar_CameraDeviceSelector_createCameraDevice(easyar_CameraDevicePreference preference, /* OUT */ easyar_CameraDevice * * Return);

#ifdef __cplusplus
}
#endif

#endif
