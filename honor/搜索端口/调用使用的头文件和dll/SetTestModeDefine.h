#pragma once
#ifndef SETTESTMODEDEFINE_H
#define SETTESTMODEDEFINE_H

// 虚拟串口的类型
enum PortType
{
    COMM_TYPE_PCUI = 0,
	COMM_TYPE_DIAG = 1,
	COMM_TYPE_COM = 2,
	COMM_TYPE_FASTBOOT = 3,
	COMM_TYPE_DLOAD = 4,
	COMM_TYPE_SIMPLEIO = 5,
    COMM_TYPE_DIAGNOSTIC = 6,
    COMM_TYPE_DFU = 7
};
// 搜索虚拟串口的策略
enum SEARCH_STRATEGY
{
    FIND_PCUI_ONLY	= 0,
	FIND_DIAG_ONLY	= 1,
	FIND_COM_ONLY	= 2,
	FIND_FASTBOOT_ONLY = 3,
	FIND_DLOAD_ONLY = 4,
	FIND_SIMPLEIO_ONLY = 5,
    FIND_DIAGNOSTIC_ONLY = 6,
    FIND_DFU_ONLY = 7
};
#endif