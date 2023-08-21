/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 校验定制信息的业务模块，包含锁卡表中的字段，但是不包含诸如非法维修、翻新机等（在定制关键动作中）
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef VERIFYCUSTOMIZATION_H
#define VERIFYCUSTOMIZATION_H

#ifndef VERIFYCUSTOMIZATION_EXPORT
#define VERIFYCUSTOMIZATION_API __declspec(dllimport)
#else
#define VERIFYCUSTOMIZATION_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 校验锁卡表 CERTIFY_CODE 电子认证标签
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyCertifyCode(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 RSN 字段，检查 RPMB 分区初始化是否成功
// 参数: const char* val 锁卡表中的定制字段原始值，只能是1，该字段要么不配置配置的话则值为1
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyRSN(const char* addr, void* callback);

// 功能: 校验锁卡表 SECRETTYPE 字段，只支持M/U平台。不支持H平台，因为H平台的逻辑比较复杂目前兼容没有意义
// 参数: const char* val 锁卡表中的定制字段原始值，应该0/1。实际上如果是0，直接退出也可以，软件内部就是直接return的，没有做任何动作。保留是为了兼容旧锁卡表逻辑
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifySecretType(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 QFUSE_REGISTER_DATA 字段，只支持M/U/Q平台
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyQfuseRegisterData(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 TRUST_DEVICE_IDS 字段，该功能和Hota升级有关
// 参数: const char* ids 锁卡表中的定制字段原始值
// 参数: const char* meid 有MEID时提供，没有时为nullptr
// 参数: const char* imei1 主卡IMEI号，没有时为nullptr
// 参数: const char* imei2 副卡IMEI号，没有时为nullptr
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);

// 功能: 校验任务令 Hw_Device_Certs_VD 字段，即PKI荣耀设备证书
// 参数: const char* certVD 任务令中分配的设备证书字段的校验数据
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyDeviceCerts(const char* addr, const char* certVD, void* callback);

// 功能: 校验锁卡表 MARKETING_NAME 字段
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyMarketingName(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 BENCHMARKFLAG 字段，即防跑分标志位
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyBenchmarkFlag(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 PUBLICKEY
// 参数: const char* val 校验PUBLICKEY字段，输入参数来源于CW工位上传到MES系统的数据
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyPublicKey(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 EMMCID
// 参数: const char* val 校验EMMCID字段，输入参数来源于CW工位上传到MES系统的数据
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyEmmcID(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 HARDWARESIZE
// 参数: const char* val 校验HARDWARESIZE字段，输入参数来源于CW工位上传到MES系统的数据
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyHardwareSize(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 UDID
// 参数: const char* val 从TGMES 获取的在 CW 工位上传的 UDID 数据
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyUDID(const char* addr, const char* val, void* callback);

// 功能: 校验整机 SN
// 参数: const char* val MES系统分配的整机条码
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifySN(const char* addr, const char* val, void* callback);

// 功能: 校验单板条码
// 参数: const char* val MES系统分配的，单板条码值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyBarcode(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 VENDOR COUNTRY
// 参数: const char* vendor 锁卡表中的定制字段原始值
// 参数: const char* country 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyVendorCountry(const char* addr, const char* vendor, const char* country, void* callback);

// 功能: 校验锁卡表 MAC
// 参数: const char* val 任务令中提供的MAC值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyBTMAC(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 WIFI
// 参数: const char* val 任务令中提供的MAC值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyWifiMAC(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 PRODUCT_NAME
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyProductName(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 NCK_DIAGUNLOCK
// 参数: const char* nckDiagUnlock 密码，16位数字和大写字母组合的随机数字符串
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyAccLock(const char* addr, const char* nckDiagUnlock, void* callback);

// 功能: 校验锁卡表 LOCKTYPE
// 参数: const char* lockType 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyUserLock(const char* addr, const char* lockType, void* callback);

// 功能: 校验锁卡表 SIMCARDMODE
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifySimcardMode(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 FRPKEY
// 参数: const char* val FRP解锁码，16位数字和大写字母组合的随机数字符串
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyFrpKey(const char* addr, const char* val, void* callback);

// 功能: 校验锁卡表 IDS_ATTESTATION 字段，该功能和Hota升级有关
// 参数: const char* ids 锁卡表中的定制字段原始值
// 参数: const char* meid 有MEID时提供，没有时为nullptr
// 参数: const char* imei1 主卡IMEI号，没有时为nullptr
// 参数: const char* imei2 副卡IMEI号，没有时为nullptr
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);

// 功能: 校验任务令 A_KeyAtte_G_Verify 字段，即谷歌设备证书
// 参数: const char* keyVD 任务令中分配的设备证书字段的校验数据
// 返回: -1 表示失败，0 表示成功
VERIFYCUSTOMIZATION_API int  VerifyKeyAttestation(const char* addr, const char* keyVD, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif