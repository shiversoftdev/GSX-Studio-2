using System;
using System.Collections.Generic;
using System.ComponentModel;

namespace GSX_Studio
{
    using namespace System::Data;
    using System.Drawing;
    using System.Text;
    using System.Windows.Forms;
    using DevExpress.XtraSplashScreen;

	public ref class LoadingSplash: SplashScreen
	{
		public LoadingSplash()
		{
			InitializeComponent();
		}

        #region Overrides
        
        public override void ProcessCommand(Enum cmd, object arg) {
            base.ProcessCommand(cmd, arg);
        }

        #endregion

        public enum SplashScreenCommand {
        }
	}
}