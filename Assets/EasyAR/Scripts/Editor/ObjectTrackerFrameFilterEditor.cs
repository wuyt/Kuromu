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
    [CustomEditor(typeof (ObjectTrackerFrameFilter), true)]
    public class ObjectTrackerFrameFilterEditor : Editor
    {
        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            var simultaneousNum = serializedObject.FindProperty("simultaneousNum");
            EditorGUILayout.PropertyField(simultaneousNum, new GUIContent("Simultaneous Target Number"), true);
            serializedObject.ApplyModifiedProperties();
            ((ObjectTrackerFrameFilter)target).SimultaneousNum = simultaneousNum.intValue;
        }
    }
}
