using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Kuromu
{

    public class ArtificialVoiceController : MonoBehaviour
    {
        /// <summary>
        /// 声音源组件
        /// </summary>
        private AudioSource audioSource;
        /// <summary>
        /// 声音源组
        /// </summary>
        private WaveGroup waveGroup;
        /// <summary>
        /// 声音播放列表
        /// </summary>
        public List<AudioClip> list;
        /// <summary>
        /// 到达终点语音
        /// </summary>
        public AudioClip audioEnd;

        void Start()
        {
            audioSource = GetComponent<AudioSource>();
            waveGroup = FindObjectOfType<WaveGroup>();
            list = new List<AudioClip>();
        }

        /// <summary>
        /// 播放语音
        /// </summary>
        /// <param name="voice">要播放的内容</param>
        public void PlayVoice(string[] voices)
        {
            if (voices.Length == 1)
            {
                PlayOneWave(voices[0]);
            }
            if (voices.Length == 3)
            {
                PlayThreeWave(voices);
            }
        }
        /// <summary>
        /// 到达终点
        /// </summary>
        public void VoiceEnd()
        {
            list.Clear();
            audioSource.Stop();
            audioSource.clip = audioEnd;
            audioSource.Play();
        }
        /// <summary>
        /// 播放3个的文本
        /// </summary>
        /// <param name="texts"></param>
        private void PlayThreeWave(string[] texts)
        {
            PlayOneWave(texts[0]);

            PlayNumber(texts[1]);

            switch (texts[2])
            {
                case "米":
                    list.Add(waveGroup.units[0]);
                    break;
                case "度":
                    list.Add(waveGroup.units[1]);
                    break;
            }
        }
        /// <summary>
        /// 播放数字
        /// </summary>
        /// <param name="number"></param>
        private void PlayNumber(string number)
        {
            var chars = number.ToCharArray();
            string[] numArray = new string[chars.Length];
            for (int i = 0; i < chars.Length; i++)
            {
                numArray[chars.Length - i - 1] = chars[i].ToString();
            }


            List<AudioClip> clipList = new List<AudioClip>();
            for (int i = 0; i < numArray.Length; i++)
            {
                switch (i)
                {
                    case 0:
                        if (numArray[i] != "0")
                        {
                            clipList.Add(waveGroup.digits[int.Parse(numArray[i])]);
                        }
                        break;
                    case 1:
                        if (numArray[0] != "0")
                        {
                            clipList.Add(waveGroup.units[2]);
                        }
                        break;
                    case 2:
                        if (numArray[i] != "0")
                        {
                            clipList.Add(waveGroup.digits[int.Parse(numArray[i])]);
                        }
                        break;
                    case 3:
                        if (numArray[i] != "0")
                        {
                            clipList.Add(waveGroup.tenDigit[int.Parse(numArray[i])]);
                        }
                        else
                        {
                            if (numArray[2] != "0")
                            {
                                clipList.Add(waveGroup.tenDigit[int.Parse(numArray[i])]);
                            }
                        }
                        break;
                    case 4:
                        clipList.Add(waveGroup.hundredsDigit[int.Parse(numArray[i])]);
                        break;
                }
            }

            for (int i = clipList.Count - 1; i >= 0; i--)
            {
                list.Add(clipList[i]);
            }
        }

        /// <summary>
        /// 播放单个文本
        /// </summary>
        /// <param name="text"></param>
        private void PlayOneWave(string text)
        {
            AudioClip audioClip = null;
            foreach (var item in waveGroup.textWaves)
            {
                if (text == item.text)
                {
                    audioClip = item.wave;
                    break;
                }
            }
            list.Add(audioClip);
        }
        /// <summary>
        /// 播放列表
        /// </summary>
        private void PlayList()
        {
            if (list.Count > 0)
            {
                audioSource.clip = list[0];
                audioSource.Play();
                list.RemoveAt(0);
            }
        }

        void Update()
        {
            if (audioSource.isPlaying)
            {
                return;
            }

            PlayList();
        }
    }

}
