using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

namespace Kuromu
{
    public class WaveGroup : MonoBehaviour
    {
        /// <summary>
        /// 单位
        /// </summary>
        public AudioClip[] units;
        /// <summary>
        /// 百位数
        /// </summary>
        public AudioClip[] hundredsDigit;
        /// <summary>
        /// 十位数
        /// </summary>
        public AudioClip[] tenDigit;
        /// <summary>
        /// 个位数
        /// </summary>
        public AudioClip[] digits;
        /// <summary>
        /// 文本语音组
        /// </summary>
        public TextWave[] textWaves;
    }

    [Serializable]
    public class TextWave
    {
        public string text;
        public AudioClip wave;
    }
}

