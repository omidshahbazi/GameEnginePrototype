// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System.Windows.Forms;
using IE.Docking;
using ManagedWrapper;

namespace IE
{
	partial class RenderWindowBase : DockContent
	{
		public Camera Camera
		{
			get { return renderView1.Camera; }
			set { renderView1.Camera = value; }
		}

		public RenderWindowBase()
		{
			InitializeComponent();
		}
	}
}
