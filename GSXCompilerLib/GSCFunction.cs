using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

namespace GSXCompilerLib
{
    internal sealed class GSCFunction : GSCFragment
    {
        internal bool Console;
        internal List<byte> Data;
        internal List<string> LocalVariables;
        internal byte NumOfParams = 0;
        internal int NumOfForeach = 0, Crc32 = 0;
        internal GSCFragment NamePtr;
        internal ByteCodeCompiler Compiler;
        internal ParseTreeNode Function;
        private Dictionary<int, GSCFragment> StringReferences;
        private Dictionary<int, GSCFragment> LocalStringReferences;
        internal int FunctionEnd;

        internal GSCFunction(List<byte> dlink, ByteCodeCompiler compiler, ParseTreeNode function, bool console) : base(dlink)
        {
            Compiler = compiler;
            Function = function;
            Data = new List<byte>();
            LocalVariables = new List<string>();
            StringReferences = new Dictionary<int, GSCFragment>();
            NamePtr = Compiler.GetStringFrag(function.ChildNodes[1].Token.ValueString);
            LocalStringReferences = new Dictionary<int, GSCFragment>();
            this.Console = console;
        }

        internal override void Write()
        {
            Contents = Data.ToArray();
            base.Write();
            MarkFunctionEnd();
            var alignedPos = (int)(DataLink.Count + 3 & 0xFFFFFFFC); //Force 32 bit alignment!
            if (DataLink.Count < alignedPos)
                DataLink.AddRange(new byte[alignedPos - DataLink.Count]);
            foreach (int key in StringReferences.Keys) //Replace String Refs
            {
                var pos = BitConverter.ToInt32(Position, 0) + key;
                var data = BitConverter.GetBytes(BitConverter.ToUInt16(StringReferences[key].Position, 0));
                if (Console)
                    Replace(pos, data.Reverse<byte>().ToArray<byte>());
                else
                    Replace(pos, data);
                StringReferences[key].AddStringReference(BitConverter.ToUInt16(Position, 0) + key); //Write the referencer's position to the referee so that we can track write positions
            }
            foreach (int key in LocalStringReferences.Keys) //Replace String Refs
            {
                var pos = BitConverter.ToInt32(Position, 0) + key;
                var data = BitConverter.GetBytes(BitConverter.ToUInt16(LocalStringReferences[key].Position, 0));
                if (Console)
                    Replace(pos, data.Reverse<byte>().ToArray<byte>());
                else
                    Replace(pos, data);
                LocalStringReferences[key].AddLocalStringReference(BitConverter.ToUInt16(Position, 0) + key); //Write the referencer's position to the referee so that we can track write positions
            }
            GSCExport export = new GSCExport(DataLink, this, Console);
            Compiler.GSCExports.Add(export);
        }

        internal void EmitFunction()
        {
            CollectParameters(Function.ChildNodes[2].ChildNodes[0]);
            CollectLocals(Function.ChildNodes[3]);
            if(LocalVariables.Count > 0)
            {
                EmitLocalVariables();
            }
            else
            {
                EmitOPCode(COD9_OP.Codes.OP_checkclearparams);
            }
            Compile(Function.ChildNodes[3].ChildNodes[0]);
            EmitOPCode(COD9_OP.Codes.OP_End);
            //TODO if count > 65535 throw error
            //TODO if locals count > 255 throw error
        }

        internal void MarkFunctionEnd()
        {
            FunctionEnd = Contents.Length;
        }

        internal COD9_OP EmitOPCode(COD9_OP.Codes code)
        {
            byte Code = (byte)code;
            COD9_OP op = new COD9_OP(Data, Code, this.Console);
            op.Write();
            return op;
        }

        private void CollectParameters(ParseTreeNode node)
        {
            foreach(var paramfragment in node.ChildNodes)
            {
                var param = paramfragment.ChildNodes[0].ChildNodes[0];
                if (!LocalVariables.Contains(param.ChildNodes[param.ChildNodes.Count - 1].Token.Value.ToString()))
                {
                    LocalVariables.Add(param.ChildNodes[param.ChildNodes.Count - 1].Token.Value.ToString());
                }
                NumOfParams++;
            }
        }

        private void CollectLocals(ParseTreeNode node)
        {
            foreach (ParseTreeNode childNode in node.ChildNodes)
            {
                switch (childNode.Term.Name)
                {
                    case "setvariablefield":
                        if (childNode.ChildNodes[0].ChildNodes[0].Term.Name == "identifier" &&
                            !LocalVariables.Contains(childNode.ChildNodes[0].ChildNodes[0].Token.Value.ToString()) && childNode.ChildNodes.Count > 2 )
                            LocalVariables.Add(childNode.ChildNodes[0].ChildNodes[0].Token.Value.ToString());
                        break;
                    case "foreachStatement":
                        LocalVariables.Add(Compiler.ArrayKeys[Function.ChildNodes[1].Token.Value.ToString()][NumOfForeach].Key);
                        LocalVariables.Add(Compiler.ArrayKeys[Function.ChildNodes[1].Token.Value.ToString()][NumOfForeach].Value);
                        NumOfForeach++;
                        if (!LocalVariables.Contains(childNode.ChildNodes[1].Token.Value.ToString()))
                        {
                            LocalVariables.Add(childNode.ChildNodes[1].Token.Value.ToString());
                        }
                        CollectLocals(childNode);
                        break;

                    case "objectcall":
                        var dcallexpression = childNode.ChildNodes[1].ChildNodes[childNode.ChildNodes[1].ChildNodes.Count - 1].ChildNodes[0];
                        if (dcallexpression.Term.Name != "identifier")
                            break;
                        if (dcallexpression.Token.Value.ToString() == "waittill")
                        {
                            ParseWaittillVars(childNode.ChildNodes[1].ChildNodes[childNode.ChildNodes[1].ChildNodes.Count - 1].ChildNodes[1]);
                        }
                        break;

                    default:
                        CollectLocals(childNode);
                        break;
                }
            }
        }

        private void ParseWaittillVars(ParseTreeNode Node, bool compile = false)
        {
            foreach (ParseTreeNode paramfragment in Node.ChildNodes[0].ChildNodes)
            {
                if (paramfragment.ChildNodes[0].ChildNodes[0].Term.Name == "identifier" && !LocalVariables.Contains(paramfragment.ChildNodes[0].ChildNodes[0].Token.Value.ToString()) &&
                    !compile)
                {
                    LocalVariables.Add(paramfragment.ChildNodes[0].ChildNodes[0].Token.Value.ToString());
                }
                else if (paramfragment.ChildNodes[0].ChildNodes[0].Term.Name == "identifier" && compile)
                {
                    //EvalLocalVariable(parameter.FindTokenAndGetValue(), false, true);
                }
                else
                {
                   //ParseWaittillVars(parameter, compile);
                }
            }
        }

        private void EmitLocalVariables()
        {
            COD9_OP code = EmitOPCode(COD9_OP.Codes.OP_CreateLocalVariables);
            code.Add((byte)LocalVariables.Count);
            foreach(var variable in LocalVariables)
            {
                code.AlignLink16(); //This trusts that this OP_Code is written next!
                AddStringRef(Compiler.GetStringFrag(variable));
            }
            LocalVariables.Reverse(); //Why? Cause it's a stack.
            code.Write();
        }

        private void Compile(ParseTreeNode node, bool _ref = false, bool waittillvar = false)
        {
            switch (node.Term.Name)
            {
                default:
                    foreach (var cnode in node.ChildNodes)
                        Compile(cnode);
                    break;
                case "wtfe":
                    EmitOPCode(COD9_OP.Codes.OP_waittillFrameEnd);
                    break;
                    //... TODO
            }
        }

        internal int ComputeCrc32()
        {
            //TODO
            return -1;
        }

        /*  Brief commentary on why this works (because I think its clever as fuck)
         *  So we need to know the amount of data before the reference to align right? So that means we cant 'local align'
         *  Well see, no. We need to know the *alignment* of the data before this to align correctly... meaning...
         *  We can align global functions to write dynamic alignment with 100% certainty.
         */
        internal void AlignLocal16(byte offset = 0)
        {
            var alignedPos = (int)(Data.Count + 1 + offset & 0xFFFFFFFE);
            if (Data.Count < alignedPos)
                Data.AddRange(new byte[alignedPos - Data.Count]);
        }

        internal void AlignLocal32(byte offset = 0)
        {
            var alignedPos = (int)(Data.Count + 3 + offset & 0xFFFFFFFC);
            if (Data.Count < alignedPos)
                Data.AddRange(new byte[alignedPos - Data.Count]);
        }

        internal void AddStringRef(GSCFragment strfrag)
        {
            StringReferences[Data.Count] = strfrag;
            Data.AddRange(new byte[2]);
        }

        internal void AddLocalStringRef(GSCFragment strfrag)
        {
            LocalStringReferences[Data.Count] = strfrag;
            Data.AddRange(new byte[2]);
        }
    }
}
