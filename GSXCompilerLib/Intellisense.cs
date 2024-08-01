using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;
using System.Drawing;
using System.Reflection;
using System.IO;

namespace GSXCompilerLib
{
    /// <summary>
    /// Intellisense operations for GSX Studio
    /// </summary>
    public sealed class Intellisense
    {
        /// <summary>
        /// Error Icon
        /// </summary>
        public static Image ERRORICON = Image.FromStream(Assembly.GetExecutingAssembly().GetManifestResourceStream("GSXCompilerLib.StatusCriticalError_16x.png"));
        /// <summary>
        /// Active error icon
        /// </summary>
        public static Image ACTIVEERRORICON = Image.FromStream(Assembly.GetExecutingAssembly().GetManifestResourceStream("GSXCompilerLib.ActiveErrorSquiggle_16x.png"));

        /// <summary>
        /// Creates a GSX Parser
        /// </summary>
        /// <returns></returns>
        public static Parser GetGSXParser()
        {
            Parser p = new Irony.Parsing.Parser(new GSXGrammar());
            return p;
        }

        /// <summary>
        /// Returns a verbose error list from the parse tree
        /// </summary>
        /// <param name="tree"></param>
        /// <returns></returns>
        public static ParserErrorData[] VerboseError(ParseTree tree)
        {
            ParserErrorData[] errors = new ParserErrorData[tree.ParserMessages.Count];
            for(int i = 0; i < errors.Length; i++)
            {
                ParserErrorData errormsg = new ParserErrorData();
                errormsg.Icon = ERRORICON;
                errormsg.ParserState = tree.ParserMessages[i].ParserState;
                errormsg.Message = tree.ParserMessages[i];
                errormsg.FileName = tree.FileName;
                errors[i] = errormsg;
            }
            return errors;
        }

        /// <summary>
        /// Info about a script
        /// </summary>
        public sealed class ScriptInfo
        {
            /// <summary>
            /// The type of typestrict mode
            /// </summary>
            public int TypestrictState;
            /// <summary>
            /// The inline mode
            /// </summary>
            public int InlineState;
            /// <summary>
            /// Script IsDebug flag
            /// </summary>
            public bool Debug;
        }

        /// <summary>
        /// Create errors in the grammar of the file (non-syntax)
        /// </summary>
        /// <param name="tree"></param>
        /// <param name="info"></param>
        /// <returns></returns>
        public static ParserGrammarErrorData[] VerboseGrammarErrors(ParseTree tree, ScriptInfo info)
        {
            List<ParserGrammarErrorData> errors = new List<ParserGrammarErrorData>();
            if (tree.ParserMessages.Count > 0)
                return errors.ToArray();
            //Add initializing errors
            //Add libreference & includereference errors
            //Add LoopWait errors
            //Add return logic checks
            //Add return and assign to thread logic
            if (errors.Count > 0)
                return errors.ToArray();
            errors.AddRange(TypingErrors(tree, info.TypestrictState));
            return errors.ToArray();
        }

        //TODO verify struct declarations declare TYPE
        internal static ParserGrammarErrorData[] TypingErrors(ParseTree tree, int TypestrictState)
        {
            List<ParserGrammarErrorData> errors = new List<ParserGrammarErrorData>();
            
            var declarations = tree.Root.ChildNodes[0].ChildNodes;
            foreach (var declaration in declarations)
            {
                if(declaration.ChildNodes[0].Term.Name == "function")
                {
                    var function = declaration.ChildNodes[0];
                    bool hasTypeSpecifier = false;
                    foreach(var fproperty in function.ChildNodes[0].ChildNodes)
                    {
                        if(fproperty.ChildNodes[0].Term.Name == "ptypestrict")
                        {
                            hasTypeSpecifier = true;
                            break;
                        }
                    }
                    if(!hasTypeSpecifier && TypestrictState > 1)
                    {
                        ParserGrammarErrorData error = new ParserGrammarErrorData();
                        error.FileName = tree.FileName;
                        error.Icon = ACTIVEERRORICON;
                        error.Code = "GS1";
                        error.TokenPosition = declaration.ChildNodes[0].FindToken().Location.Position;
                        error.TokenLine = declaration.ChildNodes[0].FindToken().Location.Line;
                        errors.Add(error);
                        continue;
                    }
                    if(hasTypeSpecifier && TypestrictState > 2)//Check params
                    {
                        foreach(var dparamsfragment in function.ChildNodes[2].ChildNodes[0].ChildNodes)
                        {
                            if(dparamsfragment.ChildNodes[0].ChildNodes[0].ChildNodes[0].ChildNodes.Count < 1)
                            {
                                ParserGrammarErrorData error = new ParserGrammarErrorData();
                                error.FileName = tree.FileName;
                                error.Icon = ACTIVEERRORICON;
                                error.Code = "GS2";
                                error.TokenPosition = dparamsfragment.FindToken().Location.Position;
                                error.TokenLine = dparamsfragment.FindToken().Location.Line;
                                errors.Add(error);
                            }
                        }
                    }
                    foreach(var statement in function.ChildNodes[3].ChildNodes[0].ChildNodes) //Check returns
                    {
                        errors.AddRange(GetStatementTypingErrors(statement, function, tree, TypestrictState, false));
                    }
                }
            }
            return errors.ToArray();
        }

        private static List<ParserGrammarErrorData> GetStatementTypingErrors(ParseTreeNode statement, ParseTreeNode function, ParseTree tree, int TypeStrictState, bool typedcontext)
        {
            List<ParserGrammarErrorData> errors = new List<ParserGrammarErrorData>();
            if (TypeStrictState > 2)
                typedcontext = true;
            switch (statement.ChildNodes[0].Term.Name)
            {
                case "command":
                    if(statement.ChildNodes[0].ChildNodes[0].Term.Name == "returncommand")
                    {
                        var command = statement.ChildNodes[0].ChildNodes[0];
                        if(TypeStrictState > 1 && command.ChildNodes[1].ChildNodes[0].ChildNodes.Count < 1 && FindFunctionType(function) != "void")
                        {
                            ParserGrammarErrorData error = new ParserGrammarErrorData();
                            error.FileName = tree.FileName;
                            error.Icon = ACTIVEERRORICON;
                            error.Code = "GS3";
                            error.TokenPosition = command.FindToken().Location.Position;
                            error.TokenLine = command.FindToken().Location.Line;
                            errors.Add(error);
                            return errors;
                        }
                        if(command.ChildNodes[1].ChildNodes[0].ChildNodes.Count > 0 && !TypeMatches(FindFunctionType(function), DeriveVariableStateFromExpression(command.ChildNodes[1].ChildNodes[0].ChildNodes[0], function)))
                        {
                            ParserGrammarErrorData error = new ParserGrammarErrorData();
                            error.FileName = tree.FileName;
                            error.Icon = ACTIVEERRORICON;
                            error.Code = "GS4";
                            error.TokenPosition = command.ChildNodes[1].ChildNodes[0].ChildNodes[0].FindToken().Location.Position;
                            error.TokenLine = command.ChildNodes[1].ChildNodes[0].ChildNodes[0].FindToken().Location.Line;
                            errors.Add(error);
                        }
                        if (errors.Count > 0)
                            return errors;
                    }
                    break;
            }
            return errors;
        }

        private static string DeriveVariableStateFromExpression(ParseTreeNode expression, ParseTreeNode function)
        {
           if(expression.ChildNodes[0].Term.Name == "cast")
            {
                return (TypeFromNode(expression.ChildNodes[0].ChildNodes[0].ChildNodes[0]));
            }
            if (expression.ChildNodes[0].Term.Name == "identifier")
                return LocationLocalType(expression.ChildNodes[0].FindTokenAndGetText(), function);
            if (expression.ChildNodes[0].Term.Name == "number")
            {
                if (expression.ChildNodes[0].FindTokenAndGetText().Contains("."))
                    return "float";
                return "int";
            }
            return "void";
        }

        private static string LocationLocalType(string identifier, ParseTreeNode function)
        {
           
            foreach(var node in function.ChildNodes[2].ChildNodes[0].ChildNodes)
            {
                if(node.ChildNodes[0].ChildNodes[0].ChildNodes[1].FindTokenAndGetText() == identifier)
                {
                    if (node.ChildNodes[0].ChildNodes[0].ChildNodes[0].ChildNodes.Count < 1)
                        return "void";
                    return FindFunctionType(node.ChildNodes[0].ChildNodes[0].ChildNodes[0].ChildNodes[0].ChildNodes[0]);
                }
            }
            List<ParseTreeNode> nodes = GetAllInitDefinitions(function.ChildNodes[3].ChildNodes[0]);
            foreach (var node in nodes)
            {
                if(node.ChildNodes[0].ChildNodes[0].Term.Name == "cast" && node.ChildNodes[0].ChildNodes[0].ChildNodes[1].ChildNodes[0].Term.Name == "identifier" && node.ChildNodes[0].ChildNodes[0].ChildNodes[1].ChildNodes[0].FindTokenAndGetText() == identifier)
                {
                    return FindFunctionType(node.ChildNodes[0].ChildNodes[0].ChildNodes[0].ChildNodes[0]);
                }
            }
            return "void";
        }

        private static List<ParseTreeNode> GetAllInitDefinitions(ParseTreeNode node)
        {
            List<ParseTreeNode> InitDefs = new List<ParseTreeNode>();
            if (node.Term.Name == "setvariablefield")
                InitDefs.Add(node);
            foreach (var xnode in node.ChildNodes)
            {
                InitDefs.AddRange(GetAllInitDefinitions(xnode));
            }
            return InitDefs;
        }

        private static bool TypeMatches(string major, string minor)
        {
            if (major == "void")
                return true;
            if (major == "number")
                return minor == "number" || minor == "int" || minor == "float";
            if (major == "float")
                return minor == "float" | minor == "int";
            return minor == major;
        }

        private static string FindFunctionType(ParseTreeNode function)
        {
            foreach (var property in function.ChildNodes[0].ChildNodes)
                if (property.ChildNodes[0].Term.Name == "ptypestrict")
                    return TypeFromNode(property.ChildNodes[0].ChildNodes[2]);
            return "void";
        }

        private static string TypeFromNode(ParseTreeNode node)
        {
            if (node.Term.Name != "gsxtypefragment")
                return "INVALID_TYPE";
            if (node.ChildNodes.Count == 1)
                return node.ChildNodes[0].FindTokenAndGetText();
            return "array:" + TypeFromNode(node.ChildNodes[2]);
        }

        internal static string VerboseMessage(ParserState state, string defaultMessage)
        {
            //TODO
            //S325 - Expected an expression, got -n
            switch(state.Name)
            {
                case "S325":
                    return "Error, expected an expression, but got a number (Did you forget a space between the '-' and the number?)";
            }
            return defaultMessage;
        }

        internal static string VerboseGrammarMessage(string errorcode)
        {
            switch(errorcode)
            {
                case "GS1":
                    return "Your typestrict settings require that all functions have a type specification";
                case "GS2":
                    return "Your typestrict settings require that all declarations have a type specification";
                case "GS3":
                    return "This function has not been declared 'void' and must have a return value";
                case "GS4":
                    return "This variable's type does not match return type of function. (Did you forget to cast?)";
                default:
                    return errorcode + " wasnt defined in the errors grammar. Please report this using the report bug form";
            }
        }

        /// <summary>
        /// Grammar error data
        /// </summary>
        public sealed class ParserGrammarErrorData
        {
            /// <summary>
            /// Icon for the error
            /// </summary>
            public Image Icon;
            /// <summary>
            /// Name of the failing file
            /// </summary>
            public string FileName;
            /// <summary>
            /// Error code
            /// </summary>
            public string Code;
            /// <summary>
            /// Position of the error token in the file
            /// </summary>
            public int TokenPosition;
            /// <summary>
            /// Line of the token in the file
            /// </summary>
            public int TokenLine;

            /// <summary>
            /// return the item at the error position
            /// </summary>
            /// <param name="index"></param>
            /// <returns></returns>
            public object this[int index]
            {
                get
                {
                    switch (index)
                    {
                        case 0:
                            return Icon;
                        case 1:
                            return Code;
                        case 2:
                            return VerboseGrammarMessage(Code);
                        case 3:
                            return FileName;
                        case 4:
                            return TokenLine + 1;
                        default:
                            return "Unkown data requested (Internal Error)";
                    }
                }
            }
            /// <summary>
            /// Object.ToString()
            /// </summary>
            /// <returns></returns>
            public override string ToString()
            {
                return Code;
            }
        }
        /// <summary>
        /// Collect all function nodes from a parsetree
        /// </summary>
        /// <param name="tree"></param>
        /// <returns></returns>
        public static List<ParseTreeNode> CollectFunctionNodes(ParseTree tree)
        {
            List<ParseTreeNode> nodes = new List<ParseTreeNode>();
            int index = tree.Root.ChildNodes.FindIndex(e => e.Term.Name == "functions");
            if (index < 0)
            {
                return nodes;
            }
                
            foreach (var node in tree.Root.ChildNodes[index].ChildNodes)
            {
                if (node.Term.Name == "function")
                    nodes.Add(node);
            }
            return nodes;
        }
        /// <summary>
        /// Find the function header of a parsetreenode
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public static string FindFunctionHeader(ParseTreeNode node)
        {
            if (node.Term.Name != "function")
                return "ERROR_NO_HEADER";
            string toreturn = "";
            toreturn += node.ChildNodes[0].FindTokenAndGetText() + "(";
            foreach(var param in node.ChildNodes[1].ChildNodes[0].ChildNodes)
            {
                toreturn += " " + param.ChildNodes[0].FindTokenAndGetText() + ",";
            }
            if(toreturn.IndexOf(",") > -1)
            {
                toreturn = toreturn.Substring(0, toreturn.Length - 1) + " ";
            }
            toreturn += ")";
            return toreturn;
        }

        /// <summary>
        /// Find the description of a GSX function node 
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public static string FindFunctionDescription(ParseTreeNode node)
        {
            /*
            if (node.Term.Name != "function")
                return "ERROR_NO_DESCRIPTION";
            foreach (var cnode in node.ChildNodes[0].ChildNodes)
            {
                if (cnode.ChildNodes[0].Term.Name == "pdescription")
                    return cnode.ChildNodes[0].ChildNodes[1].FindTokenAndGetText().Replace("\"", "");
            }
            */
            return "User defined function";
        }

        /// <summary>
        /// Error data for a parser
        /// </summary>
        public sealed class ParserErrorData
        {
            /// <summary>
            /// Icon of the error
            /// </summary>
            public Image Icon;
            /// <summary>
            /// Parser state
            /// </summary>
            public ParserState ParserState;
            /// <summary>
            /// Message for the error
            /// </summary>
            public Irony.LogMessage Message;
            /// <summary>
            /// Name of the file that the error occurred in 
            /// </summary>
            public string FileName;

            /// <summary>
            /// Retreive the error at index
            /// </summary>
            /// <param name="index"></param>
            /// <returns></returns>
            public object this[int index]
            {
                get
                {
                    switch(index)
                    {
                        case 0:
                            return Icon;
                        case 1:
                            return ParserState.Name;
                        case 2:
                            return VerboseMessage(ParserState, Message.Message);
                        case 3:
                            return FileName;
                        case 4:
                            return Message.Location.Line;
                        default:
                            return "Unkown data requested (Internal Error)";
                    }
                }
            }


            ///Object.ToString()
            public override string ToString()
            {
                return ParserState.Name;
            }
        }
    }
}
