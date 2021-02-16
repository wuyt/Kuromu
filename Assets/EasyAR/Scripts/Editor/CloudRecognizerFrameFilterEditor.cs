//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
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
                var keyType = serializedObject.FindProperty("ServerKeyType");
                EditorGUILayout.PropertyField(keyType, true);
                switch (keyType.enumValueIndex)
                {
                    case (int)CloudRecognizerFrameFilter.KeyType.Public:
                        var apiServiceConfig = serializedObject.FindProperty("ServiceConfig");
                        apiServiceConfig.isExpanded = EditorGUILayout.Foldout(apiServiceConfig.isExpanded, "Service Config");
                        EditorGUI.indentLevel += 1;
                        if (apiServiceConfig.isExpanded)
                        {
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.ServerAddress"), true);
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.APIKey"), true);
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.APISecret"), true);
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("ServiceConfig.CloudRecognizerAppID"), true);
                        }
                        EditorGUI.indentLevel -= 1;
                        break;

                    case (int)CloudRecognizerFrameFilter.KeyType.Private:
                        var cloudServiceConfig = serializedObject.FindProperty("PrivateServiceConfig");
                        cloudServiceConfig.isExpanded = EditorGUILayout.Foldout(cloudServiceConfig.isExpanded, "Private Service Config");
                        EditorGUI.indentLevel += 1;
                        if (cloudServiceConfig.isExpanded)
                        {
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("PrivateServiceConfig.ServerAddress"), true);
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("PrivateServiceConfig.CloudRecognitionServiceSecret"), true);
                            EditorGUILayout.PropertyField(serializedObject.FindProperty("PrivateServiceConfig.CloudRecognizerAppID"), true);
                        }
                        EditorGUI.indentLevel -= 1;
                        break;
                    default:
                        break;
                }
            }
            serializedObject.ApplyModifiedProperties();
        }
    }
}
