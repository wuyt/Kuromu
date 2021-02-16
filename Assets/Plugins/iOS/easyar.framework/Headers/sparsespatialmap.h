//=============================================================================================================================
//
// EasyAR Sense 4.1.0.7750-f1413084f
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

#ifndef __EASYAR_SPARSESPATIALMAP_H__
#define __EASYAR_SPARSESPATIALMAP_H__

#include "easyar/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// <summary>
/// Obtain motion tracking status.
/// </summary>
easyar_MotionTrackingStatus easyar_SparseSpatialMapResult_getMotionTrackingStatus(const easyar_SparseSpatialMapResult * This);
/// <summary>
/// Returns pose of the origin of VIO system in camera coordinate system.
/// </summary>
easyar_OptionalOfMatrix44F easyar_SparseSpatialMapResult_getVioPose(const easyar_SparseSpatialMapResult * This);
/// <summary>
/// Returns the pose of origin of the map in camera coordinate system, when localization is successful.
/// Otherwise, returns pose of the origin of VIO system in camera coordinate system.
/// </summary>
easyar_OptionalOfMatrix44F easyar_SparseSpatialMapResult_getMapPose(const easyar_SparseSpatialMapResult * This);
/// <summary>
/// Returns true if the system can reliablly locate the pose of the device with regard to the map.
/// Once relocalization succeeds, relative pose can be updated by motion tracking module.
/// As long as the motion tracking module returns normal tracking status, the localization status is also true.
/// </summary>
bool easyar_SparseSpatialMapResult_getLocalizationStatus(const easyar_SparseSpatialMapResult * This);
/// <summary>
/// Returns current localized map ID.
/// </summary>
void easyar_SparseSpatialMapResult_getLocalizationMapID(const easyar_SparseSpatialMapResult * This, /* OUT */ easyar_String * * Return);
void easyar_SparseSpatialMapResult__dtor(easyar_SparseSpatialMapResult * This);
void easyar_SparseSpatialMapResult__retain(const easyar_SparseSpatialMapResult * This, /* OUT */ easyar_SparseSpatialMapResult * * Return);
const char * easyar_SparseSpatialMapResult__typeName(const easyar_SparseSpatialMapResult * This);
void easyar_castSparseSpatialMapResultToFrameFilterResult(const easyar_SparseSpatialMapResult * This, /* OUT */ easyar_FrameFilterResult * * Return);
void easyar_tryCastFrameFilterResultToSparseSpatialMapResult(const easyar_FrameFilterResult * This, /* OUT */ easyar_SparseSpatialMapResult * * Return);

/// <summary>
/// Constructor
/// </summary>
void easyar_PlaneData__ctor(/* OUT */ easyar_PlaneData * * Return);
/// <summary>
/// Returns the type of this plane.
/// </summary>
easyar_PlaneType easyar_PlaneData_getType(const easyar_PlaneData * This);
/// <summary>
/// Returns the pose of the center of the detected plane.The pose&#39;s transformed +Y axis will be point normal out of the plane, with the +X and +Z axes orienting the extents of the bounding rectangle.
/// </summary>
easyar_Matrix44F easyar_PlaneData_getPose(const easyar_PlaneData * This);
/// <summary>
/// Returns the length of this plane&#39;s bounding rectangle measured along the local X-axis of the coordinate space centered on the plane.
/// </summary>
float easyar_PlaneData_getExtentX(const easyar_PlaneData * This);
/// <summary>
/// Returns the length of this plane&#39;s bounding rectangle measured along the local Z-axis of the coordinate frame centered on the plane.
/// </summary>
float easyar_PlaneData_getExtentZ(const easyar_PlaneData * This);
void easyar_PlaneData__dtor(easyar_PlaneData * This);
void easyar_PlaneData__retain(const easyar_PlaneData * This, /* OUT */ easyar_PlaneData * * Return);
const char * easyar_PlaneData__typeName(const easyar_PlaneData * This);

/// <summary>
/// Constructor
/// </summary>
void easyar_SparseSpatialMapConfig__ctor(/* OUT */ easyar_SparseSpatialMapConfig * * Return);
/// <summary>
/// Sets localization configurations. See also `LocalizationMode`_.
/// </summary>
void easyar_SparseSpatialMapConfig_setLocalizationMode(easyar_SparseSpatialMapConfig * This, easyar_LocalizationMode _value);
/// <summary>
/// Returns localization configurations. See also `LocalizationMode`_.
/// </summary>
easyar_LocalizationMode easyar_SparseSpatialMapConfig_getLocalizationMode(const easyar_SparseSpatialMapConfig * This);
void easyar_SparseSpatialMapConfig__dtor(easyar_SparseSpatialMapConfig * This);
void easyar_SparseSpatialMapConfig__retain(const easyar_SparseSpatialMapConfig * This, /* OUT */ easyar_SparseSpatialMapConfig * * Return);
const char * easyar_SparseSpatialMapConfig__typeName(const easyar_SparseSpatialMapConfig * This);

/// <summary>
/// Check whether SparseSpatialMap is is available, always return true.
/// </summary>
bool easyar_SparseSpatialMap_isAvailable(void);
/// <summary>
/// Input port for input frame. For SparseSpatialMap to work, the inputFrame must include camera parameters, timestamp and spatial information. See also `InputFrameSink`_
/// </summary>
void easyar_SparseSpatialMap_inputFrameSink(easyar_SparseSpatialMap * This, /* OUT */ easyar_InputFrameSink * * Return);
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
int easyar_SparseSpatialMap_bufferRequirement(easyar_SparseSpatialMap * This);
/// <summary>
/// Output port for output frame. See also `OutputFrameSource`_
/// </summary>
void easyar_SparseSpatialMap_outputFrameSource(easyar_SparseSpatialMap * This, /* OUT */ easyar_OutputFrameSource * * Return);
/// <summary>
/// Construct SparseSpatialMap.
/// </summary>
void easyar_SparseSpatialMap_create(/* OUT */ easyar_SparseSpatialMap * * Return);
/// <summary>
/// Start SparseSpatialMap system.
/// </summary>
bool easyar_SparseSpatialMap_start(easyar_SparseSpatialMap * This);
/// <summary>
/// Stop SparseSpatialMap from running。Can resume running by calling start().
/// </summary>
void easyar_SparseSpatialMap_stop(easyar_SparseSpatialMap * This);
/// <summary>
/// Close SparseSpatialMap. SparseSpatialMap can no longer be used.
/// </summary>
void easyar_SparseSpatialMap_close(easyar_SparseSpatialMap * This);
/// <summary>
/// Returns the buffer of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space, each of which takes 4 bytes.
/// </summary>
void easyar_SparseSpatialMap_getPointCloudBuffer(easyar_SparseSpatialMap * This, /* OUT */ easyar_Buffer * * Return);
/// <summary>
/// Returns detected planes in SparseSpatialMap.
/// </summary>
void easyar_SparseSpatialMap_getMapPlanes(easyar_SparseSpatialMap * This, /* OUT */ easyar_ListOfPlaneData * * Return);
/// <summary>
/// Perform hit test against the point cloud. The results are returned sorted by their distance to the camera in ascending order.
/// </summary>
void easyar_SparseSpatialMap_hitTestAgainstPointCloud(easyar_SparseSpatialMap * This, easyar_Vec2F cameraImagePoint, /* OUT */ easyar_ListOfVec3F * * Return);
/// <summary>
/// Performs ray cast from the user&#39;s device in the direction of given screen point.
/// Intersections with detected planes are returned. 3D positions on physical planes are sorted by distance from the device in ascending order.
/// For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
/// The output point cloud coordinate is in the world coordinate system.
/// </summary>
void easyar_SparseSpatialMap_hitTestAgainstPlanes(easyar_SparseSpatialMap * This, easyar_Vec2F cameraImagePoint, /* OUT */ easyar_ListOfVec3F * * Return);
/// <summary>
/// Get the map data version of the current SparseSpatialMap.
/// </summary>
void easyar_SparseSpatialMap_getMapVersion(/* OUT */ easyar_String * * Return);
/// <summary>
/// UnloadMap specified SparseSpatialMap data via callback function.The return value of callback indicates whether unload map succeeds (true) or fails (false).
/// </summary>
void easyar_SparseSpatialMap_unloadMap(easyar_SparseSpatialMap * This, easyar_String * mapID, easyar_CallbackScheduler * callbackScheduler, easyar_OptionalOfFunctorOfVoidFromBool resultCallBack);
/// <summary>
/// Set configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
/// </summary>
void easyar_SparseSpatialMap_setConfig(easyar_SparseSpatialMap * This, easyar_SparseSpatialMapConfig * config);
/// <summary>
/// Returns configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
/// </summary>
void easyar_SparseSpatialMap_getConfig(easyar_SparseSpatialMap * This, /* OUT */ easyar_SparseSpatialMapConfig * * Return);
/// <summary>
/// Start localization in loaded maps. Should set `LocalizationMode`_ first.
/// </summary>
bool easyar_SparseSpatialMap_startLocalization(easyar_SparseSpatialMap * This);
/// <summary>
/// Stop localization in loaded maps.
/// </summary>
void easyar_SparseSpatialMap_stopLocalization(easyar_SparseSpatialMap * This);
void easyar_SparseSpatialMap__dtor(easyar_SparseSpatialMap * This);
void easyar_SparseSpatialMap__retain(const easyar_SparseSpatialMap * This, /* OUT */ easyar_SparseSpatialMap * * Return);
const char * easyar_SparseSpatialMap__typeName(const easyar_SparseSpatialMap * This);

void easyar_ListOfPlaneData__ctor(easyar_PlaneData * const * begin, easyar_PlaneData * const * end, /* OUT */ easyar_ListOfPlaneData * * Return);
void easyar_ListOfPlaneData__dtor(easyar_ListOfPlaneData * This);
void easyar_ListOfPlaneData_copy(const easyar_ListOfPlaneData * This, /* OUT */ easyar_ListOfPlaneData * * Return);
int easyar_ListOfPlaneData_size(const easyar_ListOfPlaneData * This);
easyar_PlaneData * easyar_ListOfPlaneData_at(const easyar_ListOfPlaneData * This, int index);

void easyar_ListOfVec3F__ctor(easyar_Vec3F const * begin, easyar_Vec3F const * end, /* OUT */ easyar_ListOfVec3F * * Return);
void easyar_ListOfVec3F__dtor(easyar_ListOfVec3F * This);
void easyar_ListOfVec3F_copy(const easyar_ListOfVec3F * This, /* OUT */ easyar_ListOfVec3F * * Return);
int easyar_ListOfVec3F_size(const easyar_ListOfVec3F * This);
easyar_Vec3F easyar_ListOfVec3F_at(const easyar_ListOfVec3F * This, int index);

#ifdef __cplusplus
}
#endif

#endif
