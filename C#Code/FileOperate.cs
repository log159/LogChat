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

        string path = System.Environment.CurrentDirectory + "\\model\\STARTMODELPATH.txt";
        //逐行读取返回的为数组数据
        string[] strs = File.ReadAllLines(path);
        return strs[0];
    }



}
