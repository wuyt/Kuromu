using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Kuromu
{

    public class ArtificialVoiceController : MonoBehaviour
    {
        /// <summary>
        /// 播放语音
        /// </summary>
        /// <param name="voice">要播放的内容</param>
        public void PlayVoice(string[] voices)
        {
            foreach(string v in voices){
                Debug.Log(v);
            }
        }
    }

}
