// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System.Windows.Forms;
using IE.Docking.Win32;
using ManagedWrapper;
using System;

namespace IE
{
	partial class RenderView : UserControl
	{
		private RenderWindow renderWindow;
		private Camera camera;

		public Camera Camera
		{
			get { return camera; }
			set
			{
				camera = value;

				if (renderWindow != null)
					renderWindow.Camera = camera;
			}
		}

		public RenderView()
		{
			InitializeComponent();

			Click += RenderView_Click;
		}

		void RenderView_Click(object sender, EventArgs e)
		{
			PropertyWindow.SelectedObject = camera;
		}

		protected override void WndProc(ref Message m)
		{
			Msgs msg = (Msgs)m.Msg;

			if (Program.IsRunning)
			{
				if (msg == Msgs.WM_SIZE)
					WindowUtility.WndProc(m.HWnd, m.Msg, m.WParam.ToInt32(), m.LParam.ToInt32());
				if (msg == Msgs.WM_DESTROY)
					Program.Core.RenderEngine.DestroyRenderWindow(renderWindow);
				else if (msg == Msgs.WM_NCCREATE)
				{
					renderWindow = Program.Core.RenderEngine.CreateRenderWindow(Handle);
					renderWindow.Camera = camera;
				}
			}

			base.WndProc(ref m);
		}
	}
}
