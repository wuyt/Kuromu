using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace Kuromu
{
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

