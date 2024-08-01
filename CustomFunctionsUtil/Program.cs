using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using GSXCompilerLib;

namespace CustomFunctionsUtil
{
    class Program
    {
        static void Main(string[] args)
        {
            if(args.Length > 0)
            {
                foreach(string file in args)
                {
                    try
                    {
                        GSXCompilerLib.GSXCustomFunctions.LoadCustomFunctions(file);
                        List<GSXCompilerLib.GSXCustomFunctions.GSXFunction> functions = GSXCompilerLib.GSXCustomFunctions.GetCustomFunctions();
                        foreach(var func in functions)
                        {
                            Console.WriteLine(func.FunctionName + "(" + func.MinimumParams + "," + func.MaximumParams + ")\n{\n");
                            Console.WriteLine("\t.ps3 [ target=0x" + func.PS3OverwriteTargetAddress.ToString("X") + " , bytecount=0x" + (func.PS3_PPCCode != null ? func.PS3_PPCCode.Length.ToString("X") + "" : "0") + " ]\n");
                            Console.WriteLine("\t.xb3 [ target=0x" + func.XB360OverwriteTargetAddress.ToString("X") + " , bytecount=0x" + (func.XB360_PPCCode != null ? func.XB360_PPCCode.Length.ToString("X") + "" : "0") + " ]\n");
                            Console.WriteLine("\t.rmp [ target=0x" + func.RedactedMPOverwriteTargetAddress.ToString("X") + " , bytecount=0x" + (func.Redacted_mp_x86Code != null ? func.Redacted_mp_x86Code.Length.ToString("X") + "" : "0") + " ]\n");
                            Console.WriteLine("\t.rzp [ target=0x" + func.RedactedZMOverwriteTargetAddress.ToString("X") + " , bytecount=0x" + (func.Redacted_zm_x86Code != null ? func.Redacted_zm_x86Code.Length.ToString("X") + "" : "0") + " ]\n");
                            Console.WriteLine("\t.smp [ target=0x" + func.SteamMPOverwriteTargetAddress.ToString("X") + " , bytecount=0x" + (func.Steam_mp_x86Code != null ? func.Steam_mp_x86Code.Length.ToString("X") + "" : "0") + " ]\n");
                            Console.WriteLine("\t.szm [ target=0x" + func.SteamZMOverwriteTargetAddress.ToString("X") + " , bytecount=0x" + (func.Steam_zm_x86Code != null ? func.Steam_zm_x86Code.Length.ToString("X") + "" : "0") + " ]\n");
                            Console.WriteLine("}\n");
                        }
                    }
                    catch(Exception e)
                    {
                        Console.WriteLine(e.GetBaseException().ToString());
                    }
                }
                
                Console.ReadKey(false);
            }
            else
            {
                //0x00912490 -- addargus
                //0x009124A8-- removeargus

                //R 0x00C76510 -- addargus
                //R 0x00C76528 -- removeargus

                //R Scr_GetInt 0x45D840
                //R Scr_AddInt 0x57AFF0
                GSXCompilerLib.GSXCustomFunctions.GSXFunction SetInt = new GSXCustomFunctions.GSXFunction()
                {
                    FunctionName                                = "setint",
                    MinimumParams                               = 2,
                    MaximumParams                               = 2,
                    PS3OverwriteTargetAddress                   = 0x00912490,
                    XB360OverwriteTargetAddress                 = 0x8202AF30,
                    RedactedMPOverwriteTargetAddress            = 0x00C76510,
                    RedactedZMOverwriteTargetAddress            = 0x00C6C078,
                    SteamMPOverwriteTargetAddress               = 0x00C76190,
                    SteamZMOverwriteTargetAddress               = 0x00C6C578,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_setint.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_setint.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_setint.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_setint.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_setint.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_setint.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction GetInt = new GSXCustomFunctions.GSXFunction()
                {
                    FunctionName                                = "getint",
                    MinimumParams                               = 1,
                    MaximumParams                               = 1,
                    PS3OverwriteTargetAddress                   = 0x009124A8,
                    XB360OverwriteTargetAddress                 = 0x8202AF48,
                    RedactedMPOverwriteTargetAddress            = 0x00C76528,
                    RedactedZMOverwriteTargetAddress            = 0x00C6C090,
                    SteamMPOverwriteTargetAddress               = 0x00C761A8,
                    SteamZMOverwriteTargetAddress               = 0x00C6C590,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_getint.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_getint.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_getint.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_getint.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_getint.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_getint.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction SetByte = new GSXCustomFunctions.GSXFunction()
                {
                    FunctionName                                = "setbyte",
                    MinimumParams                               = 2,
                    MaximumParams                               = 2,
                    PS3OverwriteTargetAddress                   = 0x00912508,
                    XB360OverwriteTargetAddress                 = 0x8202AFA8,
                    RedactedMPOverwriteTargetAddress            = 0x00C76588,
                    RedactedZMOverwriteTargetAddress            = 0x00C6C0F0,
                    SteamMPOverwriteTargetAddress               = 0x00C76208,
                    SteamZMOverwriteTargetAddress               = 0x00C6C5F0,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_setbyte.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_setbyte.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_setbyte.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_setbyte.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_setbyte.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_setbyte.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction GetByte = new GSXCustomFunctions.GSXFunction()
                {
                    FunctionName                                = "getbyte",
                    MinimumParams                               = 1,
                    MaximumParams                               = 1,
                    PS3OverwriteTargetAddress                   = 0x00912520,
                    XB360OverwriteTargetAddress                 = 0x8202AFC0,
                    RedactedMPOverwriteTargetAddress            = 0x00C765A0,
                    RedactedZMOverwriteTargetAddress            = 0x00C6C108,
                    SteamMPOverwriteTargetAddress               = 0x00C76220,
                    SteamZMOverwriteTargetAddress               = 0x00C6C608,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_getbyte.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_getbyte.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_getbyte.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_getbyte.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_getbyte.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_getbyte.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction SetFloat = new GSXCustomFunctions.GSXFunction()
                {
                    FunctionName                                = "setfloat",
                    MinimumParams                               = 2,
                    MaximumParams                               = 2,
                    PS3OverwriteTargetAddress                   = 0xD6C490,
                    XB360OverwriteTargetAddress                 = 0x82831FF0,
                    RedactedMPOverwriteTargetAddress            = 0xD4F378,
                    RedactedZMOverwriteTargetAddress            = 0xD44218,
                    SteamMPOverwriteTargetAddress               = 0xD4F348,
                    SteamZMOverwriteTargetAddress               = 0xD45228,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_setfloat.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_setfloat.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_setfloat.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_setfloat.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_setfloat.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_setfloat.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction GetFloat = new GSXCustomFunctions.GSXFunction()
                {
                    FunctionName                                = "getfloat",
                    MinimumParams                               = 1,
                    MaximumParams                               = 1,
                    PS3OverwriteTargetAddress                   = 0xD6C4A8,
                    XB360OverwriteTargetAddress                 = 0x82832008,
                    RedactedMPOverwriteTargetAddress            = 0xD4F390,
                    RedactedZMOverwriteTargetAddress            = 0xD44230,
                    SteamMPOverwriteTargetAddress               = 0xD4F360,
                    SteamZMOverwriteTargetAddress               = 0xD45240,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_getfloat.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_getfloat.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_getfloat.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_getfloat.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_getfloat.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_getfloat.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction RPC = new GSXCustomFunctions.GSXFunction() //getcontractrewardxp
                {
                    FunctionName                                = "__rpc__",
                    MinimumParams                               = 1,
                    MaximumParams                               = 1,
                    PS3OverwriteTargetAddress                   = 0xD6CA48,
                    XB360OverwriteTargetAddress                 = 0x82832020,
                    RedactedMPOverwriteTargetAddress            = 0xD4F930,
                    RedactedZMOverwriteTargetAddress            = 0xD447D0,
                    SteamMPOverwriteTargetAddress               = 0xD4F900,
                    SteamZMOverwriteTargetAddress               = 0xD457E0,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_rpc.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_rpc.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_rpc.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_rpc.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_rpc.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_rpc.bin"),
                };

                GSXCompilerLib.GSXCustomFunctions.GSXFunction is_redacted = new GSXCustomFunctions.GSXFunction() //getcontractrewardcp
                {
                    FunctionName                                = "is_redacted",
                    MinimumParams                               = 0,
                    MaximumParams                               = 0,
                    PS3OverwriteTargetAddress                   = 0xD6CA60,
                    XB360OverwriteTargetAddress                 = 0x82832038,
                    RedactedMPOverwriteTargetAddress            = 0xD4F948,
                    RedactedZMOverwriteTargetAddress            = 0xD447E8,
                    SteamMPOverwriteTargetAddress               = 0xD4F918,
                    SteamZMOverwriteTargetAddress               = 0xD457F8,
                    PS3_PPCCode                                 = ExtractResource("CustomFunctionsUtil.ps3_isredacted.bin"),
                    XB360_PPCCode                               = ExtractResource("CustomFunctionsUtil.xb360_isredacted.bin"),
                    Redacted_mp_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_mp_isredacted.bin"),
                    Redacted_zm_x86Code                         = ExtractResource("CustomFunctionsUtil.redacted_zm_isredacted.bin"),
                    Steam_mp_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_mp_isredacted.bin"),
                    Steam_zm_x86Code                            = ExtractResource("CustomFunctionsUtil.steam_zm_isredacted.bin"),
                };

                //matchend
                //setarchive
                //startparty
                //getplayerspawnid
                //getcontractstattype (!xb)
                //getcontractstatname (!xb)
                //getcontractrewardxp
                //getcontractrewardcp
                //getcontractrequirements
                //getcontractname
                //getcontractrequiredcount
                //getcontractresetconditions
                // call( address, param... ); any gsc function
                // rpc( address ); any function at all 
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(SetInt);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(GetInt);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(SetByte);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(GetByte);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(SetFloat);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(GetFloat);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(RPC);
                GSXCompilerLib.GSXCustomFunctions.AddCustomFunction(is_redacted);
                GSXCompilerLib.GSXCustomFunctions.SaveCustomFunctions("internals.bin");
            }
        }

        public static byte[] ExtractResource(String filename)
        {
            System.Reflection.Assembly a = System.Reflection.Assembly.GetExecutingAssembly();
            using (Stream resFilestream = a.GetManifestResourceStream(filename))
            {
                if (resFilestream == null) return null;
                byte[] ba = new byte[resFilestream.Length];
                resFilestream.Read(ba, 0, ba.Length);
                return ba;
            }
        }
    }
}
