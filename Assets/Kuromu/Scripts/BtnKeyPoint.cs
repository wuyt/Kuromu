using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace Kuromu
{
    public class BtnKeyPoint : MonoBehaviour
    {
        /// <summary>
        /// 关键点
        /// </summary>
        public KeyPoint keyPoint;

        void Start()
        {
            gameObject.GetComponent<Button>().onClick.AddListener(() =>
            {
                GameObject.Find("SceneMaster").SendMessage("BtnKeyPointClicked",transform);
            });
        }

    }
}

