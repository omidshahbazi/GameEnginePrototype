// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
    public class GameObject : WrapperObject
    {
        public enum FindComponentOption
        {
            Actives = 0,
            Deactives,
            All
        }

        private Transform transform;

        public Scene Holder
        {
            get { return WrapperObject.GetObject<Scene>(GameObject_GetHolder(Pointer)); }
        }

        public string Name
        {
            get { return GameObject_GetName(Pointer); }
            set { GameObject_SetName(Pointer, value); }
        }

        public uint Tag
        {
            get { return GameObject_GetTag(Pointer); }
            set { GameObject_SetTag(Pointer, value); }
        }

        public bool Visible
        {
            get { return GameObject_GetVisible(Pointer); }
            set { GameObject_SetVisible(Pointer, value); }
        }

        public Transform Transform
        {
            get { return transform; }
        }

        public GameObject(IntPtr Pointer, string Name) :
            base(Pointer)
        {
            transform = new Transform(GameObject_GetTransform(Pointer));
        }

        protected override bool OnDestroy()
        {
			Holder.DestroyGameObject(this);

            return true;
        }

        public T AddComponent<T>() where T : Component
        {
            return (T)AddComponentCore(typeof(T).Name);
        }
        public Component AddComponent(string TypeName)
        {
            return AddComponentCore(TypeName);
        }

        public T GetComponent<T>(FindComponentOption Option = FindComponentOption.Actives) where T : Component
        {
            return (T)GetComponentCore(typeof(T).Name, Option);
        }
        public Component GetComponent(string TypeName, FindComponentOption Option = FindComponentOption.Actives)
        {
            return GetComponentCore(TypeName, Option);
        }

        private Component AddComponentCore(string TypeName)
        {
            return CreateComponentCore(TypeName, GameObject_AddComponent(Pointer, TypeName));
        }

        private Component GetComponentCore(string TypeName, FindComponentOption Option)
        {
            return WrapperObject.GetObject<Component>(GameObject_GetComponent(Pointer, TypeName, Option));
        }

        private Component CreateComponentCore(string TypeName, IntPtr Pointer)
        {
            Component com = null;

            if (TypeName == typeof(Camera).Name)
                com = new Camera(Pointer);
            else if (TypeName == typeof(Renderer).Name)
                com = new Renderer(Pointer);
            else
                com = new Component(Pointer);

            return com;
        }

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GameObject_AddComponent(IntPtr GameObject, [MarshalAs(UnmanagedType.BStr)] string TypeName);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GameObject_GetComponent(IntPtr GameObject, [MarshalAs(UnmanagedType.BStr)] string TypeName, FindComponentOption Option);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GameObject_GetHolder(IntPtr GameObject);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void GameObject_SetName(IntPtr GameObject, [MarshalAs(UnmanagedType.BStr)] string Name);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.BStr)]
        private static extern string GameObject_GetName(IntPtr GameObject);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void GameObject_SetTag(IntPtr GameObject, uint Value);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern uint GameObject_GetTag(IntPtr GameObject);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern void GameObject_SetVisible(IntPtr GameObject, bool Visible);

        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        private static extern bool GameObject_GetVisible(IntPtr GameObject);


        [DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GameObject_GetTransform(IntPtr GameObject);
    }
}
