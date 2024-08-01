using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PS3Lib;
using System.Runtime.InteropServices;
using System.Diagnostics;
using JRPC_Client;
using System.Windows.Forms;

namespace GSXCompilerLib
{
    /// <summary>
    /// Type of platform to use
    /// </summary>
    public enum XPlatformType
    {
        /// <summary>
        /// PS3->CCAPI
        /// </summary>
        PLATFORM_PS3_CCAPI,
        /// <summary>
        /// PS3->TMAPI
        /// </summary>
        PLATFORM_PS3_TMAPI,
        /// <summary>
        /// XB360->JRPC2
        /// </summary>
        PLATFORM_XBOX360,
        /// <summary>
        /// Redacted
        /// </summary>
        PLATFORM_PC_REDACTED,
        /// <summary>
        /// Steam
        /// </summary>
        PLATFORM_PC_STEAM
    }
    /// <summary>
    /// Platform used to inject GSX
    /// </summary>
    public class XPlatform
    {
        /// <summary>
        /// ID of the platform
        /// </summary>
        public XPlatformType PlatformID;
        private PS3API PS3;
        private Memory mem;
        private int ProcessID;
        private IntPtr ProcessHandle;
        private XDevkit.IXboxConsole Jtag;
        private bool IsAttached;
        internal bool HasBeenOptimized;
        /// <summary>
        /// New XPlatform
        /// </summary>
        public XPlatform()
        {
            IsAttached = false;
        }
        /// <summary>
        /// Connect to the target platform
        /// </summary>
        /// <returns></returns>
        public bool Connect()
        {
            try
            {
                switch (PlatformID)
                {
                    case XPlatformType.PLATFORM_PS3_CCAPI:
                        {
                            PS3 = new PS3API(SelectAPI.ControlConsole);
                            IsAttached = (PS3.ConnectTarget() && PS3.AttachProcess());
                            if(IsAttached)
                            {
                                PS3.CCAPI.Notify(CCAPI.NotifyIcon.FRIEND, "GSX Connected!");
                            }
                            return IsAttached;
                        }
                    case XPlatformType.PLATFORM_PS3_TMAPI:
                        {
                            PS3 = new PS3API(SelectAPI.TargetManager);
                            IsAttached = (PS3.ConnectTarget() && PS3.AttachProcess());
                            return IsAttached;
                        }
                    case XPlatformType.PLATFORM_PC_REDACTED:
                        {
                            mem = new Memory();
                            List<Process> processes = new List<Process>();
                            processes.AddRange(Process.GetProcessesByName("t6mpv43"));
                            processes.AddRange(Process.GetProcessesByName("t6zmv41"));
                            if (processes.Count > 0)
                            {
                                ProcessID = processes[0].Id;
                                bool result = mem.ConnectProcess(ProcessID);
                                ProcessHandle = mem.pHandel;
                                return IsAttached = result;
                            }
                            break;
                        }
                    case XPlatformType.PLATFORM_PC_STEAM:
                        {
                            mem = new Memory();
                            List<Process> processes = new List<Process>();
                            processes.AddRange(Process.GetProcessesByName("t6mp"));
                            processes.AddRange(Process.GetProcessesByName("t6zm"));
                            if (processes.Count > 0)
                            {
                                ProcessID = processes[0].Id;
                                bool result = mem.ConnectProcess(ProcessID);
                                ProcessHandle = mem.pHandel;
                                return IsAttached = result;
                            }
                            break;
                        }
                    case XPlatformType.PLATFORM_XBOX360:
                        {
                            IsAttached = JRPC.Connect(Jtag, out Jtag);
                            JRPC.XNotify(Jtag, "GSX Connected Successfully");
                            
                            return IsAttached;
                        }
                }
            }
            catch
            {
                return IsAttached = false;
            }
            return IsAttached = false;
        }

        private bool _zm = false;
        private bool _zm_check = false;
        private const string _zm_check_string = "maps/mp/gametypes_zm/_globallogic_player.gsc";
        /// <summary>
        /// Is the platform using zombies or MP at the time of connection
        /// </summary>
        public bool IsZombies
        {
            //maps/mp/gametypes_zm/_globallogic_player.gsc
            get
            {
                if(!_zm_check)
                {
                    if (!IsAttached)
                        return false;

                    GSCBuffer buffer = GSXInjector.ResolveBuffer(GSXInjector.XPlatformAsGSC(PlatformID), false, _zm_check_string);
                    try
                    {
                        byte[] data;
                        bool read = ReadBytes((uint)buffer.BufferPtr + 0x40, (uint)(_zm_check_string.Length), out data);
                        if(!read)
                        {
                            _zm_check = true;
                            return _zm = false;
                        }
                        string result = Encoding.ASCII.GetString(data).ToLower().Replace('\\','/');
                        if (result == _zm_check_string)
                            _zm = true;
                    }
                    catch
                    {
                        _zm_check = true;
                        return _zm = false;
                    }

                    _zm_check = true;
                }
                return _zm;
            }
        }
        /// <summary>
        /// Disconnect from the target
        /// </summary>
        /// <returns></returns>
        public bool Disconnect()
        {
            try
            {
                switch (PlatformID)
                {
                    case XPlatformType.PLATFORM_PS3_CCAPI:
                    case XPlatformType.PLATFORM_PS3_TMAPI:
                        PS3.DisconnectTarget();
                        return !(IsAttached = false);

                }
            }
            catch
            {
                return IsAttached = false;
            }
            return !(IsAttached = false);
        }

        
        /// <summary>
        /// Write the specified bytes to the platform
        /// </summary>
        /// <param name="address"></param>
        /// <param name="bytes"></param>
        /// <returns></returns>
        public bool WriteBytes(uint address, byte[] bytes, uint NewAccess = 0x0)
        {
            if (!IsAttached)
                return false;
            try
            {
                switch (PlatformID)
                {
                    case XPlatformType.PLATFORM_PS3_CCAPI:
                    case XPlatformType.PLATFORM_PS3_TMAPI:
                        if (PS3 != null)
                            PS3.SetMemory(address, bytes);
                        else
                            return false;
                        break;
                    case XPlatformType.PLATFORM_XBOX360:
                        if (Jtag != null)
                            JRPC.SetMemory(Jtag, address, bytes);
                        else
                            return false;
                        break;
                    case XPlatformType.PLATFORM_PC_REDACTED:
                    case XPlatformType.PLATFORM_PC_STEAM:
                        if (mem != null)
                            if (mem.WriteBytes(address, bytes, NewAccess) != 0)
                                return true;
                            else
                            {
                                MessageBox.Show(mem.LastErrorToString());
                                return false;
                            }
                        else
                            return false;
                }
            }
            catch
            {
                return false;
            }
            return true;
        }
        /// <summary>
        /// Write an int to the platform
        /// </summary>
        /// <param name="address"></param>
        /// <param name="write"></param>
        /// <returns></returns>
        public bool WriteInt(uint address, int write, uint NewAccess = 0x0)
        {
            if (!IsAttached)
                return false;
            try
            {
                switch (PlatformID)
                {
                    case XPlatformType.PLATFORM_PS3_CCAPI:
                    case XPlatformType.PLATFORM_PS3_TMAPI:
                        if (PS3 != null)
                            PS3.SetMemory(address, BitConverter.GetBytes(write).Reverse<byte>().ToArray<byte>());
                        else
                            return false;
                        break;
                    case XPlatformType.PLATFORM_XBOX360:
                        if (Jtag != null)
                            JRPC.WriteInt32(Jtag, address, write);
                        else
                            return false;
                        break;
                    case XPlatformType.PLATFORM_PC_REDACTED:
                    case XPlatformType.PLATFORM_PC_STEAM:
                        if (mem != null)
                            mem.WriteInteger((int)address, write, NewAccess);
                        else
                            return false;
                        break;
                }
            }
            catch
            {
                return false;
            }
            return true;
        }

        public bool IsOptimized()
        {
            return HasBeenOptimized;
        }

        /// <summary>
        /// Will try to optimize the platform
        /// </summary>
        public void TryOptimize(GSXInjector.IGSCFile[] scripts)
        {
            try
            {
                XStringReducer.OptimizeScripts(this, scripts);
            }
            catch
            {

            }
        }


        /// <summary>
        /// Read bytes from the platform
        /// </summary>
        /// <param name="address"></param>
        /// <param name="length"></param>
        /// <param name="buffer"></param>
        /// <returns></returns>
        public bool ReadBytes(uint address, uint length, out byte[] buffer)
        {
            buffer = new byte[length];
            if (!IsAttached)
                return false;
            try
            {
                switch (PlatformID)
                {
                    case XPlatformType.PLATFORM_PS3_CCAPI:
                    case XPlatformType.PLATFORM_PS3_TMAPI:
                        if (PS3 != null)
                            buffer = PS3.GetBytes(address, (int)length);
                        else
                            return false;
                        break;
                    case XPlatformType.PLATFORM_XBOX360:
                        if (Jtag != null)
                        {
                            buffer = JRPC.GetMemory(Jtag, address, length);
                        }
                        else
                            return false;
                        break;
                    case XPlatformType.PLATFORM_PC_STEAM:
                    case XPlatformType.PLATFORM_PC_REDACTED:
                        if (mem != null)
                            buffer = mem.ReadBytes((int)address, (int)length);
                        else
                            return false;
                        break;
                }
            }
            catch
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Read a ushort from the target platform
        /// </summary>
        /// <param name="address"></param>
        /// <param name="Value"></param>
        /// <returns></returns>
        public bool ReadUshort(uint address, out ushort Value)
        {
            if (PlatformID == XPlatformType.PLATFORM_XBOX360)
            {
                try
                {
                    Value = JRPC.ReadUInt16(Jtag, address);
                    return true;
                }
                catch
                {
                    Value = 0x0;
                    return false;
                }
            }
            Value = 0x0;
            byte[] buffer;
            bool result = ReadBytes(address, sizeof(ushort), out buffer);
            if (result)
                Value = BitConverter.ToUInt16(IsPC ? buffer : buffer.Reverse<byte>().ToArray<byte>(), 0);
            return result;
        }

        /// <summary>
        /// Is the platform a PC platform
        /// </summary>
        public bool IsPC
        {
            get
            {
                return PlatformID == XPlatformType.PLATFORM_PC_STEAM || PlatformID == XPlatformType.PLATFORM_PC_REDACTED;
            }
        }

        /// <summary>
        /// Read a string from the target platform
        /// </summary>
        /// <param name="address"></param>
        /// <param name="Value"></param>
        /// <returns></returns>
        public bool ReadString(uint address, out string Value)
        {
            if (PlatformID == XPlatformType.PLATFORM_XBOX360)
            {
                try
                {
                    Value = "";
                    for (int i = 0; i < 255; i++) //Max string length of 255. Chances of two strings matching at this length almost always mean a match
                    {
                        byte res = JRPC.ReadByte(Jtag, (uint)(address + i));
                        if (res == 0x0)
                            return true;
                        Value += (char)res;
                    }
                    return true;
                }
                catch
                {
                    Value = "";
                    return false;
                }
            }
            Value = "";
            uint TargetAddress = address;
            byte[] buffer = null;
            bool Result = false;
            for (int i = 0; i < 64; i++) //Max string length of 255. Chances of two strings matching at this length almost always mean a match
            {
                Result = ReadBytes(TargetAddress, 4, out buffer);
                if (!Result)
                    return false;
                for(byte j = 0; j < 4; j++)
                {
                    if (buffer[j] == 0x0)
                        return true;
                    Value += (char)buffer[j];
                }
                TargetAddress += 4;
            }
            return true;
        }

        /// <summary>
        /// Query a process
        /// </summary>
        /// <param name="address"></param>
        /// <param name="dwLength"></param>
        /// <returns></returns>
        internal Memory.MEMORY_BASIC_INFORMATION QueryProcess(IntPtr address)
        {
            return mem.QueryProcess(address);
        }

        /// <summary>
        /// Read a byte from the target platform
        /// </summary>
        /// <param name="Address"></param>
        /// <param name="Value"></param>
        /// <returns></returns>
        public bool ReadByte(uint Address, out byte Value)
        {
            if (PlatformID == XPlatformType.PLATFORM_XBOX360)
            {
                try
                {
                    Value = JRPC.ReadByte(Jtag, Address);
                    return true;
                }
                catch
                {
                    Value = 0x0;
                    return false;
                }
            }
            Value = 0x0;
            byte[] OutBuffer;
            bool result = ReadBytes(Address, 1, out OutBuffer);
            if(result)
                Value = OutBuffer[0];
            return result;
        }
        
        /// <summary>
        /// Read a uint from the target platform
        /// </summary>
        /// <param name="Address"></param>
        /// <param name="Value"></param>
        /// <returns></returns>
        public bool ReadUInt(uint Address, out uint Value)
        {
            if (PlatformID == XPlatformType.PLATFORM_XBOX360)
            {
                try
                {
                    Value = JRPC.ReadUInt32(Jtag, Address);
                    return true;
                }
                catch
                {
                    Value = 0x0;
                    return false;
                }
            }
            Value = 0x0;
            byte[] buffer;
            bool result = ReadBytes(Address, sizeof(uint), out buffer);
            if (result)
                Value = BitConverter.ToUInt32(IsPC ? buffer : buffer.Reverse<byte>().ToArray<byte>(), 0);
            return result;
        }

    }
    /// <summary>
    /// Memory class for PC
    /// </summary>
    internal class Memory
    {
        #region Basic Stuff
        [DllImport("kernel32.dll")]
        private static extern Int32 ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, [In, Out] byte[] buffer, UInt32 size, out IntPtr lpNumberOfBytesWritten);
        [DllImport("kernel32.dll")]
        private static extern Int32 WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, [In, Out] byte[] buffer, UInt32 size, out IntPtr lpNumberOfBytesWritten);
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr OpenProcess(uint dwDesiredAccess, bool bInheritHandle, int dwProcessId);
        [DllImport("kernel32.dll")]
        private static extern Int32 GetLastError();

        public IntPtr pHandel;
        const int PROCESS_ALL_ACCESS = 0x1F0FFF;

        public bool ConnectProcess(int ProcessID)
        {
            pHandel = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
            if (pHandel.ToInt32() != 0x0)
                return true;
            return false;
        }

        private byte[] Read(int Address, int Length)
        {
            byte[] Buffer = new byte[Length];
            IntPtr Zero = IntPtr.Zero;
            ReadProcessMemory(pHandel, (IntPtr)Address, Buffer, (UInt32)Buffer.Length, out Zero);
            return Buffer;
        }
        private int Write(int Address, int Value, uint NewAccess = 0x0)
        {
            byte[] Buffer = BitConverter.GetBytes(Value);
            IntPtr Zero = IntPtr.Zero;
            VirtualProtectEx(pHandel, (IntPtr)Address, (UIntPtr)4, 0x40, out OldAccess);
            int result = WriteProcessMemory(pHandel, (IntPtr)Address, Buffer, (UInt32)Buffer.Length, out Zero);
            if(NewAccess == 0x0)
                VirtualProtectEx(pHandel, (IntPtr)Address, (UIntPtr)4, OldAccess, out NullOut);
            else
                VirtualProtectEx(pHandel, (IntPtr)Address, (UIntPtr)4, NewAccess, out NullOut);
            return result;
        }
        #endregion

        #region Write Functions (Integer & String)
        public int WriteInteger(int Address, int Value, uint NewAccess = 0x0)
        {
            return Write(Address, Value, NewAccess);
        }
        public void WriteString(int Address, string Text)
        {
            byte[] Buffer = new ASCIIEncoding().GetBytes(Text);
            IntPtr Zero = IntPtr.Zero;
            WriteProcessMemory(pHandel, (IntPtr)Address, Buffer, (UInt32)Buffer.Length, out Zero);
        }

        public MEMORY_BASIC_INFORMATION QueryProcess(IntPtr address)
        {
            MEMORY_BASIC_INFORMATION info;
            int result = VirtualQueryEx(pHandel, address, out info, (uint)Marshal.SizeOf(typeof(MEMORY_BASIC_INFORMATION)));
            if(result == 0)
            {
                string err = LastErrorToString();
                return info;
            }
            return info;
        }

        [DllImport("kernel32.dll")]
        static extern bool VirtualProtectEx(IntPtr hProcess, IntPtr lpAddress,
   UIntPtr dwSize, uint flNewProtect, out uint lpflOldProtect);

        [DllImport("kernel32.dll")]
        static extern int VirtualQueryEx(IntPtr hProcess, IntPtr lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);

        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION
        {
            public IntPtr BaseAddress;
            public IntPtr AllocationBase;
            public uint AllocationProtect;
            public IntPtr RegionSize;
            public uint State;
            public uint Protect;
            public uint Type;
        }

        public enum AllocationProtect : uint
        {
            PAGE_EXECUTE = 0x00000010,
            PAGE_EXECUTE_READ = 0x00000020,
            PAGE_EXECUTE_READWRITE = 0x00000040,
            PAGE_EXECUTE_WRITECOPY = 0x00000080,
            PAGE_NOACCESS = 0x00000001,
            PAGE_READONLY = 0x00000002,
            PAGE_READWRITE = 0x00000004,
            PAGE_WRITECOPY = 0x00000008,
            PAGE_GUARD = 0x00000100,
            PAGE_NOCACHE = 0x00000200,
            PAGE_WRITECOMBINE = 0x00000400
        }

        uint OldAccess;
        uint NullOut;
        public int WriteBytes(uint Address, byte[] Bytes, uint NewAccess = 0x0)
        {
            IntPtr Zero = IntPtr.Zero;
            bool success = VirtualProtectEx(pHandel, (IntPtr)Address, (UIntPtr)Bytes.Length, 0x40, out OldAccess);
            int result = WriteProcessMemory(pHandel, (IntPtr)Address, Bytes, (uint)Bytes.Length, out Zero);
            if(NewAccess == 0x0)
                VirtualProtectEx(pHandel, (IntPtr)Address, (UIntPtr)Bytes.Length, OldAccess, out NullOut);
            else
                VirtualProtectEx(pHandel, (IntPtr)Address, (UIntPtr)Bytes.Length, NewAccess, out NullOut);
            return result;
        }
        public void WriteNOP(int Address)
        {
            byte[] Buffer = new byte[] { 0x90, 0x90, 0x90, 0x90, 0x90 };
            IntPtr Zero = IntPtr.Zero;
            WriteProcessMemory(pHandel, (IntPtr)Address, Buffer, (UInt32)Buffer.Length, out Zero);
        }

        

        public void WriteEmpty(uint Address, int length)
        {
            uint addr = Address;
            for (int i = 0; i < length; i++)
            {
                WriteBytes(addr, new byte[] { 0x00 });
                addr += 1;
            }
        }

        public string LastErrorToString()
        {
            int err = GetLastError();
            switch (err)
            {
                case 487:
                    return "Attempted to access an invalid address in memory!";

                default:
                    return "UNKNOWN ERROR - " + err;
            }

        }


        #endregion

        #region Read Functions (Integer & String)
        public int ReadInteger(int Address, int Length = 4)
        {
            return BitConverter.ToInt32(Read(Address, Length), 0);
        }
        public string ReadString(int Address, int Length = 4)
        {
            return new ASCIIEncoding().GetString(Read(Address, Length));
        }
        public byte[] ReadBytes(int Address, int Length)
        {
            return Read(Address, Length);
        }

        public byte ReadByte(int Address)
        {
            return Read(Address, 1)[0];
        }

        public string ReadStr(int Address)
        {
            int block = 40;
            int addOffset = 0;
            string str = "";
            repeat:
            byte[] buffer = ReadBytes(Address + addOffset, block);
            str += Encoding.UTF8.GetString(buffer);
            addOffset += block;
            if (str.Contains('\0'))
            {
                int index = str.IndexOf('\0');
                string final = str.Substring(0, index);
                str = String.Empty;
                return final;
            }
            else
                goto repeat;
        }

        public string getName(int index)
        {
            return ReadStr(ReadInteger(0x16A3DF4 + index * 0xC, 4));
        }

        public int GetLength(int Address)
        {
            int length = 0;
            int addr = Address;
            while (ReadBytes(addr, 4).Take(4).SequenceEqual(new byte[] { 0, 0, 0, 0 }) == false)
            {
                length++;
                addr++;
            }

            return length;
        }

        public int pointer(int index)
        {
            return ReadInteger(0x16A3DFC + index * 0xC);
        }

        public int bufferAddr(int index)
        {
            return 0x16A3DFC + index * 0xC;
        }
        #endregion
    }
}
