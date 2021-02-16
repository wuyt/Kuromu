//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using UnityEditor;
using UnityEngine;

namespace easyar
{
    [CustomEditor(typeof(ImageTargetController), true)]
    public class ImageTargetControllerEditor : Editor
    {
        public void OnEnable()
        {
            var controller = (ImageTargetController)target;
            UpdateScale(controller, controller.GizmoData.Scale);
        }

        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            var controller = (ImageTargetController)target;

            switch (controller.SourceType)
            {
                case ImageTargetController.DataSource.ImageFile:
                    var imageFileSource = serializedObject.FindProperty("ImageFileSource");
                    imageFileSource.isExpanded = EditorGUILayout.Foldout(imageFileSource.isExpanded, "Image File Source");
                    EditorGUI.indentLevel += 1;
                    if (imageFileSource.isExpanded)
                    {
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ImageFileSource.PathType"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ImageFileSource.Path"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ImageFileSource.Name"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("ImageFileSource.Scale"), true);
                    }
                    EditorGUI.indentLevel -= 1;
                    break;
                case ImageTargetController.DataSource.TargetDataFile:
                    var targetDataFileSource = serializedObject.FindProperty("TargetDataFileSource");
                    targetDataFileSource.isExpanded = EditorGUILayout.Foldout(targetDataFileSource.isExpanded, "Target Data File Source");
                    EditorGUI.indentLevel += 1;
                    if (targetDataFileSource.isExpanded)
                    {
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("TargetDataFileSource.PathType"), true);
                        EditorGUILayout.PropertyField(serializedObject.FindProperty("TargetDataFileSource.Path"), true);
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
                    tracker.objectReferenceValue = FindObjectOfType<ImageTrackerFrameFilter>();
                }
                if (tracker.objectReferenceValue)
                {
                    trackerHasSet.boolValue = true;
                }
            }
            serializedObject.ApplyModifiedProperties();
            controller.Tracker = (ImageTrackerFrameFilter)tracker.objectReferenceValue;

            if (Event.current.type == EventType.Used)
            {
                foreach (var obj in DragAndDrop.objectReferences)
                {
                    var objg = obj as GameObject;
                    if (objg && objg.GetComponent<ImageTrackerFrameFilter>() && !AssetDatabase.GetAssetPath(obj).Equals(""))
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
            var controller = (ImageTargetController)target;
            if (controller.SourceType == ImageTargetController.DataSource.ImageFile)
            {
                if (controller.GizmoData.Scale != controller.ImageFileSource.Scale)
                {
                    UpdateScale(controller, controller.ImageFileSource.Scale);
                }
                else if (controller.GizmoData.ScaleX != controller.transform.localScale.x)
                {
                    controller.ImageFileSource.Scale = Math.Abs(controller.transform.localScale.x);
                    UpdateScale(controller, controller.ImageFileSource.Scale);
                }
                else if (controller.GizmoData.Scale != controller.transform.localScale.y)
                {
                    controller.ImageFileSource.Scale = Math.Abs(controller.transform.localScale.y);
                    UpdateScale(controller, controller.ImageFileSource.Scale);
                }
                else if (controller.GizmoData.Scale != controller.transform.localScale.z)
                {
                    controller.ImageFileSource.Scale = Math.Abs(controller.transform.localScale.z);
                    UpdateScale(controller, controller.ImageFileSource.Scale);
                }
                else if (controller.GizmoData.HorizontalFlip != controller.HorizontalFlip)
                {
                    UpdateScale(controller, controller.ImageFileSource.Scale);
                }
            }
            else
            {
                if (controller.GizmoData.HorizontalFlip != controller.HorizontalFlip || controller.GizmoData.ScaleX != controller.transform.localScale.x || controller.GizmoData.Scale != controller.transform.localScale.y || controller.GizmoData.Scale != controller.transform.localScale.z)
                {
                    UpdateScale(controller, controller.GizmoData.Scale);
                }
            }
        }

        static private void UpdateScale(ImageTargetController controller, float s)
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

            controller.GizmoData.Scale = s;
            controller.GizmoData.ScaleX = controller.transform.localScale.x;
            controller.GizmoData.HorizontalFlip = controller.HorizontalFlip;
        }

        [DrawGizmo(GizmoType.Active | GizmoType.Pickable | GizmoType.NotInSelectionHierarchy | GizmoType.InSelectionHierarchy)]
        static void DrawGizmo(ImageTargetController scr, GizmoType gizmoType)
        {
            var signature = scr.SourceType.ToString();
            switch (scr.SourceType)
            {
                case ImageTargetController.DataSource.ImageFile:
                    if (!EasyARController.Settings.GizmoConfig.ImageTarget.EnableImageFile) { return; }
                    signature += scr.ImageFileSource.PathType.ToString() + scr.ImageFileSource.Path;
                    break;
                case ImageTargetController.DataSource.TargetDataFile:
                    if (!EasyARController.Settings.GizmoConfig.ImageTarget.EnableTargetDataFile) { return; }
                    signature += scr.TargetDataFileSource.PathType.ToString() + scr.TargetDataFileSource.Path;
                    break;
                case ImageTargetController.DataSource.Target:
                    if (!EasyARController.Settings.GizmoConfig.ImageTarget.EnableTarget) { return; }
                    if (scr.Target != null)
                    {
                        signature += scr.Target.runtimeID().ToString();
                    }
                    break;
                default:
                    break;
            }

            if (scr.GizmoData.Material == null)
            {
                scr.GizmoData.Material = new Material(Shader.Find("EasyAR/ImageTargetGizmo"));
            }
            if (scr.GizmoData.Signature != signature)
            {
                if (scr.GizmoData.Texture != null)
                {
                    UnityEngine.Object.DestroyImmediate(scr.GizmoData.Texture);
                    scr.GizmoData.Texture = null;
                }

                string path;
                switch (scr.SourceType)
                {
                    case ImageTargetController.DataSource.ImageFile:
                        path = scr.ImageFileSource.Path;
                        if (scr.ImageFileSource.PathType == PathType.StreamingAssets)
                        {
                            path = Application.streamingAssetsPath + "/" + scr.ImageFileSource.Path;
                        }
                        if (System.IO.File.Exists(path))
                        {
                            var sourceData = System.IO.File.ReadAllBytes(path);
                            scr.GizmoData.Texture = new Texture2D(2, 2);
                            scr.GizmoData.Texture.LoadImage(sourceData);
                            scr.GizmoData.Texture.Apply();
                            UpdateScale(scr, scr.ImageFileSource.Scale);
                            if (SceneView.lastActiveSceneView)
                            {
                                SceneView.lastActiveSceneView.Repaint();
                            }
                        }
                        break;
                    case ImageTargetController.DataSource.TargetDataFile:
                        path = scr.TargetDataFileSource.Path;
                        if (scr.TargetDataFileSource.PathType == PathType.StreamingAssets)
                        {
                            path = Application.streamingAssetsPath + "/" + scr.TargetDataFileSource.Path;
                        }
                        if (System.IO.File.Exists(path))
                        {
                            if (!EasyARController.Initialized)
                            {
                                EasyARController.GlobalInitialization();
                                if (!EasyARController.Initialized)
                                {
                                    Debug.LogWarning("EasyAR Sense target data gizmo enabled but license key validation failed, target data gizmo will not show");
                                }
                            }
                            var sourceData = System.IO.File.ReadAllBytes(path);

                            using (Buffer buffer = Buffer.wrapByteArray(sourceData))
                            {
                                var targetOptional = ImageTarget.createFromTargetData(buffer);
                                if (targetOptional.OnSome)
                                {
                                    using (ImageTarget target = targetOptional.Value)
                                    {
                                        var imageList = target.images();
                                        if (imageList.Count > 0)
                                        {
                                            var image = imageList[0];
                                            scr.GizmoData.Texture = new Texture2D(image.width(), image.height(), TextureFormat.R8, false);
                                            scr.GizmoData.Texture.LoadRawTextureData(image.buffer().data(), image.buffer().size());
                                            scr.GizmoData.Texture.Apply();
                                        }
                                        foreach (var image in imageList)
                                        {
                                            image.Dispose();
                                        }
                                        UpdateScale(scr, target.scale());
                                        if (SceneView.lastActiveSceneView)
                                        {
                                            SceneView.lastActiveSceneView.Repaint();
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case ImageTargetController.DataSource.Target:
                        if (scr.Target != null)
                        {
                            var imageList = (scr.Target as ImageTarget).images();
                            if (imageList.Count > 0)
                            {
                                var image = imageList[0];
                                scr.GizmoData.Texture = new Texture2D(image.width(), image.height(), TextureFormat.R8, false);
                                scr.GizmoData.Texture.LoadRawTextureData(image.buffer().data(), image.buffer().size());
                                scr.GizmoData.Texture.Apply();
                            }
                            foreach (var image in imageList)
                            {
                                image.Dispose();
                            }
                            UpdateScale(scr, (scr.Target as ImageTarget).scale());
                            if (SceneView.lastActiveSceneView)
                            {
                                SceneView.lastActiveSceneView.Repaint();
                            }
                        }
                        break;
                    default:
                        break;
                }

                if (scr.GizmoData.Texture == null)
                {
                    scr.GizmoData.Texture = new Texture2D(2, 2);
                    scr.GizmoData.Texture.LoadImage(new byte[0]);
                    scr.GizmoData.Texture.Apply();
                }
                scr.GizmoData.Signature = signature;
            }

            if (scr.GizmoData.Material && scr.GizmoData.Texture)
            {
                scr.GizmoData.Material.SetMatrix("_Transform", scr.transform.localToWorldMatrix);
                if (scr.GizmoData.Texture.format == TextureFormat.R8)
                {
                    scr.GizmoData.Material.SetInt("_isRenderGrayTexture", 1);
                }
                else
                {
                    scr.GizmoData.Material.SetInt("_isRenderGrayTexture", 0);
                }
                scr.GizmoData.Material.SetFloat("_Ratio", (float)scr.GizmoData.Texture.height / scr.GizmoData.Texture.width);
                Gizmos.DrawGUITexture(new Rect(0, 0, 1, 1), scr.GizmoData.Texture, scr.GizmoData.Material);
            }
        }
    }
}
