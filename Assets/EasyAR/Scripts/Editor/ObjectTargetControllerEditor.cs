//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEditor;
using UnityEngine;

namespace easyar
{
    [CustomEditor(typeof(ObjectTargetController), true)]
    public class ObjectTargetControllerEditor : Editor
    {
        private float scale = 1;
        private float scaleX = 1;
        private bool horizontalFlip;

        public void OnEnable()
        {
            UpdateScale((ObjectTargetController)target, scale);
        }

        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            var controller = (ObjectTargetController)target;

            switch (controller.SourceType)
            {
                case ObjectTargetController.DataSource.ObjFile:
                    var imageFileSource = serializedObject.FindProperty("ObjFileSource");
                    imageFileSource.isExpanded = EditorGUILayout.Foldout(imageFileSource.isExpanded, "Obj File Source");
                    EditorGUI.indentLevel += 1;
                    if (imageFileSource.isExpanded)
                    {
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ObjFileSource.PathType"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ObjFileSource.ObjPath"), true);
                        ShowListPropertyField("ObjFileSource.ExtraFilePaths", "Extra File Paths");
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ObjFileSource.Name"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ObjFileSource.Scale"), true);
                    }
                    EditorGUI.indentLevel -= 1;
                    break;
                default:
                    break;
            }

            var tracker = serializedObject.FindProperty("tracker");
            EditorGUILayout.PropertyField(tracker, new GUIContent("Tracker"), true);

            var trackerHasSet = serializedObject.FindProperty("trackerHasSet");
            if (!trackerHasSet.boolValue)
            {
                if (!tracker.objectReferenceValue)
                {
                    tracker.objectReferenceValue = FindObjectOfType<ObjectTrackerFrameFilter>();
                }
                if (tracker.objectReferenceValue)
                {
                    trackerHasSet.boolValue = true;
                }
            }
            serializedObject.ApplyModifiedProperties();
            controller.Tracker = (ObjectTrackerFrameFilter)tracker.objectReferenceValue;

            if (Event.current.type == EventType.Used)
            {
                foreach (var obj in DragAndDrop.objectReferences)
                {
                    var objg = obj as GameObject;
                    if (objg && objg.GetComponent<ObjectTrackerFrameFilter>() && !AssetDatabase.GetAssetPath(obj).Equals(""))
                        DragAndDrop.visualMode = DragAndDropVisualMode.Rejected;
                }
            }

            CheckScale();
        }

        void CheckScale()
        {
            if (Application.isPlaying)
            {
                return;
            }
            var controller = (ObjectTargetController)target;
            if (controller.SourceType == ObjectTargetController.DataSource.ObjFile)
            {
                if (scale != controller.ObjFileSource.Scale)
                {
                    UpdateScale(controller, controller.ObjFileSource.Scale);
                }
                else if (scaleX != controller.transform.localScale.x)
                {
                    controller.ObjFileSource.Scale = Math.Abs(controller.transform.localScale.x);
                    UpdateScale(controller, controller.ObjFileSource.Scale);
                }
                else if (scale != controller.transform.localScale.y)
                {
                    controller.ObjFileSource.Scale = Math.Abs(controller.transform.localScale.y);
                    UpdateScale(controller, controller.ObjFileSource.Scale);
                }
                else if (scale != controller.transform.localScale.z)
                {
                    controller.ObjFileSource.Scale = Math.Abs(controller.transform.localScale.z);
                    UpdateScale(controller, controller.ObjFileSource.Scale);
                }
                else if (horizontalFlip != controller.HorizontalFlip)
                {
                    UpdateScale(controller, controller.ObjFileSource.Scale);
                }
            }
            else
            {
                if (horizontalFlip != controller.HorizontalFlip || scaleX != controller.transform.localScale.x || scale != controller.transform.localScale.y || scale != controller.transform.localScale.z)
                {
                    UpdateScale(controller, scale);
                }
            }
        }

        private void UpdateScale(ObjectTargetController controller, float s)
        {
            if (Application.isPlaying)
            {
                return;
            }
            var vec3Unit = Vector3.one;
            if (controller.HorizontalFlip)
            {
                vec3Unit.x = -vec3Unit.x;
            }
            controller.transform.localScale = vec3Unit * s;

            scale = s;
            scaleX = controller.transform.localScale.x;
            horizontalFlip = controller.HorizontalFlip;
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

        [DrawGizmo(GizmoType.Active | GizmoType.Pickable | GizmoType.NotInSelectionHierarchy | GizmoType.InSelectionHierarchy)]
        static void DrawGizmo(ObjectTargetController scr, GizmoType gizmoType)
        {
            if (!EasyARController.Settings.GizmoConfig.ObjectTarget.Enable) { return; }

            Gizmos.color = Color.white;
            var boundingBox = scr.BoundingBox;
            if (boundingBox.Count == 8)
            {
                var scale = scr.Target.scale();
                for (int i = 0; i < 8; ++i)
                {
                    boundingBox[i] = scr.transform.localToWorldMatrix.MultiplyPoint(boundingBox[i] / scale);
                }
                Gizmos.DrawLine(boundingBox[0], boundingBox[1]);
                Gizmos.DrawLine(boundingBox[1], boundingBox[2]);
                Gizmos.DrawLine(boundingBox[2], boundingBox[3]);
                Gizmos.DrawLine(boundingBox[3], boundingBox[0]);
                Gizmos.DrawLine(boundingBox[4], boundingBox[5]);
                Gizmos.DrawLine(boundingBox[5], boundingBox[6]);
                Gizmos.DrawLine(boundingBox[6], boundingBox[7]);
                Gizmos.DrawLine(boundingBox[7], boundingBox[4]);
                Gizmos.DrawLine(boundingBox[0], boundingBox[4]);
                Gizmos.DrawLine(boundingBox[1], boundingBox[5]);
                Gizmos.DrawLine(boundingBox[2], boundingBox[6]);
                Gizmos.DrawLine(boundingBox[3], boundingBox[7]);
            }
        }
    }
}
