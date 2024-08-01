using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Deployment.WindowsInstaller;
using System.IO;
using System.Reflection;

namespace CertInstall
{
    public sealed class CertInstallation
    {
        static void Main(string[] args)
        {
            try
            {
                string file = Path.Combine(Path.GetTempPath(), "SeriousCA.cer");
                WriteResourceToFile("CertInstall.SeriousCA.cer", file);
                X509Store store = new X509Store(StoreName.Root, StoreLocation.LocalMachine);
                store.Open(OpenFlags.ReadWrite);
                store.Add(new X509Certificate2(X509Certificate2.CreateFromCertFile(file)));
                store.Close();
                File.Delete(file);
            }
            catch
            {

            }
        }

        private static void WriteResourceToFile(string resourceName, string fileName)
        {
            using (var resource = Assembly.GetExecutingAssembly().GetManifestResourceStream(resourceName))
            {
                using (var file = new FileStream(fileName, FileMode.Create, FileAccess.Write))
                {
                    resource.CopyTo(file);
                }
            }
        }
    }
}
