using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using easyar;
using System;

namespace Kuromu
{
    public class BuildMapController : MonoBehaviour
    {
        private GameController gameController;
        /// <summary>
        /// 保存按钮
        /// </summary>
        private Button btnSave;

        private ARSession session;
        private SparseSpatialMapWorkerFrameFilter mapWorker;
        private SparseSpatialMapController map;

        void Start()
        {
            gameController = FindObjectOfType<GameController>();
            btnSave = GameObject.Find("/Canvas/ButtonSave").GetComponent<Button>();
            btnSave.onClick.AddListener(Save);
            btnSave.interactable = false;

            session = FindObjectOfType<ARSession>();
            mapWorker = FindObjectOfType<SparseSpatialMapWorkerFrameFilter>();
            map = FindObjectOfType<SparseSpatialMapController>();

            //追踪状态设置
            session.WorldRootController.TrackingStatusChanged += OnTrackingStatusChanged;
            if (session.WorldRootController.TrackingStatus == MotionTrackingStatus.Tracking)
            {
                btnSave.interactable = true;
            }
            else
            {
                btnSave.interactable = false;
            }
        }

        /// <summary>
        /// 保存地图
        /// </summary>
        private void Save()
        {
            btnSave.interactable = false;
            mapWorker.BuilderMapController.MapHost += (mapInfo, isSuccess, error) =>
            {
                if (isSuccess)
                {
                    PlayerPrefs.SetString("MapID", mapInfo.ID);
                    PlayerPrefs.SetString("MapName", mapInfo.Name);
                    gameController.SendMessage("ShowMessage", "地图保存成功。");
                }
                else
                {
                    gameController.SendMessage("ShowMessage", "地图保存出错：" + error);
                    btnSave.interactable = true;
                }
            };
            try
            {
                mapWorker.BuilderMapController.Host(gameController.inputName, null);
                gameController.SendMessage("ShowMessage", "开始保存地图，请稍等。");
            }
            catch (Exception ex)
            {
                gameController.SendMessage("ShowMessage", "保存出错：" + ex.Message);
                btnSave.interactable = true;
            }
        }
        /// <summary>
        /// 摄像机状态变化
        /// </summary>
        /// <param name="status">状态</param>
        private void OnTrackingStatusChanged(MotionTrackingStatus status)
        {
            if (status == MotionTrackingStatus.Tracking)
            {
                btnSave.interactable = true;
                gameController.SendMessage("ShowMessage", "进入追踪状态。");
            }
            else
            {
                btnSave.interactable = false;
                gameController.SendMessage("ShowMessage", "追踪状态异常。");
            }
        }

    }
}

