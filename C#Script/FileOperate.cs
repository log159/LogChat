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



}
