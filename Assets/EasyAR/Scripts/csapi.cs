//=============================================================================================================================
//
// EasyAR Sense 4.0.0-final-7bc4102ce
// Copyright (c) 2015-2019 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
// EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
// and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
//
//=============================================================================================================================

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
#if ENABLE_IL2CPP
using AOT;
#endif

namespace easyar
{
    internal static partial class Detail
    {
#if UNITY_IOS && !UNITY_EDITOR
        public const String BindingLibraryName = "__Internal";
#else
        public const String BindingLibraryName = "EasyAR";
#endif
    }

    public struct Unit {}
    public enum OptionalTag
    {
        None = 0,
        Some = 1
    }
    public struct Optional<T>
    {
        public OptionalTag _Tag;

        public Unit None;
        public T Some;

        public static Optional<T> CreateNone() { return new Optional<T> { _Tag = OptionalTag.None, None = new Unit() }; }
        public static Optional<T> CreateSome(T Value) { return new Optional<T> { _Tag = OptionalTag.Some, Some = Value }; }

        public Boolean OnNone { get { return _Tag == OptionalTag.None; } }
        public Boolean OnSome { get { return _Tag == OptionalTag.Some; } }

        public static Optional<T> Empty { get { return CreateNone(); } }
        public static implicit operator Optional<T>(T v)
        {
            if (v == null)
            {
                return CreateNone();
            }
            else
            {
                return CreateSome(v);
            }
        }
        public static explicit operator T(Optional<T> v)
        {
            if (v.OnNone)
            {
                throw new InvalidOperationException();
            }
            return v.Some;
        }
        public static Boolean operator ==(Optional<T> Left, Optional<T> Right)
        {
            return Equals(Left, Right);
        }
        public static Boolean operator !=(Optional<T> Left, Optional<T> Right)
        {
            return !Equals(Left, Right);
        }
        public static Boolean operator ==(Optional<T>? Left, Optional<T>? Right)
        {
            return Equals(Left, Right);
        }
        public static Boolean operator !=(Optional<T>? Left, Optional<T>? Right)
        {
            return !Equals(Left, Right);
        }
        public override Boolean Equals(Object obj)
        {
            if (obj == null) { return Equals(this, null); }
            if (obj.GetType() != typeof(Optional<T>)) { return false; }
            var o = (Optional<T>)(obj);
            return Equals(this, o);
        }
        public override Int32 GetHashCode()
        {
            if (OnNone) { return 0; }
            return Some.GetHashCode();
        }

        private static Boolean Equals(Optional<T> Left, Optional<T> Right)
        {
            if (Left.OnNone && Right.OnNone)
            {
                return true;
            }
            if (Left.OnNone || Right.OnNone)
            {
                return false;
            }
            return Left.Some.Equals(Right.Some);
        }
        private static Boolean Equals(Optional<T>? Left, Optional<T>? Right)
        {
            if ((!Left.HasValue || Left.Value.OnNone) && (!Right.HasValue || Right.Value.OnNone))
            {
                return true;
            }
            if (!Left.HasValue || Left.Value.OnNone || !Right.HasValue || Right.Value.OnNone)
            {
                return false;
            }
            return Equals(Left.Value, Right.Value);
        }

        public T Value
        {
            get
            {
                if (OnSome)
                {
                    return Some;
                }
                else
                {
                    throw new InvalidOperationException();
                }
            }
        }
        public T ValueOrDefault(T Default)
        {
            if (OnSome)
            {
                return Some;
            }
            else
            {
                return Default;
            }
        }

        public override String ToString()
        {
            if (OnSome)
            {
                return Some.ToString();
            }
            else
            {
                return "-";
            }
        }
    }

    public abstract class RefBase : IDisposable
    {
        internal IntPtr cdata_;
        internal Action<IntPtr> deleter_;
        internal delegate void Retainer(IntPtr This, out IntPtr Return);
        internal Retainer retainer_;

        internal RefBase(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer)
        {
            cdata_ = cdata;
            deleter_ = deleter;
            retainer_ = retainer;
        }

        internal IntPtr cdata
        {
            get
            {
                if (cdata_ == IntPtr.Zero) { throw new ObjectDisposedException(GetType().FullName); }
                return cdata_;
            }
        }

        ~RefBase()
        {
            if ((cdata_ != IntPtr.Zero) && (deleter_ != null))
            {
                deleter_(cdata_);
                cdata_ = IntPtr.Zero;
                deleter_ = null;
                retainer_ = null;
            }
        }

        public void Dispose()
        {
            if ((cdata_ != IntPtr.Zero) && (deleter_ != null))
            {
                deleter_(cdata_);
                cdata_ = IntPtr.Zero;
                deleter_ = null;
                retainer_ = null;
            }
            GC.SuppressFinalize(this);
        }

        protected abstract object CloneObject();
        public RefBase Clone()
        {
            return (RefBase)(CloneObject());
        }
    }

    internal static partial class Detail
    {
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_String_from_utf8(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_String_from_utf8_begin(IntPtr begin, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_String_begin(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_String_end(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_String_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_String__dtor(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_bufferDictionary(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_setBufferDictionary(IntPtr This, IntPtr bufferDictionary);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_objPath(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_setObjPath(IntPtr This, IntPtr objPath);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_name(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_setName(IntPtr This, IntPtr name);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_uid(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_setUid(IntPtr This, IntPtr uid);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_meta(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_setMeta(IntPtr This, IntPtr meta);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_ObjectTargetParameters_scale(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters_setScale(IntPtr This, float size);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTargetParameters__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ObjectTargetParameters__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_createFromParameters(IntPtr parameters, out OptionalOfObjectTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_createFromObjectFile(IntPtr path, StorageType storageType, IntPtr name, IntPtr uid, IntPtr meta, float scale, out OptionalOfObjectTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_setupAll(IntPtr path, StorageType storageType, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_ObjectTarget_scale(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_boundingBox(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ObjectTarget_setScale(IntPtr This, float scale);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ObjectTarget_runtimeID(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_uid(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_name(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_setName(IntPtr This, IntPtr name);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_meta(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget_setMeta(IntPtr This, IntPtr data);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTarget__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ObjectTarget__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castObjectTargetToTarget(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastTargetToObjectTarget(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTrackerResult_targetInstances(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTrackerResult_setTargetInstances(IntPtr This, IntPtr instances);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTrackerResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTrackerResult__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ObjectTrackerResult__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castObjectTrackerResultToFrameFilterResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastFrameFilterResultToObjectTrackerResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castObjectTrackerResultToTargetTrackerResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastTargetTrackerResultToObjectTrackerResult(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ObjectTracker_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_feedbackFrameSink(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ObjectTracker_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_outputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ObjectTracker_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_loadTarget(IntPtr This, IntPtr target, IntPtr callbackScheduler, FunctorOfVoidFromTargetAndBool callback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_unloadTarget(IntPtr This, IntPtr target, IntPtr callbackScheduler, FunctorOfVoidFromTargetAndBool callback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker_targets(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ObjectTracker_setSimultaneousNum(IntPtr This, int num);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ObjectTracker_simultaneousNum(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ObjectTracker__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ObjectTracker__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CloudRecognizer_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CloudRecognizer_inputFrameSink(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CloudRecognizer_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CloudRecognizer_create(IntPtr cloudRecognitionServiceServerAddress, IntPtr apiKey, IntPtr apiSecret, IntPtr cloudRecognitionServiceAppId, IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromCloudStatusAndListOfTarget callback, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CloudRecognizer_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CloudRecognizer_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CloudRecognizer_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CloudRecognizer__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CloudRecognizer__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_CloudRecognizer__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_DenseSpatialMap_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap_inputFrameSink(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_DenseSpatialMap_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_DenseSpatialMap_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap_getMesh(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_DenseSpatialMap_updateSceneMesh(IntPtr This, [MarshalAs(UnmanagedType.I1)] bool updateMeshAll);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DenseSpatialMap__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_DenseSpatialMap__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_SceneMesh_getNumOfVertexAll(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_SceneMesh_getNumOfIndexAll(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getVerticesAll(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getNormalsAll(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getIndicesAll(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_SceneMesh_getNumOfVertexIncremental(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_SceneMesh_getNumOfIndexIncremental(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getVerticesIncremental(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getNormalsIncremental(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getIndicesIncremental(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh_getBlocksInfoIncremental(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_SceneMesh_getBlockDimensionInMeters(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SceneMesh__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SceneMesh__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Matrix44F easyar_SurfaceTrackerResult_transform(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTrackerResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTrackerResult__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SurfaceTrackerResult__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castSurfaceTrackerResultToFrameFilterResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastFrameFilterResultToSurfaceTrackerResult(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SurfaceTracker_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker_inputFrameSink(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_SurfaceTracker_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker_outputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SurfaceTracker_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker_alignTargetToCameraImagePoint(IntPtr This, Vec2F cameraImagePoint);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SurfaceTracker__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SurfaceTracker__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_MotionTrackerCameraDevice_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice_setBufferCapacity(IntPtr This, int capacity);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_MotionTrackerCameraDevice_bufferCapacity(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice_inputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_MotionTrackerCameraDevice_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_MotionTrackerCameraDevice__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_MotionTrackerCameraDevice__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_image(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_setImage(IntPtr This, IntPtr image);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_name(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_setName(IntPtr This, IntPtr name);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_uid(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_setUid(IntPtr This, IntPtr uid);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_meta(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_setMeta(IntPtr This, IntPtr meta);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_ImageTargetParameters_scale(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters_setScale(IntPtr This, float scale);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTargetParameters__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ImageTargetParameters__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_createFromParameters(IntPtr parameters, out OptionalOfImageTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_createFromTargetFile(IntPtr path, StorageType storageType, out OptionalOfImageTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_createFromTargetData(IntPtr buffer, out OptionalOfImageTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ImageTarget_save(IntPtr This, IntPtr path);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_createFromImageFile(IntPtr path, StorageType storageType, IntPtr name, IntPtr uid, IntPtr meta, float scale, out OptionalOfImageTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_setupAll(IntPtr path, StorageType storageType, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_ImageTarget_scale(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_ImageTarget_aspectRatio(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ImageTarget_setScale(IntPtr This, float scale);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_images(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ImageTarget_runtimeID(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_uid(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_name(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_setName(IntPtr This, IntPtr name);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_meta(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget_setMeta(IntPtr This, IntPtr data);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTarget__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ImageTarget__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castImageTargetToTarget(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastTargetToImageTarget(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTrackerResult_targetInstances(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTrackerResult_setTargetInstances(IntPtr This, IntPtr instances);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTrackerResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTrackerResult__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ImageTrackerResult__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castImageTrackerResultToFrameFilterResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastFrameFilterResultToImageTrackerResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castImageTrackerResultToTargetTrackerResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastTargetTrackerResultToImageTrackerResult(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ImageTracker_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_feedbackFrameSink(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ImageTracker_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_outputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_createWithMode(ImageTrackerMode trackMode, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ImageTracker_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_loadTarget(IntPtr This, IntPtr target, IntPtr callbackScheduler, FunctorOfVoidFromTargetAndBool callback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_unloadTarget(IntPtr This, IntPtr target, IntPtr callbackScheduler, FunctorOfVoidFromTargetAndBool callback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker_targets(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ImageTracker_setSimultaneousNum(IntPtr This, int num);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ImageTracker_simultaneousNum(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageTracker__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ImageTracker__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_Recorder_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Recorder_requestPermissions(IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromPermissionStatusAndString permissionCallback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Recorder_create(IntPtr config, IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromRecordStatusAndString statusCallback, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Recorder_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Recorder_updateFrame(IntPtr This, IntPtr texture, int width, int height);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_Recorder_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Recorder__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Recorder__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_Recorder__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setOutputFile(IntPtr This, IntPtr path);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_RecorderConfiguration_setProfile(IntPtr This, RecordProfile profile);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setVideoSize(IntPtr This, RecordVideoSize framesize);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setVideoBitrate(IntPtr This, int bitrate);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setChannelCount(IntPtr This, int count);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setAudioSampleRate(IntPtr This, int samplerate);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setAudioBitrate(IntPtr This, int bitrate);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setVideoOrientation(IntPtr This, RecordVideoOrientation mode);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration_setZoomMode(IntPtr This, RecordZoomMode mode);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_RecorderConfiguration__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_RecorderConfiguration__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern MotionTrackingStatus easyar_SparseSpatialMapResult_getMotionTrackingStatus(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern OptionalOfMatrix44F easyar_SparseSpatialMapResult_getVioPose(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern OptionalOfMatrix44F easyar_SparseSpatialMapResult_getMapPose(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SparseSpatialMapResult_getLocalizationStatus(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapResult_getLocalizationMapID(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapResult__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SparseSpatialMapResult__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castSparseSpatialMapResultToFrameFilterResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastFrameFilterResultToSparseSpatialMapResult(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_PlaneData__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern PlaneType easyar_PlaneData_getType(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Matrix44F easyar_PlaneData_getPose(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_PlaneData_getExtentX(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_PlaneData_getExtentZ(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_PlaneData__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_PlaneData__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_PlaneData__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapConfig__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapConfig_setLocalizationMode(IntPtr This, LocalizationMode @value);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern LocalizationMode easyar_SparseSpatialMapConfig_getLocalizationMode(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapConfig__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapConfig__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SparseSpatialMapConfig__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SparseSpatialMap_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_inputFrameSink(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_SparseSpatialMap_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_outputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SparseSpatialMap_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_getPointCloudBuffer(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_getMapPlanes(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_hitTestAgainstPointCloud(IntPtr This, Vec2F cameraImagePoint, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_hitTestAgainstPlanes(IntPtr This, Vec2F cameraImagePoint, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_getMapVersion(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_unloadMap(IntPtr This, IntPtr mapID, IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromBool resultCallBack);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_setConfig(IntPtr This, IntPtr config);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_getConfig(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SparseSpatialMap_startLocalization(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap_stopLocalization(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMap__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SparseSpatialMap__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_SparseSpatialMapManager_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapManager_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapManager_host(IntPtr This, IntPtr mapBuilder, IntPtr apiKey, IntPtr apiSecret, IntPtr sparseSpatialMapAppId, IntPtr name, OptionalOfImage preview, IntPtr callbackScheduler, FunctorOfVoidFromBoolAndStringAndString onCompleted);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapManager_load(IntPtr This, IntPtr mapTracker, IntPtr serverMapId, IntPtr apiKey, IntPtr apiSecret, IntPtr sparseSpatialMapAppId, IntPtr callbackScheduler, FunctorOfVoidFromBoolAndString onCompleted);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapManager_clear(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapManager__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SparseSpatialMapManager__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SparseSpatialMapManager__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImageHelper_decode(IntPtr buffer, out OptionalOfImage Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ARCoreCameraDevice_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ARCoreCameraDevice_bufferCapacity(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice_setBufferCapacity(IntPtr This, int capacity);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice_inputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ARCoreCameraDevice_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARCoreCameraDevice__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ARCoreCameraDevice__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ARKitCameraDevice_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ARKitCameraDevice_bufferCapacity(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice_setBufferCapacity(IntPtr This, int capacity);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice_inputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_ARKitCameraDevice_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ARKitCameraDevice__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ARKitCameraDevice__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CallbackScheduler__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CallbackScheduler__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_CallbackScheduler__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DelayedCallbackScheduler__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_DelayedCallbackScheduler_runOne(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DelayedCallbackScheduler__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_DelayedCallbackScheduler__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_DelayedCallbackScheduler__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castDelayedCallbackSchedulerToCallbackScheduler(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastCallbackSchedulerToDelayedCallbackScheduler(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImmediateCallbackScheduler_getDefault(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImmediateCallbackScheduler__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ImmediateCallbackScheduler__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ImmediateCallbackScheduler__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castImmediateCallbackSchedulerToCallbackScheduler(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastCallbackSchedulerToImmediateCallbackScheduler(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern AndroidCameraApiType easyar_CameraDevice_androidCameraApiType(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_setAndroidCameraApiType(IntPtr This, AndroidCameraApiType type);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraDevice_bufferCapacity(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_setBufferCapacity(IntPtr This, int capacity);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_inputFrameSource(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_setStateChangedCallback(IntPtr This, IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromCameraState stateChangedCallback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_requestPermissions(IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromPermissionStatusAndString permissionCallback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraDevice_cameraCount();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_openWithIndex(IntPtr This, int cameraIndex);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_openWithSpecificType(IntPtr This, CameraDeviceType type);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_openWithPreferredType(IntPtr This, CameraDeviceType type);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_start(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraDevice_index(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern CameraDeviceType easyar_CameraDevice_type(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_cameraParameters(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice_setCameraParameters(IntPtr This, IntPtr cameraParameters);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2I easyar_CameraDevice_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraDevice_supportedSizeCount(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2I easyar_CameraDevice_supportedSize(IntPtr This, int index);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_setSize(IntPtr This, Vec2I size);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraDevice_supportedFrameRateRangeCount(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_CameraDevice_supportedFrameRateRangeLower(IntPtr This, int index);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_CameraDevice_supportedFrameRateRangeUpper(IntPtr This, int index);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraDevice_frameRateRange(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_setFrameRateRange(IntPtr This, int index);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_setFlashTorchMode(IntPtr This, [MarshalAs(UnmanagedType.I1)] bool on);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_setFocusMode(IntPtr This, CameraDeviceFocusMode focusMode);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraDevice_autoFocus(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDevice__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_CameraDevice__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraDeviceSelector_createCameraDevice(CameraDevicePreference preference, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSink_handle(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSink__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSink__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SignalSink__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSource_setHandler(IntPtr This, OptionalOfFunctorOfVoid handler);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSource_connect(IntPtr This, IntPtr sink);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSource_disconnect(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSource__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_SignalSource__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_SignalSource__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSink_handle(IntPtr This, IntPtr inputData);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSink__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSink__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrameSink__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSource_setHandler(IntPtr This, OptionalOfFunctorOfVoidFromInputFrame handler);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSource_connect(IntPtr This, IntPtr sink);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSource_disconnect(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSource__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameSource__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrameSource__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSink_handle(IntPtr This, IntPtr inputData);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSink__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSink__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_OutputFrameSink__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSource_setHandler(IntPtr This, OptionalOfFunctorOfVoidFromOutputFrame handler);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSource_connect(IntPtr This, IntPtr sink);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSource_disconnect(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSource__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameSource__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_OutputFrameSource__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSink_handle(IntPtr This, IntPtr inputData);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSink__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSink__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_FeedbackFrameSink__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSource_setHandler(IntPtr This, OptionalOfFunctorOfVoidFromFeedbackFrame handler);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSource_connect(IntPtr This, IntPtr sink);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSource_disconnect(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSource__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameSource__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_FeedbackFrameSource__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameFork_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameFork_output(IntPtr This, int index, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_InputFrameFork_outputCount(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameFork_create(int outputCount, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameFork__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameFork__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrameFork__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameFork_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameFork_output(IntPtr This, int index, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_OutputFrameFork_outputCount(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameFork_create(int outputCount, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameFork__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameFork__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_OutputFrameFork__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameJoin_input(IntPtr This, int index, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameJoin_output(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_OutputFrameJoin_inputCount(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameJoin_create(int inputCount, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameJoin_createWithJoiner(int inputCount, FunctorOfOutputFrameFromListOfOutputFrame joiner, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameJoin__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameJoin__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_OutputFrameJoin__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameFork_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameFork_output(IntPtr This, int index, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_FeedbackFrameFork_outputCount(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameFork_create(int outputCount, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameFork__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrameFork__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_FeedbackFrameFork__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameThrottler_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_InputFrameThrottler_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameThrottler_output(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameThrottler_signalInput(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameThrottler_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameThrottler__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameThrottler__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrameThrottler__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_OutputFrameBuffer_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer_signalOutput(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer_peek(IntPtr This, out OptionalOfOutputFrame Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer_pause(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer_resume(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrameBuffer__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_OutputFrameBuffer__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToOutputFrameAdapter_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToOutputFrameAdapter_output(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToOutputFrameAdapter_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToOutputFrameAdapter__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToOutputFrameAdapter__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrameToOutputFrameAdapter__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToFeedbackFrameAdapter_input(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_InputFrameToFeedbackFrameAdapter_bufferRequirement(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToFeedbackFrameAdapter_sideInput(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToFeedbackFrameAdapter_output(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToFeedbackFrameAdapter_create(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToFeedbackFrameAdapter__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrameToFeedbackFrameAdapter__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrameToFeedbackFrameAdapter__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_Engine_schemaHash();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_Engine_initialize(IntPtr key);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Engine_onPause();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Engine_onResume();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Engine_errorMessage(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Engine_versionString(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Engine_name(out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_InputFrame_index(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame_image(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_InputFrame_hasCameraParameters(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame_cameraParameters(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_InputFrame_hasTemporalInformation(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern double easyar_InputFrame_timestamp(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_InputFrame_hasSpatialInformation(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Matrix44F easyar_InputFrame_cameraTransform(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern MotionTrackingStatus easyar_InputFrame_trackingStatus(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame_create(IntPtr image, IntPtr cameraParameters, double timestamp, Matrix44F cameraTransform, MotionTrackingStatus trackingStatus, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame_createWithImageAndCameraParametersAndTemporal(IntPtr image, IntPtr cameraParameters, double timestamp, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame_createWithImageAndCameraParameters(IntPtr image, IntPtr cameraParameters, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame_createWithImage(IntPtr image, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_InputFrame__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_InputFrame__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FrameFilterResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FrameFilterResult__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_FrameFilterResult__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrame__ctor(IntPtr inputFrame, IntPtr results, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_OutputFrame_index(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrame_inputFrame(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrame_results(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrame__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_OutputFrame__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_OutputFrame__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrame__ctor(IntPtr inputFrame, OptionalOfOutputFrame previousOutputFrame, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrame_inputFrame(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrame_previousOutputFrame(IntPtr This, out OptionalOfOutputFrame Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrame__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_FeedbackFrame__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_FeedbackFrame__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_Target_runtimeID(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target_uid(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target_name(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target_setName(IntPtr This, IntPtr name);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target_meta(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target_setMeta(IntPtr This, IntPtr data);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Target__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_Target__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetInstance__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern TargetStatus easyar_TargetInstance_status(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetInstance_target(IntPtr This, out OptionalOfTarget Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Matrix44F easyar_TargetInstance_pose(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetInstance__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetInstance__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_TargetInstance__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetTrackerResult_targetInstances(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetTrackerResult_setTargetInstances(IntPtr This, IntPtr instances);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetTrackerResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TargetTrackerResult__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_TargetTrackerResult__typeName(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_castTargetTrackerResultToFrameFilterResult(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_tryCastFrameFilterResultToTargetTrackerResult(IntPtr This, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_TextureId_getInt(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_TextureId_getPointer(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TextureId_fromInt(int @value, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TextureId_fromPointer(IntPtr ptr, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TextureId__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_TextureId__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_TextureId__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_VideoPlayer_isAvailable();
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_setVideoType(IntPtr This, VideoType videoType);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_setRenderTexture(IntPtr This, IntPtr texture);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_open(IntPtr This, IntPtr path, StorageType storageType, IntPtr callbackScheduler, OptionalOfFunctorOfVoidFromVideoStatus callback);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_close(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_VideoPlayer_play(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_stop(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_pause(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_VideoPlayer_isRenderTextureAvailable(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer_updateFrame(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_VideoPlayer_duration(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_VideoPlayer_currentPosition(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_VideoPlayer_seek(IntPtr This, int position);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2I easyar_VideoPlayer_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern float easyar_VideoPlayer_volume(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_VideoPlayer_setVolume(IntPtr This, float volume);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_VideoPlayer__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_VideoPlayer__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Buffer_wrap(IntPtr ptr, int size, FunctorOfVoid deleter, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Buffer_create(int size, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_Buffer_data(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_Buffer_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Buffer_memoryCopy(IntPtr src, IntPtr dest, int length);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_Buffer_tryCopyFrom(IntPtr This, IntPtr src, int srcIndex, int index, int length);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_Buffer_tryCopyTo(IntPtr This, int index, IntPtr dest, int destIndex, int length);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Buffer_partition(IntPtr This, int index, int length, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Buffer__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Buffer__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_Buffer__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferDictionary__ctor(out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_BufferDictionary_count(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_BufferDictionary_contains(IntPtr This, IntPtr path);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferDictionary_tryGet(IntPtr This, IntPtr path, out OptionalOfBuffer Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferDictionary_set(IntPtr This, IntPtr path, IntPtr buffer);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_BufferDictionary_remove(IntPtr This, IntPtr path);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferDictionary_clear(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferDictionary__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferDictionary__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_BufferDictionary__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferPool__ctor(int block_size, int capacity, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_BufferPool_block_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_BufferPool_capacity(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_BufferPool_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferPool_tryAcquire(IntPtr This, out OptionalOfBuffer Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferPool__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_BufferPool__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_BufferPool__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraParameters__ctor(Vec2I size, Vec2F focalLength, Vec2F principalPoint, CameraDeviceType cameraDeviceType, int cameraOrientation, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2I easyar_CameraParameters_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2F easyar_CameraParameters_focalLength(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2F easyar_CameraParameters_principalPoint(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern CameraDeviceType easyar_CameraParameters_cameraDeviceType(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraParameters_cameraOrientation(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraParameters_createWithDefaultIntrinsics(Vec2I size, CameraDeviceType cameraDeviceType, int cameraOrientation, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_CameraParameters_imageOrientation(IntPtr This, int screenRotation);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraParameters_imageHorizontalFlip(IntPtr This, [MarshalAs(UnmanagedType.I1)] bool manualHorizontalFlip);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Matrix44F easyar_CameraParameters_projection(IntPtr This, float nearPlane, float farPlane, float viewportAspectRatio, int screenRotation, [MarshalAs(UnmanagedType.I1)] bool combiningFlip, [MarshalAs(UnmanagedType.I1)] bool manualHorizontalFlip);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Matrix44F easyar_CameraParameters_imageProjection(IntPtr This, float viewportAspectRatio, int screenRotation, [MarshalAs(UnmanagedType.I1)] bool combiningFlip, [MarshalAs(UnmanagedType.I1)] bool manualHorizontalFlip);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2F easyar_CameraParameters_screenCoordinatesFromImageCoordinates(IntPtr This, float viewportAspectRatio, int screenRotation, [MarshalAs(UnmanagedType.I1)] bool combiningFlip, [MarshalAs(UnmanagedType.I1)] bool manualHorizontalFlip, Vec2F imageCoordinates);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec2F easyar_CameraParameters_imageCoordinatesFromScreenCoordinates(IntPtr This, float viewportAspectRatio, int screenRotation, [MarshalAs(UnmanagedType.I1)] bool combiningFlip, [MarshalAs(UnmanagedType.I1)] bool manualHorizontalFlip, Vec2F screenCoordinates);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_CameraParameters_equalsTo(IntPtr This, IntPtr other);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraParameters__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_CameraParameters__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_CameraParameters__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Image__ctor(IntPtr buffer, PixelFormat format, int width, int height, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Image_buffer(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern PixelFormat easyar_Image_format(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_Image_width(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_Image_height(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool easyar_Image_empty(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Image__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Image__retain(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_Image__typeName(IntPtr This);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_JniUtility_wrapByteArray(IntPtr bytes, [MarshalAs(UnmanagedType.I1)] bool readOnly, FunctorOfVoid deleter, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_JniUtility_wrapBuffer(IntPtr directBuffer, FunctorOfVoid deleter, out IntPtr Return);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Log_setLogFunc(FunctorOfVoidFromLogLevelAndString func);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_Log_resetLogFunc();

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfObjectTarget__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfObjectTarget__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfObjectTarget_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfObjectTarget_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfObjectTarget_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfVec3F__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfVec3F__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfVec3F_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfVec3F_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern Vec3F easyar_ListOfVec3F_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfTargetInstance__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfTargetInstance__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfTargetInstance_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfTargetInstance_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfTargetInstance_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfOptionalOfFrameFilterResult__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfOptionalOfFrameFilterResult__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfOptionalOfFrameFilterResult_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfOptionalOfFrameFilterResult_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern OptionalOfFrameFilterResult easyar_ListOfOptionalOfFrameFilterResult_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfTarget__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfTarget__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfTarget_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfTarget_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfTarget_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfBlockInfo__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfBlockInfo__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfBlockInfo_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfBlockInfo_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern BlockInfo easyar_ListOfBlockInfo_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfImageTarget__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfImageTarget__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfImageTarget_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfImageTarget_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfImageTarget_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfImage__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfImage__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfImage_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfImage_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfImage_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfPlaneData__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfPlaneData__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfPlaneData_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfPlaneData_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfPlaneData_at(IntPtr This, int index);

        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfOutputFrame__ctor(IntPtr begin, IntPtr end, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfOutputFrame__dtor(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern void easyar_ListOfOutputFrame_copy(IntPtr This, out IntPtr Return);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern int easyar_ListOfOutputFrame_size(IntPtr This);
        [DllImport(BindingLibraryName, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr easyar_ListOfOutputFrame_at(IntPtr This, int index);

        private static Dictionary<String, Func<IntPtr, RefBase>> TypeNameToConstructor = new Dictionary<String, Func<IntPtr, RefBase>>
        {
            { "ObjectTargetParameters", cdata => new ObjectTargetParameters(cdata, easyar_ObjectTargetParameters__dtor, easyar_ObjectTargetParameters__retain) },
            { "ObjectTarget", cdata => new ObjectTarget(cdata, easyar_ObjectTarget__dtor, easyar_ObjectTarget__retain) },
            { "ObjectTrackerResult", cdata => new ObjectTrackerResult(cdata, easyar_ObjectTrackerResult__dtor, easyar_ObjectTrackerResult__retain) },
            { "ObjectTracker", cdata => new ObjectTracker(cdata, easyar_ObjectTracker__dtor, easyar_ObjectTracker__retain) },
            { "CloudRecognizer", cdata => new CloudRecognizer(cdata, easyar_CloudRecognizer__dtor, easyar_CloudRecognizer__retain) },
            { "DenseSpatialMap", cdata => new DenseSpatialMap(cdata, easyar_DenseSpatialMap__dtor, easyar_DenseSpatialMap__retain) },
            { "SceneMesh", cdata => new SceneMesh(cdata, easyar_SceneMesh__dtor, easyar_SceneMesh__retain) },
            { "SurfaceTrackerResult", cdata => new SurfaceTrackerResult(cdata, easyar_SurfaceTrackerResult__dtor, easyar_SurfaceTrackerResult__retain) },
            { "SurfaceTracker", cdata => new SurfaceTracker(cdata, easyar_SurfaceTracker__dtor, easyar_SurfaceTracker__retain) },
            { "MotionTrackerCameraDevice", cdata => new MotionTrackerCameraDevice(cdata, easyar_MotionTrackerCameraDevice__dtor, easyar_MotionTrackerCameraDevice__retain) },
            { "ImageTargetParameters", cdata => new ImageTargetParameters(cdata, easyar_ImageTargetParameters__dtor, easyar_ImageTargetParameters__retain) },
            { "ImageTarget", cdata => new ImageTarget(cdata, easyar_ImageTarget__dtor, easyar_ImageTarget__retain) },
            { "ImageTrackerResult", cdata => new ImageTrackerResult(cdata, easyar_ImageTrackerResult__dtor, easyar_ImageTrackerResult__retain) },
            { "ImageTracker", cdata => new ImageTracker(cdata, easyar_ImageTracker__dtor, easyar_ImageTracker__retain) },
            { "Recorder", cdata => new Recorder(cdata, easyar_Recorder__dtor, easyar_Recorder__retain) },
            { "RecorderConfiguration", cdata => new RecorderConfiguration(cdata, easyar_RecorderConfiguration__dtor, easyar_RecorderConfiguration__retain) },
            { "SparseSpatialMapResult", cdata => new SparseSpatialMapResult(cdata, easyar_SparseSpatialMapResult__dtor, easyar_SparseSpatialMapResult__retain) },
            { "PlaneData", cdata => new PlaneData(cdata, easyar_PlaneData__dtor, easyar_PlaneData__retain) },
            { "SparseSpatialMapConfig", cdata => new SparseSpatialMapConfig(cdata, easyar_SparseSpatialMapConfig__dtor, easyar_SparseSpatialMapConfig__retain) },
            { "SparseSpatialMap", cdata => new SparseSpatialMap(cdata, easyar_SparseSpatialMap__dtor, easyar_SparseSpatialMap__retain) },
            { "SparseSpatialMapManager", cdata => new SparseSpatialMapManager(cdata, easyar_SparseSpatialMapManager__dtor, easyar_SparseSpatialMapManager__retain) },
            { "ARCoreCameraDevice", cdata => new ARCoreCameraDevice(cdata, easyar_ARCoreCameraDevice__dtor, easyar_ARCoreCameraDevice__retain) },
            { "ARKitCameraDevice", cdata => new ARKitCameraDevice(cdata, easyar_ARKitCameraDevice__dtor, easyar_ARKitCameraDevice__retain) },
            { "CallbackScheduler", cdata => new CallbackScheduler(cdata, easyar_CallbackScheduler__dtor, easyar_CallbackScheduler__retain) },
            { "DelayedCallbackScheduler", cdata => new DelayedCallbackScheduler(cdata, easyar_DelayedCallbackScheduler__dtor, easyar_DelayedCallbackScheduler__retain) },
            { "ImmediateCallbackScheduler", cdata => new ImmediateCallbackScheduler(cdata, easyar_ImmediateCallbackScheduler__dtor, easyar_ImmediateCallbackScheduler__retain) },
            { "CameraDevice", cdata => new CameraDevice(cdata, easyar_CameraDevice__dtor, easyar_CameraDevice__retain) },
            { "SignalSink", cdata => new SignalSink(cdata, easyar_SignalSink__dtor, easyar_SignalSink__retain) },
            { "SignalSource", cdata => new SignalSource(cdata, easyar_SignalSource__dtor, easyar_SignalSource__retain) },
            { "InputFrameSink", cdata => new InputFrameSink(cdata, easyar_InputFrameSink__dtor, easyar_InputFrameSink__retain) },
            { "InputFrameSource", cdata => new InputFrameSource(cdata, easyar_InputFrameSource__dtor, easyar_InputFrameSource__retain) },
            { "OutputFrameSink", cdata => new OutputFrameSink(cdata, easyar_OutputFrameSink__dtor, easyar_OutputFrameSink__retain) },
            { "OutputFrameSource", cdata => new OutputFrameSource(cdata, easyar_OutputFrameSource__dtor, easyar_OutputFrameSource__retain) },
            { "FeedbackFrameSink", cdata => new FeedbackFrameSink(cdata, easyar_FeedbackFrameSink__dtor, easyar_FeedbackFrameSink__retain) },
            { "FeedbackFrameSource", cdata => new FeedbackFrameSource(cdata, easyar_FeedbackFrameSource__dtor, easyar_FeedbackFrameSource__retain) },
            { "InputFrameFork", cdata => new InputFrameFork(cdata, easyar_InputFrameFork__dtor, easyar_InputFrameFork__retain) },
            { "OutputFrameFork", cdata => new OutputFrameFork(cdata, easyar_OutputFrameFork__dtor, easyar_OutputFrameFork__retain) },
            { "OutputFrameJoin", cdata => new OutputFrameJoin(cdata, easyar_OutputFrameJoin__dtor, easyar_OutputFrameJoin__retain) },
            { "FeedbackFrameFork", cdata => new FeedbackFrameFork(cdata, easyar_FeedbackFrameFork__dtor, easyar_FeedbackFrameFork__retain) },
            { "InputFrameThrottler", cdata => new InputFrameThrottler(cdata, easyar_InputFrameThrottler__dtor, easyar_InputFrameThrottler__retain) },
            { "OutputFrameBuffer", cdata => new OutputFrameBuffer(cdata, easyar_OutputFrameBuffer__dtor, easyar_OutputFrameBuffer__retain) },
            { "InputFrameToOutputFrameAdapter", cdata => new InputFrameToOutputFrameAdapter(cdata, easyar_InputFrameToOutputFrameAdapter__dtor, easyar_InputFrameToOutputFrameAdapter__retain) },
            { "InputFrameToFeedbackFrameAdapter", cdata => new InputFrameToFeedbackFrameAdapter(cdata, easyar_InputFrameToFeedbackFrameAdapter__dtor, easyar_InputFrameToFeedbackFrameAdapter__retain) },
            { "InputFrame", cdata => new InputFrame(cdata, easyar_InputFrame__dtor, easyar_InputFrame__retain) },
            { "FrameFilterResult", cdata => new FrameFilterResult(cdata, easyar_FrameFilterResult__dtor, easyar_FrameFilterResult__retain) },
            { "OutputFrame", cdata => new OutputFrame(cdata, easyar_OutputFrame__dtor, easyar_OutputFrame__retain) },
            { "FeedbackFrame", cdata => new FeedbackFrame(cdata, easyar_FeedbackFrame__dtor, easyar_FeedbackFrame__retain) },
            { "Target", cdata => new Target(cdata, easyar_Target__dtor, easyar_Target__retain) },
            { "TargetInstance", cdata => new TargetInstance(cdata, easyar_TargetInstance__dtor, easyar_TargetInstance__retain) },
            { "TargetTrackerResult", cdata => new TargetTrackerResult(cdata, easyar_TargetTrackerResult__dtor, easyar_TargetTrackerResult__retain) },
            { "TextureId", cdata => new TextureId(cdata, easyar_TextureId__dtor, easyar_TextureId__retain) },
            { "VideoPlayer", cdata => new VideoPlayer(cdata, easyar_VideoPlayer__dtor, easyar_VideoPlayer__retain) },
            { "Buffer", cdata => new Buffer(cdata, easyar_Buffer__dtor, easyar_Buffer__retain) },
            { "BufferDictionary", cdata => new BufferDictionary(cdata, easyar_BufferDictionary__dtor, easyar_BufferDictionary__retain) },
            { "BufferPool", cdata => new BufferPool(cdata, easyar_BufferPool__dtor, easyar_BufferPool__retain) },
            { "CameraParameters", cdata => new CameraParameters(cdata, easyar_CameraParameters__dtor, easyar_CameraParameters__retain) },
            { "Image", cdata => new Image(cdata, easyar_Image__dtor, easyar_Image__retain) },
        };

        public class AutoRelease : IDisposable
        {
            private List<Action> actions;

            public void Add(Action deleter)
            {
                if (actions == null) { actions = new List<Action>(); }
                actions.Add(deleter);
            }
            public T Add<T>(T p, Action<T> deleter)
            {
                if (p.Equals(default(T))) { return p; }
                if (actions == null) { actions = new List<Action>(); }
                actions.Add(() => deleter(p));
                return p;
            }

            public void Dispose()
            {
                if (actions != null)
                {
                    foreach (var a in actions)
                    {
                        a();
                    }
                    actions = null;
                }
            }
        }

        public static IntPtr String_to_c(AutoRelease ar, string s)
        {
            if (s == null) { throw new ArgumentNullException(); }
            var bytes = System.Text.Encoding.UTF8.GetBytes(s);
            var handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(bytes, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + bytes.Length);
                var returnValue = IntPtr.Zero;
                easyar_String_from_utf8(beginPtr, endPtr, out returnValue);
                return ar.Add(returnValue, easyar_String__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static IntPtr String_to_c_inner(string s)
        {
            if (s == null) { throw new ArgumentNullException(); }
            var bytes = System.Text.Encoding.UTF8.GetBytes(s);
            var handle = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(bytes, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + bytes.Length);
                var returnValue = IntPtr.Zero;
                easyar_String_from_utf8(beginPtr, endPtr, out returnValue);
                return returnValue;
            }
            finally
            {
                handle.Free();
            }
        }
        public static String String_from_c(AutoRelease ar, IntPtr ptr)
        {
            if (ptr == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(ptr, easyar_String__dtor);
            IntPtr beginPtr = easyar_String_begin(ptr);
            IntPtr endPtr = easyar_String_end(ptr);
            var length = (int)(endPtr.ToInt64() - beginPtr.ToInt64());
            var bytes = new byte[length];
            Marshal.Copy(beginPtr, bytes, 0, length);
            return System.Text.Encoding.UTF8.GetString(bytes);
        }
        public static String String_from_cstring(IntPtr ptr)
        {
            if (ptr == IntPtr.Zero) { throw new ArgumentNullException(); }
            var length = 0;
            while (true)
            {
                var b = Marshal.ReadByte(ptr, length);
                if (b == 0) { break; }
                length += 1;
            }
            var bytes = new byte[length];
            Marshal.Copy(ptr, bytes, 0, length);
            return System.Text.Encoding.UTF8.GetString(bytes);
        }

        public static T Object_from_c<T>(IntPtr ptr, Func<IntPtr, IntPtr> typeNameGetter)
        {
            if (ptr == IntPtr.Zero) { throw new ArgumentNullException(); }
            var typeName = String_from_cstring(typeNameGetter(ptr));
            if (!TypeNameToConstructor.ContainsKey(typeName)) { throw new InvalidOperationException("ConstructorNotExistForType"); }
            var ctor = TypeNameToConstructor[typeName];
            var o = ctor(ptr);
            return (T)(Object)(o);
        }
        public static TValue map<TKey, TValue>(this TKey v, Func<TKey, TValue> f)
        {
            return f(v);
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfBuffer
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoid
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoid.FunctionDelegate))]
#endif
        public static void FunctorOfVoid_func(IntPtr state, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var f = (Action)((GCHandle)(state)).Target;
                    f();
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoid.DestroyDelegate))]
#endif
        public static void FunctorOfVoid_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoid FunctorOfVoid_to_c(Action f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoid { _state = (IntPtr)(s), _func = FunctorOfVoid_func, _destroy = FunctorOfVoid_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfObjectTarget
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        public static IntPtr ListOfObjectTarget_to_c(AutoRelease ar, List<ObjectTarget> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfObjectTarget__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfObjectTarget__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<ObjectTarget> ListOfObjectTarget_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfObjectTarget__dtor);
            var size = easyar_ListOfObjectTarget_size(l);
            var values = new List<ObjectTarget>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfObjectTarget_at(l, k);
                easyar_ObjectTarget__retain(v, out v);
                values.Add(Object_from_c<ObjectTarget>(v, easyar_ObjectTarget__typeName));
            }
            return values;
        }

        public static IntPtr ListOfVec3F_to_c(AutoRelease ar, List<Vec3F> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfVec3F__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfVec3F__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<Vec3F> ListOfVec3F_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfVec3F__dtor);
            var size = easyar_ListOfVec3F_size(l);
            var values = new List<Vec3F>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfVec3F_at(l, k);
                values.Add(v);
            }
            return values;
        }

        public static IntPtr ListOfTargetInstance_to_c(AutoRelease ar, List<TargetInstance> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfTargetInstance__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfTargetInstance__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<TargetInstance> ListOfTargetInstance_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfTargetInstance__dtor);
            var size = easyar_ListOfTargetInstance_size(l);
            var values = new List<TargetInstance>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfTargetInstance_at(l, k);
                easyar_TargetInstance__retain(v, out v);
                values.Add(Object_from_c<TargetInstance>(v, easyar_TargetInstance__typeName));
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfTarget
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfOutputFrame
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        public static IntPtr ListOfOptionalOfFrameFilterResult_to_c(AutoRelease ar, List<Optional<FrameFilterResult>> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.map(p => p.OnSome ? new OptionalOfFrameFilterResult { has_value = true, value = p.Value.cdata } : new OptionalOfFrameFilterResult { has_value = false, value = default(IntPtr) })).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfOptionalOfFrameFilterResult__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfOptionalOfFrameFilterResult__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<Optional<FrameFilterResult>> ListOfOptionalOfFrameFilterResult_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfOptionalOfFrameFilterResult__dtor);
            var size = easyar_ListOfOptionalOfFrameFilterResult_size(l);
            var values = new List<Optional<FrameFilterResult>>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfOptionalOfFrameFilterResult_at(l, k);
                if (v.has_value) { easyar_FrameFilterResult__retain(v.value, out v.value); }
                values.Add(v.map(p => p.has_value ? Object_from_c<FrameFilterResult>(p.value, easyar_FrameFilterResult__typeName) : Optional<FrameFilterResult>.Empty));
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFrameFilterResult
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromOutputFrame
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromOutputFrame value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromOutputFrame
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, IntPtr arg0, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromOutputFrame.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromOutputFrame_func(IntPtr state, IntPtr arg0, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var varg0 = arg0;
                    easyar_OutputFrame__retain(varg0, out varg0);
                    var sarg0 = Object_from_c<OutputFrame>(varg0, easyar_OutputFrame__typeName);
                    ar.Add(() => sarg0.Dispose());
                    var f = (Action<OutputFrame>)((GCHandle)(state)).Target;
                    f(sarg0);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromOutputFrame.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromOutputFrame_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromOutputFrame FunctorOfVoidFromOutputFrame_to_c(Action<OutputFrame> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromOutputFrame { _state = (IntPtr)(s), _func = FunctorOfVoidFromOutputFrame_func, _destroy = FunctorOfVoidFromOutputFrame_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromTargetAndBool
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, IntPtr arg0, bool arg1, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromTargetAndBool.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromTargetAndBool_func(IntPtr state, IntPtr arg0, bool arg1, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var varg0 = arg0;
                    easyar_Target__retain(varg0, out varg0);
                    var sarg0 = Object_from_c<Target>(varg0, easyar_Target__typeName);
                    ar.Add(() => sarg0.Dispose());
                    var sarg1 = arg1;
                    var f = (Action<Target, bool>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromTargetAndBool.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromTargetAndBool_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromTargetAndBool FunctorOfVoidFromTargetAndBool_to_c(Action<Target, bool> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromTargetAndBool { _state = (IntPtr)(s), _func = FunctorOfVoidFromTargetAndBool_func, _destroy = FunctorOfVoidFromTargetAndBool_destroy };
        }

        public static IntPtr ListOfTarget_to_c(AutoRelease ar, List<Target> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfTarget__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfTarget__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<Target> ListOfTarget_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfTarget__dtor);
            var size = easyar_ListOfTarget_size(l);
            var values = new List<Target>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfTarget_at(l, k);
                easyar_Target__retain(v, out v);
                values.Add(Object_from_c<Target>(v, easyar_Target__typeName));
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromCloudStatusAndListOfTarget
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromCloudStatusAndListOfTarget value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromCloudStatusAndListOfTarget
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, CloudStatus arg0, IntPtr arg1, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromCloudStatusAndListOfTarget.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromCloudStatusAndListOfTarget_func(IntPtr state, CloudStatus arg0, IntPtr arg1, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var varg1 = arg1;
                    easyar_ListOfTarget_copy(varg1, out varg1);
                    var sarg1 = ListOfTarget_from_c(ar, varg1);
                    sarg1.ForEach(_v0_ => { ar.Add(() => _v0_.Dispose()); });
                    var f = (Action<CloudStatus, List<Target>>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromCloudStatusAndListOfTarget.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromCloudStatusAndListOfTarget_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromCloudStatusAndListOfTarget FunctorOfVoidFromCloudStatusAndListOfTarget_to_c(Action<CloudStatus, List<Target>> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromCloudStatusAndListOfTarget { _state = (IntPtr)(s), _func = FunctorOfVoidFromCloudStatusAndListOfTarget_func, _destroy = FunctorOfVoidFromCloudStatusAndListOfTarget_destroy };
        }

        public static IntPtr ListOfBlockInfo_to_c(AutoRelease ar, List<BlockInfo> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfBlockInfo__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfBlockInfo__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<BlockInfo> ListOfBlockInfo_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfBlockInfo__dtor);
            var size = easyar_ListOfBlockInfo_size(l);
            var values = new List<BlockInfo>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfBlockInfo_at(l, k);
                values.Add(v);
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromInputFrame
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromInputFrame value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromInputFrame
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, IntPtr arg0, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromInputFrame.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromInputFrame_func(IntPtr state, IntPtr arg0, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var varg0 = arg0;
                    easyar_InputFrame__retain(varg0, out varg0);
                    var sarg0 = Object_from_c<InputFrame>(varg0, easyar_InputFrame__typeName);
                    ar.Add(() => sarg0.Dispose());
                    var f = (Action<InputFrame>)((GCHandle)(state)).Target;
                    f(sarg0);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromInputFrame.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromInputFrame_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromInputFrame FunctorOfVoidFromInputFrame_to_c(Action<InputFrame> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromInputFrame { _state = (IntPtr)(s), _func = FunctorOfVoidFromInputFrame_func, _destroy = FunctorOfVoidFromInputFrame_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfImageTarget
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        public static IntPtr ListOfImageTarget_to_c(AutoRelease ar, List<ImageTarget> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfImageTarget__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfImageTarget__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<ImageTarget> ListOfImageTarget_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfImageTarget__dtor);
            var size = easyar_ListOfImageTarget_size(l);
            var values = new List<ImageTarget>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfImageTarget_at(l, k);
                easyar_ImageTarget__retain(v, out v);
                values.Add(Object_from_c<ImageTarget>(v, easyar_ImageTarget__typeName));
            }
            return values;
        }

        public static IntPtr ListOfImage_to_c(AutoRelease ar, List<Image> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfImage__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfImage__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<Image> ListOfImage_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfImage__dtor);
            var size = easyar_ListOfImage_size(l);
            var values = new List<Image>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfImage_at(l, k);
                easyar_Image__retain(v, out v);
                values.Add(Object_from_c<Image>(v, easyar_Image__typeName));
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromPermissionStatusAndString
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromPermissionStatusAndString value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromPermissionStatusAndString
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, PermissionStatus arg0, IntPtr arg1, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromPermissionStatusAndString.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromPermissionStatusAndString_func(IntPtr state, PermissionStatus arg0, IntPtr arg1, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var varg1 = arg1;
                    easyar_String_copy(varg1, out varg1);
                    var sarg1 = String_from_c(ar, varg1);
                    var f = (Action<PermissionStatus, string>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromPermissionStatusAndString.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromPermissionStatusAndString_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromPermissionStatusAndString FunctorOfVoidFromPermissionStatusAndString_to_c(Action<PermissionStatus, string> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromPermissionStatusAndString { _state = (IntPtr)(s), _func = FunctorOfVoidFromPermissionStatusAndString_func, _destroy = FunctorOfVoidFromPermissionStatusAndString_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromRecordStatusAndString
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromRecordStatusAndString value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromRecordStatusAndString
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, RecordStatus arg0, IntPtr arg1, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromRecordStatusAndString.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromRecordStatusAndString_func(IntPtr state, RecordStatus arg0, IntPtr arg1, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var varg1 = arg1;
                    easyar_String_copy(varg1, out varg1);
                    var sarg1 = String_from_c(ar, varg1);
                    var f = (Action<RecordStatus, string>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromRecordStatusAndString.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromRecordStatusAndString_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromRecordStatusAndString FunctorOfVoidFromRecordStatusAndString_to_c(Action<RecordStatus, string> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromRecordStatusAndString { _state = (IntPtr)(s), _func = FunctorOfVoidFromRecordStatusAndString_func, _destroy = FunctorOfVoidFromRecordStatusAndString_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfMatrix44F
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public Matrix44F value;
        }

        public static IntPtr ListOfPlaneData_to_c(AutoRelease ar, List<PlaneData> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfPlaneData__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfPlaneData__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<PlaneData> ListOfPlaneData_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfPlaneData__dtor);
            var size = easyar_ListOfPlaneData_size(l);
            var values = new List<PlaneData>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfPlaneData_at(l, k);
                easyar_PlaneData__retain(v, out v);
                values.Add(Object_from_c<PlaneData>(v, easyar_PlaneData__typeName));
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromBool
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromBool value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromBool
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, bool arg0, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromBool.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromBool_func(IntPtr state, bool arg0, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var f = (Action<bool>)((GCHandle)(state)).Target;
                    f(sarg0);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromBool.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromBool_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromBool FunctorOfVoidFromBool_to_c(Action<bool> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromBool { _state = (IntPtr)(s), _func = FunctorOfVoidFromBool_func, _destroy = FunctorOfVoidFromBool_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfImage
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public IntPtr value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromBoolAndStringAndString
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, bool arg0, IntPtr arg1, IntPtr arg2, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromBoolAndStringAndString.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromBoolAndStringAndString_func(IntPtr state, bool arg0, IntPtr arg1, IntPtr arg2, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var varg1 = arg1;
                    easyar_String_copy(varg1, out varg1);
                    var sarg1 = String_from_c(ar, varg1);
                    var varg2 = arg2;
                    easyar_String_copy(varg2, out varg2);
                    var sarg2 = String_from_c(ar, varg2);
                    var f = (Action<bool, string, string>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1, sarg2);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromBoolAndStringAndString.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromBoolAndStringAndString_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromBoolAndStringAndString FunctorOfVoidFromBoolAndStringAndString_to_c(Action<bool, string, string> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromBoolAndStringAndString { _state = (IntPtr)(s), _func = FunctorOfVoidFromBoolAndStringAndString_func, _destroy = FunctorOfVoidFromBoolAndStringAndString_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromBoolAndString
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, bool arg0, IntPtr arg1, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromBoolAndString.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromBoolAndString_func(IntPtr state, bool arg0, IntPtr arg1, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var varg1 = arg1;
                    easyar_String_copy(varg1, out varg1);
                    var sarg1 = String_from_c(ar, varg1);
                    var f = (Action<bool, string>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromBoolAndString.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromBoolAndString_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromBoolAndString FunctorOfVoidFromBoolAndString_to_c(Action<bool, string> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromBoolAndString { _state = (IntPtr)(s), _func = FunctorOfVoidFromBoolAndString_func, _destroy = FunctorOfVoidFromBoolAndString_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromCameraState
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromCameraState value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromCameraState
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, CameraState arg0, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromCameraState.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromCameraState_func(IntPtr state, CameraState arg0, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var f = (Action<CameraState>)((GCHandle)(state)).Target;
                    f(sarg0);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromCameraState.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromCameraState_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromCameraState FunctorOfVoidFromCameraState_to_c(Action<CameraState> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromCameraState { _state = (IntPtr)(s), _func = FunctorOfVoidFromCameraState_func, _destroy = FunctorOfVoidFromCameraState_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoid
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoid value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromFeedbackFrame
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromFeedbackFrame value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromFeedbackFrame
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, IntPtr arg0, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromFeedbackFrame.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromFeedbackFrame_func(IntPtr state, IntPtr arg0, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var varg0 = arg0;
                    easyar_FeedbackFrame__retain(varg0, out varg0);
                    var sarg0 = Object_from_c<FeedbackFrame>(varg0, easyar_FeedbackFrame__typeName);
                    ar.Add(() => sarg0.Dispose());
                    var f = (Action<FeedbackFrame>)((GCHandle)(state)).Target;
                    f(sarg0);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromFeedbackFrame.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromFeedbackFrame_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromFeedbackFrame FunctorOfVoidFromFeedbackFrame_to_c(Action<FeedbackFrame> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromFeedbackFrame { _state = (IntPtr)(s), _func = FunctorOfVoidFromFeedbackFrame_func, _destroy = FunctorOfVoidFromFeedbackFrame_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfOutputFrameFromListOfOutputFrame
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, IntPtr arg0, out IntPtr Return, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfOutputFrameFromListOfOutputFrame.FunctionDelegate))]
#endif
        public static void FunctorOfOutputFrameFromListOfOutputFrame_func(IntPtr state, IntPtr arg0, out IntPtr Return, out IntPtr exception)
        {
            Return = default(IntPtr);
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var varg0 = arg0;
                    easyar_ListOfOutputFrame_copy(varg0, out varg0);
                    var sarg0 = ListOfOutputFrame_from_c(ar, varg0);
                    sarg0.ForEach(_v0_ => { ar.Add(() => _v0_.Dispose()); });
                    var f = (Func<List<OutputFrame>, OutputFrame>)((GCHandle)(state)).Target;
                    var _return_value_ = f(sarg0);
                    var _return_value_c_ = _return_value_.cdata;
                    Return = _return_value_c_;
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfOutputFrameFromListOfOutputFrame.DestroyDelegate))]
#endif
        public static void FunctorOfOutputFrameFromListOfOutputFrame_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfOutputFrameFromListOfOutputFrame FunctorOfOutputFrameFromListOfOutputFrame_to_c(Func<List<OutputFrame>, OutputFrame> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfOutputFrameFromListOfOutputFrame { _state = (IntPtr)(s), _func = FunctorOfOutputFrameFromListOfOutputFrame_func, _destroy = FunctorOfOutputFrameFromListOfOutputFrame_destroy };
        }

        public static IntPtr ListOfOutputFrame_to_c(AutoRelease ar, List<OutputFrame> l)
        {
            if (l == null) { throw new ArgumentNullException(); }
            var arr = l.Select(e => e.cdata).ToArray();
            var handle = GCHandle.Alloc(arr, GCHandleType.Pinned);
            try
            {
                var beginPtr = Marshal.UnsafeAddrOfPinnedArrayElement(arr, 0);
                var endPtr = new IntPtr(beginPtr.ToInt64() + IntPtr.Size * arr.Length);
                var ptr = IntPtr.Zero;
                easyar_ListOfOutputFrame__ctor(beginPtr, endPtr, out ptr);
                return ar.Add(ptr, easyar_ListOfOutputFrame__dtor);
            }
            finally
            {
                handle.Free();
            }
        }
        public static List<OutputFrame> ListOfOutputFrame_from_c(AutoRelease ar, IntPtr l)
        {
            if (l == IntPtr.Zero) { throw new ArgumentNullException(); }
            ar.Add(l, easyar_ListOfOutputFrame__dtor);
            var size = easyar_ListOfOutputFrame_size(l);
            var values = new List<OutputFrame>();
            values.Capacity = size;
            for (int k = 0; k < size; k += 1)
            {
                var v = easyar_ListOfOutputFrame_at(l, k);
                easyar_OutputFrame__retain(v, out v);
                values.Add(Object_from_c<OutputFrame>(v, easyar_OutputFrame__typeName));
            }
            return values;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OptionalOfFunctorOfVoidFromVideoStatus
        {
            private Byte has_value_;
            public bool has_value { get { return has_value_ != 0; } set { has_value_ = (Byte)(value ? 1 : 0); } }
            public FunctorOfVoidFromVideoStatus value;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromVideoStatus
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, VideoStatus arg0, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromVideoStatus.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromVideoStatus_func(IntPtr state, VideoStatus arg0, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var f = (Action<VideoStatus>)((GCHandle)(state)).Target;
                    f(sarg0);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromVideoStatus.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromVideoStatus_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromVideoStatus FunctorOfVoidFromVideoStatus_to_c(Action<VideoStatus> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromVideoStatus { _state = (IntPtr)(s), _func = FunctorOfVoidFromVideoStatus_func, _destroy = FunctorOfVoidFromVideoStatus_destroy };
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct FunctorOfVoidFromLogLevelAndString
        {
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void FunctionDelegate(IntPtr state, LogLevel arg0, IntPtr arg1, out IntPtr exception);
            [UnmanagedFunctionPointer(CallingConvention.Cdecl)] public delegate void DestroyDelegate(IntPtr _state);

            public IntPtr _state;
            public FunctionDelegate _func;
            public DestroyDelegate _destroy;
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromLogLevelAndString.FunctionDelegate))]
#endif
        public static void FunctorOfVoidFromLogLevelAndString_func(IntPtr state, LogLevel arg0, IntPtr arg1, out IntPtr exception)
        {
            exception = IntPtr.Zero;
            try
            {
                using (var ar = new AutoRelease())
                {
                    var sarg0 = arg0;
                    var varg1 = arg1;
                    easyar_String_copy(varg1, out varg1);
                    var sarg1 = String_from_c(ar, varg1);
                    var f = (Action<LogLevel, string>)((GCHandle)(state)).Target;
                    f(sarg0, sarg1);
                }
            }
            catch (Exception ex)
            {
                exception = Detail.String_to_c_inner(ex.ToString());
            }
        }
#if ENABLE_IL2CPP
        [MonoPInvokeCallback(typeof(FunctorOfVoidFromLogLevelAndString.DestroyDelegate))]
#endif
        public static void FunctorOfVoidFromLogLevelAndString_destroy(IntPtr _state)
        {
            ((GCHandle)(_state)).Free();
        }
        public static FunctorOfVoidFromLogLevelAndString FunctorOfVoidFromLogLevelAndString_to_c(Action<LogLevel, string> f)
        {
            if (f == null) { throw new ArgumentNullException(); }
            var s = GCHandle.Alloc(f, GCHandleType.Normal);
            return new FunctorOfVoidFromLogLevelAndString { _state = (IntPtr)(s), _func = FunctorOfVoidFromLogLevelAndString_func, _destroy = FunctorOfVoidFromLogLevelAndString_destroy };
        }

    }

    ///<summary>
    ///ObjectTargetParameters represents the parameters to create a `ObjectTarget`_ .
    ///</summary>
    public class ObjectTargetParameters : RefBase
    {
        internal ObjectTargetParameters(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ObjectTargetParameters(cdata_new, deleter_, retainer_);
        }
        public new ObjectTargetParameters Clone()
        {
            return (ObjectTargetParameters)(CloneObject());
        }
        public ObjectTargetParameters() : base(IntPtr.Zero, Detail.easyar_ObjectTargetParameters__dtor, Detail.easyar_ObjectTargetParameters__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_ObjectTargetParameters__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Gets `Buffer`_ dictionary.
        ///</summary>
        public virtual BufferDictionary bufferDictionary()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTargetParameters_bufferDictionary(cdata, out _return_value_);
                return Detail.Object_from_c<BufferDictionary>(_return_value_, Detail.easyar_BufferDictionary__typeName);
            }
        }
        ///<summary>
        ///Sets `Buffer`_ dictionary. obj, mtl and jpg/png files shall be loaded into the dictionay, and be able to be located by relative or absolute paths.
        ///</summary>
        public virtual void setBufferDictionary(BufferDictionary bufferDictionary)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTargetParameters_setBufferDictionary(cdata, bufferDictionary.cdata);
            }
        }
        ///<summary>
        ///Gets obj file path.
        ///</summary>
        public virtual string objPath()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTargetParameters_objPath(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets obj file path.
        ///</summary>
        public virtual void setObjPath(string objPath)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTargetParameters_setObjPath(cdata, Detail.String_to_c(ar, objPath));
            }
        }
        ///<summary>
        ///Gets target name. It can be used to distinguish targets.
        ///</summary>
        public virtual string name()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTargetParameters_name(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets target name.
        ///</summary>
        public virtual void setName(string name)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTargetParameters_setName(cdata, Detail.String_to_c(ar, name));
            }
        }
        ///<summary>
        ///Gets the target uid. You can set this uid in the json config as a method to distinguish from targets.
        ///</summary>
        public virtual string uid()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTargetParameters_uid(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets target uid.
        ///</summary>
        public virtual void setUid(string uid)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTargetParameters_setUid(cdata, Detail.String_to_c(ar, uid));
            }
        }
        ///<summary>
        ///Gets meta data.
        ///</summary>
        public virtual string meta()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTargetParameters_meta(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets meta data。
        ///</summary>
        public virtual void setMeta(string meta)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTargetParameters_setMeta(cdata, Detail.String_to_c(ar, meta));
            }
        }
        ///<summary>
        ///Gets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
        ///</summary>
        public virtual float scale()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTargetParameters_scale(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets the scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
        ///It is needed to set the model scale in rendering engine separately.
        ///</summary>
        public virtual void setScale(float size)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTargetParameters_setScale(cdata, size);
            }
        }
    }

    ///<summary>
    ///ObjectTarget represents 3d object targets that can be tracked by `ObjectTracker`_ .
    ///The size of ObjectTarget is determined by the `obj` file. You can change it by changing the object `scale`, which is default to 1.
    ///A ObjectTarget should be setup using setup before any value is valid. And ObjectTarget can be tracked by `ObjectTracker`_ after a successful load into the `ObjectTracker`_ using `ObjectTracker.loadTarget`_ .
    ///</summary>
    public class ObjectTarget : Target
    {
        internal ObjectTarget(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ObjectTarget(cdata_new, deleter_, retainer_);
        }
        public new ObjectTarget Clone()
        {
            return (ObjectTarget)(CloneObject());
        }
        public ObjectTarget() : base(IntPtr.Zero, Detail.easyar_ObjectTarget__dtor, Detail.easyar_ObjectTarget__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_ObjectTarget__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Creates a target from parameters.
        ///</summary>
        public static Optional<ObjectTarget> createFromParameters(ObjectTargetParameters parameters)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfObjectTarget);
                Detail.easyar_ObjectTarget_createFromParameters(parameters.cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<ObjectTarget>(p.value, Detail.easyar_ObjectTarget__typeName) : Optional<ObjectTarget>.Empty);
            }
        }
        ///<summary>
        ///Creats a target from obj, mtl and jpg/png files.
        ///</summary>
        public static Optional<ObjectTarget> createFromObjectFile(string path, StorageType storageType, string name, string uid, string meta, float scale)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfObjectTarget);
                Detail.easyar_ObjectTarget_createFromObjectFile(Detail.String_to_c(ar, path), storageType, Detail.String_to_c(ar, name), Detail.String_to_c(ar, uid), Detail.String_to_c(ar, meta), scale, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<ObjectTarget>(p.value, Detail.easyar_ObjectTarget__typeName) : Optional<ObjectTarget>.Empty);
            }
        }
        ///<summary>
        ///Setup all targets listed in the json file or json string from path with storageType. This method only parses the json file or string.
        ///If path is json file path, storageType should be `App` or `Assets` or `Absolute` indicating the path type. Paths inside json files should be absolute path or relative path to the json file.
        ///See `StorageType`_ for more descriptions.
        ///</summary>
        public static List<ObjectTarget> setupAll(string path, StorageType storageType)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTarget_setupAll(Detail.String_to_c(ar, path), storageType, out _return_value_);
                return Detail.ListOfObjectTarget_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///The scale of model. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
        ///</summary>
        public virtual float scale()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTarget_scale(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///The bounding box of object, it contains the 8 points of the box.
        ///Vertices's indices are defined and stored following the rule:
        ///::
        ///
        ///      4-----7
        ///     /|    /|
        ///    5-----6 |    z
        ///    | |   | |    |
        ///    | 0---|-3    o---y
        ///    |/    |/    /
        ///    1-----2    x
        ///</summary>
        public virtual List<Vec3F> boundingBox()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTarget_boundingBox(cdata, out _return_value_);
                return Detail.ListOfVec3F_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets model target scale, this will overwrite the value set in the json file or the default value. The value is the physical scale divided by model coordinate system scale. The default value is 1. (Supposing the unit of model coordinate system is 1 meter.)
        ///It is needed to set the model scale in rendering engine separately.
        ///It also should been done before loading ObjectTarget into  `ObjectTracker`_ using `ObjectTracker.loadTarget`_.
        ///</summary>
        public virtual bool setScale(float scale)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTarget_setScale(cdata, scale);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
        ///</summary>
        public override int runtimeID()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTarget_runtimeID(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
        ///</summary>
        public override string uid()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTarget_uid(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Returns the target name. Name is used to distinguish targets in a json file.
        ///</summary>
        public override string name()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTarget_name(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Set name. It will erase previously set data or data from cloud.
        ///</summary>
        public override void setName(string name)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTarget_setName(cdata, Detail.String_to_c(ar, name));
            }
        }
        ///<summary>
        ///Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
        ///</summary>
        public override string meta()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTarget_meta(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Set meta data. It will erase previously set data or data from cloud.
        ///</summary>
        public override void setMeta(string data)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTarget_setMeta(cdata, Detail.String_to_c(ar, data));
            }
        }
    }

    ///<summary>
    ///Result of `ObjectTracker`_ .
    ///</summary>
    public class ObjectTrackerResult : TargetTrackerResult
    {
        internal ObjectTrackerResult(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ObjectTrackerResult(cdata_new, deleter_, retainer_);
        }
        public new ObjectTrackerResult Clone()
        {
            return (ObjectTrackerResult)(CloneObject());
        }
        ///<summary>
        ///Returns the list of `TargetInstance`_ contained in the result.
        ///</summary>
        public override List<TargetInstance> targetInstances()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTrackerResult_targetInstances(cdata, out _return_value_);
                return Detail.ListOfTargetInstance_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets the list of `TargetInstance`_ contained in the result.
        ///</summary>
        public override void setTargetInstances(List<TargetInstance> instances)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTrackerResult_setTargetInstances(cdata, Detail.ListOfTargetInstance_to_c(ar, instances));
            }
        }
    }

    ///<summary>
    ///ObjectTracker implements 3D object target detection and tracking.
    ///ObjectTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///ObjectTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview <Overview.html>`_ .
    ///Before a `Target`_ can be tracked by ObjectTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
    ///</summary>
    public class ObjectTracker : RefBase
    {
        internal ObjectTracker(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ObjectTracker(cdata_new, deleter_, retainer_);
        }
        public new ObjectTracker Clone()
        {
            return (ObjectTracker)(CloneObject());
        }
        ///<summary>
        ///Returns true.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTracker_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///`FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
        ///</summary>
        public virtual FeedbackFrameSink feedbackFrameSink()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTracker_feedbackFrameSink(cdata, out _return_value_);
                return Detail.Object_from_c<FeedbackFrameSink>(_return_value_, Detail.easyar_FeedbackFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTracker_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///`OutputFrame`_ output port.
        ///</summary>
        public virtual OutputFrameSource outputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTracker_outputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static ObjectTracker create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTracker_create(out _return_value_);
                return Detail.Object_from_c<ObjectTracker>(_return_value_, Detail.easyar_ObjectTracker__typeName);
            }
        }
        ///<summary>
        ///Starts the track algorithm.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTracker_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops the track algorithm. Call start to start the track again.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTracker_stop(cdata);
            }
        }
        ///<summary>
        ///Close. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTracker_close(cdata);
            }
        }
        ///<summary>
        ///Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
        ///This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
        ///</summary>
        public virtual void loadTarget(Target target, CallbackScheduler callbackScheduler, Action<Target, bool> callback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTracker_loadTarget(cdata, target.cdata, callbackScheduler.cdata, Detail.FunctorOfVoidFromTargetAndBool_to_c(callback));
            }
        }
        ///<summary>
        ///Unload a `Target`_ from the tracker.
        ///This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
        ///</summary>
        public virtual void unloadTarget(Target target, CallbackScheduler callbackScheduler, Action<Target, bool> callback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ObjectTracker_unloadTarget(cdata, target.cdata, callbackScheduler.cdata, Detail.FunctorOfVoidFromTargetAndBool_to_c(callback));
            }
        }
        ///<summary>
        ///Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
        ///</summary>
        public virtual List<Target> targets()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ObjectTracker_targets(cdata, out _return_value_);
                return Detail.ListOfTarget_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
        ///</summary>
        public virtual bool setSimultaneousNum(int num)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTracker_setSimultaneousNum(cdata, num);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
        ///</summary>
        public virtual int simultaneousNum()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ObjectTracker_simultaneousNum(cdata);
                return _return_value_;
            }
        }
    }

    public enum CloudStatus
    {
        ///<summary>
        ///Targets are recognized.
        ///</summary>
        FoundTargets = 0,
        ///<summary>
        ///No targets are recognized.
        ///</summary>
        TargetsNotFound = 1,
        ///<summary>
        ///Connection broke and auto reconnecting
        ///</summary>
        Reconnecting = 2,
        ///<summary>
        ///Protocol error
        ///</summary>
        ProtocolError = 3,
    }

    ///<summary>
    ///CloudRecognizer implements cloud recognition. It can only be used after created a recognition image library on the cloud. Please refer to EasyAR CRS documentation.
    ///CloudRecognizer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///After creation, you can call start/stop to enable/disable running.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///CloudRecognizer inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview <Overview.html>`_ .
    ///Before using a CloudRecognizer, an `ImageTracker`_ must be setup and prepared. Any target returned from cloud should be manually put into the `ImageTracker`_ using `ImageTracker.loadTarget`_ if it need to be tracked. Then the target can be used as same as a local target after loaded into the tracker. When a target is recognized, you can get it from callback, and you should use target uid to distinguish different targets. The target runtimeID is dynamically created and cannot be used as unique identifier in the cloud situation.
    ///</summary>
    public class CloudRecognizer : RefBase
    {
        internal CloudRecognizer(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new CloudRecognizer(cdata_new, deleter_, retainer_);
        }
        public new CloudRecognizer Clone()
        {
            return (CloudRecognizer)(CloneObject());
        }
        ///<summary>
        ///Returns true.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CloudRecognizer_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///`InputFrame`_ input port. Raw image and timestamp are essential.
        ///</summary>
        public virtual InputFrameSink inputFrameSink()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_CloudRecognizer_inputFrameSink(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CloudRecognizer_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance and connects to the server.
        ///</summary>
        public static CloudRecognizer create(string cloudRecognitionServiceServerAddress, string apiKey, string apiSecret, string cloudRecognitionServiceAppId, CallbackScheduler callbackScheduler, Optional<Action<CloudStatus, List<Target>>> callback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_CloudRecognizer_create(Detail.String_to_c(ar, cloudRecognitionServiceServerAddress), Detail.String_to_c(ar, apiKey), Detail.String_to_c(ar, apiSecret), Detail.String_to_c(ar, cloudRecognitionServiceAppId), callbackScheduler.cdata, callback.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromCloudStatusAndListOfTarget { has_value = true, value = Detail.FunctorOfVoidFromCloudStatusAndListOfTarget_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromCloudStatusAndListOfTarget { has_value = false, value = default(Detail.FunctorOfVoidFromCloudStatusAndListOfTarget) }), out _return_value_);
                return Detail.Object_from_c<CloudRecognizer>(_return_value_, Detail.easyar_CloudRecognizer__typeName);
            }
        }
        ///<summary>
        ///Starts the recognition.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CloudRecognizer_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops the recognition.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CloudRecognizer_stop(cdata);
            }
        }
        ///<summary>
        ///Stops the recognition and closes connection. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CloudRecognizer_close(cdata);
            }
        }
    }

    ///<summary>
    ///DenseSpatialMap is used to reconstruct the environment accurately and densely. The reconstructed model is represented by `triangle mesh`, which is denoted simply by `mesh`.
    ///DenseSpatialMap occupies 1 buffers of camera.
    ///</summary>
    public class DenseSpatialMap : RefBase
    {
        internal DenseSpatialMap(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new DenseSpatialMap(cdata_new, deleter_, retainer_);
        }
        public new DenseSpatialMap Clone()
        {
            return (DenseSpatialMap)(CloneObject());
        }
        ///<summary>
        ///Returns True when the device supports dense reconstruction, otherwise returns False.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_DenseSpatialMap_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Input port for input frame. For DenseSpatialMap to work, the inputFrame must include image and it's camera parameters and spatial information (cameraTransform and trackingStatus). See also `InputFrameSink`_ .
        ///</summary>
        public virtual InputFrameSink inputFrameSink()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_DenseSpatialMap_inputFrameSink(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_DenseSpatialMap_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Create `DenseSpatialMap`_ object.
        ///</summary>
        public static DenseSpatialMap create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_DenseSpatialMap_create(out _return_value_);
                return Detail.Object_from_c<DenseSpatialMap>(_return_value_, Detail.easyar_DenseSpatialMap__typeName);
            }
        }
        ///<summary>
        ///Start or continue runninng `DenseSpatialMap`_ algorithm.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_DenseSpatialMap_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Pause the reconstruction algorithm. Call `start` to resume reconstruction.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_DenseSpatialMap_stop(cdata);
            }
        }
        ///<summary>
        ///Close `DenseSpatialMap`_ algorithm.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_DenseSpatialMap_close(cdata);
            }
        }
        ///<summary>
        ///Get the mesh management object of type `SceneMesh`_ . The contents will automatically update after calling the `DenseSpatialMap.updateSceneMesh`_ function.
        ///</summary>
        public virtual SceneMesh getMesh()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_DenseSpatialMap_getMesh(cdata, out _return_value_);
                return Detail.Object_from_c<SceneMesh>(_return_value_, Detail.easyar_SceneMesh__typeName);
            }
        }
        ///<summary>
        ///Get the lastest updated mesh and save it to the `SceneMesh`_ object obtained by `DenseSpatialMap.getMesh`_ .
        ///The parameter `updateMeshAll` indicates whether to perform a `full update` or an `incremental update`. When `updateMeshAll` is True, `full update` is performed. All meshes are saved to `SceneMesh`_ . When `updateMeshAll` is False, `incremental update` is performed, and only the most recently updated mesh is saved to `SceneMesh`_ .
        ///`Full update` will take extra time and memory space, causing performance degradation.
        ///</summary>
        public virtual bool updateSceneMesh(bool updateMeshAll)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_DenseSpatialMap_updateSceneMesh(cdata, updateMeshAll);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///The dense reconstructed model is represented by triangle mesh, or simply denoted as mesh. Because mesh updates frequently, in order to ensure efficiency, the mesh of the whole reconstruction model is divided into many mesh blocks. A mesh block is composed of a cube about 1 meter long, with attributes such as vertices and indices.
    ///
    ///BlockInfo is used to describe the content of a mesh block. (x, y, z) is the index of mesh block, the coordinates of a mesh block's origin in world coordinate system can be obtained by  multiplying (x, y, z) by the physical size of mesh block. You may filter the part you want to display in advance by the mesh block's world coordinates for the sake of saving rendering time.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct BlockInfo
    {
        ///<summary>
        ///x in index (x, y, z) of mesh block.
        ///</summary>
        public int x;
        ///<summary>
        ///y in index (x, y, z) of mesh block.
        ///</summary>
        public int y;
        ///<summary>
        ///z in index (x, y, z) of mesh block.
        ///</summary>
        public int z;
        ///<summary>
        ///Number of vertices in a mesh block.
        ///</summary>
        public int numOfVertex;
        ///<summary>
        ///startPointOfVertex is the starting position of the vertex data stored in the vertex buffer, indicating from where the stored vertices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of vertex buffer. The offset is startPointOfVertex*3*4 bytes.
        ///</summary>
        public int startPointOfVertex;
        ///<summary>
        ///The number of indices in a mesh block. Each of three consecutive vertices form a triangle.
        ///</summary>
        public int numOfIndex;
        ///<summary>
        ///Similar to startPointOfVertex. startPointOfIndex is the starting position of the index data stored in the index buffer, indicating from where the stored indices belong to current mesh block. It is not equal to the number of bytes of the offset from the beginning of index buffer. The offset is startPointOfIndex*3*4 bytes.
        ///</summary>
        public int startPointOfIndex;
        ///<summary>
        ///Version represents how many times the mesh block has updated. The larger the version, the newer the block. If the version of a mesh block increases after calling `DenseSpatialMap.updateSceneMesh`_ , it indicates that the mash block has changed.
        ///</summary>
        public int version;

        public BlockInfo(int x, int y, int z, int numOfVertex, int startPointOfVertex, int numOfIndex, int startPointOfIndex, int version)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.numOfVertex = numOfVertex;
            this.startPointOfVertex = startPointOfVertex;
            this.numOfIndex = numOfIndex;
            this.startPointOfIndex = startPointOfIndex;
            this.version = version;
        }
    }

    ///<summary>
    ///SceneMesh is used to manage and preserve the results of `DenseSpatialMap`_.
    ///There are two kinds of meshes saved in SceneMesh, one is the mesh of the whole reconstructed scene, hereinafter referred to as `meshAll`, the other is the recently updated mesh, hereinafter referred to as `meshUpdated`. `meshAll` is a whole mesh, including all vertex data and index data, etc. `meshUpdated` is composed of several `mesh block` s, each `mesh block` is a cube, which contains the mesh formed by the object surface in the corresponding cube space.
    ///`meshAll` is available only when the `DenseSpatialMap.updateSceneMesh`_ method is called specifying that all meshes need to be updated. If `meshAll` has been updated previously and not updated in recent times, the data in `meshAll` is remain the same.
    ///</summary>
    public class SceneMesh : RefBase
    {
        internal SceneMesh(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SceneMesh(cdata_new, deleter_, retainer_);
        }
        public new SceneMesh Clone()
        {
            return (SceneMesh)(CloneObject());
        }
        ///<summary>
        ///Get the number of vertices in `meshAll`.
        ///</summary>
        public virtual int getNumOfVertexAll()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SceneMesh_getNumOfVertexAll(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Get the number of indices in `meshAll`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
        ///</summary>
        public virtual int getNumOfIndexAll()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SceneMesh_getNumOfIndexAll(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Get the position component of the vertices in `meshAll` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
        ///</summary>
        public virtual Buffer getVerticesAll()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getVerticesAll(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Get the normal component of vertices in `meshAll`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
        ///</summary>
        public virtual Buffer getNormalsAll()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getNormalsAll(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Get the index data in `meshAll`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
        ///</summary>
        public virtual Buffer getIndicesAll()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getIndicesAll(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Get the number of vertices in `meshUpdated`.
        ///</summary>
        public virtual int getNumOfVertexIncremental()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SceneMesh_getNumOfVertexIncremental(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Get the number of indices in `meshUpdated`. Since every 3 indices form a triangle, the returned value should be a multiple of 3.
        ///</summary>
        public virtual int getNumOfIndexIncremental()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SceneMesh_getNumOfIndexIncremental(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Get the position component of the vertices in `meshUpdated` (in the world coordinate system). The position of a vertex is described by three coordinates (x, y, z) in meters. The position data are stored tightly in `Buffer`_ by `x1, y1, z1, x2, y2, z2, ...` Each component is of `float` type.
        ///</summary>
        public virtual Buffer getVerticesIncremental()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getVerticesIncremental(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Get the normal component of vertices in `meshUpdated`. The normal of a vertex is described by three components (nx, ny, nz). The normal is normalized, that is, the length is 1. Normal data are stored tightly in `Buffer`_ by `nx1, ny1, nz1, nx2, ny2, nz2,....` Each component is of `float` type.
        ///</summary>
        public virtual Buffer getNormalsIncremental()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getNormalsIncremental(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Get the index data in `meshUpdated`. Each triangle is composed of three indices (ix, iy, iz). Indices are stored tightly in `Buffer`_ by `ix1, iy1, iz1, ix2, iy2, iz2,...` Each component is of `int32` type.
        ///</summary>
        public virtual Buffer getIndicesIncremental()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getIndicesIncremental(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Gets the description object of `mesh block` in `meshUpdate`. The return value is an array of `BlockInfo`_ elements, each of which is a detailed description of a `mesh block`.
        ///</summary>
        public virtual List<BlockInfo> getBlocksInfoIncremental()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SceneMesh_getBlocksInfoIncremental(cdata, out _return_value_);
                return Detail.ListOfBlockInfo_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Get the edge length of a `mesh block` in meters.
        ///</summary>
        public virtual float getBlockDimensionInMeters()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SceneMesh_getBlockDimensionInMeters(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///Result of `SurfaceTracker`_ .
    ///</summary>
    public class SurfaceTrackerResult : FrameFilterResult
    {
        internal SurfaceTrackerResult(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SurfaceTrackerResult(cdata_new, deleter_, retainer_);
        }
        public new SurfaceTrackerResult Clone()
        {
            return (SurfaceTrackerResult)(CloneObject());
        }
        ///<summary>
        ///Camera transform against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) For the world coordinate system, y is up (to the opposite of gravity). The data arrangement is row-major, not like OpenGL's column-major.
        ///</summary>
        public virtual Matrix44F transform()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SurfaceTrackerResult_transform(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///SurfaceTracker implements tracking with environmental surfaces.
    ///SurfaceTracker occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///SurfaceTracker inputs `InputFrame`_ from inputFrameSink. `InputFrameSource`_ shall be connected to inputFrameSink for use. Refer to `Overview <Overview.html>`_ .
    ///</summary>
    public class SurfaceTracker : RefBase
    {
        internal SurfaceTracker(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SurfaceTracker(cdata_new, deleter_, retainer_);
        }
        public new SurfaceTracker Clone()
        {
            return (SurfaceTracker)(CloneObject());
        }
        ///<summary>
        ///Returns true only on Android or iOS when accelerometer and gyroscope are available.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SurfaceTracker_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///`InputFrame`_ input port. InputFrame must have raw image, timestamp, and camera parameters.
        ///</summary>
        public virtual InputFrameSink inputFrameSink()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SurfaceTracker_inputFrameSink(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SurfaceTracker_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///`OutputFrame`_ output port.
        ///</summary>
        public virtual OutputFrameSource outputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SurfaceTracker_outputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static SurfaceTracker create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SurfaceTracker_create(out _return_value_);
                return Detail.Object_from_c<SurfaceTracker>(_return_value_, Detail.easyar_SurfaceTracker__typeName);
            }
        }
        ///<summary>
        ///Starts the track algorithm.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SurfaceTracker_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops the track algorithm. Call start to start the track again.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SurfaceTracker_stop(cdata);
            }
        }
        ///<summary>
        ///Close. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SurfaceTracker_close(cdata);
            }
        }
        ///<summary>
        ///Sets the tracking target to a point on camera image. For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
        ///</summary>
        public virtual void alignTargetToCameraImagePoint(Vec2F cameraImagePoint)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SurfaceTracker_alignTargetToCameraImagePoint(cdata, cameraImagePoint);
            }
        }
    }

    ///<summary>
    ///MotionTrackerCameraDevice implements a camera device with metric-scale six degree-of-freedom motion tracking, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF pose and tracking status).
    ///After creation, start/stop can be invoked to start or stop data flow.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///MotionTrackerCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for further use. Refer to `Overview <Overview.html>`_ .
    ///</summary>
    public class MotionTrackerCameraDevice : RefBase
    {
        internal MotionTrackerCameraDevice(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new MotionTrackerCameraDevice(cdata_new, deleter_, retainer_);
        }
        public new MotionTrackerCameraDevice Clone()
        {
            return (MotionTrackerCameraDevice)(CloneObject());
        }
        ///<summary>
        ///Create MotionTrackerCameraDevice object.
        ///</summary>
        public MotionTrackerCameraDevice() : base(IntPtr.Zero, Detail.easyar_MotionTrackerCameraDevice__dtor, Detail.easyar_MotionTrackerCameraDevice__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_MotionTrackerCameraDevice__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Check if the devices supports motion tracking. Returns True if the device supports Motion Tracking, otherwise returns False.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_MotionTrackerCameraDevice_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Set `InputFrame`_ buffer capacity.
        ///bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is higher than this number, the device will not output new `InputFrame`_ until previous `InputFrame`_ has been released. This may cause screen stuck. Refer to `Overview <Overview.html>`_ .
        ///</summary>
        public virtual void setBufferCapacity(int capacity)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_MotionTrackerCameraDevice_setBufferCapacity(cdata, capacity);
            }
        }
        ///<summary>
        ///Get `InputFrame`_ buffer capacity. The default is 8.
        ///</summary>
        public virtual int bufferCapacity()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_MotionTrackerCameraDevice_bufferCapacity(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///`InputFrame`_ output port.
        ///</summary>
        public virtual InputFrameSource inputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_MotionTrackerCameraDevice_inputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSource>(_return_value_, Detail.easyar_InputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Start motion tracking or resume motion tracking after pause.
        ///Notice: Calling start after pausing will trigger device relocalization. Tracking will resume when the relocalization process succeeds.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_MotionTrackerCameraDevice_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Pause motion tracking. Call `start` to trigger relocation, resume motion tracking if the relocation succeeds.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_MotionTrackerCameraDevice_stop(cdata);
            }
        }
        ///<summary>
        ///Close motion tracking. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_MotionTrackerCameraDevice_close(cdata);
            }
        }
    }

    ///<summary>
    ///ImageTargetParameters represents the parameters to create a `ImageTarget`_ .
    ///</summary>
    public class ImageTargetParameters : RefBase
    {
        internal ImageTargetParameters(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ImageTargetParameters(cdata_new, deleter_, retainer_);
        }
        public new ImageTargetParameters Clone()
        {
            return (ImageTargetParameters)(CloneObject());
        }
        public ImageTargetParameters() : base(IntPtr.Zero, Detail.easyar_ImageTargetParameters__dtor, Detail.easyar_ImageTargetParameters__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_ImageTargetParameters__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Gets image.
        ///</summary>
        public virtual Image image()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTargetParameters_image(cdata, out _return_value_);
                return Detail.Object_from_c<Image>(_return_value_, Detail.easyar_Image__typeName);
            }
        }
        ///<summary>
        ///Sets image.
        ///</summary>
        public virtual void setImage(Image image)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTargetParameters_setImage(cdata, image.cdata);
            }
        }
        ///<summary>
        ///Gets target name. It can be used to distinguish targets.
        ///</summary>
        public virtual string name()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTargetParameters_name(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets target name.
        ///</summary>
        public virtual void setName(string name)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTargetParameters_setName(cdata, Detail.String_to_c(ar, name));
            }
        }
        ///<summary>
        ///Gets the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as an alternative method to distinguish from targets.
        ///</summary>
        public virtual string uid()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTargetParameters_uid(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets target uid.
        ///</summary>
        public virtual void setUid(string uid)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTargetParameters_setUid(cdata, Detail.String_to_c(ar, uid));
            }
        }
        ///<summary>
        ///Gets meta data.
        ///</summary>
        public virtual string meta()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTargetParameters_meta(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets meta data。
        ///</summary>
        public virtual void setMeta(string meta)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTargetParameters_setMeta(cdata, Detail.String_to_c(ar, meta));
            }
        }
        ///<summary>
        ///Gets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
        ///</summary>
        public virtual float scale()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTargetParameters_scale(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets the scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
        ///It is needed to set the model scale in rendering engine separately.
        ///</summary>
        public virtual void setScale(float scale)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTargetParameters_setScale(cdata, scale);
            }
        }
    }

    ///<summary>
    ///ImageTarget represents planar image targets that can be tracked by `ImageTracker`_ .
    ///The fields of ImageTarget need to be filled with the create.../setupAll method before it can be read. And ImageTarget can be tracked by `ImageTracker`_ after a successful load into the `ImageTracker`_ using `ImageTracker.loadTarget`_ .
    ///</summary>
    public class ImageTarget : Target
    {
        internal ImageTarget(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ImageTarget(cdata_new, deleter_, retainer_);
        }
        public new ImageTarget Clone()
        {
            return (ImageTarget)(CloneObject());
        }
        public ImageTarget() : base(IntPtr.Zero, Detail.easyar_ImageTarget__dtor, Detail.easyar_ImageTarget__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_ImageTarget__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Creates a target from parameters.
        ///</summary>
        public static Optional<ImageTarget> createFromParameters(ImageTargetParameters parameters)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfImageTarget);
                Detail.easyar_ImageTarget_createFromParameters(parameters.cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<ImageTarget>(p.value, Detail.easyar_ImageTarget__typeName) : Optional<ImageTarget>.Empty);
            }
        }
        ///<summary>
        ///Creates a target from an etd file.
        ///</summary>
        public static Optional<ImageTarget> createFromTargetFile(string path, StorageType storageType)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfImageTarget);
                Detail.easyar_ImageTarget_createFromTargetFile(Detail.String_to_c(ar, path), storageType, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<ImageTarget>(p.value, Detail.easyar_ImageTarget__typeName) : Optional<ImageTarget>.Empty);
            }
        }
        ///<summary>
        ///Creates a target from an etd data buffer.
        ///</summary>
        public static Optional<ImageTarget> createFromTargetData(Buffer buffer)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfImageTarget);
                Detail.easyar_ImageTarget_createFromTargetData(buffer.cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<ImageTarget>(p.value, Detail.easyar_ImageTarget__typeName) : Optional<ImageTarget>.Empty);
            }
        }
        ///<summary>
        ///Saves as an etd file.
        ///</summary>
        public virtual bool save(string path)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTarget_save(cdata, Detail.String_to_c(ar, path));
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates a target from an image file. If not needed, name, uid, meta can be passed with empty string, and scale can be passed with default value 1.
        ///</summary>
        public static Optional<ImageTarget> createFromImageFile(string path, StorageType storageType, string name, string uid, string meta, float scale)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfImageTarget);
                Detail.easyar_ImageTarget_createFromImageFile(Detail.String_to_c(ar, path), storageType, Detail.String_to_c(ar, name), Detail.String_to_c(ar, uid), Detail.String_to_c(ar, meta), scale, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<ImageTarget>(p.value, Detail.easyar_ImageTarget__typeName) : Optional<ImageTarget>.Empty);
            }
        }
        ///<summary>
        ///Setup all targets listed in the json file or json string from path with storageType. This method only parses the json file or string.
        ///If path is json file path, storageType should be `App` or `Assets` or `Absolute` indicating the path type. Paths inside json files should be absolute path or relative path to the json file.
        ///See `StorageType`_ for more descriptions.
        ///</summary>
        public static List<ImageTarget> setupAll(string path, StorageType storageType)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTarget_setupAll(Detail.String_to_c(ar, path), storageType, out _return_value_);
                return Detail.ListOfImageTarget_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///The scale of image. The value is the physical image width divided by 1 meter. The default value is 1.
        ///</summary>
        public virtual float scale()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTarget_scale(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///The aspect ratio of image, width divided by height.
        ///</summary>
        public virtual float aspectRatio()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTarget_aspectRatio(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets image target scale, this will overwrite the value set in the json file or the default value. The value is the physical image width divided by 1 meter. The default value is 1.
        ///It is needed to set the model scale in rendering engine separately.
        ///</summary>
        public virtual bool setScale(float scale)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTarget_setScale(cdata, scale);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns a list of images that stored in the target. It is generally used to get image data from cloud returned target.
        ///</summary>
        public virtual List<Image> images()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTarget_images(cdata, out _return_value_);
                return Detail.ListOfImage_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
        ///</summary>
        public override int runtimeID()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTarget_runtimeID(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
        ///</summary>
        public override string uid()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTarget_uid(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Returns the target name. Name is used to distinguish targets in a json file.
        ///</summary>
        public override string name()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTarget_name(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Set name. It will erase previously set data or data from cloud.
        ///</summary>
        public override void setName(string name)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTarget_setName(cdata, Detail.String_to_c(ar, name));
            }
        }
        ///<summary>
        ///Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
        ///</summary>
        public override string meta()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTarget_meta(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Set meta data. It will erase previously set data or data from cloud.
        ///</summary>
        public override void setMeta(string data)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTarget_setMeta(cdata, Detail.String_to_c(ar, data));
            }
        }
    }

    public enum ImageTrackerMode
    {
        ///<summary>
        ///Quality is preferred.
        ///</summary>
        PreferQuality = 0,
        ///<summary>
        ///Performance is preferred.
        ///</summary>
        PreferPerformance = 1,
    }

    ///<summary>
    ///Result of `ImageTracker`_ .
    ///</summary>
    public class ImageTrackerResult : TargetTrackerResult
    {
        internal ImageTrackerResult(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ImageTrackerResult(cdata_new, deleter_, retainer_);
        }
        public new ImageTrackerResult Clone()
        {
            return (ImageTrackerResult)(CloneObject());
        }
        ///<summary>
        ///Returns the list of `TargetInstance`_ contained in the result.
        ///</summary>
        public override List<TargetInstance> targetInstances()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTrackerResult_targetInstances(cdata, out _return_value_);
                return Detail.ListOfTargetInstance_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets the list of `TargetInstance`_ contained in the result.
        ///</summary>
        public override void setTargetInstances(List<TargetInstance> instances)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTrackerResult_setTargetInstances(cdata, Detail.ListOfTargetInstance_to_c(ar, instances));
            }
        }
    }

    ///<summary>
    ///ImageTracker implements image target detection and tracking.
    ///ImageTracker occupies (1 + SimultaneousNum) buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///After creation, you can call start/stop to enable/disable the track process. start and stop are very lightweight calls.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///ImageTracker inputs `FeedbackFrame`_ from feedbackFrameSink. `FeedbackFrameSource`_ shall be connected to feedbackFrameSink for use. Refer to `Overview <Overview.html>`_ .
    ///Before a `Target`_ can be tracked by ImageTracker, you have to load it using loadTarget/unloadTarget. You can get load/unload results from callbacks passed into the interfaces.
    ///</summary>
    public class ImageTracker : RefBase
    {
        internal ImageTracker(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ImageTracker(cdata_new, deleter_, retainer_);
        }
        public new ImageTracker Clone()
        {
            return (ImageTracker)(CloneObject());
        }
        ///<summary>
        ///Returns true.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTracker_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///`FeedbackFrame`_ input port. The InputFrame member of FeedbackFrame must have raw image, timestamp, and camera parameters.
        ///</summary>
        public virtual FeedbackFrameSink feedbackFrameSink()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTracker_feedbackFrameSink(cdata, out _return_value_);
                return Detail.Object_from_c<FeedbackFrameSink>(_return_value_, Detail.easyar_FeedbackFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTracker_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///`OutputFrame`_ output port.
        ///</summary>
        public virtual OutputFrameSource outputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTracker_outputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Creates an instance. The default track mode is `ImageTrackerMode.PreferQuality`_ .
        ///</summary>
        public static ImageTracker create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTracker_create(out _return_value_);
                return Detail.Object_from_c<ImageTracker>(_return_value_, Detail.easyar_ImageTracker__typeName);
            }
        }
        ///<summary>
        ///Creates an instance with a specified track mode. On lower-end phones, `ImageTrackerMode.PreferPerformance`_ can be used to keep a better performance with a little quality loss.
        ///</summary>
        public static ImageTracker createWithMode(ImageTrackerMode trackMode)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTracker_createWithMode(trackMode, out _return_value_);
                return Detail.Object_from_c<ImageTracker>(_return_value_, Detail.easyar_ImageTracker__typeName);
            }
        }
        ///<summary>
        ///Starts the track algorithm.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTracker_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops the track algorithm. Call start to start the track again.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTracker_stop(cdata);
            }
        }
        ///<summary>
        ///Close. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTracker_close(cdata);
            }
        }
        ///<summary>
        ///Load a `Target`_ into the tracker. A Target can only be tracked by tracker after a successful load.
        ///This method is an asynchronous method. A load operation may take some time to finish and detection of a new/lost target may take more time during the load. The track time after detection will not be affected. If you want to know the load result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
        ///</summary>
        public virtual void loadTarget(Target target, CallbackScheduler callbackScheduler, Action<Target, bool> callback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTracker_loadTarget(cdata, target.cdata, callbackScheduler.cdata, Detail.FunctorOfVoidFromTargetAndBool_to_c(callback));
            }
        }
        ///<summary>
        ///Unload a `Target`_ from the tracker.
        ///This method is an asynchronous method. An unload operation may take some time to finish and detection of a new/lost target may take more time during the unload. If you want to know the unload result, you have to handle the callback data. The callback will be called from the thread specified by `CallbackScheduler`_ . It will not block the track thread or any other operations except other load/unload.
        ///</summary>
        public virtual void unloadTarget(Target target, CallbackScheduler callbackScheduler, Action<Target, bool> callback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ImageTracker_unloadTarget(cdata, target.cdata, callbackScheduler.cdata, Detail.FunctorOfVoidFromTargetAndBool_to_c(callback));
            }
        }
        ///<summary>
        ///Returns current loaded targets in the tracker. If an asynchronous load/unload is in progress, the returned value will not reflect the result until all load/unload finish.
        ///</summary>
        public virtual List<Target> targets()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImageTracker_targets(cdata, out _return_value_);
                return Detail.ListOfTarget_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
        ///</summary>
        public virtual bool setSimultaneousNum(int num)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTracker_setSimultaneousNum(cdata, num);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets the max number of targets which will be the simultaneously tracked by the tracker. The default value is 1.
        ///</summary>
        public virtual int simultaneousNum()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ImageTracker_simultaneousNum(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///Recorder implements recording for current rendering screen.
    ///Currently Recorder only works on Android (4.3 or later) and iOS with OpenGL ES 2.0 context.
    ///Due to the dependency to OpenGLES, every method in this class (except requestPermissions, including the destructor) has to be called in a single thread containing an OpenGLES context.
    ///**Unity Only** If in Unity, Multi-threaded rendering is enabled, scripting thread and rendering thread will be two separate threads, which makes it impossible to call updateFrame in the rendering thread. For this reason, to use Recorder, Multi-threaded rendering option shall be disabled.
    ///</summary>
    public class Recorder : RefBase
    {
        internal Recorder(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new Recorder(cdata_new, deleter_, retainer_);
        }
        public new Recorder Clone()
        {
            return (Recorder)(CloneObject());
        }
        ///<summary>
        ///Returns true only on Android 4.3 or later, or on iOS.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Recorder_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Requests recording permissions from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
        ///</summary>
        public static void requestPermissions(CallbackScheduler callbackScheduler, Optional<Action<PermissionStatus, string>> permissionCallback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Recorder_requestPermissions(callbackScheduler.cdata, permissionCallback.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromPermissionStatusAndString { has_value = true, value = Detail.FunctorOfVoidFromPermissionStatusAndString_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromPermissionStatusAndString { has_value = false, value = default(Detail.FunctorOfVoidFromPermissionStatusAndString) }));
            }
        }
        ///<summary>
        ///Creates an instance and initialize recording. statusCallback will dispatch event of status change and corresponding log.
        ///</summary>
        public static Recorder create(RecorderConfiguration config, CallbackScheduler callbackScheduler, Optional<Action<RecordStatus, string>> statusCallback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Recorder_create(config.cdata, callbackScheduler.cdata, statusCallback.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromRecordStatusAndString { has_value = true, value = Detail.FunctorOfVoidFromRecordStatusAndString_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromRecordStatusAndString { has_value = false, value = default(Detail.FunctorOfVoidFromRecordStatusAndString) }), out _return_value_);
                return Detail.Object_from_c<Recorder>(_return_value_, Detail.easyar_Recorder__typeName);
            }
        }
        ///<summary>
        ///Start recording.
        ///</summary>
        public virtual void start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Recorder_start(cdata);
            }
        }
        ///<summary>
        ///Update and record a frame using texture data.
        ///</summary>
        public virtual void updateFrame(TextureId texture, int width, int height)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Recorder_updateFrame(cdata, texture.cdata, width, height);
            }
        }
        ///<summary>
        ///Stop recording. When calling stop, it will wait for file write to end and returns whether recording is successful.
        ///</summary>
        public virtual bool stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Recorder_stop(cdata);
                return _return_value_;
            }
        }
    }

    public enum RecordProfile
    {
        ///<summary>
        ///1080P, low quality
        ///</summary>
        Quality_1080P_Low = 0x00000001,
        ///<summary>
        ///1080P, middle quality
        ///</summary>
        Quality_1080P_Middle = 0x00000002,
        ///<summary>
        ///1080P, high quality
        ///</summary>
        Quality_1080P_High = 0x00000004,
        ///<summary>
        ///720P, low quality
        ///</summary>
        Quality_720P_Low = 0x00000008,
        ///<summary>
        ///720P, middle quality
        ///</summary>
        Quality_720P_Middle = 0x00000010,
        ///<summary>
        ///720P, high quality
        ///</summary>
        Quality_720P_High = 0x00000020,
        ///<summary>
        ///480P, low quality
        ///</summary>
        Quality_480P_Low = 0x00000040,
        ///<summary>
        ///480P, middle quality
        ///</summary>
        Quality_480P_Middle = 0x00000080,
        ///<summary>
        ///480P, high quality
        ///</summary>
        Quality_480P_High = 0x00000100,
        ///<summary>
        ///default resolution and quality, same as `Quality_720P_Middle`
        ///</summary>
        Quality_Default = 0x00000010,
    }

    public enum RecordVideoSize
    {
        ///<summary>
        ///1080P
        ///</summary>
        Vid1080p = 0x00000002,
        ///<summary>
        ///720P
        ///</summary>
        Vid720p = 0x00000010,
        ///<summary>
        ///480P
        ///</summary>
        Vid480p = 0x00000080,
    }

    public enum RecordZoomMode
    {
        ///<summary>
        ///If output aspect ratio does not fit input, content will be clipped to fit output aspect ratio.
        ///</summary>
        NoZoomAndClip = 0x00000000,
        ///<summary>
        ///If output aspect ratio does not fit input, content will not be clipped and there will be black borders in one dimension.
        ///</summary>
        ZoomInWithAllContent = 0x00000001,
    }

    public enum RecordVideoOrientation
    {
        ///<summary>
        ///video recorded is landscape
        ///</summary>
        Landscape = 0x00000000,
        ///<summary>
        ///video recorded is portrait
        ///</summary>
        Portrait = 0x00000001,
    }

    public enum RecordStatus
    {
        ///<summary>
        ///recording start
        ///</summary>
        OnStarted = 0x00000002,
        ///<summary>
        ///recording stopped
        ///</summary>
        OnStopped = 0x00000004,
        ///<summary>
        ///start fail
        ///</summary>
        FailedToStart = 0x00000202,
        ///<summary>
        ///file write succeed
        ///</summary>
        FileSucceeded = 0x00000400,
        ///<summary>
        ///file write fail
        ///</summary>
        FileFailed = 0x00000401,
        ///<summary>
        ///runtime info with description
        ///</summary>
        LogInfo = 0x00000800,
        ///<summary>
        ///runtime error with description
        ///</summary>
        LogError = 0x00001000,
    }

    ///<summary>
    ///RecorderConfiguration is startup configuration for `Recorder`_ .
    ///</summary>
    public class RecorderConfiguration : RefBase
    {
        internal RecorderConfiguration(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new RecorderConfiguration(cdata_new, deleter_, retainer_);
        }
        public new RecorderConfiguration Clone()
        {
            return (RecorderConfiguration)(CloneObject());
        }
        public RecorderConfiguration() : base(IntPtr.Zero, Detail.easyar_RecorderConfiguration__dtor, Detail.easyar_RecorderConfiguration__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_RecorderConfiguration__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Sets absolute path for output video file.
        ///</summary>
        public virtual void setOutputFile(string path)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setOutputFile(cdata, Detail.String_to_c(ar, path));
            }
        }
        ///<summary>
        ///Sets recording profile. Default value is Quality_720P_Middle.
        ///This is an all-in-one configuration, you can control in more advanced mode with other APIs.
        ///</summary>
        public virtual bool setProfile(RecordProfile profile)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_RecorderConfiguration_setProfile(cdata, profile);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets recording video size. Default value is Vid720p.
        ///</summary>
        public virtual void setVideoSize(RecordVideoSize framesize)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setVideoSize(cdata, framesize);
            }
        }
        ///<summary>
        ///Sets recording video bit rate. Default value is 2500000.
        ///</summary>
        public virtual void setVideoBitrate(int bitrate)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setVideoBitrate(cdata, bitrate);
            }
        }
        ///<summary>
        ///Sets recording audio channel count. Default value is 1.
        ///</summary>
        public virtual void setChannelCount(int count)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setChannelCount(cdata, count);
            }
        }
        ///<summary>
        ///Sets recording audio sample rate. Default value is 44100.
        ///</summary>
        public virtual void setAudioSampleRate(int samplerate)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setAudioSampleRate(cdata, samplerate);
            }
        }
        ///<summary>
        ///Sets recording audio bit rate. Default value is 96000.
        ///</summary>
        public virtual void setAudioBitrate(int bitrate)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setAudioBitrate(cdata, bitrate);
            }
        }
        ///<summary>
        ///Sets recording video orientation. Default value is Landscape.
        ///</summary>
        public virtual void setVideoOrientation(RecordVideoOrientation mode)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setVideoOrientation(cdata, mode);
            }
        }
        ///<summary>
        ///Sets recording zoom mode. Default value is NoZoomAndClip.
        ///</summary>
        public virtual void setZoomMode(RecordZoomMode mode)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_RecorderConfiguration_setZoomMode(cdata, mode);
            }
        }
    }

    ///<summary>
    ///Describes the result of mapping and localization. Updated at the same frame rate with OutputFrame.
    ///</summary>
    public class SparseSpatialMapResult : FrameFilterResult
    {
        internal SparseSpatialMapResult(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SparseSpatialMapResult(cdata_new, deleter_, retainer_);
        }
        public new SparseSpatialMapResult Clone()
        {
            return (SparseSpatialMapResult)(CloneObject());
        }
        ///<summary>
        ///Obtain motion tracking status.
        ///</summary>
        public virtual MotionTrackingStatus getMotionTrackingStatus()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMapResult_getMotionTrackingStatus(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns pose of the origin of VIO system in camera coordinate system.
        ///</summary>
        public virtual Optional<Matrix44F> getVioPose()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMapResult_getVioPose(cdata);
                return _return_value_.map(p => p.has_value ? p.value : Optional<Matrix44F>.Empty);
            }
        }
        ///<summary>
        ///Returns the pose of origin of the map in camera coordinate system, when localization is successful.
        ///Otherwise, returns pose of the origin of VIO system in camera coordinate system.
        ///</summary>
        public virtual Optional<Matrix44F> getMapPose()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMapResult_getMapPose(cdata);
                return _return_value_.map(p => p.has_value ? p.value : Optional<Matrix44F>.Empty);
            }
        }
        ///<summary>
        ///Returns true if the system can reliablly locate the pose of the device with regard to the map.
        ///Once relocalization succeeds, relative pose can be updated by motion tracking module.
        ///As long as the motion tracking module returns normal tracking status, the localization status is also true.
        ///</summary>
        public virtual bool getLocalizationStatus()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMapResult_getLocalizationStatus(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns current localized map ID.
        ///</summary>
        public virtual string getLocalizationMapID()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMapResult_getLocalizationMapID(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
    }

    public enum PlaneType
    {
        ///<summary>
        ///Horizontal plane
        ///</summary>
        Horizontal = 0,
        ///<summary>
        ///Vertical plane
        ///</summary>
        Vertical = 1,
    }

    public class PlaneData : RefBase
    {
        internal PlaneData(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new PlaneData(cdata_new, deleter_, retainer_);
        }
        public new PlaneData Clone()
        {
            return (PlaneData)(CloneObject());
        }
        ///<summary>
        ///Constructor
        ///</summary>
        public PlaneData() : base(IntPtr.Zero, Detail.easyar_PlaneData__dtor, Detail.easyar_PlaneData__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_PlaneData__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Returns the type of this plane.
        ///</summary>
        public virtual PlaneType getType()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_PlaneData_getType(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the pose of the center of the detected plane.The pose's transformed +Y axis will be point normal out of the plane, with the +X and +Z axes orienting the extents of the bounding rectangle.
        ///</summary>
        public virtual Matrix44F getPose()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_PlaneData_getPose(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the length of this plane's bounding rectangle measured along the local X-axis of the coordinate space centered on the plane.
        ///</summary>
        public virtual float getExtentX()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_PlaneData_getExtentX(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the length of this plane's bounding rectangle measured along the local Z-axis of the coordinate frame centered on the plane.
        ///</summary>
        public virtual float getExtentZ()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_PlaneData_getExtentZ(cdata);
                return _return_value_;
            }
        }
    }

    public enum LocalizationMode
    {
        ///<summary>
        ///Attempt to perform localization in current SparseSpatialMap until success.
        ///</summary>
        UntilSuccess = 0,
        ///<summary>
        ///Perform localization only once
        ///</summary>
        Once = 1,
        ///<summary>
        ///Keep performing localization and adjust result on success
        ///</summary>
        KeepUpdate = 2,
        ///<summary>
        ///Keep performing localization and adjust localization result only when localization returns different map ID from previous results
        ///</summary>
        ContinousLocalize = 3,
    }

    ///<summary>
    ///Configuration used to set the localization mode.
    ///</summary>
    public class SparseSpatialMapConfig : RefBase
    {
        internal SparseSpatialMapConfig(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SparseSpatialMapConfig(cdata_new, deleter_, retainer_);
        }
        public new SparseSpatialMapConfig Clone()
        {
            return (SparseSpatialMapConfig)(CloneObject());
        }
        ///<summary>
        ///Constructor
        ///</summary>
        public SparseSpatialMapConfig() : base(IntPtr.Zero, Detail.easyar_SparseSpatialMapConfig__dtor, Detail.easyar_SparseSpatialMapConfig__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_SparseSpatialMapConfig__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Sets localization configurations. See also `LocalizationMode`_.
        ///</summary>
        public virtual void setLocalizationMode(LocalizationMode @value)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMapConfig_setLocalizationMode(cdata, @value);
            }
        }
        ///<summary>
        ///Returns localization configurations. See also `LocalizationMode`_.
        ///</summary>
        public virtual LocalizationMode getLocalizationMode()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMapConfig_getLocalizationMode(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///Provides core components for SparseSpatialMap, can be used for sparse spatial map building as well as localization using existing map. Also provides utilities for point cloud and plane access.
    ///SparseSpatialMap occupies 2 buffers of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///</summary>
    public class SparseSpatialMap : RefBase
    {
        internal SparseSpatialMap(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SparseSpatialMap(cdata_new, deleter_, retainer_);
        }
        public new SparseSpatialMap Clone()
        {
            return (SparseSpatialMap)(CloneObject());
        }
        ///<summary>
        ///Check whether SparseSpatialMap is is available, always return true.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMap_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Input port for input frame. For SparseSpatialMap to work, the inputFrame must include camera parameters, timestamp and spatial information. See also `InputFrameSink`_
        ///</summary>
        public virtual InputFrameSink inputFrameSink()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_inputFrameSink(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMap_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Output port for output frame. See also `OutputFrameSource`_
        ///</summary>
        public virtual OutputFrameSource outputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_outputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Construct SparseSpatialMap.
        ///</summary>
        public static SparseSpatialMap create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_create(out _return_value_);
                return Detail.Object_from_c<SparseSpatialMap>(_return_value_, Detail.easyar_SparseSpatialMap__typeName);
            }
        }
        ///<summary>
        ///Start SparseSpatialMap system.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMap_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stop SparseSpatialMap from running。Can resume running by calling start().
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMap_stop(cdata);
            }
        }
        ///<summary>
        ///Close SparseSpatialMap. SparseSpatialMap can no longer be used.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMap_close(cdata);
            }
        }
        ///<summary>
        ///Returns the buffer of point cloud coordinate. Each 3D point is represented by three consecutive values, representing X, Y, Z position coordinates in the world coordinate space, each of which takes 4 bytes.
        ///</summary>
        public virtual Buffer getPointCloudBuffer()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_getPointCloudBuffer(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Returns detected planes in SparseSpatialMap.
        ///</summary>
        public virtual List<PlaneData> getMapPlanes()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_getMapPlanes(cdata, out _return_value_);
                return Detail.ListOfPlaneData_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Perform hit test against the point cloud. The results are returned sorted by their distance to the camera in ascending order.
        ///</summary>
        public virtual List<Vec3F> hitTestAgainstPointCloud(Vec2F cameraImagePoint)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_hitTestAgainstPointCloud(cdata, cameraImagePoint, out _return_value_);
                return Detail.ListOfVec3F_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Performs ray cast from the user's device in the direction of given screen point.
        ///Intersections with detected planes are returned. 3D positions on physical planes are sorted by distance from the device in ascending order.
        ///For the camera image coordinate system ([0, 1]^2), x-right, y-down, and origin is at left-top corner. `CameraParameters.imageCoordinatesFromScreenCoordinates`_ can be used to convert points from screen coordinate system to camera image coordinate system.
        ///The output point cloud coordinate is in the world coordinate system.
        ///</summary>
        public virtual List<Vec3F> hitTestAgainstPlanes(Vec2F cameraImagePoint)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_hitTestAgainstPlanes(cdata, cameraImagePoint, out _return_value_);
                return Detail.ListOfVec3F_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Get the map data version of the current SparseSpatialMap.
        ///</summary>
        public static string getMapVersion()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_getMapVersion(out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///UnloadMap specified SparseSpatialMap data via callback function.The return value of callback indicates whether unload map succeeds (true) or fails (false).
        ///</summary>
        public virtual void unloadMap(string mapID, CallbackScheduler callbackScheduler, Optional<Action<bool>> resultCallBack)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMap_unloadMap(cdata, Detail.String_to_c(ar, mapID), callbackScheduler.cdata, resultCallBack.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromBool { has_value = true, value = Detail.FunctorOfVoidFromBool_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromBool { has_value = false, value = default(Detail.FunctorOfVoidFromBool) }));
            }
        }
        ///<summary>
        ///Set configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
        ///</summary>
        public virtual void setConfig(SparseSpatialMapConfig config)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMap_setConfig(cdata, config.cdata);
            }
        }
        ///<summary>
        ///Returns configurations for SparseSpatialMap. See also `SparseSpatialMapConfig`_.
        ///</summary>
        public virtual SparseSpatialMapConfig getConfig()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMap_getConfig(cdata, out _return_value_);
                return Detail.Object_from_c<SparseSpatialMapConfig>(_return_value_, Detail.easyar_SparseSpatialMapConfig__typeName);
            }
        }
        ///<summary>
        ///Start localization in loaded maps. Should set `LocalizationMode`_ first.
        ///</summary>
        public virtual bool startLocalization()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMap_startLocalization(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stop localization in loaded maps.
        ///</summary>
        public virtual void stopLocalization()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMap_stopLocalization(cdata);
            }
        }
    }

    ///<summary>
    ///SparseSpatialMap manager class, for managing sharing.
    ///</summary>
    public class SparseSpatialMapManager : RefBase
    {
        internal SparseSpatialMapManager(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SparseSpatialMapManager(cdata_new, deleter_, retainer_);
        }
        public new SparseSpatialMapManager Clone()
        {
            return (SparseSpatialMapManager)(CloneObject());
        }
        ///<summary>
        ///Check whether SparseSpatialMapManager is is available. It returns true when the operating system is Mac, iOS or Android.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_SparseSpatialMapManager_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static SparseSpatialMapManager create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_SparseSpatialMapManager_create(out _return_value_);
                return Detail.Object_from_c<SparseSpatialMapManager>(_return_value_, Detail.easyar_SparseSpatialMapManager__typeName);
            }
        }
        ///<summary>
        ///Creates a map from `SparseSpatialMap`_ and upload it to EasyAR cloud servers. After completion, a serverMapId will be returned for loading map from EasyAR cloud servers.
        ///</summary>
        public virtual void host(SparseSpatialMap mapBuilder, string apiKey, string apiSecret, string sparseSpatialMapAppId, string name, Optional<Image> preview, CallbackScheduler callbackScheduler, Action<bool, string, string> onCompleted)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMapManager_host(cdata, mapBuilder.cdata, Detail.String_to_c(ar, apiKey), Detail.String_to_c(ar, apiSecret), Detail.String_to_c(ar, sparseSpatialMapAppId), Detail.String_to_c(ar, name), preview.map(p => p.OnSome ? new Detail.OptionalOfImage { has_value = true, value = p.Value.cdata } : new Detail.OptionalOfImage { has_value = false, value = default(IntPtr) }), callbackScheduler.cdata, Detail.FunctorOfVoidFromBoolAndStringAndString_to_c(onCompleted));
            }
        }
        ///<summary>
        ///Loads a map from EasyAR cloud servers by serverMapId. To unload the map, call `SparseSpatialMap.unloadMap`_ with serverMapId.
        ///</summary>
        public virtual void load(SparseSpatialMap mapTracker, string serverMapId, string apiKey, string apiSecret, string sparseSpatialMapAppId, CallbackScheduler callbackScheduler, Action<bool, string> onCompleted)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMapManager_load(cdata, mapTracker.cdata, Detail.String_to_c(ar, serverMapId), Detail.String_to_c(ar, apiKey), Detail.String_to_c(ar, apiSecret), Detail.String_to_c(ar, sparseSpatialMapAppId), callbackScheduler.cdata, Detail.FunctorOfVoidFromBoolAndString_to_c(onCompleted));
            }
        }
        ///<summary>
        ///Clears allocated cache space.
        ///</summary>
        public virtual void clear()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SparseSpatialMapManager_clear(cdata);
            }
        }
    }

    ///<summary>
    ///Image helper class.
    ///</summary>
    public class ImageHelper
    {
        ///<summary>
        ///Decodes a JPEG or PNG file.
        ///</summary>
        public static Optional<Image> decode(Buffer buffer)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfImage);
                Detail.easyar_ImageHelper_decode(buffer.cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<Image>(p.value, Detail.easyar_Image__typeName) : Optional<Image>.Empty);
            }
        }
    }

    ///<summary>
    ///ARCoreCameraDevice implements a camera device based on ARCore, which outputs `InputFrame`_  (including image, camera parameters, timestamp, 6DOF location, and tracking status).
    ///Loading of libarcore_sdk_c.so with java.lang.System.loadLibrary is required.
    ///After creation, start/stop can be invoked to start or stop video stream capture.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///ARCoreCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview <Overview.html>`_ .
    ///bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview <Overview.html>`_ .
    ///Caution: Currently, ARCore(v1.13.0) has memory leaks on creating and destroying sessions. Repeated creations and destructions will cause an increasing and non-reclaimable memory footprint.
    ///</summary>
    public class ARCoreCameraDevice : RefBase
    {
        internal ARCoreCameraDevice(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ARCoreCameraDevice(cdata_new, deleter_, retainer_);
        }
        public new ARCoreCameraDevice Clone()
        {
            return (ARCoreCameraDevice)(CloneObject());
        }
        public ARCoreCameraDevice() : base(IntPtr.Zero, Detail.easyar_ARCoreCameraDevice__dtor, Detail.easyar_ARCoreCameraDevice__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_ARCoreCameraDevice__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Checks if the component is available. It returns true only on Android when ARCore is installed.
        ///If called with libarcore_sdk_c.so not loaded, it returns false.
        ///Notice: If ARCore is not supported on the device but ARCore apk is installed via side-loading, it will return true, but ARCore will not function properly.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ARCoreCameraDevice_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///`InputFrame`_ buffer capacity. The default is 8.
        ///</summary>
        public virtual int bufferCapacity()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ARCoreCameraDevice_bufferCapacity(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets `InputFrame`_ buffer capacity.
        ///</summary>
        public virtual void setBufferCapacity(int capacity)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ARCoreCameraDevice_setBufferCapacity(cdata, capacity);
            }
        }
        ///<summary>
        ///`InputFrame`_ output port.
        ///</summary>
        public virtual InputFrameSource inputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ARCoreCameraDevice_inputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSource>(_return_value_, Detail.easyar_InputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Starts video stream capture.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ARCoreCameraDevice_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops video stream capture.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ARCoreCameraDevice_stop(cdata);
            }
        }
        ///<summary>
        ///Close. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ARCoreCameraDevice_close(cdata);
            }
        }
    }

    ///<summary>
    ///ARKitCameraDevice implements a camera device based on ARKit, which outputs `InputFrame`_ (including image, camera parameters, timestamp, 6DOF location, and tracking status).
    ///After creation, start/stop can be invoked to start or stop data collection.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///ARKitCameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview <Overview.html>`_ .
    ///bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview <Overview.html>`_ .
    ///</summary>
    public class ARKitCameraDevice : RefBase
    {
        internal ARKitCameraDevice(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ARKitCameraDevice(cdata_new, deleter_, retainer_);
        }
        public new ARKitCameraDevice Clone()
        {
            return (ARKitCameraDevice)(CloneObject());
        }
        public ARKitCameraDevice() : base(IntPtr.Zero, Detail.easyar_ARKitCameraDevice__dtor, Detail.easyar_ARKitCameraDevice__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_ARKitCameraDevice__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Checks if the component is available. It returns true only on iOS 11 or later when ARKit is supported by hardware.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ARKitCameraDevice_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///`InputFrame`_ buffer capacity. The default is 8.
        ///</summary>
        public virtual int bufferCapacity()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ARKitCameraDevice_bufferCapacity(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets `InputFrame`_ buffer capacity.
        ///</summary>
        public virtual void setBufferCapacity(int capacity)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ARKitCameraDevice_setBufferCapacity(cdata, capacity);
            }
        }
        ///<summary>
        ///`InputFrame`_ output port.
        ///</summary>
        public virtual InputFrameSource inputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ARKitCameraDevice_inputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSource>(_return_value_, Detail.easyar_InputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Starts video stream capture.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_ARKitCameraDevice_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops video stream capture.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ARKitCameraDevice_stop(cdata);
            }
        }
        ///<summary>
        ///Close. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_ARKitCameraDevice_close(cdata);
            }
        }
    }

    ///<summary>
    ///Callback scheduler.
    ///There are two subclasses: `DelayedCallbackScheduler`_ and `ImmediateCallbackScheduler`_ .
    ///`DelayedCallbackScheduler`_ is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
    ///`ImmediateCallbackScheduler`_ is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
    ///</summary>
    public class CallbackScheduler : RefBase
    {
        internal CallbackScheduler(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new CallbackScheduler(cdata_new, deleter_, retainer_);
        }
        public new CallbackScheduler Clone()
        {
            return (CallbackScheduler)(CloneObject());
        }
    }

    ///<summary>
    ///Delayed callback scheduler.
    ///It is used to delay callback to be invoked manually, and it can be used in single-threaded environments (such as various UI environments).
    ///All members of this class is thread-safe.
    ///</summary>
    public class DelayedCallbackScheduler : CallbackScheduler
    {
        internal DelayedCallbackScheduler(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new DelayedCallbackScheduler(cdata_new, deleter_, retainer_);
        }
        public new DelayedCallbackScheduler Clone()
        {
            return (DelayedCallbackScheduler)(CloneObject());
        }
        public DelayedCallbackScheduler() : base(IntPtr.Zero, Detail.easyar_DelayedCallbackScheduler__dtor, Detail.easyar_DelayedCallbackScheduler__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_DelayedCallbackScheduler__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Executes a callback. If there is no callback to execute, false is returned.
        ///</summary>
        public virtual bool runOne()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_DelayedCallbackScheduler_runOne(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///Immediate callback scheduler.
    ///It is used to mark callback to be invoked when event is dispatched, and it can be used in multi-threaded environments (such as server or service daemon).
    ///All members of this class is thread-safe.
    ///</summary>
    public class ImmediateCallbackScheduler : CallbackScheduler
    {
        internal ImmediateCallbackScheduler(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new ImmediateCallbackScheduler(cdata_new, deleter_, retainer_);
        }
        public new ImmediateCallbackScheduler Clone()
        {
            return (ImmediateCallbackScheduler)(CloneObject());
        }
        ///<summary>
        ///Gets a default immediate callback scheduler.
        ///</summary>
        public static ImmediateCallbackScheduler getDefault()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_ImmediateCallbackScheduler_getDefault(out _return_value_);
                return Detail.Object_from_c<ImmediateCallbackScheduler>(_return_value_, Detail.easyar_ImmediateCallbackScheduler__typeName);
            }
        }
    }

    public enum CameraDeviceFocusMode
    {
        ///<summary>
        ///Normal auto focus mode. You should call autoFocus to start the focus in this mode.
        ///</summary>
        Normal = 0,
        ///<summary>
        ///Continuous auto focus mode
        ///</summary>
        Continousauto = 2,
        ///<summary>
        ///Infinity focus mode
        ///</summary>
        Infinity = 3,
        ///<summary>
        ///Macro (close-up) focus mode. You should call autoFocus to start the focus in this mode.
        ///</summary>
        Macro = 4,
        ///<summary>
        ///Medium distance focus mode
        ///</summary>
        Medium = 5,
    }

    public enum AndroidCameraApiType
    {
        ///<summary>
        ///Android Camera1
        ///</summary>
        Camera1 = 0,
        ///<summary>
        ///Android Camera2
        ///</summary>
        Camera2 = 1,
    }

    public enum CameraDevicePresetProfile
    {
        ///<summary>
        ///The same as AVCaptureSessionPresetPhoto.
        ///</summary>
        Photo = 0,
        ///<summary>
        ///The same as AVCaptureSessionPresetHigh.
        ///</summary>
        High = 1,
        ///<summary>
        ///The same as AVCaptureSessionPresetMedium.
        ///</summary>
        Medium = 2,
        ///<summary>
        ///The same as AVCaptureSessionPresetLow.
        ///</summary>
        Low = 3,
    }

    public enum CameraState
    {
        ///<summary>
        ///Unknown
        ///</summary>
        Unknown = 0x00000000,
        ///<summary>
        ///Disconnected
        ///</summary>
        Disconnected = 0x00000001,
        ///<summary>
        ///Preempted by another application.
        ///</summary>
        Preempted = 0x00000002,
    }

    ///<summary>
    ///CameraDevice implements a camera device, which outputs `InputFrame`_ (including image, camera paramters, and timestamp). It is available on Windows, Mac, Android and iOS.
    ///After open, start/stop can be invoked to start or stop data collection. start/stop will not change previous set camera parameters.
    ///When the component is not needed anymore, call close function to close it. It shall not be used after calling close.
    ///CameraDevice outputs `InputFrame`_ from inputFrameSource. inputFrameSource shall be connected to `InputFrameSink`_ for use. Refer to `Overview <Overview.html>`_ .
    ///bufferCapacity is the capacity of `InputFrame`_ buffer. If the count of `InputFrame`_ which has been output from the device and have not been released is more than this number, the device will not output new `InputFrame`_ , until previous `InputFrame`_ have been released. This may cause screen stuck. Refer to `Overview <Overview.html>`_ .
    ///</summary>
    public class CameraDevice : RefBase
    {
        internal CameraDevice(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new CameraDevice(cdata_new, deleter_, retainer_);
        }
        public new CameraDevice Clone()
        {
            return (CameraDevice)(CloneObject());
        }
        public CameraDevice() : base(IntPtr.Zero, Detail.easyar_CameraDevice__dtor, Detail.easyar_CameraDevice__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_CameraDevice__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Checks if the component is available. It returns true only on Windows, Mac, Android or iOS.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets current camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
        ///</summary>
        public virtual AndroidCameraApiType androidCameraApiType()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_androidCameraApiType(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets current camera API (camera1 or camera2) on Android. It must be called before calling openWithIndex, openWithSpecificType or openWithPreferredType, or it will not take effect.
        ///It is recommended to use `CameraDeviceSelector`_ to create camera with camera API set to recommended based on primary algorithm to run.
        ///</summary>
        public virtual void setAndroidCameraApiType(AndroidCameraApiType type)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_setAndroidCameraApiType(cdata, type);
            }
        }
        ///<summary>
        ///`InputFrame`_ buffer capacity. The default is 8.
        ///</summary>
        public virtual int bufferCapacity()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_bufferCapacity(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets `InputFrame`_ buffer capacity.
        ///</summary>
        public virtual void setBufferCapacity(int capacity)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_setBufferCapacity(cdata, capacity);
            }
        }
        ///<summary>
        ///`InputFrame`_ output port.
        ///</summary>
        public virtual InputFrameSource inputFrameSource()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_CameraDevice_inputFrameSource(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSource>(_return_value_, Detail.easyar_InputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Sets callback on state change to notify state of camera disconnection or preemption. It is only available on Windows.
        ///</summary>
        public virtual void setStateChangedCallback(CallbackScheduler callbackScheduler, Optional<Action<CameraState>> stateChangedCallback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_setStateChangedCallback(cdata, callbackScheduler.cdata, stateChangedCallback.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromCameraState { has_value = true, value = Detail.FunctorOfVoidFromCameraState_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromCameraState { has_value = false, value = default(Detail.FunctorOfVoidFromCameraState) }));
            }
        }
        ///<summary>
        ///Requests camera permission from operating system. You can call this function or request permission directly from operating system. It is only available on Android and iOS. On other platforms, it will call the callback directly with status being granted. This function need to be called from the UI thread.
        ///</summary>
        public static void requestPermissions(CallbackScheduler callbackScheduler, Optional<Action<PermissionStatus, string>> permissionCallback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_requestPermissions(callbackScheduler.cdata, permissionCallback.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromPermissionStatusAndString { has_value = true, value = Detail.FunctorOfVoidFromPermissionStatusAndString_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromPermissionStatusAndString { has_value = false, value = default(Detail.FunctorOfVoidFromPermissionStatusAndString) }));
            }
        }
        ///<summary>
        ///Gets count of cameras recognized by the operating system.
        ///</summary>
        public static int cameraCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_cameraCount();
                return _return_value_;
            }
        }
        ///<summary>
        ///Opens a camera by index.
        ///</summary>
        public virtual bool openWithIndex(int cameraIndex)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_openWithIndex(cdata, cameraIndex);
                return _return_value_;
            }
        }
        ///<summary>
        ///Opens a camera by specific camera device type. If no camera is matched, false will be returned. On Mac, camera device types can not be distinguished.
        ///</summary>
        public virtual bool openWithSpecificType(CameraDeviceType type)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_openWithSpecificType(cdata, type);
                return _return_value_;
            }
        }
        ///<summary>
        ///Opens a camera by camera device type. If no camera is matched, the first camera will be used.
        ///</summary>
        public virtual bool openWithPreferredType(CameraDeviceType type)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_openWithPreferredType(cdata, type);
                return _return_value_;
            }
        }
        ///<summary>
        ///Starts video stream capture.
        ///</summary>
        public virtual bool start()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_start(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops video stream capture. It will only stop capture and will not change previous set camera parameters.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_stop(cdata);
            }
        }
        ///<summary>
        ///Close. The component shall not be used after calling close.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_close(cdata);
            }
        }
        ///<summary>
        ///Camera index.
        ///</summary>
        public virtual int index()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_index(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Camera type.
        ///</summary>
        public virtual CameraDeviceType type()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_type(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation. Call after a successful open.
        ///</summary>
        public virtual CameraParameters cameraParameters()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_CameraDevice_cameraParameters(cdata, out _return_value_);
                return Detail.Object_from_c<CameraParameters>(_return_value_, Detail.easyar_CameraParameters__typeName);
            }
        }
        ///<summary>
        ///Sets camera parameters. Call after a successful open.
        ///</summary>
        public virtual void setCameraParameters(CameraParameters cameraParameters)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_CameraDevice_setCameraParameters(cdata, cameraParameters.cdata);
            }
        }
        ///<summary>
        ///Gets the current preview size. Call after a successful open.
        ///</summary>
        public virtual Vec2I size()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_size(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets the number of supported preview sizes. Call after a successful open.
        ///</summary>
        public virtual int supportedSizeCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_supportedSizeCount(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets the index-th supported preview size. It returns {0, 0} if index is out of range. Call after a successful open.
        ///</summary>
        public virtual Vec2I supportedSize(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_supportedSize(cdata, index);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets the preview size. The available nearest value will be selected. Call size to get the actual size. Call after a successful open. frameRateRange may change after calling setSize.
        ///</summary>
        public virtual bool setSize(Vec2I size)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_setSize(cdata, size);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets the number of supported frame rate ranges. Call after a successful open.
        ///</summary>
        public virtual int supportedFrameRateRangeCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_supportedFrameRateRangeCount(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets range lower bound of the index-th supported frame rate range. Call after a successful open.
        ///</summary>
        public virtual float supportedFrameRateRangeLower(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_supportedFrameRateRangeLower(cdata, index);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets range upper bound of the index-th supported frame rate range. Call after a successful open.
        ///</summary>
        public virtual float supportedFrameRateRangeUpper(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_supportedFrameRateRangeUpper(cdata, index);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets current index of frame rate range. Call after a successful open.
        ///</summary>
        public virtual int frameRateRange()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_frameRateRange(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets current index of frame rate range. Call after a successful open.
        ///</summary>
        public virtual bool setFrameRateRange(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_setFrameRateRange(cdata, index);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets flash torch mode to on. Call after a successful open.
        ///</summary>
        public virtual bool setFlashTorchMode(bool on)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_setFlashTorchMode(cdata, on);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets focus mode to focusMode. Call after a successful open.
        ///</summary>
        public virtual bool setFocusMode(CameraDeviceFocusMode focusMode)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_setFocusMode(cdata, focusMode);
                return _return_value_;
            }
        }
        ///<summary>
        ///Does auto focus once. Call after start. It is only available when FocusMode is Normal or Macro.
        ///</summary>
        public virtual bool autoFocus()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraDevice_autoFocus(cdata);
                return _return_value_;
            }
        }
    }

    public enum CameraDevicePreference
    {
        ///<summary>
        ///Optimized for `ImageTracker`_ , `ObjectTracker`_ and `CloudRecognizer`_ .
        ///</summary>
        PreferObjectSensing = 0,
        ///<summary>
        ///Optimized for `SurfaceTracker`_ .
        ///</summary>
        PreferSurfaceTracking = 1,
    }

    ///<summary>
    ///It is used for selecting camera API (camera1 or camera2) on Android. camera1 is better for compatibility, but lacks some necessary information such as timestamp. camera2 has compatibility issues on some devices.
    ///Different preferences will choose camera1 or camera2 based on usage.
    ///</summary>
    public class CameraDeviceSelector
    {
        ///<summary>
        ///Creates `CameraDevice`_ with a specified preference.
        ///</summary>
        public static CameraDevice createCameraDevice(CameraDevicePreference preference)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_CameraDeviceSelector_createCameraDevice(preference, out _return_value_);
                return Detail.Object_from_c<CameraDevice>(_return_value_, Detail.easyar_CameraDevice__typeName);
            }
        }
    }

    ///<summary>
    ///Signal input port.
    ///It is used to expose input port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class SignalSink : RefBase
    {
        internal SignalSink(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SignalSink(cdata_new, deleter_, retainer_);
        }
        public new SignalSink Clone()
        {
            return (SignalSink)(CloneObject());
        }
        ///<summary>
        ///Input data.
        ///</summary>
        public virtual void handle()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SignalSink_handle(cdata);
            }
        }
    }

    ///<summary>
    ///Signal output port.
    ///It is used to expose output port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class SignalSource : RefBase
    {
        internal SignalSource(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new SignalSource(cdata_new, deleter_, retainer_);
        }
        public new SignalSource Clone()
        {
            return (SignalSource)(CloneObject());
        }
        ///<summary>
        ///Sets data handler.
        ///</summary>
        public virtual void setHandler(Optional<Action> handler)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SignalSource_setHandler(cdata, handler.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoid { has_value = true, value = Detail.FunctorOfVoid_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoid { has_value = false, value = default(Detail.FunctorOfVoid) }));
            }
        }
        ///<summary>
        ///Connects to input port.
        ///</summary>
        public virtual void connect(SignalSink sink)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SignalSource_connect(cdata, sink.cdata);
            }
        }
        ///<summary>
        ///Disconnects.
        ///</summary>
        public virtual void disconnect()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_SignalSource_disconnect(cdata);
            }
        }
    }

    ///<summary>
    ///Input frame input port.
    ///It is used to expose input port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class InputFrameSink : RefBase
    {
        internal InputFrameSink(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrameSink(cdata_new, deleter_, retainer_);
        }
        public new InputFrameSink Clone()
        {
            return (InputFrameSink)(CloneObject());
        }
        ///<summary>
        ///Input data.
        ///</summary>
        public virtual void handle(InputFrame inputData)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_InputFrameSink_handle(cdata, inputData.cdata);
            }
        }
    }

    ///<summary>
    ///Input frame output port.
    ///It is used to expose output port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class InputFrameSource : RefBase
    {
        internal InputFrameSource(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrameSource(cdata_new, deleter_, retainer_);
        }
        public new InputFrameSource Clone()
        {
            return (InputFrameSource)(CloneObject());
        }
        ///<summary>
        ///Sets data handler.
        ///</summary>
        public virtual void setHandler(Optional<Action<InputFrame>> handler)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_InputFrameSource_setHandler(cdata, handler.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromInputFrame { has_value = true, value = Detail.FunctorOfVoidFromInputFrame_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromInputFrame { has_value = false, value = default(Detail.FunctorOfVoidFromInputFrame) }));
            }
        }
        ///<summary>
        ///Connects to input port.
        ///</summary>
        public virtual void connect(InputFrameSink sink)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_InputFrameSource_connect(cdata, sink.cdata);
            }
        }
        ///<summary>
        ///Disconnects.
        ///</summary>
        public virtual void disconnect()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_InputFrameSource_disconnect(cdata);
            }
        }
    }

    ///<summary>
    ///Output frame input port.
    ///It is used to expose input port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class OutputFrameSink : RefBase
    {
        internal OutputFrameSink(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new OutputFrameSink(cdata_new, deleter_, retainer_);
        }
        public new OutputFrameSink Clone()
        {
            return (OutputFrameSink)(CloneObject());
        }
        ///<summary>
        ///Input data.
        ///</summary>
        public virtual void handle(OutputFrame inputData)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_OutputFrameSink_handle(cdata, inputData.cdata);
            }
        }
    }

    ///<summary>
    ///Output frame output port.
    ///It is used to expose output port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class OutputFrameSource : RefBase
    {
        internal OutputFrameSource(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new OutputFrameSource(cdata_new, deleter_, retainer_);
        }
        public new OutputFrameSource Clone()
        {
            return (OutputFrameSource)(CloneObject());
        }
        ///<summary>
        ///Sets data handler.
        ///</summary>
        public virtual void setHandler(Optional<Action<OutputFrame>> handler)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_OutputFrameSource_setHandler(cdata, handler.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromOutputFrame { has_value = true, value = Detail.FunctorOfVoidFromOutputFrame_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromOutputFrame { has_value = false, value = default(Detail.FunctorOfVoidFromOutputFrame) }));
            }
        }
        ///<summary>
        ///Connects to input port.
        ///</summary>
        public virtual void connect(OutputFrameSink sink)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_OutputFrameSource_connect(cdata, sink.cdata);
            }
        }
        ///<summary>
        ///Disconnects.
        ///</summary>
        public virtual void disconnect()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_OutputFrameSource_disconnect(cdata);
            }
        }
    }

    ///<summary>
    ///Feedback frame input port.
    ///It is used to expose input port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class FeedbackFrameSink : RefBase
    {
        internal FeedbackFrameSink(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new FeedbackFrameSink(cdata_new, deleter_, retainer_);
        }
        public new FeedbackFrameSink Clone()
        {
            return (FeedbackFrameSink)(CloneObject());
        }
        ///<summary>
        ///Input data.
        ///</summary>
        public virtual void handle(FeedbackFrame inputData)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_FeedbackFrameSink_handle(cdata, inputData.cdata);
            }
        }
    }

    ///<summary>
    ///Feedback frame output port.
    ///It is used to expose output port for a component.
    ///All members of this class is thread-safe.
    ///</summary>
    public class FeedbackFrameSource : RefBase
    {
        internal FeedbackFrameSource(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new FeedbackFrameSource(cdata_new, deleter_, retainer_);
        }
        public new FeedbackFrameSource Clone()
        {
            return (FeedbackFrameSource)(CloneObject());
        }
        ///<summary>
        ///Sets data handler.
        ///</summary>
        public virtual void setHandler(Optional<Action<FeedbackFrame>> handler)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_FeedbackFrameSource_setHandler(cdata, handler.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromFeedbackFrame { has_value = true, value = Detail.FunctorOfVoidFromFeedbackFrame_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromFeedbackFrame { has_value = false, value = default(Detail.FunctorOfVoidFromFeedbackFrame) }));
            }
        }
        ///<summary>
        ///Connects to input port.
        ///</summary>
        public virtual void connect(FeedbackFrameSink sink)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_FeedbackFrameSource_connect(cdata, sink.cdata);
            }
        }
        ///<summary>
        ///Disconnects.
        ///</summary>
        public virtual void disconnect()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_FeedbackFrameSource_disconnect(cdata);
            }
        }
    }

    ///<summary>
    ///Input frame fork.
    ///It is used to branch and transfer input frame to multiple components in parallel.
    ///All members of this class is thread-safe.
    ///</summary>
    public class InputFrameFork : RefBase
    {
        internal InputFrameFork(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrameFork(cdata_new, deleter_, retainer_);
        }
        public new InputFrameFork Clone()
        {
            return (InputFrameFork)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual InputFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameFork_input(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual InputFrameSource output(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameFork_output(cdata, index, out _return_value_);
                return Detail.Object_from_c<InputFrameSource>(_return_value_, Detail.easyar_InputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Output count.
        ///</summary>
        public virtual int outputCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrameFork_outputCount(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static InputFrameFork create(int outputCount)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameFork_create(outputCount, out _return_value_);
                return Detail.Object_from_c<InputFrameFork>(_return_value_, Detail.easyar_InputFrameFork__typeName);
            }
        }
    }

    ///<summary>
    ///Output frame fork.
    ///It is used to branch and transfer output frame to multiple components in parallel.
    ///All members of this class is thread-safe.
    ///</summary>
    public class OutputFrameFork : RefBase
    {
        internal OutputFrameFork(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new OutputFrameFork(cdata_new, deleter_, retainer_);
        }
        public new OutputFrameFork Clone()
        {
            return (OutputFrameFork)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual OutputFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameFork_input(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSink>(_return_value_, Detail.easyar_OutputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual OutputFrameSource output(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameFork_output(cdata, index, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Output count.
        ///</summary>
        public virtual int outputCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_OutputFrameFork_outputCount(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static OutputFrameFork create(int outputCount)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameFork_create(outputCount, out _return_value_);
                return Detail.Object_from_c<OutputFrameFork>(_return_value_, Detail.easyar_OutputFrameFork__typeName);
            }
        }
    }

    ///<summary>
    ///Output frame join.
    ///It is used to aggregate output frame from multiple components in parallel.
    ///All members of this class is thread-safe.
    ///It shall be noticed that connections and disconnections to the inputs shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
    ///</summary>
    public class OutputFrameJoin : RefBase
    {
        internal OutputFrameJoin(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new OutputFrameJoin(cdata_new, deleter_, retainer_);
        }
        public new OutputFrameJoin Clone()
        {
            return (OutputFrameJoin)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual OutputFrameSink input(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameJoin_input(cdata, index, out _return_value_);
                return Detail.Object_from_c<OutputFrameSink>(_return_value_, Detail.easyar_OutputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual OutputFrameSource output()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameJoin_output(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Input count.
        ///</summary>
        public virtual int inputCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_OutputFrameJoin_inputCount(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance. The default joiner will be used, which takes input frame from the first input and first result or null of each input. The first result of every input will be placed at the corresponding input index of results of the final output frame.
        ///</summary>
        public static OutputFrameJoin create(int inputCount)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameJoin_create(inputCount, out _return_value_);
                return Detail.Object_from_c<OutputFrameJoin>(_return_value_, Detail.easyar_OutputFrameJoin__typeName);
            }
        }
        ///<summary>
        ///Creates an instance. A custom joiner is specified.
        ///</summary>
        public static OutputFrameJoin createWithJoiner(int inputCount, Func<List<OutputFrame>, OutputFrame> joiner)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameJoin_createWithJoiner(inputCount, Detail.FunctorOfOutputFrameFromListOfOutputFrame_to_c(joiner), out _return_value_);
                return Detail.Object_from_c<OutputFrameJoin>(_return_value_, Detail.easyar_OutputFrameJoin__typeName);
            }
        }
    }

    ///<summary>
    ///Feedback frame fork.
    ///It is used to branch and transfer feedback frame to multiple components in parallel.
    ///All members of this class is thread-safe.
    ///</summary>
    public class FeedbackFrameFork : RefBase
    {
        internal FeedbackFrameFork(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new FeedbackFrameFork(cdata_new, deleter_, retainer_);
        }
        public new FeedbackFrameFork Clone()
        {
            return (FeedbackFrameFork)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual FeedbackFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_FeedbackFrameFork_input(cdata, out _return_value_);
                return Detail.Object_from_c<FeedbackFrameSink>(_return_value_, Detail.easyar_FeedbackFrameSink__typeName);
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual FeedbackFrameSource output(int index)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_FeedbackFrameFork_output(cdata, index, out _return_value_);
                return Detail.Object_from_c<FeedbackFrameSource>(_return_value_, Detail.easyar_FeedbackFrameSource__typeName);
            }
        }
        ///<summary>
        ///Output count.
        ///</summary>
        public virtual int outputCount()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_FeedbackFrameFork_outputCount(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static FeedbackFrameFork create(int outputCount)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_FeedbackFrameFork_create(outputCount, out _return_value_);
                return Detail.Object_from_c<FeedbackFrameFork>(_return_value_, Detail.easyar_FeedbackFrameFork__typeName);
            }
        }
    }

    ///<summary>
    ///Input frame throttler.
    ///There is a input frame input port and a input frame output port. It can be used to prevent incoming frames from entering algorithm components when they have not finished handling previous workload.
    ///InputFrameThrottler occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///All members of this class is thread-safe.
    ///It shall be noticed that connections and disconnections to signalInput shall not be performed during the flowing of data, or it may stuck in a state that no frame can be output. (It is recommended to complete dataflow connection before start a camera.)
    ///</summary>
    public class InputFrameThrottler : RefBase
    {
        internal InputFrameThrottler(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrameThrottler(cdata_new, deleter_, retainer_);
        }
        public new InputFrameThrottler Clone()
        {
            return (InputFrameThrottler)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual InputFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameThrottler_input(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrameThrottler_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual InputFrameSource output()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameThrottler_output(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSource>(_return_value_, Detail.easyar_InputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Input port for clearance signal.
        ///</summary>
        public virtual SignalSink signalInput()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameThrottler_signalInput(cdata, out _return_value_);
                return Detail.Object_from_c<SignalSink>(_return_value_, Detail.easyar_SignalSink__typeName);
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static InputFrameThrottler create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameThrottler_create(out _return_value_);
                return Detail.Object_from_c<InputFrameThrottler>(_return_value_, Detail.easyar_InputFrameThrottler__typeName);
            }
        }
    }

    ///<summary>
    ///Output frame buffer.
    ///There is an output frame input port and output frame fetching function. It can be used to convert output frame fetching from asynchronous pattern to synchronous polling pattern, which fits frame by frame rendering.
    ///OutputFrameBuffer occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///All members of this class is thread-safe.
    ///</summary>
    public class OutputFrameBuffer : RefBase
    {
        internal OutputFrameBuffer(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new OutputFrameBuffer(cdata_new, deleter_, retainer_);
        }
        public new OutputFrameBuffer Clone()
        {
            return (OutputFrameBuffer)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual OutputFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameBuffer_input(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSink>(_return_value_, Detail.easyar_OutputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_OutputFrameBuffer_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Output port for frame arrival. It can be connected to `InputFrameThrottler.signalInput`_ .
        ///</summary>
        public virtual SignalSource signalOutput()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameBuffer_signalOutput(cdata, out _return_value_);
                return Detail.Object_from_c<SignalSource>(_return_value_, Detail.easyar_SignalSource__typeName);
            }
        }
        ///<summary>
        ///Fetches the most recent `OutputFrame`_ .
        ///</summary>
        public virtual Optional<OutputFrame> peek()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfOutputFrame);
                Detail.easyar_OutputFrameBuffer_peek(cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<OutputFrame>(p.value, Detail.easyar_OutputFrame__typeName) : Optional<OutputFrame>.Empty);
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static OutputFrameBuffer create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrameBuffer_create(out _return_value_);
                return Detail.Object_from_c<OutputFrameBuffer>(_return_value_, Detail.easyar_OutputFrameBuffer__typeName);
            }
        }
        ///<summary>
        ///Pauses output of `OutputFrame`_ . After execution, all results of `OutputFrameBuffer.peek`_ will be empty. `OutputFrameBuffer.signalOutput`_  is not affected.
        ///</summary>
        public virtual void pause()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_OutputFrameBuffer_pause(cdata);
            }
        }
        ///<summary>
        ///Resumes output of `OutputFrame`_ .
        ///</summary>
        public virtual void resume()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_OutputFrameBuffer_resume(cdata);
            }
        }
    }

    ///<summary>
    ///Input frame to output frame adapter.
    ///There is an input frame input port and an output frame output port. It can be used to wrap an input frame into an output frame, which can be used for rendering without an algorithm component. Refer to `Overview <Overview.html>`_ .
    ///All members of this class is thread-safe.
    ///</summary>
    public class InputFrameToOutputFrameAdapter : RefBase
    {
        internal InputFrameToOutputFrameAdapter(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrameToOutputFrameAdapter(cdata_new, deleter_, retainer_);
        }
        public new InputFrameToOutputFrameAdapter Clone()
        {
            return (InputFrameToOutputFrameAdapter)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual InputFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToOutputFrameAdapter_input(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual OutputFrameSource output()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToOutputFrameAdapter_output(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSource>(_return_value_, Detail.easyar_OutputFrameSource__typeName);
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static InputFrameToOutputFrameAdapter create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToOutputFrameAdapter_create(out _return_value_);
                return Detail.Object_from_c<InputFrameToOutputFrameAdapter>(_return_value_, Detail.easyar_InputFrameToOutputFrameAdapter__typeName);
            }
        }
    }

    ///<summary>
    ///Input frame to feedback frame adapter.
    ///There is an input frame input port, a historic output frame input port and a feedback frame output port. It can be used to combine an input frame and a historic output frame into a feedback frame, which is required by algorithm components such as `ImageTracker`_ .
    ///On every input of an input frame, a feedback frame is generated with a previously input historic feedback frame. If there is no previously input historic feedback frame, it is null in the feedback frame.
    ///InputFrameToFeedbackFrameAdapter occupies one buffer of camera. Use setBufferCapacity of camera to set an amount of buffers that is not less than the sum of amount of buffers occupied by all components. Refer to `Overview <Overview.html>`_ .
    ///All members of this class is thread-safe.
    ///</summary>
    public class InputFrameToFeedbackFrameAdapter : RefBase
    {
        internal InputFrameToFeedbackFrameAdapter(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrameToFeedbackFrameAdapter(cdata_new, deleter_, retainer_);
        }
        public new InputFrameToFeedbackFrameAdapter Clone()
        {
            return (InputFrameToFeedbackFrameAdapter)(CloneObject());
        }
        ///<summary>
        ///Input port.
        ///</summary>
        public virtual InputFrameSink input()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToFeedbackFrameAdapter_input(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrameSink>(_return_value_, Detail.easyar_InputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Camera buffers occupied in this component.
        ///</summary>
        public virtual int bufferRequirement()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrameToFeedbackFrameAdapter_bufferRequirement(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Side input port for historic output frame input.
        ///</summary>
        public virtual OutputFrameSink sideInput()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToFeedbackFrameAdapter_sideInput(cdata, out _return_value_);
                return Detail.Object_from_c<OutputFrameSink>(_return_value_, Detail.easyar_OutputFrameSink__typeName);
            }
        }
        ///<summary>
        ///Output port.
        ///</summary>
        public virtual FeedbackFrameSource output()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToFeedbackFrameAdapter_output(cdata, out _return_value_);
                return Detail.Object_from_c<FeedbackFrameSource>(_return_value_, Detail.easyar_FeedbackFrameSource__typeName);
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static InputFrameToFeedbackFrameAdapter create()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrameToFeedbackFrameAdapter_create(out _return_value_);
                return Detail.Object_from_c<InputFrameToFeedbackFrameAdapter>(_return_value_, Detail.easyar_InputFrameToFeedbackFrameAdapter__typeName);
            }
        }
    }

    public class Engine
    {
        ///<summary>
        ///Gets the version schema hash, which can be used to ensure type declarations consistent with runtime library.
        ///</summary>
        public static int schemaHash()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Engine_schemaHash();
                return _return_value_;
            }
        }
        public static bool initialize(string key)
        {
            if (Detail.easyar_Engine_schemaHash() != -279124390)
            {
                throw new InvalidOperationException("SchemaHashNotMatched");
            }
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Engine_initialize(Detail.String_to_c(ar, key));
                return _return_value_;
            }
        }
        ///<summary>
        ///Handles the app onPause, pauses internal tasks.
        ///</summary>
        public static void onPause()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Engine_onPause();
            }
        }
        ///<summary>
        ///Handles the app onResume, resumes internal tasks.
        ///</summary>
        public static void onResume()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Engine_onResume();
            }
        }
        ///<summary>
        ///Gets error message on initialization failure.
        ///</summary>
        public static string errorMessage()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Engine_errorMessage(out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Gets the version number of EasyARSense.
        ///</summary>
        public static string versionString()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Engine_versionString(out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Gets the product name of EasyARSense. (Including variant, operating system and CPU architecture.)
        ///</summary>
        public static string name()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Engine_name(out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
    }

    ///<summary>
    ///Input frame.
    ///It includes image, camera parameters, timestamp, camera transform matrix against world coordinate system, and tracking status,
    ///among which, camera parameters, timestamp, camera transform matrix and tracking status are all optional, but specific algorithms may have special requirements on the input.
    ///</summary>
    public class InputFrame : RefBase
    {
        internal InputFrame(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new InputFrame(cdata_new, deleter_, retainer_);
        }
        public new InputFrame Clone()
        {
            return (InputFrame)(CloneObject());
        }
        ///<summary>
        ///Index, an automatic incremental value, which is different for every input frame.
        ///</summary>
        public virtual int index()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_index(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets image.
        ///</summary>
        public virtual Image image()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrame_image(cdata, out _return_value_);
                return Detail.Object_from_c<Image>(_return_value_, Detail.easyar_Image__typeName);
            }
        }
        ///<summary>
        ///Checks if there are camera parameters.
        ///</summary>
        public virtual bool hasCameraParameters()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_hasCameraParameters(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets camera parameters.
        ///</summary>
        public virtual CameraParameters cameraParameters()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrame_cameraParameters(cdata, out _return_value_);
                return Detail.Object_from_c<CameraParameters>(_return_value_, Detail.easyar_CameraParameters__typeName);
            }
        }
        ///<summary>
        ///Checks if there is temporal information (timestamp).
        ///</summary>
        public virtual bool hasTemporalInformation()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_hasTemporalInformation(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Timestamp.
        ///</summary>
        public virtual double timestamp()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_timestamp(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Checks if there is spatial information (cameraTransform and trackingStatus).
        ///</summary>
        public virtual bool hasSpatialInformation()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_hasSpatialInformation(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Camera transform matrix against world coordinate system. Camera coordinate system and world coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL's column-major.
        ///</summary>
        public virtual Matrix44F cameraTransform()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_cameraTransform(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets device motion tracking status: `MotionTrackingStatus`_ .
        ///</summary>
        public virtual MotionTrackingStatus trackingStatus()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_InputFrame_trackingStatus(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates an instance.
        ///</summary>
        public static InputFrame create(Image image, CameraParameters cameraParameters, double timestamp, Matrix44F cameraTransform, MotionTrackingStatus trackingStatus)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrame_create(image.cdata, cameraParameters.cdata, timestamp, cameraTransform, trackingStatus, out _return_value_);
                return Detail.Object_from_c<InputFrame>(_return_value_, Detail.easyar_InputFrame__typeName);
            }
        }
        ///<summary>
        ///Creates an instance with image, camera parameters, and timestamp.
        ///</summary>
        public static InputFrame createWithImageAndCameraParametersAndTemporal(Image image, CameraParameters cameraParameters, double timestamp)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrame_createWithImageAndCameraParametersAndTemporal(image.cdata, cameraParameters.cdata, timestamp, out _return_value_);
                return Detail.Object_from_c<InputFrame>(_return_value_, Detail.easyar_InputFrame__typeName);
            }
        }
        ///<summary>
        ///Creates an instance with image and camera parameters.
        ///</summary>
        public static InputFrame createWithImageAndCameraParameters(Image image, CameraParameters cameraParameters)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrame_createWithImageAndCameraParameters(image.cdata, cameraParameters.cdata, out _return_value_);
                return Detail.Object_from_c<InputFrame>(_return_value_, Detail.easyar_InputFrame__typeName);
            }
        }
        ///<summary>
        ///Creates an instance with image.
        ///</summary>
        public static InputFrame createWithImage(Image image)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_InputFrame_createWithImage(image.cdata, out _return_value_);
                return Detail.Object_from_c<InputFrame>(_return_value_, Detail.easyar_InputFrame__typeName);
            }
        }
    }

    ///<summary>
    ///FrameFilterResult is the base class for result classes of all synchronous algorithm components.
    ///</summary>
    public class FrameFilterResult : RefBase
    {
        internal FrameFilterResult(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new FrameFilterResult(cdata_new, deleter_, retainer_);
        }
        public new FrameFilterResult Clone()
        {
            return (FrameFilterResult)(CloneObject());
        }
    }

    ///<summary>
    ///Output frame.
    ///It includes input frame and results of synchronous components.
    ///</summary>
    public class OutputFrame : RefBase
    {
        internal OutputFrame(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new OutputFrame(cdata_new, deleter_, retainer_);
        }
        public new OutputFrame Clone()
        {
            return (OutputFrame)(CloneObject());
        }
        public OutputFrame(InputFrame inputFrame, List<Optional<FrameFilterResult>> results) : base(IntPtr.Zero, Detail.easyar_OutputFrame__dtor, Detail.easyar_OutputFrame__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_OutputFrame__ctor(inputFrame.cdata, Detail.ListOfOptionalOfFrameFilterResult_to_c(ar, results), out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Index, an automatic incremental value, which is different for every output frame.
        ///</summary>
        public virtual int index()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_OutputFrame_index(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Corresponding input frame.
        ///</summary>
        public virtual InputFrame inputFrame()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrame_inputFrame(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrame>(_return_value_, Detail.easyar_InputFrame__typeName);
            }
        }
        ///<summary>
        ///Results of synchronous components.
        ///</summary>
        public virtual List<Optional<FrameFilterResult>> results()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_OutputFrame_results(cdata, out _return_value_);
                return Detail.ListOfOptionalOfFrameFilterResult_from_c(ar, _return_value_);
            }
        }
    }

    ///<summary>
    ///Feedback frame.
    ///It includes an input frame and a historic output frame for use in feedback synchronous components such as `ImageTracker`_ .
    ///</summary>
    public class FeedbackFrame : RefBase
    {
        internal FeedbackFrame(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new FeedbackFrame(cdata_new, deleter_, retainer_);
        }
        public new FeedbackFrame Clone()
        {
            return (FeedbackFrame)(CloneObject());
        }
        public FeedbackFrame(InputFrame inputFrame, Optional<OutputFrame> previousOutputFrame) : base(IntPtr.Zero, Detail.easyar_FeedbackFrame__dtor, Detail.easyar_FeedbackFrame__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_FeedbackFrame__ctor(inputFrame.cdata, previousOutputFrame.map(p => p.OnSome ? new Detail.OptionalOfOutputFrame { has_value = true, value = p.Value.cdata } : new Detail.OptionalOfOutputFrame { has_value = false, value = default(IntPtr) }), out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Input frame.
        ///</summary>
        public virtual InputFrame inputFrame()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_FeedbackFrame_inputFrame(cdata, out _return_value_);
                return Detail.Object_from_c<InputFrame>(_return_value_, Detail.easyar_InputFrame__typeName);
            }
        }
        ///<summary>
        ///Historic output frame.
        ///</summary>
        public virtual Optional<OutputFrame> previousOutputFrame()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfOutputFrame);
                Detail.easyar_FeedbackFrame_previousOutputFrame(cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<OutputFrame>(p.value, Detail.easyar_OutputFrame__typeName) : Optional<OutputFrame>.Empty);
            }
        }
    }

    public enum PermissionStatus
    {
        ///<summary>
        ///Permission granted
        ///</summary>
        Granted = 0x00000000,
        ///<summary>
        ///Permission denied
        ///</summary>
        Denied = 0x00000001,
        ///<summary>
        ///A error happened while requesting permission.
        ///</summary>
        Error = 0x00000002,
    }

    ///<summary>
    ///StorageType represents where the images, jsons, videos or other files are located.
    ///StorageType specifies the root path, in all interfaces, you can use relative path relative to the root path.
    ///</summary>
    public enum StorageType
    {
        ///<summary>
        ///The app path.
        ///Android: the application's `persistent data directory <https://developer.android.google.cn/reference/android/content/pm/ApplicationInfo.html#dataDir>`_
        ///iOS: the application's sandbox directory
        ///Windows: Windows: the application's executable directory
        ///Mac: the application’s executable directory (if app is a bundle, this path is inside the bundle)
        ///</summary>
        App = 0,
        ///<summary>
        ///The assets path.
        ///Android: assets directory (inside apk)
        ///iOS: the application's executable directory
        ///Windows: EasyAR.dll directory
        ///Mac: libEasyAR.dylib directory
        ///**Note:** *this path is different if you are using Unity3D. It will point to the StreamingAssets folder.*
        ///</summary>
        Assets = 1,
        ///<summary>
        ///The absolute path (json/image path or video path) or url (video only).
        ///</summary>
        Absolute = 2,
    }

    ///<summary>
    ///Target is the base class for all targets that can be tracked by `ImageTracker`_ or other algorithms inside EasyAR.
    ///</summary>
    public class Target : RefBase
    {
        internal Target(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new Target(cdata_new, deleter_, retainer_);
        }
        public new Target Clone()
        {
            return (Target)(CloneObject());
        }
        ///<summary>
        ///Returns the target id. A target id is a integer number generated at runtime. This id is non-zero and increasing globally.
        ///</summary>
        public virtual int runtimeID()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Target_runtimeID(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the target uid. A target uid is useful in cloud based algorithms. If no cloud is used, you can set this uid in the json config as a alternative method to distinguish from targets.
        ///</summary>
        public virtual string uid()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Target_uid(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Returns the target name. Name is used to distinguish targets in a json file.
        ///</summary>
        public virtual string name()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Target_name(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Set name. It will erase previously set data or data from cloud.
        ///</summary>
        public virtual void setName(string name)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Target_setName(cdata, Detail.String_to_c(ar, name));
            }
        }
        ///<summary>
        ///Returns the meta data set by setMetaData. Or, in a cloud returned target, returns the meta data set in the cloud server.
        ///</summary>
        public virtual string meta()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Target_meta(cdata, out _return_value_);
                return Detail.String_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Set meta data. It will erase previously set data or data from cloud.
        ///</summary>
        public virtual void setMeta(string data)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Target_setMeta(cdata, Detail.String_to_c(ar, data));
            }
        }
    }

    public enum TargetStatus
    {
        ///<summary>
        ///The status is unknown.
        ///</summary>
        Unknown = 0,
        ///<summary>
        ///The status is undefined.
        ///</summary>
        Undefined = 1,
        ///<summary>
        ///The target is detected.
        ///</summary>
        Detected = 2,
        ///<summary>
        ///The target is tracked.
        ///</summary>
        Tracked = 3,
    }

    ///<summary>
    ///TargetInstance is the tracked target by trackers.
    ///An TargetInstance contains a raw `Target`_ that is tracked and current status and pose of the `Target`_ .
    ///</summary>
    public class TargetInstance : RefBase
    {
        internal TargetInstance(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new TargetInstance(cdata_new, deleter_, retainer_);
        }
        public new TargetInstance Clone()
        {
            return (TargetInstance)(CloneObject());
        }
        public TargetInstance() : base(IntPtr.Zero, Detail.easyar_TargetInstance__dtor, Detail.easyar_TargetInstance__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_TargetInstance__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Returns current status of the tracked target. Usually you can check if the status equals `TargetStatus.Tracked` to determine current status of the target.
        ///</summary>
        public virtual TargetStatus status()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_TargetInstance_status(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets the raw target. It will return the same `Target`_ you loaded into a tracker if it was previously loaded into the tracker.
        ///</summary>
        public virtual Optional<Target> target()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfTarget);
                Detail.easyar_TargetInstance_target(cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<Target>(p.value, Detail.easyar_Target__typeName) : Optional<Target>.Empty);
            }
        }
        ///<summary>
        ///Returns current pose of the tracked target. Camera coordinate system and target coordinate system are all right-handed. For the camera coordinate system, the origin is the optical center, x-right, y-up, and z in the direction of light going into camera. (The right and up, on mobile devices, is the right and up when the device is in the natural orientation.) The data arrangement is row-major, not like OpenGL's column-major.
        ///</summary>
        public virtual Matrix44F pose()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_TargetInstance_pose(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///TargetTrackerResult is the base class of `ImageTrackerResult`_ and `ObjectTrackerResult`_ .
    ///</summary>
    public class TargetTrackerResult : FrameFilterResult
    {
        internal TargetTrackerResult(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new TargetTrackerResult(cdata_new, deleter_, retainer_);
        }
        public new TargetTrackerResult Clone()
        {
            return (TargetTrackerResult)(CloneObject());
        }
        ///<summary>
        ///Returns the list of `TargetInstance`_ contained in the result.
        ///</summary>
        public virtual List<TargetInstance> targetInstances()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_TargetTrackerResult_targetInstances(cdata, out _return_value_);
                return Detail.ListOfTargetInstance_from_c(ar, _return_value_);
            }
        }
        ///<summary>
        ///Sets the list of `TargetInstance`_ contained in the result.
        ///</summary>
        public virtual void setTargetInstances(List<TargetInstance> instances)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_TargetTrackerResult_setTargetInstances(cdata, Detail.ListOfTargetInstance_to_c(ar, instances));
            }
        }
    }

    ///<summary>
    ///TextureId encapsulates a texture object in rendering API.
    ///For OpenGL/OpenGLES, getInt and fromInt shall be used. For Direct3D, getPointer and fromPointer shall be used.
    ///</summary>
    public class TextureId : RefBase
    {
        internal TextureId(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new TextureId(cdata_new, deleter_, retainer_);
        }
        public new TextureId Clone()
        {
            return (TextureId)(CloneObject());
        }
        ///<summary>
        ///Gets ID of an OpenGL/OpenGLES texture object.
        ///</summary>
        public virtual int getInt()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_TextureId_getInt(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Gets pointer of a Direct3D texture object.
        ///</summary>
        public virtual IntPtr getPointer()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_TextureId_getPointer(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates from ID of an OpenGL/OpenGLES texture object.
        ///</summary>
        public static TextureId fromInt(int @value)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_TextureId_fromInt(@value, out _return_value_);
                return Detail.Object_from_c<TextureId>(_return_value_, Detail.easyar_TextureId__typeName);
            }
        }
        ///<summary>
        ///Creates from pointer of a Direct3D texture object.
        ///</summary>
        public static TextureId fromPointer(IntPtr ptr)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_TextureId_fromPointer(ptr, out _return_value_);
                return Detail.Object_from_c<TextureId>(_return_value_, Detail.easyar_TextureId__typeName);
            }
        }
    }

    public enum VideoStatus
    {
        ///<summary>
        ///Status to indicate something wrong happen in video open or play.
        ///</summary>
        Error = -1,
        ///<summary>
        ///Status to show video finished open and is ready for play.
        ///</summary>
        Ready = 0,
        ///<summary>
        ///Status to indicate video finished play and reached the end.
        ///</summary>
        Completed = 1,
    }

    public enum VideoType
    {
        ///<summary>
        ///Normal video.
        ///</summary>
        Normal = 0,
        ///<summary>
        ///Transparent video, left half is the RGB channel and right half is alpha channel.
        ///</summary>
        TransparentSideBySide = 1,
        ///<summary>
        ///Transparent video, top half is the RGB channel and bottom half is alpha channel.
        ///</summary>
        TransparentTopAndBottom = 2,
    }

    ///<summary>
    ///VideoPlayer is the class for video playback.
    ///EasyAR supports normal videos, transparent videos and streaming videos. The video content will be rendered into a texture passed into the player through setRenderTexture.
    ///This class only supports OpenGLES2 texture.
    ///Due to the dependency to OpenGLES, every method in this class (including the destructor) has to be called in a single thread containing an OpenGLES context.
    ///Current version requires width and height being mutiples of 16.
    ///
    ///Supported video file formats
    ///Windows: Media Foundation-compatible formats, more can be supported via extra codecs. Please refer to `Supported Media Formats in Media Foundation <https://docs.microsoft.com/en-us/windows/win32/medfound/supported-media-formats-in-media-foundation>`__ . DirectShow is not supported.
    ///Mac: Not supported.
    ///Android: System supported formats. Please refer to `Supported media formats <https://developer.android.com/guide/topics/media/media-formats>`__ .
    ///iOS: System supported formats. There is no reference in effect currently.
    ///</summary>
    public class VideoPlayer : RefBase
    {
        internal VideoPlayer(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new VideoPlayer(cdata_new, deleter_, retainer_);
        }
        public new VideoPlayer Clone()
        {
            return (VideoPlayer)(CloneObject());
        }
        public VideoPlayer() : base(IntPtr.Zero, Detail.easyar_VideoPlayer__dtor, Detail.easyar_VideoPlayer__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_VideoPlayer__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Checks if the component is available. It returns true only on Windows, Android or iOS. It's not available on Mac.
        ///</summary>
        public static bool isAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_isAvailable();
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets the video type. The type will default to normal video if not set manually. It should be called before open.
        ///</summary>
        public virtual void setVideoType(VideoType videoType)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_setVideoType(cdata, videoType);
            }
        }
        ///<summary>
        ///Passes the texture to display video into player. It should be set before open.
        ///</summary>
        public virtual void setRenderTexture(TextureId texture)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_setRenderTexture(cdata, texture.cdata);
            }
        }
        ///<summary>
        ///Opens a video from path.
        ///path can be a local video file (path/to/video.mp4) or url (http://www.../.../video.mp4). storageType indicates the type of path. See `StorageType`_ for more description.
        ///This method is an asynchronous method. Open may take some time to finish. If you want to know the open result or the play status while playing, you have to handle callback. The callback will be called from a different thread. You can check if the open finished successfully and start play after a successful open.
        ///</summary>
        public virtual void open(string path, StorageType storageType, CallbackScheduler callbackScheduler, Optional<Action<VideoStatus>> callback)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_open(cdata, Detail.String_to_c(ar, path), storageType, callbackScheduler.cdata, callback.map(p => p.OnSome ? new Detail.OptionalOfFunctorOfVoidFromVideoStatus { has_value = true, value = Detail.FunctorOfVoidFromVideoStatus_to_c(p.Value) } : new Detail.OptionalOfFunctorOfVoidFromVideoStatus { has_value = false, value = default(Detail.FunctorOfVoidFromVideoStatus) }));
            }
        }
        ///<summary>
        ///Closes the video.
        ///</summary>
        public virtual void close()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_close(cdata);
            }
        }
        ///<summary>
        ///Starts or continues to play video.
        ///</summary>
        public virtual bool play()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_play(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Stops the video playback.
        ///</summary>
        public virtual void stop()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_stop(cdata);
            }
        }
        ///<summary>
        ///Pauses the video playback.
        ///</summary>
        public virtual void pause()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_pause(cdata);
            }
        }
        ///<summary>
        ///Checks whether video texture is ready for render. Use this to check if texture passed into the player has been touched.
        ///</summary>
        public virtual bool isRenderTextureAvailable()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_isRenderTextureAvailable(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Updates texture data. This should be called in the renderer thread when isRenderTextureAvailable returns true.
        ///</summary>
        public virtual void updateFrame()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_VideoPlayer_updateFrame(cdata);
            }
        }
        ///<summary>
        ///Returns the video duration. Use after a successful open.
        ///</summary>
        public virtual int duration()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_duration(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the current position of video. Use after a successful open.
        ///</summary>
        public virtual int currentPosition()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_currentPosition(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Seeks to play to position . Use after a successful open.
        ///</summary>
        public virtual bool seek(int position)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_seek(cdata, position);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns the video size. Use after a successful open.
        ///</summary>
        public virtual Vec2I size()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_size(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns current volume. Use after a successful open.
        ///</summary>
        public virtual float volume()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_volume(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Sets volume of the video. Use after a successful open.
        ///</summary>
        public virtual bool setVolume(float volume)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_VideoPlayer_setVolume(cdata, volume);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///Buffer stores a raw byte array, which can be used to access image data.
    ///To access image data in Java API, get buffer from `Image`_ and copy to a Java byte array.
    ///You can always access image data since the first version of EasyAR Sense. Refer to `Image`_ .
    ///</summary>
    public class Buffer : RefBase
    {
        internal Buffer(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new Buffer(cdata_new, deleter_, retainer_);
        }
        public new Buffer Clone()
        {
            return (Buffer)(CloneObject());
        }
        ///<summary>
        ///Wraps a raw memory block. When Buffer is released by all holders, deleter callback will be invoked to execute user-defined memory destruction. deleter must be thread-safe.
        ///</summary>
        public static Buffer wrap(IntPtr ptr, int size, Action deleter)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Buffer_wrap(ptr, size, Detail.FunctorOfVoid_to_c(deleter), out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Creates a Buffer of specified byte size.
        ///</summary>
        public static Buffer create(int size)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Buffer_create(size, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Returns raw data address.
        ///</summary>
        public virtual IntPtr data()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Buffer_data(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Byte size of raw data.
        ///</summary>
        public virtual int size()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Buffer_size(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Copies raw memory. It can be used in languages or platforms without complete support for memory operations.
        ///</summary>
        public static void memoryCopy(IntPtr src, IntPtr dest, int length)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Buffer_memoryCopy(src, dest, length);
            }
        }
        ///<summary>
        ///Tries to copy data from a raw memory address into Buffer. If copy succeeds, it returns true, or else it returns false. Possible failure causes includes: source or destination data range overflow.
        ///</summary>
        public virtual bool tryCopyFrom(IntPtr src, int srcIndex, int index, int length)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Buffer_tryCopyFrom(cdata, src, srcIndex, index, length);
                return _return_value_;
            }
        }
        ///<summary>
        ///Copies buffer data to user array.
        ///</summary>
        public virtual bool tryCopyTo(int index, IntPtr dest, int destIndex, int length)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Buffer_tryCopyTo(cdata, index, dest, destIndex, length);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates a sub-buffer with a reference to the original Buffer. A Buffer will only be released after all its sub-buffers are released.
        ///</summary>
        public virtual Buffer partition(int index, int length)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Buffer_partition(cdata, index, length, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        public static Buffer wrapByteArray(byte[] bytes)
        {
            var Length = bytes.Length;
            var h = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            return Buffer.wrap(h.AddrOfPinnedObject(), Length, () => h.Free());
        }
        public static Buffer wrapByteArray(byte[] bytes, int index, int length)
        {
            return wrapByteArray(bytes, index, length, () => { });
        }
        public static Buffer wrapByteArray(byte[] bytes, int index, int length, Action deleter)
        {
            if ((length < 0) || (index < 0) || (index > bytes.Length) || (index + length > bytes.Length))
            {
                throw new ArgumentException("BufferRangeOverflow");
            }
            var h = GCHandle.Alloc(bytes, GCHandleType.Pinned);
            var ptr = new IntPtr(h.AddrOfPinnedObject().ToInt64() + index);
            return Buffer.wrap(ptr, length, () =>
            {
                h.Free();
                if (deleter != null)
                {
                    deleter();
                }
            });
        }
        public void copyFromByteArray(byte[] src)
        {
            copyFromByteArray(src, 0, 0, src.Length);
        }
        public void copyFromByteArray(byte[] src, int srcIndex, int index, int length)
        {
            var srcSize = src.Length;
            var destSize = size();
            if ((length < 0) || (srcIndex < 0) || (srcIndex > srcSize) || (srcIndex + length > srcSize) || (index < 0) || (index > destSize) || (index + length > destSize))
            {
                throw new ArgumentException("BufferRangeOverflow");
            }
            Marshal.Copy(src, srcIndex, data(), length);
        }
        public void copyToByteArray(byte[] dest)
        {
            copyToByteArray(0, dest, 0, size());
        }
        public void copyToByteArray(int index, byte[] dest, int destIndex, int length)
        {
            var srcSize = size();
            var destSize = dest.Length;
            if ((length < 0) || (index < 0) || (index > srcSize) || (index + length > srcSize) || (destIndex < 0) || (destIndex > destSize) || (destIndex + length > destSize))
            {
                throw new ArgumentException("BufferRangeOverflow");
            }
            var ptr = new IntPtr(data().ToInt64() + index);
            Marshal.Copy(ptr, dest, destIndex, length);
        }
    }

    ///<summary>
    ///A mapping from file path to `Buffer`_ . It can be used to represent multiple files in the memory.
    ///</summary>
    public class BufferDictionary : RefBase
    {
        internal BufferDictionary(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new BufferDictionary(cdata_new, deleter_, retainer_);
        }
        public new BufferDictionary Clone()
        {
            return (BufferDictionary)(CloneObject());
        }
        public BufferDictionary() : base(IntPtr.Zero, Detail.easyar_BufferDictionary__dtor, Detail.easyar_BufferDictionary__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_BufferDictionary__ctor(out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Current file count.
        ///</summary>
        public virtual int count()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_BufferDictionary_count(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Checks if a specified path is in the dictionary.
        ///</summary>
        public virtual bool contains(string path)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_BufferDictionary_contains(cdata, Detail.String_to_c(ar, path));
                return _return_value_;
            }
        }
        ///<summary>
        ///Tries to get the corresponding `Buffer`_ for a specified path.
        ///</summary>
        public virtual Optional<Buffer> tryGet(string path)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfBuffer);
                Detail.easyar_BufferDictionary_tryGet(cdata, Detail.String_to_c(ar, path), out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<Buffer>(p.value, Detail.easyar_Buffer__typeName) : Optional<Buffer>.Empty);
            }
        }
        ///<summary>
        ///Sets `Buffer`_ for a specified path.
        ///</summary>
        public virtual void @set(string path, Buffer buffer)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_BufferDictionary_set(cdata, Detail.String_to_c(ar, path), buffer.cdata);
            }
        }
        ///<summary>
        ///Removes a specified path.
        ///</summary>
        public virtual bool remove(string path)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_BufferDictionary_remove(cdata, Detail.String_to_c(ar, path));
                return _return_value_;
            }
        }
        ///<summary>
        ///Clears the dictionary.
        ///</summary>
        public virtual void clear()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_BufferDictionary_clear(cdata);
            }
        }
    }

    ///<summary>
    ///BufferPool is a memory pool to reduce memory allocation time consumption for functionality like custom camera interoperability, which needs to allocate memory buffers of a fixed size repeatedly.
    ///</summary>
    public class BufferPool : RefBase
    {
        internal BufferPool(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new BufferPool(cdata_new, deleter_, retainer_);
        }
        public new BufferPool Clone()
        {
            return (BufferPool)(CloneObject());
        }
        ///<summary>
        ///block_size is the byte size of each `Buffer`_ .
        ///capacity is the maximum count of `Buffer`_ .
        ///</summary>
        public BufferPool(int block_size, int capacity) : base(IntPtr.Zero, Detail.easyar_BufferPool__dtor, Detail.easyar_BufferPool__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_BufferPool__ctor(block_size, capacity, out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///The byte size of each `Buffer`_ .
        ///</summary>
        public virtual int block_size()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_BufferPool_block_size(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///The maximum count of `Buffer`_ .
        ///</summary>
        public virtual int capacity()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_BufferPool_capacity(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Current acquired count of `Buffer`_ .
        ///</summary>
        public virtual int size()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_BufferPool_size(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Tries to acquire a memory block. If current acquired count of `Buffer`_ does not reach maximum, a new `Buffer`_ is fetched or allocated, or else null is returned.
        ///</summary>
        public virtual Optional<Buffer> tryAcquire()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(Detail.OptionalOfBuffer);
                Detail.easyar_BufferPool_tryAcquire(cdata, out _return_value_);
                return _return_value_.map(p => p.has_value ? Detail.Object_from_c<Buffer>(p.value, Detail.easyar_Buffer__typeName) : Optional<Buffer>.Empty);
            }
        }
    }

    public enum CameraDeviceType
    {
        ///<summary>
        ///Unknown location
        ///</summary>
        Unknown = 0,
        ///<summary>
        ///Rear camera
        ///</summary>
        Back = 1,
        ///<summary>
        ///Front camera
        ///</summary>
        Front = 2,
    }

    ///<summary>
    ///MotionTrackingStatus describes the quality of device motion tracking.
    ///</summary>
    public enum MotionTrackingStatus
    {
        ///<summary>
        ///Result is not available and should not to be used to render virtual objects or do 3D reconstruction. This value occurs temporarily after initializing, tracking lost or relocalizing.
        ///</summary>
        NotTracking = 0,
        ///<summary>
        ///Tracking is available, but the quality of the result is not good enough. This value occurs temporarily due to weak texture or excessive movement. The result can be used to render virtual objects, but should generally not be used to do 3D reconstruction.
        ///</summary>
        Limited = 1,
        ///<summary>
        ///Tracking with a good quality. The result can be used to render virtual objects or do 3D reconstruction.
        ///</summary>
        Tracking = 2,
    }

    ///<summary>
    ///Camera parameters, including image size, focal length, principal point, camera type and camera rotation against natural orientation.
    ///</summary>
    public class CameraParameters : RefBase
    {
        internal CameraParameters(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new CameraParameters(cdata_new, deleter_, retainer_);
        }
        public new CameraParameters Clone()
        {
            return (CameraParameters)(CloneObject());
        }
        public CameraParameters(Vec2I size, Vec2F focalLength, Vec2F principalPoint, CameraDeviceType cameraDeviceType, int cameraOrientation) : base(IntPtr.Zero, Detail.easyar_CameraParameters__dtor, Detail.easyar_CameraParameters__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_CameraParameters__ctor(size, focalLength, principalPoint, cameraDeviceType, cameraOrientation, out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Image size.
        ///</summary>
        public virtual Vec2I size()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_size(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Focal length, the distance from effective optical center to CCD plane, divided by unit pixel density in width and height directions. The unit is pixel.
        ///</summary>
        public virtual Vec2F focalLength()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_focalLength(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Principal point, coordinates of the intersection point of principal axis on CCD plane against the left-top corner of the image. The unit is pixel.
        ///</summary>
        public virtual Vec2F principalPoint()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_principalPoint(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Camera device type. Default, back or front camera. On desktop devices, there are only default cameras. On mobile devices, there is a differentiation between back and front cameras.
        ///</summary>
        public virtual CameraDeviceType cameraDeviceType()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_cameraDeviceType(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Camera rotation against device natural orientation.
        ///For Android phones and some Android tablets, this value is 90 degrees.
        ///For Android eye-wear and some Android tablets, this value is 0 degrees.
        ///For all current iOS devices, this value is 90 degrees.
        ///</summary>
        public virtual int cameraOrientation()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_cameraOrientation(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Creates CameraParameters with default camera intrinsics. Default intrinsics are calculated by image size, which is not very precise.
        ///</summary>
        public static CameraParameters createWithDefaultIntrinsics(Vec2I size, CameraDeviceType cameraDeviceType, int cameraOrientation)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_CameraParameters_createWithDefaultIntrinsics(size, cameraDeviceType, cameraOrientation, out _return_value_);
                return Detail.Object_from_c<CameraParameters>(_return_value_, Detail.easyar_CameraParameters__typeName);
            }
        }
        ///<summary>
        ///Calculates the angle required to rotate the camera image clockwise to align it with the screen.
        ///screenRotation is the angle of rotation of displaying screen image against device natural orientation in clockwise in degrees.
        ///For iOS(UIInterfaceOrientationPortrait as natural orientation):
        ///* UIInterfaceOrientationPortrait: rotation = 0
        ///* UIInterfaceOrientationLandscapeRight: rotation = 90
        ///* UIInterfaceOrientationPortraitUpsideDown: rotation = 180
        ///* UIInterfaceOrientationLandscapeLeft: rotation = 270
        ///For Android:
        ///* Surface.ROTATION_0 = 0
        ///* Surface.ROTATION_90 = 90
        ///* Surface.ROTATION_180 = 180
        ///* Surface.ROTATION_270 = 270
        ///</summary>
        public virtual int imageOrientation(int screenRotation)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_imageOrientation(cdata, screenRotation);
                return _return_value_;
            }
        }
        ///<summary>
        ///Calculates whether the image needed to be flipped horizontally. The image is rotated, then flipped in rendering. When cameraDeviceType is front, a flip is automatically applied. Pass manualHorizontalFlip with true to add a manual flip.
        ///</summary>
        public virtual bool imageHorizontalFlip(bool manualHorizontalFlip)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_imageHorizontalFlip(cdata, manualHorizontalFlip);
                return _return_value_;
            }
        }
        ///<summary>
        ///Calculates the perspective projection matrix needed by virtual object rendering. The projection transforms points from camera coordinate system to clip coordinate system ([-1, 1]^4). The form of perspective projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL's column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL's default.
        ///</summary>
        public virtual Matrix44F projection(float nearPlane, float farPlane, float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_projection(cdata, nearPlane, farPlane, viewportAspectRatio, screenRotation, combiningFlip, manualHorizontalFlip);
                return _return_value_;
            }
        }
        ///<summary>
        ///Calculates the orthogonal projection matrix needed by camera background rendering. The projection transforms points from image quad coordinate system ([-1, 1]^2) to clip coordinate system ([-1, 1]^4), with the undefined two dimensions unchanged. The form of orthogonal projection matrix is the same as OpenGL, that matrix multiply column vector of homogeneous coordinates of point on the right, ant not like Direct3D, that matrix multiply row vector of homogeneous coordinates of point on the left. But data arrangement is row-major, not like OpenGL's column-major. Clip coordinate system and normalized device coordinate system are defined as the same as OpenGL's default.
        ///</summary>
        public virtual Matrix44F imageProjection(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_imageProjection(cdata, viewportAspectRatio, screenRotation, combiningFlip, manualHorizontalFlip);
                return _return_value_;
            }
        }
        ///<summary>
        ///Transforms points from image coordinate system ([0, 1]^2) to screen coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
        ///</summary>
        public virtual Vec2F screenCoordinatesFromImageCoordinates(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, Vec2F imageCoordinates)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_screenCoordinatesFromImageCoordinates(cdata, viewportAspectRatio, screenRotation, combiningFlip, manualHorizontalFlip, imageCoordinates);
                return _return_value_;
            }
        }
        ///<summary>
        ///Transforms points from screen coordinate system ([0, 1]^2) to image coordinate system ([0, 1]^2). Both coordinate system is x-left, y-down, with origin at left-top.
        ///</summary>
        public virtual Vec2F imageCoordinatesFromScreenCoordinates(float viewportAspectRatio, int screenRotation, bool combiningFlip, bool manualHorizontalFlip, Vec2F screenCoordinates)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_imageCoordinatesFromScreenCoordinates(cdata, viewportAspectRatio, screenRotation, combiningFlip, manualHorizontalFlip, screenCoordinates);
                return _return_value_;
            }
        }
        ///<summary>
        ///Checks if two groups of parameters are equal.
        ///</summary>
        public virtual bool equalsTo(CameraParameters other)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_CameraParameters_equalsTo(cdata, other.cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///PixelFormat represents the format of image pixel data. All formats follow the pixel direction from left to right and from top to bottom.
    ///</summary>
    public enum PixelFormat
    {
        ///<summary>
        ///Unknown
        ///</summary>
        Unknown = 0,
        ///<summary>
        ///256 shades grayscale
        ///</summary>
        Gray = 1,
        ///<summary>
        ///YUV_NV21
        ///</summary>
        YUV_NV21 = 2,
        ///<summary>
        ///YUV_NV12
        ///</summary>
        YUV_NV12 = 3,
        ///<summary>
        ///YUV_I420
        ///</summary>
        YUV_I420 = 4,
        ///<summary>
        ///YUV_YV12
        ///</summary>
        YUV_YV12 = 5,
        ///<summary>
        ///RGB888
        ///</summary>
        RGB888 = 6,
        ///<summary>
        ///BGR888
        ///</summary>
        BGR888 = 7,
        ///<summary>
        ///RGBA8888
        ///</summary>
        RGBA8888 = 8,
        ///<summary>
        ///BGRA8888
        ///</summary>
        BGRA8888 = 9,
    }

    ///<summary>
    ///Image stores an image data and represents an image in memory.
    ///Image raw data can be accessed as byte array. The width/height/etc information are also accessible.
    ///You can always access image data since the first version of EasyAR Sense.
    ///
    ///You can do this in iOS
    ///::
    ///
    ///    #import <easyar/buffer.oc.h>
    ///    #import <easyar/image.oc.h>
    ///
    ///    easyar_OutputFrame * outputFrame = [outputFrameBuffer peek];
    ///    if (outputFrame != nil) {
    ///        easyar_Image * i = [[outputFrame inputFrame] image];
    ///        easyar_Buffer * b = [i buffer];
    ///        char * bytes = calloc([b size], 1);
    ///        memcpy(bytes, [b data], [b size]);
    ///        // use bytes here
    ///        free(bytes);
    ///    }
    ///
    ///Or in Android
    ///::
    ///
    ///    import cn.easyar.*;
    ///
    ///    OutputFrame outputFrame = outputFrameBuffer.peek();
    ///    if (outputFrame != null) {
    ///        InputFrame inputFrame = outputFrame.inputFrame();
    ///        Image i = inputFrame.image();
    ///        Buffer b = i.buffer();
    ///        byte[] bytes = new byte[b.size()];
    ///        b.copyToByteArray(0, bytes, 0, bytes.length);
    ///        // use bytes here
    ///        b.dispose();
    ///        i.dispose();
    ///        inputFrame.dispose();
    ///        outputFrame.dispose();
    ///    }
    ///</summary>
    public class Image : RefBase
    {
        internal Image(IntPtr cdata, Action<IntPtr> deleter, Retainer retainer) : base(cdata, deleter, retainer)
        {
        }
        protected override object CloneObject()
        {
            var cdata_new = IntPtr.Zero;
            if (retainer_ != null) { retainer_(cdata, out cdata_new); }
            return new Image(cdata_new, deleter_, retainer_);
        }
        public new Image Clone()
        {
            return (Image)(CloneObject());
        }
        public Image(Buffer buffer, PixelFormat format, int width, int height) : base(IntPtr.Zero, Detail.easyar_Image__dtor, Detail.easyar_Image__retain)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = IntPtr.Zero;
                Detail.easyar_Image__ctor(buffer.cdata, format, width, height, out _return_value_);
                cdata_ = _return_value_;
            }
        }
        ///<summary>
        ///Returns buffer inside image. It can be used to access internal data of image. The content of `Buffer`_ shall not be modified, as they may be accessed from other threads.
        ///</summary>
        public virtual Buffer buffer()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_Image_buffer(cdata, out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Returns image format.
        ///</summary>
        public virtual PixelFormat format()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Image_format(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns image width.
        ///</summary>
        public virtual int width()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Image_width(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Returns image height.
        ///</summary>
        public virtual int height()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Image_height(cdata);
                return _return_value_;
            }
        }
        ///<summary>
        ///Checks if the image is empty.
        ///</summary>
        public virtual bool empty()
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = Detail.easyar_Image_empty(cdata);
                return _return_value_;
            }
        }
    }

    ///<summary>
    ///JNI utility class.
    ///It is used in Unity to wrap Java byte array and ByteBuffer.
    ///It is not supported on iOS.
    ///</summary>
    public class JniUtility
    {
        ///<summary>
        ///Wraps Java's byte[]。
        ///</summary>
        public static Buffer wrapByteArray(IntPtr bytes, bool readOnly, Action deleter)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_JniUtility_wrapByteArray(bytes, readOnly, Detail.FunctorOfVoid_to_c(deleter), out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
        ///<summary>
        ///Wraps Java's java.nio.ByteBuffer, which must be a direct buffer.
        ///</summary>
        public static Buffer wrapBuffer(IntPtr directBuffer, Action deleter)
        {
            using (var ar = new Detail.AutoRelease())
            {
                var _return_value_ = default(IntPtr);
                Detail.easyar_JniUtility_wrapBuffer(directBuffer, Detail.FunctorOfVoid_to_c(deleter), out _return_value_);
                return Detail.Object_from_c<Buffer>(_return_value_, Detail.easyar_Buffer__typeName);
            }
        }
    }

    public enum LogLevel
    {
        ///<summary>
        ///Error
        ///</summary>
        Error = 0,
        ///<summary>
        ///Warning
        ///</summary>
        Warning = 1,
        ///<summary>
        ///Information
        ///</summary>
        Info = 2,
    }

    ///<summary>
    ///Log class.
    ///It is used to setup a custom log output function.
    ///</summary>
    public class Log
    {
        ///<summary>
        ///Sets custom log output function.
        ///</summary>
        public static void setLogFunc(Action<LogLevel, string> func)
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Log_setLogFunc(Detail.FunctorOfVoidFromLogLevelAndString_to_c(func));
            }
        }
        ///<summary>
        ///Clears custom log output function and reverts to default log output function.
        ///</summary>
        public static void resetLogFunc()
        {
            using (var ar = new Detail.AutoRelease())
            {
                Detail.easyar_Log_resetLogFunc();
            }
        }
    }

    ///<summary>
    ///Square matrix of 4. The data arrangement is row-major.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix44F
    {
        ///<summary>
        ///The raw data of matrix.
        ///</summary>
        public float data_0;
        public float data_1;
        public float data_2;
        public float data_3;
        public float data_4;
        public float data_5;
        public float data_6;
        public float data_7;
        public float data_8;
        public float data_9;
        public float data_10;
        public float data_11;
        public float data_12;
        public float data_13;
        public float data_14;
        public float data_15;
        public float[] data
        {
            get
            {
                return new float[] { data_0, data_1, data_2, data_3, data_4, data_5, data_6, data_7, data_8, data_9, data_10, data_11, data_12, data_13, data_14, data_15 };
            }
            set
            {
                if (value.Length != 16) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
                this.data_2 = value[2];
                this.data_3 = value[3];
                this.data_4 = value[4];
                this.data_5 = value[5];
                this.data_6 = value[6];
                this.data_7 = value[7];
                this.data_8 = value[8];
                this.data_9 = value[9];
                this.data_10 = value[10];
                this.data_11 = value[11];
                this.data_12 = value[12];
                this.data_13 = value[13];
                this.data_14 = value[14];
                this.data_15 = value[15];
            }
        }

        public Matrix44F(float data_0, float data_1, float data_2, float data_3, float data_4, float data_5, float data_6, float data_7, float data_8, float data_9, float data_10, float data_11, float data_12, float data_13, float data_14, float data_15)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
            this.data_2 = data_2;
            this.data_3 = data_3;
            this.data_4 = data_4;
            this.data_5 = data_5;
            this.data_6 = data_6;
            this.data_7 = data_7;
            this.data_8 = data_8;
            this.data_9 = data_9;
            this.data_10 = data_10;
            this.data_11 = data_11;
            this.data_12 = data_12;
            this.data_13 = data_13;
            this.data_14 = data_14;
            this.data_15 = data_15;
        }
    }

    ///<summary>
    ///Square matrix of 3. The data arrangement is row-major.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix33F
    {
        ///<summary>
        ///The raw data of matrix.
        ///</summary>
        public float data_0;
        public float data_1;
        public float data_2;
        public float data_3;
        public float data_4;
        public float data_5;
        public float data_6;
        public float data_7;
        public float data_8;
        public float[] data
        {
            get
            {
                return new float[] { data_0, data_1, data_2, data_3, data_4, data_5, data_6, data_7, data_8 };
            }
            set
            {
                if (value.Length != 9) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
                this.data_2 = value[2];
                this.data_3 = value[3];
                this.data_4 = value[4];
                this.data_5 = value[5];
                this.data_6 = value[6];
                this.data_7 = value[7];
                this.data_8 = value[8];
            }
        }

        public Matrix33F(float data_0, float data_1, float data_2, float data_3, float data_4, float data_5, float data_6, float data_7, float data_8)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
            this.data_2 = data_2;
            this.data_3 = data_3;
            this.data_4 = data_4;
            this.data_5 = data_5;
            this.data_6 = data_6;
            this.data_7 = data_7;
            this.data_8 = data_8;
        }
    }

    ///<summary>
    ///4 dimensional vector of float.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Vec4F
    {
        ///<summary>
        ///The raw data of vector.
        ///</summary>
        public float data_0;
        public float data_1;
        public float data_2;
        public float data_3;
        public float[] data
        {
            get
            {
                return new float[] { data_0, data_1, data_2, data_3 };
            }
            set
            {
                if (value.Length != 4) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
                this.data_2 = value[2];
                this.data_3 = value[3];
            }
        }

        public Vec4F(float data_0, float data_1, float data_2, float data_3)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
            this.data_2 = data_2;
            this.data_3 = data_3;
        }
    }

    ///<summary>
    ///3 dimensional vector of float.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Vec3F
    {
        ///<summary>
        ///The raw data of vector.
        ///</summary>
        public float data_0;
        public float data_1;
        public float data_2;
        public float[] data
        {
            get
            {
                return new float[] { data_0, data_1, data_2 };
            }
            set
            {
                if (value.Length != 3) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
                this.data_2 = value[2];
            }
        }

        public Vec3F(float data_0, float data_1, float data_2)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
            this.data_2 = data_2;
        }
    }

    ///<summary>
    ///2 dimensional vector of float.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Vec2F
    {
        ///<summary>
        ///The raw data of vector.
        ///</summary>
        public float data_0;
        public float data_1;
        public float[] data
        {
            get
            {
                return new float[] { data_0, data_1 };
            }
            set
            {
                if (value.Length != 2) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
            }
        }

        public Vec2F(float data_0, float data_1)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
        }
    }

    ///<summary>
    ///4 dimensional vector of int.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Vec4I
    {
        ///<summary>
        ///The raw data of vector.
        ///</summary>
        public int data_0;
        public int data_1;
        public int data_2;
        public int data_3;
        public int[] data
        {
            get
            {
                return new int[] { data_0, data_1, data_2, data_3 };
            }
            set
            {
                if (value.Length != 4) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
                this.data_2 = value[2];
                this.data_3 = value[3];
            }
        }

        public Vec4I(int data_0, int data_1, int data_2, int data_3)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
            this.data_2 = data_2;
            this.data_3 = data_3;
        }
    }

    ///<summary>
    ///2 dimensional vector of int.
    ///</summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct Vec2I
    {
        ///<summary>
        ///The raw data of vector.
        ///</summary>
        public int data_0;
        public int data_1;
        public int[] data
        {
            get
            {
                return new int[] { data_0, data_1 };
            }
            set
            {
                if (value.Length != 2) { throw new ArgumentException(); }
                this.data_0 = value[0];
                this.data_1 = value[1];
            }
        }

        public Vec2I(int data_0, int data_1)
        {
            this.data_0 = data_0;
            this.data_1 = data_1;
        }
    }

}