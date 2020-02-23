using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;

namespace Kuromu
{
    public class GameController : MonoBehaviour
    {
        private static GameController instance = null;
        /// <summary>
        /// 输入的地图名称
        /// </summary>
        public string inputName;
        /// <summary>
        /// 显示信息文本框
        /// </summary>
        private Text txtShow;

        void Awake()
        {
            if (instance == null)
            {
                instance = this;
                DontDestroyOnLoad(gameObject);
            }
            else if (this != instance)
            {
                Destroy(gameObject);
            }
        }

        void Start()
        {
            txtShow = transform.GetComponentInChildren<Text>();
            txtShow.gameObject.SetActive(false);
        }

        /// <summary>
        /// /// 显示信息
        /// </summary>
        /// <param name="message"></param>
        public void ShowMessage(string message)
        {
            StopCoroutine("EndShowMessage");
            txtShow.gameObject.SetActive(true);
            txtShow.text = message;
            StartCoroutine("EndShowMessage");
        }
        /// <summary>
        /// 隐藏信息
        /// </summary>
        /// <returns></returns>
        private IEnumerator EndShowMessage()
        {
            yield return new WaitForSeconds(4f);
            txtShow.text = "";
            txtShow.gameObject.SetActive(false);
        }
    }
}

