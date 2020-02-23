//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEditor;

namespace easyar
{
    [CustomEditor(typeof(CloudRecognizerFrameFilter), true)]
    public class CloudRecognizerFrameFilterEditor : Editor
    {
        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            if (!((CloudRecognizerFrameFilter)target).UseGlobalServiceConfig)
            {
                var serviceConfig = serializedObject.FindProperty("ServiceConfig");
                serviceConfig.isExpanded = EditorGUILayout.Foldout(serviceConfig.isExpanded, "Service Config");
                EditorGUI.indentLevel += 1;
                if (serviceConfig.isExpanded)
                {
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.ServerAddress"), true);
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.APIKey"), true);
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.APISecret"), true);
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.CloudRecognizerAppID"), true);
                }
                EditorGUI.indentLevel -= 1;
            }
            serializedObject.ApplyModifiedProperties();
        }
    }
}
