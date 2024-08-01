using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GSXCompilerLib
{
    /// <summary>
    /// Injector for GSX
    /// </summary>
    public static class GSXInjector
    {



        internal static byte[] fixup_entropy = new byte[] { 0x80, (byte)'G', (byte)'S', (byte)'X' };

        private static GSXInjectionDB injection_database;
        internal static GSXInjectionDB InjectionDatabase
        {
            get
            {
                if(injection_database == null)
                {
                    injection_database = new GSXInjectionDB();
                    injection_database.LoadDB(Bytes);
                }
                return injection_database;
            }
        }

        private static byte[] bytes;
        private static byte[] Bytes
        {
            get
            {
                if (bytes == null)
                {
                    bytes = ExtractResource("GSXCompilerLib.Injection.db");
                }
                return bytes;
            }
        }

        private static List<GSCBuffer> OverwrittenBuffers = new List<GSCBuffer>();

        internal static void ResetScriptParseTree(XPlatform x)
        {
            List<GSCBuffer> ToRemove = new List<GSCBuffer>();
            foreach(GSCBuffer buff in OverwrittenBuffers)
            {
                if(XPlatformAsGSC(x.PlatformID) == buff.PlatformType)
                {
                    ToRemove.Add(buff);
                    x.WriteInt((uint)buff.PointerAddress, buff.BufferPtr);
                }

            }
            foreach(GSCBuffer b in ToRemove)
            {
                OverwrittenBuffers.Remove(b);
            }
        }

        private static bool InjectGSC_internal(XPlatform x, GSCBuffer poc, byte[] file)
        {
            int injection_address = GetInjectionAddress(x, file.Length);
            file = AdjustFixups(file, injection_address, x.PlatformID == XPlatformType.PLATFORM_PC_REDACTED || x.PlatformID == XPlatformType.PLATFORM_PC_STEAM);
            bool result = x.WriteInt((uint)poc.PointerAddress, injection_address) && x.WriteBytes((uint)injection_address, file);
            if (result && !OverwrittenBuffers.Contains(poc))
                OverwrittenBuffers.Add(poc);
            return result;
        }

        private static byte[] AdjustFixups(byte[] file, int injection_address, bool IsPC)
        {
            using (EndianReader r = new EndianReader(file, IsPC ? EndianType.LittleEndian : EndianType.BigEndian))
            {
                byte[] GSXEntropy = new byte[] { file[0x8], file[0x9], file[0xA], file[0xB] };
                r.SeekTo(0x24);
                uint Target = r.ReadUInt32();
                r.SeekTo(0x38);
                ushort NumFixups = r.ReadUInt16();
                for(uint i = 0; i < NumFixups; i++)
                {
                    byte[] vbytes = new byte[4];
                    for(int j = 0; j < 4; j++)
                    {
                        vbytes[j] = RemoveEntropy(file[Target + (i * 8) + j], j, GSXEntropy);
                    }
                    if (!IsPC)
                        vbytes = vbytes.Reverse<byte>().ToArray<byte>();
                    int Value = BitConverter.ToInt32(vbytes, 0);
                    Value -= injection_address;
                    byte[] TargetBytes = BitConverter.GetBytes(Value);
                    if (!IsPC)
                        TargetBytes = TargetBytes.Reverse<byte>().ToArray();
                    for (int j = 0; j < 4; j++)
                    {
                        file[(int)(Target + i * 8 + j)] = TargetBytes[j];
                    }
                }
            }

                return file;
        }

        internal static byte AddEntropy(byte target, int index, byte[] e_array)
        {
            return (byte)(target + e_array[index]);
        }

        internal static byte RemoveEntropy(byte target, int index, byte[] e_array)
        {
            return (byte)(target - e_array[index]);
        }

        /// <summary>
        /// Inject a list of GSCs to all of the specified platforms
        /// </summary>
        /// <param name="Files">List of IGSCFiles to inject</param>
        /// <param name="Platforms">List of platforms to inject to</param>
        /// <returns></returns>
        public static List<string> InjectGSCS(IGSCFile[] Files, XPlatform[] Platforms)
        {
            List<string> errors = new List<string>();
            if (Files == null)
            {
                errors.Add("No files were included to inject...");
                return errors;
            }

            if(Platforms == null || Platforms.Length < 1)
            {
                errors.Add("No platforms are attached...");
                return errors;
            }

            foreach (XPlatform plat in Platforms)
            {
                ResetInjectionAddress(plat);
                ResetScriptParseTree(plat);
                errors.AddRange(GSXCustomFunctions.InjectFunctions(plat));
            }

            foreach (IGSCFile file in Files)
            {
                foreach(XPlatform plat in Platforms)
                {
                    GSCBuffer buffer = ResolveBuffer(XPlatformAsGSC(plat.PlatformID), !plat.IsZombies, file.ScriptName);
                    if (buffer != null)
                    {
                        bool result = InjectGSC_internal(plat, buffer, file.Bytes);
                        if(!result)
                            errors.Add("Error: " + file.ScriptName + " was unable to inject for platform " + plat.PlatformID.ToString());
                 
                    }
                    else
                    {
                        errors.Add("Error: " + file.ScriptName + " was not resolved for platform " + plat.PlatformID.ToString());
                    }
                }
            }  
            /*
            foreach(XPlatform plat in Platforms)
            {
                //errors.AddRange(XStringReducer.OptimizeScripts(plat));
                //if (plat.PlatformID == XPlatformType.PLATFORM_PS3_CCAPI)
                    //XStringReducer.CreateStaticRedux(plat);
            }
            */

            return errors;
        }

        internal static GSCBuffer ResolveBuffer(GSCPlatformType platform, bool IsMP, string ScriptName)
        {
            if (IsMP)
                return InjectionDatabase.BuffersList[platform].MPBuffers.ContainsKey(ScriptName) ? InjectionDatabase.BuffersList[platform].MPBuffers[ScriptName] : null;
            return InjectionDatabase.BuffersList[platform].ZMBuffers.ContainsKey(ScriptName) ? InjectionDatabase.BuffersList[platform].ZMBuffers[ScriptName] : null;
        }

        internal static GSCBuffer[] BuffersForPlatform(GSCPlatformType platform, bool IsMP)
        {
            List<GSCBuffer> buffers = new List<GSCBuffer>();
            //return InjectionDatabase.BuffersList[platform].MPBuffers.Values.ToArray();
            //return InjectionDatabase.BuffersList[platform].ZMBuffers.Values.ToArray();
            if (IsMP)
            {
                foreach (GSCBuffer buff in InjectionDatabase.BuffersList[platform].MPBuffers.Values)
                    if(!buffers.Contains(buff))
                        buffers.Add(buff);
            }
            else
            {
                foreach (GSCBuffer buff in InjectionDatabase.BuffersList[platform].ZMBuffers.Values)
                    if (!buffers.Contains(buff))
                        buffers.Add(buff);
            }
            return buffers.ToArray();
        }

        /// <summary>
        /// Gets all GSCs from a directory
        /// </summary>
        /// <param name="sDir"></param>
        /// <returns></returns>
        public static List<String> GetGSCFromDir(string sDir)
        {
            List<String> files = new List<String>();
            try
            {
                foreach (string f in Directory.GetFiles(sDir))
                {
                    if (f.Contains(".gsc")) //too lazy
                        files.Add(f);
                }
                foreach (string d in Directory.GetDirectories(sDir))
                {
                    files.AddRange(GetGSCFromDir(d));
                }
            }
            catch (System.Exception)
            {

            }

            return files;
        }

        /// <summary>
        /// Creates an IGSC from file info
        /// </summary>
        /// <param name="filename">The path to the file</param>
        /// <param name="scriptname">The script name (maps/mp/...(.gsc))</param>
        /// <returns>A new IGSCFile or null if an error occurs</returns>
        public static IGSCFile GetIGSCFromInfo(string filename, string scriptname)
        {
            try
            {
                return new IGSCFile() { Bytes = File.ReadAllBytes(filename), ScriptName = scriptname };
            }
            catch
            {

            }
            return null;
        }

        /// <summary>
        /// Creates the scriptname of a gsc from its file path. Must include maps/mp in the name
        /// </summary>
        /// <param name="s"></param>
        /// <returns></returns>
        public static string ScriptNameFromPath(string s)
        {
            s = s.ToLower().Replace('\\', '/');
            if (s.IndexOf("maps/mp") < 0)
                return "invalid_scriptname";
            return s.Substring(s.IndexOf("maps/mp"));
        }

        /// <summary>
        /// GSC file for injection
        /// </summary>
        public class IGSCFile
        {
            /// <summary>
            /// The scriptname of the file (maps/mp/*.gsc)
            /// </summary>
            public string ScriptName;
            /// <summary>
            /// The gsc data of the file
            /// </summary>
            public byte[] Bytes;
        }



        internal static GSCPlatformType XPlatformAsGSC(XPlatformType x)
        {
            switch (x)
            {
                case XPlatformType.PLATFORM_PC_REDACTED:
                    return GSCPlatformType.Redacted;
                case XPlatformType.PLATFORM_PC_STEAM:
                    return GSCPlatformType.PC;
                case XPlatformType.PLATFORM_PS3_CCAPI:
                case XPlatformType.PLATFORM_PS3_TMAPI:
                    return GSCPlatformType.PS3;
                default:
                    return GSCPlatformType.Xbox;

            }

        }

        private static Dictionary<GSCPlatformType, int> injection_point;
        private static Dictionary<GSCPlatformType, int> InjectionPoints
        {
            get
            {
                if(injection_point == null)
                {
                    injection_point = new Dictionary<GSCPlatformType, int>();
                    injection_point[GSCPlatformType.PS3] = 0;
                    injection_point[GSCPlatformType.PC] = 0;
                    injection_point[GSCPlatformType.Redacted] = 0;
                    injection_point[GSCPlatformType.Xbox] = 0;
                }
                return injection_point;
            }
        }

        private static Random R = new Random();
        private static int GetInjectionAddress(XPlatform x, int size, bool Fresh = false)
        {
            if (Fresh)
                ResetInjectionAddress(x);
            int toReturn = (int)GET_ALIGNED_DWORD((uint)InjectionPoints[XPlatformAsGSC(x.PlatformID)] + (uint)(R.Next(10,20) * 4));
            InjectionPoints[XPlatformAsGSC(x.PlatformID)] = toReturn + size;
            return toReturn;
        }

        /// <summary>
        /// Align a DWORD
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public static uint GET_ALIGNED_DWORD(uint x)
        {
            return ((x + 3) & 0xFFFFFFFC);
        }

        /// <summary>
        /// Align a WORD
        /// </summary>
        /// <param name="x"></param>
        /// <returns></returns>
        public static uint GET_ALIGNED_WORD(uint x)
        {
            return (uint)((x + ((x % 2 != 0) ? 1 : 0)));
        }

        private static void ResetInjectionAddress(XPlatform x)
        {
            InjectionPoints[XPlatformAsGSC(x.PlatformID)] = GetPlatformBaseAddress(x);
        }


        private static byte[] ExtractResource(String filename)
        {
            System.Reflection.Assembly a = System.Reflection.Assembly.GetExecutingAssembly();
            using (Stream resFilestream = a.GetManifestResourceStream(filename))
            {
                if (resFilestream == null) return null;
                byte[] ba = new byte[resFilestream.Length];
                resFilestream.Read(ba, 0, ba.Length);
                return ba;
            }
        }

        /*
           RPC PC: 0x28D05000 : 0x29500000
           RPC PS3: 0x10020000
           RPC XB360: 0x40300000
        */

        internal static int GetPlatformBaseAddress(XPlatform x)
        {
            switch (x.PlatformID)
            {
                case XPlatformType.PLATFORM_PS3_CCAPI:
                case XPlatformType.PLATFORM_PS3_TMAPI:
                    return 0x51000000;
                case XPlatformType.PLATFORM_XBOX360:
                    return 0x40305000 + 0x3000;
                case XPlatformType.PLATFORM_PC_STEAM:
                case XPlatformType.PLATFORM_PC_REDACTED:
                    if (x.IsZombies)
                        return 0x29500000 + 0x1060;
                    return 0x28D05000 + 0x1060;
            }
            return 0x00000000;
        }

        internal static void ReloadDB()
        {
            injection_database = null;
            InjectionDatabase.Access();
        }

    }

    internal class GSXInjectionDB
    {
        internal byte[] Magic = { 0x80, (byte)'G', (byte)'S', (byte)'X', (byte)'d', (byte)'b', 0x0D, 0x0A };
        internal int LocationNamesPtr;
        internal int BuffersPtr;
        internal int InjectionOffsetsPtr;


        internal int NumLocationNames;

        internal int NumBuffers;

        internal int NumOffsetLists;

        internal List<string> LocationNames = new List<string>();

        internal Dictionary<GSCPlatformType, GSCBuffersList> BuffersList = new Dictionary<GSCPlatformType, GSCBuffersList>();

        internal Dictionary<GSCPlatformType, OffsetList> OffsetLists = new Dictionary<GSCPlatformType, OffsetList>();

        public void LoadDB(byte[] database)
        {
            EndianReader Reader = new EndianReader(database, EndianType.LittleEndian);
            Reader.SeekTo(0x8);
            LocationNamesPtr = Reader.ReadInt32();
            BuffersPtr = Reader.ReadInt32();
            InjectionOffsetsPtr = Reader.ReadInt32();
            NumLocationNames = Reader.ReadInt32();
            NumBuffers = Reader.ReadInt32();
            NumOffsetLists = Reader.ReadInt32();
            Reader.SeekTo(LocationNamesPtr);
            for (int i = 0; i < NumLocationNames; i++)
            {
                string str = Reader.ReadNullTerminatedString();
                LocationNames.Add(str);
            }
            Reader.SeekTo(BuffersPtr);
            for (int i = 0; i < NumBuffers; i++)
            {
                GSCPlatformType Type = (GSCPlatformType)Reader.ReadByte();
                BuffersList[Type] = new GSCBuffersList() { PlatformType = Type };
                BuffersList[Type].NumberOfMPBuffers = Reader.ReadInt32();
                BuffersList[Type].NumberOfZMBuffers = Reader.ReadInt32();
                for (int j = 0; j < BuffersList[Type].NumberOfMPBuffers; j++)
                {
                    GSCBuffer Buffer = new GSCBuffer();
                    Buffer.PlatformType = Type;
                    Buffer.NamePtr = Reader.ReadInt32();
                    Buffer.PointerAddress = Reader.ReadInt32();
                    Buffer.BufferPtr = Reader.ReadInt32();
                    long offset = Reader.BaseStream.Position;
                    Reader.SeekTo(Buffer.NamePtr);
                    string name = Reader.ReadNullTerminatedString();
                    Reader.SeekTo(offset);
                    BuffersList[Type].MPBuffers[name] = Buffer;
                }
                for (int j = 0; j < BuffersList[Type].NumberOfZMBuffers; j++)
                {
                    GSCBuffer Buffer = new GSCBuffer();
                    Buffer.PlatformType = Type;
                    Buffer.NamePtr = Reader.ReadInt32();
                    Buffer.PointerAddress = Reader.ReadInt32();
                    Buffer.BufferPtr = Reader.ReadInt32();
                    long offset = Reader.BaseStream.Position;
                    Reader.SeekTo(Buffer.NamePtr);
                    string name = Reader.ReadNullTerminatedString();
                    Reader.SeekTo(offset);
                    BuffersList[Type].ZMBuffers[name] = Buffer;
                }
            }
            Access();
        }

        public void Access()
        {

        }

        public void Drop()
        {
            LocationNames.Clear();
            BuffersList.Clear();
            OffsetLists.Clear();
        }
    }

    internal class GSCBuffersList
    {
        internal GSCPlatformType PlatformType;
        internal int NumberOfMPBuffers;
        internal int NumberOfZMBuffers;
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
        internal GSCPlatformType PlatformType;
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
        Redacted
    }

    internal enum GSCInjectionType : byte
    {


    }

}
