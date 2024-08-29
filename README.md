# 一个开源免费的AI聊天客户端！

预览:
![屏幕截图 2024-08-17 194250](https://github.com/user-attachments/assets/793a8da1-ef0d-4db6-8c05-5a6f49c101d6)


支持的聊天模型:
- ChatGPT
- 讯飞星火

支持的技术:
- LLM
- TTS
- STT
- Live2D

## 源代码架构

1. **UI设计：** 使用Qt Creator进行界面设计
2. **ChatGPT API**
3. **讯飞星火大模型官方Windows SDK**
4. **VITS-simple-api**
5. **GPT-SoVits**
6. **百度翻译API**
7. **百度语音识别API**
8. **Live2D基于Unity**

## 发布使用说明

1. 无需任何额外环境，直接可用于Windows系统，请确保安装路径中没有空格！
2. 使用ChatGPT官方key需要科学上网，或通过自定义URL设置直连。
3. 语音合成功能需要 [VITS-simple-api](https://github.com/Artrajz/vits-simple-api/tree/main)或[GPT-SoVits](https://github.com/RVC-Boss/GPT-SoVITS)
4. 配置VITS模型并成功启动端口。
5. 若VITS模型不支持对话语言，需要使用[百度翻译API](https://fanyi-api.baidu.com/)。
6. 免科学上网使用此项目方式，获取base URL以及key：[GPT_API_free](https://github.com/chatanywhere/GPT_API_free)
7. 运行`LogChat.exe`。

## 目前以及未来实现的功能
 - [x] LLM-ChatGPT[gpt-3.5-turbo]
 - [x] LLM-讯飞星火语言大模型[general,generalv2,generalv3,generalv3.5]
 - [ ] LLM-ChatGML[ChatGML3]
 - [ ] LLM-百度千帆大模型
 - [ ] LLM-DeepSeek
 - [ ] LLM-其它Ai平台的反代理方式
 - [x] TTS-VITS
 - [x] TTS-GPT-SoVits
 - [x] STT-百度语音识别[中文普通话]
 - [x] Live2D-角色模型导入
 - [x] Live2D-模型的几何位置，基本功能支持自定义
 - [x] Live2D-模型的控件偏移支持自定义
 - [x] Live2D-模型的控件渲染支持自定义
 - [ ] Live2D-模型的动画支持自定义
 - [ ] Live2D-模型的控件谐波支持自定义
 - [ ] Other-菜单项目[截图(编辑，OCR)，时钟，应用快捷启动器]

## 借鉴与引用

- **Vits-simple-api**：[GitHub链接](https://github.com/Artrajz/vits-simple-api/tree/v0.2.0)
- **Vits-simple-api配置**：[Bilibili视频](https://www.bilibili.com/video/BV1ku4y1R73r)
- **可用于Vits-simple-api的模型**：
  - [MoeTTS](https://github.com/luoyily/MoeTTS)
  - [Emotional-VITS](https://github.com/Ikaros-521/emotional-vits/releases)
  - [TTSModels](https://github.com/CjangCjengh/TTSModels)
- **GPT-SoVits**：[GitHub链接](https://github.com/RVC-Boss/GPT-SoVITS)
- **GPT-SoVits转接api**：[GitHub链接](https://github.com/jianchang512/gptsovits-api)
- **可用于GPT-SoVits的模型**：(自己随便训练的,支持中日英三语)[Bilibili视频](https://www.bilibili.com/video/BV1wy411B7uE)
- **其他文档及VITS常见问题**：[Luna Docs](https://luna.docs.ie.cx/)
- **OpenAI官网**：[访问OpenAI](https://openai.com/)
- **OpenAI API文档**：[API参考](https://platform.openai.com/docs/api-reference/introduction)
- **百度翻译API文档**：[API文档](https://fanyi-api.baidu.com/doc/11)
- **百度语音识别API文档**：[API文档](https://ai.baidu.com/ai-doc/SPEECH/Jlbxdezuf)
- **讯飞星火API**：[官方网站](https://xinghuo.xfyun.cn/sparkapi)
- **Live2D SDK手册**：[SDK文档](https://docs.live2d.com/zh-CHS/cubism-sdk-manual/top/)
- **Live2D中文文档**：[GitHub资源](https://github.com/gtf35/live2d_unity_sdk_chinese_document)
- **可用的Live2D(转自B站)**：
  - [亚托莉](https://www.bilibili.com/video/BV1zg4y1b7Yu)
  - [丛雨](https://www.bilibili.com/video/BV1mb4y1i7xu)
  - [娅萌工作室](https://www.bilibili.com/video/BV1kX4y1677W)
## 贡献者

<!-- readme: collaborators,contributors -start -->
<table>
<tr>
    <td align="center">
        <a href="https://github.com/Zao-chen">
            <img src="https://avatars.githubusercontent.com/u/77674075?v=4" width="100;" alt="Zao-chen"/>
            <br />
            <sub><b>Zao_chen</b></sub>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/log159">
            <img src="https://avatars.githubusercontent.com/u/121474554?v=4" width="100;" alt="log159"/>
            <br />
            <sub><b>Log</b></sub>
        </a>
    </td></tr>
</table>
<!-- readme: collaborators,contributors -end -->

