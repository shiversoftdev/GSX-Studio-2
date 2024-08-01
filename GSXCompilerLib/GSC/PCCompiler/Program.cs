using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;
using Irony.Parsing;

namespace GameScriptCompiler_v3_pc
{
    internal class Program
    {
        public static IntPtr ProcessHandle = IntPtr.Zero;
        private static int ProcessID = -1;
        private static void WriteInternal(int address, byte[] bytes)
        {
            I.WriteProcessMemory(ProcessHandle, (IntPtr) address, bytes, (uint) bytes.Length, 0);
        }

        private static bool ProcessLoad()
        {
            Process[] processesByName = Process.GetProcessesByName("t6zm");
            if (processesByName.Length != 0)
            {
                ProcessID = processesByName[0].Id;
                ProcessHandle = I.OpenProcess(0x1f0fff, false, ProcessID);
                return true;
            }
            return false;
        }
    }

    internal class ExternalEntry
    {
        public List<GSXCompilerLib.Compiler.CompilerError> Compile(string path, Dictionary<string, List<string>> available_keys, GSXCompilerLib.GSC.GSCCompiler ths, string outpath, object[] compilerparams)
        {
            var gameScript = new GSCGrammar();
            var parser = new Parser(gameScript);
            var compiler = new ScriptCompiler(parser.Parse(path), outpath, available_keys, ths, compilerparams, path);
            compiler.Init();
            return compiler.ErrorsToReport;
        }
    }
}