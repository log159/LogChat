#define IS_LOGCHAT
//#define IS_LIVE2D_API

using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;


public class ExplainLoom : MonoBehaviour
{
    static bool LeftMouseDown = false;
    static bool RightMouseDown = false;
    static PointF RelativePosition = new PointF(0f, 0f);

    // 消息处理主循环
    void Update()
    {
        //鼠标消息
        MouseEvent();

        //Tcp 通信消息
        TcpEvent();
    }

    private void MouseEvent()
    {
        if (Input.GetMouseButtonDown(0))
        {
            print("鼠标左键被按下！");
            if (MouseInformation.ChangeColor.r == 0 && MouseInformation.ChangeColor.g == 0 && MouseInformation.ChangeColor.b == 0) { LeftMouseDown = false; }
            else LeftMouseDown = true;

            RelativePosition.X = Config.PositionXItem.Param - MouseInformation.WorldX;
            RelativePosition.Y = Config.PositionYItem.Param - MouseInformation.WorldY;

        }
        if (Input.GetMouseButtonUp(0))
        {
            print("鼠标左键被松开！");
            LeftMouseDown = false;
        }
        if (Input.GetMouseButtonDown(1))
        {
            print("鼠标右键被按下！");
            if (MouseInformation.ChangeColor.r == 0 && MouseInformation.ChangeColor.g == 0 && MouseInformation.ChangeColor.b == 0) { RightMouseDown = false; }
            else { RightMouseDown = true; }

        }
        if (Input.GetMouseButtonUp(1))
        {
            print("鼠标右键被松开！");
            RightMouseDown = false;
        }
        //Debug.Log(MouseInformation.ChangeColor.r +"  " +MouseInformation.ChangeColor.g+"   "+ MouseInformation.ChangeColor.b);
        if (LeftMouseDown)
        {
            Config.PositionXItem.Param = RelativePosition.X + MouseInformation.WorldX;
            Config.PositionYItem.Param = RelativePosition.Y + MouseInformation.WorldY;
            GetComponent<Model>().UpdateModelCondition();
        }
        if (RightMouseDown)
        {
#if IS_LOGCHAT
            Vector2 posv2 = new Vector2(Config.PositionXItem.Param, Config.PositionYItem.Param);
                posv2 = Camera.main.WorldToScreenPoint(posv2);
                string posStr = "Pos:" + posv2.x.ToString() + "," + posv2.y.ToString() + "," + MouseInformation.TrueX.ToString() + "," + MouseInformation.TrueY.ToString() + ";";
                SocketBehaviour.Singleton.Send(posStr);
                RightMouseDown = false;
#endif
        }
    }

    private void TcpEvent()
    {
        if (Loom.IsEmpty()) { return; }
        try
        {
            string input = Loom.Get(0);
            int keyIndex = input.IndexOf(':');
            int valIndex = input.IndexOf(';');
            // 确保找到了冒号和分号  
            if (keyIndex != -1 && valIndex != -1)
            {
                string value1 = input.Substring(0, keyIndex);
                string value2 = input.Substring(keyIndex + 1, valIndex - keyIndex - 1);

                HandleRequest(value1, value2);
            }
        }
        catch (Exception e)
        {
            Debug.Log("消息队列异常：" + e.Message);
        }
        Loom.RemoveList();
    }
    private void HandleRequest(string key, string value)
    {
        //模型切换初始化
        if (key == "Init")
        {
            GetComponent<Model>().InitModel();
        }
        //音频播放
        if (key == "Audio")
        {
            if (value.Substring(0, 4) == "null")
                PlayAudioFromFile.ClearAudioPathsList();
            else
                PlayAudioFromFile.AddAudioPathsList(value);
        }
        //Window信息
        if (key == "Window")
        {
            GameObject cameraObject = GameObject.Find("Camera");
            if (cameraObject != null)
            {
                try
                {
                    if (value == "wintop")
                        WindowSetting.SetWindowTopApha(TransparentWindow.enumWinStyle.WinTop);
                    else if (value == "winapha")
                        WindowSetting.SetWindowTopApha(TransparentWindow.enumWinStyle.WinApha);
                    else if (value == "wintopapha")
                        WindowSetting.SetWindowTopApha(TransparentWindow.enumWinStyle.WinTopApha);
                    else if (value == "winnotopnoapha")
                        WindowSetting.SetWindowTopApha(TransparentWindow.enumWinStyle.WinNoTopNoApha);
                }
                catch (Exception e)
                {
                    Debug.Log(e.Message);
                }
            }
        }

#if IS_LOGCHAT
        if (key == "Hwnd")
        {
            string[] parts = value.Split(',');
            if (parts.Length != 2)
            {
                Debug.LogError("Input string does not contain expected format.");
            }
            else
            {
                string itemname = parts[0].Trim();
                string itemval = parts[1].Trim();
                if (itemname == "dialog")
                {
                    if (int.Parse(itemval) != 0)
                    {
                        TransparentWindow.dialogHwnd = new IntPtr(int.Parse(itemval));
                        Debug.Log(TransparentWindow.dialogHwnd.ToString());
                    }
                    else
                    {
                        TransparentWindow.dialogHwnd = IntPtr.Zero;
                        Debug.Log("句柄无效！");
                    }
                }
            }
        }
#endif
        //参数信息修改
        if (key == "Config")
        {
            string[] parts = value.Split(',');
            if (parts.Length != 2)
            {
                Debug.LogError("Input string does not contain expected format.");
            }
            else
            {
                string itemname = parts[0].Trim();
                float itemval;
                if (float.TryParse(parts[1].Trim(), out itemval))
                {
                    switch (itemname)
                    {
                        //布尔参数---------------------------------------------------------------------------------------------------

                        //人物是否看向鼠标
                        case "IsLookMouse": Config.IsLookMouse = itemval > 0.5f ? true : false; break;
                        //浮点参数---------------------------------------------------------------------------------------------------

                        //人物看向鼠标速度参数
                        case "Damping": Config.DampingItem.SetParam(itemval); break;
                        //位置X
                        case "X": Config.PositionXItem.SetParam(itemval / 100); break;
                        //位置Y
                        case "Y": Config.PositionYItem.SetParam(itemval / 100); break;
                        //旋转RZ
                        case "RX": Config.RotationRXItem.SetParam(itemval); break;
                        //旋转RZ
                        case "RY": Config.RotationRYItem.SetParam(itemval); break;
                        //旋转RZ
                        case "RZ": Config.RotationRZItem.SetParam(itemval); break;
                        // 模型大小参数
                        case "ScaleScaleProportion": Config.ScaleProportionItem.SetParam(itemval); break;
                        //平均眨眼周期参数
                        case "Mean": Config.MeanItem.SetParam(itemval); break;
                        //最大偏差时间参数
                        case "MaximumDeviation": Config.MaximumDeviationItem.SetParam(itemval); break;
                        //眨眼速度参数
                        case "Timescale": Config.TimescaleItem.SetParam(itemval); break;
                        //音频增益参数
                        case "Gain": Config.GainItem.SetParam(itemval); break;
                        //音频平滑参数
                        case "Smoothing": Config.SmoothingItem.SetParam(itemval); break;
                        //其它参数
                        default: break;
                    }
                    Model model = GetComponent<Model>();
                    if (model != null) model.UpdateModelCondition();
                }
                else { Debug.LogError("Failed to parse value as float."); }
            }
        }

        //控件偏移
        if (key == "Item")
        {
            string[] parts = value.Split(',');
            if (parts.Length != 2) { Debug.LogError("Input string does not contain expected format."); }
            else
            {
                string itemname = parts[0].Trim();
                float itemval;
                if (float.TryParse(parts[1].Trim(), out itemval))
                {
                    itemval = itemval / (float)100.0;
                    Model model = GetComponent<Model>();
                    if (model != null) model.AddParamsList(itemname, itemval);
                }
                else { Debug.LogError("Failed to parse value as float."); }
            }
        }
        //控件渲染
        if (key == "Draw")
        {
            string[] parts = value.Split(',');
            if (parts.Length != 2) { Debug.LogError("Input string does not contain expected format."); }
            else
            {
                string itemname = parts[0].Trim();
                float itemval;
                if (float.TryParse(parts[1].Trim(), out itemval))
                {
                    Model model = GetComponent<Model>();
                    if (model != null) model.AddDrawsList(itemname, itemval);
                }
                else { Debug.LogError("Failed to parse value as float."); }
            }
        }
        //控件保存和置为设定态
        if (key == "InitItems")
        {
            string valueStr = value;
            //加载位置默认值
            if (valueStr == "default")
                GetComponent<Model>().InitModelParameters();
            //加载位置设定值
            else if (valueStr == "self")
                GetComponent<Model>().UpdateModelParameters();
            //加载渲染默认值
            else if (valueStr == "active")
                GetComponent<Model>().InitModelDrawables();
            //加载渲染设定值
            else if (valueStr == "appoint")
                GetComponent<Model>().UpdateModelDrawables();
        }
    }

}
