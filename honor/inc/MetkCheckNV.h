/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: M平台产品射频校准NV检查测试模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef CHECK_NV_H
#define CHECK_NV_H

#ifndef CHECK_NV_EXPORT
#define CHECK_NV_API __declspec(dllimport) __cdecl
#else
#define CHECK_NV_API __declspec(dllexport) __cdecl
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 射频校准NV的完整性和正确性校验，对于平板WIFI-ONLY版本项目，不需要
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: -1 表示失败，0 表示成功
CHECK_NV_API int  MetkCheckNVChecksum(const char* addr, void* callback);

// 功能: 射频校准NV的完整性和正确性校验，对于平板WIFI-ONLY版本项目，不需要
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: -1 表示失败，0 表示成功
CHECK_NV_API int  MetkCheckNVStatus(const char* addr, void* callback);

// 功能: Q平台射频校准NV的完整性和正确性校验，diag指令，适用于未切换AT指令的产品；对于平板WIFI-ONLY版本项目，不需要
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: -1 表示失败，0 表示成功
CHECK_NV_API int  QualCheckNVStatus(const char* addr, int nvsetmask, void* callback);

// 功能: Q平台射频校准NV的完整性和正确性校验，适用于Diag切换AT的产品
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: -1 表示失败，0 表示成功
CHECK_NV_API int  QualtoATCheckNVStatus(const char* addr, void* callback);
#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif