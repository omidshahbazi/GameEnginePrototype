// Copyright 2012-2015 ?????????????. All Rights Reserved.
using IE.Docking;

namespace IE
{
	class DockableWindow : DockContent
	{
		public DockableWindow()
		{
			DockAreas = DockAreas.Float | DockAreas.DockLeft | DockAreas.DockRight | DockAreas.DockTop | DockAreas.DockBottom;
		}

		private void InitializeComponent()
		{
			this.SuspendLayout();
			// 
			// DockableWindow
			// 
			this.ClientSize = new System.Drawing.Size(284, 261);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "DockableWindow";
			this.ResumeLayout(false);

		}
	}
}
