// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System.Drawing;
using System.Drawing.Drawing2D;

namespace IE.Docking.Skins
{
	internal static class DockPanelSkinBuilder
	{
		public static DockPanelSkin Create(Style style)
		{
			switch (style)
			{
				case Style.Default:
				default:
					return CreateDefault();
			}
		}

		private static DockPanelSkin CreateDefault()
		{
			DockPanelSkin skin = new DockPanelSkin();

			skin.AutoHideStripSkin.DockStripGradient.StartColor = SystemColors.ControlLight;
			skin.AutoHideStripSkin.DockStripGradient.EndColor = SystemColors.ControlLight;
			skin.AutoHideStripSkin.TabGradient.TextColor = SystemColors.ControlDarkDark;

			skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.StartColor = SystemColors.Control;
			skin.DockPaneStripSkin.DocumentGradient.DockStripGradient.EndColor = SystemColors.Control;
			skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.StartColor = SystemColors.ControlLightLight;
			skin.DockPaneStripSkin.DocumentGradient.ActiveTabGradient.EndColor = SystemColors.ControlLightLight;
			skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.StartColor = SystemColors.ControlLight;
			skin.DockPaneStripSkin.DocumentGradient.InactiveTabGradient.EndColor = SystemColors.ControlLight;

			skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.StartColor = SystemColors.ControlLight;
			skin.DockPaneStripSkin.ToolWindowGradient.DockStripGradient.EndColor = SystemColors.ControlLight;

			skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.StartColor = SystemColors.Control;
			skin.DockPaneStripSkin.ToolWindowGradient.ActiveTabGradient.EndColor = SystemColors.Control;

			skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.StartColor = Color.Transparent;
			skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.EndColor = Color.Transparent;
			skin.DockPaneStripSkin.ToolWindowGradient.InactiveTabGradient.TextColor = SystemColors.ControlDarkDark;

			skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.StartColor = SystemColors.GradientActiveCaption;
			skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.EndColor = SystemColors.ActiveCaption;
			skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
			skin.DockPaneStripSkin.ToolWindowGradient.ActiveCaptionGradient.TextColor = SystemColors.ActiveCaptionText;

			skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.StartColor = SystemColors.GradientInactiveCaption;
			skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.EndColor = SystemColors.InactiveCaption;
			skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.LinearGradientMode = LinearGradientMode.Vertical;
			skin.DockPaneStripSkin.ToolWindowGradient.InactiveCaptionGradient.TextColor = SystemColors.InactiveCaptionText;

			return skin;
		}

	}
}
