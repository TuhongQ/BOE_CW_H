#pragma once

#include <string>
#include <iostream>
#include <memory>
using namespace std;

// ʹ�ú궨�����ö������ DataTypeID
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
/// ���ù���ָ�� �������ݻص���������е��ڴ����
typedef std::shared_ptr<void> BOEDataType;
struct BOEData {
    BOEDataTypeID boeDataTypeID;
    BOEDataType boeData;
};
typedef BOEData ParamData;
typedef BOEData RetData;
typedef BOEData ErrData;
typedef BOEData CallbackData;

//�ص�������ʽ
class CallbackInterface
{
public:
	CallbackInterface(){}
	virtual ~CallbackInterface(){}
    virtual void BOE_CallbackFunctin(CallbackData callbackData) = 0;
};

/// <summary>
///  ��ʽ����Dll�����ӿ�
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
