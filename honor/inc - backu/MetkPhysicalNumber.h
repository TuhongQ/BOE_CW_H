/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: M平台产品物理号（MEID、IMEI）写入和校验测试模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef METKPHYSICALNUMBER_H
#define METKPHYSICALNUMBER_H

#ifndef METKPHYSICALNUMBER_EXPORT
#define METKPHYSICALNUMBER_API __declspec(dllimport)
#else
#define METKPHYSICALNUMBER_API __declspec(dllexport)
#endif
#include "MetkPhysicalNumberDefine.h"
#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: M 平台写物理号接口，调用前手机AP/CP都可以，本接口结束会将手机切换到AP侧
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const PhyNumInfo* phynum 存储物理号的结构体
// 返回: -1 表示失败，0 表示成功
METKPHYSICALNUMBER_API int  MetkWritePhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback);

// 功能: M 平台校验物理号接口，调用前手机AP/CP都可以，本接口结束会将手机切换到CP侧
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const PhyNumInfo* phynum 存储物理号的结构体
// 返回: -1 表示失败，0 表示成功
METKPHYSICALNUMBER_API int  MetkCheckPhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback);

METKPHYSICALNUMBER_API int  QualCheckPhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif