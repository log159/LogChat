using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using UnityEngine;

public class ParamItem : Object
{
    public string Name;
    public float Param;
    public float InitParam;
    public PointF ParamRange;

    public ParamItem(string name, float param,PointF pointf) {
        Name = name;
        InitParam = param;
        Param = InitParam;
        ParamRange = new PointF(pointf.X,pointf.Y);
    }
    public void SetParam(float param)
    {
        if(param< ParamRange.X) { param = ParamRange.X; }
        if(param> ParamRange.Y) { param = ParamRange.Y; }
        Param = param;
    }

}
