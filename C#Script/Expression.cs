using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static ExpressionItem;

public class Expression : MonoBehaviour
{
    private Model model = null;
    private Dictionary<string,ExpressionItem> expressionItemDic = new Dictionary<string, ExpressionItem>();
    private void Start()
    {
        model = GetComponent<Model>();
    }
    public void AddExpressionItemDic(List<ExpressionItem> expressionItemList)
    {
        //旧的动画全部变为LEAVE属性
        foreach (KeyValuePair<string, ExpressionItem> paramPair in expressionItemDic)
            paramPair.Value.mark = ExpressionItem.MARK.LEAVE;
        //新的动画覆盖部分旧的并添加新的
        for (int i = 0; i < expressionItemList.Count; i++)
            expressionItemDic[expressionItemList[i].name] = expressionItemList[i];
    }
    void Update()
    {
        if (expressionItemDic.Count <= 0 || model == null) return;
        List<string>endItemList = new List<string>();
        foreach (KeyValuePair<string, ExpressionItem> paramPair in expressionItemDic) {
            float distance = Mathf.Abs(paramPair.Value.initialValue - paramPair.Value.targetValue);
            ExpressionItem expressionItem = paramPair.Value;
            //向targetValue刷新
            float nextValue = expressionItem.value;
            if (ExpressionItem.MARK.ENTER== expressionItem.mark){
                Debug.Log(expressionItem.targetValue+" "+ expressionItem.value);
                float speed = distance / (paramPair.Value.intime / Time.deltaTime);
                if (expressionItem.targetValue >= expressionItem.value) nextValue += speed;
                else nextValue -= speed;
                if (Mathf.Abs(expressionItem.targetValue - nextValue) <= speed){
                    expressionItem.value = expressionItem.targetValue;
                    expressionItem.mark = ExpressionItem.MARK.STOP;
                }
                else expressionItem.value = nextValue;
                model.AddParameterDic(expressionItem.name,expressionItem.value); 
            }
            //向initialValue刷新
            else if(ExpressionItem.MARK.LEAVE== expressionItem.mark)
            {
                float speed = distance / (paramPair.Value.outtime / Time.deltaTime);

                if (expressionItem.initialValue >= expressionItem.value) nextValue += speed;
                else nextValue -= speed;
                if (Mathf.Abs(expressionItem.initialValue - nextValue) <= speed) {
                    expressionItem.value= expressionItem.initialValue;
                    expressionItem.mark = ExpressionItem.MARK.END;
                }
                else expressionItem.value = nextValue; 
                model.AddParameterDic(expressionItem.name, expressionItem.value); 
            }
            //停止等待下一个状态切换
            else if(ExpressionItem.MARK.STOP == expressionItem.mark){}
            //加入列表队列
            else if(ExpressionItem.MARK.END == expressionItem.mark)
                endItemList.Add(paramPair.Key);
            else { }
        }
        //移除完成的Expression动画
        foreach (string key in endItemList)
            expressionItemDic.Remove(key);

    }
}
