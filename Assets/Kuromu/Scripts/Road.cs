using UnityEngine;
using System;

namespace Kuromu
{
    /// <summary>
    /// 路径
    /// </summary>
    [Serializable]
    public class Road
    {
        /// <summary>
        /// 起始坐标
        /// </summary>
        public Vector3 startPosition;
        /// <summary>
        /// 到达坐标
        /// </summary>
        public Vector3 arrivalPosition;
        /// <summary>
        /// 起始位置名称
        /// </summary>
        public string startName;
        /// <summary>
        /// 到达位置名称
        /// </summary>
        public string arrivalName;
    }
}

