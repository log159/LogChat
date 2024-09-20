using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ModelUserEvent : MonoBehaviour
{
    public void UserDataEventListener(string value)
    {
        AnimatorStateInfo animatorStateInfo = GetComponent<Animator>().GetCurrentAnimatorStateInfo(0);

        Debug.Log("Time: " + (animatorStateInfo.length) / animatorStateInfo.speed + " value: " + value);
    }
}
