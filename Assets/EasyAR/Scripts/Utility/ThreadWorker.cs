//=============================================================================================================================
//
// Copyright (c) 2015-2020 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

using System;
using System.Collections.Generic;
using System.Threading;
using UnityEngine;

namespace easyar
{
    /// <summary>
    /// <para xml:lang="en">Thread worker, to do async tasks in worker thread. All tasks pushed into the worker are ensured to finish before the worker dispose.</para>
    /// <para xml:lang="zh">线程工作器，负责在工作线程上处理异步任务。所有推送到工作器的任务会被保证在销毁前运行。</para>
    /// </summary>
    public class ThreadWorker : IDisposable
    {
        private Thread thread;
        private bool finished;
        private Queue<Action> queue = new Queue<Action>();

        ~ThreadWorker()
        {
            Finish();
        }

        /// <summary>
        /// <para xml:lang="en">Dispose resources.</para>
        /// <para xml:lang="zh">销毁资源。</para>
        /// </summary>
        public void Dispose()
        {
            Finish();
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// <para xml:lang="en">Run <paramref name="task"/> in worker thread.</para>
        /// <para xml:lang="zh">在工作线程上运行任务<paramref name="task"/>。</para>
        /// </summary>
        public void Run(Action task)
        {
            if (thread == null)
            {
                CreateThread();
            }
            Monitor.Enter(queue);
            try
            {
                if (finished)
                {
                    return;
                }
                queue.Enqueue(task);
                Monitor.PulseAll(queue);
            }
            finally
            {
                Monitor.Exit(queue);
            }
        }

        private void CreateThread()
        {
            thread = new Thread(() =>
            {
                while (!finished)
                {
                    Action task = null;

                    Monitor.Enter(queue);
                    try
                    {
                        while (!finished && queue.Count == 0)
                        {
                            Monitor.Wait(queue);
                        }
                        if (queue.Count > 0)
                        {
                            task = queue.Dequeue();
                        }
                    }
                    finally
                    {
                        Monitor.Exit(queue);
                    }

                    if (task != null)
                    {
                        try
                        {
                            task();
                        }
                        catch (Exception ex)
                        {
                            Debug.LogError(ex.ToString());
                        }
                    }
                    if (finished)
                    {
                        while (queue.Count > 0)
                        {
                            task = queue.Dequeue();
                            if (task != null)
                            {
                                try
                                {
                                    task();
                                }
                                catch (Exception ex)
                                {
                                    Debug.LogError(ex.ToString());
                                }
                            }
                        }
                    }
                }
            });
            thread.Start();
        }

        private void Finish()
        {
            if (thread == null || !thread.IsAlive)
            {
                return;
            }

            Monitor.Enter(queue);
            try
            {
                finished = true;
                Monitor.PulseAll(queue);
            }
            finally
            {
                Monitor.Exit(queue);
            }
            thread.Join();
        }
    }
}
