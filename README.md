# 可连接到VITS的Chat客户端，支持ChatGPT
#By bilibili:@LearningLog  

#Version-3.0  
+设置界面优化  
+屏幕适配  
+支持bert-vits2和w2v2-vits模型api  

# 免科学上网使用此项目方式
1、修改openpy/qtopenai.py 加一行 openai.api_base = "https://api.chatanywhere.com.cn/v1"  
2、申请密钥(无需科学上网，国内直连) 链接：https://github.com/chatanywhere/GPT_API_free  
  
# ------------source code 架构------------------  
1、ui使用C++ qt creator 搭建  
2、GPT的LLM模型交互使用openai的python脚本，需要python环境和安装openai库  
4、使用VITS-simple-api：	https://github.com/Artrajz/vits-simple-api/tree/main  
5、使用百度翻译api：	https://fanyi-api.baidu.com/  
  
# ------------relese 使用-----------------------  
1、需要python环境和openai库，需要申请openai密钥(Key)  
2、调用api需要科学上网  
3、需要 VITS-simple-api： https://github.com/Artrajz/vits-simple-api/tree/main  
4、配置 VITS模型并成功启动端口  
5、如果VITS模型不支持对话语言，需要借助百度翻译api，申请链接 https://fanyi-api.baidu.com/  
6、运行.exe  
  
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
