/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: CP鉴权、AP鉴权业务模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef AUTHENTICATEFASTBOOT_H
#define AUTHENTICATEFASTBOOT_H

#ifndef AUTHENTICATEFASTBOOT_EXPORT
#define AUTHENTICATEFASTBOOT_API __declspec(dllimport)
#else
#define AUTHENTICATEFASTBOOT_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能：完成FASTBOOT模式下的网络加密狗鉴权，支持20年之前的M/H/Q平台项目，没有合入PSS
// 参数：const char* devPath 表示Fastboot设备的设备路径
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
AUTHENTICATEFASTBOOT_API int  AuthenticateFastboot(const char* devPath, void* dog, void* callback);

// 功能：完成FASTBOOT模式下的网络加密狗鉴权，支持21年之后的M/H/Q/U平台项目，合入PSS
// 参数：const char* devPath 表示Fastboot设备的设备路径
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：char* hun 鉴权结束后，DUT返回的一串数据，存储起来可供其它地方加密需要时使用
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
AUTHENTICATEFASTBOOT_API int  AuthenticateFastbootV1(const char* devPath, void* dog, unsigned char hun[8], void* callback);

// 功能：完成FASTBOOT模式下的加密写研发模式
// 参数：const char* devPath 表示Fastboot设备的设备路径
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：const char* hun 接口 AuthenticateFastbootV1 返回的数据，需要在这里传入，加密过程中需要使用
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
AUTHENTICATEFASTBOOT_API int  FastbootWriteRdMode(const char* devPath, void* dog, const unsigned char hun[8], void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif