using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MathFunction : MonoBehaviour
{
    //Test Demo Function
    //private void Start()
    //{
    //    //key 范围 0-99 表示 0% 到 99%
    //    Dictionary<int,uint> m = new Dictionary<int, uint>();
    //    for (int i = 0; i < 100; i++)
    //    {
    //        m[i] = 0;
    //    }
    //    //f(x)为正态函数在[0,x]区间的积分
    //    //y = f(x)函数的逆函数 x = f(y)
    //    //x 精确到 0.0000 到 0.4999 (正态函数在零到正无穷积分值为0.5000)
    //    //y 在 x = 0.4999 时 最大 y = 3.71905 指定 MAX_F 为 3.8
    //    float MAX_F = 3.8f;
    //    for (int i = 0;i < 1000000; i++)
    //    {
    //        int num = UnityEngine.Random.Range(0,5000);
    //        float numR = num / 10000f;
    //        float posf = MyErfinv(numR * 2f) * Mathf.Sqrt(2f);
    //        int pos = (int)(posf / MAX_F * 100f);

    //        if (pos >= 100){pos = 99;}
    //        if (pos < 0){pos = 0;}
    //        m[pos]++;
    //    }
    //    string str = "";
    //    for(int i = 0;i < m.Count ; i++)
    //    {
    //        str += "百分之"+i.ToString()+" "+m[i].ToString()+" \n";
    //    }
    //    Debug.Log(str);
    //}


    //return value [0,100] int -> %
    public static int GetNormalDistribution()
    {
        float MAX_F = 3.8f;
        int num = UnityEngine.Random.Range(0, 5000);
        float numR = num / 10000f;
        float posf = MyErfinv(numR * 2f) * Mathf.Sqrt(2f);
        int pos = (int)(posf / MAX_F * 100f);

        if (pos >= 100) { pos = 99; }
        if (pos < 0) { pos = 0; }

        return pos;
    }



    // 修正的逆误差函数
    private static float MyErfinv(float a)
    {
        float p, r, t;
        t = MyFma(a, -a, 1.0f);
        t = MyLog(t);
        if (Mathf.Abs(t) > 6.125f)
        {
            p = 3.03697567e-10f;
            p = MyFma(p, t, 2.93243101e-8f);
            p = MyFma(p, t, 1.22150334e-6f);
            p = MyFma(p, t, 2.84108955e-5f);
            p = MyFma(p, t, 3.93552968e-4f);
            p = MyFma(p, t, 3.02698812e-3f);
            p = MyFma(p, t, 4.83185798e-3f);
            p = MyFma(p, t, -2.64646143e-1f);
            p = MyFma(p, t, 8.40016484e-1f);
        }
        else
        {
            p = 5.43877832e-9f;
            p = MyFma(p, t, 1.43285448e-7f);
            p = MyFma(p, t, 1.22774793e-6f);
            p = MyFma(p, t, 1.12963626e-7f);
            p = MyFma(p, t, -5.61530760e-5f);
            p = MyFma(p, t, -1.47697632e-4f);
            p = MyFma(p, t, 2.31468678e-3f);
            p = MyFma(p, t, 1.15392581e-2f);
            p = MyFma(p, t, -2.32015476e-1f);
            p = MyFma(p, t, 8.86226892e-1f);
        }
        r = a * p;
        return r;
    }
    private static float MyFma(float x, float y, float z)
    {
        return x * y + z;
    }
    private static float MyLog(float a)
    {
        float i, m, r, s, t;
        int e = 0;
        m = Frexpf(a, ref e);

        if (m < 0.666666667f)
        {
            m += m;
            e -= 1;
        }
        i = e;
        m -= 1.0f;
        s = m * m;
        r = -0.130310059f;
        t = 0.140869141f;
        r = MyFma(r, s, -0.121484190f);
        t = MyFma(t, s, 0.139814854f);
        r = MyFma(r, s, -0.166846052f);
        t = MyFma(t, s, 0.200120345f);
        r = MyFma(r, s, -0.249996200f);
        r = MyFma(t, m, r);
        r = MyFma(r, m, 0.333331972f);
        r = MyFma(r, m, -0.500000000f);
        r = MyFma(r, s, m);
        r = MyFma(i, 0.693147182f, r);
        return r;
    }
    private static float Frexpf(float x, ref int exp)
    {
        exp = 0;
        if (x == 0f) return 0f;

        float abs_x = Mathf.Abs(x);
        if (abs_x == float.PositiveInfinity || float.IsNaN(abs_x)){
            return x;
        }
        exp = (int)Mathf.Floor(Mathf.Log(abs_x, 2)) + 1;
        float significand = x * Mathf.Pow(2, -exp);
        if (Mathf.Abs(significand) >= 1f)
        {
            significand *= 0.5f;
            exp++;
        }
        else if (Mathf.Abs(significand) < 0.5f && significand != 0f)
        {
            significand *= 2f;
            exp--;
        }
        return significand;
    }
}
