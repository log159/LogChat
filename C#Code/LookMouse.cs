using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Live2D.Cubism.Framework.LookAt;
using UnityEngine.UIElements;

public class LookMouse : MonoBehaviour, ICubismLookTarget
{
    private bool IsLookMouse = true;

    public void SetLookMouse(bool isLookMouse)
    {
        IsLookMouse = isLookMouse;

    }
    public Vector3 GetPosition()
    {
        if (true == IsLookMouse)
        {
            Vector3 targetPosition = Vector3.zero;
            targetPosition.x = MouseInformation.TrueWorldX;
            targetPosition.y = MouseInformation.TrueWorldY;
            return targetPosition;
        }
        else
        {
            return Model.Live2dObjectTransform.position;
            //return Vector3.zero;
        }

    }

    public bool IsActive()
    {
        return true;
    }

}
