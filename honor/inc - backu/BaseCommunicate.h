/* 
 * Copyright © Honor Device Co., Ltd. 2020-2021. All rights reserved.
 * Description: 通信的基础模块，支持AT/DIAG指令，网口/串口直接发送数据，发送HDLC封包数据
 * Author: y00011914
 * Create: 2021-01-01
 */
#ifndef BASECOMMUNICATE_LIBRARY_H
#define BASECOMMUNICATE_LIBRARY_H

#ifndef BASECOMMUNICATE_EXPORT
#define BASECOMMUNICATE_API __declspec(dllimport)
#else
#define BASECOMMUNICATE_API __declspec(dllexport)
#endif

#ifdef __cplusplus 
extern "C" { 
#endif // _cplusplus

// 功能: 发送一条AT指令。无记忆接口，每次调用，内部都是先打开端口，再发送指令，获取响应包，随后关闭端口退出，建议用来发送AT指令
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* req 请求指令，比如AT^BSN?。数据大小限制：转换之后不能超过 const int MAX_TRANS_DATA_LEN = 8192
// 参数: const char* expect 期望的返回值，支持正则表达式(可以通过圆括号把期望的数据存储到rsp中)。如果输入为nullptr，则把所有直接接收到的返回值，直接返回
// 参数: char* rsp 存放响应包的缓冲区，如果为nullptr，则不反回任何信息。int size 指示缓冲区 rsp 的大小
// 参数: void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
BASECOMMUNICATE_API int   RequestString(const char* addr, const char* req, const char* expect, char* rsp, int size, void* callback);

// 功能: 发送一条缓冲区数据。无记忆接口，每次调用，内部都是先打开端口，再发送指令，获取响应包，随后关闭端口退出，建议用来发送16进制指令或者数据
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 参数: const char* req 请求数据，可以是字符串，也可以是二进制码流，本接口内部不会关心，直接把缓冲区数据下发，下发长度由int reql指定。数据大小限制：转换之后不能超过 const int MAX_TRANS_DATA_LEN = 8192
// 参数: const char* expect 期望的返回值前n BYTE长度的数据，长度由expl指定
// 参数: char* rsp 存放响应包的缓冲区，如果为nullptr，则不反回任何信息。int size 指示缓冲区 rsp 的大小。int& rspl指示实际相应包的数据大小
// 参数: void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
BASECOMMUNICATE_API int   RequestBuffer(const char* addr, const char* req, int reql, const char* expect, int expl, char* rsp, int size, int& rspl, void* callback);

// 功能: 打开一个串口或者网口设备，成功返回句柄（文件描述符）。进程内该句柄（文件描述符都有效）。OpenDevice接口返回通信对象指针，使用此指针可以发送指令，CloseDevice接口销毁通信对象
// 参数: const char* addr 的定义：网口时，ip:port[:protocol]，举例：127.0.0.1:8080
//       Win  平台下串口const char* addr 定义: port number[:baud rate][:protocol], 可选支持波特率设置，默认 57600，举例1：24，举例2：23:9600
//       Linux平台下串口const char* addr 定义：device path，举例：/dev/ttyS0
//       可选[:protocol]，用于指定预定义的特殊的组包方式(目前支持 hdlc、usbbox、hdlc_usbbox 协议)。比如192.168.1.105:1000:usbbox，或者36:9600:usbbox
// 返回: 失败返回nullptr，成功返回句柄（文件描述符）
BASECOMMUNICATE_API void* OpenDevice(const char* addr, void* callback);

// 功能: 直接给网口/串口发送一段数据，不管响应值。reql指示请求包的长度，如果需要获取响应包，使用 ReadData 获取
// 参数: const char* req 请求数据，可以是字符串，也可以是二进制码流，本接口内部不会关心，直接把缓冲区数据下发，下发长度由int reql指定
// 参数: void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
BASECOMMUNICATE_API int   SendData(void* fd, const char* req, int reql, void* callback);

// 功能: 直接从网口/串口读取一段数据，配合 SendData 使用
// 参数: char* rsp 存放响应包的缓冲区，如果为nullptr，则不反回任何信息。int size 指示缓冲区 rsp 的大小。int& rspl指示实际相应包的数据大小
// 参数: void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
// 返回: 失败返回-1，成功返回0
BASECOMMUNICATE_API int   ReadData(void* fd, char* rsp, int size, int& rspl, void* callback);

// 功能: 关闭一个CloseDevice打开的句柄（文件描述符）
// 参数: void* callback LOG打印的回调函数集对象的指针，接口内部不用关心数据结构
BASECOMMUNICATE_API void  CloseDevice(void* fd, void* callback);

#ifdef __cplusplus 
} 
#endif // _cplusplus

#endif // BASECOMMUNICATE_LIBRARY_H


