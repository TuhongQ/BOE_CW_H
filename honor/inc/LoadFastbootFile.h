/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: Fastboot降级、加载业务模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef LOADDFASTBOOTFILE_FASTBOOT_H
#define LOADDFASTBOOTFILE_FASTBOOT_H

#ifndef LOAD_FASTBOOT_EXPORT
#define FBLOAD_API __declspec(dllimport) __cdecl
#else
#define FBLOAD_API __declspec(dllexport) __cdecl
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能：实现降级功能，会PSS鉴权并写入RD模式。解析XML文件并加载所有 partially_erase_configuration 节点的镜像
// 参数：const char* devPath 表示Fastboot设备的设备路径
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
FBLOAD_API int DegradeFastboot(const char* devPath, void* dog, const char* fileName, void* callback);

// 功能：实现降级功能，会PSS鉴权并写入RD模式。解析XML文件并加载所有 fastboot 节点的镜像
// 参数：const char* devPath 表示Fastboot设备的设备路径
// 参数：void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
FBLOAD_API int DownloadFastboot(const char* devPath, void* dog, const char* fileName, void* callback);
                        
#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif