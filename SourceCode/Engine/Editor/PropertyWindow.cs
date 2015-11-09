// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Reflection;
using System.Windows.Forms;

namespace IE
{
	partial class PropertyWindow : DockableWindow
	{
		private static PropertyGrid grid;
		private static object selectedObject;

		public static object SelectedObject
		{
			get { return selectedObject; }
			set
			{
				selectedObject = value;

				//Type type = selectedObject.GetType();
				//PropertyInfo[] properties = type.GetProperties();

				//for (int i = 0; i < properties.Length; i++)
				//	grid.item

				//ExpandableObjectConverter

				grid.SelectedObject = selectedObject;
			}
		}

		public PropertyWindow()
		{
			InitializeComponent();

			grid = propertyGrid;
		}
	}
}
