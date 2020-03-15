using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.AI;
using System;

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
        /// 状态信息显示
        /// </summary>
        private Text textStatus;
        /// <summary>
        /// 刷新频率
        /// </summary>
        public float refresh;
        /// <summary>
        /// 显示导航点用的文本
        /// </summary>
        private Text textPoints;
        /// <summary>
        /// 投影相对高度
        /// </summary>
        public float projection;
        /// <summary>
        /// 玩家面向方向投影线
        /// </summary>
        private LineRenderer lrPlayer;
        /// <summary>
        /// 玩家前面的点，用于绘制面向方向投影线
        /// </summary>
        private Transform playerAhead;
        /// <summary>
        /// 玩家左边的点，用于判断左右
        /// </summary>
        private Transform playerLeft;
        /// <summary>
        /// 玩家到下一个点投影线
        /// </summary>
        private LineRenderer lrPlayerToNext;
        /// <summary>
        /// 导航起始点到下一个点投影线
        /// </summary>
        private LineRenderer lrNavToNext;
        void Start()
        {
            gameController = FindObjectOfType<GameController>();
            panel = GameObject.Find("/Canvas/Panel");
            btnNav = GameObject.Find("/Canvas/ButtonNav").GetComponent<Button>();
            btnNav.onClick.AddListener(ShowNavUI);
            //btnNav.interactable = false;
            panel.transform.Find("ButtonClose").GetComponent<Button>().onClick.AddListener(CloseNavUI);

            svContent = panel.transform.Find("Scroll View/Viewport/Content").transform;

            textStatus = GameObject.Find("/Canvas/TextStatus").GetComponent<Text>();

            textPoints = GameObject.Find("/Canvas/TextPoints").GetComponent<Text>();

            lrPlayer = GameObject.Find("/Lines/PlayerLine").GetComponent<LineRenderer>();
            playerAhead = player.Find("ahead");
            playerLeft = player.Find("left");

            lrPlayerToNext = GameObject.Find("/Lines/PlayerToNext").GetComponent<LineRenderer>();

            lrNavToNext = GameObject.Find("/Lines/NavToNext").GetComponent<LineRenderer>();

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

            InvokeRepeating("DisplayPath", 0, refresh);

            CloseNavUI();
        }
        /// <summary>
        /// 显示导航点坐标
        /// </summary>
        private void ShowPoints()
        {
            textPoints.text = "";
            for (int i = 0; i < path.corners.Length; i++)
            {
                textPoints.text = textPoints.text + i + "---" + path.corners[i] + Environment.NewLine;
            }
        }
        /// <summary>
        /// 显示状态信息
        /// </summary>
        private void ShowStatus()
        {
            textStatus.text = string.Format(
                @"
                刷新率：{0}；
                到终点距离：{1}；
                导航起始到下一个点距离：{2}；
                玩家位置到下一个点距离：{3}；
                玩家位置到导航起始距离：{4}；
                黄红夹角：{5}
                黄红Dot（<0在左，>0在右）：{6}
                黄绿夹角：{7}
                玩家在绿线左：{8}",
                refresh,
                CALCPathLength(),
                NavPointToNextLength(),
                PlayerPositionToNextLength(),
                PlayerPositionToNavLine(),
                YellowRedAngle(),
                YellowRedDot(),
                YellowGreenAngle(),
                PlayerGreenLeft());

            ShowPoints();

            ShowPlayerLine();
            ShowPlayerToNextLine();
            ShowNavToNextLine();
        }

        /// <summary>
        /// 判断目标点是否位于向量左边
        /// </summary>
        /// <param name="start">向量起点</param>
        /// <param name="origin">向量终点</param>
        /// <param name="point">目标点</param>
        /// <returns></returns>
        public bool PointOnLeftSideOfVector(Vector2 start, Vector2 origin, Vector2 point)
        {
            float verticalX = origin.x;
            float verticalY = (-verticalX * start.x) / start.y;
            Vector2 norVertical = (new Vector2(verticalX, verticalY)).normalized;
            float dotValue = Vector2.Dot(norVertical, point);
            return dotValue < 0f;
        }

        /// <summary>
        /// 判断玩家在绿线左边
        /// </summary>
        /// <returns></returns>
        private bool PlayerGreenLeft()
        {
            return PointOnLeftSideOfVector(
                new Vector2(path.corners[0].x, path.corners[0].z),
                new Vector2(path.corners[1].x, path.corners[1].z),
                new Vector2(player.position.x, player.position.z));
        }

        private bool PlayerRedLeft(){
            return PointOnLeftSideOfVector(
                new Vector2(player.position.x, player.position.z),
                new Vector2(path.corners[1].x, path.corners[1].z),
                new Vector2(playerAhead.position.x, playerAhead.position.z));
        }

        /// <summary>
        /// 黄绿线夹角
        /// </summary>
        /// <returns></returns>
        private float YellowGreenAngle()
        {
            Vector2 green = new Vector2(path.corners[1].x, path.corners[1].z) - new Vector2(path.corners[0].x, path.corners[0].z);
            Vector2 yellow = new Vector2(playerAhead.position.x, playerAhead.position.z) - new Vector2(player.position.x, player.position.z);
            return Vector2.Angle(yellow, green);
        }

        /// <summary>
        /// 黄红线夹角
        /// </summary>
        /// <returns></returns>
        private float YellowRedAngle()
        {
            Vector2 red = new Vector2(path.corners[1].x, path.corners[1].z) - new Vector2(player.position.x, player.position.z);
            Vector2 yellow = new Vector2(playerAhead.position.x, playerAhead.position.z) - new Vector2(player.position.x, player.position.z);
            return Vector2.Angle(yellow, red);
        }
        /// <summary>
        /// 黄红线左右
        /// </summary>
        /// <returns></returns>
        private bool YellowRedDot()
        {
            Vector2 red = new Vector2(path.corners[1].x, path.corners[1].z) - new Vector2(player.position.x, player.position.z);
            Vector2 yellow = new Vector2(playerLeft.position.x, playerLeft.position.z) - new Vector2(player.position.x, player.position.z);
            return Vector2.Dot(yellow, red)<0;
        }

        /// <summary>
        /// 显示导航起始到下一个点的投影线
        /// </summary>
        private void ShowNavToNextLine()
        {
            if (path.corners.Length > 1)
            {
                lrNavToNext.positionCount = 2;

                lrNavToNext.SetPosition(0, new Vector3(path.corners[0].x, player.position.y + projection, path.corners[0].z));
                lrNavToNext.SetPosition(1, new Vector3(path.corners[1].x, player.position.y + projection, path.corners[1].z));
            }
        }
        /// <summary>
        /// 显示玩家到下一个点投影线
        /// </summary>
        private void ShowPlayerToNextLine()
        {
            if (path.corners.Length > 1)
            {
                lrPlayerToNext.positionCount = 2;

                lrPlayerToNext.SetPosition(0, new Vector3(player.position.x, player.position.y + projection, player.position.z));
                lrPlayerToNext.SetPosition(1, new Vector3(path.corners[1].x, player.position.y + projection, path.corners[1].z));
            }
        }

        /// <summary>
        /// 显示玩家面向方向投影线
        /// </summary>
        private void ShowPlayerLine()
        {
            lrPlayer.positionCount = 2;

            lrPlayer.SetPosition(0, new Vector3(player.position.x, player.position.y + projection, player.position.z));
            lrPlayer.SetPosition(1, new Vector3(playerAhead.position.x, player.position.y + projection, playerAhead.position.z));
        }

        /// <summary>
        /// 玩家位置到导航起始点的距离
        /// </summary>
        /// <returns></returns>
        private float PlayerPositionToNavLine()
        {
            if (path.corners.Length > 0)
            {
                return (player.position - path.corners[0]).magnitude;
            }
            return 0;
        }
        /// <summary>
        /// 玩家位置到下一个点的距离
        /// </summary>
        /// <returns></returns>
        private float PlayerPositionToNextLength()
        {
            if (path.corners.Length > 1)
            {
                return (player.position - path.corners[1]).magnitude;
            }
            return 0;
        }
        /// <summary>
        /// /// 从导航起始点到下一个点距离
        /// </summary>
        /// <returns></returns>
        private float NavPointToNextLength()
        {
            if (path.corners.Length > 1)
            {
                return (path.corners[0] - path.corners[1]).magnitude;
            }
            return 0;
        }
        /// <summary>
        /// 计算从导航起始点到终点距离
        /// </summary>
        /// <returns>距离</returns>
        private float CALCPathLength()
        {
            float distance = 0;
            for (int i = 1; i < path.corners.Length; i++)
            {
                distance = distance + (path.corners[i] - path.corners[i - 1]).magnitude;
            }
            return distance;
        }

        /// <summary>
        /// /// 显示路径
        /// </summary>
        private void DisplayPath()
        {
            agent.transform.position = player.position;
            agent.enabled = true;
            agent.CalculatePath(arrival.position, path);
            lineRenderer.positionCount = path.corners.Length;
            lineRenderer.SetPositions(path.corners);
            agent.enabled = false;
            ShowStatus();
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
                if (point.pointType == 0)
                {
                    var btn = Instantiate(prefabButton, svContent);
                    btn.keyPoint = point;
                    btn.GetComponentInChildren<Text>().text = point.name;

                    var arrivalTemp = Instantiate(prefabArrival, navRoot.Find("Arrivals"));
                    arrivalTemp.localPosition = point.position;
                    btn.arrival = arrivalTemp;
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

