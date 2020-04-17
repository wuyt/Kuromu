using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Wit.BaiduAip.Speech;

namespace Kuromu
{
    public class AIVoiceController : MonoBehaviour
    {
        /// <summary>
        /// 声音源组件
        /// </summary>
        private AudioSource audioSource;
        /// <summary>
        /// 声音源组
        /// </summary>
        private WaveGroupBaidu waveGroup;
        /// <summary>
        /// 声音播放列表
        /// </summary>
        public List<AudioClip> list;

        public string APIKey = "";
        public string SecretKey = "";
        private Tts _asr;

        void Start()
        {
            audioSource = GetComponent<AudioSource>();
            waveGroup = FindObjectOfType<WaveGroupBaidu>();
            list = new List<AudioClip>();

            _asr = new Tts(APIKey, SecretKey);
            StartCoroutine(_asr.GetAccessToken());
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
        /// 播放3个的文本
        /// </summary>
        /// <param name="texts"></param>
        private void PlayThreeWave(string[] texts)
        {
            string voice = texts[0] + texts[1] + texts[2];

            StartCoroutine(_asr.Synthesis(voice, s =>
            {
                if (s.Success)
                {
                    Debug.Log("合成成功");
                    list.Add(s.clip);
                }
                else
                {
                    Debug.Log(s.err_msg);
                }
            }));
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

