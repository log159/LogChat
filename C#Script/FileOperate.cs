using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UnityEngine;
using UnityEngine.Networking;

public class FileOperate : MonoBehaviour
{

    public static string GetModelJsonPath()
    {

        string path = System.Environment.CurrentDirectory + "/Model/STARTMODELPATH.txt";
        string[] strs = File.ReadAllLines(path);
        return strs[0];
    }
    public static string GetModelPath()
    {
        return "";
    }
    public static Dictionary<string, Dictionary<string, string>> ParseIniFile(string filePath)
    {
        Dictionary<string, Dictionary<string, string>> iniData = new Dictionary<string, Dictionary<string, string>>();

        using (StreamReader reader = new StreamReader(filePath))
        {
            string section = "";
            Dictionary<string, string> sectionData = new Dictionary<string, string>();

            while (!reader.EndOfStream)
            {
                string line = reader.ReadLine().Trim();

                if (line.StartsWith("[") && line.EndsWith("]"))
                {
                    // 开始一个新的节
                    section = line.Substring(1, line.Length - 2);
                    sectionData = new Dictionary<string, string>();
                    iniData[section] = sectionData;
                }
                else if (line.Contains("="))
                {
                    // 解析键值对
                    string[] parts = line.Split('=');
                    string key = parts[0].Trim();
                    string value = parts[1].Trim();
                    sectionData[key] = value;
                }
            }
        }

        return iniData;
    }


}
