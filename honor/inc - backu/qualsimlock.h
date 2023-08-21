/*
* Copyright (c) Honor Technologies Co., Ltd. 2020. All rights reserved.
* Description: Qualsimlock
* Author: c00012260
* Create: 2021-11-10
*/
#ifndef QUALSIMLOCK_LIBRARY_H
#define QUALSIMLOCK_LIBRARY_H

#ifndef QUALSIMLOCK_EXPORT
#define QUALSIMLOCK_API __declspec(dllimport) __cdecl
#else
#define QUALSIMLOCK_API __declspec(dllexport) __cdecl
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

QUALSIMLOCK_API int QualUnlockSimlock(const char* addr, void* callback);

// 功能: Q 平台写SIMLOCK，调用前手机要求在CP模式。不需要写入SIMLOCK时，不需要调用此接口
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* password SIMLOCK解锁码，只有有SIMLOCK的时候才用到，内容为锁卡表 NCK_NCKNSCKSPCKRESET 字段的值，没有时，可以为nullptr
// 参数: const char* hash SIMLOCK配置表格的hash值，用于校验cfg文件是否使用错误，内容为锁卡表 INI_HASH 字段的值，没有时，可以为nullptr
// 参数: const char* cfg 配置SIMLOCK信息的表格路径，没有时，可以为nullptr
// 返回: -1 表示失败，0 表示成功
QUALSIMLOCK_API int  QualWriteSimlock(const char* addr, const char* password, const char* hash, const char* cfg, void* callback);

// 功能: Q 平台校验SIMLOCK，调用前手机要求在CP模式。不管是否有SIMLOCK，MC工位都要调用
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: char simlockFlag 锁卡表中SIMLOCK_WRITE字段的值，为"0"或者"1"。为"0"时，const char* cfg 为nullptr，为"1"时const char* cfg传入表格路径
// 参数: const char* cfg 配置SIMLOCK信息的表格路径，没有时，可以为nullptr
// 返回: -1 表示失败，0 表示成功
QUALSIMLOCK_API int  QualCheckSimlock(const char* addr, char simlockFlag, const char* cfg, void* callback);
#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif