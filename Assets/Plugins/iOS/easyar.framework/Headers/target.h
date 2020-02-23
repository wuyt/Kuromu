//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_TARGET_H__
#define __EASYAR_TARGET_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
/// </summary>
int easyar_Target_runtimeID(const easyar_Target * This);
/// <summary>
/// Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
/// </summary>
void easyar_Target_uid(const easyar_Target * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Returns the target name. Name is used to distinguish targets in a json file.
/// </summary>
void easyar_Target_name(const easyar_Target * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Set name. It will erase previously set data or data from cloud.
/// </summary>
void easyar_Target_setName(easyar_Target * This, easyar_String * name);
/// <summary>
/// Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
/// </summary>
void easyar_Target_meta(const easyar_Target * This, /* OUT */ easyar_String * * Return);
/// <summary>
/// Set meta data. It will erase previously set data or data from cloud.
/// </summary>
void easyar_Target_setMeta(easyar_Target * This, easyar_String * data);
void easyar_Target__dtor(easyar_Target * This);
void easyar_Target__retain(const easyar_Target * This, /* OUT */ easyar_Target * * Return);
const char * easyar_Target__typeName(const easyar_Target * This);

void easyar_TargetInstance__ctor(/* OUT */ easyar_TargetInstance * * Return);
/// <summary>
/// Returns current status of the tracked target. Usually you can check if the status equals `TargetStatus.Tracked` to determine current status of the target.
/// </summary>
easyar_TargetStatus easyar_TargetInstance_status(const easyar_TargetInstance * This);
/// <summary>
/// Gets the raw target. It will return the same `Target`_ you loaded into a tracker if it was previously loaded into the tracker.
/// </summary>
void easyar_TargetInstance_target(const easyar_TargetInstance * This, /* OUT */ easyar_OptionalOfTarget * Return);
/// <summary>
/// Returns current pose of the tracked target. Camera coordinate system and target coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL&#39;s column-major.
/// </summary>
easyar_Matrix44F easyar_TargetInstance_pose(const easyar_TargetInstance * This);
void easyar_TargetInstance__dtor(easyar_TargetInstance * This);
void easyar_TargetInstance__retain(const easyar_TargetInstance * This, /* OUT */ easyar_TargetInstance * * Return);
const char * easyar_TargetInstance__typeName(const easyar_TargetInstance * This);

/// <summary>
/// Returns the list of `TargetInstance`_ contained in the result.
/// </summary>
void easyar_TargetTrackerResult_targetInstances(const easyar_TargetTrackerResult * This, /* OUT */ easyar_ListOfTargetInstance * * Return);
/// <summary>
/// Sets the list of `TargetInstance`_ contained in the result.
/// </summary>
void easyar_TargetTrackerResult_setTargetInstances(easyar_TargetTrackerResult * This, easyar_ListOfTargetInstance * instances);
void easyar_TargetTrackerResult__dtor(easyar_TargetTrackerResult * This);
void easyar_TargetTrackerResult__retain(const easyar_TargetTrackerResult * This, /* OUT */ easyar_TargetTrackerResult * * Return);
const char * easyar_TargetTrackerResult__typeName(const easyar_TargetTrackerResult * This);
void easyar_castTargetTrackerResultToFrameFilterResult(const easyar_TargetTrackerResult * This, /* OUT */ easyar_FrameFilterResult * * Return);
void easyar_tryCastFrameFilterResultToTargetTrackerResult(const easyar_FrameFilterResult * This, /* OUT */ easyar_TargetTrackerResult * * Return);

void easyar_ListOfTargetInstance__ctor(easyar_TargetInstance * const * begin, easyar_TargetInstance * const * end, /* OUT */ easyar_ListOfTargetInstance * * Return);
void easyar_ListOfTargetInstance__dtor(easyar_ListOfTargetInstance * This);
void easyar_ListOfTargetInstance_copy(const easyar_ListOfTargetInstance * This, /* OUT */ easyar_ListOfTargetInstance * * Return);
int easyar_ListOfTargetInstance_size(const easyar_ListOfTargetInstance * This);
easyar_TargetInstance * easyar_ListOfTargetInstance_at(const easyar_ListOfTargetInstance * This, int index);

#ifdef __cplusplus
}
#endif

#endif
