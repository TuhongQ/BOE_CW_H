/*
* Copyright (c) 2020-2021 Honor Device Co., Ltd. All rights reserved.
* Description:
* Author: w0008474
* Create: 2020-03-08
*/
#ifndef SETTESTMODEY_H
#define SETTESTMODE_H

#ifndef SETTESTMODE_EXPORT
#define SETTESTMODE_API __declspec(dllimport)
#else
#define SETTESTMODE_API __declspec(dllexport)
#endif
#include <string>
#include "SetTestModeDefine.h"
#include "inc/DevInfo.h"

using namespace std;
#ifdef __cplusplus

extern "C" {
#endif // _cplusplus

// 功能：实现DUT开机电流的读取，鉴权写BSN及校验，写CWN标志位,关闭充电的功能
// 参数：const char* mainBoardAddr      主控板地址
// 参数：const char* powerAddr          电源地址
// 参数：const char* usbPath            usb路径
// 参数：SEARCH_STRATEGY portType       搜索虚拟串口的策略
// 参数：const char* bsn                单板条码
// 参数：DevInfo *devsResult            搜到的设备信息
// 参数：const char *userName           用户名
// 参数: const char *token              用户信息
// 参数：const char *serviceUr
// 参数：const char *platType                   指定加密狗类型(1-1024加密狗\2-2048加密狗\3-网络加密狗\0-任何加密狗)
// 参数：bool    isFactory                       是否是工厂
// 返回：-1 表示失败,0 表示成功
SETTESTMODE_API int SetTestMode(const char *mainBoardAddr, const char *powerAddr, const char *usbPath, SEARCH_STRATEGY portType, const char *bsn,  DevInfo *devsResult, void *dog, bool isFactory, void *callback);

// 功能：实现MTK平台下搜索端口功能
// 参数：const char* usbPath            usb路径
// 参数：DevInfo *devsResult            搜到的设备信息
// 参数：const char* findDeviceType     设备类型
// 返回：-1 表示失败,0 表示成功
SETTESTMODE_API int SerchPort(const char* usbPath, DevInfo *devsResult,  const char* findDeviceType, void* callback);

// 功能：实现MTK平台下在固定时间内搜索端口功能
// 参数：const char* usbPath            usb路径
// 参数：DevInfo *devsResult            搜到的设备信息
// 参数：const char* findDeviceType     设备类型
// 参数：int timeout                    超时时间,单位 s
// 返回：-1 表示失败,0 表示成功
SETTESTMODE_API int SerchPortInTimeout(const char* usbPath, DevInfo *devsResult,  const char* findDeviceType, int timeout, void* callback);
#ifdef __cplusplus
}
#endif // _cplusplus

#endif