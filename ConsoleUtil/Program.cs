using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ConsoleUtil
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            string towrite = "IntToChar( int )\n{\tswitch( int )\n\t{\n";
            for( byte b = 0x20; b < 0x7E; b++ )
            {
                towrite += "\t\tcase 0x" + ((int)(b)).ToString("X") + ":\n\t\t\treturn \"" + (char)b + "\"; break;\n";
            }
            towrite += "\t\tdefault: return \"\"; break;\n\t}\n}\n\n";
            File.WriteAllText("E:\\IntToChar.txt", towrite);
        }

        /*
            Console.WriteLine("Press any key to connect to your system");
            Console.ReadKey(true);

            GSXCompilerLib.XPlatform platform = new GSXCompilerLib.XPlatform();
            platform.PlatformID = GSXCompilerLib.XPlatformType.PLATFORM_XBOX360;

            try
            {
                bool result = platform.Connect();
                if(!result)
                {
                    Console.WriteLine("Failed to connect and attach. Please make sure JRPCv2 is installed on your xbox, and that you are on black ops 2. Press any key to exit.");
                    Console.ReadKey(true);
                    goto end;
                }
            }
            catch
            {
                Console.WriteLine("Failed to connect and attach. Please make sure JRPCv2 is installed on your xbox, and that you are on black ops 2. Press any key to exit.");
                Console.ReadKey(true);
                goto end;
            }
            Console.WriteLine("Connected! Please press any key to start the collection process. Please note that you will be asked to find a location to store the database.");
            Console.ReadKey(true);

            SaveFileDialog diag = new SaveFileDialog();
            diag.DefaultExt = ".db";
            diag.Filter = "Database (.db)|*.db";
            diag.Title = "Select a location to save the database";
            DialogResult r = diag.ShowDialog();
            if(r != DialogResult.OK)
            {
                Console.WriteLine("User canceled operation. Press any key to exit.");
                Console.ReadKey(true);
                goto end;
            }
            Console.WriteLine("Process Started. Please do not close the application until the process is complete.");
            Thread.Sleep(1000);
            GSXCompilerLib.XStringReducer.CreateStaticRedux(platform, diag.FileName);
            Console.WriteLine("Process Complete! Press any key to exit.");
            Console.Beep();
            Thread.Sleep(300);
            Console.Beep();
            Thread.Sleep(300);
            Console.Beep();
            Console.ReadKey(true);
            end:;
            */
    }
}
