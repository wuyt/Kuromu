//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_OBJECTTRACKER_H__
#define __EASYAR_OBJECTTRACKER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Returns the list of `TargetInstance`_ contained in the result.
/// </summary>
void easyar_ObjectTrackerResult_targetInstances(const easyar_ObjectTrackerResult * This, /* OUT */ easyar_ListOfTargetInstance * * Return);
/// <summary>
/// Sets the list of `TargetInstance`_ contained in the result.
/// </summary>
void easyar_ObjectTrackerResult_setTargetInstances(easyar_ObjectTrackerResult * This, easyar_ListOfTargetInstance * instances);
void easyar_ObjectTrackerResult__dtor(easyar_ObjectTrackerResult * This);
void easyar_ObjectTrackerResult__retain(const easyar_ObjectTrackerResult * This, /* OUT */ easyar_ObjectTrackerResult * * Return);
const char * easyar_ObjectTrackerResult__typeName(const easyar_ObjectTrackerResult * This);
void easyar_castObjectTrackerResultToFrameFilterResult(const easyar_ObjectTrackerResult * This, /* OUT */ easyar_FrameFilterResult * * Return);
void easyar_tryCastFrameFilterResultToObjectTrackerResult(const easyar_FrameFilterResult * This, /* OUT */ easyar_ObjectTrackerResult * * Return);
void easyar_castObjectTrackerResultToTargetTrackerResult(const easyar_ObjectTrackerResult * This, /* OUT */ easyar_TargetTrackerResult * * Return);
void easyar_tryCastTargetTrackerResultToObjectTrackerResult(const easyar_TargetTrackerResult * This, /* OUT */ easyar_ObjectTrackerResult * * Return);

/// <summary>
/// Returns true.
/// </summary>
bool easyar_ObjectTracker_isAvailable(void);
/// <summary>
/// `FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
/// </summary>
void easyar_ObjectTracker_feedbackFrameSink(easyar_ObjectTracker * This, /* OUT */ easyar_FeedbackFrameSink * * Return);
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
int easyar_ObjectTracker_bufferRequirement(easyar_ObjectTracker * This);
/// <summary>
/// `OutputFrame`_ output port.
/// </summary>
void easyar_ObjectTracker_outputFrameSource(easyar_ObjectTracker * This, /* OUT */ easyar_OutputFrameSource * * Return);
/// <summary>
/// Creates an instance.
/// </summary>
void easyar_ObjectTracker_create(/* OUT */ easyar_ObjectTracker * * Return);
/// <summary>
/// Starts the track algorithm.
/// </summary>
bool easyar_ObjectTracker_start(easyar_ObjectTracker * This);
/// <summary>
/// Stops the track algorithm. Call start to start the track again.
/// </summary>
void easyar_ObjectTracker_stop(easyar_ObjectTracker * This);
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
void easyar_ObjectTracker_close(easyar_ObjectTracker * This);
/// <summary>
/// Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
/// This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
/// </summary>
void easyar_ObjectTracker_loadTarget(easyar_ObjectTracker * This, easyar_Target * target, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromTargetAndBool callback);
/// <summary>
/// Unload a `Target`_ from the tracker.
/// This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
/// </summary>
void easyar_ObjectTracker_unloadTarget(easyar_ObjectTracker * This, easyar_Target * target, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromTargetAndBool callback);
/// <summary>
/// Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
/// </summary>
void easyar_ObjectTracker_targets(const easyar_ObjectTracker * This, /* OUT */ easyar_ListOfTarget * * Return);
/// <summary>
/// Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
/// </summary>
bool easyar_ObjectTracker_setSimultaneousNum(easyar_ObjectTracker * This, int num);
/// <summary>
/// Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
/// </summary>
int easyar_ObjectTracker_simultaneousNum(const easyar_ObjectTracker * This);
void easyar_ObjectTracker__dtor(easyar_ObjectTracker * This);
void easyar_ObjectTracker__retain(const easyar_ObjectTracker * This, /* OUT */ easyar_ObjectTracker * * Return);
const char * easyar_ObjectTracker__typeName(const easyar_ObjectTracker * This);

void easyar_ListOfTargetInstance__ctor(easyar_TargetInstance * const * begin, easyar_TargetInstance * const * end, /* OUT */ easyar_ListOfTargetInstance * * Return);
void easyar_ListOfTargetInstance__dtor(easyar_ListOfTargetInstance * This);
void easyar_ListOfTargetInstance_copy(const easyar_ListOfTargetInstance * This, /* OUT */ easyar_ListOfTargetInstance * * Return);
int easyar_ListOfTargetInstance_size(const easyar_ListOfTargetInstance * This);
easyar_TargetInstance * easyar_ListOfTargetInstance_at(const easyar_ListOfTargetInstance * This, int index);

void easyar_ListOfTarget__ctor(easyar_Target * const * begin, easyar_Target * const * end, /* OUT */ easyar_ListOfTarget * * Return);
void easyar_ListOfTarget__dtor(easyar_ListOfTarget * This);
void easyar_ListOfTarget_copy(const easyar_ListOfTarget * This, /* OUT */ easyar_ListOfTarget * * Return);
int easyar_ListOfTarget_size(const easyar_ListOfTarget * This);
easyar_Target * easyar_ListOfTarget_at(const easyar_ListOfTarget * This, int index);

#ifdef __cplusplus
}
#endif

#endif
