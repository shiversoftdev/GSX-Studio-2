using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Diagnostics;

namespace GSX_Studio.Updater
{
    static class Program
    {
        internal static string ExtractPath = "";
        internal static string CopyPath = "";
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        
        [STAThread]
        static void Main(string[] args)
        {
            if(args.Length >= 1)
            {
                try
                {
                    string token = args[0].ToLower();
                    switch (token)
                    {
                        case UpdateInfo.PHASE2STRING:
                            CopyPath = args[1].ToLower();
                            ExtractPath = Application.StartupPath;
                            Application.Run(new UpdaterMainForm(2));

                            break;
                            
                    }

                }
                catch
                {
                    Environment.Exit(0);
                }
                
            }
            else
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                // Create a new WebClient instance.
                try
                {
                    FileVersionInfo Version = FileVersionInfo.GetVersionInfo(Path.Combine(Application.StartupPath, "GSX Studio.exe"));
                    WebClient wc = new WebClient();
                    string target = Path.GetTempPath() + Path.DirectorySeparatorChar + "gsxversion.dat";
                    if (File.Exists(target))
                        File.Delete(target);
                    wc.DownloadFile(UpdateInfo.VersionURL, target);
                    UpdateInfo.TargetVersion = File.ReadAllText(target);
                    UpdateInfo.TargetVersion = UpdateInfo.TargetVersion.Trim();
                    if (UpdateInfo.TargetVersion != Version.FileVersion)
                    {
                        Application.Run(new UpdaterMainForm());
                    }
                }
                catch (Exception e)
                {
                    File.AppendAllText("ERRLOG.txt", "\n" + e.GetBaseException().ToString() + "\n");
                    Environment.Exit(1);
                }
            }
            //Environment.Exit(0);
        }
    }
}