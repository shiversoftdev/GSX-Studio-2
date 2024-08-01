using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;
using System.IO;

namespace GSXCompilerLib
{
    /// <summary>
    /// Main compiler class
    /// </summary>
    public sealed class Compiler
    {
        /// <summary>
        /// The package to compile
        /// </summary>
        public CompilationPackage Package;
        /// <summary>
        /// Background worker to run the compilation process
        /// </summary>
        public System.ComponentModel.BackgroundWorker Worker;
        private ObfuscationCompiler Obfuscator;
        private OptimizationCompiler Optimizer;
        //private ByteCodeCompiler ByteCodeConverter;
        /// <summary>
        /// New compiler instance
        /// </summary>
        /// <param name="p"></param>
        public Compiler(CompilationPackage p)
        {
            Package = p;
            Obfuscator = new ObfuscationCompiler(p);
            Optimizer = new OptimizationCompiler(p);
        }

        /// <summary>
        /// Struct for a compiler error
        /// </summary>
        public struct CompilerError
        {
            /// <summary>
            /// Message of the error
            /// </summary>
            public string Msg;
            /// <summary>
            /// Compiler node from the error. May be null, so check to make sure it isnt
            /// </summary>
            public ParseTreeNode Node;
            /// <summary>
            /// Is the error fatal
            /// </summary>
            public bool FatalError;
        }

        /// <summary>
        /// Main method to compile the entire package
        /// </summary>
        /// <returns></returns>
        public int CompileScripts()
        {
            int cscript = 1;
            int succeeded = 0;
            GSC.GSCStaticVariables.ResetAllStaticVars();
            Dictionary<CompilationScript, GSC.GSCCompiler> CWorkers = new Dictionary<CompilationScript, GSC.GSCCompiler>();
            T6FunctionResolver.ResetLib();
            if (Package.Target != PlatformTarget.Package)
            {
                CreateScriptOutputFolders();
                foreach (var Script in Package.Scripts)
                {
                    Worker.ReportProgress(cscript, "Working on " + Script.ScriptName + "...");
                    /*
                    ParseTree tree = Script.Tree;
                    try TODO Message list!
                    {
                        tree = Optimizer.Optimize(tree);
                        tree = Obfuscator.Obfuscate(tree);
                        ByteCodeConverter = new ByteCodeCompiler(Package, Obfuscator.LocalLexicon);
                        File.WriteAllBytes(Package.OutputDirectory + Path.DirectorySeparatorChar + Script.ScriptName.Substring(0, Script.ScriptName.Length - 4) + GetScriptExtension(Script.ScriptName.Substring(Script.ScriptName.Length - 4)), ByteCodeConverter.CompileToByteCode(tree, Script).ToArray());
                    }
                    catch
                    {
                        succeeded--;
                    }
                    */
                    GSC.GSCCompiler comp = new GSC.GSCCompiler(Package.OutputDirectory + Path.DirectorySeparatorChar + Script.ScriptName.Substring(0, Script.ScriptName.Length - 4) + GetScriptExtension(Script.ScriptName.Substring(Script.ScriptName.Length - 4)));
                    comp.CompileOnly = !Package.Optimize;
                    comp.OptimizeGlobals = Package.OptimizeChildren;
                    comp.UseSymbols = Package.Symbolize;
                    comp.ScriptName = Script.ScriptName.Replace('\\', '/').Replace(".gsx", ".gsc").ToLower();
                    comp.Message = Package.ProjectName + " [" + Script.ScriptName.Substring(Script.ScriptName.LastIndexOf(Path.DirectorySeparatorChar) + 1) + "] made by " + Package.CreatorName;
                    comp.PC = PlatformTarget.PC == Package.Target;
                    comp.Debug = Package.Debug;
                    CWorkers[Script] = comp;
                    /*
                    if (comp.CompileOnly)
                    {
                        if (comp.Compile(Script.ScriptContents))
                            succeeded++;
                        else
                        {
                            Worker.ReportProgress(cscript, "Error - " + comp.ERROR_MESSAGE);
                        }
                        cscript++;
                        continue;
                    }
                    */
                    if(!comp.Begin(Script.ScriptContents)) 
                    {
                        Worker.ReportProgress(cscript, "Error - " + comp.ERROR_MESSAGE);
                    }
                    cscript++;
                    /*
                    if (comp.Compile(Script.ScriptContents))
                        succeeded++;
                    else
                    {
                        Worker.ReportProgress(cscript, "Error - " + comp.ERROR_MESSAGE);
                    }
                    cscript++;
                    */
                }

                cscript = 1;
                foreach (var Script in Package.Scripts)
                {
                    if (CWorkers[Script].CompileOnly || CWorkers[Script].Optimizer.EXIT_CODE > 1)
                    {
                        cscript++;
                        continue;
                    }
                    if (!CWorkers[Script].CollectFunctions())
                        Worker.ReportProgress(cscript, "Error in (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                }
                //File.WriteAllLines("E:\\FUNC_COLLECT.txt", GSC.GSCStaticVariables.FunctionNames.ToArray());
                cscript = 1;
                foreach (var Script in Package.Scripts)
                {
                    if (CWorkers[Script].CompileOnly || CWorkers[Script].Optimizer.EXIT_CODE > 1)
                    {
                        cscript++;
                        continue;
                    }
                    if (!CWorkers[Script].CollectVTokens())
                        Worker.ReportProgress(cscript, "Error in (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                }

                cscript = 1;
                foreach (var Script in Package.Scripts)
                {
                    if (CWorkers[Script].CompileOnly || CWorkers[Script].Optimizer.EXIT_CODE > 1)
                    {
                        cscript++;
                        continue;
                    }
                    if(!CWorkers[Script].ReplaceGlobalsIfAllowed())
                        Worker.ReportProgress(cscript, "Error in (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                }
                cscript = 1;
                foreach (var Script in Package.Scripts)
                {
                    if (CWorkers[Script].CompileOnly || CWorkers[Script].Optimizer.EXIT_CODE > 1)
                    {
                        cscript++;
                        continue;
                    }
                    if (!CWorkers[Script].CollectLocal())
                        Worker.ReportProgress(cscript, "Error in (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                }
                cscript = 1;
                foreach (var Script in Package.Scripts)
                {
                    if (CWorkers[Script].CompileOnly || CWorkers[Script].Optimizer.EXIT_CODE > 1)
                    {
                        cscript++;
                        continue;
                    }
                    if (!CWorkers[Script].Finish())
                        Worker.ReportProgress(cscript, "Error in (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                }
                cscript = 1;
                foreach (var Script in Package.Scripts)
                {
                    if (CWorkers[Script].CompileOnly || CWorkers[Script].Optimizer.EXIT_CODE > 1)
                    {
                        cscript++;
                        continue;
                    }
                    if (!CWorkers[Script].Finish2())
                        Worker.ReportProgress(cscript, "Error in (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                    else
                        succeeded++;
                }

                if(Package.Scripts.Count > succeeded)
                {
                    Worker.ReportProgress(cscript, "Error: Linking failed because 1 or more scripts failed to compile");
                }
                else
                {
                    succeeded = 0;
                    Worker.ReportProgress(cscript, "Linking Scripts...");
                    foreach (var Script in Package.Scripts)
                    {
                        byte[] bytes = File.ReadAllBytes(CWorkers[Script].Optimizer.OutputPath);
                        byte result = T6FunctionResolver.UpdateLib(Script.ScriptName.Replace('\\', '/').Replace(".gsx",".gsc"), bytes, Package.Target == PlatformTarget.PC ? EndianType.LittleEndian : EndianType.BigEndian);
                        if(result > 0)
                            Worker.ReportProgress(cscript, "Error Linking (" + Script.ScriptName.Replace('\\', '/').Replace(".gsx", ".gsc") + ") ERR[" + result + "]: Failed to update the script database");
                    }
                    //T6FunctionResolver.BreakpointTest();
                    foreach (var Script in Package.Scripts)
                    {
                        if (!CWorkers[Script].Optimizer.Link(Script.ScriptName))
                            Worker.ReportProgress(cscript, "Error Linking (" + Script.ScriptName + "): " + CWorkers[Script].ERROR_MESSAGE);
                        else
                            succeeded++;
                    }
                    
                }
            }
            else
            {
                //TODO
            }

            return succeeded;
        }

        private string GetScriptExtension(string extension)
        {
            /*
            switch (extension.ToLower())
            {
                case ".gsc":
                    return ".cgsx";
                case ".csc":
                    return ".ccsx";
            }
            */
            return ".gsc";// wtf happened?
        }

        private void CreateScriptOutputFolders()
        {
            foreach (CompilationScript script in Package.Scripts)
            {
                string[] split = (script.ScriptName).Split('\\');
                string dir = Package.OutputDirectory;
                for (int i = 0; i < split.Length - 1; i++)
                {
                    dir += Path.DirectorySeparatorChar + split[i];
                    if (!Directory.Exists(dir))
                        Directory.CreateDirectory(dir);
                }
            }
        }
    }
}
