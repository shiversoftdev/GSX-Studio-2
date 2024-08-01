using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

namespace GSXCompilerLib
{
    internal sealed class ByteCodeCompiler
    {
        #region Properties 
        private byte[] Magic
        {
            set
            {
                WriteRange(0, value);
            }
        }

        private int IncludesPtr
        {
            set
            {
                if(Package.Target == PlatformTarget.Console)
                    WriteRange(0xC, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0xC, BitConverter.GetBytes(value));
            }
        }

        private int UsingAnimTreesPtr
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x10, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x10, BitConverter.GetBytes(value));
            }
        }

        private int CodeSectionPtr
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x14, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x14, BitConverter.GetBytes(value));
            }
        }

        private int StringRefsPtr
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x18, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x18, BitConverter.GetBytes(value));
            }
        }

        private int ExportsPtr
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x1C, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x1C, BitConverter.GetBytes(value));
            }
        }

        private int ImportsPtr
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x20, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x20, BitConverter.GetBytes(value));
            }
        }

        private int CodePatchesPtr
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x24, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x24, BitConverter.GetBytes(value));
            }
        }

        private int Size
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x28, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x28, BitConverter.GetBytes(value));
            }
        }

        private ushort Watermark
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x30, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x30, BitConverter.GetBytes(value));
            }
        }

        private ushort StringRefsCount
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x32, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x32, BitConverter.GetBytes(value));
            }
        }

        private ushort ExportsCount
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x34, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x34, BitConverter.GetBytes(value));
            }
        }

        private ushort ImportsCount
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x36, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x36, BitConverter.GetBytes(value));
            }
        }

        private ushort CodePatchesCount
        {
            set
            {
                if (Package.Target == PlatformTarget.Console)
                    WriteRange(0x38, BitConverter.GetBytes(value).Reverse<byte>().ToArray<byte>());
                else
                    WriteRange(0x38, BitConverter.GetBytes(value));
            }
        }

        private byte IncludesCount
        {
            set
            {
                SCRIPT[0x3C] = value;
            }
        }

        private byte AnimtreesCount
        {
            set
            {
                SCRIPT[0x3D] = value;
            }
        }
        #endregion

        #region Util
        private void AddString(string value)
        {
            GSCFragment fragment = new GSCFragment(SCRIPT);
            fragment.Contents = StringBytes(value);
            StringRefs[value] = fragment;
        }

        private void AddInclude(string value)
        {
            GSCInclude include = new GSCInclude(SCRIPT);
            include.Fragment = StringRefs[value];
            Includes.Add(include);
        }

        private void Allocate(int space)
        {
            SCRIPT.AddRange(new byte[space]);
        }

        private void WriteRange(int position, byte[] data)
        {
            if (SCRIPT.Count < position + data.Length)
            {
                Allocate(position + data.Length - SCRIPT.Count);
            }
            for (int i = 0; i < data.Length; i++)
            {
                SCRIPT[position + i] = data[i];
            }
        }

        private byte[] StringBytes(string value)
        {
            return Encoding.ASCII.GetBytes(value + '\0');
        }
        #endregion

        private CompilationPackage Package;
        private CompilationScript ActiveScript;
        private List<byte> SCRIPT;
        internal Dictionary<string, List<KeyValuePair<string, string>>> ArrayKeys;
        internal List<GSCFragment> GSCExports;
        private Dictionary<string, List<string>> ForEachLocals;
        private List<GSCFunction> Functions;

        #region Fragments
        private Dictionary<string, GSCFragment> StringRefs;
        private Dictionary<GSCFragment, int> StringRefTracker;
        private List<GSCInclude> Includes;
        #endregion

        internal ByteCodeCompiler(CompilationPackage package, Dictionary<string, List<string>> foreachlocals)
        {
            Package = package;
            SCRIPT = new List<byte>();
            ForEachLocals = foreachlocals;
            ArrayKeys = new Dictionary<string, List<KeyValuePair<string, string>>>();
            StringRefs = new Dictionary<string, GSCFragment>();
            Includes = new List<GSCInclude>();
            StringRefTracker = new Dictionary<GSCFragment, int>();
            GSCExports = new List<GSCFragment>();
            Functions = new List<GSCFunction>();
        }

        private void Intialize()
        {
            SCRIPT.Clear();
            StringRefs.Clear();
            ArrayKeys.Clear();
            Includes.Clear();
            Functions.Clear();
            StringRefTracker.Clear();
            GSCExports.Clear();
        }

        internal List<byte> CompileToByteCode(ParseTree tree, CompilationScript activescript)
        {
            ActiveScript = activescript;
            Intialize();                //Clear old data, etc. Should be like a fresh start. Basically useless because of compiler implementation, but still there for safety
            CleanTree(tree.Root, null); //Remove unnecessary information (types, etc.)
            Allocate(0x40);             //Allocate header space
            Watermark = 0x4000;         //Name Position
            WriteMagic();               //Write Header Magic
            WriteGSXSignature();        //Write the GSX Magic
            AddProjectWatermark();      //Add Watermark name
            CollectStrings(tree);       //Collect used strings and write includes structure
            CollectIncludes(tree);      //Collect used includes and write to structure
            WriteFunctions(tree);       //Write functions

            FinalizeScript();
            return SCRIPT;
        }

        private void WriteMagic()
        {
            WriteRange(0x0, new byte[] { 0x80, 0x47, 0x53, 0x43, 0x0D, 0x0A, 0x00, 0x06 });
        }
        
        private void WriteGSXSignature()
        {
            WriteRange(0x8, new byte[] { 0x43, 0x47, 0x53, 0x58 });
        }

        private void AddProjectWatermark()
        {
            string scriptshortname = ActiveScript.ScriptName.Substring(ActiveScript.ScriptName.LastIndexOf('\\') + 1);
            scriptshortname = scriptshortname.Substring(0, scriptshortname.Length - 4) + ".cgsx";
            string toadd = Package.ProjectName + " by " + Package.CreatorName + " [" + scriptshortname + "]";
            SCRIPT.AddRange(StringBytes(toadd));
        }

        internal bool CleanTree(ParseTreeNode node, ParseTreeNodeList list)
        {
            if(!IsNodeClean(node.Term.Name))
            {
                list.Remove(node);
                return true;
            }
            for(int i = 0; i < node.ChildNodes.Count; i++)
            {
                if (CleanTree(node.ChildNodes[i], node.ChildNodes))
                    i--;
            }
            return false;
        }

        internal bool IsNodeClean(string name)
        {
            return !( //Fuck demorgans. I want nice code
                name == "gsxtype" ||
                name == "gsxtype?" || 
                name == "gsxtypefragment" ||
                name == "cast" ||
                (name == "debugregion" && !Package.Debug)
                );
        }

        private void CollectStrings(ParseTree tree)
        {
            foreach(var declaration in tree.Root.ChildNodes[0].ChildNodes)
            {
                if(declaration.ChildNodes[0].Term.Name == "preprocessor" && declaration.ChildNodes[0].ChildNodes[0].Term.Name == "ppcinclude")
                {
                    var toadd = GetIncludeFromNode(declaration.ChildNodes[0].ChildNodes[0].ChildNodes[1]);
                    if (StringRefs.ContainsKey(toadd))
                        continue;
                    AddString(toadd);
                }
            }
            foreach (var declaration in tree.Root.ChildNodes[0].ChildNodes)
            {
                if (declaration.ChildNodes[0].Term.Name == "function")
                {
                    CollectAndMarkStrings(declaration.ChildNodes[0], declaration.ChildNodes[0].ChildNodes[1].Token.Value.ToString());
                }
                if (declaration.ChildNodes[0].Term.Name == "usinganimtree")
                {
                    CollectAndMarkStrings(declaration.ChildNodes[0]);
                }
            }
        }

        private static string GetIncludeFromNode(ParseTreeNode node)
        {
            string toreturn = node.ChildNodes[0].FindTokenAndGetText().ToLower() + "/";
            for(int i = 0; i < node.ChildNodes[2].ChildNodes.Count; i++)
            {
                var gsclocation = node.ChildNodes[2].ChildNodes[i];
                toreturn += gsclocation.ChildNodes[gsclocation.ChildNodes.Count - 1].FindTokenAndGetText().ToLower() + "/";
            }
            toreturn = toreturn.Substring(0, toreturn.Length - 1);
            return toreturn;
        }

        private bool IsObjectOwnerOrBuiltIn(string str)
        {
            str = str.ToLower();
            switch (str)
            {
                case "true":
                case "false":
                case "waittillmatch":
                case "waittill":
                case "endon":
                case "notify":
                case "vectorscale":
                case "getnextarraykey":
                case "getfirstarraykey":
                case "undefined":
                case "anglestoright":
                case "anglestoforward":
                case "anglelamp180":
                case "vectortoangles":
                case "abs":
                case "gettime":
                case "anglestoup":
                case "getdvar":
                case "isdefined":
                case "anim":
                case "game":
                case "self":
                case "level":
                case "getdvarint":
                case "getdvarfloat":
                case "getdvarvector":
                case "getdvarcolorred":
                case "getdvarcolorgreen":
                case "getdvarcolorblue":
                case "getdvarcoloralpha":
                    return true;
                default:
                    return false;
            }
        }

        private void CollectAndMarkStrings(ParseTreeNode node, string functionname = null)
        {
            ArrayKeys[functionname] = new List<KeyValuePair<string, string>>();
            foreach (ParseTreeNode childNode in node.ChildNodes)
            {
                switch (childNode.Term.Name)
                {
                    case "functionproperty":
                    case "gsxtype":
                    case "labelcommand":
                    case "gotocommand":
                        break;
                    case "identifier":
                        childNode.Token.Value = childNode.Token.ValueString.ToLower().Replace(@"\", "/");
                        if (IsObjectOwnerOrBuiltIn(childNode.Token.ValueString) || StringRefs.ContainsKey(childNode.Token.ValueString))
                            break;
                        AddString(childNode.Token.Value.ToString());
                        break;

                    case "stringLiteral":
                        if (IsObjectOwnerOrBuiltIn(childNode.Token.ValueString) || StringRefs.ContainsKey(childNode.Token.ValueString))
                            break;
                        AddString(childNode.Token.ValueString);
                        break;

                    case "foreachstatement":
                        string first = ForEachLocals[functionname][0];
                        ForEachLocals[functionname].RemoveAt(0);
                        string second = ForEachLocals[functionname][0];
                        ForEachLocals[functionname].RemoveAt(0);
                        ArrayKeys[functionname].Add(new KeyValuePair<string,string>(first, second));
                        if(!StringRefs.ContainsKey(first))
                            AddString(first);
                        if(!StringRefs.ContainsKey(second))
                            AddString(second);
                        CollectAndMarkStrings(childNode, functionname);
                        break;
                    default:
                        CollectAndMarkStrings(childNode, functionname);
                        break;
                }
            }
        }

        private void CollectIncludes(ParseTree tree)
        {
             byte includesCount = 0;
            foreach (var declaration in tree.Root.ChildNodes[0].ChildNodes)
            {
                if (declaration.ChildNodes[0].Term.Name == "preprocessor" && declaration.ChildNodes[0].ChildNodes[0].Term.Name == "ppcinclude")
                {
                    var toadd = GetIncludeFromNode(declaration.ChildNodes[0].ChildNodes[0].ChildNodes[1]);
                    AddInclude(toadd);
                    includesCount++;
                }
            }
            IncludesCount = includesCount;
        }

        private void WriteFunctions(ParseTree tree)
        {
            foreach(var declaration in tree.Root.ChildNodes[0].ChildNodes)
            {
                if (declaration.ChildNodes[0].Term.Name == "function")
                {
                    GSCFunction function = new GSCFunction(SCRIPT, this, declaration.ChildNodes[0], Package.Target == PlatformTarget.Console);
                    function.EmitFunction();
                    Functions.Add(function);
                }
            }
        }

        internal GSCFragment GetStringFrag(string value)
        {
            return StringRefs[value];
        }

        internal void FinalizeScript()
        {
            List<string> strings = StringRefs.Keys.ToList();
            strings.Sort();
            foreach (string key in strings)
            {
                StringRefs[key].Write();
            }
            IncludesPtr = SCRIPT.Count;
            IncludesCount = (byte)Includes.Count;
            foreach (var include in Includes)
            {
                include.Write();
            }
            Align32();
            CodeSectionPtr = SCRIPT.Count;
            foreach(var function in Functions)
            {
                function.Write();
            }
            Align32();
            ExportsPtr = SCRIPT.Count;
            ExportsCount = (ushort)GSCExports.Count;
            foreach (GSCFragment export in GSCExports)
            {
                export.Write();
            }
            Align32();
            StringRefsPtr = SCRIPT.Count;
            StringRefsCount = WriteStringRefs();
            
        }

        internal void Align16(byte offset = 0)
        {
            var alignedPos = (int)(SCRIPT.Count + 1 + offset & 0xFFFFFFFE);
            if (SCRIPT.Count < alignedPos)
                SCRIPT.AddRange(new byte[alignedPos - SCRIPT.Count]);
        }

        internal void Align32(byte offset = 0)
        {
            var alignedPos = (int)(SCRIPT.Count + 3 + offset & 0xFFFFFFFC);
            if (SCRIPT.Count < alignedPos)
                SCRIPT.AddRange(new byte[alignedPos - SCRIPT.Count]);
        }

        internal ushort WriteStringRefs()
        {
            List<string> sortedkeys = StringRefs.Keys.ToList();
            sortedkeys.Sort();
            ushort count = 0;
            foreach(var key in sortedkeys)
            {
                if(StringRefs[key].StringReferencePositions.Count > 0)
                {
                    AddData(StringRefs[key].Position, 2);
                    byte refcount;
                    while (StringRefs[key].StringReferencePositions.Count > 0)
                    {
                        refcount = (byte)Math.Min(250, StringRefs[key].StringReferencePositions.Count); //Only write 250 at a time
                        SCRIPT.Add(refcount);
                        SCRIPT.Add(0x1);
                        for (int i = 0; i < refcount; i++)
                        {
                            AddData(BitConverter.GetBytes(StringRefs[key].StringReferencePositions[0]), 4);
                            StringRefs[key].StringReferencePositions.RemoveAt(0);
                        }
                    }
                    count++;
                }
                if (StringRefs[key].LocalStringReferencePositions.Count > 0)
                {
                    AddData(StringRefs[key].Position, 2);
                    byte refcount;
                    while (StringRefs[key].LocalStringReferencePositions.Count > 0)
                    {
                        refcount = (byte)Math.Min(250, StringRefs[key].LocalStringReferencePositions.Count); //Only write 250 at a time
                        SCRIPT.Add(refcount);
                        SCRIPT.Add(0x0);
                        for (int i = 0; i < refcount; i++)
                        {
                            AddData(BitConverter.GetBytes(StringRefs[key].LocalStringReferencePositions[0]), 4);
                            StringRefs[key].LocalStringReferencePositions.RemoveAt(0);
                        }
                    }
                    count++;
                }
            }
            return count;
        }

        internal void AddData(byte[] data, int size)
        {
            if (Package.Target == PlatformTarget.Console)
                data = data.Reverse<byte>().ToArray<byte>();
            for (int i = (Package.Target == PlatformTarget.Console) ? (data.Length - size) : 0; i < ((Package.Target == PlatformTarget.Console) ? data.Length : size); i++)
            {
                SCRIPT.Add(data[i]);
            }
        }
    }
}