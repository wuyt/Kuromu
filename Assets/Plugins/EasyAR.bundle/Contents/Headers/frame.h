//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_FRAME_H__
#define __EASYAR_FRAME_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Index, an automatic incremental value, which is different for every input frame.
/// </summary>
int easyar_InputFrame_index(const easyar_InputFrame * This);
/// <summary>
/// Gets image.
/// </summary>
void easyar_InputFrame_image(const easyar_InputFrame * This, /* OUT */ easyar_Image * * Return);
/// <summary>
/// Checks if there are camera parameters.
/// </summary>
bool easyar_InputFrame_hasCameraParameters(const easyar_InputFrame * This);
/// <summary>
/// Gets camera parameters.
/// </summary>
void easyar_InputFrame_cameraParameters(const easyar_InputFrame * This, /* OUT */ easyar_CameraParameters * * Return);
/// <summary>
/// Checks if there is temporal information (timestamp).
/// </summary>
bool easyar_InputFrame_hasTemporalInformation(const easyar_InputFrame * This);
/// <summary>
/// Timestamp. In seconds.
/// </summary>
double easyar_InputFrame_timestamp(const easyar_InputFrame * This);
/// <summary>
/// Checks if there is spatial information (cameraTransform and trackingStatus).
/// </summary>
bool easyar_InputFrame_hasSpatialInformation(const easyar_InputFrame * This);
/// <summary>
/// Camera transform matrix against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL&#39;s column-major.
/// </summary>
easyar_Matrix44F easyar_InputFrame_cameraTransform(const easyar_InputFrame * This);
/// <summary>
/// Gets device motion tracking status: `MotionTrackingStatus`_ .
/// </summary>
easyar_MotionTrackingStatus easyar_InputFrame_trackingStatus(const easyar_InputFrame * This);
/// <summary>
/// Creates an instance.
/// </summary>
void easyar_InputFrame_create(easyar_Image * image, easyar_CameraParameters * cameraParameters, double timestamp, easyar_Matrix44F cameraTransform, easyar_MotionTrackingStatus trackingStatus, /* OUT */ easyar_InputFrame * * Return);
/// <summary>
/// Creates an instance with image, camera parameters, and timestamp.
/// </summary>
void easyar_InputFrame_createWithImageAndCameraParametersAndTemporal(easyar_Image * image, easyar_CameraParameters * cameraParameters, double timestamp, /* OUT */ easyar_InputFrame * * Return);
/// <summary>
/// Creates an instance with image and camera parameters.
/// </summary>
void easyar_InputFrame_createWithImageAndCameraParameters(easyar_Image * image, easyar_CameraParameters * cameraParameters, /* OUT */ easyar_InputFrame * * Return);
/// <summary>
/// Creates an instance with image.
/// </summary>
void easyar_InputFrame_createWithImage(easyar_Image * image, /* OUT */ easyar_InputFrame * * Return);
void easyar_InputFrame__dtor(easyar_InputFrame * This);
void easyar_InputFrame__retain(const easyar_InputFrame * This, /* OUT */ easyar_InputFrame * * Return);
const char * easyar_InputFrame__typeName(const easyar_InputFrame * This);

void easyar_FrameFilterResult__dtor(easyar_FrameFilterResult * This);
void easyar_FrameFilterResult__retain(const easyar_FrameFilterResult * This, /* OUT */ easyar_FrameFilterResult * * Return);
const char * easyar_FrameFilterResult__typeName(const easyar_FrameFilterResult * This);

void easyar_OutputFrame__ctor(easyar_InputFrame * inputFrame, easyar_ListOfOptionalOfFrameFilterResult * results, /* OUT */ easyar_OutputFrame * * Return);
/// <summary>
/// Index, an automatic incremental value, which is different for every output frame.
/// </summary>
int easyar_OutputFrame_index(const easyar_OutputFrame * This);
/// <summary>
/// Corresponding input frame.
/// </summary>
void easyar_OutputFrame_inputFrame(const easyar_OutputFrame * This, /* OUT */ easyar_InputFrame * * Return);
/// <summary>
/// Results of synchronous components.
/// </summary>
void easyar_OutputFrame_results(const easyar_OutputFrame * This, /* OUT */ easyar_ListOfOptionalOfFrameFilterResult * * Return);
void easyar_OutputFrame__dtor(easyar_OutputFrame * This);
void easyar_OutputFrame__retain(const easyar_OutputFrame * This, /* OUT */ easyar_OutputFrame * * Return);
const char * easyar_OutputFrame__typeName(const easyar_OutputFrame * This);

void easyar_FeedbackFrame__ctor(easyar_InputFrame * inputFrame, easyar_OptionalOfOutputFrame previousOutputFrame, /* OUT */ easyar_FeedbackFrame * * Return);
/// <summary>
/// Input frame.
/// </summary>
void easyar_FeedbackFrame_inputFrame(const easyar_FeedbackFrame * This, /* OUT */ easyar_InputFrame * * Return);
/// <summary>
/// Historic output frame.
/// </summary>
void easyar_FeedbackFrame_previousOutputFrame(const easyar_FeedbackFrame * This, /* OUT */ easyar_OptionalOfOutputFrame * Return);
void easyar_FeedbackFrame__dtor(easyar_FeedbackFrame * This);
void easyar_FeedbackFrame__retain(const easyar_FeedbackFrame * This, /* OUT */ easyar_FeedbackFrame * * Return);
const char * easyar_FeedbackFrame__typeName(const easyar_FeedbackFrame * This);

void easyar_ListOfOptionalOfFrameFilterResult__ctor(easyar_OptionalOfFrameFilterResult const * begin, easyar_OptionalOfFrameFilterResult const * end, /* OUT */ easyar_ListOfOptionalOfFrameFilterResult * * Return);
void easyar_ListOfOptionalOfFrameFilterResult__dtor(easyar_ListOfOptionalOfFrameFilterResult * This);
void easyar_ListOfOptionalOfFrameFilterResult_copy(const easyar_ListOfOptionalOfFrameFilterResult * This, /* OUT */ easyar_ListOfOptionalOfFrameFilterResult * * Return);
int easyar_ListOfOptionalOfFrameFilterResult_size(const easyar_ListOfOptionalOfFrameFilterResult * This);
easyar_OptionalOfFrameFilterResult easyar_ListOfOptionalOfFrameFilterResult_at(const easyar_ListOfOptionalOfFrameFilterResult * This, int index);

#ifdef __cplusplus
}
#endif

#endif
