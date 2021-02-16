//================================================================================================================================
//
//  Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using System;
using System.Collections;
using UnityEngine;
#if UNITY_2019_2_OR_NEWER
using UnityEngine.Networking;
#endif

namespace easyar
{
    /// <summary>
    /// <para xml:lang="en">Path type.</para>
    /// <para xml:lang="zh">路径类型。</para>
    /// </summary>
    public enum PathType
    {
        /// <summary>
        /// <para xml:lang="en">Absolute path.</para>
        /// <para xml:lang="zh">绝对路径。</para>
        /// </summary>
        Absolute,
        /// <summary>
        /// <para xml:lang="en">Unity StreamingAssets path.</para>
        /// <para xml:lang="zh">UnityStreamingAssets路径。</para>
        /// </summary>
        StreamingAssets,
        /// <summary>
        /// <para xml:lang="en">Not file storage.</para>
        /// <para xml:lang="zh">不是文件存储。</para>
        /// </summary>
        None,
    }

    /// <summary>
    /// <para xml:lang="en">File utility.</para>
    /// <para xml:lang="zh">文件工具。</para>
    /// </summary>
    public static class FileUtil
    {
        /// <summary>
        /// <para xml:lang="en">Async Load file and return <see cref="Buffer"/> object in the callback.</para>
        /// <para xml:lang="zh">异步加载文件，回调返回<see cref="Buffer"/>对象。</para>
        /// </summary>
        public static IEnumerator LoadFile(string filePath, PathType filePathType, Action<Buffer> onLoad)
        {
            return LoadFile(filePath, filePathType, (data) =>
            {
                if (onLoad == null)
                {
                    return;
                }
                using (var buffer = Buffer.wrapByteArray(data))
                {
                    onLoad(buffer);
                }
            });
        }

        /// <summary>
        /// <para xml:lang="en">Async Load file and return byte array in the callback.</para>
        /// <para xml:lang="zh">异步加载文件，回调返回字节数组。</para>
        /// </summary>
        public static IEnumerator LoadFile(string filePath, PathType filePathType, Action<byte[]> onLoad)
        {
            if (onLoad == null)
            {
                yield break;
            }
            var path = filePath;
            if (filePathType == PathType.StreamingAssets)
            {
                path = Application.streamingAssetsPath + "/" + path;
            }
            byte[] data;
#if UNITY_2019_2_OR_NEWER
            using (var handle = new DownloadHandlerBuffer())
            {
                var webRequest = new UnityWebRequest(PathToUrl(path), "GET", handle, null);
                webRequest.Send();
                while (!handle.isDone)
                {
                    yield return 0;
                }
                if (!string.IsNullOrEmpty(webRequest.error))
                {
                    Debug.LogError(webRequest.error);
                    yield break;
                }
                data = handle.data;
            }
#else
            using (var www = new WWW(PathToUrl(path)))
            {
                while (!www.isDone)
                {
                    yield return 0;
                }
                if (!string.IsNullOrEmpty(www.error))
                {
                    Debug.LogError(www.error);
                    yield break;
                }
                data = www.bytes;
            }
#endif
            onLoad(data);
        }

        /// <summary>
        /// <para xml:lang="en">Convert file path to URL.</para>
        /// <para xml:lang="zh">将路径转换成URL。</para>
        /// </summary>
        public static string PathToUrl(string path)
        {
            if (string.IsNullOrEmpty(path) || path.StartsWith("jar:file://") || path.StartsWith("file://") || path.StartsWith("http://") || path.StartsWith("https://"))
            {
                return path;
            }
            if (Application.platform == RuntimePlatform.OSXEditor ||
                Application.platform == RuntimePlatform.OSXPlayer ||
                Application.platform == RuntimePlatform.IPhonePlayer ||
                Application.platform == RuntimePlatform.Android)
            {
                path = "file://" + path;
            }
            else if (Application.platform == RuntimePlatform.WindowsEditor || Application.platform == RuntimePlatform.WindowsPlayer)
            {
                path = "file:///" + path;
            }
            return path;
        }
    }
}
