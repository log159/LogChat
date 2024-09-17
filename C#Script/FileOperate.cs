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
    //读取 INI 文件
    public static Dictionary<string, Dictionary<string, string>> ParseIniFile(string filePath)
    {
        Dictionary<string, Dictionary<string, string>> iniData = new Dictionary<string, Dictionary<string, string>>();

        if (!FileExists(filePath))
        {
            Debug.Log("文件不存在");
            return iniData;
        }

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

    // 保存 INI 文件
    public static void WriteIniFile(Dictionary<string, Dictionary<string, string>>data,string filePath)
    {
        if (!FileExists(filePath))
        {
            FileStream fs = File.Create(filePath);
            fs.Close();
        }
        Dictionary<string, Dictionary<string, string>> willData = ParseIniFile(filePath);
        foreach (var kvp in data)
        {
            if (willData.ContainsKey(kvp.Key))
                foreach (var innerKvp in kvp.Value)
                    willData[kvp.Key][innerKvp.Key] = innerKvp.Value;
            else
                willData[kvp.Key] = new Dictionary<string, string>(kvp.Value);
        }
        StringBuilder sb = new StringBuilder();
        foreach (var section in willData)
        {
            sb.AppendLine($"[{section.Key}]");
            foreach (var keyValue in section.Value)
            {
                sb.AppendLine($"{keyValue.Key}={keyValue.Value}");
            }
        }
        File.WriteAllText(filePath, sb.ToString(), Encoding.UTF8);
    }

    //写文件
    public static void WriteAllText(string filePath,string data)
    {
        File.WriteAllText(filePath, data, Encoding.UTF8);
    }
    //判断文件存在
    public static bool FileExists(string filePath)
    {
        return File.Exists(filePath);
    }

    //文件名提取
    public static string GetFileNameWithoutExtension(string filePath)
    {
        string fileNameWithExtension = Path.GetFileName(filePath);
        string fileNameWithoutExtension = Path.GetFileNameWithoutExtension(fileNameWithExtension);
        return fileNameWithoutExtension;
    }
}
