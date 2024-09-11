using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Live2D.Cubism.Core;
using Unity.VisualScripting;
using System.Linq;

public class Harmonic : MonoBehaviour
{
    private static Dictionary<string, ParameterItem> ParameterDictionary = new Dictionary<string, ParameterItem>();

    //完全偏移控件
    private static HashSet<string> HashSetExcursion = new HashSet<string>();
    //偏移独占控件
    private static HashSet<string> HashSetExcursionUnique = new HashSet<string>();
    //特殊关联控件
    private static HashSet<string> HashSetExcursionConnection = new HashSet<string>();

    //心情对应的单次谐波控件
    private static Dictionary<int, List<string>> FeelingDictionary = new Dictionary<int, List<string>>();


    private void Init()
    {
        CubismModel cubismModel = this.FindCubismModel();
        if (cubismModel == null)
        {
            Debug.LogError("CubismModel Is Null");
            return;
        }
        CubismParameter[] cubismParameters = cubismModel.Parameters;
        if (cubismParameters == null)
        {
            Debug.LogError("CubismModel Parameters Or  CubismDrawables Is Null");
            return;
        }
        Harmonic.InitParameterDictionary(cubismParameters);
    }

    // 静态构造函数  
    static void InitStatic()
    {
        HashSetExcursion.Add("ParamLeftHand"/*[手掌 - 左]*/);
        HashSetExcursion.Add("ParamRightHand"/*[手掌 - 右]*/);

        //HashSetExcursion.Add("ParamAngleX"/*[主轴角X]*/);
        //HashSetExcursion.Add("ParamAngleY"/*[主轴角Y]*/);
        //HashSetExcursion.Add("ParamAngleZ"/*[主轴角Z]*/);
        HashSetExcursion.Add("ParamBodyAngleX"/*[身体轴角X]*/);
        HashSetExcursion.Add("ParamBodyAngleY"/*[身体轴角Y]*/);
        HashSetExcursion.Add("ParamBodyAngleZ"/*[身体轴角Z]*/);

        //HashSetExcursionUnique.Add("ParamKirakira"/*[两眼泛光]*/);
        //HashSetExcursionUnique.Add("ParamFuee"/*[眯眼]*/);
        //HashSetExcursionUnique.Add("ParamHeartEye"/*[心眼]*/);
        //HashSetExcursionUnique.Add("ParamWhiteEye"/*[白眼]*/);
        //HashSetExcursionUnique.Add("Param2"/*[坏笑眼]*/);
        //HashSetExcursionUnique.Add("ParamEyeMaxOpen"/*[睁大眼]*/);
        //HashSetExcursionUnique.Add("ParamTear"/*眼泪*/);

        //HashSetExcursionConnection.Add("ParamShoulderL"/*[手臂 - 左]*/);
        //HashSetExcursionConnection.Add("ParamShoulderR"/*[手臂 - 右]*/);
        //HashSetExcursionConnection.Add("ParamLeftElbow"/*[手肘 - 左]*/);
        //HashSetExcursionConnection.Add("ParamRightElbow"/*[手肘 - 右]*/);
        //HashSetExcursionConnection.Add("ParamLeftWrist"/*[手腕 - 左]*/);
        //HashSetExcursionConnection.Add("ParamRightWrist"/*[手腕 - 右]*/);
        //HashSetExcursionConnection.Add("ParamLeftHandChange"/*[左手变化]*/);
        //HashSetExcursionConnection.Add("ParamRightHandChange"/*[右手变化]*/);
        //HashSetExcursionConnection.Add("ParamEyeLOpen"/*[睁左眼]*/);
        //HashSetExcursionConnection.Add("ParamEyeROpen"/*[睁右眼]*/);
        //HashSetExcursionConnection.Add("ParamEyebrowL"/*[左眼眉毛]*/);
        //HashSetExcursionConnection.Add("ParamEyebrowR"/*[右眼眉毛]*/);
        //HashSetExcursionConnection.Add("ParamMouthForm"/*[嘴的状态]*/);
        //HashSetExcursionConnection.Add("ParamEyeROpen"/*左眼开闭*/);
        //HashSetExcursionConnection.Add("ParamEyeLOpen"/*左眼开闭*/);




        HashSetExcursion.Add("ParamLeftWrist"/*[手腕 - 左]*/);
        HashSetExcursion.Add("ParamRightWrist"/*[手腕 - 右]*/);
        HashSetExcursionConnection.Add("ParamLeftHandChange"/*[左手变化]*/);
        HashSetExcursionConnection.Add("ParamRightHandChange"/*[右手变化]*/);
        HashSetExcursionConnection.Add("ParamEyeLOpen"/*[睁左眼]*/);
        HashSetExcursionConnection.Add("ParamEyeROpen"/*[睁右眼]*/);
        HashSetExcursionConnection.Add("ParamEyebrowL"/*[左眼眉毛]*/);
        HashSetExcursionConnection.Add("ParamEyebrowR"/*[右眼眉毛]*/);
        HashSetExcursionConnection.Add("ParamMouthForm"/*[嘴的状态]*/);
        HashSetExcursionConnection.Add("ParamEyeROpen"/*左眼开闭*/);
        HashSetExcursionConnection.Add("ParamEyeLOpen"/*左眼开闭*/);

        ////快乐 0
        //List<string> list0 = new List<string>();list0.Add("ParamKirakira");list0.Add("ParamFuee");list0.Add("Param2");
        ////悲伤 1
        //List<string> list1 = new List<string>();list1.Add("ParamEyeMaxOpen");list1.Add("ParamTear");
        ////愤怒 2
        //List<string> list2 = new List<string>();list2.Add("ParamEyeMaxOpen");
        ////恐惧 3
        //List<string> list3 = new List<string>();list3.Add("ParamEyeMaxOpen");list3.Add("ParamTear");
        ////惊奇 4
        //List<string> list4 = new List<string>();list4.Add("ParamKirakira"); list4.Add("ParamWhiteEye");list4.Add("ParamEyeMaxOpen");
        ////疑惑 5
        //List<string> list5 = new List<string>();list5.Add("ParamWhiteEye");
        ////羞耻 6
        //List<string> list6 = new List<string>();list6.Add("ParamFuee"); list6.Add("ParamHeartEye");list6.Add("ParamTear");


        //FeelingDictionary.Add(0, list0);
        //FeelingDictionary.Add(1, list1);
        //FeelingDictionary.Add(2, list2);
        //FeelingDictionary.Add(3, list3);
        //FeelingDictionary.Add(4, list4);
        //FeelingDictionary.Add(5, list5);
        //FeelingDictionary.Add(6, list6);


    }

    //谐波列表 ParameterDictionary 初始化
    public static void InitParameterDictionary(CubismParameter[] cubismParameters)
    {

        for (int i = 0; i < cubismParameters.Length; i++)
        {
            CubismParameter cub = cubismParameters[i];
            if (cubismParameters[i] != null)
            {

                if (HashSetExcursion.Contains(cub.name))
                {

                    ParameterItem parameterItem = new ParameterItem(cub);
                    parameterItem.SetMoveUpdateRule(ParameterItem.MOVERULE.DEFAULT);

                    Harmonic.AddHarmonicDictionary(parameterItem);
                }
            }
        }
    }
    //添加谐波到 ParameterDictionary
    public static void AddHarmonicDictionary(ParameterItem parameterItem)
    {
        if (ParameterDictionary.ContainsKey(parameterItem.GetCubismParameter().name) == true) { return; }
        ParameterDictionary.Add(parameterItem.GetCubismParameter().name, parameterItem);

    }

    ////派出单次谐波
    //public static void SendHarmonicOnce()
    //{
    //    foreach (var item in ParameterDictionary)
    //    {
    //        if (HashSetExcursionUnique.Contains(item.Value.GetCubismParameter().name))
    //        {
    //            item.Value.SetMoveUpdateRule(ParameterItem.MOVERULE.DEFAULT);
    //        }
    //    }

    //    if(Config.Feeling >= FeelingDictionary.Count)
    //    {
    //        Debug.LogError("Config Feeling Index 越界");
    //        return;
    //    }
    //    List<string> feelingList = FeelingDictionary[Config.Feeling];
    //    string posStr = feelingList[Random.Range(0, feelingList.Count)];

    //    foreach (var item in ParameterDictionary)
    //    {
    //        ParameterItem parameterItem = item.Value;
    //        if (HashSetExcursionUnique.Contains(parameterItem.GetCubismParameter().name))
    //        {
    //            if (parameterItem.GetCubismParameter().name == posStr)
    //            {
    //                parameterItem.InitCubismParameter();
    //                parameterItem.SetMoveUpdateRule(ParameterItem.MOVERULE.SINGLE);
    //                Debug.Log("SendHarmonicOnce : "+ parameterItem.GetCubismParameter().name);
    //                break;
    //            }

    //        }
    //    }
    //}


    //谐波刷新
    private void LateUpdate()
    {
        if (ParameterDictionary == null)
        {
            return;
        }
        if (ParameterDictionary.Count <= 0)
        {
            return;
        }

        foreach (var item in ParameterDictionary)
        {
            item.Value.MoveUpdate();
        }

    }
}

