using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Kuromu
{
    //路径场景控制器
    public class RoadsController : MonoBehaviour
    {
        //游戏控制
        private GameController gameController;
        /// <summary>
        /// 出发点下拉列表
        /// </summary>
        private Dropdown dpdStart;
        /// <summary>
        /// 到达点下拉列表
        /// </summary>
        private Dropdown dpdArrival;
        /// <summary>
        /// 按钮
        /// </summary>
        public SelectButton prefab;
        /// <summary>
        /// 按钮容器
        /// </summary>
        private Transform svContent;
        /// <summary>
        /// 显示信息
        /// </summary>
        private Text info;
        /// <summary>
        /// 关键点列表
        /// </summary>
        private List<KeyPoint> keyPoints;
        /// <summary>
        /// 选中对象
        /// </summary>
        private Transform selected;
        /// <summary>
        /// 删除按钮
        /// </summary>
        private Button btnDelete;

        void Start()
        {
            //填充下拉列表
            gameController = FindObjectOfType<GameController>();
            dpdStart = GameObject.Find("/Canvas/Panel/dpdStart").GetComponent<Dropdown>();
            dpdArrival = GameObject.Find("/Canvas/Panel/dpdArrival").GetComponent<Dropdown>();
            //添加按钮
            svContent = GameObject.Find("/Canvas/Panel/Scroll View/Viewport/Content").transform;
            info = GameObject.Find("/Canvas/Panel/Text").GetComponent<Text>();
            GameObject.Find("/Canvas/Panel/ButtonAdd").GetComponent<Button>().onClick.AddListener(AddRoad);
            keyPoints = new List<KeyPoint>();
            //删除按钮
            btnDelete = GameObject.Find("/Canvas/Panel/ButtonDelete").GetComponent<Button>();
            btnDelete.onClick.AddListener(DeleteRoad);
            btnDelete.interactable = false;
            //保存按钮
            GameObject.Find("/Canvas/Panel/ButtonSave").GetComponent<Button>().onClick.AddListener(SaveRoads);

            BindDropdown();
            LoadRoad();
        }
        /// <summary>
        /// 添加路径
        /// </summary>
        private void LoadRoad()
        {
            var list = gameController.LoadRoads();
            foreach (var item in list)
            {
                var btn = Instantiate(prefab, svContent);
                btn.road = JsonUtility.FromJson<Road>(item);
                btn.GetComponentInChildren<Text>().text = btn.road.startName + "<===>" + btn.road.arrivalName;
            }
        }
        /// <summary>
        /// 保存路径
        /// </summary>
        private void SaveRoads()
        {
            string[] jsons = new string[svContent.childCount];
            for (int i = 0; i < svContent.childCount; i++)
            {
                jsons[i] = JsonUtility.ToJson(svContent.GetChild(i).GetComponent<SelectButton>().road);
            }
            gameController.SaveRoads(jsons);
            info.text = "保存成功。";
        }
        /// <summary>
        /// 删除路径
        /// </summary>
        private void DeleteRoad()
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
        }
        /// <summary>
        /// 添加路径
        /// </summary>
        private void AddRoad()
        {
            var btn = Instantiate(prefab, svContent);

            btn.road.startName = dpdStart.captionText.text;
            btn.road.arrivalName = dpdArrival.captionText.text;
            btn.road.startPosition = GetPositionByName(btn.road.startName);
            btn.road.arrivalPosition = GetPositionByName(btn.road.arrivalName);

            btn.GetComponentInChildren<Text>().text = btn.road.startName + "<===>" + btn.road.arrivalName;

            info.text = "添加成功。";
        }
        /// <summary>
        /// 根据关键点名称获取坐标
        /// </summary>
        /// <param name="pName">名称</param>
        /// <returns>坐标</returns>
        private Vector3 GetPositionByName(string pName)
        {
            foreach (var kp in keyPoints)
            {
                if (kp.name == pName)
                {
                    return kp.position;
                }
            }
            return Vector3.zero;
        }
        /// <summary>
        /// 绑定下拉列表
        /// </summary>
        private void BindDropdown()
        {
            var list = gameController.LoadKeyPoins();

            foreach (var item in list)
            {
                KeyPoint point = JsonUtility.FromJson<KeyPoint>(item);
                keyPoints.Add(point);
                dpdStart.options.Add(new Dropdown.OptionData(point.name));
                dpdArrival.options.Add(new Dropdown.OptionData(point.name));
                dpdStart.captionText.text = dpdStart.options[0].text;
                dpdArrival.captionText.text = dpdArrival.options[0].text;
            }
        }
    }
}

