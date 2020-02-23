//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_LOG_H__
#define __EASYAR_LOG_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Sets custom log output function.
/// </summary>
void easyar_Log_setLogFunc(easyar_FunctorOfVoidFromLogLevelAndString func);
/// <summary>
/// Clears custom log output function and reverts to default log output function.
/// </summary>
void easyar_Log_resetLogFunc(void);

#ifdef __cplusplus
}
#endif

#endif
