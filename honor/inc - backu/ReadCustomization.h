/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 读取定制信息，主要用于上传MES系统和外部需要的其它场景，包括EMMCID、PUBLICKEY、UDID等
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef READCUSTOMIZATION_H
#define READCUSTOMIZATION_H

#ifndef READCUSTOMIZATION_EXPORT
#define READCUSTOMIZATION_API __declspec(dllimport)
#else
#define READCUSTOMIZATION_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 触发DUT开始生成锁卡表 PUBLICKEY 字段的数据，一般需要几秒到十几秒才能生成成功，这个时候调用者可以去做其它事情
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  CreatePublicKey(const char* addr, void* callback);

// 功能: 从 DUT 读取锁卡表字段 PUBLICKEY
// 参数: char* buff 存储 PUBLICKEY 的缓冲区，需要足够大，＞1024。内部会给实际读取的数据后补充空格，补够640位长度。原因是和MES配合，早期约定的长度
// 参数: int size 指示 PUBLICKEY 缓冲区大小
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  ReadPublicKey(const char* addr, char* buff, int size, void* callback);

// 功能: 从 DUT 读取锁卡表字段 EMMCID
// 参数: char* buff 存储 EMMCID 的缓冲区，需要足够大，＞128。内部会给实际读取的数据后补充空格，补够48位长度。原因是和MES配合，早期约定的长度
// 参数: int size 指示 EMMCID 缓冲区大小
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  ReadEmmcID(const char* addr, char* buff, int size, void* callback);

// 功能: 从 DUT 读取锁卡表字段 UDID
// 参数: char* buff 存储 UDID 的缓冲区，需要足够大，＞128
// 参数: int size 指示 UDID 缓冲区大小
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  ReadUDID(const char* addr, char* buff, int size, void* callback);

// 功能: 读取整机SN
// 参数: char* data 存储 SN 的缓冲区，需要足够大，＞128
// 参数: int size 指示 SN 缓冲区大小
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  ReadSN(const char* addr, char* data, int size, void* callback);

// 功能: 从 DUT 读取单板条码
// 参数: char* buff 存储 单板条码 的缓冲区，需要足够大，＞16
// 参数: int size 指示 UDID 缓冲区大小   
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  ReadBarcode(const char* addr, char* buff, int size, void* callback);

// 功能: 从 DUT 读取runmode
// 参数: char* buff 存储 runmode 的缓冲区，需要足够大，＞16
// 参数: int size 指示 UDID 缓冲区大小
// 返回: -1 表示失败，0 表示成功
READCUSTOMIZATION_API int  ReadRunMode(const char* addr, char* buff, int size, void* callback);


#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif