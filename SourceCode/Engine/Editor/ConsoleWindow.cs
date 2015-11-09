// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Windows.Forms;
using IE.Docking;
using ManagedWrapper;

namespace IE
{
	partial class ConsoleWindow : DockableWindow
	{
		public static ConsoleWindow instance;

		private string[] TypesName = { "", "[Warning] ", "[Error] " };

		public ConsoleWindow()
		{
			InitializeComponent();

			instance = this;

			Log.SetCallback(LogCallback);
		}

		public void LogCallback(string Text, int Type)
		{
			listBox.Items.Insert(0, TypesName[Type] + Text);
		}
	}
}
