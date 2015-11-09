// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
    public class Camera : Component
    {
        public enum ProjectionType
        {
            Perspective = 0,
            Orthographic
        }

        public ProjectionType Type
        {
            get { return Camera_GetProjectionType(Pointer); }
            set { Camera_SetProjectionType(Pointer, value); }
        }

        public float FieldOfView
        {
            get { return Camera_GetFieldOfView(Pointer); }
            set { Camera_SetFieldOfView(Pointer, value); }
        }

        public Vector2 TargetSize
        {
            get { return Camera_GetTargetSize(Pointer); }
        }
        public float AspectRatio
        {
            get { return Camera_GetAspectRatio(Pointer); }
        }

        public float NearClipDistance
        {
            get { return Camera_GetNearClipDistance(Pointer); }
            set { Camera_SetNearClipDistance(Pointer, value); }
        }

        public float FarClipDistance
        {
            get { return Camera_GetFarClipDistance(Pointer); }
            set { Camera_SetFarClipDistance(Pointer, value); }
        }

        public Colour ClearColour
        {
            get { return Camera_GetClearColour(Pointer); }
            set { Camera_SetClearColour(Pointer, value); }
        }

        public uint CompositesCount
        {
            get { return Camera_GetCompositesCount(Pointer); }
        }

        public void AddComposite(Composite Composite, int Index = -1)
        {
            Camera_AddComposite(Pointer, Composite.Pointer, Index);
        }

        public void RemoveComposite(Composite Composite)
        {
            Camera_RemoveComposite(Pointer, Composite.Pointer);
        }

        public void RemoveCompositeAt(uint Index)
        {
            Camera_RemoveCompositeAt(Pointer, Index);
        }

        public Composite GetComposite(uint Index)
        {
            return WrapperObject.GetObject<Composite>(Camera_GetComposite(Pointer, Index));
        }

        //public Matrix4 ViewMatrix
        //{
        //	get { return (Matrix4)Marshal.PtrToStructure(Camera_GetViewMatrix(Pointer), typeof(Matrix4)); }
        //}

        //public Matrix4 ProjectionMatrix
        //{
        //	get { return (Matrix4)Marshal.PtrToStructure(Camera_GetProjectionMatrix(Pointer), typeof(Matrix4)); }
        //}

        //public Matrix4 ViewProjectionMatrix
        //{
        //	get { return (Matrix4)Marshal.PtrToStructure(Camera_GetViewProjectionMatrix(Pointer), typeof(Matrix4)); }
        //}

        public Camera(IntPtr Pointer) :
            base(Pointer)
        {
        }

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern ProjectionType Camera_GetProjectionType(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_SetProjectionType(IntPtr Camera, ProjectionType Value);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern float Camera_GetFieldOfView(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_SetFieldOfView(IntPtr Camera, float Value);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern Vector2 Camera_GetTargetSize(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern float Camera_GetAspectRatio(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern float Camera_GetNearClipDistance(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_SetNearClipDistance(IntPtr Camera, float Value);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern float Camera_GetFarClipDistance(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_SetFarClipDistance(IntPtr Camera, float Value);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern Colour Camera_GetClearColour(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_SetClearColour(IntPtr Camera, Colour Value);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern Matrix4 Camera_GetViewMatrix(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern Matrix4 Camera_GetProjectionMatrix(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern Matrix4 Camera_GetViewProjectionMatrix(IntPtr Camera);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_AddComposite(IntPtr Camera, IntPtr Composite, int Index);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_RemoveComposite(IntPtr Camera, IntPtr Composite);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_RemoveCompositeAt(IntPtr Camera, uint Index);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Camera_GetComposite(IntPtr Camera, uint Index);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Camera_GetCompositesCount(IntPtr Camera);
    }
}
