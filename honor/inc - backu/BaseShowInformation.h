/*
 * Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
 * Description: LOG打印和数据回传基础模块，通过回调函数实现
 * Author: y00011914
 * Create: 2021-01-01
 */
#ifndef SHOWINFORMATION_LIBRARY_H
#define SHOWINFORMATION_LIBRARY_H

#ifndef SHOWINFO_EXPORT
#define SHOWINFO_API __declspec(dllimport)
#else
#define SHOWINFO_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 设置记录器，用于防呆。避免定制动作遗漏
SHOWINFO_API void SaveFunctionRecord(void* callbackParam, const char* tagName);

// 功能: 打印正常的LOG信息
SHOWINFO_API void ShowNormalInformation(void* callbackParam, const char* info);

// 功能: 打印失败的LOG信息
SHOWINFO_API void ShowFailInformation(void* callbackParam, const char* info);

// 功能: 打印DEBUG LOG信息
SHOWINFO_API void ShowDebugInformation(void* callbackParam, const char* info);

// 功能: 回传一个测试结果的值，值为字符串格式
SHOWINFO_API void UploadStringValue(void* callbackParam, const char* info, const char* value);

// 功能: 回传一个double格式的测试结果，并给出测试门限
SHOWINFO_API void UploadDoubleValue(void* callbackParam, const char* info, double value, double upLimit, double lowLimit);

// 功能: 当需要确认是否有外部信息触发停止时，可以调用此函数。如果有指针为空等情况，都认为不需要停止
// 返回：当外部需要停止时此函数返回-1，当外部不需要停止时次函数返回0
SHOWINFO_API int  StopTestWhenManualBreak(void* callbackParam);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif // SHOWINFORMATION_LIBRARY_H

