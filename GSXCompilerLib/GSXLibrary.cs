using Irony.Parsing;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace GSXCompilerLib
{
    /// <summary>
    /// Library for GSX Library creation and usage in the compiler
    /// </summary>
    public static class GSXLibraries
    {
        internal static Dictionary<string, GSXLibrary> LoadedLibraries = new Dictionary<string, GSXLibrary>();

        

        /// <summary>
        /// Resolve a library reference from loaded libraries. Will write the source text if successful, otherwise, the error text
        /// </summary>
        /// <param name="librefnode"></param>
        /// <param name="SourceText"></param>
        /// <param name="ErrorMessage"></param>
        /// <returns></returns>
        internal static bool ResolveLibReference(ParseTreeNode librefnode, GSC.GSCOptimizer optimizer, out GSXLibReference Ref, out string ErrorMessage)
        {
            Ref = new GSXLibReference();
            ErrorMessage = "";
            try
            {
                string libname = librefnode.ChildNodes[1].FindTokenAndGetText().ToLower();
                ParseTreeNode Libuse = librefnode.ChildNodes[2];
                if(Libuse.ChildNodes.Count == 2)
                {
                    Ref.Type = RefType.Function;
                    Ref.LibName = libname;
                    Ref.RefName = Libuse.ChildNodes[0].FindTokenAndGetText().ToLower();
                    Ref.RefParams = optimizer.HandleNode(Libuse.ChildNodes[1]);
                    Ref.NumParams = GSC.GSCOptimizer.CountParams(Libuse.ChildNodes[1]);
                }
                else
                {
                    Ref.Type = RefType.Variable;
                    Ref.LibName = libname;
                    Ref.RefName = Libuse.ChildNodes[0].FindTokenAndGetText().ToLower();
                }

                if(LoadedLibraries.ContainsKey(Ref.LibName))
                {
                    if(Ref.Type == RefType.Function)
                    {
                        bool FoundName = true;
                        foreach(var function in LoadedLibraries[Ref.LibName].GSXFunctions)
                        {
                            if (function.Name.ToLower() == Ref.RefName)
                            {
                                FoundName = true;
                                if (function.NumParams >= Ref.NumParams)
                                {
                                    Ref.LibItem = function;
                                    return true;
                                }
                                    
                            }
                        }
                        if(FoundName)
                        {
                            ErrorMessage = "Failed to resolve library function '" + Ref.RefName + "' with '" + Ref.NumParams + "' in library '" + Ref.LibName + "', but found a function with the same name and less parameters. Please use the correct number of parameters.";
                            return false;
                        }
                        ErrorMessage = "Failed to resolve library function '" + Ref.RefName + "' in library '" + Ref.LibName + "'";
                        return false;
                    }
                    else
                    {
                        foreach (var variable in LoadedLibraries[Ref.LibName].GSXVars)
                        {
                            if(variable.Name.ToLower() == Ref.RefName)
                            {
                                Ref.LibItem = variable;
                                return true;
                            }
                        }
                        ErrorMessage = "Failed to resolve library variable '" + Ref.RefName + "' in library '" + Ref.LibName + "'";
                        return false;
                    }
                }
                else
                {
                    ErrorMessage = "Failed to resolve library '" + Ref.LibName + "'. Please install the library and restart the tool.";
                    return false;
                }
            }
            catch
            {

            }
            return false;
            //return "libraries/" + libname + "/" + functionname;
        }

        /// <summary>
        /// Get the source text for a reference
        /// </summary>
        /// <param name="LibReference"></param>
        /// <returns></returns>
        internal static string GetRefText(GSXLibReference LibReference)
        {
            if (LibReference.Type == RefType.Function)
                return "libraries/" + LibReference.LibName + "/" + LibReference.RefName + LibReference.RefParams;
            return "level." + LibReference.LibName + "." + LibReference.RefName;
        }

        /// <summary>
        /// Load the libraries from the specified directory into memory for compilation use
        /// </summary>
        /// <param name="LibrariesDirectory"></param>
        /// <returns></returns>
        public static bool LoadLibraries(string LibrariesDirectory)
        {
            bool FinalResult = true;
            try
            {
                DirectoryInfo di = new DirectoryInfo(LibrariesDirectory);
                foreach(var file in di.GetFiles("*.gsxlib", SearchOption.AllDirectories))
                {
                    GSXLibrary lib;
                    bool result = LoadLibrary(file.FullName, out lib);
                    if(!result)
                    {
                        FinalResult = false;
                        continue;
                    }
                    LoadedLibraries[lib.LibraryInfo.LibName] = lib;
                }
            }
            catch
            {
                return false;
            }

            return FinalResult;
        }

        /// <summary>
        /// Clears all loaded libraries
        /// </summary>
        public static void ClearLibraries()
        {
            LoadedLibraries.Clear();
        }


        /// <summary>
        /// Save a library
        /// </summary>
        /// <param name="outpath"></param>
        /// <returns></returns>
        public static bool SaveLibrary(string outpath, GSXLibrary lib, string password = "")
        {
            lib.PasswordHash = GSXLibrary.CalculateMD5Hash(password);
            lib.Header.Replace(0, lib.Magic.ToList());
            lib.Header[0x7] = (byte)lib.LibType;
            lib.DataBlock.Clear();
            lib.LibInfoPtr = lib.DataBlock.Count;
            lib.DataBlock.AddRange(Encoding.ASCII.GetBytes(lib.LibraryInfo.LibTitle));
            lib.DataBlock.Add(0);
            lib.DataBlock.AddRange(Encoding.ASCII.GetBytes(lib.LibraryInfo.LibName));
            lib.DataBlock.Add(0);
            lib.DataBlock.AddRange(Encoding.ASCII.GetBytes(lib.LibraryInfo.LibCreator));
            lib.DataBlock.Add(0);
            lib.DataBlock.AddRange(Encoding.ASCII.GetBytes(lib.LibraryInfo.LibDescription));
            lib.DataBlock.Add(0);
            lib.NumIncludes = lib.Includes.Count;
            lib.IncludesPtr = lib.DataBlock.Count;
            foreach (string s in lib.Includes)
            {
                lib.DataBlock.AddRange(Encoding.ASCII.GetBytes(s));
                lib.DataBlock.Add(0);
            }




            lib.Encrypted = true;
            lib.DataBlockSize = lib.DataBlock.Count;
            IFormatter formatter = new BinaryFormatter();
            using (MemoryStream stream = new MemoryStream())
            {
                formatter.Serialize(stream, lib);
                byte[] contents = stream.ToArray();
                File.WriteAllBytes(outpath, contents);
            }

            return true;
        }


        /// <summary>
        /// Load a library
        /// </summary>
        /// <param name="inpath"></param>
        /// <returns></returns>
        public static bool LoadLibrary(string inpath, out GSXLibrary lib, string password = "")
        {
            lib = new GSXLibrary();
            lib.PasswordHash = GSXLibrary.CalculateMD5Hash(password);



            return false;
        }







        /// <summary>
        /// Library that contains a GSX for use by external scripts
        /// </summary>
        [Serializable]
        public sealed class GSXLibrary
        {
            internal byte[] Magic = new byte[] { (byte)'G', (byte)'S', (byte)'X', (byte)'L', (byte)'I', (byte)'B', (byte)0x0 };
            internal GSXLibraryType LibType;

            internal int LibInfoPtr
            {
                set
                {
                    Header.Replace(0x8, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x8);
                }
            }

            internal int VariablesPtr
            {
                set
                {
                    Header.Replace(0xC, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0xC);
                }
            }

            internal int FunctionsPtr
            {
                set
                {
                    Header.Replace(0x10, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x10);
                }
            }
            internal int IncludesPtr
            {
                set
                {
                    Header.Replace(0x14, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x14);
                }
            }
            internal int LibIncludesPtr
            {
                set
                {
                    Header.Replace(0x18, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x18);
                }
            }

            internal int NumVariables
            {
                set
                {
                    Header.Replace(0x1C, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x1C);
                }
            }

            internal int NumFunctions
            {
                set
                {
                    Header.Replace(0x20, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x20);
                }
            }

            internal int NumIncludes
            {
                set
                {
                    Header.Replace(0x24, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x24);
                }
            }

            internal int NumLibIncludes
            {
                set
                {
                    Header.Replace(0x28, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x28);
                }
            }

            internal int DataBlockSize
            {
                set
                {
                    Header.Replace(0x2C, BitConverter.GetBytes(value).ToList());
                }
                get
                {
                    return BitConverter.ToInt32(Header.ToArray(), 0x2C);
                }
            }


            private bool isEncrypted;
            internal bool Encrypted
            {
                get
                {
                    return isEncrypted;
                }

                set
                {
                    isEncrypted = Encrypt(value);
                }
            }


            [NonSerialized]
            internal LibInfo LibraryInfo;
            [NonSerialized]
            internal List<GSXVariable> GSXVars = new List<GSXVariable>();
            [NonSerialized]
            internal List<GSXFunction> GSXFunctions = new List<GSXFunction>();

            [NonSerialized]
            internal List<string> Includes = new List<string>();

            internal struct LibInfo
            {
                internal string LibTitle;
                internal string LibName;
                internal string LibCreator;
                internal string LibDescription;
            }

            internal static byte[] CalculateMD5Hash(string input)
            {

                MD5 md5 = System.Security.Cryptography.MD5.Create();

                byte[] inputBytes = System.Text.Encoding.ASCII.GetBytes(input);

                byte[] hash = md5.ComputeHash(inputBytes);

                return hash;

            }


            /// <summary>
            /// Adds a function to the library, including all required functions by the library, except other library refs
            /// </summary>
            /// <param name="node"></param>
            /// <param name="IsPublic"></param>
            /// <returns></returns>
            internal bool AddFunction(ParseTreeNode node, bool IsPublic)
            {
                GSXFunction[] Functions = ResolveFunctions(node, IsPublic);

                foreach(var func in Functions)
                {
                    if (GSXFunctions.Contains(func))
                        continue;
                    GSXFunctions.Add(func);
                }

                return true;
            }

            internal GSXFunction[] ResolveFunctions(ParseTreeNode node, bool ispublic)
            {
                List<GSXFunction> Functions = new List<GSXFunction>();
                //TODO


                return Functions.ToArray();
            }

            /// <summary>
            /// Add a variable to the library
            /// </summary>
            /// <param name="name"></param>
            /// <param name="value"></param>
            /// <param name="parent"></param>
            /// <returns></returns>
            internal bool AddVariable(string name, string value = "", string parent = "lib")
            {
                

                return false;
            }


            [NonSerialized]
            private byte[] IV; //16 bytes

            [NonSerialized]
            internal byte[] PasswordHash; //16 bytes

            [NonSerialized]
            Random r = new Random();

            /// <summary>
            /// Returns the encryption state post operation
            /// </summary>
            /// <param name="target"></param>
            /// <returns></returns>
            internal bool Encrypt(bool target)
            {
                bool start = Encrypted;
                if (start == target)
                    return target;
                byte[] key = null;
                if(LibType ==  GSXLibraryType.Private)
                {
                    key = PasswordHash;
                }
                else
                {
                    key = new byte[] { 0xf8, 0x88, 0x10, 0x76, 0x43, 0x9d, 0x97, 0x7a, 0x5c, 0xa8, 0x1a, 0x24, 0xb1, 0x7f, 0xbb, 0x32 };
                }

                byte[] IV = new byte[16];
                if(target)
                {
                    r.NextBytes(IV);
                }
                else
                {
                    if(DataBlock.Count >= 16)
                    {
                        for (int i = 0; i < 16; i++)
                            IV[i] = DataBlock[i];
                    }
                    else
                    {
                        return start; //Failed to decrypt because the IV was not found
                    }
                }

                if(target)
                {
                    try
                    {
                        DataBlock = encryptStream(DataBlock.ToArray(), key, IV).ToList();
                        DataBlock.InsertRange(0, IV);
                    }
                    catch
                    {
                        return start;
                    }
                }
                else
                {
                    try
                    {
                        DataBlock.RemoveRange(0, 16);
                        DataBlock = decryptStream(DataBlock.ToArray(), key, IV).ToList();
                    }
                    catch
                    {
                        DataBlock.InsertRange(0, IV);
                        return start;
                    }
                }
                return target;
            }

            private static byte[] encryptStream(byte[] plain, byte[] Key, byte[] IV)
            {
                byte[] encrypted; ;
                using (MemoryStream mstream = new MemoryStream())
                {
                    using (AesCryptoServiceProvider aesProvider = new AesCryptoServiceProvider())
                    {
                        using (CryptoStream cryptoStream = new CryptoStream(mstream,
                            aesProvider.CreateEncryptor(Key, IV), CryptoStreamMode.Write))
                        {
                            cryptoStream.Write(plain, 0, plain.Length);
                        }
                        encrypted = mstream.ToArray();
                    }
                }
                return encrypted;
            }

            private static byte[] decryptStream(byte[] encrypted, byte[] Key, byte[] IV)
            {
                byte[] plain;
                using (MemoryStream mStream = new MemoryStream(encrypted)) //add encrypted
                {
                    using (AesCryptoServiceProvider aesProvider = new AesCryptoServiceProvider())
                    {
                        using (CryptoStream cryptoStream = new CryptoStream(mStream,
                            aesProvider.CreateDecryptor(Key, IV), CryptoStreamMode.Read))
                        {
                            //cryptoStream.Read(encrypted, 0, encrypted.Length);
                            using (StreamReader stream = new StreamReader(cryptoStream))
                            {
                                string sf = stream.ReadToEnd();
                                plain = System.Text.Encoding.Default.GetBytes(sf);
                            }
                        }
                    }
                }
                return plain;
            }

            internal List<byte> Header = new List<byte>(0x30);
            internal List<byte> DataBlock = new List<byte>();
        }

        /// <summary>
        /// Config for a gsx library
        /// </summary>
        public sealed class GSXLibraryConfig
        {
            public string LibTitle;
            public string LibCodeName;
            public string LibCreator;
            public GSXLibraryType LibType;
            public GSXLibrary Library;
        }

        public enum GSXLibraryType
        {
            Public,
            Private
        }

        internal sealed class GSXFunction
        {
            /// <summary>
            /// Can the function be called outside of the library
            /// </summary>
            internal bool IsPublic;
            /// <summary>
            /// The name of the function. The function will be named _LIBNAME_NAME in script, all lowercase
            /// </summary>
            internal string Name;

            /// <summary>
            /// Documentation of GSX
            /// </summary>
            internal string Documentation;

            /// <summary>
            /// Number of parameters
            /// </summary>
            internal byte NumParams
            {
                get
                {
                    return (byte)Parameters.Count;
                }
            }

            /// <summary>
            /// List of parameter names
            /// </summary>
            internal List<string> Parameters;

            /// <summary>
            /// Function parsetree
            /// </summary>
            internal ParseTreeNode Function;


            /// <summary>
            /// All referenced libraries to resolve
            /// </summary>
            internal List<GSXLibReference> References = new List<GSXLibReference>();
            
            
        }

        internal sealed class GSXVariable
        {
            /// <summary>
            /// If not set, the variable is assumed to be a child of the package (level.packagename)
            /// </summary>
            internal string Parent;
            /// <summary>
            /// If not set, the variable is assumed to be undefined
            /// </summary>
            internal string Value;
            /// <summary>
            /// Name of the variable
            /// </summary>
            internal string Name;
        }


        internal enum RefType
        {
            Function,
            Variable
        }

        internal struct GSXLibReference
        {
            internal string LibName;
            internal string RefName;
            internal string RefParams;
            internal byte NumParams;
            internal object LibItem;
            internal RefType Type;

            public bool Equals(GSXLibReference obj)
            {
                return Type == obj.Type &&
                    LibName == obj.LibName &&
                    RefName == obj.RefName &&
                    NumParams == obj.NumParams;
            }
        }
    }
}
