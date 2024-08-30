#define  _CRT_SECURE_NO_WARNINGS
#include "../include/sparkchain.h"
#include "../include/sc_llm.h"

#include <iostream>
#include <string>
#include <atomic>
#include <Windows.h>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET "\033[0m"

using namespace SparkChain;
using namespace std;

// async status tag
static atomic_bool finish(false);
// result cache
std::string final_result = "";

//user question
std::string user_question;

class Config {
public:
	static std::string appID;
	static std::string apiKey;
	static std::string apiSecret;
	static std::string model;
	static std::string fileWay;
};
std::string Config::appID;
std::string Config::apiKey;
std::string Config::apiSecret;
std::string Config::model;
std::string Config::fileWay;


class SparkCallbacks : public LLMCallbacks {
	void onLLMResult(LLMResult* result, void* usrContext) {
		int status = result->getStatus();
		printf(GREEN "%d:%s:%s " "usrContext:%d\n" RESET, status, result->getRole(), result->getContent(), *(int*)usrContext);
		final_result += string(result->getContent());
		if (status == 2) {
			printf(GREEN "tokens:%d + %d = %d "  "usrContext:%d\n" RESET, result->getCompletionTokens(), result->getPromptTokens(), result->getTotalTokens(), *(int*)usrContext);
			finish = true;
		}
	}
	void onLLMEvent(LLMEvent* event, void* usrContext) {
		printf(YELLOW "onLLMEventCB\n  eventID:%d eventMsg:%s "  "usrContext:%d\n" RESET, event->getEventID(), event->getEventMsg(), *(int*)usrContext);
	}
	void onLLMError(LLMError* error, void* usrContext) {
		printf(RED "onLLMErrorCB\n errCode:%d errMsg:%s "  "usrContext:%d\n" RESET, error->getErrCode(), error->getErrMsg(), *(int*)usrContext);
		finish = true;
	}
};

int initSDK()
{
	// 全局初始化
	SparkChainConfig *config = SparkChainConfig::builder();
	config->appID(Config::appID.data())        // appid
		->apiKey(Config::apiKey.data())        // apikey
		->apiSecret(Config::apiSecret.data()); // apisecret
	int ret = SparkChain::init(config);
	//printf(RED "\ninit SparkChain result:%d" RESET, ret);
	return ret;
}

void syncLLMTest()
{
	//cout << "\n######### 同步调用 #########" << endl;
	// 配置大模型参数
	LLMConfig *llmConfig = LLMConfig::builder();
	llmConfig->domain(Config::model.data());

	Memory* window_memory = Memory::WindowMemory(5);
	LLM *syncllm = LLM::create(llmConfig, window_memory);

	// Memory* token_memory = Memory::TokenMemory(500);
	// LLM *syncllm = LLM::create(llmConfig,token_memory);

	const char* input = user_question.data();

	{
		// 同步请求
		LLMSyncOutput* result = syncllm->run(input);
		if (result->getErrCode() != 0){
			//printf(RED "\nsyncOutput: %d:%s\n\n" RESET, result->getErrCode(), result->getErrMsg());
			printf("syncOutput: %d:%s", result->getErrCode(), result->getErrMsg());
		}
		else{
			//printf(GREEN "\nsyncOutput: %s:%s\n" RESET, result->getRole(), result->getContent());
			printf("%s", result->getContent());
		}
	}
	// 垃圾回收
	if (syncllm != nullptr)
	{
		LLM::destroy(syncllm);
	}
}
void uninitSDK()
{
	// 全局逆初始化
	SparkChain::unInit();
}

std::string getFileInformation(const std::string& path) {
	std::ifstream in(path);
	std::stringstream buffer;
	buffer << in.rdbuf();
	std::string contents(buffer.str());
	return contents;
} 

//argv 1 appid
//argv 2 apikey
//argv 3 apiSecret
//argv 4 模型
//argv 5 txt way

int main(int argc, char const *argv[])
{
	if (argc <= 1) {
		return -1;
	}
	//system("chcp 65001");

	//init config
	Config::appID		=argv[1];
	Config::apiKey		=argv[2];
	Config::apiSecret	=argv[3];
	Config::model		=argv[4];
	Config::fileWay		=argv[5];

	user_question = getFileInformation(Config::fileWay);
	// 全局初始化
	int ret = initSDK();
	if (ret != 0)
	{
		cout << "init failed:" << ret << endl;
		return -1;
	}
	syncLLMTest(); // 同步调用
	uninitSDK();// 退出
	return 0;

}
