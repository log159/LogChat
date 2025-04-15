# 💬 LogChat / 对数聊天 — 轻量支持Live2d的AI聊天客户端!

> 支持 ChatGPT / 讯飞星火 / DeepSeek / 百度语音识别 / TTS 合成 / Live2D 动画角色等，开箱即用，免环境部署！

---

## 🌈 项目预览

![AT](https://github.com/user-attachments/assets/3ccc4a8b-9a46-43ae-8afe-544b1eeb1e3e)

---

## 🚀 支持的模型

- 🧠 ChatGPT（官方API支持）
- 🌟 讯飞星火（general / v2 / v3 / v3.5）
- 🔎 DeepSeek
- 🧪 ChatGLM3（计划中）
- 🐲 百度千帆大模型（计划中）
- 🖥️ Ollama（计划中）

---

## 🧩 架构说明

- 🖥️ UI：基于 Qt Creator 开发界面
- 💬 LLM：ChatGPT API / DeepSeek API / 讯飞SDK（Windows）
- 🛠️ MT：百度翻译 API / 百度语音识别 API
- 🔊 TTS：VITS-simple-api / GPT-SoVits 接口联动
- 🧍‍♀️ Live2D：Unity 驱动，支持模型导入和动画绑定

---

## 📦 快速开始

1. 解压并运行 `LogChat.exe`（请确保路径中无空格）  
2. ChatGPT 使用需科学上网，或设置自定义代理 URL  
3. TTS需要安装并运行 [VITS-simple-api](https://github.com/Artrajz/vits-simple-api/tree/main) 或 [GPT-SoVits](https://github.com/RVC-Boss/GPT-SoVITS)  
4. 如模型不支持语言，配置 [百度翻译 API](https://fanyi-api.baidu.com/)  
5. 语音识别需配置 [百度语音识别 API](https://ai.baidu.com/ai-doc/SPEECH/Jlbxdezuf)  
6. GPT-SoVits转接api：[GitHub链接](https://github.com/jianchang512/gptsovits-api)（目前仅支持V1，其他版本请使用项目中的Self-VITS自定义配置）  

---

## 📋 已实现功能清单

### ✅ 聊天功能
- ✅ ChatGPT 接入
- ✅ DeepSeek 支持
- ✅ 讯飞星火模型（general v1~v3.5）
- 🔜 ChatGLM3
- 🔜 百度千帆 / Ollama / 反代理等

### ✅ TTS/语音合成
- ✅ VITS-simple-api
- ✅ GPT-SoVits
- 🔜 模型情绪调节、语速调节等高级功能

### ✅ STT/语音识别
- ✅ 百度语音识别（普通话）

### ✅ Live2D 角色动画
- ✅ 模型导入
- ✅ 位置与偏移控制
- ✅ 自定义控件渲染
- ✅ 动画动作绑定
- 🔜 控件谐波支持

### 🧰 其他计划功能
- 🔜 屏幕截图（OCR提取文字）
- 🔜 时钟组件
- 🔜 快捷启动器
## 📚 参考与依赖

| 模块 | 链接 |
|------|------|
| 💬 ChatGPT API | [OpenAI](https://platform.openai.com/docs/api-reference/introduction) |
| 💬 DeepSeek API | [官方文档](https://platform.deepseek.com/api-docs/zh-cn/) |
| 🌟 讯飞星火 SDK | [Windows SDK 文档](https://www.xfyun.cn/doc/spark/WindowsSDK.html) |
| 🗣️ 百度语音识别 | [文档](https://ai.baidu.com/ai-doc/SPEECH/Jlbxdezuf) |
| 🌐 百度翻译 API | [文档](https://fanyi-api.baidu.com/doc/11) |
| 🔊 VITS-simple-api | [GitHub](https://github.com/Artrajz/vits-simple-api/tree/v0.2.0) |
| 🔊 GPT-SoVits | [GitHub](https://github.com/RVC-Boss/GPT-SoVITS) |
| 👧 Live2D SDK 文档 | [官方](https://docs.live2d.com/zh-CHS/cubism-sdk-manual/top/) |
| 👧 中文翻译文档 | [GitHub](https://github.com/gtf35/live2d_unity_sdk_chinese_document) |

---

### 🔄 GPT-SoVits 转接 API

- [GitHub链接](https://github.com/jianchang512/gptsovits-api)  
  （目前仅支持 V1，其他版本请使用 Self-VITS 自定义配置）

---

### 🧠 可用于 VITS-simple-api 的模型

- [MoeTTS](https://github.com/luoyily/MoeTTS)
- [Emotional-VITS](https://github.com/Ikaros-521/emotional-vits/releases)
- [TTSModels](https://github.com/CjangCjengh/TTSModels)

---

### 🧠 可用于 GPT-SoVits 的模型

- [薄荷（支持中日英三语）](https://www.bilibili.com/video/BV1wy411B7uE)  
  （自己随便训练的）

---

## 🎨 可用 Live2D 模型资源（转载）

- [亚托莉](https://www.bilibili.com/video/BV1zg4y1b7Yu)
- [丛雨](https://www.bilibili.com/video/BV1mb4y1i7xu)
- [娅萌工作室模型](https://www.bilibili.com/video/BV1kX4y1677W)

---

## 📬 联系与反馈

欢迎提 Issue 或 PR，也可通过 B 站私信联系开发者！
- [BiliBili链接](https://space.bilibili.com/3493110573172862)

---
## 🙌 贡献者名单

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


