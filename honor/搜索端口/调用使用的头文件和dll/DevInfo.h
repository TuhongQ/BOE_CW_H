
#ifndef BASEDEVICEINFODEFINE_H
#define BASEDEVICEINFODEFINE_H

const char PORT_PCUI[] = ("Android Adapter PCUI");
const char PORT_DIAG[] = ("DBAdapter Reserved Interface");
const char PORT_ADB[]  = ("Android Composite ADB Interface");

const char PORT_QUALLOAD[] = ("Qualcomm HS-USB QDLoader 9008");  // 高通强制加载口
const char PORT_HISILOAD[] = ("HUAWEI USB COM 1.0");             // 海思强制加载口
const char PORT_METKLOAD[] = ("MediaTek USB Port");                     // MTK 强制加载端口名称
const char PORT_METKBROM[] = ("MediaTek PreLoader USB VCOM (Android)"); // MTK BROM端口名称

const char DESCRIPTION_FASTBOOT[]  = ("Android Sooner Single ADB Interface"); // FASTBOOT模式下的设备描述
const char DESCRIPTION_COMPOSITE[] = ("USB Composite Device");    // 正常模式下的设备描述

const int DEVINFO_SIZE = 1024;
const int MAX_DEVICE_CONNECTED = 256;

struct DevInfo {
    char devicePath[DEVINFO_SIZE] = {0};        // 本设备的设备路径
    char locationPath[DEVINFO_SIZE] = {0};      // 本设备的物理路径
    char driverKeyName[DEVINFO_SIZE] = {0};     // 本设备的驱动程序关键字
    char description[DEVINFO_SIZE] = {0};       // 本设备的设备描述符
    char deviceID[DEVINFO_SIZE] = {0};          // 本设备的制造商、SN拼接而成
    int  hubIndex = 0;              // 本设备连接的HUB的编号
    int  hubPort = 0;               // 本设备的USB连接点在父HUB中的序号(本设备是连接在父HUB的第几个PORT上)
    int  PCUI = 0;                  // 本设备的USB连接点接入的组合设备的子设备的虚拟PCUI串口号
    int  DBA = 0;                   // 本设备的USB连接点接入的组合设备的子设备的虚拟DIAG串口号
    int  HISILoad = 0;      // 本设备的强制加载端口号
    int  QUALLoad = 0;
    int  METKLoad = 0;      // MTK平台产品，强制加载端口
};

#endif // BASEDEVICEINFODEFINE_H
