/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 写和校验标志位模块，包括加密写入MMI标志位等功能
* Author: y00011914
* Create: 2021-03-12
*/
#ifndef MANUFACTUREFLAG_H
#define MANUFACTUREFLAG_H

#ifndef MANUFACTUREFLAG_EXPORT
#define MANUFACTUREFLAG_API __declspec(dllimport)
#else
#define MANUFACTUREFLAG_API __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif // _cplusplus

// 功能: 写入MMI标志位，支持MMI1、MMI2等
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数：int keyID 鉴权时存放DUT中公钥ID的数组中的一位
// 参数: const char* val 要写入的整体MMI标志位的字符串形式，对应的HEX数据中，每个bit位表示一个MMI的标志位，0x01表示MMI1，0x08表示MMI2
// 参数：bool isQualPlat 是否为高通平台
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
MANUFACTUREFLAG_API int  WriteMMIFlag(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

#ifdef __cplusplus
}
#endif // _cplusplus

#endif