#pragma once
#include "sc_llm.h"

#include <string>
#include <unordered_set>
#include <map>

namespace SparkChain {

class SPARKCHAIN_API Prompt {
public:
    Prompt(const std::string &tmpl);
    virtual ~Prompt();
    std::string format(std::map<std::string, std::string> &input);

private:
    std::string mValue;
    std::unordered_set<std::string> mInput;
};

}
