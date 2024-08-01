using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

namespace GSXCompilerLib
{
    internal sealed class ObfuscationCompiler
    {
        private CompilationPackage Package;
        public Dictionary<string, List<string>> LocalLexicon;
        internal ObfuscationCompiler(CompilationPackage package)
        {
            Package = package;
        }

        internal ParseTree Obfuscate(ParseTree tree)
        {
            LocalLexicon = new Dictionary<string, List<string>>();
            GenerateDebugForeachLexicon(tree);
            return tree;//TODO
        }

        private void GenerateDebugForeachLexicon(ParseTree tree)
        {
            foreach(var statenent in tree.Root.ChildNodes[0].ChildNodes)
            {
                if(statenent.ChildNodes[0].Term.Name == "function")
                {
                    var fname = statenent.ChildNodes[0].ChildNodes[1].FindTokenAndGetText();
                    LocalLexicon[fname] = new List<string>();
                    for(int i = 0; i < 255; i++)
                    {
                        LocalLexicon[fname].Add("8g7cMfUPbt" + i);
                    }
                }
            }
        }
    }
}
