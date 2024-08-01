using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;


namespace FixAndCompressOffsets
{
    class Program
    {
        private static string DBNAME = "pc_inj_adresses.db";
        private static Dictionary<string, string> dbdata;
        static void Main(string[] args)
        {
            //ORDER: ZM,MP,RZM,RMP
            List<string> PC_ZM = File.ReadAllLines("PLATFORM_PC_ZM.txt").ToList();
            List<string> PC_MP = File.ReadAllLines("PLATFORM_PC_MP.txt").ToList();
            List<string> PC_R_ZM = File.ReadAllLines("PLATFORM_PC_REDACTED_ZM.txt").ToList();
            List<string> PC_R_MP = File.ReadAllLines("PLATFORM_PC_REDACTED_MP.txt").ToList();
            dbdata = new Dictionary<string, string>();
            ParseAddresses(PC_ZM, "PCZM");
            ParseAddresses(PC_MP, "PCMP");
            ParseAddresses(PC_R_ZM, "PCRZM");
            ParseAddresses(PC_R_MP, "PCRRMP");
            string final = "";
            foreach(string key in dbdata.Keys)
            {
                final += "@" + key + "#" + dbdata[key];
            }
            File.WriteAllText(DBNAME, final);
        }

        static void ParseAddresses(List<string> lines, string id)
        {
            for(int i = 0; i * 5 < lines.Count; i++)
            {
                string name = lines[i * 5 + 0].Replace("\n", "").Replace("\r", "").Replace("Name: ", "").ToLower();
                string buffer = lines[i * 5 + 1].Replace("\n", "").Replace("\r", "").Replace("Pointer: ", "").Replace("Pointer Address: ", "").ToLower();
                string ptr = lines[i * 5 + 2].Replace("\n", "").Replace("\r", "").Replace("Buffer: ", "").Replace("Buffer Address: ", "").ToLower();
                if(!dbdata.ContainsKey(name))
                {
                    dbdata[name] = "";
                }
                dbdata[name] += id + ":" + buffer + ":" + ptr + ";";
            }
        }
    }
}
