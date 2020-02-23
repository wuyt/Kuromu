//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace easyar
{
    public class GUIPopup : MonoBehaviour
    {
        private static GUIPopup popup;
        private readonly Queue<KeyValuePair<string, float>> messageQueue = new Queue<KeyValuePair<string, float>>();
        private bool isShowing;
        private bool isDisappearing;
        private GUISkin skin;

        private void Start()
        {
            skin = Instantiate(Resources.Load<GUISkin>("EasyAR/GUISkin/GUISkin"));
            StartCoroutine(ShowMessage());
        }

        private void OnDestroy()
        {
            if (skin)
            {
                Destroy(skin);
            }
        }

        public static void EnqueueMessage(string message, float seconds)
        {
            if (EasyARController.Instance && !EasyARController.Instance.ShowPopupMessage)
            {
                Debug.Log(message);
                return;
            }

            if (popup == null)
            {
                var go = new GameObject("MessagePopup");
                popup = go.AddComponent<GUIPopup>();
            }
            popup.messageQueue.Enqueue(new KeyValuePair<string, float>(message, seconds));
        }

        private IEnumerator ShowMessage()
        {
            while (true)
            {
                if (EasyARController.Instance && !EasyARController.Instance.ShowPopupMessage)
                {
                    while (messageQueue.Count > 0)
                    {
                        var message = messageQueue.Dequeue();
                        Debug.Log(message);
                    }
                }

                if (messageQueue.Count > 0)
                {
                    if (skin)
                    {
                        var color = skin.GetStyle("box").normal.textColor;
                        color.a = 0;
                        skin.GetStyle("box").normal.textColor = color;
                    }

                    isShowing = true;
                    isDisappearing = false;

                    var time = messageQueue.Peek().Value;
                    yield return new WaitForSeconds(time > 1 ? time - 0.5f : time / 2);
                    isDisappearing = true;
                    yield return new WaitForSeconds(time > 1 ? 0.5f : time / 2);

                    messageQueue.Dequeue();
                    isShowing = false;
                }
                else
                {
                    yield return 0;
                }
            }
        }

        private void OnGUI()
        {
            if (!isShowing || !skin)
            {
                return;
            }

            var color = skin.GetStyle("box").normal.textColor;
            color.a += isDisappearing ? -Time.deltaTime * 2 : Time.deltaTime * 2;
            color.a = color.a > 1 ? 1 : (color.a < 0 ? 0 : color.a);
            skin.GetStyle("box").normal.textColor = color;
            GUI.Box(new Rect(0, Screen.height / 2, Screen.width, Math.Min(Screen.height / 4, 160)), messageQueue.Peek().Key, skin.GetStyle("box"));
        }
    }

    public class UIPopupException : Exception
    {
        public UIPopupException(string message, float seconds) : base(message)
        {
            GUIPopup.EnqueueMessage(message, seconds);
        }

        public UIPopupException(string message) : this(message, 10)
        {
        }
    }
}
