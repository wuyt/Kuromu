//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEngine;
using UnityEditor;

namespace easyar
{
    [CustomEditor(typeof (EasyARSettings), true)]
    public class EasyARSettingsEditor : Editor
    {
        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            EditorGUILayout.PropertyField(serializedObject.FindProperty("LicenseKey"), new GUIContent("EasyAR SDK License Key"), true);
            serializedObject.ApplyModifiedProperties();
        }
    }
}
