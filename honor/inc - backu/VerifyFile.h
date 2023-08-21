/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 文件校验模块
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef VERIFYFILEVALID_LIBRARY_H
#define VERIFYFILEVALID_LIBRARY_H

#ifndef VERIFYFILE_EXPORT
#define VERIFYFILE_API __declspec(dllimport)
#else
#define VERIFYFILE_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能：完成烧片xml文件的checksum校验
// 参数：const char* xmlName 烧片版本xml文件的绝对路径，包含后缀名
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
VERIFYFILE_API int VerifyChecksum(const char* xmlName, void* callback);

// 功能：完成烧片xml文件中所有镜像文件的CRC校验，计算镜像的CRC和镜像对应的CRC.IMG文件中的数据进行比对
// 参数：const char* xmlName 烧片版本xml文件的绝对路径，包含后缀名
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
VERIFYFILE_API int VerifyTotalCrc(const char* xmlName, void* callback);

// 功能：完成烧片版本中指定镜像文件的CRC校验，计算该镜像的CRC和镜像对应的CRC.IMG文件中的数据进行比对
// 参数：const char* imageName 镜像文件的绝对路径，包含后缀名
// 参数：void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
VERIFYFILE_API int VerifyImageCrc(const char* imageName, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif