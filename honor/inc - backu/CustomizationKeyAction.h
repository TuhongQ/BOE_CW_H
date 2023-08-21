/*
* Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
* Description: 定制工位关键动作模块，包含擦除荣耀账号、擦除OEMINFO分区信息、工厂版本防回退标志位、NV备份、SD卡升级、ROOT拦截、卡托在位检测、恢复出厂设置、等待恢复出厂设置成功、重置翻新机、MC后重启DUT
* Author: y00011914
* Create: 2021-01-01
*/
#ifndef CUSTOMIZATIONKEYACTION_H
#define CUSTOMIZATIONKEYACTION_H

#include <string>

#ifndef CUSTOMIZATIONKEYACTION_EXPORT
#define CUSTOMIZATIONKEYACTION_API __declspec(dllimport)
#else
#define CUSTOMIZATIONKEYACTION_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus


// 功能: 擦除荣耀账号，CW/降级工位调用
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  EraseAccount(const char* addr, void* dog, int keyID, void* callback);

// 功能: 擦除OEMINFO分区信息，一般包含VENDOR/COUNTRY/PRODUCT_NAME，CW/降级工位调用
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  EraseCustInfo(const char* addr, void* dog, int keyID, void* callback);

// 功能: 擦除OEMINFO PhyNum信息，包含OEMINFO_IMEI2、OEMINFO_IMEI、OEMINFO_MEID、OEMINFO_ESN，CW/降级工位调用
// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  EraseOEMPhyNum(const char* addr, void* dog, int keyID, void* callback);

// 功能: 设置工厂版本防回退标志位，CW工位调用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  SetFactoryVer(const char* addr, void* callback);

// 功能: 检查工厂版本防回退标志位，MC工位调用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckFactoryVer(const char* addr, void* callback);

// 功能: 设置MMI2自启动标志位，在MMI2 APK启动后DUT会自己清除，CW工位调用(内部写完之后会检查是否写成功)。调用后 MMI2 APK会自动启动，免去人工点击的动作，节省时间
// 参数: const char hun[8] AP鉴权接口返回的HUN数据，这里是长度为8的数组，不是字符串
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  SetMMI2AutoRunFlag(const char* addr, void* dog, int keyID, const char hun[8], bool isQualPlat, void* callback);

// 功能: 检查MMI2自启动标志位是否已经清除，MC工位调用。确保出厂设备MMI2自动标志位已经失效，确保不出现用户拿到设备开机后进入MMI2测试APK的问题
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckMMI2AutoRunFlagClear(const char* addr, void* callback);

// 功能: NV 备份功能，CW工位使用。M/H/Q需要，展锐平台不需要
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  NVBackup(const char* addr, void* callback);

// 功能: SD卡触发小包升级功能，CW工位最后使用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  SDUpdate(const char* addr, void* callback);

// 功能: SD卡触发大包升级功能，CW工位最后使用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  SDUpdateMainVer(const char* addr, void* callback);

// 功能: ROOT 检查
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckRoot(const char* addr, void* callback);

// 功能: 擦除开机时间，MC工位使用，发送 AT^DAPTIME=erase
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  ErasePowerOnTime(const char* addr, void* callback);

// 功能: 工厂级恢复出厂设置，MC工位使用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  FactoryReset(const char* addr, void* callback);

// 功能: 用户级恢复出厂设置，CW工位使用，恢厂后手机开机
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  FactoryResetCW(const char* addr, void* callback);

// 功能: 用户级恢复出厂设置，MC工位 演示样机使用，恢厂后手机开机
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  FactoryResetForDemo(const char* addr, void* callback);

// 功能: 超时检测工厂级恢复出厂设置是否成功，MC工位使用
// 参数：int timeOut 单位s
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckFactoryResetFinished(const char* addr, int timeOut, void* callback);

// 功能: 重置翻新机方案，MC工位使用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  EnableRetread(const char* addr, void* callback);

// 功能: 重启 DUT，MC工位最后使用。发送指令AT^TMODE=3，发完后MC测试结束。 DUT会重启开机在进入导航界面前自动关机，目的是在工厂执行首次开机，避免用户首次开机慢导致体验不好
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  RestartDevice(const char* addr, void* callback);

// 功能: MTK平台，MC工位校验卡托在位，防止漏插卡托的手机流出去
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  MtkCheckSimTray(const char* addr, void* callback);

// 功能: Unisoc平台，MC工位校验卡托在位，防止漏插卡托的手机流出去
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  UnisocCheckSimTray(const char* addr, void* callback);

// 功能: Q平台特有逻辑，设置手机为NRW模式(非返工模式，即正常模式)
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualSetNRWFlag(const char* addr, void* callback);

// 功能: Q平台特有逻辑，获取手机模式(0 返工模式，1 正常模式)
// 参数  NRWFlag 为出参
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualGetNRWFlag(const char* addr, int& NRWFlag, void* callback);

// 功能: Q平台特有逻辑，检查手机是否为返工模式
// 返回: -1 表示检查失败  0 表示成功，返工模式
CUSTOMIZATIONKEYACTION_API int  QualCheckRWFlag(const char* addr, void* callback);

// 功能: Q平台特有逻辑，擦除NRW模式标志位(即设置手机为返工模式)
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualEraseNRWFlag(const char* addr, void* callback);

// 功能: Q平台特有逻辑，设置手机为offline模式并回读校验设置是否ok，返工流程中使用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualSetDutOffline(const char* addr, void* callback);

// 功能: Q平台特有逻辑，判断手机是否为online模式，如果是，则设置手机为offline模式并回读校验设置是否ok，正常流程使用
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualCheckOnlineAndSetOffline(const char* addr, void* callback);

// 功能: Q平台特有逻辑，NV同步
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualNVEMMCSync(const char* addr, void* callback);

// 功能: 删除软件log
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  DeleteSoftwareLog(const char* addr, void* callback);

// 功能: 读取SD卡 获取SD卡在位或者不在位的状态
//参数  SDcardState 为出参， 表示SD卡状态：0不在位   1在位
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadSDCardState(const char* addr, int& sdCardState, void* callback);

// 功能: 功能检查 读取 UT指令的标志位进行检查
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckUTFlag(const char* addr, void* callback);

// 功能: 功能检查 读取 PT指令的标志位进行检查
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckPTFlag(const char* addr, void* callback);

//功能：大小包升级前 开机优化方案， 1设置dexopt标志位，一次有效；2、判断标志位写入是否成功；
//参数 optimizeMode 为入参，内容目前只有 dexopt
//参数 optimizeValue 为入参，内容目前只有 once
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  WriteOptimizeFlag(const char* addr, const char* optimizeMode, const char* optimizeValue, void* callback);

//功能：BoardID校验（升级之前校验，升级之后不校验）
//     从手机读取BoardID值，存入strBoardId中
//参数  strBoardId 为出参， size 为其大小
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadBoardId(const char* addr, char* strBoardId, int size, void* callback);

//功能：判断DG和服务备板标志位 
//      从手机读取DG标志位，如果标志位是TS769|P或者读取出来没有TS769标志装备校验通过
//      从手机读取备板标志位，如果存在TS463|P则为备板；如果返回值第5个字节不为0，也不报错，认为为非备板
//参数  boardFlag 为出参， size 为其大小
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadSubBoardFlag(const char* addr, char*boardFlag, int size, void* callback);

//功能：MMI组合标志位校验（自动化 or 手动，升级之前校验，升级之后不校验）
//      读取MMI标志位与预期标志位比较，是否一致
//参数  MMIFlagList 为出参， size 为其大小
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadMMIFlag(const char* addr, char* MMIFlagList, int size, void* callback);

//功能：读取电池电量
//参数  value 为出参，表示读取到的电量值     
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadBatteryPower(const char* addr,int& value, void* callback);

//功能：读取非法维修的关键器件列表
//参数  testItem 为出参， size 为其大小
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadMaintenance(const char* addr, char* testItem, int size, void* callback);

//功能：新的校验软件版本号方案，版本号校验要求所有从手机中读取的版本号都要校验；
//参数  stationFlag 为入参，以字符串形式传入，取值为MC、CW，
//参数  softVerInfo 为出参， Size 为其大小
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  ReadSoftwareVer(const char* addr, const char* stationFlag, char* softVerInfo, int size, void* callback);

//功能：写入CW MC标志位
//参数  CWflag 为入参，参数可取值：CW F,  CW P,  LT P,  LT F
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  SetCWFlag(const char* addr, const char* CWflag, void* callback);

//功能：检查CW MC 标志位是否设置成功
//参数  CWflag 为入参，参数可取值：CW F,  CW P,  LT P,  LT F
//返回：-1 表示失败， 0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckCWFlag(const char* addr, const char* CWflag, void* callback);

//功能：卡托在位检查,1表示在位 0表示不在位
//返回：-1 表示失败卡托不在位， 0 表示成功卡托在位
CUSTOMIZATIONKEYACTION_API int  CheckSimSlot(const char* addr, void* callback);

// 功能: Q平台特有逻辑，清除手机中运行态使用的NV数据（保存在modemst1 和modemst2分区中，指令发送完重启生效）
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualEraseModem(const char* addr, void* callback);

// 功能: Q平台特有逻辑，AP侧触发modem子系统重启（支持5.0 R上qcom产品）
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualRebootModem(const char* addr, void* callback);

// 功能: Q平台特有逻辑，清除CP侧IMEI1, IMEI2, MEID, ESN等物理号信息。
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualEraseCPPhyNum(const char* addr, void* callback);

// 功能: Q/M平台通用，判断手机在timeout时间内是否完全启动
// 参数: int timeout 入参，判断手机完全启动的超时时间
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CheckBootState(const char* addr, int timeout, void* callback);

// 功能: Q平台特有逻辑，写入并回读校验NV是否正确，目前支持NV453和NV60009
// 参数: uint16_t nvid为入参，要写入的NV id 
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualWriteNVItem(const char* addr, uint16_t nvid, void* callback);

// 功能: Q平台特有逻辑，校验NV453是否为0
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualCheckNV453(const char* addr, void* callback);

// 功能: Q平台特有逻辑，golden copy，包含NV同步功能，将NV信息同步到EMMC分区以及EFS分区
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualGoldenCopy(const char* addr, void* callback);

// 功能: Q平台特有逻辑，用于删除adb抓log脚本。脚本路径：/log/GetAdblog.bat
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  QualDelLogbat(const char* addr, void* callback);

// 功能: 读取当前手机模式，判断当前手机模式是否为正常模式
// 返回: -1 表示recovery模式，0 表示正常模式
CUSTOMIZATIONKEYACTION_API int CheckMode(const char* addr, void* callback);

// 功能: 关闭自动充电
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int StopAutoCharge(const char* addr, void* callback);

// 功能: 开启自动充电
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int StartAutoCharge(const char* addr, void* callback);

// 功能: 检查当前sim卡，是否不在位
// 返回: -1 表示失败，0 表示成功
CUSTOMIZATIONKEYACTION_API int  CkeckSimCard(const char* addr, void* callback);
#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif