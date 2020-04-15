using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections.Generic;

namespace Kuromu
{
    /// <summary>
    /// 公共功能
    /// </summary>
    public class Common : MonoBehaviour
    {
        /// <summary>
        /// 加载场景
        /// </summary>
        /// <param name="sceneName">场景名称</param>
        public void LoadScene(string sceneName)
        {
            SceneManager.LoadScene(sceneName);
        }
    }
}

