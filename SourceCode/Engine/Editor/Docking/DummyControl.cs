// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;
using System.Windows.Forms;

namespace IE.Docking
{
    internal class DummyControl : Control
    {
        public DummyControl()
        {
            SetStyle(ControlStyles.Selectable, false);
        }
    }
}
