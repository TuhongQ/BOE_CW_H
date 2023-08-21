/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 网络加密狗的驱动库，提供网络狗对象的生成、销毁、初始化功能
* Author: y00011914
* Create: 2021-01-01
*/

#ifndef SAFEDOG_LIBRARY_H
#define SAFEDOG_LIBRARY_H

#ifndef SAFEDOG_EXPORT
#define SAFEDOG_API __declspec(dllimport)
#else
#define SAFEDOG_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 创建网络加密狗对象，并返回其对象指针。调用者在使用此指针前需要调用InitSafeDog对网络狗对象进行初始化，否则直接使用会失败
// 参数: void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 说明：
// 返回: 失败返回nullptr,成功返回对象指针
SAFEDOG_API void*CreateSafeDog(void*callback);

// 功能: 销毁CreateSafeDog接口产生的网络加密狗对象，传入对象指针。内部是把空指针转换为正确的对象指针，然后delete
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 返回: 无
SAFEDOG_API void DestroySafeDog(void* dog);

// 功能: 使用ATE账号获取用于初始化网络加密狗的TOKEN，如果已经有TOKEN可以忽略此步骤。通常EMS工厂都是使用的ATE账号，应当通过此接口获取
// 参数: const char* userName ATE账号
// 参数: const char* password ATE密码
// 参数: const char* tokenUrl "http://dongle.pki.hihonor.com/api/ATECenterToken/GenerateToken";
// 参数: char* token 存放TOKEN信息的缓冲区，大小建议＞1024
// 参数: int size TOKEN缓冲区大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  GetNetDogToken(const char* userName, const char* password, const char* tokenUrl, char* token, int size, void*callback);

// 功能: 使用W3账号获取用于初始化网络加密狗的TOKEN，如果已经有TOKEN可以忽略此步骤。通常服务维修都是使用的W3账号，应当通过此接口获取
// 参数: const char* userName W3账号
// 参数: const char* password W3密码
// 参数: char* token 存放TOKEN信息的缓冲区，大小建议＞2048
// 参数: int size TOKEN缓冲区大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  GetNetDogCookie(const char* userName, const char* password, char* token, int size, void*callback);

// 功能: 初始化网络加密狗，不初始化的化无法正常使用
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: const char* token GetNetDogToken接口获取的TOKEN数据
// 参数: const char* serviceUrl "http://dongle.pki.hihonor.com:80/cdic/services/encryption/center"
// 参数: const char* platType 平台类型一般ODM选"ATE"
// 参数: bool isFactory 一般选择true
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  InitNetDogPara(void* dog, const char* userName, const char* token, const char* serviceUrl, const char* platType, bool isFactory);

// 功能: 在调用网络加密狗接口进行加密、解密、签名等动作前，每次都需要调用本接口，用于告诉网络狗服务器本次调用行为关联的AT/DIAG/FASTBOOT命令，便于管控
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: const char* commandID 需要配合 RSA_PriEncryptData_Ext RSA_PriDecryptData_Ext SignWithPSS RsaSignature 等对应的AT/DIAG/FASTBOOT命令
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  SetCommandID(void* dog, const char* commandID);

// 功能: 网络加密狗通用接口
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数：const char* serverName 内部调用的网络狗服务器的 encryption / decrypted / SignWithPSS / signWithPSSEx 服务接口
// 参数: char* pucOut 输出缓冲区，建议的大小＞2048
// 参数: long* pulOutLen 输入&输出参数，输入时指示pucOut缓冲区大小，输出时指示实际错误信息大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  CommonNetDog(void* dog, const char* serverName, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);

// 功能: 获取加密狗证书剩余有效期
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 返回: 失败返回-1，成功返回0
SAFEDOG_API long GetNetDogRemainDays(void* dog);

// 功能: 网络加密狗加密接口，调用 POST encryption 接口
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: char* pucOut 输出缓冲区，建议的大小＞2048
// 参数: long* pulOutLen 输入&输出参数，输入时指示pucOut缓冲区大小，输出时指示实际错误信息大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  RSA_PriEncryptData_Ext(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);

// 功能: 网络加密狗解密接口，调用 POST decrypted 接口
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: char* pucOut 输出缓冲区，建议的大小＞2048
// 参数: long* pulOutLen 输入&输出参数，输入时指示pucOut缓冲区大小，输出时指示实际错误信息大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  RSA_PriDecryptData_Ext(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);

// 功能: 获取本地电脑的加密狗证书ID
// 参数: long* pulCertIDLength 输入&输出参数，输入时指示pucCertID缓冲区大小，输出时指示实际大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  GetCertID(void* dog, char* pucCertID, long* pulCertIDLength);

// 功能: 网络加密狗签名接口，内部调用的网络狗服务器的 SignWithPSS 服务接口
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: char* pucOut 输出缓冲区，建议的大小＞2048
// 参数: long* pulOutLen 输入&输出参数，输入时指示pucOut缓冲区大小，输出时指示实际错误信息大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  SignWithPSS(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);

// 功能: 网络加密狗签名接口，内部调用的网络狗服务器的 signWithPSSEx 服务接口
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: char* pucOut 输出缓冲区，建议的大小＞2048
// 参数: long* pulOutLen 输入&输出参数，输入时指示pucOut缓冲区大小，输出时指示实际错误信息大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  RsaSignature(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);

// 功能: 从网络加密狗服务器根据芯片的chipid获取GID_P3的接口，内部调用的网络狗服务器的 retrieve/gid 服务接口
// 参数: void* dog CreateSafeDog 接口返回的对象指针
// 参数: const char* publicKey 手机中读取的公钥 
// 参数: char* pucOut 输出缓冲区，建议的大小＞2048
// 参数: long* pulOutLen 输入&输出参数，输入时指示pucOut缓冲区大小，输出时指示实际错误信息大小
// 返回: 失败返回-1，成功返回0
SAFEDOG_API int  GetGIDP3ByChipID(void* dog, const char* chipID, long ulIdInLen, const char* publicKey, long ulPubInLen, char* pucOut, long pulOutLen);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif