using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

namespace Kuromu
{
    /// <summary>
    /// 菜单场景控制器
    /// </summary>
    public class MenuController : MonoBehaviour
    {
        /// <summary>
        /// 地图名称输入
        /// </summary>
        private InputField inputField;
        /// <summary>
        /// 建立地图按钮
        /// </summary>
        private GameObject btnBuildMap;
        /// <summary>
        /// 删除地图按钮
        /// </summary>
        private GameObject btnDelete;
        /// <summary>
        /// 游戏控制
        /// </summary>
        private GameController gameController;


        void Start()
        {
            Transform canvas = GameObject.Find("/Canvas").transform;
            inputField = canvas.Find("InputField").GetComponent<InputField>();
            btnBuildMap = canvas.Find("ButtonBuildMap").gameObject;
            btnDelete = canvas.Find("ButtonDelete").gameObject;
            gameController = FindObjectOfType<GameController>();

            SetBuildUI();
        }
        /// <summary>
        /// 进入建立地图
        /// </summary>
        public void BuildMap()
        {
            if (!string.IsNullOrEmpty(inputField.text))
            {
                gameController.inputName = inputField.text;
                SceneManager.LoadScene("BuildMap");
            }
        }
        /// <summary>
        /// 删除
        /// </summary>
        public void DeleteMap()
        {
            PlayerPrefs.DeleteKey("MapID");
            PlayerPrefs.DeleteKey("MapName");
            SetBuildUI();
        }
        /// <summary>
        /// 设置建立地图相关UI
        /// </summary>
        private void SetBuildUI()
        {
            inputField.text = PlayerPrefs.GetString("MapName");
            bool status = string.IsNullOrEmpty(inputField.text);

            inputField.interactable = status;
            btnBuildMap.SetActive(status);
            btnDelete.SetActive(!status);
        }
        /// <summary>
        /// 退出应用
        /// </summary>
        public void Exit()
        {
            Application.Quit();
        }
    }
}

