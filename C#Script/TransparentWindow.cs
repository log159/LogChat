/*这个宏定义后会使得程序无法在Unity编辑器调试，导出后直接运行看到窗口透明效果*/
//#define IS_TRANSPARENT

using UnityEngine;
using System.Collections;
using System;
using System.Runtime.InteropServices;
using System.IO;

public class TransparentWindow : MonoBehaviour
{
    /// <summary>
    /// 一共可选择三种样式
    /// </summary>
    public enum enumWinStyle
    {
        /// <summary>
        /// 置顶不穿透
        /// </summary>
        WinTop,
        /// <summary>
        /// 穿透不置顶
        /// </summary>
        WinApha,
        /// <summary>
        /// 置顶并且穿透
        /// </summary>
        WinTopApha,
        /// <summary>
        ///  不置顶并且不穿透
        /// </summary>
        WinNoTopNoApha
    }

    // 定义RECT结构体，表示窗口的矩形区域
    [Serializable]
    public struct RECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
    }

    #region Win函数常量
    private struct MARGINS
    {
        public int cxLeftWidth;
        public int cxRightWidth;
        public int cyTopHeight;
        public int cyBottomHeight;
    }
    [DllImport("user32.dll")]
    static extern bool SetForegroundWindow(IntPtr hwnd);

    [DllImport("user32.dll")]
    static extern IntPtr GetForegroundWindow();
    [DllImport("user32.dll")]
    public static extern bool ShowWindow(IntPtr hwnd, int nCmdShow);

    [DllImport("user32.dll")]
    private static extern IntPtr GetActiveWindow();

    [DllImport("User32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    private static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);

    [DllImport("user32.dll")]
    static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
    [DllImport("user32.dll")]
    static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

    [DllImport("user32.dll")]
    static extern int GetWindowLong(IntPtr hWnd, int nIndex);

    [DllImport("user32.dll")]
    static extern int SetWindowPos(IntPtr hWnd, int hWndInsertAfter, int X, int Y, int cx, int cy, int uFlags);

    [DllImport("user32.dll")]
    static extern int SetLayeredWindowAttributes(IntPtr hwnd, int crKey, int bAlpha, int dwFlags);

    [DllImport("Dwmapi.dll")]
    static extern uint DwmExtendFrameIntoClientArea(IntPtr hWnd, ref MARGINS margins);
    [DllImport("user32.dll")]
    private static extern int SetWindowLong(IntPtr hWnd, int nIndex, uint dwNewLong);
    [DllImport("user32.dll")]
    public static extern bool ReleaseCapture();
    [DllImport("user32.dll")]

    public static extern bool SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);
    private const int WS_POPUP = 0x800000;
    private const int GWL_EXSTYLE = -20;
    private const int GWL_STYLE = -16;
    private const int WS_EX_LAYERED = 0x00080000;
    private const int WS_BORDER = 0x00800000;
    private const int WS_CAPTION = 0x00C00000;
    private const int SWP_SHOWWINDOW = 0x0040;
    private const int LWA_COLORKEY = 0x00000001;
    private const int LWA_ALPHA = 0x00000002;
    private const int WS_EX_TRANSPARENT = 0x20;
    private const int WS_EX_TOPMOST = 0x00000008;
    private const int ULW_COLORKEY = 0x00000001;
    private const int ULW_ALPHA = 0x00000002;
    private const int ULW_OPAQUE = 0x00000004;
    private const int ULW_EX_NORESIZE = 0x00000008;
    private const int SWP_NOSIZE = 0x0001;
    private const int SWP_NOZORDER = 0x0004;
    private const int SWP_NOMOVE = 0x0002;
    private const int SWP_NOACTIVATE = 0x0010;

    public const int SW_HIDE = 0;
    public const int SW_MAXIMIZE = 3;
    public const int SW_SHOW = 1;
    public const int SW_MINIMIZE = 6;
    public const int SW_RESTORE = 9;

    private const int HWND_BOTTOM = 1;
    private const int HWND_NOTOPMOST = -2;
    private const int HWND_TOP = 0;
    private const int HWND_TOPMOST = -1;

    #endregion
    private enumWinStyle WinStyle = enumWinStyle.WinTop;//窗体样式
    private int ResWidth;//窗口宽度
    private int ResHeight;//窗口高度
    private int currentX;//窗口左上角坐标x
    private int currentY;//窗口左上角坐标y

    private bool isWinTop = true;//是否置顶
    private bool isWinApha = false;//是否透过

    public static IntPtr hwnd;
    public static IntPtr dialogHwnd;

    private static bool mouseEnter = false;

    bool istop = true;


#if IS_TRANSPARENT
    private void Awake()
    {
        Application.targetFrameRate = 120;

        SetWindowInit();
    }
    private void SetWindowInit()
    {
        ResWidth = Screen.currentResolution.width;
        ResHeight = Screen.currentResolution.height;
        Screen.fullScreen = true;
        switch (WinStyle)
        {
            case enumWinStyle.WinTop:
                isWinTop = true;
                isWinApha = false;
                break;
            case enumWinStyle.WinApha:
                isWinTop = false;
                isWinApha = true;
                break;
            case enumWinStyle.WinTopApha:
                isWinTop = true;
                isWinApha = true;
                break;
            case enumWinStyle.WinNoTopNoApha:
                isWinTop = false;
                isWinApha = false;
                break;
        }
        currentX = Screen.currentResolution.width / 2 - Screen.width / 2;
        currentY = Screen.currentResolution.height / 2 - Screen.height / 2;
        Application.runInBackground = true;
        hwnd = GetActiveWindow();
        SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED);
        SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_BORDER & ~WS_CAPTION);
        SetWindowPos(hwnd, -1, currentX, currentY, ResWidth, ResHeight, SWP_SHOWWINDOW);
        var margins = new MARGINS() { cxLeftWidth = -1 };
        DwmExtendFrameIntoClientArea(hwnd, ref margins);
    }
    private void SetWindowTopApha(bool isTop, bool isApha)
    {
        isWinTop = isTop;
        isWinApha = isApha;
        int intExTemp = GetWindowLong(hwnd, GWL_EXSTYLE);

        if (isTop)
        {
            intExTemp |= WS_EX_TOPMOST;
            if (!isApha) intExTemp &= ~(WS_EX_TRANSPARENT | WS_EX_LAYERED);
            else intExTemp |= (WS_EX_TRANSPARENT | WS_EX_LAYERED);
        }
        else
        {
            intExTemp &= ~WS_EX_TOPMOST;
            if (isApha) intExTemp |= (WS_EX_LAYERED | WS_EX_TRANSPARENT);
            else intExTemp &= ~(WS_EX_TRANSPARENT | WS_EX_LAYERED);
        }

        SetWindowLong(hwnd, GWL_EXSTYLE, intExTemp);
        if (isTop) SetWindowPos(hwnd, HWND_TOPMOST, currentX, currentY, ResWidth, ResHeight, SWP_SHOWWINDOW);
        else SetWindowPos(hwnd, HWND_NOTOPMOST, currentX, currentY, ResWidth, ResHeight, SWP_SHOWWINDOW);

        var margins = new MARGINS() { cxLeftWidth = -1 };
        DwmExtendFrameIntoClientArea(hwnd, ref margins);
        SetWindowPos(hwnd, dialogHwnd.ToInt32(), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    void OnApplicationQuit()
    {
        //解决程序加载时会闪白色边框的现象
        SetWindowPos(hwnd, -1, currentX, currentY, 0, 0, SWP_SHOWWINDOW);
    }

    void Update()
    {
        if (MouseInformation.ChangeColor.r == 0 && MouseInformation.ChangeColor.g == 0 && MouseInformation.ChangeColor.b == 0){
            if (mouseEnter == true) return;
            mouseEnter = true;
        }
        else{
            if (mouseEnter == false) return; 
            mouseEnter = false;
        }
        UpdateWindowStyle();
    }

    //SetSize是废弃的接口(直接修改Window大小)
    public void SetSize(int size)
    {
        // 检查窗口句柄是否有效
        if (hwnd == IntPtr.Zero)
        {
            Debug.LogError("窗口句柄无效！");
            return;
        }
        int rw = ResWidth;
        int rh = ResHeight;
        int cx = currentX;
        int cy = currentY;
        RECT rect;
        if (GetWindowRect(hwnd, out rect))
        {
            cx = rect.left;
            cy = rect.top;
        }
        cx = cx + (ResWidth - size) / 2;
        cy = cy + (ResHeight - size) / 2;
        rw = size;
        rh = size;
        ResWidth = rw;
        ResHeight = rh;
        currentX = cx;
        currentY = cy;

        if (istop == true)
            SetWindowPos(hwnd, -1, currentX, currentY, ResWidth, ResHeight, SWP_SHOWWINDOW);
        else
            SetWindowPos(hwnd, -2, currentX, currentY, ResWidth, ResHeight, SWP_SHOWWINDOW);
    }

    public void ShowTaskBar()
    {
        ShowWindow(hwnd, SW_SHOW);
    }
    public void HideTaskBar()
    {
        ShowWindow(hwnd, SW_HIDE);
    }

#endif

    public void SetWinStyle(enumWinStyle enumWinStyle)
    {
        WinStyle = enumWinStyle;
    }

    public void UpdateWindowStyle()
    {
#if IS_TRANSPARENT
        if (MouseInformation.ChangeColor.r == 0 && MouseInformation.ChangeColor.g == 0 && MouseInformation.ChangeColor.b == 0)
        {
            if (WinStyle == enumWinStyle.WinTop)
                SetWindowTopApha(true, true);
            else if (WinStyle == enumWinStyle.WinApha)
                SetWindowTopApha(false, true);
            else if (WinStyle == enumWinStyle.WinTopApha)
                SetWindowTopApha(true, true);
            else if (WinStyle == enumWinStyle.WinNoTopNoApha)
                SetWindowTopApha(false, true);
        }
        else
        {
            if (WinStyle == enumWinStyle.WinTop)
                SetWindowTopApha(true, false);
            else if (WinStyle == enumWinStyle.WinApha)
                SetWindowTopApha(false, true);
            else if (WinStyle == enumWinStyle.WinTopApha)
                SetWindowTopApha(true, true);
            else if (WinStyle == enumWinStyle.WinNoTopNoApha)
                SetWindowTopApha(false, false);
        }
#endif
    }
}