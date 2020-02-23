using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using System.IO;

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

        private string pathKeyPoints;

        private string pathRoads;

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

            pathKeyPoints = Application.persistentDataPath + "/keypoints.txt";
            pathRoads = Application.persistentDataPath + "roads.txt";
        }

        void Start()
        {
            txtShow = transform.GetComponentInChildren<Text>();
            txtShow.gameObject.SetActive(false);
        }

        #region 提示信息
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

        #endregion

        #region 读取关键点和路径

        public void SaveKeyPoints(string[] jsons)
        {
            SaveStringArray(jsons, pathKeyPoints);
        }

        public List<string> LoadKeyPoins()
        {
            return LoadStringList(pathKeyPoints);
        }

        public void SaveRoads(string[] jsons)
        {
            SaveStringArray(jsons, pathRoads);
        }

        public List<string> LoadRoads()
        {
            return LoadStringList(pathRoads);
        }

        private void SaveStringArray(string[] stringArray, string path)
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(path))
                {
                    foreach (var s in stringArray)
                    {
                        writer.WriteLine(s);
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.Log(ex.Message);
            }
        }

        private List<string> LoadStringList(string path)
        {
            List<string> list = new List<string>();
            try
            {
                using (StreamReader reader = new StreamReader(path))
                {
                    while (!reader.EndOfStream)
                    {
                        list.Add(reader.ReadLine());
                    }
                }
            }
            catch (Exception ex)
            {
                Debug.Log(ex.Message);
            }
            return list;
        }

        #endregion
    }
}

