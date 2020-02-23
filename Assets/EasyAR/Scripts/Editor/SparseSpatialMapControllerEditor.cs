//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEditor;
using UnityEngine;

namespace easyar
{
    [CustomEditor(typeof(SparseSpatialMapController), true)]
    public class SparseSpatialMapControllerEditor : Editor
    {
        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            var controller = (SparseSpatialMapController)target;

            switch (controller.SourceType)
            {
                case SparseSpatialMapController.DataSource.MapManager:
                    var mapManagerSource = serializedObject.FindProperty("MapManagerSource");
                    mapManagerSource.isExpanded = EditorGUILayout.Foldout(mapManagerSource.isExpanded, "Map Manager Source");
                    EditorGUI.indentLevel += 1;
                    if (mapManagerSource.isExpanded)
                    {
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("MapManagerSource.ID"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("MapManagerSource.Name"), true);
                    }
                    EditorGUI.indentLevel -= 1;
                    break;
                default:
                    break;
            }

            var mapWorker = serializedObject.FindProperty("mapWorker");
            EditorGUILayout.PropertyField(mapWorker, new GUIContent("Map Worker"), true);

            var mapWorkerHasSet = serializedObject.FindProperty("mapWorkerHasSet");
            if (!mapWorkerHasSet.boolValue)
            {
                if (!mapWorker.objectReferenceValue)
                {
                    mapWorker.objectReferenceValue = FindObjectOfType<SparseSpatialMapWorkerFrameFilter>();
                }
                if (mapWorker.objectReferenceValue)
                {
                    mapWorkerHasSet.boolValue = true;
                }
            }

            var showPointCloud = serializedObject.FindProperty("showPointCloud");
            EditorGUILayout.PropertyField(showPointCloud, true);

            var pointCloudParticleParameter = serializedObject.FindProperty("pointCloudParticleParameter");
            pointCloudParticleParameter.isExpanded = EditorGUILayout.Foldout(pointCloudParticleParameter.isExpanded, "Point Cloud Particle Parameter");
            EditorGUI.indentLevel += 1;
            if (pointCloudParticleParameter.isExpanded)
            {
                EditorGUILayout.PropertyField(serializedObject.FindProperty("pointCloudParticleParameter.StartColor"), true);
                EditorGUILayout.PropertyField(serializedObject.FindProperty("pointCloudParticleParameter.StartSize"), true);
                EditorGUILayout.PropertyField(serializedObject.FindProperty("pointCloudParticleParameter.StartLifetime"), true);
                EditorGUILayout.PropertyField(serializedObject.FindProperty("pointCloudParticleParameter.RemainingLifetime"), true);
            }
            EditorGUI.indentLevel -= 1;

            serializedObject.ApplyModifiedProperties();
            controller.MapWorker = (SparseSpatialMapWorkerFrameFilter)mapWorker.objectReferenceValue;
            controller.ShowPointCloud = showPointCloud.boolValue;
        }
    }
}
