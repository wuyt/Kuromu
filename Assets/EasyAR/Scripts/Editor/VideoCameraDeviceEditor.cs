//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEngine;
using UnityEditor;

namespace easyar
{
    [CustomEditor(typeof (VideoCameraDevice), true)]
    public class VideoCameraDeviceEditor : Editor
    {
        CameraDevicePreference preference;

        public void OnEnable()
        {
            preference = ((VideoCameraDevice)target).CameraPreference;
        }

        public override void OnInspectorGUI()
        {
            DrawDefaultInspector();
            if (((VideoCameraDevice)target).CameraOpenMethod == VideoCameraDevice.CameraDeviceOpenMethod.DeviceType)
            {
                EditorGUILayout.PropertyField(serializedObject.FindProperty("CameraType"), true);
            }
            else
            {
                EditorGUILayout.PropertyField(serializedObject.FindProperty("CameraIndex"), true);
            }
            var cameraPreference = serializedObject.FindProperty("cameraPreference");
            EditorGUILayout.PropertyField(cameraPreference, new GUIContent("Camera Preference"), true);
            serializedObject.ApplyModifiedProperties();
            if(preference != (CameraDevicePreference)cameraPreference.enumValueIndex)
            {
                ((VideoCameraDevice)target).CameraPreference = (CameraDevicePreference)cameraPreference.enumValueIndex;
                preference = (CameraDevicePreference)cameraPreference.enumValueIndex;
            }
        }
    }
}
