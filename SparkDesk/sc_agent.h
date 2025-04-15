#ifndef SC_AGENT_API_H
#define SC_AGENT_API_H

#include "sc_llm.h"
#include "sc_plugins.h"

namespace SparkChain {

using AgentBaseOutput = LLMBaseOutput;

class SPARKCHAIN_API AgentResult : virtual public AgentBaseOutput {
public:
    virtual ~AgentResult();

    virtual const char* getRequest() const     = 0;
    virtual const char* getResponse() const    = 0;
};

using AgentEvent = LLMEvent;

using AgentError = LLMError;

class SPARKCHAIN_API AgentSyncOutput : virtual public AgentResult , virtual public AgentError {
public:
    virtual ~AgentSyncOutput();

};

class SPARKCHAIN_API AgentCallbacks {
public:
    /**
     *
     * @param key
     * @param request
     * @param response
     * @param usrContext
     */
    virtual void onAgentResult(AgentResult* result, void* usrContext) = 0;

    /**
     *
     * @param key
     * @param eventMsg
     * @param eventID
     * @param usrContext
     */
    virtual void onAgentEvent(AgentEvent* event, void* usrContext) = 0;

    /**
     *
     * @param key
     * @param errCode
     * @param errMsg
     * @param usrContext
     */
    virtual void onAgentError(AgentError* error, void* usrContext) = 0;
};

class SPARKCHAIN_API PluginResult {
public:
    ~PluginResult();

    virtual const char* getName() const        = 0;
    virtual const char* getRequest() const     = 0;
    virtual const char* getResponse() const    = 0;
};

class SPARKCHAIN_API PluginCallbacks {
public:
    /**
     * @brief 
     * 
     * @param plugin 
     * @param request 
     * @param response 
     * @param usrContext 
     */
    virtual void onPluginOutput(PluginResult* output, void* usrContext) = 0;

};

/**
 * @brief Agent Api class
 * 
 */
class SPARKCHAIN_API Agent {
public:

    /**
     * @brief agent type
     * 
     */
    typedef enum {
        PLUGIN_AGENT    = 0,
        ZERO_SHOT_REACT = 1
    } AgentType;

public:

    virtual ~Agent();

    /**
     * @brief 
     * 
     * @param agentType 
     * @param llm 
     * @param plugins 
     * @return Agent* 
     */
    static Agent* create(AgentType agentType, LLM* llm, Plugins* plugins);

    /**
     * @brief destroy agent inst
     * 
     */
    static void destroy(Agent* agent);

    /**
     * @brief 
     * 
     * @param text 
     * @param memory 
     * @return int 
     */
    virtual AgentSyncOutput* run(const char* text, Memory* memory = nullptr) = 0;

    /**
     * @brief 
     * 
     * @param cbs 
     */
    virtual void registerAgentCallbacks(AgentCallbacks* agentCbs) = 0;

    /**
     * @brief 
     * 
     * @param pluginCbs 
     */
    virtual void registerPluginCallbacks(PluginCallbacks* pluginCbs) = 0;

    /**
     * @brief 
     * 
     * @param text 
     * @param usrTag 
     * @param memory 
     * @return int 
     */
    virtual int arun(const char* text, void* usrTag = nullptr, Memory* memory = nullptr) = 0;

};

}

#endif  //AGENT_AGENT_API_H
