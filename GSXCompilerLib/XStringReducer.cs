using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using static GameScriptCompiler_v3.ScriptCompiler;
namespace GSXCompilerLib
{

    public static class XStringReducer
    {

        /*  Note: Only rewrite needed is the full strings section, because remember, number of total refs dont change, only the key strings.
            Steps:
                1: Retreive a list of injection locations from the database
                2: Iterate gscs and for each script
                    - Iterate code sections and collect all local references, and replacement globals, including foreach calls
                    - Replace local variable names to global keys to lower string count by:
                        > Using string ref sections to include this location
        */

        internal class XString
        {
            internal bool PublicUse;
            internal byte StringType;
            internal string Name;
            internal int NumberOfReferences
            {
                get
                {
                    return References.Count;
                }
            }

            internal ushort NamePtr;

            internal List<uint> References = new List<uint>();
        }

        internal class XFunction
        {
            internal uint Start { get; set; }
            internal byte NumofParameters { get; set; }
            //internal List<uint> StrRefs = new List<uint>();
            internal List<uint> Locals = new List<uint>();
        }


        /// <summary>
        /// Optimize the entire script environment
        /// </summary>
        /// <param name="platform"></param>
        /// <returns></returns>
        public static List<string> OptimizeScripts(XPlatform platform, GSXInjector.IGSCFile[] DontOptimize)
        {
            if (platform == null || platform.HasBeenOptimized)
                return new List<string>();
            if (platform.PlatformID != XPlatformType.PLATFORM_PC_REDACTED && platform.PlatformID != XPlatformType.PLATFORM_PC_STEAM)
                return StaticRedux(platform, DontOptimize);
            platform.HasBeenOptimized = true;
            List<string> errors = new List<string>();
            List<GSCBuffer> buffers = GSXInjector.BuffersForPlatform(GSXInjector.XPlatformAsGSC(platform.PlatformID), !platform.IsZombies).ToList();

            foreach(var file in DontOptimize)
            {
                GSCBuffer buffer = GSXInjector.ResolveBuffer(GSXInjector.XPlatformAsGSC(platform.PlatformID), !platform.IsZombies, file.ScriptName);
                if (buffer == null)
                    continue;
                if (buffers.Contains(buffer))
                    buffers.Remove(buffer);
                else
                {
                    for(int i = 0; i < buffers.Count; i++)
                    {
                        if (buffers[i] == null)
                            continue;
                        if(buffers[i].PointerAddress == buffer.PointerAddress)
                        {
                            buffers.RemoveAt(i);
                            i--;
                        }
                    }
                }
            }


            List<XString> XStrings = new List<XString>();
            Dictionary<uint, XString> RefMap = new Dictionary<uint, XString>();
            uint StringsPointer;
            int NumRefStringsPtr;
            bool result;
            ushort NumRefStrings;
            uint RefStringsPtr;
            uint index;
            ushort NamePtr;
            string Name = "";
            byte NumRefs = 0;
            byte Type = 0;
            uint ptr = 0;
            uint FunctionsStart = 0;
            ushort FunctionsCount = 0;
            uint CodeStart = 0;
            byte NumParams = 0;
            uint CodeSectionSize = 0;
            List<XFunction> Functions = new List<XFunction>();
            uint CurrentSize = 0;
            byte[] FunctionCode = null;
            int NumStringsSaved = 0;
            int RefDataSize = 0;
            uint bufferPtr;
            ushort NumFixups;
            foreach (GSCBuffer buffer in buffers)
            {
                try
                {
                    //Reset variables
                    XStrings.Clear();
                    Functions.Clear();
                    RefMap.Clear();
                    NamePtr = 0;
                    result = platform.ReadUInt((uint)buffer.PointerAddress, out bufferPtr);
                    if (!result)
                    {
                        errors.Add("SE String Reduction failed due to a critical read failure (RE-105)");
                        goto skipfile;
                    }

                    StringsPointer = (uint)bufferPtr + 0x18;
                    NumRefStringsPtr = (int)bufferPtr + 0x32;

                    result = platform.ReadUshort((uint)NumRefStringsPtr, out NumRefStrings);
                    if (!result)
                    {
                        errors.Add("SE String Reduction failed due to a critical read failure (RE-108)");
                        goto skipfile;
                    }
                    if (NumRefStrings < 1) //why optimize an empty script...?
                        goto skipfile;

                    result = platform.ReadUInt((uint)StringsPointer, out RefStringsPtr);
                    if (!result)
                    {
                        errors.Add("SE String Reduction failed due to a critical read failure (RE-117)");
                        goto skipfile;
                    }

                    result = platform.ReadUInt((uint)(bufferPtr + 0x1C), out FunctionsStart);
                    if (!result)
                        goto skipfile;

                    result = platform.ReadUshort((uint)(bufferPtr + 0x34), out FunctionsCount);
                    if (!result)
                        goto skipfile;

                    result = platform.ReadUshort((uint)(bufferPtr + 0x38), out NumFixups);
                    if (result && NumFixups > 0) //Fixups cause lots of issues. Skip these files because chances are that it will break the whole operation
                        goto skipfile;

                    //First, Collect the ref strings from the file and load them into memory, along with some mapping for performance reasons (specifically, o(1) vs o(n^2))
                    index = (uint)bufferPtr + RefStringsPtr;
                    byte[] RefData;
                    for (int i = 0; i < NumRefStrings; i++)
                    {
                        result = platform.ReadBytes((uint)index, 4, out RefData); //Read name pointer for refstring
                        if (!result)
                            break;

                        /*
                        result = platform.ReadString((uint)bufferPtr + NamePtr, out Name); //Read name for refstring
                        if (!result)
                            break;
                        */

                        XString str = null;
                        index += 4;
                        byte[] targetdata = new byte[] { RefData[0], RefData[1] };
                        if (!platform.IsPC)
                            targetdata = targetdata.Reverse<byte>().ToArray<byte>();

                        NamePtr = BitConverter.ToUInt16(targetdata, 0);
                        NumRefs = RefData[2];
                        Type = RefData[3];


                        if (Type > 1)
                        {
                            errors.Add("SE String Reduction failed due to an unexpected string type in the string table... (RE-154)");
                            goto end;
                        }
                        //Find the string associated with this ref. If not found, create one to match it.
                        foreach (XString xstr in XStrings.Where(xstr => xstr.NamePtr == NamePtr && xstr.StringType == Type))
                        {
                            str = xstr;
                            goto Found;
                        }
                        str = new XString();
                        //str.Name = Name;
                        str.StringType = Type;
                        str.NamePtr = NamePtr;
                        XStrings.Add(str);

                        
                        Found:
                        byte[] data;
                        platform.ReadBytes(index, (uint)NumRefs * 4, out data);
                        index += (uint)data.Length;
                        byte[] Temp;

                        for (byte j = 0; j < NumRefs; j++)
                        {
                            //index = GSXInjector.GET_ALIGNED_DWORD(index);
                            Temp = new byte[] { data[j * 4], data[j * 4 + 1], data[j * 4 + 2], data[j * 4 + 3] };
                            if (!platform.IsPC)
                                Temp = Temp.Reverse<byte>().ToArray<byte>();
                            ptr = BitConverter.ToUInt32(Temp, 0);
                            str.References.Add(ptr);
                            RefMap[ptr] = str;
                            //index += sizeof(uint);
                        }

                        RefDataSize += 4 + (NumRefs * 4);
                    }


                    //Then, iterate the function headers and parse them into memory as well
                    index = (uint)bufferPtr + FunctionsStart;
                    for(int i = 0; i < FunctionsCount; i++)
                    {
                        index += sizeof(uint); //Skip crc32
                        result = platform.ReadUInt((uint)(index), out CodeStart); //Read bytecode ref start
                        if (!result)
                            continue;

                        index += sizeof(uint) + sizeof(ushort); //Skip name
                        /*
                        result = platform.ReadByte((uint)(index), out NumParams); //Read Number of params
                        if (!result)
                            continue;
                            */
                        index += 2; //Skip flag


                        XFunction Function = new XFunction();
                        //Function.NumofParameters = NumParams;
                        Function.Start = (uint)(CodeStart);
                        Functions.Add(Function);

                    }

                    //Read the code section size
                    //result = platform.ReadUInt((uint)(bufferPtr + 0x2C), out CodeSectionSize);

                    //Next, iterate the bytecode of each function, collecting global and local references along the way
                    CurrentSize = 0;
                    List<XString> Globals = new List<XString>();
                    byte OP_Code;
                    byte NumVars;
                    byte[] Result;
                    for (int i = 0; i < FunctionsCount; i++)
                    {
                        //Load the bytecode into memory for faster manipulation
                        Functions[i].Locals = new List<uint>();
                        platform.ReadBytes((uint)Functions[i].Start + (uint)bufferPtr, 2 , out Result);

                        OP_Code = Result[0];
                        NumVars = Result[1];

                        if (OP_Code == OP_CreateLocalVariables)
                        {
                            uint startOff = GSXInjector.GET_ALIGNED_WORD(Functions[i].Start + 3) - Functions[i].Start;
                            for (int k = 0; k < NumVars; k++)
                            {
                                Functions[i].Locals.Add((uint)(Functions[i].Start + startOff + k * 2));
                            }
                        }
                        #region old
                        //errors.Add(ByteArrayToString(FunctionCode));
                        //Iterate the bytecode
                        /*
                        for (uint j = 0; j < FunctionSize;)
                        {
                            switch(FunctionCode[j])
                            {
                                case OP_CreateLocalVariables:
                                    //errors.Add("OP 0x" + FunctionCode[j].ToString("X") + " index " + j + " local");
                                    byte NumVars = FunctionCode[j + 1]; //Read the number of variables to create
                                    j += 2; //Move to the next position

                                    for(int k = 0; k < NumVars; k++) //Align and read locals, adding the positions of the refs into
                                    {
                                        j = GSXInjector.GET_ALIGNED_WORD(j);
                                        Functions[i].Locals.Add((uint)(Functions[i].Start + j)); //Add the local script offset
                                        //Functions[i].StrRefs.Add((uint)Functions[i].Start + j); //Add the local script offset
                                        j += sizeof(ushort);
                                    }
                                    break;
                                case OP_EvalFieldVariableRef:
                                case OP_EvalFieldVariable:
                                    //errors.Add("OP 0x" + FunctionCode[j].ToString("X") + " index " + j + " global");
                                    j++;
                                    j = GSXInjector.GET_ALIGNED_WORD(j);
                                    if (RefMap.ContainsKey(Functions[i].Start + j))
                                        if (!Globals.Contains(RefMap[(uint)(Functions[i].Start + j)])) //Add a global ref if it doesnt already exist
                                            Globals.Add(RefMap[(uint)(Functions[i].Start + j)]);
                                       // else
                                        //    errors.Add("Found a global that does not have a ref replacement key... ");
                                    j += sizeof(ushort);
                                    break;
                                default:

                                    int amount = gsclde(FunctionCode[j], (int)j, FunctionCode, platform.IsPC);
                                    //errors.Add("OP 0x" + FunctionCode[j].ToString("X") + " index " + j + " gsclde " + amount);
                                    if (amount == -1)
                                        goto EndOfFunction;
                                    j += (uint)amount;
                                    break;
                            }
                           
                        }
                        */
                        #endregion
                    }
                    foreach(var str in XStrings)
                    {
                        if (str.StringType == 1) //Cannonical
                            Globals.Add(str);
                    }
                    byte FunctionLocalsCount = 0;
                    byte MaxFunctionLocalsCount = 0;
                    foreach(var function in Functions)
                    {
                        FunctionLocalsCount = 0;
                        foreach (var local in function.Locals)
                        {
                            FunctionLocalsCount++;
                            if (!RefMap.ContainsKey(local))
                                continue;
                            Globals.Remove(RefMap[local]); //Its a local so it cant be a global
                        }
                        if (FunctionLocalsCount > MaxFunctionLocalsCount)
                            MaxFunctionLocalsCount = FunctionLocalsCount;
                    }
                    if(Globals.Count < MaxFunctionLocalsCount)
                    {
                        //TODO
                        //byte breakpoint = 1;
                        goto skipfile;
                    }
                    else
                    {
                        foreach (var function in Functions)
                        {
                            Dictionary<XString, XString> replacers = new Dictionary<XString, XString>();
                            int LocalCount = 0;


                            for (int i = 0; i < function.Locals.Count; i++)
                            {
                                uint value = function.Locals[i];
                                if (!RefMap.ContainsKey(value))
                                    continue;
                                XString key = RefMap[value];//Potential exception??
                                if (!replacers.ContainsKey(key))
                                {
                                    if (LocalCount >= Globals.Count)
                                        continue;
                                    replacers[key] = Globals[LocalCount++];
                                }
                                if (key.References.Contains(value))
                                {
                                    key.References.Remove(value);
                                    replacers[key].References.Add(value);
                                }
                            }
                        }
                    }
                    

                    //Finally, assemble the refstring data to write back to memory
                    List<byte> FinalData = new List<byte>();
                    int OriginalRefStrings = NumRefStrings;
                    NumRefStrings = 0;
                    foreach(XString x in XStrings)
                    {
                        if (x.References.Count < 1)//Irrelevant xstring. Can be excluded because, well, it has no references!
                            continue;
                        int numrefsleft = x.References.Count;
                        int n_index = 0;
                        while(numrefsleft > 0)
                        {
                            FinalData.AddRange(platform.IsPC ? BitConverter.GetBytes(x.NamePtr) : BitConverter.GetBytes(x.NamePtr).Reverse<byte>());
                            byte numToRecord = numrefsleft > 0xFF ? (byte)0xFF : (byte)numrefsleft;
                            numrefsleft -= numToRecord;
                            FinalData.Add(numToRecord);
                            FinalData.Add(x.StringType);
                            for(int i = 0; i < numToRecord; i++)
                            {
                                FinalData.AddRange(platform.IsPC ? BitConverter.GetBytes(x.References[n_index]) : BitConverter.GetBytes(x.References[n_index]).Reverse<byte>());
                                n_index++;
                            }
                        }
                        NumRefStrings++;
                    }

                    if (OriginalRefStrings >= NumRefStrings && FinalData.Count <= RefDataSize)
                    {
                        platform.WriteBytes((uint)bufferPtr + RefStringsPtr, FinalData.ToArray());
                        platform.WriteBytes((uint)NumRefStringsPtr, platform.IsPC ? BitConverter.GetBytes((ushort)NumRefStrings) : BitConverter.GetBytes((ushort)NumRefStrings).Reverse<byte>().ToArray<byte>());
                        NumStringsSaved += OriginalRefStrings - NumRefStrings;
                    }
                    else
                    {
                        errors.Add("SE String Reduction failed due to a string reduction inflating the string table (WE-383)");
                    }
                }
                catch(Exception x)
                {
                    errors.Add("SE String Reduction failed due to an unhandled exception (EX-389): " + x.GetBaseException().ToString());
                    goto end;
                }
                skipfile:;
            }
            end:;
            //errors.Add("debug -- saved " + NumStringsSaved + " strings");
            return errors;
        }

        public static List<string> StaticRedux(XPlatform platform, GSXInjector.IGSCFile[] DontOptimize)
        {
            List<string> errors = new List<string>();
            if (platform.PlatformID == XPlatformType.PLATFORM_PC_REDACTED || platform.PlatformID == XPlatformType.PLATFORM_PC_STEAM)
                return errors;

            if (platform.HasBeenOptimized)
                return errors;
            string TargetLib = "GSXCompilerLib.";
            if (platform.PlatformID == XPlatformType.PLATFORM_XBOX360)
                TargetLib += "XB360_";
            else
                TargetLib += "PS3_";
            if (platform.IsZombies)
                TargetLib += "ZM";
            else
                TargetLib += "MP";
            TargetLib += ".db";

            platform.HasBeenOptimized = true;
            StaticReduxLibrary Lib;
            IFormatter formatter = new BinaryFormatter();
            System.Reflection.Assembly a = System.Reflection.Assembly.GetExecutingAssembly();
            using (Stream resFilestream = a.GetManifestResourceStream(TargetLib))
            {
                Lib = (StaticReduxLibrary)formatter.Deserialize(resFilestream);
            }

            List<GSCBuffer> buffers = GSXInjector.BuffersForPlatform(GSXInjector.XPlatformAsGSC(platform.PlatformID), !platform.IsZombies).ToList();

            foreach (var file in DontOptimize)
            {
                GSCBuffer buffer = GSXInjector.ResolveBuffer(GSXInjector.XPlatformAsGSC(platform.PlatformID), !platform.IsZombies, file.ScriptName);
                if (buffer == null)
                    continue;
                if (buffers.Contains(buffer))
                    buffers.Remove(buffer);
                else
                {
                    for (int i = 0; i < buffers.Count; i++)
                    {
                        if (buffers[i] == null)
                            continue;
                        if (buffers[i].PointerAddress == buffer.PointerAddress)
                        {
                            buffers.RemoveAt(i);
                            i--;
                        }
                    }
                }
            }


            foreach (var buffer in buffers)
            {
                if (!Lib.ReduxEntries.ContainsKey((uint)buffer.PointerAddress))
                    continue;
                StaticReduxEntry Entry = Lib.ReduxEntries[(uint)buffer.PointerAddress];
                uint Value = (uint)buffer.PointerAddress;
                uint BufferAddress;
                platform.ReadUInt(Value, out BufferAddress);
                platform.WriteBytes(BufferAddress + 0x32, BitConverter.GetBytes(Entry.NumberOfRefs).Reverse<byte>().ToArray<byte>());
                platform.WriteBytes(BufferAddress + Entry.LocalRefPtr, Entry.RefData);
                byte breakpoint = 0;
            }

            return errors;
        }

        public static void CreateStaticRedux(XPlatform platform, string filepath)
        {
            GSCBuffer[] buffers = GSXInjector.BuffersForPlatform(GSXInjector.XPlatformAsGSC(platform.PlatformID), !platform.IsZombies);
            Console.WriteLine("Number of buffers: " + buffers.Length);

            List<XString> XStrings = new List<XString>();
            Dictionary<uint, XString> RefMap = new Dictionary<uint, XString>();
            StaticReduxLibrary Lib = new StaticReduxLibrary();
            Lib.Platform = GSXInjector.XPlatformAsGSC(platform.PlatformID);
            uint StringsPointer;
            uint NumRefStringsPtr;
            bool result;
            ushort NumRefStrings;
            uint RefStringsPtr;
            uint index;
            ushort NamePtr;
            byte NumRefs = 0;
            byte Type = 0;
            uint ptr = 0;
            uint FunctionsStart = 0;
            ushort FunctionsCount = 0;
            uint CodeStart = 0;
            List<XFunction> Functions = new List<XFunction>();
            uint RefDataSize = 0;
            uint bufferPtr;
            ushort NumFixups;
            ushort NumFixed = 0;
            foreach (GSCBuffer buffer in buffers)
            {
                try
                {
                    //Reset variables
                    StaticReduxEntry Entry = new StaticReduxEntry();
                    XStrings.Clear();
                    Functions.Clear();
                    RefMap.Clear();
                    NamePtr = 0;
                    result = platform.ReadUInt((uint)buffer.PointerAddress, out bufferPtr);
                    if (!result || bufferPtr == 0x0)
                    {
                        //errors.Add("SE String Reduction failed due to a critical read failure (RE-105)");
                        Console.WriteLine("Failed to read buffer address.. Substituting with original buffer... ");
                        bufferPtr = (uint)buffer.BufferPtr;
                        if(bufferPtr == 0x0)
                            goto skipfile;
                    }

                    StringsPointer = (uint)bufferPtr + 0x18;
                    NumRefStringsPtr = (uint)bufferPtr + 0x32;

                    result = platform.ReadUshort((uint)NumRefStringsPtr, out NumRefStrings);
                    if (!result)
                    {
                        //errors.Add("SE String Reduction failed due to a critical read failure (RE-108)");
                        goto skipfile;
                    }
                    if (NumRefStrings < 1) //why optimize an empty script...?
                    {
                        goto skipfile;
                    }
                        

                    result = platform.ReadUInt((uint)StringsPointer, out RefStringsPtr);
                    if (!result)
                    {
                        //errors.Add("SE String Reduction failed due to a critical read failure (RE-117)");
                        //Console.WriteLine("Failed to read RefStringsPtr.. Skipping file... Press any key to continue");
                        goto skipfile;
                    }

                    Entry.LocalRefPtr = RefStringsPtr;


                    result = platform.ReadUInt((uint)(bufferPtr + 0x1C), out FunctionsStart);
                    if (!result)
                    {
                        //Console.WriteLine("Failed to read FunctionsStart.. Skipping file...");
                        goto skipfile;
                    }
                        

                    result = platform.ReadUshort((uint)(bufferPtr + 0x34), out FunctionsCount);
                    if (!result)
                    {
                        //Console.WriteLine("Failed to read FunctionsCount.. Skipping file...");
                        goto skipfile;
                    }

                    result = platform.ReadUshort((uint)(bufferPtr + 0x38), out NumFixups);
                    if (result && NumFixups > 0) //Fixups cause lots of issues. Skip these files because chances are that it will break the whole operation
                    {
                        Console.WriteLine("Fixups found.. Skipping file...");
                        goto skipfile;
                    }

                    //First, Collect the ref strings from the file and load them into memory, along with some mapping for performance reasons (specifically, o(1) vs o(n^2))
                    index = (uint)bufferPtr + RefStringsPtr;
                    byte[] RefData;
                    Console.WriteLine("Attempting to read ref strings...");
                    for (uint i = 0; i < NumRefStrings; i++)
                    {
                        result = platform.ReadBytes((uint)index, 4, out RefData); //Read name pointer for refstring
                        if (!result)
                            break;

                        /*
                        result = platform.ReadString((uint)bufferPtr + NamePtr, out Name); //Read name for refstring
                        if (!result)
                            break;
                        */

                        XString str = null;
                        index += 4;
                        byte[] targetdata = new byte[] { RefData[0], RefData[1] };
                        if (!platform.IsPC)
                            targetdata = targetdata.Reverse<byte>().ToArray<byte>();

                        NamePtr = BitConverter.ToUInt16(targetdata, 0);
                        NumRefs = RefData[2];
                        Type = RefData[3];


                        if (Type > 1)
                        {
                            // errors.Add("SE String Reduction failed due to an unexpected string type in the string table... (RE-154)");
                            Console.WriteLine("Unexpected stringtype in string table, skipping file!");
                            goto skipfile;
                        }
                        //Find the string associated with this ref. If not found, create one to match it.
                        foreach (XString xstr in XStrings.Where(xstr => xstr.NamePtr == NamePtr && xstr.StringType == Type))
                        {
                            str = xstr;
                            goto Found;
                        }
                        str = new XString();
                        //str.Name = Name;
                        str.StringType = Type;
                        str.NamePtr = NamePtr;
                        XStrings.Add(str);


                        Found:
                        byte[] data;
                        platform.ReadBytes(index, (uint)NumRefs * 4, out data);
                        index += (uint)data.Length;
                        byte[] Temp;

                        for (byte j = 0; j < NumRefs; j++)
                        {
                            //index = GSXInjector.GET_ALIGNED_DWORD(index);
                            Temp = new byte[] { data[j * 4], data[j * 4 + 1], data[j * 4 + 2], data[j * 4 + 3] };
                            if (!platform.IsPC)
                                Temp = Temp.Reverse<byte>().ToArray<byte>();
                            ptr = BitConverter.ToUInt32(Temp, 0);
                            str.References.Add(ptr);
                            RefMap[ptr] = str;
                            //index += sizeof(uint);
                        }

                        RefDataSize += 4 + (uint)(NumRefs * 4);
                    }


                    //Then, iterate the function headers and parse them into memory as well
                    index = (uint)bufferPtr + FunctionsStart;
                    Console.WriteLine("Trying to read function headers");
                    for (uint i = 0; i < FunctionsCount; i++)
                    {
                        index += sizeof(uint); //Skip crc32
                        result = platform.ReadUInt((uint)(index), out CodeStart); //Read bytecode ref start
                        if (!result)
                            continue;

                        index += sizeof(uint) + sizeof(ushort); //Skip name
                        /*
                        result = platform.ReadByte((uint)(index), out NumParams); //Read Number of params
                        if (!result)
                            continue;
                            */
                        index += 2; //Skip flag


                        XFunction Function = new XFunction();
                        //Function.NumofParameters = NumParams;
                        Function.Start = (uint)(CodeStart);
                        Functions.Add(Function);

                    }

                    //Read the code section size
                    //result = platform.ReadUInt((uint)(bufferPtr + 0x2C), out CodeSectionSize);

                    //Next, iterate the bytecode of each function, collecting global and local references along the way
                    List<XString> Globals = new List<XString>();
                    byte OP_Code;
                    byte NumVars;
                    byte[] Result;
                    Console.WriteLine("Trying to read op codes...");
                    for (uint i = 0; i < FunctionsCount; i++)
                    {
                        //Load the bytecode into memory for faster manipulation
                        Functions[(int)i].Locals = new List<uint>();
                        platform.ReadBytes((uint)Functions[(int)i].Start + (uint)bufferPtr, 2, out Result);

                        OP_Code = Result[0];
                        NumVars = Result[1];

                        if (OP_Code == OP_CreateLocalVariables)
                        {
                            uint startOff = GSXInjector.GET_ALIGNED_WORD(Functions[(int)i].Start + 3) - Functions[(int)i].Start;
                            for (uint k = 0; k < NumVars; k++)
                            {
                                Functions[(int)i].Locals.Add((uint)(Functions[(int)i].Start + startOff + k * 2));
                            }
                        }
                        #region old
                        //errors.Add(ByteArrayToString(FunctionCode));
                        //Iterate the bytecode
                        /*
                        for (uint j = 0; j < FunctionSize;)
                        {
                            switch(FunctionCode[j])
                            {
                                case OP_CreateLocalVariables:
                                    //errors.Add("OP 0x" + FunctionCode[j].ToString("X") + " index " + j + " local");
                                    byte NumVars = FunctionCode[j + 1]; //Read the number of variables to create
                                    j += 2; //Move to the next position

                                    for(uint k = 0; k < NumVars; k++) //Align and read locals, adding the positions of the refs into
                                    {
                                        j = GSXInjector.GET_ALIGNED_WORD(j);
                                        Functions[i].Locals.Add((uint)(Functions[i].Start + j)); //Add the local script offset
                                        //Functions[i].StrRefs.Add((uint)Functions[i].Start + j); //Add the local script offset
                                        j += sizeof(ushort);
                                    }
                                    break;
                                case OP_EvalFieldVariableRef:
                                case OP_EvalFieldVariable:
                                    //errors.Add("OP 0x" + FunctionCode[j].ToString("X") + " index " + j + " global");
                                    j++;
                                    j = GSXInjector.GET_ALIGNED_WORD(j);
                                    if (RefMap.ContainsKey(Functions[i].Start + j))
                                        if (!Globals.Contains(RefMap[(uint)(Functions[i].Start + j)])) //Add a global ref if it doesnt already exist
                                            Globals.Add(RefMap[(uint)(Functions[i].Start + j)]);
                                       // else
                                        //    errors.Add("Found a global that does not have a ref replacement key... ");
                                    j += sizeof(ushort);
                                    break;
                                default:

                                    uint amount = gsclde(FunctionCode[j], (uint)j, FunctionCode, platform.IsPC);
                                    //errors.Add("OP 0x" + FunctionCode[j].ToString("X") + " index " + j + " gsclde " + amount);
                                    if (amount == -1)
                                        goto EndOfFunction;
                                    j += (uint)amount;
                                    break;
                            }
                           
                        }
                        */
                        #endregion
                    }
                    foreach (var str in XStrings)
                    {
                        if (str.StringType == 1) //Cannonical
                            Globals.Add(str);
                    }
                    byte FunctionLocalsCount = 0;
                    byte MaxFunctionLocalsCount = 0;
                    foreach (var function in Functions)
                    {
                        FunctionLocalsCount = 0;
                        foreach (var local in function.Locals)
                        {
                            FunctionLocalsCount++;
                            if (!RefMap.ContainsKey(local))
                                continue;
                            Globals.Remove(RefMap[local]); //Its a local so it cant be a global
                        }
                        if (FunctionLocalsCount > MaxFunctionLocalsCount)
                            MaxFunctionLocalsCount = FunctionLocalsCount;
                    }
                    if (Globals.Count < MaxFunctionLocalsCount)
                    {
                        //TODO
                        //byte breakpoint = 1;
                        Console.WriteLine("Not enough globals!");
                        goto skipfile;
                    }
                    else
                    {
                        foreach (var function in Functions)
                        {
                            Dictionary<XString, XString> replacers = new Dictionary<XString, XString>();
                            uint LocalCount = 0;


                            for (uint i = 0; i < function.Locals.Count; i++)
                            {
                                uint value = function.Locals[(int)i];
                                if (!RefMap.ContainsKey(value))
                                    continue;
                                XString key = RefMap[value];//Potential exception??
                                if (!replacers.ContainsKey(key))
                                {
                                    if (LocalCount >= Globals.Count)
                                        continue;
                                    replacers[key] = Globals[(int)LocalCount++];
                                }
                                if (key.References.Contains(value))
                                {
                                    key.References.Remove(value);
                                    replacers[key].References.Add(value);
                                }
                            }
                        }
                    }


                    //Finally, assemble the refstring data to write back to memory
                    List<byte> FinalData = new List<byte>();
                    uint OriginalRefStrings = NumRefStrings;
                    NumRefStrings = 0;
                    foreach (XString x in XStrings)
                    {
                        if (x.References.Count < 1)//Irrelevant xstring. Can be excluded because, well, it has no references!
                            continue;
                        uint numrefsleft = (uint)x.References.Count;
                        uint n_index = 0;
                        while (numrefsleft > 0)
                        {
                            FinalData.AddRange(platform.IsPC ? BitConverter.GetBytes(x.NamePtr) : BitConverter.GetBytes(x.NamePtr).Reverse<byte>());
                            byte numToRecord = numrefsleft > 0xFF ? (byte)0xFF : (byte)numrefsleft;
                            numrefsleft -= numToRecord;
                            FinalData.Add(numToRecord);
                            FinalData.Add(x.StringType);
                            for (uint i = 0; i < numToRecord; i++)
                            {
                                FinalData.AddRange(platform.IsPC ? BitConverter.GetBytes(x.References[(int)n_index]) : BitConverter.GetBytes(x.References[(int)n_index]).Reverse<byte>());
                                n_index++;
                            }
                        }
                        NumRefStrings++;
                    }

                    if (OriginalRefStrings >= NumRefStrings && FinalData.Count <= RefDataSize)
                    {
                        Entry.NumberOfRefs = NumRefStrings;
                        Entry.RefData = FinalData.ToArray();
                        Lib.ReduxEntries[(uint)buffer.PointerAddress] = Entry;
                    }
                    else
                    {
                        Console.WriteLine("Buffer inflated...");
                        //errors.Add("SE String Reduction failed due to a string reduction inflating the string table (WE-383)");
                    }
                }
                catch (Exception x)
                {
                    Console.WriteLine(x.GetBaseException().ToString());
                    //errors.Add("SE String Reduction failed due to an unhandled exception (EX-389): " + x.GetBaseException().ToString());
                }
                NumFixed++;
                skipfile:;
            }
            Console.WriteLine("Total scripts collected: " + NumFixed);
            IFormatter formatter = new BinaryFormatter();
            using (MemoryStream stream = new MemoryStream())
            {
                formatter.Serialize(stream, Lib);
                byte[] contents = stream.ToArray();
                File.WriteAllBytes(filepath, contents);
            }
        }


        private static string ByteArrayToString(byte[] bytes)
        {
            var sb = new StringBuilder("");
            int count = 0;
            foreach (var b in bytes)
            {
                sb.Append(count.ToString() + " :: 0x" + b.ToString("X") + ", ");
                count++;
            }
            //sb.Append("}");
            return sb.ToString();
        }

        private static int gsclde(byte Code, int StartPos, byte[] data, bool ispc)
        {
            // variables used inside the switch
            int caseCount = 0;
            int currentPos = StartPos;
            currentPos++; //Skip OPCode
            switch (Code)
            {
                case OP_End:
                case OP_Return:
                case OP_GetUndefined:
                case OP_GetZero:
                case OP_GetLevelObject:
                case OP_GetAnimObject:
                case OP_GetSelf:
                case OP_GetLevel:
                case OP_GetGame:
                case OP_GetAnim:
                case OP_GetGameRef: // ADD DECOMPILATION SUPPORT FOR THIS (WTFFFF)
                case 24: // ADD SUPPORT FOR THIS TOO
                case OP_EvalArray:
                case OP_EvalArrayRef:
                case OP_ClearArray:
                case OP_EmptyArray:
                case OP_GetSelfObject:
                case OP_clearparams: // ADD SUPPORT FOR THIS TOO
                case OP_checkclearparams:
                case OP_SetVariableField:
                case OP_wait:
                case OP_RealWait:
                case OP_waittillFrameEnd:
                case OP_PreScriptCall:
                case OP_DecTop:
                case OP_CastFieldObject:
                case OP_CastBool: // ADD SUPPORT FOR THIS TOO? hmm...
                case OP_BoolNot:
                case OP_BoolComplement: // ADD SUPPORT FOR THIS TOO
                case OP_inc:
                case OP_dec:
                case OP_bit_or:
                case OP_bit_ex_or:
                case OP_bit_and:
                case OP_equality:
                case OP_inequality:
                case OP_less:
                case OP_greater:
                case OP_less_equal:
                case OP_greater_equal:
                case OP_shift_left:
                case OP_shift_right:
                case OP_plus:
                case OP_minus:
                case OP_multiply:
                case OP_divide:
                case OP_mod:
                case OP_size:
                case OP_waittillmatch:
                case OP_waittill:
                case OP_notify:
                case OP_endon:
                case OP_voidCodepos:
                case OP_vector:
                case OP_isdefined:
                case OP_vectorscale:
                case OP_anglestoup:
                case OP_anglestoright:
                case OP_anglestoforward:
                case OP_angleclamp180:
                case OP_vectortoangles:
                case OP_abs:
                case OP_gettime:
                case OP_getdvar:
                case OP_getdvarint:
                case OP_getdvarfloat:
                case OP_Breakpoint:
                case OP_DevblockEnd:
                case 107:
                case 108:
                case 109:
                case 110:
                case 111:
                case OP_GetFirstArrayKey:
                case OP_GetNextArrayKey:
                case OP_GetUndefined2:
                case 116: // ADD SUPPORT FOR THIS TOO
                case 117: // ADD SUPPORT FOR THIS TOO (LOL)
                case 118: // ADD SUPPORT FOR THIS TOO (in cod4, this decreases g_script_error_level, and seems to do the same in bo2)
                    return 1;
                case OP_GetByte:
                case OP_GetNegByte:
                case 27: // ADD SUPPORT FOR THIS TOO
                case 35: // ADD SUPPORT FOR THIS TOO
                case OP_SafeSetWaittillVariableFieldCached:
                case OP_EvalLocalVariableRefCached:
                case OP_ScriptFunctionCallPointer:
                case OP_ScriptMethodCallPointer:
                case OP_ScriptThreadCallPointer:
                case OP_ScriptMethodThreadCallPointer:
                case OP_GetSimpleVector:
                    return 2;
                case OP_EvalLocalVariableCached:
                    return 2;
                case OP_GetUnsignedShort:
                case OP_GetNegUnsignedShort:
                case OP_GetString:
                case OP_GetIString:
                case OP_EvalFieldVariable:
                case OP_EvalFieldVariableRef:
                case OP_ClearFieldVariable:
                case OP_JumpOnFalse:
                case OP_JumpOnTrue:
                case OP_JumpOnFalseExpr:
                case OP_JumpOnTrueExpr:
                case OP_JumpBack:
                case OP_jump:
                case 120: // ADD SUPPORT FOR THIS TOO (pushes a type_object var to the stack like OP_object, but differently)
                case 121: // ADD SUPPORT FOR THIS TOO
                case 122: // ADD SUPPORT FOR THIS TOO
                case OP_skipdev: // ADD SUPPORT FOR THIS TOO
                    currentPos = (int)GSXInjector.GET_ALIGNED_WORD((uint)currentPos) + 2;
                    return currentPos - StartPos;
                case OP_GetInteger:
                case OP_GetFloat:
                case OP_GetAnimation:
                case OP_GetFunction:
                case OP_switch: // we don't skip the cases' code here
                case OP_GetHash:
                case 114: // ADD SUPPORT FOR THIS ONE TOO (what it does is the same as OP_GetUndefined, but changes currentPos too)
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD((uint)currentPos) + 4;
                    return currentPos - StartPos;
                case OP_GetVector:
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD((uint)currentPos) + 12;
                    return currentPos - StartPos;
                    /*
                case OP_CreateLocalVariables:
                    currentPos++;
                    numOfVariables = data[currentPos];
                    currentPos += 1;
                    for (int i = 0; i < numOfVariables; i++)
                        currentPos = (int)GSXInjector.GET_ALIGNED_WORD((uint)currentPos) + 2;
                    return currentPos - StartPos;
                    */
                case OP_ScriptFunctionCall:
                case OP_ScriptMethodCall:
                case OP_ScriptThreadCall:
                case OP_ScriptMethodThreadCall:
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD((uint)currentPos + 1) + 4;
                    return currentPos - StartPos;
                case OP_CallBuiltin:
                case OP_CallBuiltinMethod:
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD((uint)currentPos) + 4;
                    return currentPos - StartPos;
                case OP_endswitch:
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD((uint)currentPos);
                    byte[] sizebytes = null;
                    if (currentPos + sizeof(int) <= data.Length)
                    {
                        sizebytes = data.ToList().GetRange(currentPos, sizeof(int)).ToArray();
                        if (!ispc)
                            sizebytes = sizebytes.Reverse<byte>().ToArray<byte>();
                    } 
                    else
                        return -1;
                    caseCount = BitConverter.ToInt32(sizebytes, 0);
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD(GSXInjector.GET_ALIGNED_DWORD((uint)currentPos) + 4) + 8 * caseCount;
                    return currentPos - StartPos;
                case 119: // ADD SUPPORT FOR THIS TOO (what i know is that it pushes a type_object var to the stack)
                    currentPos = (int)GSXInjector.GET_ALIGNED_DWORD(GSXInjector.GET_ALIGNED_DWORD((uint)currentPos) + 4) + 4;
                    return currentPos - StartPos;
            }
            return -1;
        }

        [Serializable]
        internal sealed class StaticReduxLibrary
        {
            internal GSCPlatformType Platform;
            //PointerAddress -> Entry
            internal Dictionary<uint, StaticReduxEntry> ReduxEntries = new Dictionary<uint, StaticReduxEntry>();
        }

        [Serializable]
        internal struct StaticReduxEntry
        {
            internal ushort NumberOfRefs;
            internal uint LocalRefPtr;
            internal byte[] RefData;
        }
    }
}
