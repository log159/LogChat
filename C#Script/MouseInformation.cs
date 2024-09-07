using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class MouseInformation : MonoBehaviour
{
    public static float X { get; private set; }
    public static float Y { get; private set; }
    public static float TrueX { get; private set; }
    public static float TrueY { get; private set; }
    public static float WorldX { get; private set; }
    public static float WorldY { get; private set; }
    public static float TrueWorldX { get; private set; }
    public static float TrueWorldY { get; private set; }

    public static readonly Color InitColor = new Color(0,0,0);
    public static Color ChangeColor;

    bool IsEffective = true;

    private void Update()
    {
        // 获取鼠标在屏幕上的位置
        Vector3 mousePosition = Input.mousePosition;
        IsEffective = true;
        TrueX = mousePosition.x;
        TrueY = mousePosition.y;
        // 将屏幕上的位置转换为世界坐标
        Vector3 trueWorldPosition = Camera.main.ScreenToWorldPoint(mousePosition);
        TrueWorldX = trueWorldPosition.x;
        TrueWorldY = trueWorldPosition.y;

        if (mousePosition.x >= Screen.width) { mousePosition.x = Screen.width; IsEffective = false; }
        if (mousePosition.y >= Screen.height) { mousePosition.y = Screen.height; IsEffective = false; }
        if (mousePosition.x <= 0) { mousePosition.x = 0; IsEffective = false; }
        if (mousePosition.y <= 0) { mousePosition.y = 0; IsEffective = false; }
        // 将屏幕上的位置转换为世界坐标
        Vector3 worldPosition = Camera.main.ScreenToWorldPoint(mousePosition);

        X = mousePosition.x;
        Y = mousePosition.y;
        WorldX = worldPosition.x;
        WorldY = worldPosition.y;

        // 输出鼠标的实时位置
        //Debug.Log("Mouse Position:  x = " + worldPosition.x + " y = " + worldPosition.y);

        StartCoroutine(CaptureScreenshot());

    }
    IEnumerator CaptureScreenshot()
    {
        yield return new WaitForEndOfFrame();
        Texture2D m_texture = new Texture2D(Screen.width, Screen.height, TextureFormat.RGB24, false);
        // 读取Rect范围内的像素并存入纹理中
        Rect rect = new Rect(0, 0, Screen.width, Screen.height);
        m_texture.ReadPixels(rect, 0, 0);

        // 实际应用纹理
        m_texture.Apply();
        if (IsEffective == true) { ChangeColor = m_texture.GetPixel((int)Input.mousePosition.x, (int)Input.mousePosition.y); }
        else { ChangeColor = InitColor; }

        Destroy(m_texture);

        StopCoroutine(CaptureScreenshot());
    }
}
