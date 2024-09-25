using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExpressionItem
{
    public enum MARK{
        ENTER,  /*进入*/
        STOP,   /*等待*/
        LEAVE,  /*返回*/
        END     /*结束*/
    };
    public string   name;
    public float    initialValue;
    public float    targetValue;
    public float    value;
    public float    inTime;
    public float    outTime;
    public MARK     mark = MARK.ENTER;
}
