using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using UnityEngine;
using UnityEngine.UIElements;

public class ExplainLoom : MonoBehaviour
{
    static bool LeftMouseDown = false;
    static PointF RelativePosition=new PointF(0f,0f);

    // 消息处理主循环
    void Update()
    {

        //鼠标消息
        if (Input.GetMouseButtonDown(0))
        {
            print("鼠标左键被按下！");
            LeftMouseDown = true;

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
        }
        if (Input.GetMouseButtonDown(2))
        {
            print("鼠标中键被按下！");
        }
        if (Input.GetMouseButtonDown(3))
        {
            print("鼠标侧键被按下！");
        }

        //Debug.Log(MouseInformation.ChangeColor.r +"  " +MouseInformation.ChangeColor.g+"   "+ MouseInformation.ChangeColor.b);

        if (LeftMouseDown)
        {
            if (MouseInformation.ChangeColor.r == 0 && MouseInformation.ChangeColor.g == 0 && MouseInformation.ChangeColor.b == 0)
            {
            }
            else
            {

                Config.PositionXItem.Param = RelativePosition.X + MouseInformation.WorldX;
                Config.PositionYItem.Param = RelativePosition.Y + MouseInformation.WorldY;
                GetComponent<Model>().UpdateModelCondition();
            }
        }



        //Tcp 通信消息
        if (Loom.IsEmpty()) { return; }
        string handleString=Loom.Get(0);
        string keyString = "";
        string valueString = "";
        bool sel = false;
        for(int i = 0;i< handleString.Length; ++i)
        {
            if (sel == false){
                if (handleString[i] == ':'){
                    sel = true;
                    continue;
                }
            }

            if(sel==false)keyString += handleString[i];
            else valueString += handleString[i];
        }
        try
        {
            HandleRequest(keyString, valueString);
        }
        catch (Exception e)
        {
            Debug.Log("消息队列异常："+e.Message);
        }
        Loom.RemoveList();
    }
    private void HandleRequest(string key,string value)
    {
        //模型切换初始化
        if (key == "Init")
        {
            GetComponent<Model>().InitModel();
        }
        //音频播放
        if (key == "Audio")
        {
            GetComponentInChildren<PlayAudioFromFile>().PlayAudioByPath(value);
        }
        //Window信息
        if (key == "Window")
        {
            GameObject cameraObject = GameObject.Find("Camera");
            if (cameraObject != null)
            {
                try
            {
                    if (value[0] == 't')
                    {
                        WindowSetting.SetWindowTopApha(TransparentWindow.enumWinStyle.WinTop);

                    }
                    else if (value[0] == 'n')
                    {
                        WindowSetting.SetWindowTopApha(TransparentWindow.enumWinStyle.WinNoTopNoApha);

                    }
                }
                catch (Exception e)
                {
                    Debug.Log(e.Message);

                }

            }
        }


        //参数信息修改
        if (key == "Config")
        {
            string paramNameString = "";
            string paramValueString = "";
            float paramValue=0.0f;
            bool sel = false;
            for (int i=0;i<value.Length; ++i)
            {
                if (value[i] == ';')
                {
                    break;
                }
                if (sel == false)
                {
                    if (value[i] == ',')
                    {
                        sel = true;
                        continue;
                    }
                }
                if (sel == false) paramNameString += value[i];
                else paramValueString += value[i];
            }
            paramValue= float.Parse(paramValueString);

            switch (paramNameString)
            {
                //布尔参数---------------------------------------------------------------------------------------------------

                //人物是否看向鼠标
                case "IsLookMouse":Config.IsLookMouse = paramValue > 0.5f ? true : false;break;
                //浮点参数---------------------------------------------------------------------------------------------------

                //人物看向鼠标速度参数
                case "Damping":Config.DampingItem.SetParam(paramValue);break;
                //位置X
                case "X":Config.PositionXItem.SetParam(paramValue/100);break;
                //位置Y
                case "Y": Config.PositionYItem.SetParam(paramValue/100); break;
                //旋转RZ
                case "RX": Config.RotationRXItem.SetParam(paramValue); break;
                //旋转RZ
                case "RY": Config.RotationRYItem.SetParam(paramValue); break;
                //旋转RZ
                case "RZ": Config.RotationRZItem.SetParam(paramValue); break;
                // 模型大小参数
                case "ScaleScaleProportion":Config.ScaleProportionItem.SetParam(paramValue);break;
                //平均眨眼周期参数
                case "Mean": Config.MeanItem.SetParam(paramValue);break;
                //最大偏差时间参数
                case "MaximumDeviation":Config.MaximumDeviationItem.SetParam(paramValue);break;
                //眨眼速度参数
                case "Timescale":Config.TimescaleItem.SetParam(paramValue);break;
                //音频增益参数
                case "Gain": Config.GainItem.SetParam(paramValue);break;
                //音频平滑参数
                case "Smoothing":Config.SmoothingItem.SetParam(paramValue);break;
                //其它参数
                default:break;
            }

            GetComponent<Model>().UpdateModelCondition();
        }

        //控件信息修改
        if (key == "Item")
        {
            string itemNameString = "";
            string itemValueString = "";
            float itemValue = 0.0f;
            bool sel = false;
            for (int i = 0; i < value.Length; ++i)
            {
                if (value[i] == ';')
                {
                    break;
                }
                if (sel == false)
                {
                    if (value[i] == ',')
                    {
                        sel = true;
                        continue;
                    }
                }
                if (sel == false) itemNameString += value[i];
                else itemValueString += value[i];
            }
            itemValue = float.Parse(itemValueString);
            itemValue = itemValue / (float)100.0;
            GetComponent<Model>().AddParamsList(itemNameString,itemValue);


        }
        //控件渲染
        if(key == "Draw")
        {
            string itemNameString = "";
            string itemValueString = "";
            float itemValue = 0.0f;
            bool sel = false;
            for (int i = 0; i < value.Length; ++i)
            {
                if (value[i] == ';')
                {
                    break;
                }
                if (sel == false)
                {
                    if (value[i] == ',')
                    {
                        sel = true;
                        continue;
                    }
                }
                if (sel == false) itemNameString += value[i];
                else itemValueString += value[i];
            }
            itemValue = float.Parse(itemValueString);


            GetComponent<Model>().AddDrawsList(itemNameString, itemValue);

        }


        //控件保存和置为设定态
        if (key == "InitItems")
        {
            string valueStr = "";
            if (value.IndexOf(";") == -1)
            {
            }
            else
            {
                valueStr = value.Substring(0, value.IndexOf(";"));
                //加载位置默认值
                if (valueStr == "default")
                {
                    GetComponent<Model>().InitModelParameters();
                }
                //加载位置设定值
                else if (valueStr == "self")
                {
                    GetComponent<Model>().UpdateModelParameters();
                }
                //加载渲染默认值
                else if (valueStr == "active"){
                    GetComponent<Model>().InitModelDrawables();
                }
                //加载渲染设定值
                else if(valueStr == "appoint")
                {
                    GetComponent<Model>().UpdateModelDrawables();
                }

            }

        }
    }


}
