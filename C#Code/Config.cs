using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using UnityEngine;

public class Config : MonoBehaviour
{

    const float MAX = 99999f;
    const float MIN = -99999f;

    private static Config instance = null;
    public static Config Instance
    {
        get
        {
            if (instance == null)
            {
                instance = new Config();
            }
            return instance;
        }
    }

    /// <summary>
    /// 基本信息
    /// </summary>
    public static string ModelPath  = null;
    public static string DirectoryPath = null;
    public static string PersonName = "";
    public static string ModelName  = "Model";
    public static int    ModelId    = 0;

    /// <summary>
    /// 布尔参数
    /// </summary>
    //是否看向鼠标
    public static bool IsLookMouse = true;


    /// <summary>
    /// 常量信息
    /// </summary>
    //鼠标追踪控件名数组
    public static readonly string[] NeedAddCubismLookParameterObjectStrings = {
            "ParamAngleX","ParamAngleY","ParamAngleZ",
            "ParamBodyAngleX","ParamBodyAngleY","ParamBodyAngleZ",
            "ParamEyeBallX","ParamEyeBallY"
    };

    /// <summary>
    /// Config信息
    /// </summary>
    // 人物看向鼠标速度参数
    public static ParamItem DampingItem = new ParamItem("Damping", 0.15f, new PointF(0f, 2f));
    // 模型缩放参数
    public static ParamItem ScaleProportionItem = new ParamItem("ScaleProportion", 3f, new PointF(0.1f, 100f));
    //模型位置参数
    public static ParamItem PositionXItem = new ParamItem("Position", 0f, new PointF(MIN, MAX));
    public static ParamItem PositionYItem = new ParamItem("Position", 0f, new PointF(MIN, MAX));

    public static ParamItem RotationRXItem = new ParamItem("Rotation", 0f, new PointF(MIN, MAX));
    public static ParamItem RotationRYItem = new ParamItem("Rotation", 0f, new PointF(MIN, MAX));
    public static ParamItem RotationRZItem = new ParamItem("Rotation", 0f, new PointF(MIN, MAX));



    //主轴物理参数
    public static ParamItem ParamAngleItem = new ParamItem("ParamAngle", 30f, new PointF(0f, 30f));
    //身体轴物理参数
    public static ParamItem ParamBodyAngleItem = new ParamItem("ParamBodyAngle", 10f, new PointF(0f, 30f));
    //眼睛轴物理参数
    public static ParamItem ParamEyeBallItem = new ParamItem("ParamEyeBall", 1f, new PointF(0f, 30f));
    //平均眨眼周期参数
    public static ParamItem MeanItem = new ParamItem("Mean", 2.5f, new PointF(1f, 10f));
    //最大偏差时间参数
    public static ParamItem MaximumDeviationItem = new ParamItem("MaximumDeviation", 2f, new PointF(0.5f, 5f));
    //眨眼速度参数
    public static ParamItem TimescaleItem = new ParamItem("Timescale", 10f, new PointF(1f, 20f));
    //嘴型最大值参数
    public static ParamItem MouthOpeningItem = new ParamItem("MouthOpening", 1f, new PointF(0f, 1f));
    //音频增益参数
    public static ParamItem GainItem = new ParamItem("Gain", 10f, new PointF(1f, 10f));
    //音频平滑参数
    public static ParamItem SmoothingItem = new ParamItem("Smoothing", 1f, new PointF(0f, 1f));




    ///// <summary>
    ///// Parameters控件协调
    ///// </summary>

    //private static Dictionary<string, Vector2> InitParametersDictionary = new Dictionary<string, Vector2>();
    //private static Dictionary<string, float> InitParametersAmplitudeDictionary = new Dictionary<string, float>();
    //private static Dictionary<string, float> InitParametersFrequencyDictionary = new Dictionary<string, float>();

    ////string 控件名 Vector2 控件范围
    //private static Dictionary<string,Vector2> ParametersDictionary=new Dictionary<string, Vector2>();
    ////float 控件振幅
    //private static Dictionary<string,float> ParametersAmplitudeDictionary=new Dictionary<string,float>();
    ////float 控件频率
    //private static Dictionary<string,float> ParametersFrequencyDictionary = new Dictionary<string,float>();

    ///// <summary>
    ///// Parts控件协调
    ///// </summary>

    //private static List<string> InitPartsDictionary = new List<string>();
    //private static Dictionary<string,bool> InitPartsBoolDictionary = new Dictionary<string,bool>();

    ////string 控件名 
    //private static List<string> PartsDictionary = new List<string>();
    ////bool 控件显示与否
    //private static Dictionary<string, bool> PartsBoolDictionary = new Dictionary<string, bool>();


    ///// <summary>
    ///// Drawables控件协调
    ///// </summary>

    //private static List<string> InitDrawablesDictionary = new List<string>();
    //private static Dictionary<string, bool> InitDrawablesBoolDictionary = new Dictionary<string, bool>();

    ////记录所有Drawables控件的名称 string 控件名
    //private static  List<string> DrawablesDictionary = new List<string>();
    ////bool 控件显示与否
    //private static Dictionary<string, bool> DrawablesBoolDictionary = new Dictionary<string, bool>();


    public static void SetConfigLookParam(float pa,float pb,float pe)
    {
        //ParamAngle = pa;
        //ParamBodyAngle = pb;
        //ParamEyeBall = pe;
    }

    private static void InitSize()
    {
        //ScaleVector3 = InitScaleVector3;

    }
    private static void InitParam()
    {

        //ParamAngle = InitParamAngle;
        //ParamBodyAngle = InitParamBodyAngle;
        //ParamEyeBall = InitParamEyeBall;
    }

    private static void DestroyConfig()
    {
        

    }





}
