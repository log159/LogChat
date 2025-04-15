#ifndef SC_MEMORY_API_H
#define SC_MEMORY_API_H

#include "sc_type.h"

#define DEFAULT_WINDOW_SIZE 5
#define DEFAULT_TOKEN_SIZE  9120

namespace SparkChain {

/**
 * @brief base momory api
 * 
 */
class SPARKCHAIN_API Memory {
public:
    virtual ~Memory();

    /**
     * @brief 
     * 
     * @param type 
     * @param maxCache : memory cache capacity
     * @return Memory* : inst
     */
    static Memory* WindowMemory(int maxCache = DEFAULT_WINDOW_SIZE);

    /**
     * @brief 
     * 
     * @param maxCache 
     * @return Memory* 
     */
    static Memory* TokenMemory(int maxTokens = DEFAULT_TOKEN_SIZE);

};

}

#endif