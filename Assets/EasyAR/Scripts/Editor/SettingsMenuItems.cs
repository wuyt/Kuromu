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
    public class LicenseKeyWindow : EditorWindow
    {
        [MenuItem("EasyAR/Change License Key")]
        private static void OpenTheWindow()
        {
            Selection.SetActiveObjectWithContext(EasyARController.Settings, null);
        }
    }

    public class SpatialMapServiceConfigWindow : EditorWindow
    {
        [MenuItem("EasyAR/Change Global Spatial Map Service Config")]
        private static void OpenTheWindow()
        {
            Selection.SetActiveObjectWithContext(EasyARController.Settings, null);
        }
    }

    public class CloudRecognizerServiceConfigWindow : EditorWindow
    {
        [MenuItem("EasyAR/Change Global Cloud Recognizer Service Config")]
        private static void OpenTheWindow()
        {
            Selection.SetActiveObjectWithContext(EasyARController.Settings, null);
        }
    }

    public class GizmoConfigWindow : EditorWindow
    {
        [MenuItem("EasyAR/Change Gizmo Config")]
        private static void OpenTheWindow()
        {
            Selection.SetActiveObjectWithContext(EasyARController.Settings, null);
        }
    }
}
