using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace Kuromu
{
    public class PositionRecordController : MonoBehaviour
    {
        /// <summary>
        /// 导航状态
        /// </summary>
        private NavStatus navStatus;
        /// <summary>
        /// 玩家
        /// </summary>
        public Transform player;
        /// <summary>
        /// 终点
        /// </summary>
        private Transform arrival;
        /// <summary>
        /// 保存文件名
        /// </summary>
        private string fileName;
        /// <summary>
        /// 刷新速度
        /// </summary>
        public float refresh;
        /// <summary>
        /// 音频列表
        /// </summary>
        private List<string> record;
        /// <summary>
        /// 游戏控制
        /// </summary>
        private GameController game;

        public Transform tempPoint;

        public Transform map;



        void Start()
        {
            game = FindObjectOfType<GameController>();
            record = new List<string>();
            navStatus = NavStatus.waiting;
            fileName = "";
        }

        public void SelectButtonClicked(Transform btnTF)
        {
            CancelInvoke("Save");
            if (navStatus == NavStatus.navigation)
            {
                game.SaveByFileName(record.ToArray(), fileName);
                fileName = "";
                record.Clear();
            }
            arrival = btnTF.GetComponent<SelectButton>().arrival;
            InvokeRepeating("Save", 0, refresh);
        }

        private void Save()
        {
            string strSave = "";
            //strSave = player.position + "," + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:ffff") + "," + (int)navStatus;
            strSave = GetSaveString();
            record.Add(strSave);
            if (fileName.EndsWith(""))
            {
                fileName = DateTime.Now.ToString("yyyyMMdd-HH-mm-ss") + ".txt";
            }
            if (navStatus == NavStatus.waiting)
            {
                navStatus = NavStatus.navigation;
            }

            float temp = (player.position - arrival.position).magnitude;
            if (temp < game.endDistance)
            {
                CancelInvoke("Save");
                navStatus = NavStatus.end;
                // strSave = player.position + "," + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:ffff") + "," + (int)navStatus;
                strSave = GetSaveString();
                record.Add(strSave);
                game.SaveByFileName(record.ToArray(), fileName);

                fileName = "";
                navStatus = NavStatus.waiting;
                record.Clear();
            }
        }

        private string GetSaveString()
        {
            string strReturn = "";
            tempPoint.parent = null;
            tempPoint.position = player.position;
            tempPoint.parent = map;
            strReturn = tempPoint.localPosition + "," + DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss:ffff") + "," + (int)navStatus;
            return strReturn;
        }

    }
    /// <summary>
    /// 导航状态
    /// </summary>
    public enum NavStatus
    {
        /// <summary>
        /// 等待
        /// </summary>
        waiting,
        /// <summary>
        /// 导航
        /// </summary>
        navigation,
        /// <summary>
        /// 结束
        /// </summary>
        end
    }
}

