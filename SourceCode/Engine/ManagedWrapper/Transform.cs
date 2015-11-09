// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Runtime.InteropServices;

namespace ManagedWrapper
{
	public class Transform : Component
	{
		private Transform parent;

		public Transform Parent
		{
			get { return parent; }
			set
			{
				parent = value;
				Transform_SetParent(Pointer, parent.Pointer);
			}
		}

		public Vector3 LocalPosition
		{
			get { return Transform_GetLocalPosition(Pointer); }
			set { Transform_SetLocalPosition(Pointer, value); }
		}

		public Vector3 LocalRotation
		{
			get { return Transform_GetLocalRotation(Pointer); }
			set { Transform_SetLocalRotation(Pointer, value); }
		}

		public Vector3 LocalScale
		{
			get { return Transform_GetLocalScale(Pointer); }
			set { Transform_SetLocalScale(Pointer, value); }
		}

		public Vector3 WorldPosition
		{
			get { return Transform_GetPosition(Pointer); }
			set { Transform_SetPosition(Pointer, value); }
		}

		public Vector3 WorldRotation
		{
			get { return Transform_GetRotation(Pointer); }
			set { Transform_SetRotation(Pointer, value); }
		}

		public Vector3 WorldScale
		{
			get { return Transform_GetScale(Pointer); }
			set { Transform_SetScale(Pointer, value); }
		}

		public Transform(IntPtr Pointer) :
			base(Pointer)
		{
			IntPtr p = Transform_GetParent(Pointer);
			if (p != IntPtr.Zero)
				parent = WrapperObject.GetObject<Transform>(p);
		}

		public void Translate(Vector3 Value)
		{
			Transform_Translate(Pointer, Value);
		}

		public void Rotate(Vector3 Value)
		{
			Transform_Rotate(Pointer, Value);
		}

		public void Scale(Vector3 Value)
		{
			Transform_Scale(Pointer, Value);
		}

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern IntPtr Transform_GetParent(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetParent(IntPtr Transform, IntPtr Parent);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector3 Transform_GetLocalPosition(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetLocalPosition(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector3 Transform_GetLocalRotation(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetLocalRotation(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector3 Transform_GetLocalScale(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetLocalScale(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector3 Transform_GetPosition(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetPosition(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector3 Transform_GetRotation(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetRotation(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern Vector3 Transform_GetScale(IntPtr Transform);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_SetScale(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_Translate(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_Rotate(IntPtr Transform, Vector3 Value);

		[DllImport(Constants.CWrapperDLL, CallingConvention = CallingConvention.Cdecl)]
		private static extern void Transform_Scale(IntPtr Transform, Vector3 Value);
	}
}
