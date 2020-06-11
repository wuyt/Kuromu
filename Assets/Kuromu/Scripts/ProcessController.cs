using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace Kuromu
{
    [RequireComponent(typeof(NavInfoController))]
    public class ProcessController : MonoBehaviour
    {

        private NavInfoController infoController;

        private GameController game;

        private ProcessStatus status;
        /// <summary>
        /// 误差距离
        /// </summary>
        [Tooltip("误差距离")]
        public float errorDistance;

        private bool showAllDistance;
        /// <summary>
        /// 最大远离导航线距离
        /// </summary>
        [Tooltip("最大远离导航线距离")]
        public float maxLeaveDistance;
        /// <summary>
        /// 误差角度
        /// </summary>
        [Tooltip("误差角度")]
        public float errorAngle;
        /// <summary>
        /// 最大转向角度
        /// </summary>
        [Tooltip("最大转向角度")]
        public float maxChangeAngle;
        /// <summary>
        /// 开始转向时候的方向
        /// </summary>
        private bool startDot;

        void Start()
        {
            game=FindObjectOfType<GameController>();
            infoController = GetComponent<NavInfoController>();

            status = ProcessStatus.waiting;
            showAllDistance = false;
        }

        public void StartProcess()
        {
            status = ProcessStatus.keepGoing;
            SendVoice("开始前进");
            showAllDistance = true;
        }

        public void CheckStatus()
        {
            // Debug.Log("check");
            if (status == ProcessStatus.end)
            {
                return;
            }

            //提示到终点总路程
            if (showAllDistance)
            {
                SendVoice("距离目标", infoController.CALCPathLength(), "米");
                showAllDistance = false;
            }



            if (infoController.CALCPathLength() < game.endDistance)
            {
                EndProcess();
                return;
            }

            switch (status)
            {
                case ProcessStatus.keepGoing:
                    if (infoController.PlayerPositionToNavLine() > maxLeaveDistance)
                    {
                        ToBackNavLineAngle();
                        break;
                    }
                    if (infoController.YellowRedAngle() > maxChangeAngle)
                    {
                        ToChangeDirection();
                        break;
                    }
                    break;
                case ProcessStatus.backNavLineAngle:
                    if (infoController.YellowBlackAngle() < errorAngle)
                    {
                        ToBackNavLienDistance();
                    }
                    break;
                case ProcessStatus.backNavLineDistance:
                    if (infoController.PlayerPositionToNavLine() < errorDistance || infoController.YellowRedAngle() > 90f)
                    {
                        ToChangeDirection();
                    }
                    break;
                case ProcessStatus.changeDirection:
                    if (infoController.YellowRedAngle() < errorAngle || startDot != infoController.YellowRedDot())
                    {
                        ToKeepGoing();
                    }
                    break;
            }







            // OnKeepGoing();
        }

        private void ToKeepGoing()
        {
            status = ProcessStatus.keepGoing;
            SendVoice("开始前进");
        }

        private void EndProcess()
        {
            status = ProcessStatus.end;
            //SendVoice("到达终点");
            SendMessage("VoiceEnd");
        }

        private void ToBackNavLineAngle()
        {
            Debug.Log("start BNL angel");
            status = ProcessStatus.backNavLineAngle;


            string direction = "";
            if (infoController.YellowBlackDot())
            {
                direction = "向右转";
            }
            else
            {
                direction = "向左转";
            }
            float angle = infoController.YellowBlackAngle();
            
            SendVoice(direction, angle, "度");

        }

        private void ToBackNavLienDistance()
        {
            Debug.Log("start BNL distance");
            status = ProcessStatus.backNavLineDistance;
            SendVoice("开始前进");
        }

        private void ToChangeDirection()
        {
            Debug.Log("start Change Direction");
            status = ProcessStatus.changeDirection;
            startDot = infoController.YellowRedDot();

            string direction = "";
            if (startDot)
            {
                direction = "向右转";
            }
            else
            {
                direction = "向左转";
            }
            float angle = infoController.YellowRedAngle();

            SendVoice(direction, angle, "度");


        }

        /// <summary>
        /// 发送语音
        /// </summary>
        /// <param name="voice"></param>
        private void SendVoice(string voice)
        {
            string[] strArray = new string[] { voice };
            SendMessage("PlayVoice", strArray);
        }

        private void SendVoice(string front, float number, string unit)
        {
            string[] strArray = new string[] { front, number.ToString("0.0"), unit };
            SendMessage("PlayVoice", strArray);
        }

    }

    #region 状态枚举

    /// <summary>
    /// 处理状态
    /// </summary>
    public enum ProcessStatus
    {
        /// <summary>
        /// 等待
        /// </summary>
        waiting,
        /// <summary>
        /// 返回导航线转向
        /// </summary>
        backNavLineAngle,
        /// <summary>
        /// 返回导航线前进
        /// </summary>
        backNavLineDistance,
        /// <summary>
        /// 改变方向
        /// </summary>
        changeDirection,
        /// <summary>
        /// 继续前进
        /// </summary>
        keepGoing,
        /// <summary>
        /// 到达终点
        /// </summary>
        end
    }

    #endregion
}

