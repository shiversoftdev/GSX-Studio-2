using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

namespace GSXCompilerLib.GSC
{
    /// <summary>
    /// Internal Compiler for GSC. Use class 'Compiler' for full compilation purposes
    /// </summary>
    public class GSCCompiler
    {
        /// <summary>
        /// Error of the compiler
        /// </summary>
        public string ERROR_MESSAGE
        {
            get
            {
                return Optimizer.ERROR_MSG;
            }

        }
        /// <summary>
        /// Should the compiler skip optimization altogether?
        /// </summary>
        public bool CompileOnly = false;
        /// <summary>
        /// Symbolize the gsc?
        /// </summary>
        public bool UseSymbols = true;
        /// <summary>
        /// Create the debug output file
        /// </summary>
        public bool CreateDebugFile = false;
        /// <summary>
        /// Use default protections for globals
        /// </summary>
        public bool DefaultProtections = true;
        /// <summary>
        /// Is the platform for PC
        /// </summary>
        public bool PC = false;
        /// <summary>
        /// Optimize global variables (children)
        /// </summary>
        public bool OptimizeGlobals = true;

        /// <summary>
        /// Is the script a debug build?
        /// </summary>
        public bool Debug = false;


        /// <summary>
        /// name of the script
        /// </summary>
        /// 
        public string ScriptName;
        /// <summary>
        /// Message 
        /// </summary>
        public string Message;
        private string Path;
        internal GSCOptimizer Optimizer;
        /// <summary>
        /// New internal GSC Compiler
        /// </summary>
        /// <param name="path"></param>
        public GSCCompiler(string path)
        {
            Path = path;
        }
        /// <summary>
        /// Start compiling
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        internal bool Begin(string text)
        {
            object[] param = new object[2];
            param[0] = Message;
            param[1] = Debug;
            Optimizer = new GSCOptimizer(this, text, Path, param);
            bool result = Optimizer.Begin();
            return result;
        }

        internal bool CollectFunctions()
        {
            return Optimizer.ICollectFunctionNames();
        }

        internal bool CollectVTokens()
        {
            return Optimizer.ICollectVariableTokens();
        }

        internal bool ReplaceGlobalsIfAllowed()
        {
            return Optimizer.ReplaceGlobals();
        }

        internal bool CollectLocal()
        {
            return Optimizer.CollectLocal();
        }

        internal bool Finish()
        {
            return Optimizer.Finish();
        }

        internal bool Finish2()
        {
            return Optimizer.NewFinish();
        }

        internal bool Compile(string text)
        {
            object[] param = new object[1];
            param[0] = Message;
            Optimizer = new GSCOptimizer(this, text, Path, param);
            bool result = Optimizer.Main();
            return result;
        }

        internal string GetErrors()
        {
            if (ERROR_MESSAGE == null)
                return "No errors";
            return ERROR_MESSAGE;
        }

        /// <summary>
        /// Get syntax errors from a gsc
        /// </summary>
        /// <param name="Tree"></param>
        /// <param name="text"></param>
        /// <param name="filename"></param>
        /// <returns></returns>
        public static GSXCompilerLib.Intellisense.ParserErrorData[] CheckSyntax(out ParseTree Tree, string text, string filename = "unknown")
        {
            var gameScript = new GSC2Grammar();
            var parser = new Parser(gameScript);
            Tree = parser.Parse(text, filename);
            return Intellisense.VerboseError(Tree);
        }
    }

    /// <summary>
    /// GSC2 Grammar
    /// </summary>
    [Language("Game Script", "2.0", "GSC Grammar for Black Ops 2")]
    public class GSC2Grammar : Grammar
    {
        /// <summary>
        /// Identifier
        /// </summary>
        public static IdentifierTerminal identifier;
        /// <summary>
        /// String literal
        /// </summary>
        public static StringLiteral stringLiteral;
        /// <summary>
        /// Number literal
        /// </summary>
        public static NumberLiteral numberLiteral;
        /// <summary>
        /// New GSC2 Grammar
        /// </summary>
        /// 
        public GSC2Grammar()
        {
            #region Lexical structure

            //Comments
            var blockComment = new CommentTerminal("block-comment", "/*", "*/");
            var ParserNotification = new CommentTerminal("ParserNotification", "/$", "$/");
            var StringAway = new CommentTerminal("StringAway", "/!", "!/");
            var lineComment = new CommentTerminal("line-comment", "//",
                "\r", "\n", "\u2085", "\u2028", "\u2029");
            var region = new CommentTerminal("line-comment", "#region",
                "\r", "\n", "\u2085", "\u2028", "\u2029");
            var endregion = new CommentTerminal("line-comment", "#endregion",
                "\r", "\n", "\u2085", "\u2028", "\u2029");
            NonGrammarTerminals.Add(region);
            NonGrammarTerminals.Add(endregion);
            NonGrammarTerminals.Add(blockComment);
            NonGrammarTerminals.Add(lineComment);

            //Literals
            numberLiteral = new NumberLiteral("numberLiteral", NumberOptions.AllowSign | NumberOptions.AllowStartEndDot);
            numberLiteral.AddPrefix("0x", NumberOptions.Hex);
            numberLiteral.AddSuffix("f", System.TypeCode.Single);
            numberLiteral.AddSuffix("d", System.TypeCode.Single);
            stringLiteral = new StringLiteral("stringLiteral", "\"");
            identifier = new IdentifierTerminal("identifier", @"_/\", "_");
            

            MarkPunctuation("(", ")", "{", "}", "[", "]", ",", ".", ";", "::", "[[", "]]", "#include", "#using_animtree", "$");

            RegisterOperators(1, "+", "-");
            RegisterOperators(2, "*", "/", "%");
            RegisterOperators(3, "|", "&", "^");
            RegisterOperators(4, "&&", "||");
            RegisterBracePair("(", ")");

            #endregion

            var program = new NonTerminal("program");
            var functions = new NonTerminal("functions");
            var function = new NonTerminal("function");
            var declarations = new NonTerminal("declarations");
            var declaration = new NonTerminal("declaration");
            var defines = new NonTerminal("defines");
            var define = new NonTerminal("define");
            var includes = new NonTerminal("includes");
            var include = new NonTerminal("include");
            var gscForFunction = new NonTerminal("gscForFunction");
            var baseCall = new NonTerminal("baseCall");
            var baseCallPointer = new NonTerminal("baseCallPointer");
            var scriptFunctionCall = new NonTerminal("scriptFunctionCall");
            var scriptFunctionCallPointer = new NonTerminal("scriptFunctionCallPointer");
            var scriptMethodCall = new NonTerminal("scriptMethodCall");
            var scriptMethodCallPointer = new NonTerminal("scriptMethodCallPointer");
            var scriptThreadCall = new NonTerminal("scriptThreadCall");
            var scriptThreadCallPointer = new NonTerminal("scriptThreadCallPointer");
            var scriptMethodThreadCall = new NonTerminal("scriptMethodThreadCall");
            var scriptMethodThreadCallPointer = new NonTerminal("scriptMethodThreadCallPointer");
            var call = new NonTerminal("call");
            var simpleCall = new NonTerminal("simpleCall");
            var parenParameters = new NonTerminal("parenParameters");
            var parameters = new NonTerminal("parameters");
            var expr = new NonTerminal("expr");
            var setVariableField = new NonTerminal("setVariableField");
            var array = new NonTerminal("array");
            var vector = new NonTerminal("vector");
            var _operator = new NonTerminal("operator");
            var relationalOperator = new NonTerminal("relationalOperator");
            var expression = new NonTerminal("expression");
            var relationalExpression = new NonTerminal("relationalExpression");
            var directAccess = new NonTerminal("directAccess");
            var boolNot = new NonTerminal("boolNot");
            var wait = new NonTerminal("wait");
            var size = new NonTerminal("size");
            var isString = new NonTerminal("isString");
            var hashedString = new NonTerminal("hashedString");

            var statement = new NonTerminal("statement");
            var ifStatement = new NonTerminal("ifStatement");
            var elseStatement = new NonTerminal("elseStatement");
            var whileStatement = new NonTerminal("whileStatement");
            var forStatement = new NonTerminal("forStatement");
            var forBody = new NonTerminal("forBody");
            var switchStatement = new NonTerminal("switchStatement");
            var switchLabel = new NonTerminal("switchLabel");
            var switchContents = new NonTerminal("switchContents");
            var switchContent = new NonTerminal("switchContent");
            var foreachStatement = new NonTerminal("foreachStatement");
            var booleanExpression = new NonTerminal("booleanExpression");
            var boolParen = new NonTerminal("boolParen");
            var block = new NonTerminal("block");
            var blockContent = new NonTerminal("blockContent");
            var statementBlock = new NonTerminal("statementBlock");
            var shortExprOperator = new NonTerminal("shortExprOperator");
            var forIterate = new NonTerminal("forIterate");
            var conditionalStatement = new NonTerminal("conditionalStatement");
            var _return = new NonTerminal("return");
            var getFunction = new NonTerminal("getFunction");
            var developerScript = new NonTerminal("developerScript");
            var animTree = new NonTerminal("animTree");
            var usingAnimTree = new NonTerminal("usingAnimTree");
            var getAnimation = new NonTerminal("getAnimation");
            var waitTillFrameEnd = new NonTerminal("waitTillFrameEnd");
            var jumpStatement = new NonTerminal("jumpStatement");
            var parenExpr = new NonTerminal("parenExpr");
            var boolevaloperator = new NonTerminal("boolevaloperator");
            var userprotections = new NonTerminal("userprotections");
            var userblacklist = new NonTerminal("userblacklist");
            var hasAnims = new NonTerminal("animtrees");

            //GSX
            var gotoTerminal = new NonTerminal("gotoTerminal");
            var labelTerminal = new NonTerminal("labelTerminal");
            gotoTerminal.Rule = ToTerm("goto") + identifier + ToTerm(";"); 
            labelTerminal.Rule = identifier + ToTerm(":");

            var thisReference = new NonTerminal("thisReference");
            thisReference.Rule = ToTerm("this") + ToTerm("::") + expr;
            var libUse = new NonTerminal("libUse");
            var libraryReference = new NonTerminal("libraryReference");
            libraryReference.Rule = ToTerm("libraries") + ToTerm("::") + identifier + ToTerm("::") + libUse;
            libUse.Rule = identifier | identifier + parenParameters;
            var usingLibs = new NonTerminal("usingLibs");
            var usingLib = new NonTerminal("usingLib");
            usingLibs.Rule = MakeStarRule(usingLibs, usingLib);
            usingLib.Rule = ToTerm("#using") + ToTerm("libraries") + ToTerm("::") + identifier + ";";


            var protectHeader = new NonTerminal("protectHeader");
            protectHeader.Rule = ToTerm("$") + ToTerm("(") + identifier + ToTerm(")");

            var protectExpr = new NonTerminal("protectExpr");
            protectExpr.Rule = protectHeader + ToTerm("{") + expr + "}";

            var protectBlock = new NonTerminal("protectBlock");
            protectBlock.Rule = protectHeader + block;

            var arraymacro = new NonTerminal("arraymacro");
            arraymacro.Rule = ToTerm("array") + "{" + parameters + "}";

            var arrayshorthand = new NonTerminal("arrayshorthand");
            //+ ToTerm("array")
            arrayshorthand.Rule = ToTerm("array") + expr + ToTerm("=") + "{" + parameters + "}" + ToTerm(";");



            var programEntry = new NonTerminal("programEntry");
            programEntry.Rule = define | include | usingLib | usingAnimTree | ParserNotification | StringAway | function;


            defines.Rule = MakeStarRule(defines, define);
            define.Rule = ToTerm("define") + identifier + expr + ";";
            userblacklist.Rule = MakeStarRule(userblacklist, StringAway);
            hasAnims.Rule = MakeStarRule(hasAnims, animTree);
            userprotections.Rule = MakeStarRule(userprotections, ParserNotification);
            boolevaloperator.Rule = ToTerm("&&") | ToTerm("||");
            waitTillFrameEnd.Rule = identifier + ";";
            usingAnimTree.Rule = ToTerm("#using_animtree") + "(" + stringLiteral + ")" + ";";
            getAnimation.Rule = ToTerm("%") + identifier;
            animTree.Rule = ToTerm("#animtree");
            program.Rule = MakeStarRule(program, programEntry);//includes + hasAnims + userprotections + userblacklist + defines + functions;
            functions.Rule = MakeStarRule(functions, function);
            function.Rule = identifier + parenParameters + block;
            declarations.Rule = MakePlusRule(declarations, declaration);
            declaration.Rule = simpleCall | statement | setVariableField | wait | _return | waitTillFrameEnd | jumpStatement | userblacklist | gotoTerminal | labelTerminal | arrayshorthand;
            block.Rule = ToTerm("{") + blockContent + "}" | ToTerm("{") + "}";
            blockContent.Rule = declarations;
            parenExpr.Rule = ToTerm("(") + expr + ")";
            expr.Rule = directAccess | call | identifier | stringLiteral | array | numberLiteral | vector | expression | protectExpr |
                        relationalExpression | conditionalStatement | boolNot | size |
                        isString | getFunction | libraryReference | hashedString | getAnimation | animTree | parenExpr;
            parameters.Rule = MakeStarRule(parameters, ToTerm(","), expr) | expr;
            parenParameters.Rule = ToTerm("(") + parameters + ")" | "(" + ")";
            includes.Rule = MakeStarRule(includes, include);
            include.Rule = ToTerm("#include") + identifier + ";";

            array.Rule = expr + "[" + expr + "]" | ToTerm("[]");


            vector.Rule = ToTerm("(") + expr + "," + expr + "," + expr + ")";
            shortExprOperator.Rule = ToTerm("=") | "+=" | "-=" | "*=" | "/=" | "%=" | "&=" | "|=" | "++" | "--";
            setVariableField.Rule = expr + shortExprOperator + expr + ";" | expr + shortExprOperator + ";";
            _operator.Rule = ToTerm("+") | "-" | "/" | "*" | "%" | "&" | "|";
            relationalOperator.Rule = ToTerm(">") | ">=" | "<" | "<=" | "==" | "!=";
            expression.Rule = expr + _operator + expr | "(" + expr + _operator + expr + ")";
            relationalExpression.Rule = expr + relationalOperator + expr;


            booleanExpression.Rule = expr | ((booleanExpression) + boolevaloperator + (booleanExpression)) | boolParen;
            boolParen.Rule = (ToTerm("(") + booleanExpression + ToTerm(")"));


            directAccess.Rule = expr + "." + identifier;
            boolNot.Rule = ToTerm("!") + booleanExpression;
            wait.Rule = ToTerm("wait") + expr + ";";
            size.Rule = expr + ".size";
            _return.Rule = ToTerm("return") + expr + ";" | ToTerm("return") + booleanExpression + ";" | ToTerm("return") + ";";
            jumpStatement.Rule = ToTerm("break") + ";" | ToTerm("continue") + ";";
            isString.Rule = ToTerm("&") + stringLiteral;
            hashedString.Rule = ToTerm("#") + stringLiteral;
            getFunction.Rule = ToTerm("::") + expr | gscForFunction + expr;

            gscForFunction.Rule = identifier + "::";
            baseCall.Rule = gscForFunction + identifier + parenParameters | identifier + parenParameters;
            baseCallPointer.Rule = ToTerm("[[") + expr + "]]" + parenParameters;
            scriptFunctionCall.Rule = baseCall;
            scriptFunctionCallPointer.Rule = baseCallPointer;
            scriptMethodCall.Rule = expr + baseCall;
            scriptMethodCallPointer.Rule = expr + baseCallPointer;
            scriptThreadCall.Rule = ToTerm("thread") + baseCall;
            scriptThreadCallPointer.Rule = ToTerm("thread") + baseCallPointer;
            scriptMethodThreadCall.Rule = expr + "thread" + baseCall;
            scriptMethodThreadCallPointer.Rule = expr + "thread" + baseCallPointer;

            call.Rule = scriptFunctionCall | scriptFunctionCallPointer | scriptMethodCall | scriptMethodCallPointer |
                        scriptThreadCall | scriptThreadCallPointer | scriptMethodThreadCall |
                        scriptMethodThreadCallPointer;
            simpleCall.Rule = call + ";";

            statementBlock.Rule = block | declaration;
            statement.Rule = ifStatement | whileStatement | forStatement | switchStatement | foreachStatement | developerScript | protectBlock;
            ifStatement.Rule = ToTerm("if") + "(" + booleanExpression + ")" + statementBlock |
                               ToTerm("if") + "(" + booleanExpression + ")" + statementBlock + elseStatement;
            elseStatement.Rule = ToTerm("else") + statementBlock | ToTerm("else") + ifStatement;
            whileStatement.Rule = ToTerm("while") + "(" + booleanExpression + ")" + statementBlock;
            forIterate.Rule = expr + shortExprOperator + expr | expr + shortExprOperator;
            forBody.Rule = setVariableField + booleanExpression + ";" + forIterate
                           | ToTerm(";") + booleanExpression + ";" + forIterate
                           | ToTerm(";") + ";" + forIterate
                           | ToTerm(";") + ";"
                           | setVariableField + ";" + forIterate
                           | setVariableField + ";"
                           | ToTerm(";") + booleanExpression + ";"
                           | setVariableField + booleanExpression + ";";

            forStatement.Rule = ToTerm("for") + "(" + forBody + ")" + statementBlock;
            foreachStatement.Rule = ToTerm("foreach") + "(" + identifier + "in" + expr + ")" + statementBlock;
            switchLabel.Rule = ToTerm("case") + expr + ":" | ToTerm("default") + ":";
            switchContents.Rule = MakeStarRule(switchContents, switchContent);
            switchContent.Rule = switchLabel + blockContent | switchLabel;
            switchStatement.Rule = ToTerm("switch") + parenExpr + "{" + switchContents + "}";
            conditionalStatement.Rule = booleanExpression + ToTerm("?") + expr + ToTerm(":") + expr;
            developerScript.Rule = ToTerm("/#") + blockContent + "#/";
            Root = program;
        }
    }

    
}
