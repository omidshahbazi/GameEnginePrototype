// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.IO;

namespace Frontend
{
	static class LogHelper
	{
		private static string logPath = "";

		private static string LogPath
		{
			get
			{
				if (string.IsNullOrEmpty(logPath))
				{
					logPath = BuildSystem.IntermediateDirectory + "Logs" + EnvironmentHelper.PathSeparator;

					if (!Directory.Exists(logPath))
						Directory.CreateDirectory(logPath);
				}

				return logPath;
			}
		}

		public static void WriteLineInfo(string FileName, string Text)
		{
			File.AppendAllText(GetFillPath(FileName), Text);
		}

		public static void WriteLineWarning(string FileName, string Text)
		{
			File.AppendAllText(GetFillPath(FileName), Text);
		}

		public static void WriteLineError(string FileName, string Text)
		{
			File.AppendAllText(GetFillPath(FileName), Text + "\r\n");
		}

		public static void DeleteLog(string FileName)
		{
			string path = GetFillPath(FileName);

			if (File.Exists(path))
				File.Delete(path);
		}

		private static string GetFillPath(string FileName)
		{
			return LogPath + FileName + ".log";
		}
	}
}
