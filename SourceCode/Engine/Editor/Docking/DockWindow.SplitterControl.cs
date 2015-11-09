// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace IE.Docking
{
    partial class DockWindow
    {
        private class SplitterControl : SplitterBase
        {
            protected override int SplitterSize
            {
                get { return Measures.SplitterSize; }
            }

            protected override void StartDrag()
            {
                DockWindow window = Parent as DockWindow;
                if (window == null)
                    return;

                window.DockPanel.BeginDrag(window, window.RectangleToScreen(Bounds));
            }
        }
    }
}
