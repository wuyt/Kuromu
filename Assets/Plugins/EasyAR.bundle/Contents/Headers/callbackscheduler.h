//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_CALLBACKSCHEDULER_H__
#define __EASYAR_CALLBACKSCHEDULER_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

void easyar_CallbackScheduler__dtor(easyar_CallbackScheduler * This);
void easyar_CallbackScheduler__retain(const easyar_CallbackScheduler * This, /* OUT */ easyar_CallbackScheduler * * Return);
const char * easyar_CallbackScheduler__typeName(const easyar_CallbackScheduler * This);

void easyar_DelayedCallbackScheduler__ctor(/* OUT */ easyar_DelayedCallbackScheduler * * Return);
/// <summary>
/// Executes a callback. If there is no callback to execute, false is returned.
/// </summary>
bool easyar_DelayedCallbackScheduler_runOne(easyar_DelayedCallbackScheduler * This);
void easyar_DelayedCallbackScheduler__dtor(easyar_DelayedCallbackScheduler * This);
void easyar_DelayedCallbackScheduler__retain(const easyar_DelayedCallbackScheduler * This, /* OUT */ easyar_DelayedCallbackScheduler * * Return);
const char * easyar_DelayedCallbackScheduler__typeName(const easyar_DelayedCallbackScheduler * This);
void easyar_castDelayedCallbackSchedulerToCallbackScheduler(const easyar_DelayedCallbackScheduler * This, /* OUT */ easyar_CallbackScheduler * * Return);
void easyar_tryCastCallbackSchedulerToDelayedCallbackScheduler(const easyar_CallbackScheduler * This, /* OUT */ easyar_DelayedCallbackScheduler * * Return);

/// <summary>
/// Gets a default immediate callback scheduler.
/// </summary>
void easyar_ImmediateCallbackScheduler_getDefault(/* OUT */ easyar_ImmediateCallbackScheduler * * Return);
void easyar_ImmediateCallbackScheduler__dtor(easyar_ImmediateCallbackScheduler * This);
void easyar_ImmediateCallbackScheduler__retain(const easyar_ImmediateCallbackScheduler * This, /* OUT */ easyar_ImmediateCallbackScheduler * * Return);
const char * easyar_ImmediateCallbackScheduler__typeName(const easyar_ImmediateCallbackScheduler * This);
void easyar_castImmediateCallbackSchedulerToCallbackScheduler(const easyar_ImmediateCallbackScheduler * This, /* OUT */ easyar_CallbackScheduler * * Return);
void easyar_tryCastCallbackSchedulerToImmediateCallbackScheduler(const easyar_CallbackScheduler * This, /* OUT */ easyar_ImmediateCallbackScheduler * * Return);

#ifdef __cplusplus
}
#endif

#endif
