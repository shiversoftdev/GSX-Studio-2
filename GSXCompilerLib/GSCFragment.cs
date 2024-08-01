using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;
namespace GSXCompilerLib
{
    internal class GSCFragment
    {
        internal byte[] Contents;
        internal byte[] Position; //Stays null until written
        internal List<GSCFragment> Children = new List<GSCFragment>();
        internal List<byte> DataLink;
        internal int StringReferenceCount, LocalStringReferenceCount;
        internal List<int> StringReferencePositions, LocalStringReferencePositions;
        private bool Finalized;

        internal GSCFragment(List<byte> dlink)
        {
            StringReferenceCount = 0;
            DataLink = dlink;
            Children = new List<GSCFragment>();
            StringReferencePositions = new List<int>();
            LocalStringReferencePositions = new List<int>();
        }

        virtual internal void Write()
        {
            if (Finalized)
                return; //Do not write twice
            Finalized = true;
            Position = BitConverter.GetBytes(DataLink.Count);
            DataLink.AddRange(Contents);
        }

        virtual internal void Write(int position)
        {
            if (Finalized)
                return;
            Finalized = true;
            Position = BitConverter.GetBytes(position);
            if (position + Contents.Length > DataLink.Count)
            {
                DataLink.AddRange(new byte[position + Contents.Length - DataLink.Count]);
            }
            for (int i = 0; i < Contents.Length; i++)
            {
                DataLink[i + position] = Contents[i];
            }
        }

        virtual internal void Write(int position, byte[] contents)
        {
            if (Finalized)
                return;
            Finalized = true;
            Position = BitConverter.GetBytes(position);
            if (position + contents.Length > DataLink.Count)
            {
                DataLink.AddRange(new byte[position + contents.Length - DataLink.Count]);
            }
            for (int i = 0; i < contents.Length; i++)
            {
                DataLink[i + position] = contents[i];
            }
        }

        virtual internal void Replace(int position, byte[] contents)
        {
            if (!Finalized) //Cant replace what doesnt exist
                return;
            for (int i = 0; i < contents.Length; i++) //Potential index out of bounds left behind to debug. Real compiler wont ever take these chances
            {
                DataLink[i + position] = contents[i];
            }
        }

        internal void AddStringReference(int location)
        {
            StringReferencePositions.Add(location);
            StringReferenceCount++;
        }

        internal void AddLocalStringReference(int location)
        {
            LocalStringReferencePositions.Add(location);
            LocalStringReferenceCount++;
        }
    }
}