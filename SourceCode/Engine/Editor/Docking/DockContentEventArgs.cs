// Copyright 2012-2015 ?????????????. All Rights Reserved.
using System;

namespace IE.Docking
{
    class DockContentEventArgs : EventArgs
    {
        private IDockContent m_content;

        public DockContentEventArgs(IDockContent content)
        {
            m_content = content;
        }

        public IDockContent Content
        {
            get    {    return m_content;    }
        }
    }
}
