using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;
using System.Reflection;
using System.IO;
using static GSXCompilerLib.GSXLibraries;

namespace GSXCompilerLib.GSC
{
    internal static class GSCStaticVariables
    {
        /// <summary>
        /// Defines replacements for any function references
        /// </summary>
        internal static Dictionary<string, string> FunctionRefLexicon = new Dictionary<string, string>();
        /// <summary>
        /// Defines replacements for any local for each function
        /// </summary>
        internal static Dictionary<string, Dictionary<string, string>> LocalLexicon = new Dictionary<string, Dictionary<string, string>>();
        internal static Dictionary<string, string> GlobalLexicon = new Dictionary<string, string>();
        internal static List<string> WhiteListedFunctions = new List<string>();
        internal static List<string> BlacklistedStrings = new List<string>();
        internal static Dictionary<string, string> StringLexicon = new Dictionary<string, string>();
        internal static Dictionary<string, List<string>> Available_keys = new Dictionary<string, List<string>>();
        /// <summary>
        /// List of function names within the current file used only to compare against references to it
        /// </summary>
        internal static List<string> FunctionNames;
        /// <summary>
        /// List of names that have been used already when generating function names
        /// </summary>
        internal static List<string> FunctionExcludes;

        internal static void ResetAllStaticVars()
        {
            FunctionExcludes = new List<string>();
            FunctionExcludes.Add("abs");
            FunctionExcludes.Add("int");
            FunctionRefLexicon = new Dictionary<string, string>();
            LocalLexicon = new Dictionary<string, Dictionary<string, string>>();
            GlobalLexicon = new Dictionary<string, string>();
            WhiteListedFunctions = new List<string>();
            BlacklistedStrings = new List<string>();
            StringLexicon = new Dictionary<string, string>();
            Available_keys = new Dictionary<string, List<string>>();
            FunctionNames = new List<string>();
        }
    }

    /// <summary>
    /// Optimize GSCs
    /// </summary>
    internal sealed class GSCOptimizer
    {
        #region private
        private const string chars = "abcdefghijklmnopqrstuvwxyz_0123456789";
        #endregion
        //This limits the amount of times a string will be used at any point in the program
        public string ERROR_MSG
        {
            get
            {
                if(error_msg == null)
                {
                    error_msg = "";
                }
                return error_msg;
            }
            set
            {
                if (value != "")
                    EXIT_CODE = 1;
                error_msg = value;
            }
        }
        private string error_msg = "Unknown Error";


        public int EXIT_CODE = 0;
        internal static int includespaced = 0;
        internal List<int> whitespacepositions = new List<int>();

        //New
        private GSCCompiler This;
        internal const int STRING_REF_MAX = 65535;//lol
        internal static string StringFromBytes = "";
        internal List<KeyValuePair<string, string>> whitelist = new List<KeyValuePair<string, string>>();
        internal List<KeyValuePair<string, string>> blacklist = new List<KeyValuePair<string, string>>();
        internal List<string> stringblacklist = new List<string>(), functionwhitelist = new List<string>();
        internal ParseTree Tree;



        internal List<ParseTreeNode> Includes = new List<ParseTreeNode>();
        internal List<ParseTreeNode> LibIncludes = new List<ParseTreeNode>();
        internal List<ParseTreeNode> Defines = new List<ParseTreeNode>();
        internal List<ParseTreeNode> StringAways = new List<ParseTreeNode>();
        internal List<ParseTreeNode> StringProtections = new List<ParseTreeNode>();
        internal List<ParseTreeNode> AnimTrees = new List<ParseTreeNode>();
        internal List<ParseTreeNode> Functions = new List<ParseTreeNode>();


        /// <summary>
        /// List of argument tokens for each function in the file
        /// </summary>
        internal Dictionary<string, List<Token>> FunctionArguments;
        /// <summary>
        /// List of local variable tokens for each function
        /// </summary>
        internal Dictionary<string, List<Token>> FunctionLocals;
        /// <summary>
        /// List of references to each function (including header of function)
        /// </summary>
        internal Dictionary<string, List<Token>> FunctionRefs;
        /// <summary>
        /// Variable names that are invalid for the current function's locals
        /// </summary>
        internal List<string> local_excludes;

        /// <summary>
        /// List of global variable references within the curent file
        /// </summary>
        internal List<Token> Globals;
        /// <summary>
        /// Deprecated way of counting string usage
        /// </summary>
        internal Dictionary<string, int> GlobalUses;//Should be fine not being static

        /// <summary>
        /// List of all identifier tokens within the file
        /// </summary>
        internal List<ParseTreeNode> IdentifierTokens;

        internal List<string> ReplacedStrings = new List<string>();

        internal delegate void NodeOperator(ParseTreeNode node, string function, string type);
        
        
        internal List<Token> StringLiterals;
        
        internal Dictionary<Token, int> Foreach_Ref_count;
        internal Dictionary<string, int> Function_Foreach_Count;
        internal string Data;
        internal string OutputPath;
        internal List<GSCOptimizer> OtherScripts;
        internal object[] CompilerParams;

        public GSCOptimizer(GSCCompiler ths, string DATA, string outpath, object[] compilerparams)
        {
            CompilerParams = compilerparams;
            Data = DATA;
            OutputPath = outpath;
            This = ths;
            //FunctionNames = new List<string>();
            FunctionArguments = new Dictionary<string, List<Token>>();
            FunctionRefs = new Dictionary<string, List<Token>>();
            FunctionLocals = new Dictionary<string, List<Token>>();
            Globals = new List<Token>();
            local_excludes = new List<string>();
            GlobalUses = new Dictionary<string, int>();
            IdentifierTokens = new List<ParseTreeNode>();
            ReplacedStrings = new List<string>();
            StringLiterals = new List<Token>();
            Foreach_Ref_count = new Dictionary<Token, int>();
            Function_Foreach_Count = new Dictionary<string, int>();
            OtherScripts = new List<GSCOptimizer>();
        }

        public bool Begin()
        {
            return
                Defaults() &&
                ParseAndReplaceDefines();
        }

        public bool ReplaceGlobals()
        {
            return IReplaceGlobals(); 
        }

        public bool CollectLocal()
        {
            return  IAssignLocalTemplates(); 
        }

        public bool Finish()
        {
            return
                IReplaceLocals() &&
                IReplaceStrings() &&
                IAssignFunctionRefs();
                
        }

        public bool NewFinish()
        {
            return
                IReplaceFunctionRefs() &&
                IReconstructGSC() &&
                ICompile() &&
                IObfuscate();
        }

        internal bool Link(string scr_name)
        {
            bool Success = true;
            List<string> Includes = new List<string>();
            Includes.Add(scr_name.Replace('\\', '/').ToLower().Replace(".gsx", ".gsc"));
            EndianReader Reader = new EndianReader(File.ReadAllBytes(OutputPath), This.PC ? EndianType.LittleEndian : EndianType.BigEndian);
            Reader.SeekTo(0xC);
            int IncludesPTR = Reader.ReadInt32();
            Reader.SeekTo(0x20);
            uint PtrToEterns = Reader.ReadUInt32();
            Reader.SeekTo(0x36);
            ushort NumExterns = Reader.ReadUInt16();
            Reader.SeekTo(0x3C);
            byte NumIncludes = Reader.ReadByte();

            Reader.SeekTo(IncludesPTR);
            for(int i = 0; i < NumIncludes; i++)
            {
                uint location = Reader.ReadUInt32();
                long origin = Reader.BaseStream.Position;
                Reader.SeekTo(location);
                string target = Reader.ReadNullTerminatedString().ToLower().Replace('\\', '/');
                Includes.Add(target);
                Reader.SeekTo(origin);
            }
            string FinalMSG = "";
            int ErrorCount = 0;
            Reader.SeekTo(PtrToEterns);
            for(int i = 0; i < NumExterns; i++)
            {
                ushort NamePtr = Reader.ReadUInt16();
                ushort NamespacePtr = Reader.ReadUInt16();
                ushort NumReferences = Reader.ReadUInt16();
                byte NumParams = Reader.ReadByte();
                byte Flag = Reader.ReadByte();
                for(int j = 0; j < NumReferences; j++)
                    Reader.ReadUInt32();
                long Origin = Reader.BaseStream.Position;
                Reader.SeekTo(NamePtr);
                string Name = Reader.ReadNullTerminatedString();
                string Namespace = "";
                if(NamespacePtr != 0x0)
                {
                    Reader.SeekTo(NamespacePtr);
                    Namespace = Reader.ReadNullTerminatedString();
                }
                Reader.SeekTo(Origin);
                T6FunctionResolver.FunctionResolution resolution = T6FunctionResolver.ResolveFunctionFromLib(Name, NumParams, Includes, Namespace);
                if(resolution.IsError)
                {
                    Success = false;
                    ErrorCount++;
                    //FinalMSG += "\nNamespace: " + resolution.Namespace + " Name: " + resolution.Name + " Internal: " + resolution.Internal + " Numparams: " + resolution.NumParams + " FailureType: " + resolution.FailureType + " UsingInclude: " + resolution.UsingInclude;
                    FinalMSG += "\nFailed to resolve " + (Namespace == "" ? "" : Namespace + "::") + F_ResolveOriginalName(Name) + " with " + NumParams +" parameters in " + scr_name + "\n";
                }
            }

            if (!Success)
            {
                ERROR_MSG += "\n\\\\***** " + ErrorCount + " script error(s) *****//\n" + FinalMSG;
            }

            return Success;
        }

        /// <summary>
        /// Resolve the original name of a function after being optimized
        /// </summary>
        /// <param name="o_name"></param>
        /// <returns></returns>
        public string F_ResolveOriginalName(string o_name)
        {
            foreach (string key in GSCStaticVariables.FunctionRefLexicon.Keys)
                if (GSCStaticVariables.FunctionRefLexicon[key].ToLower().Equals(o_name.ToLower()))
                    return key.ToLower();

            return "__ERROR__" + o_name;
        }

        /// <summary>
        /// Resolve the original name of a variable after optimization
        /// </summary>
        /// <param name="varname"></param>
        /// <param name="funcname"></param>
        /// <returns></returns>
        public string V_ResolveOriginalName(string varname, string funcname)
        {
            if (varname == null)
                return "NULL_VARIABLE";
            if (funcname == null)
                return varname;
            funcname = funcname.ToLower();
            varname = varname.ToLower();
            if (GSCStaticVariables.LocalLexicon.ContainsKey(funcname))
            {
                foreach(string key in GSCStaticVariables.LocalLexicon[funcname].Keys)
                {
                    if (GSCStaticVariables.LocalLexicon[funcname][key] == varname)
                        return key.ToLower();
                }
            }
            return varname;
        }

        public bool Main()
        {
            ResetGlobals();
            try
            {
                if (!This.CompileOnly)
                    return 
                           Defaults() &&
                           ParseAndReplaceDefines() &&
                           ICollectVariableTokens() &&
                           IReplaceGlobals() && //Should be good
                           IAssignLocalTemplates() &&
                           IReplaceLocals() &&
                           IReplaceStrings() &&
                           IAssignFunctionRefs() &&
                           IReconstructGSC() &&
                           ICompile() &&
                           IObfuscate();
                else
                {
                    return
                            ICompile();
                }
                    
            }
            catch (Exception e)
            {
                ERROR_MSG = "Internal exception: " + e.GetBaseException().ToString();
                return false;
            }
        }

        internal void ResetGlobals()
        {
            whitelist = new List<KeyValuePair<string, string>>();
            blacklist = new List<KeyValuePair<string, string>>();
            stringblacklist = new List<string>();
            functionwhitelist = new List<string>();
            //FunctionNames = new List<string>();
            FunctionArguments = new Dictionary<string, List<Token>>();
            FunctionLocals = new Dictionary<string, List<Token>>();
            FunctionRefs = new Dictionary<string, List<Token>>();
            local_excludes = new List<string>();
            Globals = new List<Token>();
            GlobalUses = new Dictionary<string, int>();
            IdentifierTokens = new List<ParseTreeNode>();
            ReplacedStrings = new List<string>();
            StringLiterals = new List<Token>();
            Foreach_Ref_count = new Dictionary<Token, int>();
            Function_Foreach_Count = new Dictionary<string, int>();
        }

        ParseTree MacrosTree;

        public bool Defaults()
        {
            if (This.DefaultProtections)
            {
                var assembly = Assembly.GetExecutingAssembly();
                using (Stream stream = assembly.GetManifestResourceStream("GSXCompilerLib.DefaultLists.txt"))
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    List<string> lines = result.Split('\n').ToList();
                    foreach (string line in lines)
                    {
                        line.Replace("\r", "");
                        ProcessPT(line);
                    }
                }
                //WhiteListedFunctions
                using (Stream stream = assembly.GetManifestResourceStream("GSXCompilerLib.functions.txt"))
                using (StreamReader reader = new StreamReader(stream))
                {
                    string result = reader.ReadToEnd();
                    List<string> lines = result.Split('\n').ToList();
                    foreach (string line in lines)
                    {
                        functionwhitelist.Add(line.Replace("\r", ""));
                    }
                }
            }

            try
            {
                var gameScript = new GSC2Grammar();
                var parser = new Parser(gameScript);
                var assembly = Assembly.GetExecutingAssembly();
                var resourceName = "GSXCompilerLib.Macros.txt";
                string result = "";
                using (Stream stream = assembly.GetManifestResourceStream(resourceName))
                using (StreamReader reader = new StreamReader(stream))
                {
                    result = reader.ReadToEnd();
                }
                MacrosTree = parser.Parse(result);
            }
            catch
            {

            }


            return true;
        }

        /// <summary>
        /// Process Protect
        /// </summary>
        /// <param name="data">Protection Parameter</param>
        internal void ProcessPT(string data)
        {
            data = data.Trim();
            string dat = data.Split(' ')[data.Split(' ').Length - 1];
            if (dat.IndexOf(".") < 1)
            {
                whitelist.Add(new KeyValuePair<string, string>("*", dat.Substring(dat.IndexOf(".") + 1)));
            }
            else if (dat.IndexOf(".") == dat.Length - 1)
            {
                whitelist.Add(new KeyValuePair<string, string>(dat.Substring(0, dat.IndexOf(".")), "*"));
            }
            else
            {
                whitelist.Add(new KeyValuePair<string, string>(dat.Substring(0, dat.IndexOf(".")), dat.Substring(dat.IndexOf(".") + 1)));
            }
        }

        private bool ParseAndReplaceDefines()
        {
            var gameScript = new GSC2Grammar();
            var parser = new Parser(gameScript);
            Tree = parser.Parse(Data);
            if(Tree.ParserMessages.Count > 0)
            {
                ERROR_MSG = "Failed to parse. Error on line " + Tree.ParserMessages[0].Location.Line;
                //File.WriteAllText("E:\\FAILED.TXT", Data);
                return false;
            }

            AppendMacros();
            CreateSubGroups();

            foreach (var function in Functions)
            {
                string name = function.ChildNodes[0].ToString().Split(' ')[0].ToLower();
                if (function.ChildNodes[2].ChildNodes.Count < 1)
                    continue; //We have no block content in this function
                var declarations = function.ChildNodes[2].ChildNodes[0].ChildNodes[0].ChildNodes; //function -> block -> blockcontent -> declarations
                IterateDefineNode(name, function.ChildNodes[2].ChildNodes[0].ChildNodes[0]);
            }

            return true;
        }

        private void AppendMacros()
        {
            foreach(var node in MacrosTree.Root.ChildNodes)
            {
                Tree.Root.ChildNodes.Add(node);
            }
        }

        private void CreateSubGroups()
        {
            Includes = new List<ParseTreeNode>();
            LibIncludes = new List<ParseTreeNode>();
            Defines = new List<ParseTreeNode>();
            StringAways = new List<ParseTreeNode>();
            StringProtections = new List<ParseTreeNode>();
            AnimTrees = new List<ParseTreeNode>();
            Functions = new List<ParseTreeNode>();
            foreach(ParseTreeNode programEntry in Tree.Root.ChildNodes)
            {
                switch (programEntry.ChildNodes[0].Term.Name.ToLower())
                {
                    case "include":
                        Includes.Add(programEntry.ChildNodes[0]);
                        break;
                    case "usinglib":
                        LibIncludes.Add(programEntry.ChildNodes[0]);
                        break;
                    case "define":
                        Defines.Add(programEntry.ChildNodes[0]);
                        break;
                    case "stringaway":
                        StringAways.Add(programEntry.ChildNodes[0]);
                        break;
                    case "parsernotification":
                        StringProtections.Add(programEntry.ChildNodes[0]);
                        break;
                    case "usingAnimTree":
                        Includes.Add(programEntry.ChildNodes[0]);
                        break;
                    case "function":
                        Functions.Add(programEntry.ChildNodes[0]);
                        break;
                    
                }

            }

            return;
        }

        private void ReplaceDefine(ParseTreeNode define, ParseTreeNode target, int Index)
        {
            string dname = define.ChildNodes[1].Token.Value.ToString().ToLower();
            if (dname != target.ChildNodes[Index].FindToken().Value.ToString().ToLower())
                return;
            target.ChildNodes[Index] = define.ChildNodes[2];
        }

        private void IDefineReplacement(ParseTreeNode ParentNode, int Index, string function, string type)
        {
            if(type == "local")
            {
                foreach (var define in Defines)
                {
                    ReplaceDefine(define, ParentNode, Index);
                }
            }
            
        }

        internal bool ICollectFunctionNames()
        {
           
            foreach (var function in Functions) //Setup functions
            {
                string name = function.ChildNodes[0].ToString().Split(' ')[0].ToLower();
                GSCStaticVariables.FunctionNames.Add(name.ToLower());       //All function names need to be setup
                FunctionArguments[name] = new List<Token>();
                Function_Foreach_Count[name] = 0;
                FunctionLocals[name] = new List<Token>();
                FunctionRefs[name] = new List<Token>();
                if (!GSCStaticVariables.LocalLexicon.ContainsKey(name))
                    GSCStaticVariables.LocalLexicon[name] = new Dictionary<string, string>();
                
            }

            return true;
        }

        /// <summary>
        /// Collects variable tokens from the gsc parse tree
        /// </summary>
        /// <returns></returns>
        public bool ICollectVariableTokens()
        {
            CollectIdentifiers(Tree.Root);
            //List<string> uniqueids = new List<string>(); //count ids
            //foreach (var tok in IdentifierTokens)
            //{
            //    if (tok.Term == GSC2Grammar.numberLiteral)
            //        continue;
            //    string val = tok.FindToken().ValueString.ToLower();
            //    if (tok.Term == GSC2Grammar.stringLiteral)
            //    {
            //        val = tok.FindToken().ValueString;
            //    }
            //    if (uniqueids.Contains(val))
            //        continue;
            //    uniqueids.Add(tok.FindToken().ValueString.ToLower());
            //}

            foreach(var userprot in StringProtections)
            {
                IterateNode("undefined", ICollect, userprot);
            }

            foreach (var stringaway in StringAways)
            {
                IterateNode("undefined", ICollect, stringaway);
            }

            foreach (var function in Functions)
            {
                string name = function.ChildNodes[0].ToString().Split(' ')[0].ToLower();
                if (function.ChildNodes[1].ChildNodes[0].ToString().Split(' ')[0] == "parameters")
                {
                    foreach (var arg in function.ChildNodes[1].ChildNodes[0].ChildNodes)
                    {
                        FunctionArguments[name].Add(arg.ChildNodes[0].Token);
                        FunctionLocals[name].Add(arg.ChildNodes[0].Token);
                    }
                }
                if (function.ChildNodes[2].ChildNodes.Count < 1)
                    continue; //We have no block content in this function
                var declarations = function.ChildNodes[2].ChildNodes[0].ChildNodes[0].ChildNodes; //function -> block -> blockcontent -> declarations
                IterateNode(name, ICollect, function.ChildNodes[2].ChildNodes[0].ChildNodes[0]);
            }
            return true;
        }

        private int IterateDefineNode(string function, ParseTreeNode node, bool HasChild = false, bool IsRef = false)
        {
            try
            {
                switch (node.ToString())
                {
                    case "arrayshorthand":
                        {
                            IterateDefineNode(function, node.ChildNodes[1], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[3], HasChild, IsRef);
                            break;
                        }
                    case "expr":
                        {
                            if (node.ChildNodes[0].Term.Name == GSC2Grammar.identifier.Name)
                            {
                                if (IsRef)
                                {
                                    
                                }
                                else
                                {
                                    IDefineReplacement(node, 0 ,function, "local"); //Always local -- Direct access picks up children
                                }
                                break;
                            }
                            if (node.ChildNodes[0].Term.Name == GSC2Grammar.stringLiteral.Name)
                            {
                                
                            }
                            foreach (var child in node.ChildNodes)
                            {
                                IterateDefineNode(function, child, HasChild, IsRef);
                            }
                            break;
                        }
                    case "protectBlock":
                        {
                            if(node.ChildNodes.Count > 1)
                            {
                                IterateDefineNode(function, node.ChildNodes[1], HasChild, IsRef);
                            }
                            break;
                        }
                    case "protectExpr":
                        {
                            IterateDefineNode(function, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "directAccess": //expr + identifier -- this is aka global
                        {
                            IterateDefineNode(function, node.ChildNodes[0], true); //Let our handler work
                            
                            break;
                        }
                    case "getFunction": //function | external + function -- We only need internals
                        {
                            if (node.ChildNodes.Count < 2)
                                IterateDefineNode(function, node.ChildNodes[0], false, true);
                            break;
                        }
                    case "size": // expr + .size
                        {
                            IterateDefineNode(function, node.ChildNodes[0]);
                            break;
                        }
                    case "boolNot": //! + expr
                        {
                            IterateDefineNode(function, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "conditionalStatement": //bool + ? + expr + : + expr
                        {
                            IterateDefineNode(function, node.ChildNodes[0], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[4], HasChild, IsRef);
                            break;
                        }
                    case "array": //expr + expr | []
                        {
                            if (node.ChildNodes.Count < 2)
                            {
                                break;
                            }
                            foreach (var child in node.ChildNodes)
                            {
                                IterateDefineNode(function, child); //Dont pass because scope changes
                            }
                            break;
                        }

                    case "baseCall": // gscForFunction + identifier + parenParameters | identifier + parenParameters
                        {
                            if (node.ChildNodes.Count < 3)
                            {
                                IterateDefineNode(function, node.ChildNodes[1], HasChild, IsRef);
                                
                            }
                            else
                            {
                                //INode(node.ChildNodes[1], function, "function"); Dont parse externals
                                IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef); //Collect parameters, but not the external function name
                            }
                            break;
                        }
                    case "developerScript": // /# + expr + #/
                        {
                            IterateDefineNode(function, node.ChildNodes[1]);
                            break;
                        }
                    case "foreachStatement": //foreach + local + in + expr + statementblock
                        {
                            IterateDefineNode(function,  node.ChildNodes[3], HasChild, IsRef);
                            IterateDefineNode(function,  node.ChildNodes[4], HasChild, IsRef);
                            break;
                        }
                    case "forStatement": //for + forbody + statementblock
                        {
                            IterateDefineNode(function,  node.ChildNodes[1], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "ifStatement": //if + boolExpr + statementblock + ?else
                        {
                            IterateDefineNode(function,node.ChildNodes[1], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef);
                            if (node.ChildNodes.Count > 3) //else
                                IterateDefineNode(function, node.ChildNodes[3], HasChild, IsRef);
                            break;
                        }
                    case "whileStatement": //while + boolExpr + statementblock
                        {
                            IterateDefineNode(function,  node.ChildNodes[1], HasChild, IsRef);
                            IterateDefineNode(function,  node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "elseStatement": //else + statementblock
                        {
                            IterateDefineNode(function,  node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "switchStatement": //switch + parenExpr + switchContents
                        {
                            IterateDefineNode(function,  node.ChildNodes[1], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "switchLabel": //keyword + ?id + keyword
                        {
                            if (node.ChildNodes.Count > 2)
                                IterateDefineNode(function, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "boolevaloperator": //Dont care
                        {
                            break;
                        }
                    case "scriptThreadCall": //thread (keyword) + basecall
                        {
                            IterateDefineNode(function,  node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "scriptThreadCallPointer": //thread (keyword) + baseCallPointer
                        {
                            IterateDefineNode(function,  node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "scriptMethodThreadCall": //expr + thread + basecall
                        {
                            IterateDefineNode(function, node.ChildNodes[0], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "scriptMethodThreadCallPointer": //expr + thread + baseCallPointer
                        {
                            IterateDefineNode(function,  node.ChildNodes[0], HasChild, IsRef);
                            IterateDefineNode(function, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "baseCallPointer": //expr + paren
                        {
                            //INode(node.ChildNodes[0].ChildNodes[0], function, "function"); //expr.identifier
                            IterateDefineNode(function, node.ChildNodes[0], HasChild);
                            IterateDefineNode(function, node.ChildNodes[1], HasChild);
                            break;
                        }
                    case "userprotections":
                        {
                            
                            break;
                        }
                    case "userblacklist":
                        {
                            
                            break;
                        }
                    case "waitTillFrameEnd":
                    case "relationalOperator":
                    case "operator":
                    case "numberLiteral":
                    case "xnumberLiteral":
                    case "stringLiteral":
                    case "shortExprOperator":
                    case "isString":
                    case "gscForFunction":
                    case "libraryReference":
                    case "hashedString":
                    case "getAnimation":
                    case "labelTerminal":
                    case "gotoTerminal":
                    case "animTree":
                        break; //ignore
                    default:
                        {
                            //if(node.Token != null && node.Term == GSC2Grammar.identifier)
                            //{
                            //    if(IsRef)
                            //    {

                            //    }
                            //    else
                            //    {

                            //    }
                            //}
                            foreach (var child in node.ChildNodes)
                            {
                                IterateDefineNode(function, child, HasChild, IsRef);
                            }
                            break;
                        }
                }
            }
            catch
            {
                throw new Exception();
            }
            return 0;
        }

        internal void CollectIdentifiers(ParseTreeNode node)
        {
            foreach (var nod in node.ChildNodes)
            {
                CollectIdentifiers(nod);
            }
            if (node.Token != null && (node.Term.Name == GSC2Grammar.identifier.Name || node.Term.Name == GSC2Grammar.stringLiteral.Name))
            {
                //node.Token.Value = node.Token.ToString();
                IdentifierTokens.Add(node);
            }
        }

        private int IterateNode(string function, NodeOperator INode, ParseTreeNode node, bool HasChild = false, bool IsRef = false)
        {
            try
            {
                switch (node.ToString())
                {
                    case "arrayshorthand":
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[3], HasChild, IsRef);
                            break;
                        }
                    case "expr":
                        {
                            if (node.ChildNodes[0].Term.Name == GSC2Grammar.identifier.Name)
                            {
                                if (IsRef)
                                {
                                    INode(node.ChildNodes[0], function, "function");
                                }
                                else
                                {
                                    INode(node.ChildNodes[0], function, "local"); //Always local -- Direct access picks up children
                                }
                                break;
                            }
                            if (node.ChildNodes[0].Term.Name == GSC2Grammar.stringLiteral.Name)
                            {
                                INode(node.ChildNodes[0], function, "string");
                            }
                            foreach (var child in node.ChildNodes)
                            {
                                IterateNode(function, INode, child, HasChild, IsRef);
                            }
                            break;
                        }
                    case "protectBlock":
                        {
                            if (node.ChildNodes.Count > 1)
                            {
                                IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            }
                            break;
                        }
                    case "protectExpr":
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "directAccess": //expr + identifier -- this is aka global
                        {
                            IterateNode(function, INode, node.ChildNodes[0], true); //Let our handler work
                            INode(node.ChildNodes[1], function, "global");
                            break;
                        }
                    case "getFunction": //function | external + function -- We only need internals
                        {
                           // string GetFuncID = "";
                            if (node.ChildNodes.Count < 2)
                                IterateNode(function, INode, node.ChildNodes[0], false, true);
                            break;
                        }
                    case "size": // expr + .size
                        {
                            IterateNode(function, INode, node.ChildNodes[0]);
                            break;
                        }
                    case "boolNot": //! + expr
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "conditionalStatement": //bool + ? + expr + : + expr
                        {
                            IterateNode(function, INode, node.ChildNodes[0], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[4], HasChild, IsRef);
                            break;
                        }
                    case "array": //expr + expr | []
                        {
                            if (node.ChildNodes.Count < 2)
                            {
                                break;
                            }
                            foreach (var child in node.ChildNodes)
                            {
                                IterateNode(function, INode, child); //Dont pass because scope changes
                            }
                            break;
                        }

                    case "baseCall": // gscForFunction + identifier + parenParameters | identifier + parenParameters
                        {
                            if (node.ChildNodes.Count < 3)
                            {
                                IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                                INode(node.ChildNodes[0], function, "function");
                            }
                            else
                            {
                                //INode(node.ChildNodes[1], function, "function"); Dont parse externals
                                IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef); //Collect parameters, but not the external function name
                            }
                            break;
                        }
                    case "developerScript": // /# + expr + #/
                        {
                            IterateNode(function, INode, node.ChildNodes[1]);
                            break;
                        }
                    case "foreachStatement": //foreach + local + in + expr + statementblock
                        {
                            INode(node.ChildNodes[1], function, "local");
                            Function_Foreach_Count[function] += 2;
                            int count_of_refs = CountForeachRefs(node.ChildNodes[1].FindTokenAndGetText().ToLower(), node.ChildNodes[3]) + CountForeachRefs(node.ChildNodes[1].FindTokenAndGetText().ToLower(), node.ChildNodes[4]);
                            Foreach_Ref_count[node.ChildNodes[1].Token] = count_of_refs;
                            IterateNode(function, INode, node.ChildNodes[3], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[4], HasChild, IsRef);
                            break;
                        }
                    case "forStatement": //for + forbody + statementblock
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "ifStatement": //if + boolExpr + statementblock + ?else
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            if (node.ChildNodes.Count > 3) //else
                                IterateNode(function, INode, node.ChildNodes[3], HasChild, IsRef);
                            break;
                        }
                    case "whileStatement": //while + boolExpr + statementblock
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "elseStatement": //else + statementblock
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "switchStatement": //switch + parenExpr + switchContents
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "switchLabel": //keyword + ?id + keyword
                        {
                            if (node.ChildNodes.Count > 2)
                                IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "boolevaloperator": //Dont care
                        {
                            break;
                        }
                    case "scriptThreadCall": //thread (keyword) + basecall
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "scriptThreadCallPointer": //thread (keyword) + baseCallPointer
                        {
                            IterateNode(function, INode, node.ChildNodes[1], HasChild, IsRef);
                            break;
                        }
                    case "scriptMethodThreadCall": //expr + thread + basecall
                        {
                            IterateNode(function, INode, node.ChildNodes[0], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "scriptMethodThreadCallPointer": //expr + thread + baseCallPointer
                        {
                            IterateNode(function, INode, node.ChildNodes[0], HasChild, IsRef);
                            IterateNode(function, INode, node.ChildNodes[2], HasChild, IsRef);
                            break;
                        }
                    case "baseCallPointer": //expr + paren
                        {
                            //INode(node.ChildNodes[0].ChildNodes[0], function, "function"); //expr.identifier
                            IterateNode(function, INode, node.ChildNodes[0], HasChild);
                            IterateNode(function, INode, node.ChildNodes[1], HasChild);
                            break;
                        }
                    case "userprotections":
                        {
                            foreach (var nod in node.ChildNodes)
                            {
                                string text = nod.FindTokenAndGetText();
                                text = text.Replace("/$", "");
                                text = text.Replace("$/", "");
                                string[] lines = text.Split('\n');
                                foreach (string s in lines)
                                {
                                    if (s.Replace(" ", "").Trim().Replace("\r", "").ToLower().Length < 1)
                                        continue;
                                    whitelist.Add(new KeyValuePair<string, string>("*", s.Replace(" ", "").Trim().Replace("\r", "").ToLower()));
                                }
                            }
                            break;
                        }
                    case "userblacklist":
                        {
                            foreach (var nod in node.ChildNodes)
                            {
                                string text = nod.FindTokenAndGetText();
                                text = text.Replace("/!", "");
                                text = text.Replace("!/", "");
                                string[] lines = text.Split('\n');
                                foreach (string s in lines)
                                {
                                    if (s.Replace(" ", "").Trim().Replace("\r", "").Length < 1)
                                        continue;
                                    GSCStaticVariables.BlacklistedStrings.Add("\"" + s.Replace(" ", "").Trim().Replace("\r", "") + "\"");
                                }
                            }
                            break;
                        }
                    case "waitTillFrameEnd":
                    case "relationalOperator":
                    case "operator":
                    case "numberLiteral":
                    case "xnumberLiteral":
                    case "stringLiteral":
                    case "shortExprOperator":
                    case "isString":
                    case "gscForFunction":
                    case "hashedString":
                    case "getAnimation":
                    case "gotoTerminal":
                    case "libraryReference":
                    case "labelTerminal":
                    case "animTree":
                        break; //ignore
                    default:
                        {
                            //if(node.Token != null && node.Term == GSC2Grammar.identifier)
                            //{
                            //    if(IsRef)
                            //    {

                            //    }
                            //    else
                            //    {

                            //    }
                            //}
                            foreach (var child in node.ChildNodes)
                            {
                                IterateNode(function, INode, child, HasChild, IsRef);
                            }
                            break;
                        }
                }
            }
            catch
            {
                throw new Exception();
            }
            return 0;
        }

        private void ICollect(ParseTreeNode node, string function, string type)
        {
            if (node.Token == null)
                return;
            switch (type)
            {
                case "function":
                    {
                        if (GSCStaticVariables.FunctionNames.Contains(node.Token.Text.ToLower()))
                            FunctionRefs[function].Add(node.Token);
                        
                        break;
                    }
                case "local":
                    {
                        if (node.Token.Text.ToLower() != "level" && node.Token.Text.ToLower() != "self" && node.Token.Text.ToLower() != "game" && node.Token.Text.ToLower() != "true" && node.Token.Text.ToLower() != "false" && node.Token.Text.ToLower() != "undefined")
                        {
                            FunctionLocals[function].Add(node.Token);
                        }
                        break;
                    }
                case "global":
                    {
                        if (node.Token.Text.ToLower() != "level" && node.Token.Text.ToLower() != "self" && node.Token.Text.ToLower() != "game")
                            Globals.Add(node.Token);
                        break;
                    }
                case "string":
                    {
                        node.Token.Value = node.Token.Text;
                        StringLiterals.Add(node.Token);
                        break;
                    }
            }
        }

        internal int CountForeachRefs(string identifier, ParseTreeNode node)
        {
            int count = 0;
            foreach (var nod in node.ChildNodes)
            {
                count += CountForeachRefs(identifier, nod);
            }
            if (node.Token != null)
            {
                if (node.FindTokenAndGetText().ToLower() == identifier.ToLower())
                    count++;
            }
            return count;
        }

        /// <summary>
        /// Assign keys to the lexicon and replace values all in one.
        /// </summary>
        /// <returns></returns>
        private bool IReplaceGlobals() //Iterate and define global lexicon, then replace token object values for terminal identities
        {
            int i = 0;
            if(!This.OptimizeGlobals)
            {
                foreach (Token t in Globals)
                {
                    t.Value = t.Text.ToLower();
                    if (!GSCStaticVariables.GlobalLexicon.Keys.Contains(t.Value as string))
                        GSCStaticVariables.GlobalLexicon[t.Value as string] = t.Value as string;
                    if (GlobalUses.Keys.Contains(t.Value as string))
                    {
                        GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]]++;
                    }
                    else
                    {
                        GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]] = 1;
                    }
                }
                return true;
            }
            foreach (Token t in Globals)
            {
                t.Value = t.Text.ToLower();
                foreach (KeyValuePair<string, string> kvp in whitelist) //Replace whitelist
                {
                    if (t.Value as string == kvp.Value)
                    {
                        GSCStaticVariables.GlobalLexicon[t.Value as string] = t.Value as string; //Allow to be used for locals and function references
                        if (GlobalUses.Keys.Contains(t.Value as string))
                        {
                            GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]]++;
                        }
                        else
                        {
                            GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]] = 1;
                        }
                        goto EndOfLoop;
                    }
                }
                if (GSCStaticVariables.GlobalLexicon.Keys.Contains(t.Value as string)) //If the variable is already defined in the lexicon, increment uses and continue
                {
                    if(!GlobalUses.ContainsKey(GSCStaticVariables.GlobalLexicon[t.Value as string]))
                    {
                        GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]] = 0;
                    }
                    GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]]++;
                    continue;
                }
                
                string key = "";
                if (i == 0)
                {
                    key = "serioushd";
                }
                else
                {
                    key = chars[i / (chars.Length * chars.Length)] + "" + chars[i / (chars.Length)] + chars[i % chars.Length];
                    if (key == "abs")
                    {
                        i++;
                        key = chars[i / (chars.Length * chars.Length)] + "" + chars[i / (chars.Length)] + chars[i % chars.Length];
                    }
                }
                GSCStaticVariables.GlobalLexicon[t.Value as string] = key;
                ReplacedStrings.Add(key);
                GlobalUses[GSCStaticVariables.GlobalLexicon[t.Value as string]] = 1;
                i++;
                EndOfLoop:;
            }
            foreach (Token t in Globals)
            {
                if (GSCStaticVariables.GlobalLexicon.Keys.Contains(t.Value as string))
                {
                    t.Value = GSCStaticVariables.GlobalLexicon[t.Value as string];
                }
            }
            return true;
        }

        /// <summary>
        /// Assign local keys a lexicon value
        /// </summary>
        /// <returns></returns>
        private bool IAssignLocalTemplates()
        {
            foreach (string s in FunctionLocals.Keys)
            {
                local_excludes.Clear();
                local_excludes.Add("abs");
                foreach (Token t in FunctionLocals[s])
                {
                    int count = CountToken(FunctionLocals[s], t);
                    t.Value = t.Text.ToLower();
                    if (GSCStaticVariables.LocalLexicon[s].Keys.Contains(t.Value as string))
                    {
                        local_excludes.Add(GSCStaticVariables.LocalLexicon[s][t.Value as string]);
                        ReplacedStrings.Add(GSCStaticVariables.LocalLexicon[s][t.Value as string]);
                        continue;
                    }
                    string key = null;
                    foreach (string str in GlobalUses.Keys)
                    {
                        if (local_excludes.Contains(str))
                            continue;
                        if (GlobalUses[str] + count <= STRING_REF_MAX)
                        {
                            key = str;
                            break;
                        }
                    }
                    int i = GlobalUses.Count;
                    if (key == null)
                    {
                        GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = count;
                        key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                        while (local_excludes.Contains(key))
                        {
                            i++;
                            GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = count;
                            key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                        }
                    }
                    else
                        GlobalUses[key] += count;
                    local_excludes.Add(key);
                    ReplacedStrings.Add(key);
                    GSCStaticVariables.LocalLexicon[s][t.Value as string] = key;
                }
            }
            return true;
        }

        private int CountToken(List<Token> tokens, Token t)
        {
            int count = 0;
            foreach (Token ts in tokens)
            {
                if (ts.Text.ToLower() == t.Text.ToLower())
                    count++;
            }
            return count;
        }

        /// <summary>
        /// Replace all local references
        /// </summary>
        /// <returns></returns>
        internal bool IReplaceLocals() //Working correctly, locals are replaced with the values from the lexicon
        {
            foreach (string s in FunctionLocals.Keys) //for each function local
            {
                GSCStaticVariables.Available_keys[s] = new List<string>();
                GSCStaticVariables.Available_keys[s].AddRange(GSCStaticVariables.GlobalLexicon.Values); //add all the currently used strings in there for locals
                GSCStaticVariables.Available_keys[s].Remove("abs");
                int HighestCount = 0;
                foreach (Token t in Foreach_Ref_count.Keys) //obtain the highest foreach counter for string safety (unnecessary due to recent developments)
                {
                    if (FunctionLocals[s].Contains(t) && Foreach_Ref_count[t] > HighestCount)
                        HighestCount = Foreach_Ref_count[t];
                }
                foreach (string str in GSCStaticVariables.LocalLexicon[s].Values) //Remove any values that conflict with locals within the function
                {
                    GSCStaticVariables.Available_keys[s].Remove(str);
                }
                for (int i = 0; i < GSCStaticVariables.Available_keys[s].Count; i++) //Fix ref count
                {
                    if(!GlobalUses.ContainsKey(GSCStaticVariables.Available_keys[s][i]))
                    {
                        GlobalUses[GSCStaticVariables.Available_keys[s][i]] = 0;
                    }
                    if (GlobalUses[GSCStaticVariables.Available_keys[s][i]] + HighestCount > STRING_REF_MAX)
                    {
                        GSCStaticVariables.Available_keys[s].RemoveAt(i);
                        i--;
                    }
                }
                while (GSCStaticVariables.Available_keys[s].Count < Function_Foreach_Count[s]) //Add local references for foreaches
                {
                    int i = GlobalUses.Count;
                    GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = HighestCount; //Innaccurate but safe :)
                    string key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                    GSCStaticVariables.Available_keys[s].Add(key);
                }
            }
            
            foreach (string s in FunctionLocals.Keys) //Replace all locals
            {
                foreach (Token t in FunctionLocals[s])
                {
                    //ERROR_MSG += "\nLOCAL: " + t.Value.ToString() + " -> " + GSCStaticVariables.LocalLexicon[s][t.Text.ToLower()];
                    t.Value = GSCStaticVariables.LocalLexicon[s][t.Text.ToLower()];
                }
            }
            
            return true;
        }

        internal bool IReplaceStrings()
        {
            local_excludes.Clear();
            foreach (string s in GSCStaticVariables.BlacklistedStrings)
            {
                foreach (Token t in StringLiterals)
                {
                    if (s != t.Text)
                        continue;
                    t.Value = t.Text;
                    if (GSCStaticVariables.StringLexicon.Keys.Contains(t.Value as string))
                    {
                        local_excludes.Add(GSCStaticVariables.StringLexicon[t.Value as string]);
                        ReplacedStrings.Add(GSCStaticVariables.StringLexicon[t.Value as string]);
                        continue;
                    }
                    int count = CountStringTokens(StringLiterals, t.Value as string);
                    string key = null;
                    foreach (string str in GlobalUses.Keys)
                    {
                        if (local_excludes.Contains(str))
                            continue;
                        if (str.Length > 3)
                            continue; //Only use our newly created values to be safe :)
                        if (GlobalUses[str] + count <= STRING_REF_MAX)
                        {
                            key = str;
                            break;
                        }
                    }
                    int i = GlobalUses.Count;
                    if (key == null)
                    {
                        GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = count;
                        key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                        while (local_excludes.Contains(key))
                        {
                            i++;
                            GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = count;
                            key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                        }
                    }
                    else
                        GlobalUses[key] += count;
                    local_excludes.Add(key);
                    ReplacedStrings.Add(key);
                    GSCStaticVariables.StringLexicon[t.Value as string] = key;
                }
            }
            foreach (Token t in StringLiterals)
            {
                if (!GSCStaticVariables.StringLexicon.Keys.Contains(t.Value as string))
                    continue;
                t.Value = "\"" + GSCStaticVariables.StringLexicon[t.Value as string] + "\"";
            }
            return true;
        }

        internal int CountStringTokens(List<Token> tokens, string match)
        {
            int count = 0;
            foreach (Token t in tokens)
            {
                if ((string)t.Value == match)
                    count++;
            }
            return count;
        }

        /// <summary>
        /// Replace references to all functions
        /// </summary>
        /// <returns></returns>
        internal bool IAssignFunctionRefs()
        {
            
            GSCStaticVariables.FunctionExcludes.AddRange(functionwhitelist);
            foreach (string s in FunctionRefs.Keys) //Collect keys
            {
                if (s.ToLower() == "init")
                    continue;
                

                int count = CountToken(FunctionRefs[s.ToLower()], s.ToLower());
                count++;
                if (GSCStaticVariables.FunctionRefLexicon.ContainsKey(s.ToLower()))
                {
                    if(!GlobalUses.ContainsKey(GSCStaticVariables.FunctionRefLexicon[s.ToLower()]))
                        GlobalUses[GSCStaticVariables.FunctionRefLexicon[s.ToLower()]] = 0;
                    GlobalUses[GSCStaticVariables.FunctionRefLexicon[s.ToLower()]] += count;
                    GSCStaticVariables.FunctionExcludes.Add(GSCStaticVariables.FunctionRefLexicon[s.ToLower()]);
                    ReplacedStrings.Add(GSCStaticVariables.FunctionRefLexicon[s.ToLower()]);
                    continue;
                }
                if(!T6FunctionResolver.ResolveFunctionFromLib(s.ToLower(), 0, new List<string>(), This.ScriptName).IsError) //TODO: Verify params correctly
                {
                    GSCStaticVariables.FunctionRefLexicon[s.ToLower()] = s.ToLower();
                    if (!GlobalUses.ContainsKey(GSCStaticVariables.FunctionRefLexicon[s.ToLower()]))
                        GlobalUses[GSCStaticVariables.FunctionRefLexicon[s.ToLower()]] = 0;
                    GlobalUses[GSCStaticVariables.FunctionRefLexicon[s.ToLower()]] += count;
                    GSCStaticVariables.FunctionExcludes.Add(GSCStaticVariables.FunctionRefLexicon[s.ToLower()]);
                    ReplacedStrings.Add(GSCStaticVariables.FunctionRefLexicon[s.ToLower()]);
                    continue;
                }
                //FunctionRefLexicon
                string key = null;
                foreach (string str in GlobalUses.Keys)
                {
                    if (GSCStaticVariables.FunctionExcludes.Contains(str))
                        continue;
                    if (GlobalUses[str] + count <= STRING_REF_MAX)
                    {
                        key = str;
                        break;
                    }
                }
                int i = GlobalUses.Count;
                if (key == null)
                {
                    GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = count;
                    key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                    while (GSCStaticVariables.FunctionExcludes.Contains(key))
                    {
                        i++;
                        GlobalUses["a" + chars[i / chars.Length] + chars[i % chars.Length]] = count;
                        key = "a" + chars[i / chars.Length] + chars[i % chars.Length];
                    }
                }
                else
                    GlobalUses[key] += count;
                GSCStaticVariables.FunctionExcludes.Add(key);
                ReplacedStrings.Add(key);
                GSCStaticVariables.FunctionRefLexicon[s.ToLower()] = key;
            }

          
            return true;
        }

        /// <summary>
        /// Replace function references
        /// </summary>
        /// <returns></returns>
        internal bool IReplaceFunctionRefs()
        {
            //ERROR_MSG += "\n--IReplaceFunctionRefs--\n";
            foreach (string s in FunctionRefs.Keys) //Replace function references
            {
                foreach (Token t in FunctionRefs[s])
                {
                    if (t.Text.ToLower().ToLower() == "init")
                        continue;
                    //ERROR_MSG += "\n" + t.Value.ToString() + " ->> " + GSCStaticVariables.FunctionRefLexicon[t.Text.ToLower()];
                    t.Value = GSCStaticVariables.FunctionRefLexicon[t.Text.ToLower()];
                    
                }
            }
            
            foreach (var function in Functions)
            {
                if (function.ChildNodes[0].Token.Text.ToLower() == "init")
                    continue;

                GSCStaticVariables.Available_keys[GSCStaticVariables.FunctionRefLexicon[function.ChildNodes[0].Token.Text.ToLower()]] = GSCStaticVariables.Available_keys[function.ChildNodes[0].Token.Text.ToLower()]; //Redefine the pass to point the the right spot
                function.ChildNodes[0].Token.Value = GSCStaticVariables.FunctionRefLexicon[function.ChildNodes[0].Token.Text.ToLower()];
                //ERROR_MSG += "\nFUNCTION: " + function.ChildNodes[0].Token.Value.ToString();
            }
            
            return true;
        }

        private int CountToken(List<Token> tokens, string t)
        {
            int count = 0;
            foreach (Token ts in tokens)
            {
                if (ts.Text.ToLower() == t.ToLower())
                    count++;
            }
            return count;
        }

        internal bool IReconstructGSC()
        {
            List<string> uniqueids = new List<string>();
            foreach (var tok in IdentifierTokens) //count string refs
            {
                if (tok.Term == GSC2Grammar.numberLiteral)
                    continue;
                string val = tok.FindToken().ValueString.ToLower();
                if (tok.Term == GSC2Grammar.stringLiteral)
                {
                    val = tok.FindToken().ValueString;
                }
                if (uniqueids.Contains(val))
                    continue;
                uniqueids.Add(tok.FindToken().ValueString.ToLower());
            }
            string FinalText = "";
            FinalText += ReconstructHeader();
            FinalText += ReconstructBody();
            /*
            string tpath = path.Substring(0, path.LastIndexOf(".gsc")) + ".txt";
            File.WriteAllText(tpath, FinalText);
            */
            Data = FinalText;
            return true;
        }

        internal string ReconstructHeader()
        {
            string toReturn = "";
            //includes + usingAnimTree + defines + functions
            foreach (var node in Includes)
            {
                toReturn += "#include " + node.ChildNodes[0].Token.Text + ";\n";
            }
            toReturn += "\n";
            foreach (var node in AnimTrees)
            {
                toReturn += "#using_animtree(" + node.ChildNodes[0].Token.Text + ");\n";
            }
            return toReturn;
        }

        internal string ReconstructBody()
        {
            string toReturn ="\n";
            foreach(var node in Functions)
            {
                toReturn += HandleNode(node) + "\n";
            }
            return toReturn;
        }

        internal string HandleNode(ParseTreeNode node, int indent = 0)
        {
            string toreturn = "";
            /*
            * 
            * 
            * 
            * 
            */
            //ERROR_MSG += "\nNODE_ENTRY: " + node.ToString();
            switch (node.ToString())
            {
                case "arrayshorthand":
                    {
                        string exprresult = HandleNode(node.ChildNodes[1], indent);
                        toreturn += exprresult + " = [];\n";
                        int count = 0;
                        foreach(var parameter in node.ChildNodes[3].ChildNodes)
                        {
                            toreturn += exprresult + " [" + count + "] = " + HandleNode(parameter) + ";\n";
                            count++;
                        }
                        break;
                    }
                case "function":
                    {
                        toreturn += node.ChildNodes[0].Token.Value;
                        if (node.ChildNodes[1].ChildNodes[0].ToString() == "parameters")
                        {
                            toreturn += "(";
                            foreach (var nod in node.ChildNodes[1].ChildNodes[0].ChildNodes)
                            {
                                toreturn += nod.ChildNodes[0].Token.Value + ",";
                            }
                            toreturn = toreturn.Substring(0, toreturn.Length - 1) + ")\n{\n";
                        }
                        else
                        {
                            toreturn += "()\n{\n";
                        }
                        if (node.ChildNodes[2].ChildNodes.Count > 0)
                        {
                            foreach (var nod in node.ChildNodes[2].ChildNodes[0].ChildNodes[0].ChildNodes)
                            {
                                toreturn += HandleNode(nod, 1);
                            }
                        }
                        toreturn += "}\n";
                        break;
                    }
                case "protectExpr":
                case "protectBlock":
                    {
                        toreturn += "$(" + node.ChildNodes[0].ChildNodes[0].FindTokenAndGetText() + ")\n{\n" + (node.ChildNodes.Count > 1 ? HandleNode(node.ChildNodes[1], indent + 1) : "") + "\n}\n";
                        break;
                    }
                case "libraryReference":
                    {
                        string outstr;
                        string errormsg;
                        if (AddLibReference(node, out outstr, out errormsg))
                            toreturn += outstr;
                        else
                        {
                            ERROR_MSG += "\n" + errormsg + "\n";
                            EXIT_CODE = 2;
                        }
                        break;
                    }
                case "labelTerminal":
                    {
                        toreturn += node.ChildNodes[0].FindTokenAndGetText() + ": \n";

                        break;
                    }
                case "gotoTerminal":
                    {
                        toreturn += "goto " + node.ChildNodes[1].FindTokenAndGetText() + ";\n";
                        break;
                    }
                case "animTree":
                    {
                        toreturn += "#animTree";
                        break;
                    }
                case "getAnimation":
                    {
                        toreturn += "%" + node.ChildNodes[1].Token.Value;
                        break;
                    }
                case "conditionalStatement":
                    {
                        toreturn += "(" + HandleNode(node.ChildNodes[0]) + ") ? (" + HandleNode(node.ChildNodes[2]) + ") : (" + HandleNode(node.ChildNodes[4]) + ")";
                        break;
                    }
                case "hashedString":
                    {
                        toreturn += "#" + node.ChildNodes[1].Token.Text + "";
                        break;
                    }
                case "getFunction"://ToTerm("::") + expr | gscForFunction + expr;
                    {
                        if (node.ChildNodes.Count == 1)
                        {
                            toreturn += "::" + HandleNode(node.ChildNodes[0]);
                        }
                        else
                        {
                            toreturn += HandleNode(node.ChildNodes[0]) + HandleNode(node.ChildNodes[1]);
                        }
                        break;
                    }
                case "gscForFunction":
                    {
                        toreturn += node.ChildNodes[0].Token.Text + "::";
                        break;
                    }
                case "isString":
                    {
                        toreturn += "&" + node.ChildNodes[1].Token.Text + "";
                        break;
                    }
                case "directAccess":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + "." + node.ChildNodes[1].Token.Value;
                        break;
                    }
                case "relationalExpression":
                case "expression":
                    {
                        toreturn += "(" + HandleNode(node.ChildNodes[0]) + ") " + node.ChildNodes[1].FindTokenAndGetText() + " (" + HandleNode(node.ChildNodes[2]) + ") ";
                        break;
                    }
                case "boolNot":
                    {
                        toreturn += "!" + HandleNode(node.ChildNodes[1]);
                        break;
                    }
                case "size":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + ".size";
                        break;
                    }
                case "expr":
                    {
                        //ERROR_MSG += "\nEXPR.Count[" + node.ChildNodes.Count + "] EXPR.Node.0[" + node.ChildNodes[0].Term.Name + "] EXPR.Node.IDMatch[" + node.ChildNodes[0].Term.Name + " =? " + GSC2Grammar.identifier.Name + "];";
                        if (node.ChildNodes[0].Term.Name == GSC2Grammar.identifier.Name)
                        {
                            toreturn += node.ChildNodes[0].Token.Value;
                            //ERROR_MSG += "\nEXPR.IDENTIFIER: " + node.ChildNodes[0].FindTokenAndGetText();
                        }
                        else if (node.ChildNodes[0].Term.Name == GSC2Grammar.stringLiteral.Name)
                        {
                            if (StringLiterals.Contains(node.ChildNodes[0].Token))
                            {
                                toreturn += node.ChildNodes[0].Token.Value;
                                //ERROR_MSG += "\nEXPR.STRINGLITERAL: " + node.ChildNodes[0].Token.Value.ToString();
                            }
                            else
                            {
                                toreturn += node.ChildNodes[0].Token.Text;
                                //ERROR_MSG += "\nEXPR.STRINGLITERAL: " + node.ChildNodes[0].Token.Text;
                            }
                                
                        }
                        else if (node.ChildNodes[0].Term.Name == GSC2Grammar.numberLiteral.Name)
                        {
                            toreturn += node.ChildNodes[0].FindTokenAndGetText();
                            //ERROR_MSG += "\nEXPR.NUMBERLITERAL: " + node.ChildNodes[0].FindTokenAndGetText();
                        }
                        else
                        {
                            toreturn += HandleNode(node.ChildNodes[0]);
                        }
                        break;
                    }
                case "array":
                    {
                        if (node.ChildNodes.Count < 2)
                        {
                            toreturn += "[]";
                        }
                        else
                        {
                            toreturn += HandleNode(node.ChildNodes[0]) + "[ " + HandleNode(node.ChildNodes[1]) + " ]";
                        }
                        break;
                    }
                case "vector":
                    {
                        toreturn += "(" + HandleNode(node.ChildNodes[0]) + ", " + HandleNode(node.ChildNodes[1]) + ", " + HandleNode(node.ChildNodes[2]) + ")";
                        break;
                    }
                case "wait":
                    {
                        toreturn += "wait " + HandleNode(node.ChildNodes[1]) + ";\n";
                        break;
                    }
                case "jumpStatement":
                    {
                        toreturn += node.ChildNodes[0].Token.Text + ";";
                        break;
                    }
                case "waitTillFrameEnd":
                    {
                        toreturn += "waittillframeend;\n";
                        break;
                    }
                case "return":
                    {
                        toreturn += GetTabs(indent) + "return ";
                        if (node.ChildNodes.Count > 1)
                        {
                            toreturn += HandleNode(node.ChildNodes[1]);
                        }
                        toreturn += ";\n";
                        break;
                    }
                case "declaration":
                    {
                        for (int i = 0; i < indent; i++)
                        {
                            toreturn += "\t";
                        }

                        toreturn += HandleNode(node.ChildNodes[0], indent);
                        break;
                    }
                case "switchStatement":
                    {
                        toreturn += "switch(" + HandleNode(node.ChildNodes[1]) + ")\n";
                        toreturn += GetTabs(indent) + "{\n";
                        toreturn += HandleNode(node.ChildNodes[2], indent + 1);
                        toreturn += GetTabs(indent) + "}\n";
                        break;
                    }
                case "switchContent":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + "\n" + GetTabs(indent);
                        toreturn += HandleNode(node.ChildNodes[1]);
                        break;
                    }
                case "switchLabel":
                    {
                        if (node.ChildNodes[0].FindTokenAndGetText().ToLower().Contains("default"))
                            toreturn += "default:";
                        else
                            toreturn += "case " + HandleNode(node.ChildNodes[1]) + " :";
                        break;
                    }
                case "setVariableField":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + node.ChildNodes[1].FindTokenAndGetText(); //Might be null. I dunno
                        if (node.ChildNodes.Count > 2)
                            toreturn += HandleNode(node.ChildNodes[2]);
                        toreturn += ";\n";
                        break;
                    }
                case "developerScript":
                    {
                        toreturn += "/#" + HandleNode(node.ChildNodes[1], indent) + "#/";
                        break;
                    }
                case "foreachStatement":
                    {
                        toreturn += "foreach(";
                        toreturn += node.ChildNodes[1].Token.Value + " in ";
                        toreturn += HandleNode(node.ChildNodes[3]) + ")\n";
                        toreturn += GetTabs(indent) + "{\n";
                        if (node.ChildNodes[4].ChildNodes[0].ToString() == "declaration")
                        {
                            toreturn += HandleNode(node.ChildNodes[4].ChildNodes[0], indent + 1);
                        }
                        else
                        {
                            foreach (var nod in node.ChildNodes[4].ChildNodes[0].ChildNodes)
                            {
                                toreturn += HandleNode(nod, indent + 1);
                            }
                        }
                        toreturn += GetTabs(indent) + "}\n";
                        break;
                    }
                case "ifStatement":
                    {
                        toreturn += "if(";
                        toreturn += HandleNode(node.ChildNodes[1]) + ")\n";
                        toreturn += GetTabs(indent) + "{\n";
                        if (node.ChildNodes[2].ChildNodes[0].ToString() == "declaration")
                        {
                            toreturn += HandleNode(node.ChildNodes[2].ChildNodes[0], indent + 1);
                        }
                        else
                        {
                            foreach (var nod in node.ChildNodes[2].ChildNodes[0].ChildNodes)
                            {
                                toreturn += HandleNode(nod, indent + 1);
                            }
                        }
                        toreturn += GetTabs(indent) + "}\n";
                        if (node.ChildNodes.Count > 3)
                        {
                            toreturn += GetTabs(indent) + "else\n" + GetTabs(indent) + "{\n";
                            if (node.ChildNodes[3].ChildNodes[1].ChildNodes[0].ToString() == "declaration")
                            {
                                toreturn += HandleNode(node.ChildNodes[3].ChildNodes[1].ChildNodes[0], indent + 1);
                            }
                            else
                            {
                                foreach (var nod in node.ChildNodes[3].ChildNodes[1].ChildNodes[0].ChildNodes)
                                {
                                    toreturn += HandleNode(nod, indent + 1);
                                }
                            }
                            toreturn += GetTabs(indent) + "}\n";
                        }
                        break;
                    }
                case "whileStatement":
                    {
                        toreturn += "while(";
                        toreturn += HandleNode(node.ChildNodes[1]) + ")\n";
                        toreturn += GetTabs(indent) + "{\n";
                        if (node.ChildNodes[2].ChildNodes[0].ToString() == "declaration")
                        {
                            toreturn += HandleNode(node.ChildNodes[2].ChildNodes[0], indent + 1);
                        }
                        else
                        {
                            foreach (var nod in node.ChildNodes[2].ChildNodes[0].ChildNodes)
                            {
                                toreturn += HandleNode(nod, indent + 1);
                            }
                        }
                        toreturn += GetTabs(indent) + "}\n";
                        break;
                    }
                case "forStatement":
                    {
                        toreturn += "for(";
                        if (node.ChildNodes[1].ChildNodes.Count > 0)
                        {
                            switch (node.ChildNodes[1].ChildNodes[0].ToString())
                            {
                                case "setVariableField":
                                    {
                                        toreturn += HandleNode(node.ChildNodes[1].ChildNodes[0]).Replace("\n", "");
                                        if (node.ChildNodes[1].ChildNodes.Count > 1)
                                        {
                                            switch (node.ChildNodes[1].ChildNodes[1].ToString())
                                            {
                                                case "booleanExpression":
                                                    {
                                                        toreturn += HandleNode(node.ChildNodes[1].ChildNodes[1]).Replace("\n", "") + ";";
                                                        if (node.ChildNodes[1].ChildNodes.Count > 2)
                                                        {
                                                            toreturn += HandleNode(node.ChildNodes[1].ChildNodes[2]);
                                                        }
                                                        break;
                                                    }
                                                case "forIterate":
                                                    {
                                                        toreturn += ";";
                                                        toreturn += HandleNode(node.ChildNodes[1].ChildNodes[1]);
                                                        break;
                                                    }
                                            }
                                        }
                                        else
                                        {
                                            toreturn += ";";
                                        }
                                        break;
                                    }
                                case "booleanExpression":
                                    {
                                        toreturn += ";";
                                        toreturn += HandleNode(node.ChildNodes[1].ChildNodes[0]).Replace("\n", "") + ";";
                                        if (node.ChildNodes[1].ChildNodes.Count > 1)
                                        {
                                            toreturn += HandleNode(node.ChildNodes[1].ChildNodes[1]);
                                        }
                                        break;
                                    }
                                case "forIterate":
                                    {
                                        toreturn += ";;";
                                        toreturn += HandleNode(node.ChildNodes[1].ChildNodes[0]);
                                        break;
                                    }
                            }
                        }
                        else
                        {
                            toreturn += ";;";
                        }
                        toreturn += ")\n";
                        toreturn += GetTabs(indent) + "{\n";
                        foreach (var nod in node.ChildNodes[2].ChildNodes)
                        {
                            toreturn += HandleNode(nod, indent + 1);
                        }
                        toreturn += GetTabs(indent) + "}\n";
                        break;
                    }
                case "forIterate":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + node.ChildNodes[1].FindTokenAndGetText();
                        if (node.ChildNodes.Count > 2)
                            toreturn += HandleNode(node.ChildNodes[2], indent);
                        break;
                    }
                case "boolParen": //We have to ignore because OG compiler cant handle that expression :(
                case "booleanExpression":
                    {
                        if (node.ChildNodes.Count == 1)
                        {
                            toreturn += HandleNode(node.ChildNodes[0], indent);
                        }
                        else
                        {
                            toreturn += HandleNode(node.ChildNodes[0], indent) + " " + node.ChildNodes[1].ChildNodes[0].FindTokenAndGetText() + " " + HandleNode(node.ChildNodes[2], indent);
                        }
                        break;
                    }
                case "simpleCall":
                    {
                        toreturn += HandleNode(node.ChildNodes[0], indent) + ";\n";
                        break;
                    }
                case "baseCall": //gscForFunction + identifier + parenParameters | identifier + parenParameters
                    {
                        if (node.ChildNodes.Count > 2)
                        {
                            toreturn += node.ChildNodes[0].ChildNodes[0].Token.Value + "::" + node.ChildNodes[1].Token.Value + HandleNode(node.ChildNodes[2], indent);
                        }
                        else
                        {
                            toreturn += node.ChildNodes[0].Token.Value + HandleNode(node.ChildNodes[1], indent);
                        }
                        break;
                    }
                case "scriptMethodThreadCallPointer":
                case "scriptMethodThreadCall":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + " thread " + HandleNode(node.ChildNodes[2]);
                        break;
                    }
                case "scriptThreadCallPointer":
                case "scriptThreadCall":
                    {
                        toreturn += "thread " + HandleNode(node.ChildNodes[1]);
                        break;
                    }
                case "scriptMethodCallPointer":
                case "scriptMethodCall":
                    {
                        toreturn += HandleNode(node.ChildNodes[0]) + " " + HandleNode(node.ChildNodes[1]);
                        break;
                    }
                case "baseCallPointer":
                    {
                        toreturn += "[[ " + HandleNode(node.ChildNodes[0]) + " ]]" + HandleNode(node.ChildNodes[1]);
                        break;
                    }
                case "parenParameters":
                    {
                        if (node.ChildNodes[0].ToString() == "parameters")
                        {
                            foreach (var nod in node.ChildNodes[0].ChildNodes)
                            {
                                toreturn += HandleNode(nod) + ",";
                            }
                            toreturn = "(" + toreturn.Substring(0, toreturn.Length - 1) + ")";
                        }
                        else
                        {
                            toreturn += "()";
                        }
                        break;
                    }
                case "StringAway":
                case "ParserNotification":
                    break;
                default:
                    foreach (var nod in node.ChildNodes)
                    {
                        toreturn += HandleNode(nod, indent);
                    }
                    break;
            }
            return toreturn;
        }

        private static string GetTabs(int indent)
        {
            string toreturn = "";
            for (int i = 0; i < indent; i++)
                toreturn += "\t";
            return toreturn;
        }

        internal bool ICompile()
        {
            bool IsFatal = false;
            List<GSXCompilerLib.Compiler.CompilerError> errors = new List<Compiler.CompilerError>();
            if (!This.PC)
            {
                errors.AddRange(new GameScriptCompiler_v3.ExternalEntry().Compile(Data, GSCStaticVariables.Available_keys, This, OutputPath, CompilerParams));
            }
            else
            {
                errors.AddRange(new GameScriptCompiler_v3_pc.ExternalEntry().Compile(Data, GSCStaticVariables.Available_keys, This, OutputPath, CompilerParams));
            }
            foreach(Compiler.CompilerError error in errors)
            {
                if (error.FatalError)
                {
                    ERROR_MSG += "\n(FATAL ERROR)";
                    IsFatal = true;
                }
                else
                {
                    ERROR_MSG += "\n(WARNING)";
                }
                /*
                if(error.Node != null && error.Node.FindToken() != null)
                {
                    ERROR_MSG += " at line " + error.Node.FindToken().Location.Line;
                }
                */
                ERROR_MSG += ": ";
                ERROR_MSG += error.Msg;
            }

            if (IsFatal)
            {
                EXIT_CODE = 2;
                return false;
            }

            return true;
        }

        [Obsolete("Symbolization is not currently supported", false)]
        internal bool IObfuscate()
        {
            return true;
            if (!This.UseSymbols)
                return true;
            foreach (var kvp in whitelist)
            {
                while (ReplacedStrings.Contains(kvp.Value.ToLower()))
                {
                    ReplacedStrings.Remove(kvp.Value.ToLower());
                }
            }
            foreach (string s in functionwhitelist)
            {
                while (ReplacedStrings.Contains(s.ToLower()))
                {
                    ReplacedStrings.Remove(s.ToLower());
                }
            }
            List<byte> bytes = File.ReadAllBytes(OutputPath).ToList();
            int index = 0x40;
            index = ReadStringFromByteArray(bytes.ToArray(), index); //Skip name
            int numofincludes = BitConverter.ToInt16(BitConverter.GetBytes(bytes[0x3C]).ToArray<byte>(), 0);
            int EndOfStrings = -1;
            if (This.PC)
            {
                EndOfStrings = BitConverter.ToInt32(bytes.GetRange(0xC, sizeof(int)).ToArray<byte>(), 0);
            }
            else
            {
                EndOfStrings = BitConverter.ToInt32(bytes.GetRange(0xC, sizeof(int)).Reverse<byte>().ToArray<byte>(), 0);
            }
            for (int i = 0; i < numofincludes; i++)
            {
                index = ReadStringFromByteArray(bytes.ToArray(), index); //Skip includes
            }
            while (index < EndOfStrings)
            {
                int ogindex = index;
                index = ReadStringFromByteArray(bytes.ToArray(), index);
                if (StringFromBytes.ToLower() == "serioushd") //Leave the watermark :P
                    continue;
                if (ReplacedStrings.Contains(StringFromBytes))
                {
                    for (int i = 0; i < StringFromBytes.Length; i++)
                    {
                        bytes[ogindex + i] = (byte)(chars.IndexOf((char)bytes[ogindex + i]) + 1);
                    }
                }
            }
            File.WriteAllBytes(OutputPath, bytes.ToArray());
            return true;
        }

        /// <summary>
        /// Read a string from the given byte array and set the 'StringFromBytes' global to result
        /// </summary>
        /// <param name="array">Byte array to read from</param>
        /// <param name="index">Index starting location</param>
        /// <returns>Final Index Position after NULL</returns>
        internal static int ReadStringFromByteArray(byte[] array, int index)
        {
            string toReturn = "";
            if (index < 0)
            {
                throw new Exception();
            }
            for (; index < array.Length; index++)
            {
                if (array[index] == 0x00)
                    break;
                toReturn += (char)array[index];
            }
            StringFromBytes = toReturn;
            return index + 1;
        }

        internal static byte CountParams(ParseTreeNode node)
        {
            try
            {
                return (byte)node.ChildNodes[0].ChildNodes.Count; //ParenParameters.Parameters.Count
            }
            catch
            {
                return 0;
            }
        }

        internal List<GSXLibReference> LibReferences = new List<GSXLibReference>();

        internal bool AddLibReference(ParseTreeNode node, out string SourceText, out string ErrorMessage)
        {
            GSXLibReference LibReference;
            bool ShouldAddReference = ResolveLibReference(node, this, out LibReference, out ErrorMessage);
            SourceText = GetRefText(LibReference);
            if (ShouldAddReference)
            {
                bool unique = true;
                foreach(var reference in LibReferences)
                {
                    if (reference.Equals(LibReference))
                        unique = false;
                }
                if(unique)
                {
                    LibReferences.Add(LibReference);
                    return LibReference.Type == RefType.Function ? RecursiveLibRefs((LibReference.LibItem as GSXLibraries.GSXFunction).Function.ChildNodes[2], out ErrorMessage) : true;
                }
            }
            return ShouldAddReference;
        }

        internal string MemSave = ""; //Saves tons and tons of strings from initing for no reason
        internal bool RecursiveLibRefs(ParseTreeNode node, out string ErrorMessage)
        {
            ErrorMessage = "";
            bool result = true;
            if (node.Term.Name == "libraryReference")
            {
                string ErrMessage;
                result = AddLibReference(node, out MemSave, out ErrMessage);
                if (!result)
                    ErrorMessage += "\n" + ErrMessage + "\n";
            }
            foreach(ParseTreeNode n in node.ChildNodes)
            {
                string errMsg = "";
                result = result && RecursiveLibRefs(n, out errMsg);
                ErrorMessage += errMsg;
            }
            return result;
        }

    }
}
