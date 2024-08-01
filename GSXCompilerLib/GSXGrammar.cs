using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

//Hate yourself later alright. You are the dipshit who decided to order it like a half brained monkey.

namespace GSXCompilerLib
{
    /// <summary>
    /// Old GSX Grammar
    /// </summary>
    [Language("GSX", "1.0", "Grammar of GSX")]
   
    internal sealed class GSXGrammar : Grammar
    {
        internal GSXGrammar() : base(false)
        {
            #region NonRules
            var blockComment = new CommentTerminal("block-comment", "/*", "*/");
            var lineComment = new CommentTerminal("line-comment", "//", "\r", "\n", "\u2085", "\u2028", "\u2029");
            NonGrammarTerminals.Add(blockComment);
            NonGrammarTerminals.Add(lineComment);
            var number = new RegexBasedTerminal("number", "(-?0x([0-9A-Fa-f]+)\\b)|(-?\\d+([\\.]\\d+)?\\b)|([\\.]\\d+)");
            var stringLiteral = new StringLiteral("stringLiteral", "\"");
            var identifier = new IdentifierTerminal("identifier", "_", "_");

            MarkPunctuation("(", ")", "{", "}", "[", "]", ",", ".", ";", "::", "[[", "]]", "<", ">");
            RegisterOperators(13, "--", "++");
            RegisterOperators(12, "*", "/", "%");
            RegisterOperators(11, "+", "-");
            RegisterOperators(10, "<<", ">>");
            RegisterOperators(9, "<", ">", "<=", ">=");
            RegisterOperators(8, "==", "!=");
            RegisterOperators(7, "&");
            RegisterOperators(6, "^");
            RegisterOperators(5, "|");
            RegisterOperators(4, "&&");
            RegisterOperators(3, "||");
            RegisterOperators(2, "?", ":");
            RegisterOperators(1, "=", "+=", "-=", "*=", "/=", "<<=", ">>=", "%=", "&=", "^=", "|=");
            RegisterBracePair("(", ")");
            RegisterBracePair("{", "}");
            RegisterBracePair("[", "]");
            RegisterBracePair("#debugonly", "#enddebug");
            #endregion
            #region NonTerminals
            var program = new NonTerminal("program");
            var declarations = new NonTerminal("declarations");
            var declaration = new NonTerminal("declaration");
            var preprocessor = new NonTerminal("preprocessor");
            var annotation = new NonTerminal("annotation");
            var function = new NonTerminal("function");
            var structure = new NonTerminal("structure");
            var ppcinclude = new NonTerminal("ppcinclude");
            var ppcuselib = new NonTerminal("ppcuselib");
            var ppctoggleinline = new NonTerminal("ppctoggleinline");
            var ppctoggletypestrict = new NonTerminal("ppctoggletypestrict");
            var gsclocation = new NonTerminal("gsclocation");
            var gsclocationfragment = new NonTerminal("gsclocationfragment");
            var gsxlocation = new NonTerminal("gsxlocation");
            var gsxpath = new NonTerminal("gsxpath");
            var gsxpathfragment = new NonTerminal("gsxpathfragment");
            var creatorannotation = new NonTerminal("creatorannotation");
            var debugannotation = new NonTerminal("debugannotation");
            var projectnameannotation = new NonTerminal("projectnameannotation");
            var watermarkannotation = new NonTerminal("watermarkannotation");
            var structurebody = new NonTerminal("structurebody");
            var structurefield = new NonTerminal("structurefields");
            var structuremember = new NonTerminal("structuremember");
            var variabledeclaration = new NonTerminal("variabledeclaration");
            var gsxtype = new NonTerminal("gsxtype");
            var gsxarraytype = new NonTerminal("gsxarraytype");
            var structureconstruct = new NonTerminal("structureconstruct");
            var structuredestruct = new NonTerminal("structuredestruct");
            var declarationparams = new NonTerminal("declarationparams");
            var declarationparamsbody = new NonTerminal("declarationparamsbody");
            var assignment = new NonTerminal("variableassignment");
            var expression = new NonTerminal("expression");
            var dparamsfragment = new NonTerminal("dparamsfragment");
            var variableassignment = new NonTerminal("variableassignment");
            var paramclause = new NonTerminal("paramclause");
            var gsxtypefragment = new NonTerminal("gsxtypefragment");
            var codeblock = new NonTerminal("codeblock");
            var statements = new NonTerminal("statements");
            var statement = new NonTerminal("statement");
            var functionproperties = new NonTerminal("functionproperties");
            var functionproperty = new NonTerminal("functionproperty");
            var pentrypoint = new NonTerminal("pentrypoint");
            var pnoinline = new NonTerminal("pnoinline");
            var poverride = new NonTerminal("poverride");
            var pinline = new NonTerminal("pinline");
            var pstatic = new NonTerminal("pstatic");
            var ptypestrict = new NonTerminal("ptypestrict");
            var controlflow = new NonTerminal("controlflow");
            var ifstatement = new NonTerminal("ifstatement");
            var contextblock = new NonTerminal("contextblock");
            var whilestatement = new NonTerminal("whilestatement");
            var foreverstatement = new NonTerminal("foreverstatement");
            var dowhilestatement = new NonTerminal("dowhilestatement");
            var forstatement = new NonTerminal("forstatement");
            var foreachstatement = new NonTerminal("foreachstatement");
            var switchstatement = new NonTerminal("switchstatement");
            var switchblock = new NonTerminal("switchblock");
            var switchstatements = new NonTerminal("switchstatements");
            var switchcase = new NonTerminal("switchcase");
            var caserule = new NonTerminal("caserule");
            var defaultrule = new NonTerminal("defaultrule");
            var setvariablefield = new NonTerminal("setvariablefield");
            var setoperator = new NonTerminal("setoperator");
            var setunaryoperator = new NonTerminal("setunaryoperator");
            var command = new NonTerminal("command");
            var breakcommand = new NonTerminal("breakcommand");
            var continuecommand = new NonTerminal("continuecommand");
            var returncommand = new NonTerminal("returncommand");
            var gotocommand = new NonTerminal("gotocommand");
            var labelcommand = new NonTerminal("labelcommand");
            var abortcommand = new NonTerminal("abortcommand");
            var deletecommand = new NonTerminal("deletecommand");
            var destroycommand = new NonTerminal("destroycommand");
            var debugregion = new NonTerminal("debugregion");
            var call = new NonTerminal("call");
            var paramcall = new NonTerminal("paramcall");
            var paramcallbody = new NonTerminal("paramcallbody");
            var paramfragment = new NonTerminal("paramfragment");
            var dcall = new NonTerminal("dcall");
            var externallocation = new NonTerminal("externallocation");
            var ptrcall = new NonTerminal("ptrcall");
            var gscpath = new NonTerminal("gscpath");
            var gsclocationprefix = new NonTerminal("gsclocationprefix");
            var thread = new NonTerminal("thread");
            var paramexpr = new NonTerminal("paramexpr");
            var specialvalue = new NonTerminal("specialvalue");
            var directaccess = new NonTerminal("directaccess");
            var initializer = new NonTerminal("initializer");
            var arraydec = new NonTerminal("arraydec");
            var arraydeclaration = new NonTerminal("arraydeclaration");
            var arrayinitializer = new NonTerminal("arrayinitializer");
            var arrayaccess = new NonTerminal("arrayaccess");
            var stringexpr = new NonTerminal("stringexpr");
            var stringprefix = new NonTerminal("stringprefix");
            var functionptr = new NonTerminal("functionptr");
            var mathoperation = new NonTerminal("mathoperation");
            var binaryoperator = new NonTerminal("binaryoperator");
            var unaryoperation = new NonTerminal("unaryoperation");
            var unaryoperator = new NonTerminal("unaryoperator");
            var compareoperation = new NonTerminal("compareoperation");
            var compareoperator = new NonTerminal("compareoperator");
            var ternaryoperation = new NonTerminal("ternaryoperation");
            var ppcvariable = new NonTerminal("ppcvariable");
            var ppcdefineconstant = new NonTerminal("ppcdefineconstant");
            var usinganimtree = new NonTerminal("usinganimtree");
            var vector = new NonTerminal("vector");
            var size = new NonTerminal("size");
            var basecall = new NonTerminal("basecall");
            var baseptrcall = new NonTerminal("baseptrcall");
            var objectcall = new NonTerminal("objectcall");
            var objectptrcall = new NonTerminal("objectptrcall");
            var waitcommand = new NonTerminal("waitcommand");
            var wtfe = new NonTerminal("wtfe");
            var elsestatement = new NonTerminal("elsestatement");
            var scopemodifier = new NonTerminal("scopemodifier");
            var thisaccessor = new NonTerminal("thisaccessor");
            var fieldaccessor = new NonTerminal("fieldaccessor");
            var pdescription = new NonTerminal("pdescription");
            var destructcommand = new NonTerminal("destructcommand");
            var structCall = new NonTerminal("structCall");
            var structThreadedCall = new NonTerminal("structThreadedCall");
            var cast = new NonTerminal("cast");
            var pexport = new NonTerminal("pexport");
            var animtree = new NonTerminal("animtree");
            var getanim = new NonTerminal("getanim");
            #endregion
            #region preprocessor
            preprocessor.Rule = ppcinclude | ppcuselib | ppcdefineconstant | usinganimtree;
            ppcinclude.Rule = ToTerm("#include") + gsclocation + ";";
            gsclocation.Rule = gsclocationprefix + "\\" + gscpath;
            gsclocationprefix.Rule = ToTerm("maps") | ToTerm("animscripts") | ToTerm("codescripts") | ToTerm("common_scripts") | ToTerm("clientscripts") | ToTerm("character") | ToTerm("aitype") | ToTerm("mpbody");
            gscpath.Rule = MakePlusRule(gscpath, gsclocationfragment);
            gsclocationfragment.Rule = ("\\" + identifier) | identifier;
            ppcuselib.Rule = ToTerm("#uselib") + gsxlocation + ";";
            gsxlocation.Rule = ToTerm("libraries") + "::" + gsxpath;
            gsxpath.Rule = MakePlusRule(gsxpath, gsxpathfragment);
            gsxpathfragment.Rule = ("\\" + identifier) | identifier;
            ppctoggleinline.Rule = ToTerm("#inline") + (ToTerm("on") | ToTerm("off") | ToTerm("context"));
            ppctoggletypestrict.Rule = ToTerm("#typestrict") + (ToTerm("all") | ToTerm("returns") | ToTerm("context") | ToTerm("off"));
            annotation.Rule = creatorannotation | debugannotation | projectnameannotation | watermarkannotation;
            creatorannotation.Rule = ToTerm("@creator") + stringLiteral;
            debugannotation.Rule = ToTerm("@debug") + (ToTerm("on") | ToTerm("off"));
            projectnameannotation.Rule = ToTerm("@projectname") + stringLiteral;
            watermarkannotation.Rule = ToTerm("@watermark") + stringLiteral;
            ppcdefineconstant.Rule = ToTerm("#define") + identifier + (stringexpr | number);
            usinganimtree.Rule = ToTerm("#using_animtree") + "(" + identifier + ")" + ";";
            #endregion
            #region structure
            structure.Rule = ToTerm("struct") + identifier + "{" + structurebody + "}";
            structurebody.Rule = MakeStarRule(structurebody, structuremember);
            structuremember.Rule = structurefield | structureconstruct | structuredestruct | function;
            structurefield.Rule = variabledeclaration + ";";
            variabledeclaration.Rule = gsxtype.Q() + identifier;
            gsxtype.Rule = "<" + gsxtypefragment + ">";
            gsxtypefragment.Rule = gsxarraytype | identifier;
            gsxarraytype.Rule = ToTerm("array") + ":" + gsxtypefragment;
            structureconstruct.Rule = ToTerm("construct") + declarationparams + codeblock;
            structuredestruct.Rule = ToTerm("destruct") + "(" + ")" + codeblock;
            declarationparams.Rule = "(" + declarationparamsbody + ")" | ToTerm("()");
            declarationparamsbody.Rule = MakeStarRule(declarationparamsbody, ToTerm(","),dparamsfragment);
            assignment.Rule = "=" + expression;
            dparamsfragment.Rule = paramclause;
            variableassignment.Rule = variabledeclaration + assignment;
            paramclause.Rule = (variableassignment | variabledeclaration);


            #endregion
            #region function
            function.Rule = functionproperties + identifier + declarationparams + codeblock;
            functionproperties.Rule = MakeStarRule(functionproperties, functionproperty);
            functionproperty.Rule = pentrypoint | pnoinline | pinline | ptypestrict | poverride | pstatic | pdescription | pexport;
            pentrypoint.Rule = "[" + ToTerm("main") + "]";
            pexport.Rule = "[" + ToTerm("export") + "]";
            pnoinline.Rule = "[" + ToTerm("noinline") + "]";
            poverride.Rule = "[" + ToTerm("override") + "]";
            pinline.Rule = "[" + ToTerm("inline") + "]";
            pstatic.Rule = "[" + ToTerm("static") + "]";
            pdescription.Rule = "[" + ToTerm("description") + "(" + stringLiteral + ")" + "]";
            ptypestrict.Rule = "[" + ToTerm("typestrict") + "-" + gsxtypefragment + "]";
            #endregion
            #region Control Flow
            controlflow.Rule = ifstatement | whilestatement | forstatement | foreachstatement | dowhilestatement | foreverstatement | switchstatement;
            ifstatement.Rule = ToTerm("if") + "(" + expression + ")" + contextblock + elsestatement.Q();
            elsestatement.Rule = ToTerm("else") + contextblock;
            contextblock.Rule = codeblock | statement | ";";
            whilestatement.Rule = ToTerm("while") + "(" + expression + ")" + contextblock;
            foreverstatement.Rule = ToTerm("forever") + contextblock;
            dowhilestatement.Rule = ToTerm("do") + contextblock + ToTerm("while") + "(" + expression + ")" + ";";
            forstatement.Rule = ToTerm("for") + "(" + setvariablefield.Q() + ";" + expression.Q() + ";" + setvariablefield.Q() + ")" + contextblock;
            foreachstatement.Rule = ToTerm("foreach") + "(" + identifier + ToTerm("in") + expression + ")" + contextblock;
            switchstatement.Rule = ToTerm("switch") + "(" + expression + ")" + switchblock;
            switchblock.Rule = "{" + switchstatements + "}";
            switchstatements.Rule = MakeStarRule(switchstatements, switchcase);
            switchcase.Rule = caserule | defaultrule;
            caserule.Rule = ToTerm("case") + expression + ":" + statements + breakcommand;
            defaultrule.Rule = ToTerm("default") + ":" + statements + breakcommand;
            setvariablefield.Rule = (expression + setoperator + expression) | (expression + setunaryoperator);
            setoperator.Rule =
                ToTerm("=") |
                ToTerm("+=") |
                ToTerm("-=") |
                ToTerm("*=") |
                ToTerm("/=") |
                ToTerm("%=") |
                ToTerm("^=") |
                ToTerm("|=") |
                ToTerm("&=") |
                ToTerm("<<=") |
                ToTerm(">>=");
            setunaryoperator.Rule = ToTerm("++") |
                                    ToTerm("--");
            #endregion
            #region Commands
            command.Rule = waitcommand | wtfe | breakcommand | continuecommand | returncommand | gotocommand | labelcommand | abortcommand | deletecommand | destroycommand | destructcommand;
            breakcommand.Rule = ToTerm("break") + ";";
            continuecommand.Rule = ToTerm("continue") + ";";
            returncommand.Rule = ToTerm("return") + expression.Q() + ";";
            gotocommand.Rule = ToTerm("goto") + identifier + ";";
            labelcommand.Rule = identifier + ":";
            abortcommand.Rule = ToTerm("abort") + ";";
            deletecommand.Rule = ToTerm("delete") + expression + ";";
            destroycommand.Rule = ToTerm("destroy") + expression + ";";
            debugregion.Rule = ToTerm("#debugonly") + statements + ToTerm("#enddebug");
            waitcommand.Rule = ToTerm("wait") + expression + ";";
            wtfe.Rule = ToTerm("waittillframeend") + ";";
            destructcommand.Rule = ToTerm("destruct") + expression;
            #endregion
            #region Call
            call.Rule = objectptrcall | objectcall | basecall | baseptrcall;
            basecall.Rule = dcall | ToTerm("thread") + dcall;
            baseptrcall.Rule = ptrcall | ToTerm("thread") + ptrcall;
            objectcall.Rule = expression + basecall;
            objectptrcall.Rule = expression + baseptrcall;
            paramcall.Rule = "(" + paramcallbody + ")" | ToTerm("()");
            paramcallbody.Rule = MakeStarRule(paramcallbody, ToTerm(",") ,paramfragment) | paramcall;
            paramfragment.Rule = expression;
            dcall.Rule = externallocation + identifier + paramcall | identifier + paramcall;
            externallocation.Rule = (gsxlocation + "::") | (gsclocation + "::") | (ToTerm("this") + "::");
            ptrcall.Rule = "[[" + expression + "]]" + paramcall;
            #endregion
            #region expression
            expression.Rule = cast | scopemodifier | directaccess | size | animtree | getanim | structCall | structThreadedCall | call | ppcvariable | specialvalue 
                | identifier | stringexpr | initializer | 
                 arraydec | variabledeclaration |
                 number | vector | unaryoperation |
                 mathoperation | compareoperation | ternaryoperation |
                 functionptr | arrayaccess | paramexpr;
            animtree.Rule = ToTerm("animtrees") + "::" + identifier;
            getanim.Rule = "%" + identifier;
            cast.Rule = gsxtype + expression;
            structCall.Rule = expression + ToTerm("->") + identifier + paramcall;
            structThreadedCall.Rule = expression + ToTerm("->>") + identifier + paramcall;
            scopemodifier.Rule = thisaccessor | fieldaccessor;
            fieldaccessor.Rule = ToTerm("field") + "::" + expression;
            thisaccessor.Rule = ToTerm("this") + "::" + expression;
            directaccess.Rule = expression + "." + identifier;
            initializer.Rule = ToTerm("new") + identifier + paramcall;
            arraydec.Rule = arrayinitializer | arraydeclaration;
            arraydeclaration.Rule = ToTerm("[]");
            arrayinitializer.Rule = ToTerm("[]") + "{" + paramcallbody + "}";
            arrayaccess.Rule = expression + "[" + expression + "]";
            stringexpr.Rule = stringprefix.Q() + stringLiteral;
            stringprefix.Rule = ToTerm("$") | ToTerm("&");
            functionptr.Rule = "&" + expression;
            paramexpr.Rule = "(" + expression + ")";
            specialvalue.Rule = ToTerm("undefined");
            mathoperation.Rule = expression + binaryoperator + expression;
            binaryoperator.Rule =
                ToTerm("*") |
                ToTerm("/") |
                ToTerm("%") |
                ToTerm("+") |
                ToTerm("-") |
                ToTerm("<<") |
                ToTerm(">>") |
                ToTerm("^") |
                ToTerm("|") |
                ToTerm("&") |
                ToTerm("||") |
                ToTerm("&&") ;
            unaryoperation.Rule = unaryoperator + expression;
            unaryoperator.Rule = ToTerm("!") | ToTerm("~");
            compareoperation.Rule = expression + compareoperator + expression;
            compareoperator.Rule = ToTerm(">=") | ToTerm("<=") | ToTerm(">") | ToTerm("<") | ToTerm("==") | ToTerm("!=");
            ternaryoperation.Rule = expression + "?" + expression + ":" + expression;
            ppcvariable.Rule = "%" + identifier + "%";
            vector.Rule = "(" + expression + "," + expression + "," + expression + ")";
            size.Rule = expression + "." + ToTerm("size");
            #endregion
            #region Etc
            declarations.Rule = MakeStarRule(declarations, declaration);
            declaration.Rule = preprocessor | structure | function;
            codeblock.Rule = "{" + statements + "}";
            statements.Rule = MakeStarRule(statements, statement);
            statement.Rule = controlflow | (setvariablefield + ";") | call + ";" | command | debugregion;
            #endregion
            Root = program;
            program.Rule = declarations;
        }
    }
}
