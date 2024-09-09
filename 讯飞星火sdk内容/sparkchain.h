#ifndef SPARK_CHAIN_API_H
#define SPARK_CHAIN_API_H

#include "sc_agent.h"
#include "sc_llm.h"
#include "sc_error.h"
#include "sc_memory.h"
#include "sc_type.h"

namespace SparkChain {

/**
 * @brief SparkChain global config
 * 
 */
class SPARKCHAIN_API SparkChainConfig {
public:
    static SparkChainConfig* builder();

    virtual ~SparkChainConfig();

    virtual SparkChainConfig* appID(const char* appid)         = 0;
    virtual SparkChainConfig* apiKey(const char* apiKey)       = 0;
    virtual SparkChainConfig* apiSecret(const char* apiSecret) = 0;
    virtual SparkChainConfig* uid(const char* uid)             = 0;
    virtual SparkChainConfig* workDir(const char* workDir)     = 0;
    virtual SparkChainConfig* logLevel(int logLevel )          = 0;
    virtual SparkChainConfig* logPath(const char* logPath)     = 0;
    
};

/**
 * @brief golbal init
 * 
 * @param config 
 * @return SPARKCHAIN_API 
 */
SPARKCHAIN_API int32_t init(SparkChainConfig* config);

/**
 * @brief global unInit
 * 
 * @return SPARKCHAIN_API 
 */
SPARKCHAIN_API int32_t unInit();

}

#endif