using UnityEngine;
using UnityEngine.UI;
using UnityEngine.AI;
using easyar;
using System;

namespace Kuromu
{
    /// <summary>
    /// 导航场景控制器
    /// </summary>
    public class NavigationController : MonoBehaviour
    {

        /// <summary>
        /// 游戏控制
        /// </summary>
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
        /// <summary>
        /// 导航路径
        /// </summary>
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

        private ARSession session;
        private SparseSpatialMapWorkerFrameFilter mapWorker;
        private SparseSpatialMapController map;

        /// <summary>
        /// 刷新频率
        /// </summary>
        public float refresh;
        void Start()
        {

            gameController = FindObjectOfType<GameController>();
            panel = GameObject.Find("/Canvas/Panel");
            btnNav = GameObject.Find("/Canvas/ButtonNav").GetComponent<Button>();
            btnNav.onClick.AddListener(ShowNavUI);
            btnNav.interactable = false;
            panel.transform.Find("ButtonClose").GetComponent<Button>().onClick.AddListener(CloseNavUI);

            svContent = panel.transform.Find("Scroll View/Viewport/Content").transform;



            session = FindObjectOfType<ARSession>();
            mapWorker = FindObjectOfType<SparseSpatialMapWorkerFrameFilter>();
            map = FindObjectOfType<SparseSpatialMapController>();

            SetLine();
            CloseNavUI();
            LoadMap();
        }

        /// <summary>
        /// 加载地图
        /// </summary>
        private void LoadMap()
        {
            //设置地图
            map.MapManagerSource.ID = PlayerPrefs.GetString("MapID");
            map.MapManagerSource.Name = PlayerPrefs.GetString("MapName");
            //地图加载反馈
            map.MapLoad += (map, status, error) =>
            {
                if (status)
                {
                    gameController.SendMessage("ShowMessage", "地图加载成功。");
                }
                else
                {
                    gameController.SendMessage("ShowMessage", "地图加载失败。" + error);
                }
            };
            //地图定位反馈
            map.MapLocalized += () =>
            {
                gameController.SendMessage("ShowMessage", "进入稀疏空间定位。");
                ClearNav();
                LoadArrivals();
                LoadRoads();
                BakePath();
                btnNav.interactable = true;
                ShowNavUI();
            };
            //停止定位反馈
            map.MapStopLocalize += () =>
            {
                gameController.SendMessage("ShowMessage", "停止稀疏空间定位");
            };
            gameController.SendMessage("ShowMessage", "开始加载地图。");
            mapWorker.Localizer.startLocalization();    //本地化地图
        }
        /// <summary>
        /// 清理导航元素
        /// </summary>
        private void ClearNav()
        {
            //删除按钮
            foreach (Transform tf in svContent)
            {
                Destroy(tf.gameObject);
            }
            //删除目的地
            foreach (Transform tf in navRoot.Find("Arrivals"))
            {
                Destroy(tf.gameObject);
            }
            //删除路径
            foreach (Transform tf in navRoot.Find("Roads"))
            {
                Destroy(tf.gameObject);
            }
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

            InvokeRepeating("DisplayPath", 0, refresh);
            CloseNavUI();
        }
        /// <summary>
        /// 显示路径
        /// </summary>
        private void DisplayPath()
        {
            agent.transform.position = player.position;
            agent.enabled = true;
            agent.CalculatePath(arrival.position, path);
            lineRenderer.positionCount = path.corners.Length;
            lineRenderer.SetPositions(path.corners);
            agent.enabled = false;

            gameObject.SendMessage("ShowStatus",path);
           // ShowStatus();
        }


        /// <summary>
        /// 烘培路径
        /// </summary>
        private void BakePath()
        {
            surface = FindObjectOfType<NavMeshSurface>();
            agent = FindObjectOfType<NavMeshAgent>();
            agent.transform.position = player.position;
            agent.enabled = false;
            surface.BuildNavMesh();
            path = new NavMeshPath();
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
            lineRenderer.widthMultiplier = 0.05f;
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
                if (point.pointType == 0)
                {
                    var btn = Instantiate(prefabButton, svContent);
                    btn.keyPoint = point;
                    btn.GetComponentInChildren<Text>().text = point.name;

                    var arrivalTemp = Instantiate(prefabArrival, navRoot.Find("Arrivals"));
                    arrivalTemp.localPosition = point.position;
                    btn.arrival = arrivalTemp;
                    arrivalTemp.gameObject.SetActive(false);
                }
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

