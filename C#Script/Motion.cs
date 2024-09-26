using Live2D.Cubism.Framework.Json;
using System.Collections.Generic;
using System.Drawing;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Timeline;
using UnityEngine.UIElements;

public class Motion : MonoBehaviour
{
    private Model model = null;
    private Dictionary<string, MotionItem> parameterItemsDic    = new Dictionary<string, MotionItem>();
    private Dictionary<string, MotionItem> partItemsDic         =new Dictionary<string, MotionItem>();

    private List<Dictionary<string, Dictionary<string, Keyframe[]>>> waitMotItemDicList = new List<Dictionary<string, Dictionary<string, Keyframe[]>>>();
    private List<Dictionary<string, Dictionary<string, Keyframe[]>>> reactMotItemDicList = new List<Dictionary<string, Dictionary<string, Keyframe[]>>>();

    public void AddWaitMotionItemList(Dictionary<string, Dictionary<string, Keyframe[]>> motItemDic)
    {
        waitMotItemDicList.Add(motItemDic);
    }
    public void AddReactMotionItemList(Dictionary<string, Dictionary<string, Keyframe[]>> motItemDic)
    {
        reactMotItemDicList.Add(motItemDic);
    }
    public void SendReactMotion()
    {
        if(reactMotItemDicList.Count > 0)
            AddMotionItem(reactMotItemDicList[Random.Range(0, reactMotItemDicList.Count)]);
    }

    public void Clear()
    {
        parameterItemsDic.Clear();
        partItemsDic.Clear();
        waitMotItemDicList.Clear();
        reactMotItemDicList.Clear ();
    }
    public void AddMotionItem(Dictionary<string,Dictionary<string, Keyframe[]>> motItemDic)
    {
        this.model = GetComponent<Model>();
        if (model == null)  return;
        MotionItem.addTime = 0.0f;
        if (motItemDic.ContainsKey("Parameter"))
        {
            foreach (KeyValuePair<string, Keyframe[]> item in motItemDic["Parameter"])
            {
                MotionItem motionItem = new MotionItem();
                motionItem.free = false;
                motionItem.lastIndex = 0;
                motionItem.keyframeArr = item.Value;
                if (motionItem.keyframeArr.Length < 2) continue;
                parameterItemsDic[item.Key] = motionItem;
            }
        }
        if (motItemDic.ContainsKey("PartOpacity"))
        {
            foreach (KeyValuePair<string, Keyframe[]> item in motItemDic["PartOpacity"])
            {
                MotionItem motionItem = new MotionItem();
                motionItem.free = false;
                motionItem.lastIndex = 0;
                motionItem.keyframeArr = item.Value;
                if (motionItem.keyframeArr.Length < 2) continue;
                partItemsDic[item.Key] = motionItem;
            }
        }
    }
    private static List<string> endParameterItemList = new List<string>();
    private static List<string> endPartItemList = new List<string>();
    private void Update()
    {
        this.model = GetComponent<Model>();
        if (model == null) return;
        endParameterItemList.Clear();
        endPartItemList.Clear();
        if(parameterItemsDic.Count==0 && partItemsDic.Count == 0)
        {
            Debug.Log("待机动画");
            //添加待机动画
            if(waitMotItemDicList.Count>0)
                AddMotionItem(waitMotItemDicList[Random.Range(0, waitMotItemDicList.Count)]);
        }

        foreach (KeyValuePair<string, MotionItem> item in parameterItemsDic)
        {
            if (parameterItemsDic[item.Key].free == true) {
                endParameterItemList.Add(item.Key);
                continue; 
            }
            int index = -1;
            Keyframe[] keyframeArr = item.Value.keyframeArr;
            for (int i = item.Value.lastIndex; i < keyframeArr.Length; ++i)
            {
                if (MotionItem.addTime >= keyframeArr[i].time) { index = i; }
                else break;
            }
            if (index == -1) continue;
            if (index == keyframeArr.Length - 1)
            {
                parameterItemsDic[item.Key].free = true;
                model.AddParameterDic(item.Key, keyframeArr[index].value);
                continue;
            }
            item.Value.lastIndex = index;
            float x1 = keyframeArr[index].time;
            float y1 = keyframeArr[index].value;
            float x2 = keyframeArr[index + 1].time;
            float y2 = keyframeArr[index + 1].value;
            if (x2 - x1 == 0) continue;
            float a = (y2 - y1) / (x2 - x1);
            float b = y1 - a * x1;
            float value = a * MotionItem.addTime + b;
            model.AddParameterDic(item.Key, value);
        }
        foreach (KeyValuePair<string, MotionItem> item in partItemsDic)
        {
            if (partItemsDic[item.Key].free == true) {
                endPartItemList.Add(item.Key);
                continue; 
            }
            int index = -1;
            Keyframe[] keyframeArr = item.Value.keyframeArr;
            for (int i = item.Value.lastIndex; i < keyframeArr.Length; ++i)
            {
                if (MotionItem.addTime >= keyframeArr[i].time) { index = i; }
                else break;
            }
            if (index == -1) continue;
            if (index == keyframeArr.Length - 1)
            {
                partItemsDic[item.Key].free = true;
                model.AddParameterDic(item.Key, keyframeArr[index].value);
                continue;
            }
            item.Value.lastIndex = index;
            float x1 = keyframeArr[index].time;
            float y1 = keyframeArr[index].value;
            float x2 = keyframeArr[index + 1].time;
            float y2 = keyframeArr[index + 1].value;
            if (x2 - x1 == 0) continue;
            float a = (y2 - y1) / (x2 - x1);
            float b = y1 - a * x1;
            float value = a * MotionItem.addTime + b;
            model.AddPartDic(item.Key, value);
        }
        //移除完成的Parameter动画
        foreach (string key in endParameterItemList)
            parameterItemsDic.Remove(key);
        //移除完成的Part动画
        foreach (string key in endPartItemList)
            partItemsDic.Remove(key);
        MotionItem.addTime += Time.deltaTime;
    }
}
