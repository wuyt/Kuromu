using UnityEngine;
using System;

namespace Kuromu
{
    /// <summary>
    /// 关键点
    /// </summary>
    [Serializable]
    public class KeyPoint
    {
        /// <summary>
        /// 位置
        /// </summary>
        public Vector3 position;
        /// <summary>
        /// 角度
        /// </summary>
        public Quaternion rotation;
        /// <summary>
        /// 名称
        /// </summary>
        public string name;
        /// <summary>
        /// 类型：0=目的地；1=途经点
        /// </summary>
        public int pointType;
    }
}

