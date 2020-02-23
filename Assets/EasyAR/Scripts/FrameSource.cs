//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

using UnityEngine;

namespace easyar
{
    public abstract class FrameSource : MonoBehaviour
    {
        protected InputFrameSink sink;
        private ARSession arSession;

        public abstract bool HasSpatialInformation
        {
            get;
        }

        protected virtual void OnEnable()
        {
            if (arSession)
            {
                arSession.Assembly.Resume();
            }
        }

        protected virtual void OnDisable()
        {
            if (arSession)
            {
                arSession.Assembly.Pause();
            }
        }

        public virtual void Connect(InputFrameSink val)
        {
            sink = val;
        }

        public virtual void OnAssemble(ARSession session)
        {
            arSession = session;
        }
    }
}
