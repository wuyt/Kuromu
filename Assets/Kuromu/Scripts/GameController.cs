using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using System.IO;

namespace Kuromu
{
    /// <summary>
    /// 游戏控制
    /// </summary>
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
        /// <summary>
        /// 关键点存储路径
        /// </summary>
        private string pathKeyPoints;
        /// <summary>
        /// 导航路径存储路径
        /// </summary>
        private string pathRoads;
        /// <summary>
        /// 到达终点判断距离
        /// </summary>
        public float endDistance;

        void Awake()
        {
            //实现单实例
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
            pathRoads = Application.persistentDataPath + "/roads.txt";
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
        /// <param name="message">信息</param>
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
        /// <summary>
        /// 根据文件名保存
        /// </summary>
        /// <param name="stringArray"></param>
        /// <param name="fileName"></param>
        public void SaveByFileName(string[] stringArray, string fileName)
        {
            SaveStringArray(stringArray, Application.persistentDataPath + "/" + fileName);
        }


        #region 读取关键点和路径
        /// <summary>
        /// 保存关键点
        /// </summary>
        /// <param name="jsons">json字符串数组</param>
        public void SaveKeyPoints(string[] jsons)
        {
            SaveStringArray(jsons, pathKeyPoints);
        }
        /// <summary>
        /// 加载关键点
        /// </summary>
        /// <returns>关键点json列表</returns>
        public List<string> LoadKeyPoins()
        {
            return LoadStringList(pathKeyPoints);
        }
        /// <summary>
        /// 保存路径
        /// </summary>
        /// <param name="jsons">json字符串数组</param>
        public void SaveRoads(string[] jsons)
        {
            SaveStringArray(jsons, pathRoads);
        }
        /// <summary>
        /// 加载路径
        /// </summary>
        /// <returns>路径json列表</returns>
        public List<string> LoadRoads()
        {
            return LoadStringList(pathRoads);
        }
        /// <summary>
        /// 保存字符串数组
        /// </summary>
        /// <param name="stringArray">字符串数组</param>
        /// <param name="path">保存路径</param>
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
        /// <summary>
        /// 读取文本信息
        /// </summary>
        /// <param name="path">文本路径</param>
        /// <returns>字符串列表</returns>
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

