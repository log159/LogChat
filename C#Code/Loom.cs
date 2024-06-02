using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Loom : MonoBehaviour
{
    private static List<string> HandleList= new List<string>();

    public static string Get(int id)
    {
        return HandleList[id];
    }
    public static void AddList(string str)
    {
        HandleList.Add(str);
    }
    public static bool IsEmpty()
    {
        return HandleList.Count == 0;
    }
    public static void RemoveList() 
    {
        if (Loom.IsEmpty()) { return; }
        HandleList.RemoveAt(0);
    }
}
