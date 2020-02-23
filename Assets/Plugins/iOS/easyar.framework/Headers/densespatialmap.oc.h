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
/// DenseSpatialMap is used to reconstruct the environment accurately and densely. The reconstructed model is represented by `triangle mesh`, which is denoted simply by `mesh`.
/// DenseSpatialMap occupies 1 buffers of camera.
/// </summary>
@interface easyar_DenseSpatialMap : easyar_RefBase

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// <summary>
/// Returns True when the device supports dense reconstruction, otherwise returns False.
/// </summary>
+ (bool)isAvailable;
/// <summary>
/// Input port for input frame. For DenseSpatialMap to work, the inputFrame must include image and it&#39;s camera parameters and spatial information (cameraTransform and trackingStatus). See also `InputFrameSink`_ .
/// </summary>
- (easyar_InputFrameSink *)inputFrameSink;
/// <summary>
/// Camera buffers occupied in this component.
/// </summary>
- (int)bufferRequirement;
/// <summary>
/// Create `DenseSpatialMap`_ object.
/// </summary>
+ (easyar_DenseSpatialMap *)create;
/// <summary>
/// Start or continue runninng `DenseSpatialMap`_ algorithm.
/// </summary>
- (bool)start;
/// <summary>
/// Pause the reconstruction algorithm. Call `start` to resume reconstruction.
/// </summary>
- (void)stop;
/// <summary>
/// Close `DenseSpatialMap`_ algorithm.
/// </summary>
- (void)close;
/// <summary>
/// Get the mesh management object of type `SceneMesh`_ . The contents will automatically update after calling the `DenseSpatialMap.updateSceneMesh`_ function.
/// </summary>
- (easyar_SceneMesh *)getMesh;
/// <summary>
/// Get the lastest updated mesh and save it to the `SceneMesh`_ object obtained by `DenseSpatialMap.getMesh`_ .
/// The parameter `updateMeshAll` indicates whether to perform a `full update` or an `incremental update`. When `updateMeshAll` is True, `full update` is performed. All meshes are saved to `SceneMesh`_ . When `updateMeshAll` is False, `incremental update` is performed, and only the most recently updated mesh is saved to `SceneMesh`_ .
/// `Full update` will take extra time and memory space, causing performance degradation.
/// </summary>
- (bool)updateSceneMesh:(bool)updateMeshAll;

@end
