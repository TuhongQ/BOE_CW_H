/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 写定制信息业务模块，本接口中只提供明文写入信息的接口，需要使用加密算法的写入接口在 WriteCiphertextCustomization
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef WRITECUSTOMIZATION_H
#define WRITECUSTOMIZATION_H

#ifndef WRITECUSTOMIZATION_EXPORT
#define WRITECUSTOMIZATION_API __declspec(dllimport)
#else
#define WRITECUSTOMIZATION_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 写入锁卡表 CERTIFY_CODE 电子认证标签
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteCertifyCode(const char* addr, const char* val, void* callback);

// 功能: 写入锁卡表 RSN 字段，即 RPMB 分区初始化
// 参数: const char* val 锁卡表中的定制字段原始值，只能是1，该字段要么不配置配置的话则值为1
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteRSN(const char* addr, const char* val, void* callback);

// 功能: 写入锁卡表 SECRETTYPE 字段，只支持M/U平台。不支持H平台，因为H平台的逻辑比较复杂目前兼容没有意义
// 参数: const char* val 锁卡表中的定制字段原始值，应该0/1。实际上如果是0，直接退出也可以，软件内部就是直接return的，没有做任何动作。保留是为了兼容旧锁卡表逻辑
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteSecretType(const char* addr, const char* val, void* callback);

// 功能: 写入锁卡表 TRUST_DEVICE_IDS 字段，和Hota升级有关，缺失无法升级，要求必须先写入IMEI(平板WIFI-ONLY项目除外)和SN才会生效
// 参数: const char* ids 锁卡表中的定制字段原始值
// 参数: const char* meid 有MEID时提供，没有时为nullptr
// 参数: const char* imei1 主卡IMEI号，平板WIFI-ONLY项目，没有时设置为nullptr
// 参数: const char* imei2 副卡IMEI号，没有时为nullptr
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);

// 功能: 写入任务令 Hw_Device_Certs_1 ... Hw_Device_Certs_5 字段，即PKI荣耀设备证书
// 参数: const char* cert1 ... cert5 任务令中分配的设备证书字段数据
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteDeviceCerts(const char* addr, const char* cert1, const char* cert2, const char* cert3, const char* cert4, const char* cert5, void* callback);

// 功能: 写入锁卡表 MARKETING_NAME 字段
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteMarketingName(const char* addr, const char* val, void* callback);

// 功能: 写入锁卡表 BENCHMARKFLAG 字段，即防跑分标志位
// 参数: const char* val 锁卡表中的定制字段原始值
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteBenchmarkFlag(const char* addr, const char* val, void* callback);

// 功能: 写入任务令 A_KeyAttestation_G_1 ... A_KeyAttestation_G_4 字段，即谷歌设备证书
// 参数: const char* key1 ... key4 任务令中分配的设备证书字段数据，其中key4有可能没有数据，此时key4传入nullptr
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteKeyAttestation(const char* addr, const char* key1, const char* key2, const char* key3, const char* key4, void* callback);

// 功能: 写入锁卡表 IDS_ATTESTATION 字段，和Hota升级有关，缺失无法升级，要求必须先写入IMEI(平板WIFI-ONLY项目除外)和SN才会生效
// 参数: const char* ids 锁卡表中的定制字段原始值
// 参数: const char* meid 有MEID时提供，没有时为nullptr
// 参数: const char* imei1 主卡IMEI号，平板WIFI-ONLY项目，没有时设置为nullptr
// 参数: const char* imei2 副卡IMEI号，没有时为nullptr
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);

// 功能: 写入锁卡表 HTEE RSN 字段，即 TEE RPMB 分区初始化
// 参数: const char* val 锁卡表中的定制字段原始值，RSN字段内容取值范围1,2,3；bit0为1表示支持QTEE，bit1为1表示支持HTEE
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteTEERPMB(const char* addr, const char* val, void* callback);

// 功能: 产线操作初始化安全存储芯片
// 参数: const char* mode 表示操作安全存储芯片的操作模式
// 入参mode取值：init(升级版本作用为检查安全芯片是否完成初始化)、set_urs(用于设置安全芯片状态为URS状态，设置成功后安全芯片不能再次被初始化)、check_urs(用于检查安全芯片状态是否已经切换为URS状态）
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteSecFlash(const char* addr, const char* mode, void* callback);

// 功能: 写入锁卡表 THEMECOLOR 字段，只支持DeviceColor(BACK、MID、FRONT)颜色
// 参数: const char* deviceColor 锁卡表定制字段中DeviceColor(BACK、MID、FRONT)颜色的原始值
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteDeviceColor(const char* addr, const char* deviceColor, void* callback);

// 功能: 写入CPL信息
// 参数: const char* cpl CPL(Cancel Preload List) 取消预装清单
// 返回: -1 表示失败，0 表示成功
WRITECUSTOMIZATION_API int  WriteCPL(const char* addr, const char* cpl, void* callback);
#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif