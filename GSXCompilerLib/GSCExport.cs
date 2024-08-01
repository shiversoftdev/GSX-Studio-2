using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GSXCompilerLib
{
    internal sealed class GSCExport : GSCFragment
    {
        private List<byte> Data;
        private GSCFunction Function;
        private bool Console;
        internal GSCExport(List<byte> dlink, GSCFunction function, bool console) : base(dlink)
        {
            Console = console;
            Data = new List<byte>();
            Function = function;
        }

        internal override void Write() //using sizeof simply to make this make more sense when re-reading tomorrow morning
        {
            AddData(BitConverter.GetBytes(Function.ComputeCrc32()), sizeof(int));
            AddData(Function.Position, sizeof(int));
            AddData(Function.NamePtr.Position, sizeof(short));
            Data.Add(Function.NumOfParams);
            Data.Add(0x0);
            Contents = Data.ToArray();
            base.Write();
        }

        internal void AddData(byte[] data, int size)
        {
            if (Console)
                data = data.Reverse<byte>().ToArray<byte>();
            for(int i = Console ? (data.Length - size) : 0; i < (Console ? data.Length : size); i++)
            {
                Data.Add(data[i]);
            }
        }
    }
}
