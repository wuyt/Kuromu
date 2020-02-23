//================================================================================================================================
//
//  Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
//  EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
//  and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//================================================================================================================================

namespace easyar
{
    public abstract class CameraSource : FrameSource
    {
        protected int bufferCapacity;

        public virtual int BufferCapacity
        {
            get
            {
                return bufferCapacity;
            }
            set
            {
                bufferCapacity = value;
            }
        }

        protected virtual void Start()
        {
            if (!EasyARController.Initialized)
            {
                return;
            }
            Open();
        }

        protected virtual void OnDestroy()
        {
            Close();
        }

        public abstract void Open();
        public abstract void Close();
    }
}
