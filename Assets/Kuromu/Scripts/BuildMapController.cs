using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Kuromu
{
    public class BuildMapController : MonoBehaviour
    {
        private GameController gameController;
        /// <summary>
        /// 保存按钮
        /// </summary>
        private Button btnSave;

        void Start()
        {
            gameController = FindObjectOfType<GameController>();
            btnSave = GameObject.Find("/Canvas/ButtonSave").GetComponent<Button>();
            btnSave.onClick.AddListener(Save);
        }
        /// <summary>
        /// 保存地图
        /// </summary>
        private void Save()
        {
            PlayerPrefs.SetString("MapID", "TestID");
            PlayerPrefs.SetString("MapName", gameController.inputName);
            btnSave.interactable = false;
            gameController.SendMessage("ShowMessage", "地图保存成功。");
        }
    }
}

