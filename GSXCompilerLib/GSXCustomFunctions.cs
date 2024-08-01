using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace GSXCompilerLib
{
    /// <summary>
    /// All custom GSC functions written to memory at injection time
    /// </summary>
    public static class GSXCustomFunctions
    {
        #region User
        private static List<GSXFunction> LoadedFunctions = new List<GSXFunction>();

        /// <summary>
        /// Clears all user loaded functions
        /// </summary>
        public static void ClearCustomFunctions()
        {
            LoadedFunctions.Clear();
        }

        /// <summary>
        /// Adds a custom function to the list of loaded functions to write to memory
        /// </summary>
        /// <param name="f"></param>
        public static void AddCustomFunction(GSXFunction f)
        {
            LoadedFunctions.Add(f);
        }

        /// <summary>
        /// Returns the number of custom functions currently loaded into memory
        /// </summary>
        /// <returns></returns>
        public static int GetNumCustomFunctions()
        {
            return LoadedFunctions.Count;
        }

        /// <summary>
        /// Gets a list of custom functions that will be injected
        /// </summary>
        /// <returns></returns>
        public static List<GSXFunction> GetCustomFunctions()
        {
            return LoadedFunctions;
        }

        #endregion


        private static List<GSXFunction> internal_functions;
        private static List<GSXFunction> InternalFunctions
        {
            get
            {
                if(internal_functions == null)
                {
                    internal_functions = new List<GSXFunction>();
                    internal_functions.AddRange(LoadInternalFunctions());
                }
                return internal_functions;
            }
        }

        private static GSXFunction[] LoadInternalFunctions()
        {
            GSXFunction[] Functions = null;
            try
            {
                byte[] internalsArray = GetInternals();
                Functions = LoadFunctionsFromBytes(internalsArray);
            }
            catch
            {

            }
            return Functions;
        }

        private static byte[] GetInternals()
        {
            System.Reflection.Assembly a = System.Reflection.Assembly.GetExecutingAssembly();
            using (Stream resFilestream = a.GetManifestResourceStream("GSXCompilerLib.internals.bin"))
            {
                if (resFilestream == null) return null;
                byte[] ba = new byte[resFilestream.Length];
                resFilestream.Read(ba, 0, ba.Length);
                return ba;
            }
        }

        /// <summary>
        /// Returns whether a function exists in the database or not
        /// </summary>
        /// <param name="name"></param>
        /// <param name="paramcount"></param>
        /// <returns></returns>
        internal static bool ResolveFunction(string name, int paramcount)
        {
            foreach(GSXFunction f in InternalFunctions)
            {
                if (f.FunctionName == name.ToLower() && f.MaximumParams >= paramcount && f.MinimumParams <= paramcount)
                    return true;
            }

            foreach (GSXFunction f in LoadedFunctions)
            {
                if (f.FunctionName == name.ToLower() && f.MaximumParams >= paramcount && f.MinimumParams <= paramcount)
                    return true;
            }

            return false;
        }

        /// <summary>
        /// Save all custom functions to the filename specified
        /// </summary>
        /// <param name="filename"></param>
        public static void SaveCustomFunctions(string filename)
        {
            List<byte> FileToWrite = new List<byte>();
            FileToWrite.AddRange(BitConverter.GetBytes(LoadedFunctions.Count));
            foreach(GSXFunction f in LoadedFunctions)
            {
                IFormatter formatter = new BinaryFormatter();
                using (MemoryStream stream = new MemoryStream())
                {
                    formatter.Serialize(stream, f);
                    byte[] contents = stream.ToArray();
                    FileToWrite.AddRange(BitConverter.GetBytes(contents.Length));
                    FileToWrite.AddRange(contents);
                }
            }
            File.WriteAllBytes(filename, FileToWrite.ToArray());
        }

        /// <summary>
        /// Load all custom functions from the filename specified. Does not clear loaded functions
        /// </summary>
        /// <param name="filename"></param>
        public static void LoadCustomFunctions(string filename)
        {
            byte[] file = File.ReadAllBytes(filename);
            GSXFunction[] functions = LoadFunctionsFromBytes(file);
            foreach(var function in functions)
            {
                AddCustomFunction(function);
            }
        }

        private static GSXFunction[] LoadFunctionsFromBytes(byte[] file)
        {
            int NumEntries = BitConverter.ToInt32(file, 0);
            int index = sizeof(int);
            GSXFunction[] functions = new GSXFunction[NumEntries];
            for (int i = 0; i < NumEntries; i++)
            {
                int EntrySize = BitConverter.ToInt32(file, index);
                index += sizeof(int);
                byte[] Entry = new byte[EntrySize];
                for (int j = 0; j < EntrySize; j++, index++)
                {
                    Entry[j] = file[index];
                }
                IFormatter formatter = new BinaryFormatter();
                using (MemoryStream stream = new MemoryStream(Entry))
                {
                    functions[i] = (GSXFunction)formatter.Deserialize(stream);
                }
            }
            return functions;
        }

        /// <summary>
        /// Inject all custom functions to memory and update the target structs. Returns a list of errors
        /// </summary>
        /// <param name="TargetPlatform"></param>
        /// <returns></returns>
        public static List<string> InjectFunctions(XPlatform TargetPlatform)
        {
            List<string> Errors = new List<string>();
            List<GSXFunction> AllFunctions = new List<GSXFunction>();
            AllFunctions.AddRange(LoadedFunctions);
            AllFunctions.AddRange(InternalFunctions);
            ResetInjectionAddress(GSXInjector.XPlatformAsGSC(TargetPlatform.PlatformID));
            foreach(GSXFunction f in AllFunctions)
            {
                string error = "";
                if(f.FunctionName == null)
                {
                    error = "Error Injecting Custom Function 'null' -- Function does not have a name!";
                    goto error;
                }
                if (GetTargetLocation(TargetPlatform, f) == 0 || GetTargetBytes(TargetPlatform, f) == null)
                {
                    error = "Error Injecting Custom Function '" + f.FunctionName + "' -- Target was selected but does not include the required data to inject!";
                    goto error;
                }

                error = Inject_internal(TargetPlatform, f);

                error: if(error != "")
                {
                    Errors.Add(error);
                }
            }


            return Errors;
        }

        private static string Inject_internal(XPlatform TargetPlatform, GSXFunction function)
        {
            string result = "";
            try
            {
                BuiltinFunctionDef def = new BuiltinFunctionDef();
                UInt32 TargetLocation = GetTargetLocation(TargetPlatform, function);
                byte[] IntBuffer = new byte[4];
                #region UglyCode

                bool ReadSuccess = TargetPlatform.ReadBytes((uint)TargetLocation, 4, out IntBuffer);
                if (!ReadSuccess)
                {
                    result = "Failed to read critical data from the target platform!";
                    goto error;
                }
                def.NamePtr = ToInt(TargetPlatform.PlatformID, IntBuffer);
                ReadSuccess = TargetPlatform.ReadBytes((uint)TargetLocation + 4, 4, out IntBuffer);
                if (!ReadSuccess)
                {
                    result = "Failed to read critical data from the target platform!";
                    goto error;
                }
                def.ID = ToInt(TargetPlatform.PlatformID, IntBuffer);
                ReadSuccess = TargetPlatform.ReadBytes((uint)TargetLocation + 8, 4, out IntBuffer);
                if (!ReadSuccess)
                {
                    result = "Failed to read critical data from the target platform!";
                    goto error;
                }
                def.MinArgs = ToInt(TargetPlatform.PlatformID, IntBuffer);
                ReadSuccess = TargetPlatform.ReadBytes((uint)TargetLocation + 12, 4, out IntBuffer);
                if (!ReadSuccess)
                {
                    result = "Failed to read critical data from the target platform!";
                    goto error;
                }
                def.MaxArgs = ToInt(TargetPlatform.PlatformID, IntBuffer);
                ReadSuccess = TargetPlatform.ReadBytes((uint)TargetLocation + 16, 4, out IntBuffer);
                if (!ReadSuccess)
                {
                    result = "Failed to read critical data from the target platform!";
                    goto error;
                }
                def.FuncRefPtr = ToInt(TargetPlatform.PlatformID, IntBuffer);

                List<byte> NameBytes = new List<byte>();
                NameBytes.AddRange(Encoding.ASCII.GetBytes(function.FunctionName));//function.FunctionName
                NameBytes.Add(0x0);

                bool WriteSuccess;

                if(TargetPlatform.PlatformID == XPlatformType.PLATFORM_PC_STEAM)
                {
                    uint strAddress = GetSteamStringsAddress((uint)NameBytes.Count);
                    WriteSuccess = TargetPlatform.WriteInt(TargetLocation, (int)strAddress);
                    if (!WriteSuccess)
                    {
                        result = "Failed to write critical data to the target platform!";
                        goto error;
                    }
                    WriteSuccess = TargetPlatform.WriteBytes(strAddress, NameBytes.ToArray());
                    if (!WriteSuccess)
                    {
                        result = "Failed to write critical data to the target platform!";
                        goto error;
                    }
                }
                else
                {
                    WriteSuccess = TargetPlatform.WriteBytes(def.NamePtr, NameBytes.ToArray());
                    if (!WriteSuccess)
                    {
                        result = "Failed to write critical data to the target platform!";
                        goto error;
                    }
                }
                
                WriteSuccess = TargetPlatform.WriteInt((uint)TargetLocation + 8, function.MinimumParams);
                if (!WriteSuccess)
                {
                    result = "Failed to write critical data to the target platform!";
                    goto error;
                }
                WriteSuccess = TargetPlatform.WriteInt((uint)TargetLocation + 12, function.MaximumParams);
                if (!WriteSuccess)
                {
                    result = "Failed to write critical data to the target platform!";
                    goto error;
                }
                #endregion
                byte[] TargetBytes = GetTargetBytes(TargetPlatform, function);
                int InjectionAddress = GetInjectionAddress(GSXInjector.XPlatformAsGSC(TargetPlatform.PlatformID), TargetBytes.Length);
                WriteSuccess = TargetPlatform.WriteBytes((uint)InjectionAddress, TargetBytes, 0x40); //Need executing priviledges in this region
                if (!WriteSuccess)
                {
                    result = "Failed to write critical data to the target platform!";
                    goto error;
                }
                if(TargetPlatform.PlatformID == XPlatformType.PLATFORM_PS3_CCAPI || TargetPlatform.PlatformID == XPlatformType.PLATFORM_PS3_TMAPI)
                    WriteSuccess = TargetPlatform.WriteInt(def.FuncRefPtr, InjectionAddress);
                else
                    WriteSuccess = TargetPlatform.WriteInt((uint)TargetLocation + 16, InjectionAddress); //0048B3F0 nullsub
                if (!WriteSuccess)
                {
                    result = "Failed to write critical data to the target platform!";
                    goto error;
                }
                
            }
            catch
            {
                result = "Error Injecting Custom Function '" + function.FunctionName + "' -- An internal exception occurred when trying to inject";
            }

            error: return result;
        }

        private static uint ToInt(XPlatformType p, byte[] b)
        {
            if (p == XPlatformType.PLATFORM_PC_REDACTED || p == XPlatformType.PLATFORM_PC_STEAM)
                return BitConverter.ToUInt32(b, 0);
            return BitConverter.ToUInt32(b.Reverse<byte>().ToArray<byte>(), 0);
        }

        private static UInt32 GetTargetLocation(XPlatform p, GSXFunction f)
        {
            switch(p.PlatformID)
            {
                case XPlatformType.PLATFORM_PS3_CCAPI:
                case XPlatformType.PLATFORM_PS3_TMAPI:
                    return f.PS3OverwriteTargetAddress;
                case XPlatformType.PLATFORM_XBOX360:
                    return f.XB360OverwriteTargetAddress;
                case XPlatformType.PLATFORM_PC_STEAM:
                    if (p.IsZombies)
                        return f.SteamZMOverwriteTargetAddress;
                    return f.SteamMPOverwriteTargetAddress;
                case XPlatformType.PLATFORM_PC_REDACTED:
                    if (p.IsZombies)
                        return f.RedactedZMOverwriteTargetAddress;
                    return f.RedactedMPOverwriteTargetAddress;

            }
            return 0;
        }

        private static byte[] GetTargetBytes(XPlatform p, GSXFunction f)
        {
            switch(p.PlatformID)
            {
                case XPlatformType.PLATFORM_PS3_CCAPI:
                case XPlatformType.PLATFORM_PS3_TMAPI:
                    return f.PS3_PPCCode;
                case XPlatformType.PLATFORM_XBOX360:
                    return f.XB360_PPCCode;
                case XPlatformType.PLATFORM_PC_REDACTED:
                    if (p.IsZombies)
                        return f.Redacted_zm_x86Code;
                    return f.Redacted_mp_x86Code;
                case XPlatformType.PLATFORM_PC_STEAM:
                    if (p.IsZombies)
                        return f.Steam_zm_x86Code;
                    return f.Steam_mp_x86Code;
            }
            return null;
        }



        private static void ResetInjectionAddress(GSCPlatformType type)
        {
            switch (type)
            {
                case GSCPlatformType.PS3:
                    InjectionPoints[GSCPlatformType.PS3] = GetPlatformBaseAddress(XPlatformType.PLATFORM_PS3_CCAPI);
                    break;
                case GSCPlatformType.PC:
                    InjectionPoints[GSCPlatformType.PC] = GetPlatformBaseAddress(XPlatformType.PLATFORM_PC_STEAM);
                    break;
                case GSCPlatformType.Redacted:
                    InjectionPoints[GSCPlatformType.Redacted] = GetPlatformBaseAddress(XPlatformType.PLATFORM_PC_REDACTED);
                    break;
                case GSCPlatformType.Xbox:
                    InjectionPoints[GSCPlatformType.Xbox] = GetPlatformBaseAddress(XPlatformType.PLATFORM_XBOX360);
                    break;

            }
            ResetSteamStringsAddress();
        }


        private static Dictionary<GSCPlatformType, int> injection_point;
        private static Dictionary<GSCPlatformType, int> InjectionPoints
        {
            get
            {
                if (injection_point == null)
                {
                    injection_point = new Dictionary<GSCPlatformType, int>();
                    injection_point[GSCPlatformType.PS3] = GetPlatformBaseAddress(XPlatformType.PLATFORM_PS3_CCAPI);
                    injection_point[GSCPlatformType.PC] = GetPlatformBaseAddress(XPlatformType.PLATFORM_PC_STEAM);
                    injection_point[GSCPlatformType.Redacted] = GetPlatformBaseAddress(XPlatformType.PLATFORM_PC_REDACTED);
                    injection_point[GSCPlatformType.Xbox] = GetPlatformBaseAddress(XPlatformType.PLATFORM_XBOX360);
                }
                return injection_point;
            }
        }

        internal static int GetPlatformBaseAddress(XPlatformType type)
        {
            switch (type)
            {
                case XPlatformType.PLATFORM_PS3_CCAPI:
                case XPlatformType.PLATFORM_PS3_TMAPI:
                    return 0x00D494B8;
                case XPlatformType.PLATFORM_XBOX360:
                    return 0x40300000 + 0x3000;
                case XPlatformType.PLATFORM_PC_STEAM:
                case XPlatformType.PLATFORM_PC_REDACTED:
                    return 0xb71000;
            }
            return 0x00000000;
        }

        internal static uint SteamStringsAddress = 0xb70bf0;

        internal static uint GetSteamStringsAddress(uint stringsize)
        {
            uint ToReturn = SteamStringsAddress;
            SteamStringsAddress += stringsize;
            return ToReturn;
        }

        internal static void ResetSteamStringsAddress()
        {
            SteamStringsAddress = 0xb70bf0;
        }

        private static Random R = new Random();
        private static int GetInjectionAddress(GSCPlatformType type, int size, bool Fresh = false)
        {
            if (Fresh)
                ResetInjectionAddress(type);
            int toReturn = ALIGN_16(InjectionPoints[type] + (R.Next(10, 20) * 4));
            InjectionPoints[type] = toReturn + size;
            return toReturn;
        }

        private static int ALIGN_16(int i)
        {
            while (i % 16 != 0)
                i++;
            return i;
        }

        /// <summary>
        /// Function wrapper for a GSX Function
        /// </summary>
        [Serializable]
        public sealed class GSXFunction
        {
            private string f_name;
            /// <summary>
            /// The name of the function when its called in a script. Must be smaller than the target name
            /// </summary>
            public string FunctionName
            {
                get
                {
                    return f_name;
                }
                set
                {
                    f_name = value.ToLower();
                }
            }

            /// <summary>
            /// Lowest number of parameters accepted to not throw a script error
            /// </summary>
            public int MinimumParams;

            /// <summary>
            /// Highest number of parameters accepted to not throw a script error
            /// </summary>
            public int MaximumParams;

            /// <summary>
            /// The address of the target BuiltinFunctionDef to overwrite for the PS3 Platform
            /// </summary>
            public UInt32 PS3OverwriteTargetAddress;

            /// <summary>
            /// The address of the target BuiltinFunctionDef to overwrite for the Xbox 360 Platform
            /// </summary>
            public UInt32 XB360OverwriteTargetAddress;

            /// <summary>
            /// The address of the target BuiltinFunctionDef to overwrite for the Steam Platform on Multiplayer
            /// </summary>
            public UInt32 SteamMPOverwriteTargetAddress;

            /// <summary>
            /// The address of the target BuiltinFunctionDef to overwrite for the Steam Platform on Zombies
            /// </summary>
            public UInt32 SteamZMOverwriteTargetAddress;

            /// <summary>
            /// The address of the target BuiltinFunctionDef to overwrite for the Redacted Platform on Multiplayer
            /// </summary>
            public UInt32 RedactedMPOverwriteTargetAddress;

            /// <summary>
            /// The address of the target BuiltinFunctionDef to overwrite for the Redacted Platform on Zombies
            /// </summary>
            public UInt32 RedactedZMOverwriteTargetAddress;

            /// <summary>
            /// The ppc code for the function for PS3
            /// </summary>
            public byte[] PS3_PPCCode;

            /// <summary>
            /// The ppc code for the function for Xbox 360
            /// </summary>
            public byte[] XB360_PPCCode;

            /// <summary>
            /// The x86 code for the function for Steam MP
            /// </summary>
            public byte[] Steam_mp_x86Code;

            /// <summary>
            /// The x86 code for the function for Steam ZM
            /// </summary>
            public byte[] Steam_zm_x86Code;

            /// <summary>
            /// The x86 code for the function for Redacted MP
            /// </summary>
            public byte[] Redacted_mp_x86Code;

            /// <summary>
            /// The x86 code for the function for Redacted ZM
            /// </summary>
            public byte[] Redacted_zm_x86Code;
        }

        internal struct BuiltinFunctionDef
        {
            internal UInt32 NamePtr;
            internal UInt32 ID;
            internal UInt32 MinArgs;
            internal UInt32 MaxArgs;
            internal UInt32 FuncRefPtr;
        }
    }
}
