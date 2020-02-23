//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_IMAGETRACKER_H__
#define __EASYAR_IMAGETRACKER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Returns the list of `TargetInstance`_ contained in the result.
/// </summary>
void easyar_ImageTrackerResult_targetInstances(const easyar_ImageTrackerResult * This, /* OUT */ easyar_ListOfTargetInstance * * Return);
/// <summary>
/// Sets the list of `TargetInstance`_ contained in the result.
/// </summary>
void easyar_ImageTrackerResult_setTargetInstances(easyar_ImageTrackerResult * This, easyar_ListOfTargetInstance * instances);
void easyar_ImageTrackerResult__dtor(easyar_ImageTrackerResult * This);
void easyar_ImageTrackerResult__retain(const easyar_ImageTrackerResult * This, /* OUT */ easyar_ImageTrackerResult * * Return);
const char * easyar_ImageTrackerResult__typeName(const easyar_ImageTrackerResult * This);
void easyar_castImageTrackerResultToFrameFilterResult(const easyar_ImageTrackerResult * This, /* OUT */ easyar_FrameFilterResult * * Return);
void easyar_tryCastFrameFilterResultToImageTrackerResult(const easyar_FrameFilterResult * This, /* OUT */ easyar_ImageTrackerResult * * Return);
void easyar_castImageTrackerResultToTargetTrackerResult(const easyar_ImageTrackerResult * This, /* OUT */ easyar_TargetTrackerResult * * Return);
void easyar_tryCastTargetTrackerResultToImageTrackerResult(const easyar_TargetTrackerResult * This, /* OUT */ easyar_ImageTrackerResult * * Return);

/// <summary>
/// Returns true.
/// </summary>
bool easyar_ImageTracker_isAvailable(void);
/// <summary>
/// `FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
/// </summary>
void easyar_ImageTracker_feedbackFrameSink(easyar_ImageTracker * This, /* OUT */ easyar_FeedbackFrameSink * * Return);
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
int easyar_ImageTracker_bufferRequirement(easyar_ImageTracker * This);
/// <summary>
/// `OutputFrame`_ output port.
/// </summary>
void easyar_ImageTracker_outputFrameSource(easyar_ImageTracker * This, /* OUT */ easyar_OutputFrameSource * * Return);
/// <summary>
/// Creates an instance. The default track mode is `ImageTrackerMode.PreferQuality`_ .
/// </summary>
void easyar_ImageTracker_create(/* OUT */ easyar_ImageTracker * * Return);
/// <summary>
/// Creates an instance with a specified track mode. On lower-end phones, `ImageTrackerMode.PreferPerformance`_ can be used to keep a better performance with a little quality loss.
/// </summary>
void easyar_ImageTracker_createWithMode(easyar_ImageTrackerMode trackMode, /* OUT */ easyar_ImageTracker * * Return);
/// <summary>
/// Starts the track algorithm.
/// </summary>
bool easyar_ImageTracker_start(easyar_ImageTracker * This);
/// <summary>
/// Stops the track algorithm. Call start to start the track again.
/// </summary>
void easyar_ImageTracker_stop(easyar_ImageTracker * This);
/// <summary>
/// Close. The component shall not be used after calling close.
/// </summary>
void easyar_ImageTracker_close(easyar_ImageTracker * This);
/// <summary>
/// Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
/// This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
/// </summary>
void easyar_ImageTracker_loadTarget(easyar_ImageTracker * This, easyar_Target * target, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromTargetAndBool callback);
/// <summary>
/// Unload a `Target`_ from the tracker.
/// This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
/// </summary>
void easyar_ImageTracker_unloadTarget(easyar_ImageTracker * This, easyar_Target * target, easyar_CallbackScheduler * callbackScheduler, easyar_FunctorOfVoidFromTargetAndBool callback);
/// <summary>
/// Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
/// </summary>
void easyar_ImageTracker_targets(const easyar_ImageTracker * This, /* OUT */ easyar_ListOfTarget * * Return);
/// <summary>
/// Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
/// </summary>
bool easyar_ImageTracker_setSimultaneousNum(easyar_ImageTracker * This, int num);
/// <summary>
/// Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
/// </summary>
int easyar_ImageTracker_simultaneousNum(const easyar_ImageTracker * This);
void easyar_ImageTracker__dtor(easyar_ImageTracker * This);
void easyar_ImageTracker__retain(const easyar_ImageTracker * This, /* OUT */ easyar_ImageTracker * * Return);
const char * easyar_ImageTracker__typeName(const easyar_ImageTracker * This);

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
