using UnityEngine;
using UnityEngine.UI;

namespace Kuromu
{
    /// <summary>
    /// 滚动视图中的点击按钮
    /// </summary>
    public class SelectButton : MonoBehaviour
    {
        /// <summary>
        /// 关键点
        /// </summary>
        public KeyPoint keyPoint;
        /// <summary>
        /// 路径
        /// </summary>
        public Road road;
        /// <summary>
        /// 目的地
        /// </summary>
        public Transform arrival;

        void Start()
        {
            gameObject.GetComponent<Button>().onClick.AddListener(() =>
            {
                GameObject.Find("SceneMaster").SendMessage("SelectButtonClicked", transform);
            });
        }
    }
}

