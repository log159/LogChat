using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Live2D.Cubism.Core;
using System.Timers;
using Live2D.Cubism.Framework;
using System.Data.Common;

public class ParameterItem : Object
{
    public enum MOVERULE
    {
        KEEP,/*无更新保持干涉*/
        DEFAULT/*向默认位置刷新干涉*/
    }

    /// <summary>
    /// 可控协调
    /// </summary>

    //目标位置百分比
    [Range(0f, 1f)]
    private float MoveValuePercentag = 0;
    //速度百分比
    [Range(0f, 0.1f)]
    private const float MaxMoveSpeedPercentage = 0.01f;
    private float MoveSpeedPercentage = 0.001f;
    //加速度百分比
    //[Range(0f,0.01f)]
    //private float Acceleration = 0;

    /// <summary>
    /// 内部协调
    /// </summary>
    //引用到的控件
    private CubismParameter Cub = null;
    //刷新规则
    private MOVERULE MoveUpdateRule = ParameterItem.MOVERULE.KEEP;


    public ParameterItem(CubismParameter cubismParameter)
    {
        Cub = cubismParameter;
        if (Cub == null)
        {
            Debug.LogError("CubismParameter Is Null");
            return;
        }
        SendNewMoveValuePercentag();

    }



    public void InitCubismParameter()
    {
        if (Cub != null)
        {
            Cub.Value = Cub.DefaultValue;
        }
    }

    public CubismParameter GetCubismParameter()
    {
        return Cub;
    }

    public void SendNewMoveValuePercentag()
    {

        float lfPercentag = (Cub.DefaultValue - Cub.MinimumValue) / (Cub.MaximumValue - Cub.MinimumValue);

        float nrmalDistribution = (float)MathFunction.GetNormalDistribution() / 100f;
        if (lfPercentag >= Random.Range(0f, 1f))
        {
            MoveValuePercentag = lfPercentag - (lfPercentag * nrmalDistribution);

        }
        else
        {
            MoveValuePercentag = lfPercentag + ((1f - lfPercentag) * nrmalDistribution);

        }

        MoveSpeedPercentage = MaxMoveSpeedPercentage * (float)MathFunction.GetNormalDistribution() / 100f;

    }
    public void SetMoveUpdateRule(MOVERULE moveUpdateRule)
    {
        this.MoveUpdateRule = moveUpdateRule;
    }

    public void SetMoveValuePercentag(float val)
    {
        MoveValuePercentag = val;
    }
    public void SetMoveSpeedPercentage(float val)
    {
        MoveSpeedPercentage = val;
    }

    public void SetCubismParameterValue(float value)
    {
        Cub.BlendToValue(CubismParameterBlendMode.Additive, value);
    }


    public float GetDistance(float lh, float rh)
    {
        return Mathf.Abs(lh - rh);
    }
    public void MoveUpdate()
    {

        if (MoveUpdateRule == MOVERULE.KEEP)
        {

        }
        else if (MoveUpdateRule == MOVERULE.DEFAULT)
        {
            float thisPercentag = ((Cub.Value - Cub.MinimumValue)) / (Cub.MaximumValue - Cub.MinimumValue);
            if (GetDistance(thisPercentag, MoveValuePercentag) <= MoveSpeedPercentage)
            {
                SendNewMoveValuePercentag();

            }
            else if (thisPercentag < MoveValuePercentag)
            {
                Cub.Value = (Cub.Value + (MoveSpeedPercentage * (Cub.MaximumValue - Cub.MinimumValue)));
            }
            else if (thisPercentag > MoveValuePercentag)
            {
                Cub.Value = (Cub.Value - (MoveSpeedPercentage * (Cub.MaximumValue - Cub.MinimumValue)));

            }
        }

    }






}
