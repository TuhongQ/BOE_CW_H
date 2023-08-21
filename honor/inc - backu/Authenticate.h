/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: CP鉴权、AP鉴权业务模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#ifndef AUTHENTICATE_EXPORT
#define AUTHENTICATE_API __declspec(dllimport)
#else
#define AUTHENTICATE_API __declspec(dllexport)
#endif
#include <stdint.h>

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能：M/H/U平台的AP鉴权。网络狗需要外部初始化完成，本接口直接使用，返回的HUN为字符串，不是字节流，调用者注意控制缓冲区大小
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：char* hun 鉴权结束后，DUT返回的一串数据，存储起来可供其它地方加密需要时使用
// 参数：uint64_t* outKeyID 存放DUT中公钥ID的数组
// 参数：int keySize 参数uint64_t* outKeyID按照BYTE计算的大小
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
AUTHENTICATE_API int  Authenticate(const char* addr, void* dog, char* hun, int size, uint64_t* outKeyID, int keySize, void* callback);

// 功能：M/H平台CP鉴权，网络狗需要外部初始化完成，本接口直接使用。平板WIFI-ONLY项目没有MODEM不需要CP鉴权
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：char* hun 鉴权结束后，DUT返回的一串数据，存储起来可供其它地方加密需要时使用
// 参数：uint64_t* outKeyID 存放DUT中公钥ID的数组
// 参数：int keySize 参数uint64_t* outKeyID按照BYTE计算的大小
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
AUTHENTICATE_API int  AuthenticateModem(const char* addr, void* dog, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif