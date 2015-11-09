// Copyright 2012-2015 ?????????????. All Rights Reserved.
namespace IE
{
	partial class InitializeWindow
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.lInfo = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// lInfo
			// 
			this.lInfo.AutoSize = true;
			this.lInfo.Location = new System.Drawing.Point(12, 178);
			this.lInfo.Name = "lInfo";
			this.lInfo.Size = new System.Drawing.Size(61, 13);
			this.lInfo.TabIndex = 0;
			this.lInfo.Text = "Initiliazing...";
			// 
			// InitializeWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.Color.Silver;
			this.ClientSize = new System.Drawing.Size(700, 200);
			this.Controls.Add(this.lInfo);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
			this.Name = "InitializeWindow";
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "InitializeWindow";
			this.TopMost = true;
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label lInfo;
	}
}
