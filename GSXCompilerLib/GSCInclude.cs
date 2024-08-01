using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;
namespace GSXCompilerLib
{
    internal sealed class GSCInclude : GSCFragment
    {
        internal GSCFragment Fragment;

        internal GSCInclude(List<byte> dlink) : base( dlink )
        {
        }

        internal override void Write()
        {
            Contents = BitConverter.GetBytes(BitConverter.ToInt32(Fragment.Position, 0));
            base.Write();
        }
    }
}