# 可连接到VITS的Chat客户端，支持ChatGPT、讯飞星火  
  
# ------------source code 架构------------------  
1、ui使用qt creator 搭建  
2、ChatGPT的LLM模型交互使用openai的python脚本，需要python环境和安装openai库  
3、讯飞星火大模型使用官方windows SDK  
4、VITS-simple-api：	https://github.com/Artrajz/vits-simple-api/tree/main  
5、百度翻译api：	https://fanyi-api.baidu.com/  
  
# ------------relese 使用-----------------------  
1、需要python环境和openai库，需要申请openai密钥(Key)  
2、使用ChatGPT官方key需要科学上网，设置base url 可通过自己的url设置直连  
3、需要 VITS-simple-api： https://github.com/Artrajz/vits-simple-api/tree/main  
4、配置 VITS模型并成功启动端口  
5、如果VITS模型不支持对话语言，需要借助百度翻译api，申请链接 https://fanyi-api.baidu.com/  
6、运行LogChat.exe  
  
# ------------借鉴&引用--------------------------  
#VITS-simple-api：  
#https://github.com/Artrajz/vits-simple-api/releases/tag/v0.2.0  
#VITS-simple-api配置：  
#https://www.bilibili.com/video/BV1ku4y1R73r  
#可用于VITS-api的模型：  
#https://github.com/luoyily/MoeTTS  
#https://github.com/Ikaros-521/emotional-vits/releases  
#https://github.com/CjangCjengh/TTSModels  
#其它文档，以及一些VITS常见问题：  
#https://luna.docs.ie.cx/  
#openai官网：  
#https://openai.com/  
#openai-api文档：  
#https://platform.openai.com/docs/api-reference/introduction  
#百度翻译-api文档：  
#https://fanyi-api.baidu.com/doc/11  
#讯飞星火-api：  
#https://xinghuo.xfyun.cn/sparkapi  
