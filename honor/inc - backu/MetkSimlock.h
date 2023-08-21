/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: M平台产品SIMLOCK写入和校验测试模块
* Author: y00011914
* Create: 2021-05-08
*/
#ifndef METKSIMLOCK_H
#define METKSIMLOCK_H

#ifndef METKSIMLOCK_EXPORT
#define METKSIMLOCK_API __declspec(dllimport)
#else
#define METKSIMLOCK_API __declspec(dllexport)
#endif
#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: M 平台擦除SIMLOCK，调用前手机要求在CP模式。CW工位必须先调用
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: -1 表示失败，0 表示成功
METKSIMLOCK_API int  MetkUnlockSimlock(const char* addr, void* callback);

// 功能: M 平台写SIMLOCK，调用前手机要求在CP模式。不需要写入SIMLOCK时，不需要调用此接口
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* password SIMLOCK解锁码，只有有SIMLOCK的时候才用到，内容为锁卡表 NCK_NCKNSCKSPCKRESET 字段的值，没有时，可以为nullptr
// 参数: const char* hash SIMLOCK配置表格的hash值，用于校验cfg文件是否使用错误，内容为锁卡表 INI_HASH 字段的值，没有时，可以为nullptr
// 参数: const char* cfg 配置SIMLOCK信息的表格路径，没有时，可以为nullptr
// 返回: -1 表示失败，0 表示成功
METKSIMLOCK_API int  MetkWriteSimlock(const char* addr, const char* password, const char* hash, const char* cfg, void* callback);

// 功能: M 平台校验SIMLOCK，调用前手机要求在CP模式。不管是否有SIMLOCK，MC工位都要调用
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: char simlockFlag 锁卡表中SIMLOCK_WRITE字段的值，为"0"或者"1"。为"0"时，const char* cfg 为nullptr，为"1"时const char* cfg传入表格路径
// 参数: const char* cfg 配置SIMLOCK信息的表格路径，没有时，可以为nullptr
// 返回: -1 表示失败，0 表示成功
METKSIMLOCK_API int  MetkCheckSimlock(const char* addr, char simlockFlag, const char* cfg, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif