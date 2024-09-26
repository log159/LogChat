using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static TransparentWindow;

public class WindowSetting : MonoBehaviour
{
    public static void SetWindowTopApha(TransparentWindow.enumWinStyle enumWinStyle)
    {
        GameObject cameraObject = GameObject.Find("Camera");
        if (cameraObject != null)
        {
            TransparentWindow transparentWindow = cameraObject.GetComponent<TransparentWindow>();
            if (transparentWindow != null)
            {
                transparentWindow.SetWinStyle(enumWinStyle);
                transparentWindow.UpdateWindowStyle();
            }
        }
    }
    public static void SetWindowFps(int fps)
    {
        GameObject cameraObject = GameObject.Find("Camera");
        if (cameraObject != null)
        {
            TransparentWindow transparentWindow = cameraObject.GetComponent<TransparentWindow>();
            if (transparentWindow != null)
            {
                transparentWindow.SetFps(fps);
            }
        }
    }

}
