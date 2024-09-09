#ifndef SC_KNOWLEDGE_API_H
#define SC_KNOWLEDGE_API_H

#include "sc_type.h"
#include <string>
#include <vector>
namespace SparkChain {



class SPARKCHAIN_API KnowledgeBase {
public:
    virtual ~KnowledgeBase(){;}

};


typedef struct QADocument {
    QADocument* next;     // 链表节点
    std::vector<std::string> tags;   //标签
    std::string name;
    std::string sourceID;
    std::string url;
    int32_t count;          // 链表节点个数
    int32_t totalLen;       // 链表节点所占内存空间：count*(sizeof(AEE_BaseData)+strlen(node->key)+node->len)
} QADocument, *QADocumentPtr;      // 配置对复用该结构定义


class SPARKCHAIN_API QADocResult  {
public:
    virtual ~QADocResult();

    static QADocResult* create();
    static void destroy(QADocResult* docResult);

    virtual  int getCode() const     = 0;
    virtual  const char* getMsg() const    = 0;

    virtual  std::vector<QADocument> getDocs() const = 0;

    // virtual const std::vector<std::string>  getIDs() const = 0;
    // virtual const  std::vector<std::string>  getTags() const = 0;
private:
    int code = 0;
    std::string msg;
    std::vector<QADocument> docs;   
};







class SPARKCHAIN_API Knowledge : virtual public KnowledgeBase {
public:
    virtual ~Knowledge();

    static Knowledge* create();
    static void destroy(Knowledge* knowledge);

    virtual  QADocResult* upload(const char* uri,const char* tag) const     = 0;
    virtual  QADocResult* deleteByID(std::vector<std::string> ids) const    = 0;
    virtual  QADocResult* deleteAll() const    = 0;
    virtual  int getAllDocs(QADocResult* result) const    = 0;
    virtual  QADocResult* getDocsByID(std::vector<std::string> ids) const    = 0;
    virtual  QADocResult* getDocsByTag(std::vector<std::string> tags) const    = 0;

};



}

#endif  //SC_LLM_API_H
