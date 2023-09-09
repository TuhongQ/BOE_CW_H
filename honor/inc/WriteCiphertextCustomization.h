/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 写定制信息业务模块，本接口中只提供加密写入信息的接口，明文写入的接口在WriteCustomization
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef WRITECIPHERTEXTCUSTOMIZATION_H
#define WRITECIPHERTEXTCUSTOMIZATION_H

#ifndef WRITECIPHERTEXTCUSTOMIZATION_EXPORT
#define WRITECIPHERTEXTCUSTOMIZATION_API __declspec(dllimport)
#else
#define WRITECIPHERTEXTCUSTOMIZATION_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 计算 UDID
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* bt 即BT MAC值
// 参数: const char* wlan 即WIFI MAC值
// 参数: char* udid 输出参数，存放UDID值的缓冲区，size参数指示缓冲区大小，必须＞64
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  CreateUDID(const char* addr, const char* sn, const char* bt, const char* wlan, char* udid, int size, void* callback);

// 功能: 写入锁卡表 UDID
// 参数: const char* val 接口 CreateUDID 计算出来的UDID值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteUDID(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入整机 SN
// 参数: const char* val MES系统分配的整机条码值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteSN(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入单板条码
// 参数: const char* val MES系统分配的，单板条码值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteBarcode(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入锁卡表 VENDOR COUNTRY
// 参数: const char* vendor 锁卡表中的定制字段原始值
// 参数: const char* country 锁卡表中的定制字段原始值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteVendorCountry(const char* addr, void* dog, int keyID, const char* vendor, const char* country, void* callback);

// 功能: 写入锁卡表 MAC
// 参数: const char* val 任务令中提供的MAC值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteBTMAC(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入锁卡表 WIFI
// 参数: const char* val 任务令中提供的MAC值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteWifiMAC(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入锁卡表 PRODUCT_NAME
// 参数: const char* val 锁卡表中的定制字段原始值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteProductName(const char* addr, void* dog, int keyID, const char* val, void* callback);

// 功能: 写入锁卡表 NCK_DIAGUNLOCK
// 参数: const char* nckDiagUnlock 密码，16位数字和大写字母组合的随机数字符串
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数: const char hun[8] AP鉴权接口返回的HUN数据，这里是长度为8的数组，不是字符串
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteAccLock(const char* addr, void* dog, int keyID, const char* nckDiagUnlock, const char hun[8], bool isQualPlat, void* callback);

// 功能: 写入锁卡表 LOCKTYPE
// 参数: const char* lockType 锁卡表中的定制字段原始值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数: const char hun[8] AP鉴权接口返回的HUN数据，这里是长度为8的数组，不是字符串
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteUserLock(const char* addr, void* dog, int keyID, const char* lockType, const char hun[8], bool isQualPlat, void* callback);

// 功能: 写入锁卡表 SIMCARDMODE
// 参数: const char* val 锁卡表中的定制字段原始值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteSimcardMode(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入锁卡表 FRPKEY
// 参数: const char* val FRP解锁码，16位数字和大写字母组合的随机数字符串
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteFrpKey(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写入锁卡表 FUSE_GID
// 参数: const char* chipid 为锁卡表定制字段FUSE_GID的原始值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteFuseGid(const char* addr, void* dog, const char* chipid, void* callback);

// 功能: 检查锁卡表 FUSE_GID
// 参数: const char* chipid 为锁卡表定制字段FUSE_GID的原始值
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int CheckFuseGid(const char* addr, void* dog, const char* chipid, void* callback);

// 功能: 写入鉴权标志位AUTHEN
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteAUTHEN(const char* addr, void* dog, int keyID, bool isQualPlat, void* callback);

// 功能: 检测大屏版本runmode是否为factory
// 参数: const char* val factory / normal，小写
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int  WriteRunMode(const char* addr, void* dog, int keyID, const char* val, void* callback);

// 功能: 写入keybox信息
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数: int keyID AP鉴权接口返回的数据解密ID，为第4组ID值
// 参数：const char* widevineDRMKey 入参，keybox的原始字符串信息
// 参数：const char* widevineKeyCRC 入参，keybox原始字符串的CRC值
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteKeyBox(const char* addr, void* dog, int keyID, const char* widevineDRMKey, const char* widevineKeyCRC, bool isQualPlat, void* callback);

// 功能: 校验keybox数据信息
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 参数: int keyID AP鉴权接口返回的数据解密ID，为第4组ID值
// 参数：const char* widevineDRMKey 入参，keybox的原始字符串信息
// 参数：const char* widevineKeyCRC 入参，keybox原始字符串的CRC值
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int CheckKeyBox(const char* addr, void* dog, int keyID, const char* widevineDRMKey, const char* widevineKeyCRC, bool isQualPlat, void* callback);

// 功能: 写入产线场景参数，包含：无线自启动参数，MMI2自启动参数等
// 参数：const char* sceneName,产线场景名称，无线自启动参数：WIRELESSUPDATE；MMI2自启动参数：AUTOMMI2；
// 参数: const char* scenePara,场景参数明文信息：
// 1、无线自启动场景：APK建立wifi连接时的路由器配置参数，举例：ssid:HN_BD_CABINET1_ROUTER2_5;password:hihonor123;cw2Ip:192.168.1.100;
// 2、MMI2自启动场景：无业务参数时固定为字符串 NONE；
// 参数：const char* sceneInfo，取值：ONCE(仅自启动一次，手机重启标志位失效)/FORVER(永久生效，如果需要删除该标志位，需要专门执行擦除指令AT^FACENVPARACFG =ERASE)
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteFacEnvParacfg(const char* addr, void* dog, int keyID, const char* sceneName, const char* scenePara, const char* sceneInfo, void* callback);

// 功能: 擦除无线升级方案APK自启动参数
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int EraseWLUpdatePara(const char* addr, void* callback);

// 功能: 写入允许APK安装标志位
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteAllowApkInstall(const char* addr, void* dog, int keyID, bool isQualPlat, void* callback);

// 功能: 写入MMI标志位
// 参数: const char* val, 要写入的MMI标志位信息
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteMMIFlag(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);

// 功能: 写FacSign数据通用接口
// 参数: const char* val 任务令中提供的写入内容；注意电子入网证场景，必须是E_NETWORK+扰码再转换成16进制字符串格式，举例：2384981384A1P1C238C48，转换成323338343938313338344131503143323338433438写入
// 参数: const char* signType 数据签名类型，目前有2种参数：2048加密狗类型：RSA2048_SHA256_PSS，3072加密狗类型：RSA3072_SHA256_PSS
// 参数: const char* signTag 数据Tag标志，具体入参如下：
// ------写UDID：UDID；整机条码：SN；单板条码：BSN；蓝牙地址：MACBT；WIFI地址：MACWLAN；签名授权：AUTHEN(true)；电子入网证：NAL
// ------可替代如下函数接口：WriteUDID-UDID  WriteSN-SN WriteBarcode-BSN WriteBTMAC-MACBT  WriteWifiMAC-MACWLAN WriteAUTHEN-AUTHEN(true)  WriteRunMode-RUNMODE
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int WriteSignDataFunc(const char* addr, void* dog, int keyID, const char* val, const char* signType, const char* signTag, bool isQualPlat, void* callback);

// 功能: 回读FacSign数据通用接口
// 参数: const char* val 任务令中提供的校验内容
// 参数: const char* signType 数据签名类型
// 参数: const char* signTag 数据Tag标志
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
WRITECIPHERTEXTCUSTOMIZATION_API int CheckSignDataFunc(const char* addr, void* dog, int keyID, const char* val, const char* signType, const char* signTag, bool isQualPlat, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif