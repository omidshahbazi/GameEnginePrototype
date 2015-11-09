// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using ManagedWrapper;
using System.Windows.Forms;

namespace IE
{
	static class Program
	{
		private static Core core = null;

		public static Core Core
		{
			get { return core; }
		}

		public static bool IsRunning
		{
			get { return core != null; }
		}

		[STAThread]
		static void Main()
		{
			core = new Core();

			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);

			//Application.Run(new InitializeWindow());
			Application.Run(new MainWindow());
		}
	}
}
