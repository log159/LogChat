using System.Collections;
using System.Collections.Generic;
using System.IO;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Networking;

//旧的加载方式 接收即播放
//public class PlayAudioFromFile : MonoBehaviour
//{
//    public void PlayAudioByPath(string path)
//    {
//        // 获取AudioSource组件
//        AudioSource audioSource = GetComponentInChildren<AudioSource>();

//        if (audioSource == null) {
//            Debug.Log("组件信息为空");
//            return; 
//        }
//        // 使用WWW类加载音频文件

//        Debug.Log("音频开始播放");
//        StartCoroutine(LoadAudioFile(path, audioSource));

//    }
//    private IEnumerator LoadAudioFile(string filePath, AudioSource audioSource)
//    {
//        // 使用UnityWebRequest加载音频文件
//        UnityWebRequest www = UnityWebRequestMultimedia.GetAudioClip("file://" + filePath, AudioType.WAV);

//        // 发送请求并等待返回
//        yield return www.SendWebRequest();

//        // 检查是否有错误
//        if (www.result == UnityWebRequest.Result.Success)
//        {
//            // 获取加载的音频文件
//            AudioClip audioClip = DownloadHandlerAudioClip.GetContent(www);

//            // 播放音频文件
//            audioSource.clip = audioClip;
//            audioSource.Play();
//        }
//        else
//        {
//            Debug.Log("Failed to load audio file: " + www.error);
//        }
//    }

//}

//新的加载方式 音频播放队列
public class PlayAudioFromFile : MonoBehaviour
{
    public static List<string> AudioPathsList=new List<string>();
    private AudioSource audioSource;

    private void Start()
    {
        audioSource = GetComponent<AudioSource>();

        StartCoroutine(AudioPlaying());
    }
    public static void AddAudioPathsList(string path)
    {
        AudioPathsList.Add(path);
    }
    public static void ClearAudioPathsList()
    {
        AudioPathsList.Clear();
    }

    private IEnumerator AudioPlaying()
    {
        while (true)
        {
            if (AudioPathsList.Count > 0)
            {
                Debug.Log("当前正在播放: "+ AudioPathsList[0]);
                yield return StartCoroutine(LoadAndPlayAudioFile(AudioPathsList[0], audioSource));
                if(AudioPathsList.Count>=1) {
                    AudioPathsList.RemoveAt(0);
                }
            }
            else
            {
                yield return null;
            }
        }
    }

    private IEnumerator LoadAndPlayAudioFile(string filePath, AudioSource audioSource)
    {
        // 使用UnityWebRequest加载音频文件  
        UnityWebRequest www = UnityWebRequestMultimedia.GetAudioClip("file://" + filePath, AudioType.WAV);

        // 发送请求并等待返回  
        yield return www.SendWebRequest();

        // 检查是否有错误  
        if (www.result == UnityWebRequest.Result.Success)
        {
            // 获取加载的音频文件  
            AudioClip audioClip = DownloadHandlerAudioClip.GetContent(www);

            // 播放音频文件  
            audioSource.clip = audioClip;
            audioSource.Play();
        }
        else
        {
            Debug.LogError("Failed to load audio file: " + www.error);
        }

        // 等待音频播放完成  
        while (audioSource.isPlaying)
        {
            yield return null;
        }
        yield break;
    }
}