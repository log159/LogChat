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
    public static string ModelPath = null;
    public static string DirectoryPath = null;
    public static string PersonName = "";
    public static string ModelName = "Model";
    public static int ModelId = 0;

    /// <summary>
    /// 布尔参数
    /// </summary>
    //是否看向鼠标
    public static bool IsLookMouse = true;


    /// <summary>
    /// 常量信息
    /// </summary>
    //鼠标追踪控件 CubismLookParameter
    public static readonly string[] NeedAddCubismLookParameterObjectStrings = {
            "ParamAngleX","ParamAngleY","ParamAngleZ",
            "ParamBodyAngleX","ParamBodyAngleY","ParamBodyAngleZ",
            "ParamEyeBallX","ParamEyeBallY",
            "PARAM_ANGLE_X","PARAM_ANGLE_Y","PARAM_ANGLE_Z",
            "PARAM_BODY_ANGLE_X","PARAM_BODY_ANGLE_Y","PARAM_BODY_ANGLE_Z",
            "PARAM_EYE_BALL_X","PARAM_EYE_BALL_Y",
    };

    public static readonly Dictionary<string, List<string>> keyValueParameters = new Dictionary<string, List<string>>
    {
        {"PAX", new List<string> { "ParamAngleX", "PARAM_ANGLE_X" }},
        {"PAY", new List<string> { "ParamAngleY", "PARAM_ANGLE_Y" }},
        {"PAZ", new List<string> { "ParamAngleZ", "PARAM_ANGLE_Z" }},
        {"PBAX", new List<string> { "ParamBodyAngleX", "PARAM_BODY_ANGLE_X" }},
        {"PBAY", new List<string> { "ParamBodyAngleY", "PARAM_BODY_ANGLE_Y" }},
        {"PBAZ", new List<string> { "ParamBodyAngleZ", "PARAM_BODY_ANGLE_Z" }},
        {"PEBX", new List<string> { "ParamEyeBallX", "PARAM_EYE_BALL_X" }},
        {"PEBY", new List<string> { "ParamEyeBallY", "PARAM_EYE_BALL_Y" }},
    };
    //口型同步控件 CubismMouthParameter
    public static readonly string[] NeedAddCubismMouthParameterObjectStrings ={
        "ParamMouthOpenY","PARAM_MOUTH_OPEN_Y",
    };
    //自动眨眼控件 CubismEyeBlinkParameter
    public static readonly string[] NeedAddCubismEyeBlinkParameterObjectStrings ={
        "ParamEyeLOpen","ParamEyeROpen",
        "PARAM_EYE_L_OPEN","PARAM_EYE_R_OPEN",
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
    public static ParamItem MouthOpeningItem = new ParamItem("MouthOpening", 0f, new PointF(0f, 1f));
    //音频增益参数
    public static ParamItem GainItem = new ParamItem("Gain", 10f, new PointF(1f, 10f));
    //音频平滑参数
    public static ParamItem SmoothingItem = new ParamItem("Smoothing", 1f, new PointF(0f, 1f));

}
