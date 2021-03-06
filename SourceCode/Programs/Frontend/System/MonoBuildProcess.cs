// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System.Diagnostics;
using System.Xml;

namespace Frontend
{
	//http://www.mono-project.com/docs/about-mono/languages/csharp/
	//http://stackoverflow.com/questions/13664441/how-can-you-use-monos-mcs-to-compile-and-run-a-csproj-file

	class MonoBuildProcess : BuildProcess
	{
		public MonoBuildProcess() :
		base("xbuild")
		{
		}

		public override void Build (string FilePath)
		{
			XmlDocument xml = new XmlDocument ();
			xml.Load (FilePath);

			base.Start("\"" + FilePath + "\" /t:build /p:configuration=" + BuildSystem.BuildConfiguration.ToString().ToLower());
		}
	}
}