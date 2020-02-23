using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Kuromu.Pre
{
    public class KeyPointsController : MonoBehaviour
    {
        /// <summary>
        /// 关键点画布
        /// </summary>
        private GameObject panel;
        /// <summary>
        /// 信息文本框
        /// </summary>
        private Text info;
        /// <summary>
        /// 选中的对象
        /// </summary>
        private Transform selected;
        /// <summary>
        /// 滚动视图容器
        /// </summary>
        private Transform svContent;
        /// <summary>
        /// 名称输入
        /// </summary>
        private InputField inputField;
        /// <summary>
        /// 类型选择
        /// </summary>
        private Dropdown dropdown;
        /// <summary>
        /// 关键点按钮预制件
        /// </summary>
        public BtnKeyPoint prefab;

        private Button btnAdd;

        private Button btnDelete;

        private GameController gameController;

        void Start()
        {
            //界面控制
            panel = GameObject.Find("/Canvas/Panel");
            panel.transform.Find("ButtonClose").GetComponent<Button>().onClick.AddListener(() =>
            {
                HiddenPanel();
            });
            info = panel.transform.Find("Text").GetComponent<Text>();

            svContent = panel.transform.Find("Scroll View/Viewport/Content");
            inputField = panel.transform.Find("InputField").GetComponent<InputField>();
            dropdown = panel.transform.Find("Dropdown").GetComponent<Dropdown>();
            btnAdd = panel.transform.Find("ButtonAdd").GetComponent<Button>();
            btnAdd.onClick.AddListener(AddKeyPoint);
            btnAdd.interactable = false;

            btnDelete = panel.transform.Find("ButtonDelete").GetComponent<Button>();
            btnDelete.onClick.AddListener(DeleteKeyPoint);
            btnDelete.interactable = false;

            panel.transform.Find("ButtonSave").GetComponent<Button>().onClick.AddListener(SaveKeyPoints);
            gameController = FindObjectOfType<GameController>();

            LoadKeyPoints();

            HiddenPanel();
        }
        private void LoadKeyPoints()
        {
            var list = gameController.LoadKeyPoins();
            foreach (var item in list)
            {
                var btn = Instantiate(prefab, svContent);
                btn.keyPoint = JsonUtility.FromJson<KeyPoint>(item);
                btn.GetComponentInChildren<Text>().text = btn.keyPoint.name;
            }
        }

        /// <summary>
        /// 保存关键点
        /// </summary>
        private void SaveKeyPoints()
        {
            string[] jsons = new string[svContent.childCount];
            for (int i = 0; i < svContent.childCount; i++)
            {
                jsons[i] = JsonUtility.ToJson(svContent.GetChild(i).GetComponent<BtnKeyPoint>().keyPoint);
            }
            gameController.SaveKeyPoints(jsons);
            info.text = "保存完成。";
        }
        /// <summary>
        /// 删除关键点
        /// </summary>
        private void DeleteKeyPoint()
        {
            Destroy(selected.gameObject);
            info.text = "删除成功。";
            btnDelete.interactable = false;
        }
        /// <summary>
        /// 关键点按钮点击
        /// </summary>
        /// <param name="btnTF"></param>
        public void BtnKeyPointClicked(Transform btnTF)
        {
            selected = btnTF;
            info.text = btnTF.GetComponentInChildren<Text>().text;
            btnDelete.interactable = true;
            btnAdd.interactable = false;
        }

        /// <summary>
        /// 添加关键点
        /// </summary>
        private void AddKeyPoint()
        {
            if (!string.IsNullOrEmpty(inputField.text) && selected != null)
            {
                BtnKeyPoint btnKP = Instantiate(prefab, svContent);

                btnKP.keyPoint.name = inputField.text;
                btnKP.keyPoint.position = selected.localPosition;
                btnKP.keyPoint.pointType = dropdown.value;

                btnKP.GetComponentInChildren<Text>().text = inputField.text;

                inputField.text = "";
                selected = null;
                info.text = "添加成功。";
                btnAdd.interactable = false;
            }
        }

        /// <summary>
        /// 隐藏画布
        /// </summary>
        private void HiddenPanel()
        {
            panel.SetActive(false);
            info.text = "";
        }
        /// <summary>
        /// 显示画布
        /// </summary>
        private void ShowPanel()
        {
            panel.SetActive(true);
            info.text = "Position:" + selected.localPosition;
        }

        void Update()
        {
            if (Input.GetMouseButtonUp(0))
            {
                RaycastHit hit;
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                if (Physics.Raycast(ray, out hit))
                {
                    selected = hit.transform;
                    btnAdd.interactable = true;
                    ShowPanel();
                }
            }
        }
    }
}

