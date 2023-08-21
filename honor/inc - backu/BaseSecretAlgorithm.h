/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 定制算法基础模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef SECRETALGORITHM_LIBRARY_H
#define SECRETALGORITHM_LIBRARY_H

#ifndef SECRETALG_EXPORT
#define SECRETALG_API __declspec(dllimport)
#else
#define SECRETALG_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 初始FRP KEY加密方案
// 参数: psn 从EMMCID的第20位开始（从0开始计数）取8位字符串，strtoul 转换为uint64即为此参数
// 返回: 失败返回-1，成功返回0
SECRETALG_API int  EncryptFrpKey(const char frpKey[16], unsigned int psn, void *dog, int keyID, char buff[2048]);

// 功能: V1版本FRP KEY加密方案，使用PSS填充签名，替代加密
// 参数: psn 从EMMCID的第20位开始（从0开始计数）取8位字符串，strtoul 转换为uint64即为此参数
// 返回: 失败返回-1，成功返回0
SECRETALG_API int  EncryptFrpKeyV1(const char frpKey[16], unsigned int psn, void *dog, int keyID, char buff[2048], bool isQualPlat);

// 返回: 失败返回-1，成功返回0
SECRETALG_API int  EncryptAccKey(const char accKey[16], const char hun[8],void* dog, int keyID, char buff[2048]);

// 功能: V1版本DIAG_UNLOCK KEY加密方案，使用PSS填充签名，替代加密
// 参数: hun 为鉴权结束后返回的 HUN 字符串，通过 HexString 转 BYTE 之后得到
// 返回: 失败返回-1，成功返回0
SECRETALG_API int  EncryptAccKeyV1(const char accKey[16], const char hun[8],void* dog, int keyID, char buff[2048], bool isQualPlat);

// 返回: 失败返回-1，成功返回0
SECRETALG_API int  EncryptRdMode(const char hun[8], void* dog, int keyID, char buff[2048]);

// 功能: V1版本写研发模式算法，使用PSS填充签名，替代加密
// 参数: hun 为鉴权结束后返回的 HUN 字符串，通过 HexString 转 BYTE 之后得到
// 返回: 失败返回-1，成功返回0
SECRETALG_API int  EncryptRdModeV1(const char hun[8], void* dog, int keyID, char buff[2048]);

// 返回: 失败返回-1，成功返回0
SECRETALG_API int  FacSignData(const char hun[32], const char random[16], void* dog, int keyID, const char* value, const char* tag, char buff[2048]);

// 功能: V1版本写 BTMAC WIFIMAC UDID SN BSN算法，使用PSS填充签名，替代加密
// 参数: hun random 都是单独的指令返回的字符串，通过HEXSTR转BYTE之后得到的数据
// 返回: 失败返回-1，成功返回0
SECRETALG_API int  FacSignDataV1(const char hun[32], const char random[16], void* dog, int keyID, const char* value, const char* tag, char buff[2048], bool isQualPlat);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif