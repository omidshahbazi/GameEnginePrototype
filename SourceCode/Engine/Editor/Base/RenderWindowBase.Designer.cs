// Copyright 2012-2015 ?????????????. All Rights Reserved.
namespace IE
{
	partial class RenderWindowBase
	{
		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.renderView1 = new IE.RenderView();
			this.SuspendLayout();
			// 
			// renderView1
			// 
			this.renderView1.BackColor = System.Drawing.Color.Black;
			this.renderView1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.renderView1.Location = new System.Drawing.Point(0, 0);
			this.renderView1.Name = "renderView1";
			this.renderView1.Size = new System.Drawing.Size(284, 261);
			this.renderView1.TabIndex = 0;
			// 
			// RenderWindow
			// 
			this.BackColor = System.Drawing.Color.Black;
			this.ClientSize = new System.Drawing.Size(284, 261);
			this.Controls.Add(this.renderView1);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "RenderWindow";
			this.ResumeLayout(false);

		}

		#endregion

		private RenderView renderView1;


	}
}
