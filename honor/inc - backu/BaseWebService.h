/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 基于socket实现http请求，C++开发，提供标准C接口给调用者。也可以用于荣耀TGMES访问和微服务调用
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef WEBSERVICE_LIB_H
#define WEBSERVICE_LIB_H

#ifndef WEBSERVICE_EXPORT
#define WEBSERVICE_API __declspec(dllimport)
#else
#define WEBSERVICE_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: Http请求，可以用于调用微服务。相应包缓冲区response要足够大（调用者自行根据实际场景设置），否则可能不够存储返回信息，size表示response缓冲区大小
// 参数: const char* addr IP地址加端口号，如"100.100.186.181:23002"
// 参数: const char* host 域名，可以为""，为空时http请求中的host属性设置为IP地址加端口号，例如dongle.pki.hihonor.com
// 参数：const char* cookie 可以为""，为空时不设置cookie属性
// 参数: const char* path 请求的服务名称，如"/s/com-huawei-cloudate-manufacture-rest-service/v1/manufacture_tgmesall/getproductinfo"
//      TGMES通用接口/s/com-huawei-cloudate-manufacture-rest-service/v1/manufacture_tgmesall/tHatePublicServiceHandle
// 参数: const char* req 服务要求的输入入参，如"{ \"barcode\": \"VER4C19706000001\", \"barcodeType\": \"barcode\"}"。缓冲区大小建议至少1024*1024*10
// 返回: 失败返回-1，成功返回0
WEBSERVICE_API int  HttpRequestPost(const char* addr, const char* host, const char* cookie, const char* path, const char* req, char* rsp, int size, void* callback);

// 功能: Http请求，可以用于调用 WebService 服务。相应包缓冲区response要足够大（调用者自行根据实际场景设置），否则可能不够存储返回信息，size表示response缓冲区大小
// 参数: const char* addr IP地址加端口号，如"100.100.186.181:23002"
// 参数: const char* host 域名，可以为""，为空时http请求中的host属性设置为IP地址加端口号，例如dongle.pki.hihonor.com
// 参数：const char* cookie 可以为""，为空时不设置cookie属性
// 参数: const char* req 服务要求的输入入参，如"{ \"barcode\": \"VER4C19706000001\", \"barcodeType\": \"barcode\"}"。缓冲区大小建议至少1024*1024*10
// 返回: 失败返回-1，成功返回0
WEBSERVICE_API int  HttpRequestTmis(const char* addr, const char* host, const char* cookie, const char* req, char* rsp, int size, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif