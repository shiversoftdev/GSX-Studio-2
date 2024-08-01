using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Compression;
using System.Diagnostics;

namespace GSX_Studio.Updater
{
    public partial class UpdaterMainForm : Form
    {
        BackgroundWorker Worker;
        internal int Phase = 1;

        public UpdaterMainForm(int phase = 1)
        {
            try
            {
                InitializeComponent();
                Phase = phase;
                Worker = new BackgroundWorker();
                Worker.WorkerReportsProgress = true;
                Worker.DoWork += DoUpdate;
                Worker.ProgressChanged += Worker_ProgressChanged;
                Worker.RunWorkerAsync();
            }
            catch(Exception e)
            {
                File.AppendAllText("ERRLOG.txt", "\n" + e.GetBaseException().ToString() + "\n");
            }
        }

        private void Worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            if(e.ProgressPercentage == -1)
            {
                Progress.ForeColor = Color.Red;
                Progress.Value = 100;
                StatusLabel.ForeColor = Color.Red;
            }
            else
            {
                Progress.Value = e.ProgressPercentage;

            }
            
            if(e.UserState as string != null)
            {
                StatusLabel.Text = e.UserState as string;
            }
            //Progress.u
        }

        private void DoUpdate(object sender, DoWorkEventArgs e)
        {
            if (Phase == 1)
            {
                try
                {
                    Worker.ReportProgress(1, "Downloading package...");
                    WebClient wc = new WebClient();
                    string target = Path.Combine(Path.GetTempPath(), "package.zip");
                    if (File.Exists(target))
                        File.Delete(target);
                    wc.DownloadFile(UpdateInfo.PackageURL, target);
                    string ExtractPath = Application.StartupPath + Path.DirectorySeparatorChar + UpdateInfo.PHASE2STRING;
                    if (Directory.Exists(ExtractPath))
                        Directory.Delete(ExtractPath, true);
                    Directory.CreateDirectory(ExtractPath);
                    using (ZipArchive archive = ZipFile.OpenRead(target))
                    {
                        string UpdaterName = "";
                        foreach (ZipArchiveEntry entry in archive.Entries)
                        {
                            if (entry.Name.ToLower().Contains("updater.exe"))
                                UpdaterName = Path.Combine(ExtractPath, entry.FullName);
                        }
                        Worker.ReportProgress(33, "Extracting Package...");
                        if (UpdaterName != "")
                        {
                            int count = 0;
                            foreach (ZipArchiveEntry entry in archive.Entries)
                            {
                                entry.ExtractToFile(Path.Combine(ExtractPath, entry.FullName));
                                count++;
                                Worker.ReportProgress(33 + (int)(((float)count / (float)archive.Entries.Count) * 33), "Extracting " + entry.Name + "...");
                            }
                            Worker.ReportProgress(70, "Starting Copy Process...");
                            System.Threading.Thread.Sleep(2000);
                            ProcessStartInfo start = new ProcessStartInfo();
                            start.FileName = UpdaterName;
                            // Do you want to show a console window?
                            start.WindowStyle = ProcessWindowStyle.Hidden;
                            start.CreateNoWindow = true;
                            start.Arguments = UpdateInfo.PHASE2STRING + " \"" + Application.StartupPath + "\"";
                            Process p = Process.Start(start);
                            Environment.Exit(2);
                        }
                        throw new Exception();
                    }
                }
                catch(Exception x)
                {
#if DEBUG
                    MessageBox.Show(x.GetBaseException().ToString());
                    MessageBox.Show(x.StackTrace.ToString());
#endif
                    File.AppendAllText("ERRLOG.txt", "\n" + x.GetBaseException().ToString() + "\n" + " unhandled exception");
                    Worker.ReportProgress(-1, "Updater Failed. Exiting Updater...");
                    System.Threading.Thread.Sleep(2000);
                    Environment.Exit(1);
                }
            }
            else if (Phase == 2)
            {
                Worker.ReportProgress(75, "Working Copy Process...");
                System.Threading.Thread.Sleep(2000);
                Process p = null;
                int Attempts = 0;
                start:
                try
                {
                    Attempts++;
                    if (Attempts <= 3)
                    {
                        AttemptKillProcesses();
                        DirectoryInfo ExtractInfo = new DirectoryInfo(Program.ExtractPath);
                        FileInfo[] infos = ExtractInfo.GetFiles("*.*", SearchOption.AllDirectories);
                        int count = 0;
                        foreach (var file in infos)
                        {
                            Worker.ReportProgress(75 + (int)(((float)count / (float)infos.Length) * 20), "Copying " + file.Name + "...");
                            File.Copy(file.FullName, Path.Combine(Program.CopyPath, file.Name), true);
                            count++;
                        }
                        Worker.ReportProgress(96, "Starting GSX Studio...");
                    }
                    ProcessStartInfo start = new ProcessStartInfo();
                    // Enter in the command line arguments, everything you would enter after the executable name itself
                    //start->Arguments = arguments;
                    // Enter the executable to run, including the complete path
                    start.FileName = Path.Combine(Program.CopyPath, "GSX Studio.exe");
                    // Do you want to show a console window?
                    start.Arguments = "no-update";
                    start.WindowStyle = ProcessWindowStyle.Hidden;
                    start.CreateNoWindow = true;
                    start.UseShellExecute = true;
                    p = Process.Start(start);
                    Worker.ReportProgress(100, "Finishing...");
                    System.Threading.Thread.Sleep(1000);
                }
                catch(IOException)
                {
                    goto start;
                }
                catch(UnauthorizedAccessException)
                {
                    goto start;
                }
                catch(Exception x)
                {
                    if(x.InnerException.ToString().ToLower().Contains("the process cannot access the file"))
                        goto start;
#if DEBUG
                    MessageBox.Show(x.GetBaseException().ToString());
                    MessageBox.Show(x.StackTrace.ToString());
#endif
                    if (p == null)
                    {
                        File.AppendAllText("ERRLOG.txt", "\n" + x.GetBaseException().ToString() + "\n" + "Failed to create GSX Studio process");
                        Environment.Exit(0);
                    }
                    Worker.ReportProgress(-1, "Updater Failed. Exiting Updater...");
                    System.Threading.Thread.Sleep(2000);
                    Environment.Exit(1);
                }
                
            }
            Environment.Exit(0);
        }

        private void AttemptKillProcesses()
        {
            Worker.ReportProgress(75, "Killing active process...");
            List<Process> processes = new List<Process>();
            processes.AddRange(Process.GetProcessesByName("GSX Studio"));
            processes.AddRange(Process.GetProcessesByName("GSX Development Environment"));
            processes.AddRange(Process.GetProcessesByName("ps3tmserver"));
            processes.AddRange(Process.GetProcessesByName("ps3tm"));
            bool IsError = false;
            if (processes.Count > 0)
            {
                foreach(Process p in processes)
                {
                    try
                    {
                        p.Kill();
                    }
                    catch
                    {
                        IsError = true;
                    }
                }
            }
            if (IsError)
                throw new UnauthorizedAccessException();
        }

    }
}
