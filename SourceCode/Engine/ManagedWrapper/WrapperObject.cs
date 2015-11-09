// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace ManagedWrapper
{
	public abstract class WrapperObject
	{
		private static Dictionary<IntPtr, WrapperObject> objects = new Dictionary<IntPtr, WrapperObject>();

		private IntPtr pointer;

		//[BrowsableAttribute(false)]
		public IntPtr Pointer
		{
			get { return pointer; }
		}

		public WrapperObject(IntPtr Pointer)
		{
			pointer = Pointer;

			objects[pointer] = this;
		}

		//public static bool HasObject(IntPtr Pointer)
		//{
		//	if (Pointer == IntPtr.Zero)
		//		return false;

		//	return objects.ContainsKey(Pointer);
		//}

		public static WrapperObject GetObject(IntPtr Pointer)
		{
			if (Pointer != IntPtr.Zero && objects.ContainsKey(Pointer))
				return objects[Pointer];

			return null;
		}

		public static T GetObject<T>(IntPtr Pointer) where T : WrapperObject
		{
			if (Pointer == IntPtr.Zero)
				return null;

			if (objects.ContainsKey(Pointer))
				return (T)objects[Pointer];

			return (T)Activator.CreateInstance(typeof(T), Pointer);
		}

        public static void Destroy(WrapperObject Object)
        {
            if (Object.OnDestroy())
                objects.Remove(Object.pointer);
        }

        protected virtual bool OnDestroy()
        {
            return false;
        }
	}
}
