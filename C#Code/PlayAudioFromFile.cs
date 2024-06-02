using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PlayAudioFromFile : MonoBehaviour
{
    public void PlayAudioByPath(string path)
    {
        // 获取AudioSource组件
        AudioSource audioSource = GetComponentInChildren<AudioSource>();

        if (audioSource == null) {
            Debug.Log("组件信息为空");
            return; 
        }
        // 使用WWW类加载音频文件

        Debug.Log("音频开始播放");
        StartCoroutine(LoadAudioFile(path, audioSource));

    }
    private IEnumerator LoadAudioFile(string filePath, AudioSource audioSource)
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
            Debug.Log("Failed to load audio file: " + www.error);
        }
    }

}
