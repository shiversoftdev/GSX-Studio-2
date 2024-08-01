using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GSX_Studio.Updater
{
    public static class UpdateInfo
    {
        private const string UpdateURL = "http://gsxstudio.net/";

        internal static string TargetVersion = "";

        public const string PHASE2STRING = "phase2";

        internal static string PackageURL
        {
            get
            {
                return UpdateURL + TargetVersion + ".zip";
            }
        }

        internal static string VersionURL
        {
            get
            {
                return UpdateURL + "VERSION.dat";
            }
        }
    }
}
