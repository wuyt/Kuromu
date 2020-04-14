using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using UnityEngine.UI;
using UnityEngine.AI;

namespace Kuromu.Pre
{
    public class NavInfoController : MonoBehaviour
    {
        /// <summary>
        /// 玩家
        /// </summary>
        public Transform player;
        /// <summary>
        /// 状态信息显示
        /// </summary>
        private Text textStatus;

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
        /// <summary>
        /// 玩家到导航线的投影线
        /// </summary>
        private LineRenderer lrPlayerToLine;

        private NavMeshPath path;

        void Start()
        {
            textStatus = GameObject.Find("/Canvas/TextStatus").GetComponent<Text>();

            textPoints = GameObject.Find("/Canvas/TextPoints").GetComponent<Text>();

            lrPlayer = GameObject.Find("/Lines/PlayerLine").GetComponent<LineRenderer>();
            playerAhead = player.Find("ahead");
            playerLeft = player.Find("left");

            lrPlayerToNext = GameObject.Find("/Lines/PlayerToNext").GetComponent<LineRenderer>();

            lrNavToNext = GameObject.Find("/Lines/NavToNext").GetComponent<LineRenderer>();

            lrPlayerToLine = GameObject.Find("/Lines/PlayerToLine").GetComponent<LineRenderer>();

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
        private void ShowStatus(NavMeshPath navPath)
        {
            path = navPath;
            textStatus.text = string.Format(
                @"{0}；
                到终点距离：{1}；
                导航起始到下一个点距离：{2}；
                玩家位置到下一个点距离：{3}；
                玩家位置到导航起始距离：{4}；
                黄红夹角：{5}
                黄红Dot（<0在左，>0在右）：{6}
                黄绿夹角：{7}
                玩家在绿线左：{8}
                黄黑夹角：{9}
                黄黑Dot（<0在左，>0在右）：{10}",
                "",
                CALCPathLength(),
                NavPointToNextLength(),
                PlayerPositionToNextLength(),
                PlayerPositionToNavLine(),
                YellowRedAngle(),
                YellowRedDot(),
                YellowGreenAngle(),
                PlayerGreenLeft(),
                YellowBlackAngle(),
                YellowBlackDot());

            ShowPoints();

            ShowPlayerLine();
            ShowPlayerToNextLine();
            ShowNavToNextLine();
            ShowPlayerToLine();

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

        private bool PlayerRedLeft()
        {
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
            return Vector2.Dot(yellow, red) < 0;
        }

        /// <summary>
        /// 黄黑线夹角
        /// </summary>
        /// <returns></returns>
        private float YellowBlackAngle()
        {
            Vector2 black = new Vector2(path.corners[0].x, path.corners[0].z) - new Vector2(player.position.x, player.position.z);
            Vector2 yellow = new Vector2(playerAhead.position.x, playerAhead.position.z) - new Vector2(player.position.x, player.position.z);
            return Vector2.Angle(yellow, black);
        }
        /// <summary>
        /// 黄黑线左右
        /// </summary>
        /// <returns></returns>
        private bool YellowBlackDot()
        {
            Vector2 black = new Vector2(path.corners[0].x, path.corners[0].z) - new Vector2(player.position.x, player.position.z);
            Vector2 yellow = new Vector2(playerLeft.position.x, playerLeft.position.z) - new Vector2(player.position.x, player.position.z);
            return Vector2.Dot(yellow, black) < 0;
        }


        /// <summary>
        /// 显示导航起始到下一个点的投影线（绿线）
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
        /// 显示玩家到下一个点投影线（红线）
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
        /// 显示玩家面向方向投影线（黄线）
        /// </summary>
        private void ShowPlayerLine()
        {
            lrPlayer.positionCount = 2;

            lrPlayer.SetPosition(0, new Vector3(player.position.x, player.position.y + projection, player.position.z));
            lrPlayer.SetPosition(1, new Vector3(playerAhead.position.x, player.position.y + projection, playerAhead.position.z));
        }
        /// <summary>
        /// 显示玩家到导航线起点的投影（黑线）
        /// </summary>
        private void ShowPlayerToLine()
        {
            if (path.corners.Length > 1)
            {
                lrPlayerToLine.positionCount = 2;

                lrPlayerToLine.SetPosition(0, new Vector3(player.position.x, player.position.y + projection, player.position.z));
                lrPlayerToLine.SetPosition(1, new Vector3(path.corners[0].x, player.position.y + projection, path.corners[0].z));
            }
        }

        /// <summary>
        /// 玩家位置到导航起始点的距离
        /// </summary>
        /// <returns></returns>
        private float PlayerPositionToNavLine()
        {
            if (path.corners.Length > 0)
            {
                return (
                    new Vector3(player.position.x, player.position.y + projection, player.position.z) -
                    new Vector3(path.corners[0].x, player.position.y + projection, path.corners[0].z)
                    ).magnitude;
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
                return (
                    new Vector3(player.position.x, player.position.y + projection, player.position.z) -
                    new Vector3(path.corners[1].x, player.position.y + projection, path.corners[1].z)
                    ).magnitude;
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

    }
}

