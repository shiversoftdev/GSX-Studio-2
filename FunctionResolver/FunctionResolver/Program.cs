using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FunctionResolver
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            T6GSXFuncResolveDB DB = new T6GSXFuncResolveDB();
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            Console.WriteLine("Select a folder to parse");
            List<string> FilesToParse = new List<string>();
            do
            {
                DialogResult r = dialog.ShowDialog();
                if (r != DialogResult.OK)
                    Application.Exit();
                FilesToParse.AddRange(DirSearch(dialog.SelectedPath));
                /*
                if (dialog.SelectedPath.ToLower().Contains("maps" + Path.DirectorySeparatorChar + "mp"))
                {
                    FilesToParse.AddRange(DirSearch(dialog.SelectedPath));
                }
                else
                {
                    Console.WriteLine("Invalid folder selected. Must include maps\\mp");
                }
                */
                Console.WriteLine("More? Y/N");
            }
            while (Console.ReadKey(false).Key == ConsoleKey.Y);
            
            if(FilesToParse.Count > 0)
            {
                FilesToParse.Sort();
                DB.DataBase.AddRange(DB.Magic);
                DB.DataBase.AddRange(new byte[24]); //header
                foreach (string file in FilesToParse)
                {
                    byte[] bytes = File.ReadAllBytes(file);
                    EndianReader Reader = new EndianReader(bytes, EndianType.BigEndian);
                    ulong magic = Reader.ReadUInt64();
                    if(magic != 0x804753430d0a0006)
                    {
                        Console.WriteLine("Bad magic (" + file + ")... " + magic.ToString("x") + "!=" + ((ulong)(0x804753430D0A0006)).ToString("X"));
                        continue;
                    }
                    Reader.ReadUInt32(); //Skip past CRC32
                    Reader.ReadUInt32(); //Skip past Includes
                    Reader.ReadUInt32(); //Skip past Anims
                    Reader.ReadUInt32(); //Skip past CodeSection
                    Reader.ReadUInt32(); //Skip past Strings
                    int PtrToExports = Reader.ReadInt32();
                    Reader.ReadUInt32(); //Skip past Externs
                    Reader.ReadUInt32(); //Skip past Relocations
                    Reader.ReadUInt32(); //Skip past Size
                    Reader.ReadUInt32(); //Skip past CodeSec
                    ushort NamePtr = Reader.ReadUInt16();
                    Reader.ReadUInt16(); //Skip past NumStrings
                    ushort NumExports = Reader.ReadUInt16();
                    Reader.SeekTo(NamePtr);
                    string name = Reader.ReadNullTerminatedString().ToLower();
                    Reader.SeekTo(PtrToExports);
                    if (!DB.AssetNames.Contains(name))
                        DB.AssetNames.Add(name);
                    if (!DB.AssetExports.ContainsKey(name))
                    {
                        AssetExportList AssetExport = new AssetExportList();
                        DB.AssetExports[name] = AssetExport;
                    }
                    try
                    {
                        for (int i = 0; i < NumExports; i++)
                        {
                            Reader.ReadUInt32(); //Skip past CRC32
                            Reader.ReadUInt32(); //Skip past Start
                            ushort NamePos = Reader.ReadUInt16();
                            long origin = Reader.BaseStream.Position;
                            Reader.SeekTo(NamePos);
                            string exportname = Reader.ReadNullTerminatedString().ToLower();
                            Reader.SeekTo(origin);
                            byte Numparams = Reader.ReadByte();
                            Reader.ReadByte(); //Skip Flags
                            string exportkey = exportname + "?" + Numparams;
                            if (!DB.ExportNames.Contains(exportname))
                                DB.ExportNames.Add(exportname);
                            if (!DB.AssetExports[name].Exports.ContainsKey(exportkey))
                            {
                                DB.AssetExports[name].Exports[exportkey] = new Export();
                                DB.AssetExports[name].Exports[exportkey].NumParams = Numparams;
                            }
                        }
                    }
                    catch(Exception e)
                    {
                        Console.WriteLine(name + " was not parsed correctly! (" + e.Message.ToString() + ")");
                    }
                    
                }
                DB.Write();
                File.WriteAllBytes("FunctionResolve.db", DB.DataBase.ToArray());
                Console.ReadKey(false);
            }

        }

        private static List<String> DirSearch(string sDir)
        {
            List<String> files = new List<String>();
            try
            {
                foreach (string f in Directory.GetFiles(sDir))
                {
                    if(f.Contains(".gsc")) //too lazy
                        files.Add(f);
                }
                foreach (string d in Directory.GetDirectories(sDir))
                {
                    files.AddRange(DirSearch(d));
                }
            }
            catch (System.Exception)
            {
                
            }

            return files;
        }


        class T6GSXFuncResolveDB
        {
            internal byte[] Magic = { 0x80, 0x47, 0x53, 0x58, 0x64, 0x62, 0x0A, 0x00 };
            internal int PtrToEntries; //0x8
            internal int PtrToAssetNames; //0xC
            internal int PtrToAssetExports; //0x10
            internal int NumEntries         //0x14
            {
                get
                {
                    return ExportNames.Count;
                }
            }
            internal int NumAssetNames  //0x18
            {
                get
                {
                    return AssetNames.Count;
                }
            }
            internal int NumAssetExports    //0x1C
            {
                get
                {
                    return AssetExports.Count;
                }
            }
            internal List<string> ExportNames = new List<string>();
            internal Dictionary<string, int> ExportLocations = new Dictionary<string, int>();
            internal List<string> AssetNames = new List<string>();
            internal Dictionary<string, AssetExportList> AssetExports = new Dictionary<string, AssetExportList>();
            internal List<byte> DataBase = new List<byte>();

            public void Write()
            {
                WriteExports();
                WriteAssets();
                WriteAssetExportLists();
                PatchPointers();
            }

            public void WriteExports()
            {
                ExportNames.Sort();
                PtrToEntries = DataBase.Count;
                foreach(string s in ExportNames)
                {
                    ExportLocations[s] = DataBase.Count;
                    DataBase.AddRange(System.Text.Encoding.ASCII.GetBytes(s));
                    DataBase.Add(0x0);
                }
            }

            public void WriteAssets()
            {
                AssetNames.Sort();
                PtrToAssetNames = DataBase.Count;
                foreach (string s in AssetNames)
                {
                    AssetExports[s].PtrToName = DataBase.Count;
                    DataBase.AddRange(System.Text.Encoding.ASCII.GetBytes(s));
                    DataBase.Add(0x0);
                }
            }

            public void WriteAssetExportLists()
            {
                PtrToAssetExports = DataBase.Count;
                foreach(string s in AssetExports.Keys)
                {
                    DataBase.AddRange(BitConverter.GetBytes(AssetExports[s].PtrToName));
                    DataBase.AddRange(BitConverter.GetBytes(AssetExports[s].ExportCount));
                    foreach (string key in AssetExports[s].Exports.Keys)
                    {
                        string ExportName = key.Split('?')[0];
                        if (ExportLocations.ContainsKey(ExportName))
                            AssetExports[s].Exports[key].PtrToName = ExportLocations[ExportName];
                        DataBase.AddRange(BitConverter.GetBytes(AssetExports[s].Exports[key].PtrToName));
                        DataBase.Add(AssetExports[s].Exports[key].NumParams);
                    }
                }
            }

            public void PatchPointers()
            {
                WriteDBRange(0x8, BitConverter.GetBytes(PtrToEntries));
                WriteDBRange(0xC, BitConverter.GetBytes(PtrToAssetNames));
                WriteDBRange(0x10, BitConverter.GetBytes(PtrToAssetExports));
                WriteDBRange(0x14, BitConverter.GetBytes(NumEntries));
                WriteDBRange(0x18, BitConverter.GetBytes(NumAssetNames));
                WriteDBRange(0x1C, BitConverter.GetBytes(NumAssetExports));
            }

            public void WriteDBRange(int index, byte[] bytes)
            {
                for(int i = 0; i < bytes.Length && (i + index) < DataBase.Count; i++)
                {
                    DataBase[i + index] = bytes[i];
                }
            }
        }

        class AssetExportList
        {
            internal int PtrToName;
            internal int ExportCount
            {
                get
                {
                    return Exports.Count;
                }
            }
            internal Dictionary<string, Export> Exports = new Dictionary<string, Export>();
        }

        class Export
        {
            internal int PtrToName;
            internal byte NumParams;
        }
    }
}
