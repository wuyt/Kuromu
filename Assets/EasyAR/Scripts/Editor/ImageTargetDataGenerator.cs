//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.IO;
using UnityEditor;
using UnityEngine;

namespace easyar
{
    public class ImageTargetDataGenerator : EditorWindow
    {
        private GenerateType generateType;
        private string outputPathDir;
        private string imagePaths = "Try drop images here";
        private Texture2D texture;
        private float targetScale = 0.1f;
        private string targetName = string.Empty;

        enum GenerateType
        {
            Image,
            ImageList,
            Texture,
        }

        [MenuItem("EasyAR/Image Target Data")]
        private static void OpenTheWindow()
        {
            var win = GetWindow(typeof(ImageTargetDataGenerator));
            win.minSize = new Vector2(250, 400);
            win.titleContent = new GUIContent("ImageTarget");
            win.Show();
        }

        private void OnEnable()
        {
            if (!EasyARController.Initialized)
            {
                EasyARController.GlobalInitialization();
            }
            outputPathDir = Application.streamingAssetsPath;
        }

        private void OnGUI()
        {
            if (!EasyARController.Initialized || !string.IsNullOrEmpty(Engine.errorMessage()))
            {
                if (GUI.Button(new Rect(20, 20, position.width - 40, 30), "Apply License Key Change"))
                {
                    Selection.SetActiveObjectWithContext(EasyARController.Settings, null);
                    EasyARController.GlobalInitialization();
                }
                var textStyle = new GUIStyle(EditorStyles.label);
                textStyle.normal.textColor = Color.red;
                EditorGUI.LabelField(new Rect(20, 60, position.width - 40, 20), Engine.errorMessage(), textStyle);
                return;
            }

            if (generateType == GenerateType.Image || generateType == GenerateType.ImageList)
            {
                if (Event.current.type == EventType.DragUpdated)
                {
                    foreach (var path in DragAndDrop.paths)
                    {
                        var ext = Path.GetExtension(path).ToLower();
                        if (ext == ".jpg" || ext == ".png" || ext == ".bmp")
                        {
                            DragAndDrop.visualMode = DragAndDropVisualMode.Generic;
                            break;
                        }
                    }
                }
            }

            var yPosition = 20;
            EditorGUI.LabelField(new Rect(20, yPosition, 100, 30), "Generate From");
            generateType = (GenerateType)EditorGUI.EnumPopup(new Rect(120, yPosition, 100, 30), generateType);
            yPosition += 30;

            switch (generateType)
            {
                case GenerateType.Image:
                    if (Event.current.type == EventType.DragExited)
                    {
                        imagePaths = string.Empty;
                        foreach (var path in DragAndDrop.paths)
                        {
                            var ext = Path.GetExtension(path).ToLower();
                            if (ext == ".jpg" || ext == ".png" || ext == ".bmp")
                            {
                                imagePaths = path;
                                if (File.Exists(path))
                                {
                                    targetName = GetNameFromPath(path);
                                }
                                break;
                            }
                        }
                        Repaint();
                    }

                    GUI.Label(new Rect(20, yPosition, 120, 20), "Image Path");
                    yPosition += 20;
                    imagePaths = EditorGUI.TextArea(new Rect(20, yPosition, position.width - 40, 30), imagePaths);
                    yPosition += 30 + 30;
                    if (string.IsNullOrEmpty(targetName))
                    {
                        foreach (var path in imagePaths.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries))
                        {
                            if (File.Exists(path))
                            {
                                targetName = GetNameFromPath(path);
                            }
                            break;
                        }
                    }

                    targetName = EditorGUI.TextField(new Rect(20, yPosition, position.width - 40, 20), "Name:", targetName);
                    yPosition += 20;
                    targetScale = EditorGUI.FloatField(new Rect(20, yPosition, position.width - 40, 20), "Scale (m):", targetScale);
                    break;
                case GenerateType.ImageList:
                    if (Event.current.type == EventType.DragExited)
                    {
                        imagePaths = string.Empty;
                        foreach (var path in DragAndDrop.paths)
                        {
                            var ext = Path.GetExtension(path).ToLower();
                            if (ext == ".jpg" || ext == ".png" || ext == ".bmp")
                            {
                                imagePaths += path + Environment.NewLine;
                            }
                        }
                        Repaint();
                    }
                    GUI.Label(new Rect(20, yPosition, 120, 20), "Image Paths");
                    yPosition += 20;
                    imagePaths = EditorGUI.TextArea(new Rect(20, yPosition, position.width - 40, 100), imagePaths);
                    yPosition += 100 + 30;

                    EditorGUI.LabelField(new Rect(20, yPosition, position.width - 40, 20), "Name: (Filename is Used)");
                    yPosition += 20;
                    targetScale = EditorGUI.FloatField(new Rect(20, yPosition, position.width - 40, 20), "Scale (m):", targetScale);
                    break;
                case GenerateType.Texture:
                    GUI.Label(new Rect(20, yPosition, 120, 20), "Texture");
                    yPosition += 20;
                    texture = EditorGUI.ObjectField(new Rect(20, yPosition, 80, 80), texture, typeof(Texture2D), false) as Texture2D;
                    yPosition += 80 + 30;
                    if (!string.IsNullOrEmpty(AssetDatabase.GetAssetPath(texture)))
                    {
                        targetName = GetNameFromPath(AssetDatabase.GetAssetPath(texture));
                    }

                    targetName = EditorGUI.TextField(new Rect(20, yPosition, position.width - 40, 20), "Name:", targetName);
                    yPosition += 20;
                    targetScale = EditorGUI.FloatField(new Rect(20, yPosition, position.width - 40, 20), "Scale (m):", targetScale);
                    break;
                default:
                    break;
            }

            EditorGUI.LabelField(new Rect(20, position.height - 50 - 40 - 20, 160, 20), "Generate To");
            outputPathDir = EditorGUI.TextArea(new Rect(20, position.height - 50 - 40, position.width - 40, 20), outputPathDir);

            if (GUI.Button(new Rect(20, position.height - 50, position.width - 40, 30), "Generate"))
            {
                try
                {
                    switch (generateType)
                    {
                        case GenerateType.Image:
                            foreach (var path in imagePaths.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries))
                            {
                                CreateTargetFileByByteArray(File.ReadAllBytes(path), targetName);
                                break;
                            }
                            break;
                        case GenerateType.ImageList:
                            foreach (var path in imagePaths.Split(new string[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries))
                            {
                                if (!File.Exists(path))
                                {
                                    continue;
                                }
                                var ext = Path.GetExtension(path).ToLower();
                                if (ext == ".jpg" || ext == ".png" || ext == ".bmp")
                                {
                                    CreateTargetFileByByteArray(File.ReadAllBytes(path), GetNameFromPath(path));
                                }
                            }
                            break;
                        case GenerateType.Texture:
                            var filePath = AssetDatabase.GetAssetPath(texture);
                            if (filePath.StartsWith("Assets/"))
                            {
                                filePath = filePath.Substring(6);
                            }
                            else
                            {
                                throw new Exception("invalid image file: " + filePath);
                            }
                            var texturePath = Application.dataPath + filePath;
                            CreateTargetFileByByteArray(File.ReadAllBytes(texturePath), targetName);
                            break;
                        default:
                            break;
                    }
                }
                catch (Exception e)
                {
                    Debug.LogError(e.Message);
                }
            }
        }

        private string GetNameFromPath(string path)
        {
            var name = string.Empty;
            try
            {
                name = Path.GetFileNameWithoutExtension(path);
            }
            catch (Exception)
            {
            }
            if (name == null)
            {
                name = string.Empty;
            }
            return name;
        }

        private void CreateTargetFileByByteArray(byte[] data, string name)
        {
            using (Buffer buffer = Buffer.wrapByteArray(data))
            {
                var imageOptional = ImageHelper.decode(buffer);
                if (imageOptional.OnNone)
                {
                    throw new Exception("invalid image data");
                }
                using (var image = imageOptional.Value)
                using (var param = new ImageTargetParameters())
                {
                    var uid = Guid.NewGuid().ToString();
                    param.setImage(image);
                    param.setName(name);
                    param.setScale(targetScale);
                    param.setUid(uid);
                    param.setMeta(string.Empty);
                    var targetOptional = ImageTarget.createFromParameters(param);
                    if (targetOptional.OnNone)
                    {
                        throw new Exception("invalid parameter");
                    }

                    if (!Directory.Exists(outputPathDir))
                    {
                        Directory.CreateDirectory(outputPathDir);
                    }
                    var path = outputPathDir + "/" + (string.IsNullOrEmpty(name) ? uid : name) + ".etd";
                    if (targetOptional.Value.save(path))
                    {
                        Debug.Log("Created etd: " + path);
                    }
                    else
                    {
                        Debug.LogWarning("Fail to create etd: " + path);
                    }
                }
            }
        }
    }
}
