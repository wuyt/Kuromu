using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.AI;
using System;
using System.Collections.Generic;

namespace Kuromu.Pre
{
    public class NavigationController : MonoBehaviour
    {
        private GameController gameController;
        /// <summary>
        /// 导航画布
        /// </summary>
        private GameObject panel;
        /// <summary>
        /// 导航按钮
        /// </summary>
        private Button btnNav;
        /// <summary>
        /// 导航按钮
        /// </summary>
        public SelectButton prefabButton;
        /// <summary>
        /// 导航按钮容器
        /// </summary>
        private Transform svContent;
        /// <summary>
        /// 导航根节点
        /// </summary>
        public Transform navRoot;
        /// <summary>
        /// 目的地预制件
        /// </summary>
        public Transform prefabArrival;
        /// <summary>
        /// 路径预制件
        /// </summary>
        public Transform prefabRoad;
        /// <summary>
        /// 导航线
        /// </summary>
        private LineRenderer lineRenderer;
        /// <summary>
        /// 导航代理
        /// </summary>
        private NavMeshAgent agent;

        private NavMeshPath path;

        private NavMeshSurface surface;
        /// <summary>
        /// 导航目标
        /// </summary>
        private Transform arrival;
        /// <summary>
        /// 玩家
        /// </summary>
        public Transform player;
        /// <summary>
        /// 刷新频率
        /// </summary>
        public float refresh;
        /// <summary>
        /// 参照数组
        /// </summary>
        private Vector3[] aryArrivals;
        /// <summary>
        /// 最终导航数组
        /// </summary>
        private Vector3[] arrangePoints;

        void Start()
        {
            gameController = FindObjectOfType<GameController>();
            panel = GameObject.Find("/Canvas/Panel");
            btnNav = GameObject.Find("/Canvas/ButtonNav").GetComponent<Button>();
            btnNav.onClick.AddListener(ShowNavUI);
            //btnNav.interactable = false;
            panel.transform.Find("ButtonClose").GetComponent<Button>().onClick.AddListener(CloseNavUI);

            svContent = panel.transform.Find("Scroll View/Viewport/Content").transform;



            LoadArrivals();

            LoadRoads();

            SetLine();

            BakePath();

            CloseNavUI();

        }

        /// <summary>
        /// 按钮点击
        /// </summary>
        /// <param name="btnTF"></param>
        public void SelectButtonClicked(Transform btnTF)
        {
            CancelInvoke("DisplayPath");
            arrival = btnTF.GetComponent<SelectButton>().arrival;

            Transform root = navRoot.Find("Arrivals");
            for (int i = 0; i < root.childCount; i++)
            {
                root.GetChild(i).gameObject.SetActive(false);
            }
            arrival.gameObject.SetActive(true);

            if (GetComponent<ProcessController>().enabled)
            {
                gameObject.SendMessage("StartProcess");
            }

            InvokeRepeating("DisplayPath", 0, refresh);

            CloseNavUI();
        }


        /// <summary>
        /// /// 显示路径
        /// </summary>
        private void DisplayPath()
        {
            agent.transform.position = player.position;
            agent.enabled = true;
            agent.CalculatePath(arrival.position, path);

            ChangePoints();

            lineRenderer.positionCount = arrangePoints.Length;
            lineRenderer.SetPositions(arrangePoints);

            //lineRenderer.positionCount = path.corners.Length;
            // lineRenderer.SetPositions(path.corners);
            agent.enabled = false;



            if (GetComponent<NavInfoController>().enabled)
            {
                gameObject.SendMessage("ShowStatus", path);
            }
            //ShowStatus();
        }
        /// <summary>
        /// 修改导航路径
        /// </summary>
        private void ChangePoints()
        {
            List<Vector3> list = new List<Vector3>();
            int mark = 0;
            for (int i = 0; i < path.corners.Length; i++)
            {
                if (i == mark)
                {
                    float d = 1000f;
                    Vector3 p = Vector3.zero;
                    foreach (Vector3 v in aryArrivals)
                    {
                        if ((path.corners[i] - v).magnitude < d)
                        {
                            d = (path.corners[i] - v).magnitude;
                            p = v;
                        }
                    }
                    list.Add(p);
                }

                if (i + 1 < path.corners.Length)
                {
                    if ((path.corners[i] - path.corners[i + 1]).magnitude > 0.1f)
                    {
                        mark = i + 1;
                    }
                }
            }

            arrangePoints = list.ToArray();
        }

        /// <summary>
        /// 烘培路径
        /// </summary>
        private void BakePath()
        {

            surface = FindObjectOfType<NavMeshSurface>();
            Debug.Log("bake start");
            agent = FindObjectOfType<NavMeshAgent>();
            Debug.Log(agent);
            agent.enabled = false;
            surface.BuildNavMesh();
            path = new NavMeshPath();
            Debug.Log("bake end");
        }

        /// <summary>
        /// 设置导航线样式
        /// </summary>
        private void SetLine()
        {
            lineRenderer = navRoot.Find("Line").gameObject.AddComponent<LineRenderer>();
            Debug.Log(lineRenderer);
            lineRenderer.material = new Material(Shader.Find("Sprites/Default"));
            lineRenderer.positionCount = 0;
            lineRenderer.widthMultiplier = 0.3f;
            Gradient gradient = new Gradient();
            gradient.SetKeys(
                new GradientColorKey[] {
                new GradientColorKey(Color.blue, 0.0f),
                new GradientColorKey(Color.blue, 1.0f) },
                new GradientAlphaKey[] {
                new GradientAlphaKey(1f, 0.0f),
                new GradientAlphaKey(1f, 1.0f) });
            lineRenderer.colorGradient = gradient;
        }


        /// <summary>
        /// 加载路径
        /// </summary>
        private void LoadRoads()
        {
            var list = gameController.LoadRoads();

            var temp = new GameObject().transform;
            temp.parent = navRoot.Find("Roads");

            foreach (var item in list)
            {
                var road = JsonUtility.FromJson<Road>(item);
                var tfRoad = Instantiate(prefabRoad, navRoot.Find("Roads"));

                tfRoad.localPosition = (road.startPosition + road.arrivalPosition) / 2;
                temp.localPosition = road.arrivalPosition;
                tfRoad.LookAt(temp);
                tfRoad.localScale = new Vector3(0.02f, 1f, (road.arrivalPosition - road.startPosition).magnitude * 0.1f + 0.2f);
            }
            Destroy(temp.gameObject);
        }
        /// <summary>
        /// 加载目标
        /// </summary>
        private void LoadArrivals()
        {
            var list = gameController.LoadKeyPoins();
            foreach (var item in list)
            {
                KeyPoint point = JsonUtility.FromJson<KeyPoint>(item);

                var arrivalTemp = Instantiate(prefabArrival, navRoot.Find("Arrivals"));
                arrivalTemp.localPosition = point.position;
                if (point.pointType == 0)
                {
                    var btn = Instantiate(prefabButton, svContent);
                    btn.keyPoint = point;
                    btn.GetComponentInChildren<Text>().text = point.name;
                    btn.arrival = arrivalTemp;
                }
            }

            //整理导航点用
            aryArrivals = new Vector3[navRoot.Find("Arrivals").childCount];
            for (int i = 0; i < navRoot.Find("Arrivals").childCount; i++)
            {
                aryArrivals[i] = navRoot.Find("Arrivals").GetChild(i).transform.position;
            }
        }
        /// <summary>
        /// 显示导航菜单
        /// </summary>
        private void ShowNavUI()
        {
            panel.SetActive(true);
        }
        /// <summary>
        /// 关闭导航菜单
        /// </summary>
        private void CloseNavUI()
        {
            panel.SetActive(false);
        }


    }
}

