using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Kuromu.Pre
{
    public class BuildMapController : MonoBehaviour
    {
        /// <summary>
        /// 游戏控制器
        /// </summary>
        private GameController gameController;
        /// <summary>
        /// 保存按钮
        /// </summary>
        private Button btnSave;


        void Start()
        {
            //保存按钮初始
            gameController = FindObjectOfType<GameController>();
            btnSave = GameObject.Find("/Canvas/ButtonSave").GetComponent<Button>();
            btnSave.onClick.AddListener(Save);
            //btnSave.interactable = false;
        }

        /// <summary>
        /// 保存地图
        /// </summary>
        private void Save()
        {
            btnSave.interactable = false;
            PlayerPrefs.SetString("MapName", gameController.inputName);
            PlayerPrefs.SetString("MapID", "mapid");
        }
    }
}

