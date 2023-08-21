#pragma once

#include <string>
#include <iostream>
#include <memory>
using namespace std;

// 使用宏定义代替枚举类型 DataTypeID
// // DataTypeID Error
#define T_NoError           0
#define T_Error             1
// DataTypeID ret
#define T_RetErrorData      101
#define T_RetFailData       102
#define T_RetSuccessData    103
// DataTypeID tip
#define T_LogData           11
#define T_WarningData       12
#define T_ErrorData         13
#define T_MessgeBoxData     14
#define T_SN                15

// DataTypeID Mes
#define T_MesConnectJson    1001

#define T_CommonID          999999
typedef int BOEDataTypeID;
/// 采用共享指针 方便数据回调传输过程中的内存管理
typedef std::shared_ptr<void> BOEDataType;
struct BOEData {
    BOEDataTypeID boeDataTypeID;
    BOEDataType boeData;
};
typedef BOEData ParamData;
typedef BOEData RetData;
typedef BOEData ErrData;
typedef BOEData CallbackData;

//回调函数格式
class CallbackInterface
{
public:
	CallbackInterface(){}
	virtual ~CallbackInterface(){}
    virtual void BOE_CallbackFunctin(CallbackData callbackData) = 0;
};

/// <summary>
///  程式测试Dll开发接口
/// </summary>
class TestDllInterface
{
public:
	TestDllInterface(){}
	virtual ~TestDllInterface(){}
	virtual bool BOE_CALL(char* RequestMathed, ParamData paraData, RetData &retData, ErrData &errData) = 0;
protected:
    shared_ptr<CallbackInterface> callBackObj = nullptr;
};
