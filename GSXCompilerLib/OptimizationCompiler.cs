using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

namespace GSXCompilerLib
{
    /*
        Never too late to start documentation...

        Alright so the purpose of this class is as follows:
            -Recieve a parse tree that has been checked for syntax and grammar
            -Change the input tree to make a parse tree with a GSC syntax
            -Produce a parse tree to be sent to the obfuscation compiler
     */
    internal sealed class OptimizationCompiler
    {
        private CompilationPackage Package;
        internal OptimizationCompiler(CompilationPackage package)
        {
            Package = package;
        }

        internal ParseTree Optimize(ParseTree tree)
        {
            return tree;//TODO
        }
    }
}
