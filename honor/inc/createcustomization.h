/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 主要用于生成、读取和校验RKP数据
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef CREATECUSTOMIZATION_H
#define CREATECUSTOMIZATION_H

#ifndef CREATECUSTOMIZATION_EXPORT
#define CREATECUSTOMIZATION_API __declspec(dllimport)
#else
#define CREATECUSTOMIZATION_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 生成RKP数据和RKP校验数据, 包括校验Hash值
/* 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
         Win平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
         Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0 */
// 参数: char *rkpData 输出参数，回传RKP数据
// 参数: int size1 输入参数，rkpData数组大小
// 参数: char *verifyData 输出参数，回传RKP校验数据
// 参数: int size2 输入参数，verifyData数组大小
// 参数: ivoid* callback 回调函数
// 返回: -1 表示失败，0 表示成功
CREATECUSTOMIZATION_API int GetRkpAndVdData(const char* addr, char *rkpData, int size1, char *verifyData, int size2, void* callback);

// 功能: 校验RKP数据
// 参数: char* verifyData 输入参数，传入RKP校验数据
// 参数: void* callback 回调函数
// 返回: -1 表示失败，0 表示成功
CREATECUSTOMIZATION_API int VerifyRkpData(const char* addr, char* verifyData, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif