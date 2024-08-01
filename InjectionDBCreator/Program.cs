using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace InjectionDBCreator
{
    class Program
    {
        /*
         * [80 GSXdb 0D 0A]
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         * 
         */
        static void Main(string[] args)
        {
            FolderBrowserDialog dialog = new FolderBrowserDialog();
            GSXInjectionDB Database = new GSXInjectionDB();
            Database.DataBase.AddRange(Database.Magic);
            Database.DataBase.AddRange(new byte[24]);
            //string PCDB = File.ReadAllText("pc.db");
            //string[] entries = PCDB.Split('@');
            Database.BuffersList[GSCPlatformType.PC] = new GSCBuffersList() { PlatformType=GSCPlatformType.PC };
            Database.BuffersList[GSCPlatformType.PS3] = new GSCBuffersList() { PlatformType = GSCPlatformType.PS3 };
            Database.BuffersList[GSCPlatformType.Xbox] = new GSCBuffersList() { PlatformType = GSCPlatformType.Xbox };
            Database.BuffersList[GSCPlatformType.Redacted] = new GSCBuffersList() { PlatformType = GSCPlatformType.Redacted };
            /*
            foreach (string entry in entries)
            {
                if (!entry.Contains("#"))
                    continue;
                string entryname = entry.Substring(0, entry.IndexOf("#"));
                entryname = entryname.ToLower().Replace('\\', '/');
                string[] platform_entries = entry.Substring(entry.IndexOf('#') + 1).Split(';');
                foreach(string plat_entry in platform_entries)
                {
                    if (!plat_entry.Contains(':'))
                        continue;
                    string platform = plat_entry.Split(':')[0];
                    string Address = plat_entry.Split(':')[1];
                    string Buffer = plat_entry.Split(':')[2];
                    GSCBuffersList TargetList = null;
                    switch(platform)
                    {
                        case "PCZM":
                        case "PCMP":
                            TargetList = Database.BuffersList[GSCPlatformType.PC];
                            break;
                        case "PCRZM":
                        case "PCRRMP":
                        case "PCRMP":
                            TargetList = Database.BuffersList[GSCPlatformType.Redacted];
                            break;

                    }
                    if (!Database.LocationNames.Contains(entryname))
                        Database.LocationNames.Add(entryname);
                    if(!TargetList.Buffers.ContainsKey(entryname))
                    {
                        TargetList.Buffers[entryname] = new GSCBuffer();
                    }
                    TargetList.Buffers[entryname].PointerAddress = Convert.ToInt32(Address.ToLower().Replace("0x",""), 16);
                    TargetList.Buffers[entryname].BufferPtr = Convert.ToInt32(Buffer.ToLower().Replace("0x", ""), 16);
                }
            }
            */

            string XBMP = File.ReadAllText("xbox_mp.txt");
            string XBZM = File.ReadAllText("xbox_zm.txt");
            string PSMP = File.ReadAllText("ps3_mp.txt");
            string PSZM = File.ReadAllText("ps3_zm.txt");

            string PCMP = File.ReadAllText("pc_mp.txt");
            string PCZM = File.ReadAllText("pc_zm.txt");
            string RMP = File.ReadAllText("r_mp.txt");
            string RZM = File.ReadAllText("r_zm.txt");

            Dictionary<string, GSCPlatformType> platform_dictionaries_mp = new Dictionary<string, GSCPlatformType>();
            platform_dictionaries_mp[XBMP] = GSCPlatformType.Xbox;
            platform_dictionaries_mp[PSMP] = GSCPlatformType.PS3;
            platform_dictionaries_mp[PCMP] = GSCPlatformType.PC;
            platform_dictionaries_mp[RMP] = GSCPlatformType.Redacted;
            

            foreach (string source in platform_dictionaries_mp.Keys)
            {
                string[] split = source.Replace("\r","").Split('\n');
                Console.WriteLine(split.Length);
                GSCBuffersList TargetList = Database.BuffersList[platform_dictionaries_mp[source]];
                for (int i = 0; i < split.Length;)
                {
                    string Name = split[i].ToLower().Replace("name: ", "").Trim();
                    int Address = Convert.ToInt32(split[i + 1].ToLower().Replace("pointer address: ", "").Replace("0x", "").Replace("pointer: ","").Trim(), 16);
                    int Buffer = Convert.ToInt32(split[i + 2].ToLower().Replace("buffer address: ", "").Replace("0x", "").Replace("buffer: ", "").Trim(), 16);
                    if (!Database.LocationNames.Contains(Name))
                        Database.LocationNames.Add(Name);
                    if (!TargetList.MPBuffers.ContainsKey(Name))
                    {
                        TargetList.MPBuffers[Name] = new GSCBuffer();
                    }
                    TargetList.MPBuffers[Name].PointerAddress = Address;
                    TargetList.MPBuffers[Name].BufferPtr = Buffer;
                    i += 5;
                }
            }

            Dictionary<string, GSCPlatformType> platform_dictionaries_zm = new Dictionary<string, GSCPlatformType>();
            platform_dictionaries_zm[XBZM] = GSCPlatformType.Xbox;
            platform_dictionaries_zm[PSZM] = GSCPlatformType.PS3;
            platform_dictionaries_zm[PCZM] = GSCPlatformType.PC;
            platform_dictionaries_zm[RZM] = GSCPlatformType.Redacted;

            foreach (string source in platform_dictionaries_zm.Keys)
            {
                string[] split = source.Replace("\r", "").Split('\n');
                GSCBuffersList TargetList = Database.BuffersList[platform_dictionaries_zm[source]];
                for (int i = 0; i < split.Length;)
                {
                    string Name = split[i].ToLower().Replace("name: ", "").Trim();
                    int Address = Convert.ToInt32(split[i + 1].ToLower().Replace("pointer address: ", "").Replace("0x", "").Replace("pointer: ", "").Trim(), 16);
                    int Buffer = Convert.ToInt32(split[i + 2].ToLower().Replace("buffer address: ", "").Replace("0x", "").Replace("buffer: ", "").Trim(), 16);
                    if (!Database.LocationNames.Contains(Name))
                        Database.LocationNames.Add(Name);
                    if (!TargetList.ZMBuffers.ContainsKey(Name))
                    {
                        TargetList.ZMBuffers[Name] = new GSCBuffer();
                    }
                    TargetList.ZMBuffers[Name].PointerAddress = Address;
                    TargetList.ZMBuffers[Name].BufferPtr = Buffer;
                    i += 5;
                }
            }

            Database.WriteDB();
            File.WriteAllBytes("Injection.db", Database.DataBase.ToArray());
            Console.ReadKey(false);
        }

        private static List<String> DirSearch(string sDir)
        {
            List<String> files = new List<String>();
            try
            {
                foreach (string f in Directory.GetFiles(sDir))
                {
                    if (f.Contains(".offsets")) //too lazy
                        files.Add(f);
                }
                foreach (string d in Directory.GetDirectories(sDir))
                {
                    files.AddRange(DirSearch(d));
                }
            }
            catch (Exception)
            {

            }

            return files;
        }


        internal class GSXInjectionDB
        {
            internal byte[] Magic = { 0x80, (byte)'G', (byte)'S', (byte)'X', (byte)'d', (byte)'b', 0x0D, 0x0A };
            internal int LocationNamesPtr;
            internal int BuffersPtr;
            internal int InjectionOffsetsPtr;

            
            internal int NumLocationNames
            {
                get
                {
                    return LocationNames.Count;
                }
            }

            internal int NumBuffers
            {
                get
                {
                    return BuffersList.Count;
                }
            }

            internal int NumOffsetLists
            {
                get
                {
                    return OffsetLists.Count;
                }
            }

            internal List<string> LocationNames = new List<string>();

            internal Dictionary<GSCPlatformType, GSCBuffersList> BuffersList = new Dictionary<GSCPlatformType, GSCBuffersList>();

            internal Dictionary<GSCPlatformType, OffsetList> OffsetLists = new Dictionary<GSCPlatformType, OffsetList>();

            internal List<byte> DataBase = new List<byte>();


            public void WriteDB()
            {
                LocationNames.Sort();
                LocationNamesPtr = DataBase.Count;
                Dictionary<string, int> LocationPtrs = new Dictionary<string, int>();
                foreach(string s in LocationNames)
                {
                    LocationPtrs[s] = DataBase.Count;
                    DataBase.AddRange(Encoding.ASCII.GetBytes(s));
                    DataBase.Add(0x0);
                }
                BuffersPtr = DataBase.Count;
                foreach(var key in BuffersList.Keys)
                {
                    DataBase.Add((byte)key);
                    DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].NumberOfMPBuffers));
                    DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].NumberOfZMBuffers));
                    foreach (string name in BuffersList[key].MPBuffers.Keys)
                    {
                        BuffersList[key].MPBuffers[name].NamePtr = LocationPtrs[name];
                        DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].MPBuffers[name].NamePtr));
                        DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].MPBuffers[name].PointerAddress));
                        DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].MPBuffers[name].BufferPtr));
                    }
                    foreach (string name in BuffersList[key].ZMBuffers.Keys)
                    {
                        BuffersList[key].ZMBuffers[name].NamePtr = LocationPtrs[name];
                        DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].ZMBuffers[name].NamePtr));
                        DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].ZMBuffers[name].PointerAddress));
                        DataBase.AddRange(BitConverter.GetBytes(BuffersList[key].ZMBuffers[name].BufferPtr));
                    }
                }
                InjectionOffsetsPtr = DataBase.Count;



                PatchPointers();
            }

            public void PatchPointers()
            {
                WriteDBRange(0x8, BitConverter.GetBytes(LocationNamesPtr));
                WriteDBRange(0xC, BitConverter.GetBytes(BuffersPtr));
                WriteDBRange(0x10, BitConverter.GetBytes(InjectionOffsetsPtr));
                WriteDBRange(0x14, BitConverter.GetBytes(NumLocationNames));
                WriteDBRange(0x18, BitConverter.GetBytes(NumBuffers));
                WriteDBRange(0x1C, BitConverter.GetBytes(NumOffsetLists));
            }

            public void WriteDBRange(int index, byte[] bytes)
            {
                for (int i = 0; i < bytes.Length && (i + index) < DataBase.Count; i++)
                {
                    DataBase[i + index] = bytes[i];
                }
            }
        }

        internal class GSCBuffersList
        {
            internal GSCPlatformType PlatformType;
            internal int NumberOfMPBuffers
            {
                get
                {
                    return MPBuffers.Count;
                }
            }
            internal int NumberOfZMBuffers
            {
                get
                {
                    return ZMBuffers.Count;
                }
            }
            internal Dictionary<string, GSCBuffer> MPBuffers = new Dictionary<string, GSCBuffer>();
            internal Dictionary<string, GSCBuffer> ZMBuffers = new Dictionary<string, GSCBuffer>();
        }

        internal class OffsetList
        {
            internal GSCPlatformType PlatformType;
            internal int NumberOfInjectionOffsets
            {
                get
                {
                    return InjectionOffsets.Count;
                }
            }
            internal List<InjectionOffset> InjectionOffsets = new List<InjectionOffset>();
        }

        internal class GSCBuffer
        {
            internal int NamePtr;
            internal int PointerAddress;//Pointer to vv
            internal int BufferPtr; //Value of ^^
        }

        internal struct InjectionOffset
        {
            internal uint Address;
            internal uint Size;
        }

        internal enum GSCPlatformType : byte
        {
            PS3,
            Xbox,
            PC,
            Redacted,
        }
    }
}
