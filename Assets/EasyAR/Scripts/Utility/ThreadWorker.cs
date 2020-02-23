//=============================================================================================================================
//
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
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
    public class ThreadWorker : IDisposable
    {
        private Thread thread;
        private bool finished;
        private Queue<Action> queue = new Queue<Action>();

        ~ThreadWorker()
        {
            Finish();
        }

        public void Dispose()
        {
            Finish();
            GC.SuppressFinalize(this);
        }

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
