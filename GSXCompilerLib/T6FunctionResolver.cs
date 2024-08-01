using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace GSXCompilerLib
{
    internal static class T6FunctionResolver
    {
        private static byte[] bytes;
        private static byte[] Bytes
        {
            get
            {
                if(bytes == null)
                {
                    bytes = ExtractResource("GSXCompilerLib.FunctionResolve.db");
                }
                return bytes;
            }
        }

        private static string[] functions;
        public static string[] Functions
        {
            get
            {
                if(functions == null)
                {
                    var assembly = Assembly.GetExecutingAssembly();
                    var resourceName = "GSXCompilerLib.functions.txt";

                    using (Stream stream = assembly.GetManifestResourceStream(resourceName))
                    using (StreamReader reader = new StreamReader(stream))
                    {
                        string result = reader.ReadToEnd();
                        string[] split = result.Split('\n', '\r');
                        for (int i = 0; i < split.Length; i++)
                            split[i] = split[i].ToLower();
                        functions = split;
                    }
                    
                }
                return functions;
            }

        }

        private static T6GSXFuncResolveDB resolver;
        private static T6GSXFuncResolveDB Resolver
        {
            get
            {
                if(resolver == null)
                {
                    resolver = new T6GSXFuncResolveDB();
                    resolver.LoadDB(Bytes, Functions);
                }
                return resolver;
            }
        }

        /// <summary>
        /// Try to resolve a function from the database
        /// </summary>
        /// <returns></returns>
        public static FunctionResolution ResolveFunctionFromLib(string name, byte ParamCount, List<string> includes, string Namespace = "")
        {
            FunctionResolution Res = Resolver.LookUp(name, ParamCount, Namespace, false);
            if (!Res.IsError || Namespace != "")
                return Res;
            FunctionResolution IncludeRes = Resolver.LookUp(name, ParamCount, Namespace, false);
            foreach (string s in includes)
            {
                IncludeRes = Resolver.LookUp(name, ParamCount, s, true);
                if (!IncludeRes.IsError)
                    return IncludeRes;
            }
            return Res;
        }

        /*
        public static void BreakpointTest()
        {
            var link = Resolver.AssetExports;
            bp:;
        }
        */
        /// <summary>
        /// Updates a the library with an updated gsc to parse
        /// </summary>
        public static byte UpdateLib(string name, byte[] GSC, EndianType Type)
        {
            if (!Resolver.AssetExports.ContainsKey(name))
                return 1;
            try
            {
                Resolver.AssetExports[name].Exports.Clear();
                EndianReader Reader = new EndianReader(GSC, Type);
                Reader.SeekTo(0x1C);
                uint ExportsPtr = Reader.ReadUInt32();
                Reader.SeekTo(0x34);
                ushort ExportsCount = Reader.ReadUInt16();
                Reader.SeekTo(ExportsPtr);
                for (int i = 0; i < ExportsCount; i++)
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
                    if (!Resolver.AssetExports[name].Exports.ContainsKey(exportkey))
                        Resolver.AssetExports[name].Exports[exportkey] = new Export();
                    Resolver.AssetExports[name].Exports[exportkey].PtrToName = -1;
                    Resolver.AssetExports[name].Exports[exportkey].NumParams = Numparams;
                }
            }
            catch(Exception e)
            {
                string temp = e.Message;
                string temp2 = e.StackTrace.ToString();
                return 2;
            }
            return 0;
        }

        /// <summary>
        /// Reset the library to the default state
        /// </summary>
        public static void ResetLib()
        {
            resolver = new T6GSXFuncResolveDB();
            resolver.LoadDB(Bytes, Functions);
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

        internal class T6GSXFuncResolveDB
        {
            internal byte[] Magic = { 0x80, 0x47, 0x53, 0x58, 0x64, 0x62, 0x0A, 0x00 };
            internal int PtrToEntries; //0x8
            internal int PtrToAssetNames; //0xC
            internal int PtrToAssetExports; //0x10
            internal int NumEntries;        //0x14
            internal int NumAssetNames;  //0x18
            internal int NumAssetExports;    //0x1C
            internal Dictionary<string, AssetExportList> AssetExports = new Dictionary<string, AssetExportList>();

            public void LoadDB(byte[] DataBase, string[] Functions)
            {
                EndianReader Reader = new EndianReader(DataBase, EndianType.LittleEndian);
                Reader.ReadUInt64();
                PtrToEntries = Reader.ReadInt32();
                PtrToAssetNames = Reader.ReadInt32();
                PtrToAssetExports = Reader.ReadInt32();
                NumEntries = Reader.ReadInt32();
                NumAssetNames = Reader.ReadInt32();
                NumAssetExports = Reader.ReadInt32();
                Reader.SeekTo(PtrToAssetExports);
                for(int i = 0; i < NumAssetExports; i++)
                {
                    AssetExportList List = new AssetExportList();
                    List.PtrToName = Reader.ReadInt32();
                    long position = Reader.BaseStream.Position;
                    Reader.SeekTo(List.PtrToName);
                    string name = Reader.ReadNullTerminatedString();
                    Reader.SeekTo(position);
                    List.ExportCount = Reader.ReadInt32();
                    for(int j = 0; j < List.ExportCount; j++)
                    {
                        Export export = new Export();
                        export.PtrToName = Reader.ReadInt32();
                        export.NumParams = Reader.ReadByte();
                        position = Reader.BaseStream.Position;
                        Reader.SeekTo(export.PtrToName);
                        string exportname = Reader.ReadNullTerminatedString();
                        Reader.SeekTo(position);
                        List.Exports[exportname + "?" + export.NumParams] = export;
                    }
                    AssetExports[name] = List;
                }
            }
            /// <summary>
            /// TODO Check name when ns is undefined from includes
            /// </summary>
            /// <param name="name"></param>
            /// <param name="ParamCount"></param>
            /// <param name="Namespace"></param>
            /// <returns></returns>
            public FunctionResolution LookUp(string name, byte ParamCount, string Namespace, bool UsingInclude)
            {
                name = name.ToLower();
                string TEMP = "";
                if (Namespace == "")
                {
                    if (LookUpInternal(name))
                        return new FunctionResolution() { Namespace = "", Internal = true, Name = name, NumParams = ParamCount, IsError = false };
                    if(GSXCustomFunctions.ResolveFunction(name, ParamCount))
                        return new FunctionResolution() { Namespace = "", Internal = true, Name = name, NumParams = ParamCount, IsError = false };
                }
                else
                {
                    Namespace = Namespace.ToLower().Replace('\\', '/').Replace(".gsc", "") + ".gsc";
                    if (!AssetExports.ContainsKey(Namespace))
                        return new FunctionResolution() { Namespace = Namespace, Internal = false, Name = name, NumParams = ParamCount, IsError = true, FailureType = 1, UsingInclude = UsingInclude };

                    if (AssetExports[Namespace].Exports.ContainsKey(name + "?" + ParamCount))
                    {
                        return new FunctionResolution() { Namespace = Namespace, Internal = false, Name = name, NumParams = ParamCount, IsError = false };
                    }

                    foreach (string key in AssetExports[Namespace].Exports.Keys)
                    {
                        if(AssetExports[Namespace].Exports[key].NumParams >= ParamCount)
                        {
                            if (key.Split('?')[0].ToLower().Equals(name))
                                return new FunctionResolution() { Namespace = Namespace, Internal = false, Name = name, NumParams = ParamCount, IsError = false };
                            TEMP += "\nkey: " + key.Split('?')[0].ToLower() + " Name: " + name;
                        }
                        else
                        {
                            TEMP += "\nkey: " + key.Split('?')[0].ToLower() + " Name: " + name + " Params " + AssetExports[Namespace].Exports[key].NumParams + ":" +ParamCount;
                        }
                    }
                    Namespace += TEMP;
                    return new FunctionResolution() { Namespace = Namespace, Internal = false, Name = name, NumParams = ParamCount, IsError = true, FailureType = 2, UsingInclude = UsingInclude };
                }
/*
                foreach(string s in AssetExports.Keys)
                {
                    if (AssetExports[s].Exports.ContainsKey(name + "?" + ParamCount))
                    {
                        return new FunctionResolution() { Namespace = s, Internal = false, Name = name, NumParams = ParamCount, IsError = false };
                    }

                    foreach (string key in AssetExports[s].Exports.Keys)
                    {
                        if (AssetExports[s].Exports[key].NumParams >= ParamCount)
                            if (key.Split('?')[0].ToLower().Equals(name))
                                return new FunctionResolution() { Namespace = s, Internal = false, Name = name, NumParams = ParamCount, IsError = false };
                    }
                }
*/
                return new FunctionResolution() { Namespace = "", Internal = false, Name = name, NumParams = ParamCount, IsError = true, FailureType = 4, UsingInclude = UsingInclude };
            }

            public bool LookUpInternal(string name)
            {
                return Functions.Contains(name.ToLower());
            }
        }

        internal class AssetExportList
        {
            internal int PtrToName;
            internal int ExportCount;
            internal Dictionary<string, Export> Exports = new Dictionary<string, Export>();
        }

        internal class Export
        {
            internal int PtrToName;
            internal byte NumParams;
        }

        internal struct FunctionResolution
        {
            internal string Namespace;
            internal string Name;
            internal byte NumParams;
            internal bool Internal;
            internal bool IsError;
            internal byte FailureType;
            internal bool UsingInclude;
        }
    }
}
