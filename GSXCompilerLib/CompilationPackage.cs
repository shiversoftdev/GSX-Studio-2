using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;
namespace GSXCompilerLib
{
    /// <summary>
    /// Package used by the compiler to compile gscs
    /// </summary>
    public sealed class CompilationPackage
    {
        /// <summary>
        /// List of CompilationScripts to compile
        /// </summary>
        public List<CompilationScript> Scripts = new List<CompilationScript>();
        /// <summary>
        /// Should the GSC include the debug flag
        /// </summary>
        public bool Debug;
        /// <summary>
        /// Target platform for the compilation
        /// </summary>
        public PlatformTarget Target;
        /// <summary>
        /// Directory to write the files to
        /// </summary>
        public string OutputDirectory;
        /// <summary>
        /// Name of the project creator
        /// </summary>
        public string CreatorName;
        /// <summary>
        /// Name of the project
        /// </summary>
        public string ProjectName;
        /// <summary>
        /// Watermark embedded in the gsc
        /// </summary>
        public string WaterMark;
        /// <summary>
        /// Should the script be optimized? (Must be true if defines are used)
        /// </summary>
        public bool Optimize = true;
        /// <summary>
        /// Should the child variables be optimized (*.var?)
        /// </summary>
        public bool OptimizeChildren = false;
        /// <summary>
        /// Should the gsc be symbolized
        /// </summary>
        public bool Symbolize = true;

        internal string GetFileExtension(string TargetExtension)
        {
            if(TargetExtension == ".gsc")
            {
                return ".csx";
            }
            
            return ".gsc";
        }
    }

    /// <summary>
    /// Target platform for compilation
    /// </summary>
    public enum PlatformTarget
    {
        /// <summary>
        /// Build for console
        /// </summary>
        Console = 0x0,
        /// <summary>
        /// Build for PC
        /// </summary>
        PC = 0x1,
        /// <summary>
        /// Not supported
        /// </summary>
        Package = 0x2,
        
    }

    /// <summary>
    /// Script wrapper for compilation
    /// </summary>
    public sealed class CompilationScript
    {
        /// <summary>
        /// Parse tree of the script (using GSC2)
        /// </summary>
        public ParseTree Tree;
        /// <summary>
        /// Contents of the script
        /// </summary>
        public string ScriptContents;
        /// <summary>
        /// Name of the script
        /// </summary>
        public string ScriptName;
    }
}
