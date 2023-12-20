#ifndef SC_TYPE_API_H
#define SC_TYPE_API_H

/**
 * SPARKCHAIN API type
 */
#if defined(_MSC_VER)            /* Microsoft Visual C++ */
#   if !defined(SPARKCHAIN_API)
#       if defined(SPARKCHAIN_EXPORT)
#           define SPARKCHAIN_API __declspec(dllexport)
#       else
#           define SPARKCHAIN_API __declspec(dllimport)
#       endif
#   endif
#elif defined(__BORLANDC__)      /* Borland C++ */
#   if !defined(SPARKCHAIN_API)
#       define SPARKCHAIN_API __stdcall
#   endif
#elif defined(__WATCOMC__)       /* Watcom C++ */
#   if !defined(SPARKCHAIN_API)
#       define SPARKCHAIN_API __stdcall
#   endif
#else                            /* Any other including Unix */
#   if !defined(SPARKCHAIN_API)
#       if defined(SPARKCHAIN_EXPORT)
#           define SPARKCHAIN_API __attribute__ ((visibility("default")))
#       else
#           define SPARKCHAIN_API
#       endif
#   endif
#endif

#if defined(_MSC_VER)            /* Microsoft Visual C++ */
  #pragma pack(push, 8)
#elif defined(__BORLANDC__)      /* Borland C++ */
  #pragma option -a8
#elif defined(__WATCOMC__)       /* Watcom C++ */
  #pragma pack(push, 8)
#else                            /* Any other including Unix */
#endif

typedef enum {
    AGENT_Event_UnKnown  = -1,
    AGENT_Event_Start    = 0,  // Agent开始事件
    AGENT_Event_Progress = 1,  // Agent进度事件
    AGENT_Event_End      = 2,  // Agent结束事件
    AGENT_Event_Timeout  = 3,  // Agent超时事件

    // 在线能力连接状态事件
    LLM_Event_Null = 10,          // 空连接状态
    LLM_Event_Init,               // 初始状态
    LLM_Event_Connecting,         // 正在连接
    LLM_Event_ConnTimeout,        // 连接超时
    LLM_Event_Failed,             // 连接失败
    LLM_Event_Connected,          // 已经连接
    LLM_Event_Error,              // 收发出错，意味着断开连接
    LLM_Event_Disconnected,       // 断开连接，一般指心跳超时，连接无错误
    LLM_Event_Closing,            // 正在关闭连接
    LLM_Event_Closed,             // 已经关闭连接
    LLM_Event_Responding,         // 网络连接正在响应
    LLM_Event_ResponseTimeout,    // 网络连接响应超时

    //Chain的时间
    CHAIN_EVENT_UnKnown = 30,

} SPARKCHAIN_EVENT;

/* Reset the structure packing alignments for different compilers. */
#if defined(_MSC_VER)            /* Microsoft Visual C++ */
#pragma pack(pop)
#elif defined(__BORLANDC__)      /* Borland C++ */
#pragma option -a.
#elif defined(__WATCOMC__)       /* Watcom C++ */
#pragma pack(pop)
#endif

#endif