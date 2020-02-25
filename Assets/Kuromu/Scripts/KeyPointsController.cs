using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using easyar;

namespace Kuromu
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
        public SelectButton prefab;

        private Button btnAdd;

        private Button btnDelete;

        private GameController gameController;

        private ARSession session;
        private SparseSpatialMapWorkerFrameFilter mapWorker;
        private SparseSpatialMapController map;

        private bool localized = false;

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

            session = FindObjectOfType<ARSession>();
            mapWorker = FindObjectOfType<SparseSpatialMapWorkerFrameFilter>();
            map = FindObjectOfType<SparseSpatialMapController>();

            LoadKeyPoints();
            HiddenPanel();

            LoadMap();
        }
        /// <summary>
        /// 加载地图
        /// </summary>
        private void LoadMap()
        {
            Debug.Log("start set map");
            map.MapManagerSource.ID = PlayerPrefs.GetString("MapID");
            map.MapManagerSource.Name = PlayerPrefs.GetString("MapName");
            Debug.Log("set end.");

            map.MapLoad += (map, status, error) =>
            {
                if (status)
                {
                    localized = true;
                    gameController.SendMessage("ShowMessage", "地图加载成功。");
                }
                else
                {
                    gameController.SendMessage("ShowMessage", "地图加载失败。" + error);
                }
            };

            map.MapLocalized += () =>
            {
                gameController.SendMessage("ShowMessage", "进入稀疏空间定位。");
            };
            map.MapStopLocalize += () =>
            {
                gameController.SendMessage("ShowMessage", "停止稀疏空间定位");
            };

            gameController.SendMessage("ShowMessage", "开始加载地图。");
            mapWorker.Localizer.startLocalization();
        }

        /// <summary>
        /// 加载关键点
        /// </summary>
        private void LoadKeyPoints()
        {
            var list = gameController.LoadKeyPoins();
            foreach (var item in list)
            {
                SelectButton btn = Instantiate(prefab, svContent);
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
                jsons[i] = JsonUtility.ToJson(svContent.GetChild(i).GetComponent<SelectButton>().keyPoint);
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
        /// 按钮点击
        /// </summary>
        /// <param name="btnTF"></param>
        public void SelectButtonClicked(Transform btnTF)
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
                SelectButton btn = Instantiate(prefab, svContent);

                btn.keyPoint.name = inputField.text;
                btn.keyPoint.position = selected.localPosition;
                btn.keyPoint.pointType = dropdown.value;

                btn.GetComponentInChildren<Text>().text = inputField.text;

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
            if (Input.GetMouseButtonUp(0) && localized)
            {
                RaycastHit hit;
                Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
                if (Physics.Raycast(ray, out hit))
                {
                    selected = hit.transform;
                    btnAdd.interactable = true;
                    HitObject();
                    ShowPanel();
                }
            }
        }
        /// <summary>
        /// 点中游戏对象
        /// </summary>
        private void HitObject()
        {
            var tf = new GameObject().transform;
            tf.position = selected.position;
            tf.parent = map.transform;
            selected = tf;
        }
    }
}

