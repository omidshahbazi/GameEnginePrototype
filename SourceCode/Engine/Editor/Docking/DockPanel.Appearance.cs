// Copyright 2012-2015 ?????????????. All Rights Reserved.
using IE.Docking.Skins;
using System.ComponentModel;

namespace IE.Docking
{
	partial class DockPanel
	{
		private DockPanelSkin m_dockPanelSkin = DockPanelSkinBuilder.Create(Style.Default);
		[LocalizedCategory("Category_Docking")]
		[LocalizedDescription("DockPanel_DockPanelSkin")]
		public DockPanelSkin Skin
		{
			get { return m_dockPanelSkin; }
			set { m_dockPanelSkin = value; }
		}

		private Style m_dockPanelSkinStyle = Style.Default;
		[LocalizedCategory("Category_Docking")]
		[LocalizedDescription("DockPanel_DockPanelSkinStyle")]
		[DefaultValue(Style.Default)]
		public Style SkinStyle
		{
			get { return m_dockPanelSkinStyle; }
			set
			{
				if (m_dockPanelSkinStyle == value)
					return;

				m_dockPanelSkinStyle = value;

				Skin = DockPanelSkinBuilder.Create(m_dockPanelSkinStyle);
			}
		}
	}
}
