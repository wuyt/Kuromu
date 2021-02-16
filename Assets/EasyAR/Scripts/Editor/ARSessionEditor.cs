//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEditor;
using UnityEngine;

namespace easyar
{
    [CustomEditor(typeof(ARSession), true)]
    public class ARSessionEditor : Editor
    {
        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            if (((ARSession)target).AssembleMode == ARAssembly.AssembleMode.Manual)
            {
                var assembly = serializedObject.FindProperty("Assembly");
                assembly.isExpanded = EditorGUILayout.Foldout(assembly.isExpanded, "Assembly");
                EditorGUI.indentLevel += 1;
                if (assembly.isExpanded)
                {
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("Assembly.Camera"), true);
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("Assembly.CameraRoot"), true);
                    EditorGUILayout.PropertyField(serializedObject.FindProperty("Assembly.FrameSource"), true);
                    ShowListPropertyField("Assembly.RenderCameras", "Render Cameras");
                    ShowListPropertyField("Assembly.FrameFilters", "Frame Filters");
                }
                EditorGUI.indentLevel -= 1;
            }
            serializedObject.ApplyModifiedProperties();
        }

        private void ShowListPropertyField(string propertyPath, string label)
        {
            var list = serializedObject.FindProperty(propertyPath);
            list.isExpanded = EditorGUILayout.Foldout(list.isExpanded, label);
            EditorGUI.indentLevel += 1;
            if (list.isExpanded)
            {
                int count = Mathf.Max(0, EditorGUILayout.IntField("Size", list.arraySize));
                while (count < list.arraySize) { list.DeleteArrayElementAtIndex(list.arraySize - 1); }
                while (count > list.arraySize) { list.InsertArrayElementAtIndex(list.arraySize); }
                for (int i = 0; i < list.arraySize; i++) { EditorGUILayout.PropertyField(list.GetArrayElementAtIndex(i)); }
            }
            EditorGUI.indentLevel -= 1;
        }
    }
}
