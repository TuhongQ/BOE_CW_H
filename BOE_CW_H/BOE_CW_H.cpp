// BOE_CW_H.cpp : 定义 DLL 的导出函数。
//
#include "pch.h"
#include "framework.h"
#include "BOE_CW_H.h"
#include "ajson.hpp"
#include "json.hpp"
#include "BaseShowInformation.h"
#include "../BOE_MES/BOE_MES.h"
#include <thread>
#include "INIParser.h"

#include <regex>
#include "Tool.h"
#include <unordered_map>
#include <time.h>　　//秒
#include <sys/timeb.h> //毫秒
#include "rapidxml_utils.hpp"

#ifdef _DEBUG
//#pragma comment(lib,"OpenXLSXd.lib")
//#pragma comment(lib,"GetSNLib/Debug/GetSNLib.lib")
#else
//#pragma comment(lib,"OpenXLSX.lib")
#endif // _DEBUG

#pragma comment(lib,"libBaseSafedog.dll.a")

std::vector<std::string> split(std::string& line, const std::string& delim)
{
	size_t pstart = 0;
	size_t phit = 0;
	std::string sstr;
	size_t length = line.length();
	std::vector<std::string> vstr;
	vstr.clear();
	for (; pstart <= length;)
	{
		phit = line.find(delim, pstart);
		if (std::string::npos != phit)
		{
			/* find delim, get substr */
			sstr = line.substr(pstart, phit - pstart);
			vstr.push_back(sstr);
			pstart = phit + delim.size();
		}
		else {
			/* not find delim, append remaining str and break */
			vstr.push_back(line.substr(pstart));
			break;
		}
	}
	return vstr;
}

template <class T>
std::string join(T& val, std::string delim)
{
	std::string str;
	typename T::iterator it;
	const typename T::iterator itlast = val.end() - 1;
	for (it = val.begin(); it != val.end(); it++)
	{
		str += *it;
		if (it != itlast)
		{
			str += delim;
		}
	}
	return str;
}
int toUnicode(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
	//constexpr std::hash<std::string> hash_fn;
	//return hash_fn(str);
	//return str[0] + (str[1] ? toUnicode(str + 1) : 0);
}
void replace_str(char* text, char sp_ch, char re_ch) {
	int len = strlen(text);
	char* copy = (char*)malloc(len + 1);
	for (size_t i = 0; i < len; i++)
	{
		char ch = text[i];
		if (ch == sp_ch)
		{
			copy[i] = re_ch;
		}
		else {
			copy[i] = ch;
		}
	}
	copy[len] = 0;
	//text = copy;//等号赋值是值传递，strcpy是引用传递
	strcpy(text, copy);
	free(copy);
}
constexpr inline int U(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
	//constexpr std::hash<std::string> hash_fn;
	//return hash_fn(str);
	//return str[0] + (str[1] ? U(str + 1) : 0);
}

inline void HelpSetData(ParamData& paraData, int typeID, string value)
{
	paraData.boeDataTypeID = typeID;
	if (paraData.boeData == nullptr || value.length() >= 1024)
	{
		paraData.boeData = std::shared_ptr<char>(new char[value.length() + 1] {0}, std::default_delete<char[]>());
	}
	strcpy((char*)paraData.boeData.get(), value.c_str());
	((char*)(paraData.boeData.get()))[value.length()] = '\0';
}



void ShowInfo(void* param, const char* info)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default("ShowInfo:" + string(info));
		}
	}
}
void H_SaveFunctionRecord(void* param, const char* info)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default(info);
		}
	}
}
void H_ShowNormalInformation(void* param, const char* info)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default(info);
		}
	}
}
void H_showFailInformation(void* param, const char* info)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default(info);
			if (boe->ErrorMsg.size() != 0)
			{
				boe->ErrorMsg += "\r\n";
			}
			auto info_replace = std::regex_replace(info, regex("(AT\\^.*)"), "AT^***");
			boe->ErrorMsg += info_replace;
		}
	}
}
void H_ShowDebugInformation(void* param, const char* info)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default(info);
		}
	}
}
void H_UploadStringValue(void* param, const char* info, const char* value)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << "\t" << value << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default(info);
		}
	}
}
void H_UploadDoubleValue(void* param, const char* info, double value, double upLimit, double lowLimit)
{
	cout << __FUNCTION__ << ":" << param << " :" << info << "\t" << value << "\t" << upLimit << "\t" << lowLimit << endl;
	if (param)
	{
		auto boe = static_cast<BOE_CW*>(param);
		if (boe)
		{
			boe->BOE_CB_OUTLog_Default(info);
		}
	}
}
int H_StopWhenNeed(void* param)
{
	cout << __FUNCTION__ << ":" << param << endl;
	return 0;
}

AJSON(BOE_CW, TestMathed, Code);
//AJSON(BOE_CW, authenticationParam, authenticationModeParam, testExampleParam, checkSDCardParam, checkManufacturerFlagParam)
AJSON(ParamInterface, TestMathed);
// 这是导出变量的一个示例
BOECWH_API int nBOECWH = 0;

// 这是导出函数的一个示例。
BOECWH_API int fnBOECWH(void)
{
	return 0;
}

// 这是已导出类的构造函数。
CBOECWH::CBOECWH()
{
	return;
}

string ParamInterface::getJson() {
	ajson::string_stream ss;
	ajson::save_to(ss, *this);
	return ss.str();
}

bool ParamInterface::setJson(string value) {
	if (value.empty()) return true;
	ajson::load_from_buff(*this, value.c_str());
	return true;
}


bool BOE_CW::BOE_CALL(char* RequestMathed, ParamData paraData, RetData& retData, ErrData& errData)
{
	std::cout << __FUNCTION__ << "*************************" << RequestMathed << " " << this->TestMathed << endl;
#pragma region
	/// 设置常规参数 key1:value1;key2:value2 这样的字符串形式传入 
	if (!strcmp(RequestMathed, "SetCommonParam")) /// 每次启动测试的时候传入一次（单次启动每次都执行 循环执行时首次启动执行）
	{
		CommonParam.clear();
		// ParallelID
		string value = (char*)paraData.boeData.get();
		std::cout << "____________" << RequestMathed << endl;
		std::cout << value << endl;
		if (value.size() == 0) return true;
		//BOE_CB_MessageBoxData(value);
		bool ret = false;
		auto splitData = split(value, "\r\n");
		BOE_CB_OUTLog_Default("\r\n" + value);
		for (auto itemData : splitData) {

			auto splitItemData = split(itemData, "\r");
			if (splitItemData.size() == 2)
			{
				CommonParam[splitItemData[0]] = splitItemData[1];
			}
			else
			{
				// 异常
			}
		}
		ret = CommonParam.size() > 0;
		if (ret)
		{
			HelpSetData(retData, T_RetSuccessData, RequestMathed + string(" Is Successed!"));
			HelpSetData(errData, T_NoError, RequestMathed + string(" Is Successed!"));
		}
		else
		{
			HelpSetData(retData, T_RetFailData, RequestMathed + string(" Is Failed!"));
			HelpSetData(errData, T_Error, RequestMathed + string(" Is Failed!"));
		}
		return ret;
	}

	if (!strcmp(RequestMathed, "RegisterCallbackFunctin")) /// 该部分内容 每次启动都会执行一次
	{
		callBackObj = static_pointer_cast<CallbackInterface>(paraData.boeData);
		if (callBackObj == nullptr)
		{
			HelpSetData(retData, T_RetFailData, "RegisterCallbackFunctin Is Failed!");
			HelpSetData(errData, T_Error, "RegisterCallbackFunctin Is Failed!");
			return false;
		}
		else
		{
			this->callBackObj = callBackObj;
			HelpSetData(retData, T_RetSuccessData, "RegisterCallbackFunctin Is Successed!");
			HelpSetData(errData, T_NoError, "RegisterCallbackFunctin Is Successed!");
		}
		return true;
	}

	if (!strcmp(RequestMathed, "UnregisterCallbackFunctin")) // 移除注册的回调函数
	{
		this->callBackObj = nullptr;
		HelpSetData(retData, T_RetSuccessData, "UnregisterCallbackFunctin Is Successed!");
		HelpSetData(errData, T_NoError, "UnregisterCallbackFunctin Is Successed!");
		return true;
	}

	if (!strcmp(RequestMathed, "GetConfigJson"))
	{
		string retValue = "";

		//if (paraData.boeData != nullptr)
		//{
		//	string value = (char*)paraData.boeData.get();
		//	if (Mathed2PramaObj.count(value))
		//	{
		//		retValue = Mathed2PramaObj[value]->getJson();					
		//	}
		//}
		if (retValue == "") retValue = getConfigJson();

		HelpSetData(retData, T_RetSuccessData, retValue);
		HelpSetData(errData, T_NoError, "GetConfigJson Is Successed!");
		return true;
	}

	if (!strcmp(RequestMathed, "SetConfigJson"))
	{
		string value = (char*)paraData.boeData.get();

		auto ret = this->setConfigJson(value);
		if (ret)
		{
			HelpSetData(retData, T_RetSuccessData, "SetConfigJson Is Successed!");
			HelpSetData(errData, T_NoError, "SetConfigJson Is Successed!");
		}
		else
		{
			HelpSetData(retData, T_RetFailData, "SetConfigJson Is Failed!");
			HelpSetData(errData, T_Error, "SetConfigJson Is Failed!");
		}
		return ret;
	}
#pragma endregion

	// 一次测试开始
	if (!strcmp(RequestMathed, "BeginOnceTest"))
	{

		/*pHonor_callback = CallbackParamObjManagement::BorrowObj();
		int count  = CallbackParamObjManagement::getObjList().size();*/
		//BOE_CB_MessageBoxData(" CallbackParamObjManagement::getObjList().size():"+std::to_string(count));
		//pHonor_callback = &honor_callback;
		pHonor_callback = CallbackParamObjSet::getCallbackParamObj(CommonParam["ParallelID"]);
		if (pHonor_callback)
		{
			pHonor_callback->showNormalInformation = H_ShowNormalInformation;
			pHonor_callback->showFailInformation = H_showFailInformation;
			pHonor_callback->showDebugInformation = H_ShowDebugInformation;
			pHonor_callback->uploadStringValue = H_UploadStringValue;
			pHonor_callback->uploadDoubleValue = H_UploadDoubleValue;
			pHonor_callback->stopWhenNeed = H_StopWhenNeed;
			pHonor_callback->callbackFunctionReserve1 = nullptr;
			pHonor_callback->callbackFunctionReserve2 = nullptr;
			pHonor_callback->callbackFunctionReserve3 = nullptr;
			pHonor_callback->logPath = nullptr;
			pHonor_callback->paramReserve1 = nullptr;
			pHonor_callback->paramReserve2 = nullptr;
			pHonor_callback->paramReserve3 = nullptr;
			pHonor_callback->record = nullptr;
			pHonor_callback->sn = nullptr;
			pHonor_callback->saveFunctionRecord = nullptr;
			pHonor_callback->param = this;
			if (pHonor_callback->callbackFunctionReserve1 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->callbackFunctionReserve1");
			}
			if (pHonor_callback->callbackFunctionReserve2 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->callbackFunctionReserve2");
			}
			if (pHonor_callback->callbackFunctionReserve3 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->callbackFunctionReserve3");
			}
			if (pHonor_callback->logPath != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->logPath");
			}
			if (pHonor_callback->paramReserve1 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->paramReserve1");
			}
			if (pHonor_callback->paramReserve2 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->paramReserve2");
			}
			if (pHonor_callback->paramReserve3 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->paramReserve3");
			}
			if (pHonor_callback->record != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->record");
			}
			if (pHonor_callback->sn != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->sn");
			}
			if (pHonor_callback->saveFunctionRecord != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->saveFunctionRecord");
			}
		}
		else
		{
			BOE_CB_MessageBoxData("借用对象失败CallbackParamObjManagement::BorrowObj()");
		}
		//cout << "测试。。。。" << RequestMathed << std::endl;
		//BOE_CB_MessageBoxData("一次测试开始！");

		dogInfoPtr = getDogInfoPtr(CommonParam["ParallelID"]);
		return true;
	}

	if (!strcmp(RequestMathed, "BeginTest"))
	{
		ErrorMsg = "";
		//honorLog.hLog_TestItem = TestMathed;
		//honorLog.hLog_LowerLimit = "/";
		//honorLog.hLog_Value = "/";
		//honorLog.hLog_UpperLimit = "/";
		//honorLog.hLog_Result = false;
		//honorLog.hLog_IsOut = true;
		//honorLog.hLog_IsCopy = true;
		//honorLog.hLog_StartTime = getTimeStamp();
		DWORD startTickCount = GetTickCount64();
		bool ret = BeginTest(RequestMathed, paraData, retData, errData);
		DWORD endTickCount = GetTickCount64();
		BOE_CB_OUTLog_Default("Time count:" + std::to_string(endTickCount - startTickCount));
		BOE_CB_ShowInfo("Time count:" + std::to_string(endTickCount - startTickCount));
		//honorLog.hLog_Result = retBool;
		//honorLog.writeCSVLog();
		//honorLog.Copy();
		return ret;
	}

	// 一次测试完成 不记录测试结果是否完成 是否成功 自行判断
	if (!strcmp(RequestMathed, "EndOnceTest"))
	{
		//cout<<"测试。。。。" << RequestMathed << std::endl;
		if (pHonor_callback)
		{
			if (pHonor_callback->callbackFunctionReserve1 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->callbackFunctionReserve1");
			}
			if (pHonor_callback->callbackFunctionReserve2 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->callbackFunctionReserve2");
			}
			if (pHonor_callback->callbackFunctionReserve3 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->callbackFunctionReserve3");
			}
			if (pHonor_callback->logPath != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->logPath");
			}
			if (pHonor_callback->paramReserve1 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->paramReserve1");
			}
			if (pHonor_callback->paramReserve2 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->paramReserve2");
			}
			if (pHonor_callback->paramReserve3 != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->paramReserve3");
			}
			if (pHonor_callback->record != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->record");
			}
			if (pHonor_callback->sn != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->sn");
			}
			if (pHonor_callback->saveFunctionRecord != nullptr)
			{
				BOE_CB_MessageBoxData("pHonor_callback->saveFunctionRecord");
			}
			pHonor_callback->showNormalInformation = nullptr;
			pHonor_callback->showFailInformation = nullptr;
			pHonor_callback->showDebugInformation = nullptr;
			pHonor_callback->uploadStringValue = nullptr;
			pHonor_callback->uploadDoubleValue = nullptr;
			pHonor_callback->stopWhenNeed = nullptr;
			pHonor_callback->param = nullptr;
			//if (!CallbackParamObjManagement::ReturnObj(pHonor_callback))
			//{
			//	BOE_CB_MessageBoxData("归还对象失败CallbackParamObjManagement::ReturnObj(pHonor_callback)");

			//}

		}
		return true;
	}

	return false;
}

bool BOE_CW::BeginTest(char* RequestMathed, ParamData paraData, RetData& retData, ErrData& errData)
{
	pParaData = &paraData;
	pRetData = &retData;
	pErrData = &errData;
	retBool = false;
	// 返回的false是否上传MES
	isRetFalsePostMes = true;
	BOE_CB_OUTLog_Default("--------------------------" + TestMathed + "---------------------------");
	BOE_CB_ShowInfo("--------------------------" + TestMathed + "---------------------------");
#if CW // CW站点	
	switch (toUnicode(TestMathed.c_str()))
	{
	case U("Init"):						//      自定义 进行设备等待 可能是等待端口接通
	{
		Init(paraData, retData, errData);
		isRetFalsePostMes = false; // 工具Init失败不上传MES
		break;
	}
	case U("Authentication"):			//1     鉴权
	{
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^DEVBOOTSTATE?\r", "DEVBOOTSTATE:1\\s*OK", nullptr, 0, pHonor_callback) == 0, "DUT启动状态检查");
		if (!retBool)break;
		Authentication(paraData, retData, errData);
		break;
	}
	case U("CheckMode"):				//2     检查手机模式
	{
		resultSetFP(CheckMode(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, this->TestMathed);
		break;
	}
	case U("DeleteExtLog"):				//3		删除软件log
	{
		resultSetFP(DeleteSoftwareLog(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, this->TestMathed);
		break;
	}
	case U("CheckBoardSn"):				//4		单板条码读取
	{
		CheckBarcode(paraData, retData, errData);
		break;
	}
	case U("CheckSDCard"):				//5     SD卡在位校验(CW工位用SD卡升级才需要校验是否在位)
	{
		if (lastResponseData.SupportSD == "0") // 有NSD 即不带SD卡版本 无需测试SD卡功能
		{
			resultSetEx(true, "Warning:当前DUT不支持SD卡,跳过检查。SupportSD:" + lastResponseData.SupportSD);
			break;
		}
		// 0不在位   1在位
		int sdCardState = 0;
		resultSetFP(ReadSDCardState(CommonParam["DUTCom"].c_str(), sdCardState, pHonor_callback) == 0, "ReadSDCardState ");
		if (!retBool) {
			BOE_CB_ShowInfo("Error: 读取SD卡状态失败，无法读取到SD卡状态。");
		}
		if (!retBool) break;
		resultSetEx(sdCardState, "CheckSDCard Is " + string(sdCardState ? " Pass." : "Fail. It is need SDCard."));
		if (!retBool) {
			BOE_CB_ShowInfo("Error: SD卡不在位，请确认检查SD卡。");
		}
		if (!retBool) break;
		break;
	}
	case U("CheckBoardID"):				//6		ProductName校验
	{
		char buff[128];
		resultSetFP(ReadBoardId(CommonParam["DUTCom"].c_str(), buff, 128, pHonor_callback) == 0, "ReadProductName");
		if (!retBool) break;
		//string BoardID = string(buff);
		//vector<string> s = split(BoardID, "-");
		retBool = false;
		resultSetFP(lastResponseData.ProductName == string(buff), "Compare DUT Read_ProductName[" + string(buff) + "]" + "With MES_ProductName[" + lastResponseData.ProductName + "] ");
		if (!retBool) {
			isRetFalsePostMes = false; // ProductName不一致不上传MES
			BOE_CB_OUTLog_Default("ProductName核验不一致，不上传MES");
			break;
		}
		break;
	}
	case U("NVCheck"):					//7		NVCheck   (QualCheckNVStatus接口  nvsetmask定义不明确)
	{
		resultSetFP(QualCheckNVStatus(CommonParam["DUTCom"].c_str(), 0, pHonor_callback) == 0, "QualCheckNVStatus");
		if (!retBool)break;
		break;
	}
	case U("CheckSubBoardFlag"):		//8		判断服务备板标志位
	{
		CheckSubBoardFlag(paraData, retData, errData);
		break;
	}
	case U("CheckManufacturerFlag"):	//9		检测PT、MT、UT、MMI1组合标志位（自动化MMIT or 手动MMI1)  清除CW后的MMI标志位
	{
		BOE_CB_OUTLog_Default("读取标志位.");
		char rsp[512];
		int ret = RequestString(CommonParam["DUTCom"].c_str(), "AT^FACINFO?\r", nullptr, rsp, 512, pHonor_callback);
		resultSetFP(ret == 0, "Send AT Command ");
		if (!retBool) break;
		string retStr = string(rsp);
		cmatch what;
		if (std::regex_search(rsp, what, regex("\\^FACINFO:0,(.*)")))
		{
			if (what.size() > 1) retStr = what[1];
		}
		resultSetFP(retStr.find("PT P") == 90, "Check PT Flag ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:PT标志位检查失败，请确认PT工序是否完成！");
			isRetFalsePostMes = false; // PT P标志位没有不上传MES
			break;
		}
		// PT MT 服务备版不检查
		resultSetFP(retStr.find("MT P") == 65, "Check MT Flag ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:MT标志位检查失败，请确认MT工序是否完成！");
			isRetFalsePostMes = false; // MT P标志位没有不上传MES
			break;
		}
		// UT 标志位检查
		resultSetFP(retStr.find("UT P") == 110, "Check UT Flag ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:UT标志位检查失败，请确认UT工序是否完成！");
			isRetFalsePostMes = false; // UT P标志位没有不上传MES
			break;
		}

		// MMIT MMIS标志位检查
		if (!dataParam.isDGSlaveServer) // 不是备板时，检查MMIT 和 MMIS，是备板时跳过该检查
		{
			// MMI1
			char buff[512]{ 0 };
			resultSetFP(ReadMMIFlag(CommonParam["DUTCom"].c_str(), buff, 512, pHonor_callback) == 0, "读取MMI标志位 ");
			if (!retBool) break;
			string MMIFlagList = buff;
			BOE_CB_OUTLog_Default("MMIFlagList:" + MMIFlagList);
			int num = HexStrToInt(MMIFlagList);
			BOE_CB_OUTLog_Default("MMIFlagList To DEC:" + std::to_string(num));
			resultSetFP((num & 6) == 6, "Check MMIT and MMIS Flag");
			if (!retBool) {
				BOE_CB_ShowInfo("Error: MMIT 和 MMIS 标志位检查失败，请确认该测试是否完成。");
				isRetFalsePostMes = false; // MMIT 和 MMIS 标志位检查失败不上传MES
			}
			if (!retBool) break;
			if ((num & 72) == 0)
			{
				// 未做过MMI2 或者 MMI2S测试
				resultSetEx(true, "MMI2 or MM2S 标志位为空，无需执行清除操作.");
				break;
			}

			int value = num & 0xFFB7;
			char s[128];
			std::sprintf(s, "%X", value);
			BOE_CB_OUTLog_Default("MMIResult & 0xFFB7:" + value);
			// AT^TMMI=0xXXX)
			BOE_CB_OUTLog_Default("Try to clear MMI2 or MMI2S flag.");
			char rsp[512]{ 0 };
			string command = string("AT^TMMI=") + string(s) + "\r";
			resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), command.c_str(), nullptr, rsp, 512, pHonor_callback) == 0, "发送清除MMI2OrMMI2S标志位指令");
			string retStr = rsp;
			resultSetFP(retStr.find("OK") != string::npos, "清除MMI2OrMMI2S标志位");
		}
		else
		{
			BOE_CB_ShowInfo("Warning: 读取MMI备板跳过MMIT/MMIS检查。");
			BOE_CB_OUTLog_Default("读取MMI备板跳过MMIT/MMIS检查。");
		}
		break;
	}
	case U("SetFactoryVer"):			//10	设置工厂版本防回退标志位（升级之后写入，升级之前不写）
	{
		resultSetFP(SetFactoryVer(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "设置工厂版本防回退标志位");
		if (!retBool)  break;

		resultSetFP(CheckFactoryVer(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "检查工厂版本防回退标志位");
		if (!retBool)  break;
		break;
	}
	case U("CheckDGFlag"):			 	//11	判断DG标志位
	{
		char rsp[512]{ 0 };
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^CONTROLBIT?\r", nullptr, rsp, 512, pHonor_callback) == 0, "读取降级标志位");
		if (!retBool)break;
		resultSetFP(std::regex_search(rsp, std::regex(".*TS769\\|P.*")) || !std::regex_search(rsp, std::regex(".*TS769.*")), "DG Flag Check");
		if (!retBool) {
			BOE_CB_ShowInfo("降级标志位检查未通过，检查是否降级失败。");
			break;
		}
		break;
	}
	case U("EraseAccount"):				//12	擦除荣耀账号
	{
		resultSetFP(EraseAccount(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], pHonor_callback) == 0, "EraseAccount");
		if (!retBool) {
			BOE_CB_ShowInfo("Error:擦除荣耀账号失败。");
		}
		break;
	}
	case U("CheckBatteryLevel"):		//13	电池电量检查
	{
		CheckBatteryLevel(paraData, retData, errData);
		break;
	}
	case U("CheckMaintenance"):			//14	检查是否非法维修
	{
		CheckMaintenance(paraData, retData, errData);
		break;
	}
	case U("WriteOptimizeFlag"):		//15	大包升级前 开机优化方案（大包升级之前和小包升级之前配置）
	{
		resultSet(WriteOptimizeFlag(CommonParam["DUTCom"].c_str(), "dexopt", "once", pHonor_callback) == 0);
		break;
	}
	case U("EraseCustInfo"):			//17	擦除OEMINFO中的片区信息（vendor/country/product_name）
	{
		BOE_CB_OUTLog_Default("Try To EraseCustInfo.");
		resultSetFP(EraseCustInfo(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], pHonor_callback) == 0, "EraseCustInfo");
		if (!retBool) {
			BOE_CB_ShowInfo("Error:擦除OEMINFO分区信息失败。");
		}
		break;
	}
	case U("EraseModem"):				//18-19 判断当前手机是不是返工模式
	{
		EraseModem(paraData, retData, errData);
		break;
	}
	case U("SetDUTOffline"):			//20    检查手机online模式，设置offline模式
	{
		// 功能: Q平台特有逻辑，判断手机是否为online模式，如果是，则设置手机为offline模式并回读校验设置是否ok，正常流程使用
		// 返回: -1 表示失败，0 表示成功
		resultSet(QualCheckOnlineAndSetOffline(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0);
		break;
	}
	case U("CheckSoftwareVersion"):		//21	版本号校验、写CW F标志位	
	{
		CheckSoftwareVersion(paraData, retData, errData);
		if (!retBool) break;
		// 写入CW F标志位
		WriteCWFFlag(paraData, retData, errData);
		if (!retBool) break;
		break;
	}
	case U("ErasePhyNo"):				//22    清除物理号信息
	{
		// 功能: Q平台特有逻辑，清除CP侧IMEI1, IMEI2, MEID, ESN等物理号信息。
		// 返回: -1 表示失败，0 表示成功
		resultSet(QualEraseCPPhyNum(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0);
		break;
	}
	case U("CheckHardwareSize"):		//23	校验锁卡表HARDWARESIZE字段
	{
		CheckHardwareSize(paraData, retData, errData);
		break;
	}
	case U("WriteSimcardMode"): // M4新增1 写双卡模式，并校验
	{
		if (lastResponseData.IS5G == "")
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 当前非5G产品，跳过当前测试。");
			break;
		}
		if (StationData.customInfos.find("SIMCARD_MODE") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SIMCARD_MODE]配置，跳过当前测试。");
			break;
		}
		string SIMCARD_MODE = StationData.customInfos["SIMCARD_MODE"].Value;
		BOE_CB_OUTLog_Default("Try To Write SIMCARD_MODE(" + SIMCARD_MODE);
		resultSetFP(WriteSimcardMode(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], SIMCARD_MODE.c_str(), IsQualPlat, pHonor_callback) == 0, "写入SIMCARD_MODE");
		if (!retBool) break;
		resultSetFP(VerifySimcardMode(CommonParam["DUTCom"].c_str(), SIMCARD_MODE.c_str(), pHonor_callback) == 0, "校验VerifySimcardMode");
		if (!retBool) break;
		break;

	}
	case U("UnSimlock")://M4新增 解锁Simlock 必测项？验证需要提供SIMLOCK表格,不确定测试
	{
		if (lastResponseData.IS5G == "")
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 当前非5G产品，跳过当前测试。");
			break;
		}
		resultSetFP(QualUnlockSimlock(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "解锁Simlock");
		if (!retBool) break;
		break;
	}

	case U("WritePhyno"): //M4新增3 写入MEID/IMEI 并校验 :需要确认imei获取方式 Q平台写入的接口
	{
		if (lastResponseData.IS5G == "")
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 当前非5G产品，跳过当前测试。");
			break;
		}
		if (StationData.customInfos.find("MEID_RULE") == StationData.customInfos.end()&& !StationData.customInfos["MEID_RULE"].Value.empty())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[MEID_RULE]配置，跳过当前测试。");
			break;
		}
		if (StationData.customInfos.find("IMEI_RULE") == StationData.customInfos.end() && !StationData.customInfos["IMEI_RULE"].Value.empty())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[IMEI_RULE]配置，跳过当前测试。");
			break;
		}
		BOE_CB_OUTLog_Default("Try To Write MEID:" + lastResponseData.MEID);
		if (lastResponseData.MEID.empty())
		{
			resultSetEx(false, "Error:MES分配的MEID是空值.");
			break;
		}
		BOE_CB_OUTLog_Default("Try To Write IMEI:" + lastResponseData.IMEI);
		if (lastResponseData.IMEI.empty())
		{
			resultSetEx(false, "Error:MES分配的IMEI是空值.");
			break;
		}
		
		PhyNumInfo phyNumInfo;
		phyNumInfo.meid_rule = atoi(StationData.customInfos["MEID_RULE"].Value.c_str());
		phyNumInfo.imei_1_rule = atoi(StationData.customInfos["IMEI_RULE"].Value.c_str());;
		strcpy_s(phyNumInfo.meid, lastResponseData.MEID.c_str());
		strcpy_s(phyNumInfo.imei_1, lastResponseData.IMEI.c_str());

		//strcpy_s(phyNumInfo.meid, "35731118026718");//测试
		//strcpy_s(phyNumInfo.imei_1, "357311180267139");
		resultSetFP(MetkWritePhysicalNumber(CommonParam["DUTCom"].c_str(), &phyNumInfo, pHonor_callback) == 0, "写入WritePhyno");
		if (!retBool) break;
		resultSetFP(QualCheckPhysicalNumber(CommonParam["DUTCom"].c_str(), &phyNumInfo, pHonor_callback) == 0, "校验WritePhyno");
		if (!retBool) break;
		break;
	}
	case U("WriteSimlock")://M4新增5 写入SIMLOCk信息 参数: const char* cfg 配置SIMLOCK信息的表格路径，没有时，可以为nullptr,需要提供SIMLOCK表格
	{
		if (lastResponseData.IS5G == "")
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 当前非5G产品，跳过当前测试。");
			break;
		}
		if (StationData.customInfos.find("SIMLOCK_WRITE") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SIMLOCK_WRITE]配置，跳过当前测试。");
			break;
		}
		string str_SIMLOCK_WRITE = StationData.customInfos["SIMLOCK_WRITE"].Value;
		if (str_SIMLOCK_WRITE.compare("1"))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SIMLOCK_WRITE[" + str_SIMLOCK_WRITE + "].Don't need to write value!");
			break;
		}
		string strPassword;
		string strHash;
		if (StationData.customInfos.find("NCK_NCKNSCKSPCKRESET") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[NCK_NCKNSCKSPCKRESET]配置，Password默认nullptr。");
			strPassword = nullptr;
		}
		else
			strPassword = StationData.customInfos["NCK_NCKNSCKSPCKRESET"].Value;
		if (StationData.customInfos.find("INI_HASH") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[INI_HASH]配置，Hash默认nullptr。");
			strHash = nullptr;
		}
		else
			strHash = StationData.customInfos["INI_HASH"].Value;

		resultSetFP(QualWriteSimlock(CommonParam["DUTCom"].c_str(), strPassword.c_str(), strHash.c_str(), nullptr, pHonor_callback) == 0, "WriteSimlock");
		if (!retBool) break;
		resultSetFP(QualCheckSimlock(CommonParam["DUTCom"].c_str(), 0, nullptr, pHonor_callback) == 0, "CheckSimlock");
		if (!retBool) break;
		break;
	}
	case U("WriteNV453")://M4新增6 清除NV453 : uint16_t nvid为入参，要写入的NV id 目前未知
	{
		if (lastResponseData.IS5G == "")
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 当前非5G产品，跳过当前测试。");
			break;
		}
		resultSetFP(QualWriteNVItem(CommonParam["DUTCom"].c_str(), 453, pHonor_callback) == 0, "清除NV453");
		if (!retBool) break;
		resultSetFP(QualCheckNV453(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "校验NV453");
		if (!retBool) break;
		break;
	}

	case U("WriteCPL")://M4新增10 写入精细化预装定制
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 11))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SPECIAL_DATA_SWITCH[" + SPECIAL_DATA_SWITCH + "].Don't need to write value!");
			break;
		}
		//“预装清单”是mes获取的
		if (StationData.customInfos.find("CPL_ID") == this->StationData.customInfos.end() && StationData.customInfos.find("CPL_CONTENT") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有CPL_ID或CPL_CONTENT配置，跳过当前测试。");
			break;
		}
		if (lastResponseData.CPL_ID.empty())
		{
			resultSetEx(false, "Error:MES分配的CPL_ID是空值.");
			break;
		}
		if (lastResponseData.CPL_CONTENT.empty())
		{
			resultSetEx(false, "Error:MES分配的CPL_CONTENT是空值.");
			break;
		}
		BOE_CB_OUTLog_Default("CPL_ID:" + lastResponseData.CPL_CONTENT);
		resultSet(WriteCPL(CommonParam["DUTCom"].c_str(), lastResponseData.CPL_CONTENT.c_str(), pHonor_callback) == 0);
		break;
	}
	case U("WriteRKP")://M4新增11 写入谷歌证书新方案
	{
		//if (lastResponseData.IS5G=="")
		//{
		//	resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 当前非5G产品，跳过当前测试。");
		//	break;
		//}
		char rkpData[8001]{ 0 };
		char verifyData[8001]{ 0 };
		char Rkp_Data_1[4001]{ 0 };
		char Rkp_Data_2[4001]{ 0 };
		char sp_ch = '\"', re_ch = '\'';
		resultSetFP(GetRkpAndVdData(CommonParam["DUTCom"].c_str(), rkpData, 8000, verifyData, 8000, pHonor_callback) == 0, "GetRkpAndVdData");
		if (!retBool) break;
		replace_str(rkpData, sp_ch, re_ch);
		strcat(rkpData, "EndWithTheFollowing");
		while (strlen(rkpData) < 8000)
		{
			strcat(rkpData, "=");
		}

		strncpy_s(Rkp_Data_1, rkpData, 4000);
		strncpy_s(Rkp_Data_2, rkpData + 4000, 4000);
		string strRkp = string(rkpData);
		BOE_CB_OUTLog_Default("rkpData is：" + strRkp);
		string strverifyData = string(verifyData);
		BOE_CB_OUTLog_Default("strverifyData is：" + strverifyData);
		//上传MES
		this->dataParam.RKP_DATA_1 = Rkp_Data_1;
		this->dataParam.RKP_DATA_2 = Rkp_Data_2;
		this->dataParam.RKP_DATA_VD = verifyData;
		resultSetFP(VerifyRkpData(CommonParam["DUTCom"].c_str(), verifyData, pHonor_callback) == 0, "VerifyRkpData");
		if (!retBool) break;
		break;
	}
	case U("WriteRPMB")://M4新增12 写入RPMB
	{
		if (StationData.customInfos.find("RSN") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有RSN配置，跳过当前测试。");
			break;
		}
		string RSN = StationData.customInfos["RSN"].Value;
		BOE_CB_OUTLog_Default("RSN:" + RSN);
		if (RSN != "1")
		{
			resultSetEx(false, "锁卡表中RSN配置错误，该字段要么不配置配置的话则值为1。");
			break;
		}
		resultSet(WriteRSN(CommonParam["DUTCom"].c_str(), RSN.c_str(), pHonor_callback) == 0);
		break;
	}
	case U("CheckQfuseRegisterData"):	//32	校验锁卡表QFUSE_REGISTER_DATA字段的值，即熔丝标志位
	{
		CheckQfuseRegisterData(paraData, retData, errData);
		break;
	}
	case U("CheckRPMB"):				//33	校验RPMB
	{
		if (StationData.customInfos.find("RSN") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有RSN配置，跳过当前测试。");
			break;
		}
		string RSN = StationData.customInfos["RSN"].Value;
		BOE_CB_OUTLog_Default("RSN:" + RSN);
		if (RSN != "1")
		{
			resultSetEx(false, "锁卡表中RSN配置错误，该字段要么不配置配置的话则值为1。");
			break;
		}
		resultSet(VerifyRSN(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0);
		break;
	}
	case U("WriteMobileSN"):			//34	写入整机SN，并校验  IsQualPlat为true
	{
		// 写入整机SN，并校验
		// 写
		// WriteCiphertextCustomization.h
#pragma region 赋值测试
		//lastResponseData.MSN = "ANSTUN3410G01355";
		//lastResponseData.BTMAC = "386504710CAD";
		//lastResponseData.WIFIMAC = "386504710CAE";
#pragma endregion

		BOE_CB_OUTLog_Default("Try To Write SN:" + lastResponseData.MSN);
		if (lastResponseData.MSN.empty())
		{
			resultSetEx(false, "Error:MES分配的SN为空.");
			break;
		}
		resultSetFP(WriteSN(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], lastResponseData.MSN.c_str(), IsQualPlat, pHonor_callback) == 0, "WriteSN");
		if (!retBool) break;
		resultSetFP(VerifySN(CommonParam["DUTCom"].c_str(), lastResponseData.MSN.c_str(), pHonor_callback) == 0, "VerifySN");
		if (!retBool) break;
		break;
	}
	case U("WriteBTMac"):				//35	写BT MAC，并校验  
	{
		BOE_CB_OUTLog_Default("Try To Write BTMAC:" + lastResponseData.BTMAC);
		if (lastResponseData.BTMAC.empty())
		{
			resultSetEx(false, "Error:MES分配的BT_MAC是空值.");
			break;
		}
		resultSetFP(WriteBTMAC(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], lastResponseData.BTMAC.c_str(), IsQualPlat, pHonor_callback) == 0, "WriteBTMAC");
		if (!retBool) break;
		resultSetFP(VerifyBTMAC(CommonParam["DUTCom"].c_str(), lastResponseData.BTMAC.c_str(), pHonor_callback) == 0, "VerifyBTMAC");
		if (!retBool) break;
		break;
	}
	case U("WriteWIFIMac"):				//36	写WIFI MAC，并校验
	{
		BOE_CB_OUTLog_Default("Try To Write WLANMAC:" + lastResponseData.WIFIMAC);
		if (lastResponseData.WIFIMAC.empty())
		{
			resultSetEx(false, "Error: MES分配的WLAN_MAC是空值.");
			break;
		}
		resultSetFP(WriteWifiMAC(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], lastResponseData.WIFIMAC.c_str(), IsQualPlat, pHonor_callback) == 0, "WriteWifiMAC");
		if (!retBool) break;
		resultSetFP(VerifyWifiMAC(CommonParam["DUTCom"].c_str(), lastResponseData.WIFIMAC.c_str(), pHonor_callback) == 0, "VerifyWifiMAC");
		if (!retBool) break;
		break;
	}
	case U("WriteUDID"):				//37	写入UDID，并校验
	{
		if (StationData.customInfos.find("UDID") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有UDID配置，跳过当前测试。");
			break;
		}
		// 创建UDID
		char UDID[128]{ 0 };
		resultSetFP(CreateUDID(CommonParam["DUTCom"].c_str(), lastResponseData.MSN.c_str(), lastResponseData.BTMAC.c_str(), lastResponseData.WIFIMAC.c_str(), UDID, 128, pHonor_callback) == 0, "CreateUDID");
		if (!retBool) break;
		BOE_CB_OUTLog_Default("CreateUDID Is:" + std::string(UDID));
		// 写入UDID
		BOE_CB_OUTLog_Default("Try To Write UDID:" + std::string(UDID));
		resultSetFP(WriteUDID(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], std::string(UDID).c_str(), IsQualPlat, pHonor_callback) == 0, "WriteUDID");
		if (!retBool) break;
		// 校验UDID
		resultSetFP(VerifyUDID(CommonParam["DUTCom"].c_str(), std::string(UDID).c_str(), pHonor_callback) == 0, "VerifyUDID");
		if (!retBool) break;
		dataParam.UDID = std::string(UDID);
		break;
	}
	case U("CreatePublicKey"):			//38	触发软件开始生成PUBLICK KEY
	{
		if (StationData.customInfos.find("PUBLICKEY") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有PUBLICKEY配置，跳过当前测试。");
			break;
		}
		// 创建PUBLICKEY
		resultSetFP(CreatePublicKey(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "CreatePublicKey");
		if (!retBool) break;
		// 读取PUBLICKEY
		char buff[4096]{ 0 };
		resultSetFP(ReadPublicKey(CommonParam["DUTCom"].c_str(), buff, 4096, pHonor_callback) == 0, "读取PublicKey");
		if (!retBool) break;
		dataParam.PublicKey = string(buff);
		break;
	}
	case U("WriteVendorCountry"):		//40	写入锁卡表VENDOR COUNTRY字段信息，并校验
	{
		if (StationData.customInfos.find("VENDOR") == StationData.customInfos.end() && StationData.customInfos.find("COUNTRY") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[VENDOR]&[COUNTRY]配置，跳过当前测试。");
			break;
		}
		string VENDOR = StationData.customInfos["VENDOR"].Value;
		string COUNTRY = StationData.customInfos["COUNTRY"].Value;
		BOE_CB_OUTLog_Default("Try To Write VENDOR(" + VENDOR + ") And COUNTRY(" + COUNTRY + ").");
		resultSetFP(WriteVendorCountry(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], VENDOR.c_str(), COUNTRY.c_str(), pHonor_callback) == 0, "写入VendorCountry");
		if (!retBool) break;
		resultSetFP(VerifyVendorCountry(CommonParam["DUTCom"].c_str(), VENDOR.c_str(), COUNTRY.c_str(), pHonor_callback) == 0, "校验VendorCountry");
		if (!retBool) break;
		break;
	}
	case U("WriteProductName"):			//41	写入锁卡表PRODUCT_NAME字段，并校验
	{
		if (StationData.customInfos.find("PRODUCT_NAME") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[PRODUCT_NAME]配置，跳过当前测试。");
			break;
		}
		string PRODUCT_NAME = StationData.customInfos["PRODUCT_NAME"].Value;
		BOE_CB_OUTLog_Default("Try To Write PRODUCT_NAME:" + PRODUCT_NAME);
		resultSetFP(WriteProductName(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], PRODUCT_NAME.c_str(), pHonor_callback) == 0, "写入ProductName");
		if (!retBool) break;
		resultSetFP(VerifyProductName(CommonParam["DUTCom"].c_str(), PRODUCT_NAME.c_str(), pHonor_callback) == 0, "校验ProductName");
		if (!retBool) break;
		break;
	}
	case U("WriteMarketingName"):		//42	写入锁卡表MARKETING_NAME字段，并校验
	{
		if (StationData.customInfos.find("MARKETING_NAME") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[MARKETING_NAME]配置，跳过当前测试。");
			break;
		}
		string MARKETING_NAME = StationData.customInfos["MARKETING_NAME"].Value;
		BOE_CB_OUTLog_Default("Try To Write MARKETING_NAME:" + MARKETING_NAME);
		resultSetFP(WriteMarketingName(CommonParam["DUTCom"].c_str(), MARKETING_NAME.c_str(), pHonor_callback) == 0, "写入MarketingName");
		if (!retBool) break;
		resultSetFP(VerifyMarketingName(CommonParam["DUTCom"].c_str(), MARKETING_NAME.c_str(), pHonor_callback) == 0, "校验MarketingName");
		if (!retBool) break;
		break;
	}
	case U("WriteCertifyCode"):			//44    写入和校验电子认证标签CERTIFY_CODE
	{
		if (StationData.customInfos.find("CERTIFY_CODE") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[CERTIFY_CODE]配置，跳过当前测试。");
			break;
		}
		string CERTIFY_CODE = StationData.customInfos["CERTIFY_CODE"].Value;
		BOE_CB_OUTLog_Default("Try To Write CERTIFY_CODE:" + CERTIFY_CODE);
		resultSetFP(WriteCertifyCode(CommonParam["DUTCom"].c_str(), CERTIFY_CODE.c_str(), pHonor_callback) == 0, "写入CertifyCode");
		if (!retBool) break;
		resultSetFP(VerifyCertifyCode(CommonParam["DUTCom"].c_str(), CERTIFY_CODE.c_str(), pHonor_callback) == 0, "校验CertifyCode");
		if (!retBool) break;
		break;
	}
	case U("WriteSecretType"):			//45	写入锁卡表SECRETTYPE字段，并校验
	{
		if (StationData.customInfos.find("SECRETTYPE") == StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SECRETTYPE]配置，跳过当前测试。");
			break;
		}
		BOE_CB_ShowInfo("Try to WriteSecretType:" + StationData.customInfos["SECRETTYPE"].Value);
		BOE_CB_OUTLog_Default("Try to WriteSecretType:" + StationData.customInfos["SECRETTYPE"].Value);
		resultSetFP(WriteSecretType(CommonParam["DUTCom"].c_str(), StationData.customInfos["SECRETTYPE"].Value.c_str(), pHonor_callback) == 0, "WriteSecretType");
		break;
	}
	case U("WriteFRPKey"):				//46	写FRP_KEY，并校验
	{
		if (StationData.customInfos.find("FRP_KEY") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[FRP_KEY]配置，跳过当前测试。");
			break;
		}
		dataParam.FRP_KEY = "";
		if (dataParam.FRP_KEY.empty() || dataParam.FRP_KEY == "")
		{
			BOE_CB_OUTLog_Default("Mes have not the FrpKey Data. FrpKey data will create by this app.");
			string FRPKey = "";
			int count = 0;
			while (!ProduceRandomNumberCrypt(FRPKey) && count < 3)
			{
				FRPKey = "";
				count++;
			}
			resultSetFP(!FRPKey.empty(), "ProduceRandomNumberCrypt(Create FrpKey)");
			if (!retBool)
			{
				BOE_CB_ShowInfo("Error:创建 FRPKey 信息失败，请检查锁卡表和排查相关指令。");
			}
			if (!retBool) break;
			BOE_CB_OUTLog_Default("Create FRPKey:" + FRPKey);
			dataParam.FRP_KEY = FRPKey;
		}
		BOE_CB_OUTLog_Default("Try To Write FRPKey:" + dataParam.FRP_KEY);
		resultSetFP(WriteFrpKey(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], dataParam.FRP_KEY.c_str(), IsQualPlat, pHonor_callback) == 0, "WriteFrpKey");
		if (!retBool) break;
		resultSetFP(VerifyFrpKey(CommonParam["DUTCom"].c_str(), dataParam.FRP_KEY.c_str(), pHonor_callback) == 0, "VerifyFrpKey");
		if (!retBool) break;
		break;
	}
	case U("WriteKeyAttestation"):		//51	写入锁卡表谷歌设备证书，并校验
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 1))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SPECIAL_DATA_SWITCH[" + SPECIAL_DATA_SWITCH + "].Don't need to write value!");
			break;
		}
		if (lastResponseData.GoogleKey.A_KeyAttestation_G_1.empty() || lastResponseData.GoogleKey.A_KeyAttestation_G_2.empty() || lastResponseData.GoogleKey.A_KeyAttestation_G_3.empty() || lastResponseData.GoogleKey.A_KeyAttestation_G_4.empty())
		{
			resultSetEx(false, "Error:MES配置错误，谷歌Key字段存在空值！");
		}
		BOE_CB_OUTLog_Default("Try To Write KeyAttestation -k1:" +
			lastResponseData.GoogleKey.A_KeyAttestation_G_1 + " -k2:" +
			lastResponseData.GoogleKey.A_KeyAttestation_G_2 + " -k3:" +
			lastResponseData.GoogleKey.A_KeyAttestation_G_3 + " -k4:" +
			lastResponseData.GoogleKey.A_KeyAttestation_G_4
		);
		resultSetFP(WriteKeyAttestation(CommonParam["DUTCom"].c_str(),
			lastResponseData.GoogleKey.A_KeyAttestation_G_1.c_str(),
			lastResponseData.GoogleKey.A_KeyAttestation_G_2.c_str(),
			lastResponseData.GoogleKey.A_KeyAttestation_G_3.c_str(),
			lastResponseData.GoogleKey.A_KeyAttestation_G_4.c_str(), pHonor_callback) == 0, "WriteKeyAttestation");
		if (!retBool) break;

		BOE_CB_OUTLog_Default("Target A_KeyAtte_G_Verify:" + lastResponseData.GoogleKey.A_KeyAtte_G_Verify);
		resultSetFP(VerifyKeyAttestation(CommonParam["DUTCom"].c_str(), lastResponseData.GoogleKey.A_KeyAtte_G_Verify.c_str(), pHonor_callback) == 0, "VerifyKeyAttestation");
		if (!retBool) break;
		break;
	}
	case U("WriteDeviceCerts"):			//52	写入锁卡表荣耀设备证书，并校验
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 4))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SPECIAL_DATA_SWITCH[" + SPECIAL_DATA_SWITCH + "].Don't need to write value!");
			break;
		}
		if (lastResponseData.DeviceKey.Hw_Device_Certs_1.empty() || lastResponseData.DeviceKey.Hw_Device_Certs_2.empty() || lastResponseData.DeviceKey.Hw_Device_Certs_3.empty() || lastResponseData.DeviceKey.Hw_Device_Certs_4.empty() || lastResponseData.DeviceKey.Hw_Device_Certs_5.empty())
		{
			resultSetEx(false, "Error:MES配置错误，设备证书字段存在空值！");
		}
		BOE_CB_OUTLog_Default("Try To Write DeviceCerts -Certs_1:" +
			lastResponseData.DeviceKey.Hw_Device_Certs_1 + " -Certs_2:" +
			lastResponseData.DeviceKey.Hw_Device_Certs_2 + " -Certs_3:" +
			lastResponseData.DeviceKey.Hw_Device_Certs_3 + " -Certs_4:" +
			lastResponseData.DeviceKey.Hw_Device_Certs_4 + " -Certs_5:" +
			lastResponseData.DeviceKey.Hw_Device_Certs_5
		);
		resultSetFP(WriteDeviceCerts(CommonParam["DUTCom"].c_str(),
			lastResponseData.DeviceKey.Hw_Device_Certs_1.c_str(),
			lastResponseData.DeviceKey.Hw_Device_Certs_2.c_str(),
			lastResponseData.DeviceKey.Hw_Device_Certs_3.c_str(),
			lastResponseData.DeviceKey.Hw_Device_Certs_4.c_str(),
			lastResponseData.DeviceKey.Hw_Device_Certs_5.c_str(), pHonor_callback) == 0, "WriteDeviceCerts");
		if (!retBool) break;

		BOE_CB_OUTLog_Default("Target Hw_Device_Certs_VD:" + lastResponseData.DeviceKey.Hw_Device_Certs_VD);
		resultSetFP(VerifyDeviceCerts(CommonParam["DUTCom"].c_str(), lastResponseData.DeviceKey.Hw_Device_Certs_VD.c_str(), pHonor_callback) == 0, "VerifyDeviceCerts");
		if (!retBool) break;
		break;
	}
	case U("WriteTrustDeviceIDS"):		//43	写入锁卡表TRUST_DEVICE_IDS字段，并校验要求必须先写入IMEI(平板WIFI-ONLY项目除外)和SN才会生效
	{
		if (StationData.customInfos.find("TRUST_DEVICE_IDS") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[TRUST_DEVICE_IDS]配置，跳过当前测试。");
			break;
		}
		string TrustDeviceIDS = StationData.customInfos["TRUST_DEVICE_IDS"].Value;

		if (TrustDeviceIDS.empty())
		{
			resultSetEx(false, "TRUST_DEVICE_IDS is empty! 检查锁卡表内容.");
			break;
		}
		BOE_CB_OUTLog_Default("Try To Write TrustDeviceIDS:" + TrustDeviceIDS);
		BOE_CB_OUTLog_Default("MSN:" + lastResponseData.MSN);
		if (lastResponseData.IS5G == "")
		{
			resultSetFP(WriteTrustDeviceIDS(CommonParam["DUTCom"].c_str(), TrustDeviceIDS.c_str(), lastResponseData.MSN.c_str(), lastResponseData.MEID.c_str(), lastResponseData.IMEI.c_str(), nullptr, pHonor_callback) == 0, "WriteTrustDeviceIDS");
			if (!retBool) break;
		}
		else
		{
			resultSetFP(WriteTrustDeviceIDS(CommonParam["DUTCom"].c_str(), TrustDeviceIDS.c_str(), lastResponseData.MSN.c_str(), nullptr, nullptr, nullptr, pHonor_callback) == 0, "WriteTrustDeviceIDS");
			if (!retBool) break;
		}
		break;
	}
	case U("WriteIDSAttestation"):		//53	写入锁卡表IDS_ATTESTATION字段，并校验 5G需要写imei
	{
		if (StationData.customInfos.find("IDS_ATTESTATION") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[IDS_ATTESTATION]配置，跳过当前测试。");
			break;
		}
		string AttestationIDS = StationData.customInfos["IDS_ATTESTATION"].Value;
		if (AttestationIDS.empty()) {
			resultSetEx(false, "IDS_ATTESTATION is empty! 检查锁卡表内容.");
			break;
		}
		BOE_CB_OUTLog_Default("Try To Write AttestationIDS:" + AttestationIDS);
		resultSetFP(WriteAttestationIDS(CommonParam["DUTCom"].c_str(), AttestationIDS.c_str(), lastResponseData.MSN.c_str(), nullptr, nullptr, nullptr, pHonor_callback) == 0, "WriteAttestationIDS");
		if (!retBool) break;
		break;
	}
	case U("WriteFuseGid"):				//54	写GID数据
	{
		if (StationData.customInfos.find("FUSE_GID") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[FUSE_GID]配置，跳过当前测试。");
			break;
		}
		string FUSE_GID = StationData.customInfos["FUSE_GID"].Value;
		if (FUSE_GID.empty())
		{
			resultSetEx(false, "Error:FUSE_GID为空,检查锁卡表数据。");
			break;
		}
		BOE_CB_OUTLog_Default("Try To Write FUSE_GID:" + FUSE_GID);
		BOE_CB_ShowInfo("Try To Write FUSE_GID:" + FUSE_GID);
		resultSetFP(WriteFuseGid(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, FUSE_GID.c_str(), pHonor_callback) == 0, "WriteFuseGid");
		if (!retBool) break;
		resultSetFP(CheckFuseGid(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, FUSE_GID.c_str(), pHonor_callback) == 0, "CheckFuseGid");
		if (!retBool) break;
		break;
	}
	case U("WriteBenchmarkFlag"):		//56	写防跑分：锁卡表BENCHMARKFLAG字段，并校验
	{
		if (StationData.customInfos.find("BENCHMARKFLAG") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[BENCHMARKFLAG]配置，跳过当前测试。");
			break;
		}
		string BENCHMARKFLAG = StationData.customInfos["BENCHMARKFLAG"].Value;
		BOE_CB_OUTLog_Default("Try To Write BENCHMARKFLAG:" + BENCHMARKFLAG);
		resultSetFP(WriteBenchmarkFlag(CommonParam["DUTCom"].c_str(), BENCHMARKFLAG.c_str(), pHonor_callback) == 0, "WriteBenchmarkFlag");
		if (!retBool) break;
		resultSetFP(VerifyBenchmarkFlag(CommonParam["DUTCom"].c_str(), BENCHMARKFLAG.c_str(), pHonor_callback) == 0, "VerifyBenchmarkFlag");
		if (!retBool) break;
		break;
	}
	case U("CloseQuickAccess"):			//57    关闭快速接入 指令不完整 流程描述不清楚
	{
		// 功能: Q平台特有逻辑，写入并回读校验NV是否正确，目前支持NV453和NV60009
		// 参数: uint16_t nvid为入参，要写入的NV id 
		// 返回: -1 表示失败，0 表示成功
		// CUSTOMIZATIONKEYACTION_API int  QualWriteNVItem(const char* addr, uint16_t nvid, void* callback);
		// BOE_CB_OUTLog_Default("不确定关闭快速接入是否执行 QualWriteNVItem 传参 60009");
		resultSetFP(QualWriteNVItem(CommonParam["DUTCom"].c_str(), 60009, pHonor_callback) == 0, "QualWriteNVItem");
		if (!retBool) break;
		break;
	}
	case U("WriteAcclock"):				//59	写准入模式：写入ACCLOCK，并校验
	{
		if (StationData.customInfos.find("NCK_DIAGUNLOCK") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[NCK_DIAGUNLOCK]配置，跳过当前测试。");
			break;
		}
		// 强制重新创建 避免意外出错
		dataParam.NCK_DIAGUNLOCK = "";

		string str_LOCKTYPE = StationData.customInfos["LOCKTYPE"].Value;
		int num = HexStrToInt(str_LOCKTYPE);
		BOE_CB_OUTLog_Default("LOCKTYPE:" + str_LOCKTYPE + " HexStrToInt:" + std::to_string(num));
		if ((num & 2) != 0) // 第二位不为0 则要生成随机数
		{
			if (dataParam.NCK_DIAGUNLOCK.empty() || dataParam.NCK_DIAGUNLOCK == "")
			{
				// 生成NCK_DIAGUNLOCK
				string NCK_DIAGUNLOCK = "";
				int count = 0;
				while (!ProduceRandomNumberCrypt(NCK_DIAGUNLOCK) && count < 3)
				{
					NCK_DIAGUNLOCK = "";
					count++;
				}
				resultSetFP(!NCK_DIAGUNLOCK.empty(), "ProduceRandomNumberCrypt");
				if (!retBool) break;
				BOE_CB_OUTLog_Default("Create NCK_DIAGUNLOCK:" + NCK_DIAGUNLOCK);
				dataParam.NCK_DIAGUNLOCK = NCK_DIAGUNLOCK;
			}
		}
		else // 第二位为0 写入16位0
		{
			dataParam.NCK_DIAGUNLOCK = "0000000000000000";
		}

		// 写入ACCLOCK，并校验
		BYTE HUN[8]{ 0 };
		hexToBytes(dogInfoPtr->hun, HUN, 8);
		BOE_CB_OUTLog_Default("Try To Write NCK_DIAGUNLOCK:" + dataParam.NCK_DIAGUNLOCK);
		resultSetFP(WriteAccLock(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], dataParam.NCK_DIAGUNLOCK.c_str(), (char*)HUN, IsQualPlat, pHonor_callback) == 0, "WriteAccLock");
		if (!retBool) break;

		// VERIFYCUSTOMIZATION_API int  VerifyAccLock(const char* addr, const char* nckDiagUnlock, void* callback);
		resultSetFP(VerifyAccLock(CommonParam["DUTCom"].c_str(), dataParam.NCK_DIAGUNLOCK.c_str(), pHonor_callback) == 0, "VerifyAccLock");
		if (!retBool) break;
		break;
	}
	case U("WriteUserlock"):			//60	写研发/用户模式：写入USERLOCK，并校验
	{
		if (StationData.customInfos.find("LOCKTYPE") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[LOCKTYPE]配置，跳过当前测试。");
			break;
		}
		string LOCKTYPE = StationData.customInfos["LOCKTYPE"].Value;
		// 写入USERLOCK，并校验
		BYTE HUN[8]{ 0 };
		hexToBytes(dogInfoPtr->hun, HUN, 8);
		BOE_CB_OUTLog_Default("Try To Write LOCKTYPE:" + LOCKTYPE);
		resultSetFP(WriteUserLock(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], LOCKTYPE.c_str(), (char*)HUN, IsQualPlat, pHonor_callback) == 0, "WriteUserLock");
		if (!retBool) break;
		// VERIFYCUSTOMIZATION_API int  VerifyUserLock(const char* addr, const char* lockType, void* callback);
		resultSetFP(VerifyUserLock(CommonParam["DUTCom"].c_str(), LOCKTYPE.c_str(), pHonor_callback) == 0, "VerifyUserLock");
		if (!retBool) break;
		break;
	}
	case U("ReadEmmcID"):
	{
		if (StationData.customInfos.find("EMMC_ID") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[EMMC_ID]配置，跳过当前测试。");
			break;
		}
		string strReadEmmcID;
		resultSetFP(ReadEMMCID(strReadEmmcID) == 0, "从DUT中读取EMMCID");
		if (!retBool) break;
		BOE_CB_OUTLog_Default("ReadEmmcID:" + strReadEmmcID);
		this->dataParam.EMMC_ID = strReadEmmcID;
		break;
	}
	case U("WriteCWFlag"):				//61	写CW P标志位
	{
		string stationFlag = "CW P";
		// 写入CW P标志位
		BOE_CB_OUTLog_Default("Try To Write stationFlag:" + stationFlag);
		resultSetFP(SetCWFlag(CommonParam["DUTCom"].c_str(), stationFlag.c_str(), pHonor_callback) == 0, "SetCWFlag");
		if (!retBool) break;
		//功能：检查CW MC 标志位是否设置成功
		//返回：-1 表示失败， 0 表示成功
		resultSetFP(CheckCWFlag(CommonParam["DUTCom"].c_str(), stationFlag.c_str(), pHonor_callback) == 0, "CheckCWFlag");
		if (!retBool) break;
		break;
	}
	case U("NVBackup"):                 //64    NV备份
	{
		// 功能: Q平台特有逻辑，golden copy，包含NV同步功能，将NV信息同步到EMMC分区以及EFS分区
		// 返回: -1 表示失败，0 表示成功
		// CUSTOMIZATIONKEYACTION_API int  QualGoldenCopy(const string& addr, void* callback);
		resultSetFP(QualGoldenCopy(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "QualGoldenCopy");
		if (!retBool) break;
		break;
	}
	case U("SetRWFlag"):			//62    设置返工模式
	{
		// QualEraseNRWFlag
		// 功能: Q平台特有逻辑，擦除NRW模式标志位(即设置手机为返工模式)
		// 返回: -1 表示失败，0 表示成功
		// CUSTOMIZATIONKEYACTION_API int  QualEraseNRWFlag(const char* addr, void* callback);
		resultSetFP(QualEraseNRWFlag(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "QualEraseNRWFlag");
		if (!retBool) break;

		// QualCheckRWFlag
		// 功能: Q平台特有逻辑，检查手机是否为返工模式
		// 返回: -1 表示失败，非返工模式  0 表示成功，返工模式
		// CUSTOMIZATIONKEYACTION_API int  QualCheckRWFlag(const char* addr, void* callback);
		resultSetFP(QualCheckRWFlag(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "QualCheckRWFlag");
		if (!retBool) break;
		break;
	}

	case U("WriteMMIAutoRunFlag"):		//64	写MMI2S自启动标志位，并校验
	{
		if (dataParam.isDGSlaveServer)// 备板跳过MMI自启
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item is Skiped; 判定当前为服务备板，跳过当前测试。");
			break;
		}
		// 写MMI2自启动标志位，并校验
		BYTE HUN[8]{ 0 };
		hexToBytes(dogInfoPtr->hun, HUN, 8);
		resultSetFP(SetMMI2AutoRunFlag(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], (char*)HUN, IsQualPlat, pHonor_callback) == 0, "SetMMI2AutoRunFlag");// 内部包含检查
		break;
	}
	case U("CheckBatteryAntiFake"):     //62    电池防伪
	{
		if (dataParam.isDGSlaveServer)// 备板跳过电池防伪
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item is Skiped; 判定当前为服务备板，跳过当前测试。");
			break;
		}
		char rsp[512]{ 0 };
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^BATTCTYPE?\r", "BATTCTYPE:0,original\\s*OK", rsp, 512, pHonor_callback) == 0, "电池防伪");
		break;
	}
	case U("WriteKeyBox"):				//69	写keybox
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 0))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表[SPECIAL_DATA_SWITCH]配置值为[" + SPECIAL_DATA_SWITCH + "]，跳过当前测试。");
			break;
		}
		// CRC校验
		string error = "";
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey CRC Check...");
		if (!WidevineKeyCRCCheck(lastResponseData.WidevineKey, error))
		{
			resultSetEx(false, "Error:" + error);
			break;
		}
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey CRC Check Pass.");

		// 数据解密
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey Data Decrypt...");
		string outDecryptData = "";
		//string error = "";
		int outLength = 0;
		if (!WidevineKeyDecryptData(lastResponseData.WidevineKey, outDecryptData, outLength, error))
		{
			resultSetEx(false, "Error:" + error);
			break;
		}
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey Data Decrypt Pass.");

		// 写入KeyBox
		BOE_CB_OUTLog_DefaultAndShowInfo("Write WidevineKey Data...");
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), string("AT^KEYBOXDATA=STORE," + outDecryptData + "\r").c_str(), "^KEYBOXDATA:1\\s*OK", nullptr, 0, pHonor_callback) == 0, "写入KeyBox");
		if (!retBool) break;

		// 校验KeyBox
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), string("AT^KEYBOXDATA=VERIFY," + outDecryptData + "\r").c_str(), "^KEYBOXDATA:1\\s*OK", nullptr, 0, pHonor_callback) == 0, "校验KeyBox");
		break;
	}
	case U("FactoryResetCW"):			//71	恢复出厂设置
	{
		resultSetFP(FactoryResetCW(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "FactoryReset");
		if (!retBool)
		{
			ErrorMsg = "恢复出厂设置失败";
		}
		break;
	}

	case U("UploadInformation"):		//72	上传UDID、EMMCID、PUBLICKEY信息到MES上保存
	{
		//获取加密狗剩余时间
		long remainDays = GetNetDogRemainDays(dogInfoPtr->dog);
		if (remainDays < 30)
		{
			BOE_CB_OUTLog_Default("获取加密狗剩余时间：" + to_string(remainDays) + "天");
			resultSet(false, "获取加密狗剩余时间：" + to_string(remainDays) + "天");
			resultSet(true, "设置为true");
		}
		else
		{
			BOE_CB_OUTLog_Default("获取加密狗剩余时间：" + to_string(remainDays) + "天");
			BOE_CB_ShowInfo("获取加密狗剩余时间：" + to_string(remainDays) + "天");
		}
		// 上传到MES
		resultSetFP(MesPostPass(), "Post Result Data To MES ");
		// 已经上传了结果，不需要再次上传
		isRetFalsePostMes = false;
		break;
	}
	default:
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("Error:" + TestMathed + " does not exit!");
		BOE_CB_MessageBoxData("Error:" + TestMathed + " does not exit!");
		resultSet(false);
		break;
	}
	}
#elif MC||OBA  // MC站点
	switch (toUnicode(TestMathed.c_str()))
	{
	case U("Init"):						// 自定义 进行设备等待 可能是等待端口接通
	{
		Init(paraData, retData, errData);
		isRetFalsePostMes = false;
		break;
	}
	case U("Authentication"):			//3		AP鉴权
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("启动状态检查...");
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^DEVBOOTSTATE?\r", "DEVBOOTSTATE:1\\s*OK", nullptr, 0, pHonor_callback) == 0, "DUT启动状态检查");
		if (!retBool)break;
		Authentication(paraData, retData, errData);
		break;
	}
	case U("ReadBoardSN"):				//2		读取单板SN
	{
		CheckBarcode(paraData, retData, errData);
		break;
	}
	case U("ReadMobileSN"):				//3		读取整机SN
	{
		char data[128]{ 0 };
		resultSetFP(ReadSN(CommonParam["DUTCom"].c_str(), data, 128, pHonor_callback) == 0, "读取SN");
		if (!retBool) break;
		BOE_CB_OUTLog_DefaultAndShowInfo("读取的MSN：" + string(data));
#ifdef OBA //!OBA
		resultSetFP(string(data) == dataParam.ScanCode, "背贴条码比对");
		if (!retBool) break;
		//BOE_CB_SN(string(data));
#else	
		// 校验读取的SN是否和MES一致
		resultSetFP(string(data) == lastResponseData.MSN, "DUT内部SN与MES分配的SN校验");
		if (!retBool) break;
#endif // !0BA
		break;

	}
	case U("ReadSubBoardFlag"):			//4		读取背板标志
	{
		CheckSubBoardFlag(paraData, retData, errData);
		break;
	}
	case U("CheckNV453"):				//5		校验NV453的值是否为0
	{
		resultSetFP(QualCheckNV453(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "校验NV453");
		break;
	}

	case U("CheckManufacturerFlag"):	//7		检测UT、MMI2 / MMI2S标志位
	{
		BOE_CB_OUTLog_Default("读取标志位.");
		char rsp[512];
		int ret = RequestString(CommonParam["DUTCom"].c_str(), "AT^FACINFO?\r", nullptr, rsp, 512, pHonor_callback);
		resultSetFP(ret == 0, "Send AT Command ");
		if (!retBool) break;
		string retStr = string(rsp);
		cmatch what;
		if (std::regex_search(rsp, what, regex("\\^FACINFO:0,(.*)")))
		{
			if (what.size() > 1) retStr = what[1];
		}
		// UT 标志位检查
		resultSetFP(retStr.find("UT P") == 110, "Check UT Flag ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:UT标志位检查失败，请确认UT工序是否完成！");
			isRetFalsePostMes = false;
			break;
		}

		// MMI2/MMI2S
		//CUSTOMIZATIONKEYACTION_API int  CheckMMIFlag(const char* addr, const char* MMIFlagList, void* callback);
		char buff[512];
		resultSetFP(ReadMMIFlag(CommonParam["DUTCom"].c_str(), buff, 512, pHonor_callback) == 0, "ReadMMIFlag");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:读取MMI标志位 失败！");
			isRetFalsePostMes = false;
		}
		if (!retBool) break;

		string MMIFlagList(buff);
		BOE_CB_OUTLog_Default("MMIFlagList:" + string(buff));
		int num = HexStrToInt(MMIFlagList);
		BOE_CB_OUTLog_Default("MMIFlagList To DEC:" + std::to_string(num));
		resultSetFP((num & 72) != 0, "Check MMI2/MMI2S Flag ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:MMI2/MMI2S 没有PASS标志位！");
			isRetFalsePostMes = false;
		}
		if (!retBool) break;
		break;
	}
	case U("CheckSoftwareVersion"):		//8		版本号校验
	{
		CheckSoftwareVersion(paraData, retData, errData);
		break;
	}
	case U("EraseDapTime"):				//9		擦除开机时间，MTK新增
	{
		resultSetFP(ErasePowerOnTime(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "擦除开机时间");
		break;
	}
	case U("CheckSDCardNotExist"):		//10    SD 卡不能在位 在位要拦截
	{
		if (lastResponseData.SupportSD == "N") // 有NSD 即不带SD卡版本 无需测试SD卡功能
		{
			resultSetEx(true, "Warning:当前DUT不支持SD卡,跳过检查。SupportSD:" + lastResponseData.SupportSD);
			break;
		}
		if (dataParam.isDGSlaveServer)
		{
			BOE_CB_ShowInfo("Skip:备板 跳过检测!");
			resultSetEx(true, "It is a DGSlaveServer and this step will be skipped.");
			break;
		}

		// SD卡在位 sdCardState=1 不在位 sdCardState=0
		int sdCardState = 0;
		auto ret = ReadSDCardState(CommonParam["DUTCom"].c_str(), sdCardState, pHonor_callback);
		if (ret == 0)
		{
			BOE_CB_OUTLog_Default("ReadSDCardState:" + std::to_string(sdCardState));
			resultSet(sdCardState == 0);
			if (!retBool)
			{
				BOE_CB_ShowInfo("Error:SD卡在位，请取出SD卡！");
			}
			break;
		}
		else
		{
			if (!retBool)
			{
				BOE_CB_ShowInfo("Error:读取SD卡状态失败！");
			}
			resultSet(false);
			break;
		}

		break;
	}
	case U("CheckRoot"):				//13	Root检测拦截
	{
		resultSetFP(CheckRoot(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "ROOT 检查");
		break;
	}
	case U("CheckFactoryVer"):			//14	检查版本防回退标志位
	{
		resultSetFP(CheckFactoryVer(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "检查版本防回退标志位");
		break;
	}
	case U("CheckSIMTray"):				//15    卡托在位检查
	{
		if (lastResponseData.SupportSD == "N") // 有NSD 即不带SD卡版本 无需测试SD卡功能
		{
			resultSetEx(true, "Warning:当前DUT不支持SD卡,跳过检查。SupportSD:" + lastResponseData.SupportSD);
			break;
		}
		if (dataParam.isDGSlaveServer)
		{
			BOE_CB_ShowInfo("Skip:备板 跳过检测!");
			resultSetEx(true, "It is a DGSlaveServer and this step will be skipped.");
			break;
		}

		////功能：卡托在位检查,1表示在位 0表示不在位
		//返回：-1 表示失败卡托不在位， 0 表示成功卡托在位
		//CUSTOMIZATIONKEYACTION_API int  CheckSimSlot(const char* addr, void* callback);
		resultSet(CheckSimSlot(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0); /// 测试提示不支持 可能需要使用DIAG指令 4b c9 d6 ee 00 00 00 00 16 00 00 00 00 00 00 00 00 00 00 00 8e 33 7e 
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:卡托在位检查失败！");
		}
		break;
	}
	case U("CheckMMIAutoRunFlag"):		//16	检查MMI2自启动标志位是否已经不存在
	{
		resultSetFP(CheckMMI2AutoRunFlagClear(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "检查MMI2自启动标志位是否已经不存在");
		break;
	}
	case U("CheckRWFlag"):					//17
	{
		// 功能: Q平台特有逻辑，检查手机是否为返工模式
		// 返回: -1 表示失败，非返工模式  0 表示成功，返工模式
		// CUSTOMIZATIONKEYACTION_API int  QualCheckRWFlag(const char* addr, void* callback);
		resultSet(QualCheckRWFlag(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0);
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:检查手机是否为返工模式失败！");
		}
		break;
	}
	case U("CheckMaintenance"):			//18	检查非法维修
	{
		CheckMaintenance(paraData, retData, errData);
		break;
	}
	case U("CheckBatteryLevel"):		//19	电池电量检查
	{
		CheckBatteryLevel(paraData, retData, errData);
		break;
	}
	case U("CheckBTMac"):				//20	校验BT MAC
	{
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.BTMAC);
		if (lastResponseData.BTMAC.empty())
		{
			resultSetEx(false, "Error:BTMAC为空,检查MES数据。");
			break;
		}
		resultSetFP(VerifyBTMAC(CommonParam["DUTCom"].c_str(), lastResponseData.BTMAC.c_str(), pHonor_callback) == 0, "校验BTMac");
		break;
	}
	case U("CheckWIFIMac"):				//21	校验WIFI MAC
	{
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.WIFIMAC);
		if (lastResponseData.WIFIMAC.empty())
		{
			resultSetEx(false, "Error:WIFIMAC为空,检查MES数据。");
			break;
		}
		resultSetFP(VerifyWifiMAC(CommonParam["DUTCom"].c_str(), lastResponseData.WIFIMAC.c_str(), pHonor_callback) == 0, "校验WIFIMac");
		break;
	}
	case U("CheckUDID"):				//22	校验UDID
	{
		if (StationData.customInfos.find("UDID") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有UDID配置，跳过当前测试。");
			break;
		}
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.UDID);
		if (lastResponseData.UDID.empty())
		{
			resultSetEx(false, "Error:UDID为空,检查MES数据。");
			break;
		}
		resultSetFP(VerifyUDID(CommonParam["DUTCom"].c_str(), lastResponseData.UDID.c_str(), pHonor_callback) == 0, "校验UDID");
		break;
	}
	case U("CheckVendorCountry"):		//23	校验锁卡表VENDOR COUNTRY字段信息
	{
		if (StationData.customInfos.find("VENDOR") == StationData.customInfos.end() && StationData.customInfos.find("COUNTRY") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[VENDOR]&[COUNTRY]配置，跳过当前测试。");
			break;
		}
		string VENDOR = StationData.customInfos["VENDOR"].Value;
		string COUNTRY = StationData.customInfos["COUNTRY"].Value;
		if (VENDOR.empty() || COUNTRY.empty())
		{
			resultSetEx(false, "Error:VENDOR或COUNTRY为空,检查锁卡表数据。");
			break;
		}
		BOE_CB_OUTLog_Default("Target value VENDOR:" + VENDOR + " COUNTRY:" + COUNTRY);
		resultSetFP(VerifyVendorCountry(CommonParam["DUTCom"].c_str(), VENDOR.c_str(), COUNTRY.c_str(), pHonor_callback) == 0, "校验VendorCountry");
		break;
	}
	case U("CheckProductName"):			//24	校验锁卡表PRODUCT_NAME字段
	{
		if (StationData.customInfos.find("PRODUCT_NAME") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[PRODUCT_NAME]配置，跳过当前测试。");
			break;
		}
		string PRODUCT_NAME = StationData.customInfos["PRODUCT_NAME"].Value;
		BOE_CB_OUTLog_Default("Target value:" + PRODUCT_NAME);
		if (PRODUCT_NAME.empty())
		{
			resultSetEx(false, "Error:PRODUCT_NAME为空,检查锁卡表数据。");
			break;
		}
		resultSetFP(VerifyProductName(CommonParam["DUTCom"].c_str(), PRODUCT_NAME.c_str(), pHonor_callback) == 0, "校验ProductName");
		break;
	}
	case U("CheckMarketingName"):		//25	校验锁卡表MARKETING_NAME字段
	{
		if (StationData.customInfos.find("MARKETING_NAME") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[MARKETING_NAME]配置，跳过当前测试。");
			break;
		}
		string MARKETING_NAME = StationData.customInfos["MARKETING_NAME"].Value;
		BOE_CB_OUTLog_Default("Target value:" + MARKETING_NAME);
		if (MARKETING_NAME.empty())
		{
			resultSetEx(false, "Error:MARKETING_NAME为空,检查锁卡表数据。");
			break;
		}
		resultSetFP(VerifyMarketingName(CommonParam["DUTCom"].c_str(), MARKETING_NAME.c_str(), pHonor_callback) == 0, "校验MarketingName");
		break;
	}
	case U("CheckBenchmarkFlag"):		//26	防跑分：校验锁卡表BENCHMARKFLAG字段
	{
		if (StationData.customInfos.find("BENCHMARKFLAG") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[BENCHMARKFLAG]配置，跳过当前测试。");
			break;
		}
		string BENCHMARKFLAG = StationData.customInfos["BENCHMARKFLAG"].Value;
		BOE_CB_OUTLog_Default("Target value:" + BENCHMARKFLAG);
		if (BENCHMARKFLAG.empty())
		{
			resultSetEx(false, "Error:BENCHMARKFLAG为空,检查锁卡表数据。");
			break;
		}
		resultSetFP(VerifyBenchmarkFlag(CommonParam["DUTCom"].c_str(), BENCHMARKFLAG.c_str(), pHonor_callback) == 0, "校验BenchmarkFlag");
		break;
	}
	case U("CheckCertifyCode"):         //28    校验锁卡表CERTIFY_CODE字段
	{
		if (StationData.customInfos.find("CERTIFY_CODE") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[CERTIFY_CODE]配置，跳过当前测试。");
			break;
		}
		string CERTIFY_CODE = StationData.customInfos["CERTIFY_CODE"].Value;
		if (CERTIFY_CODE.empty())
		{
			resultSetEx(false, "Error:锁卡表中[CERTIFY_CODE]为空值.");
			break;
		}
		// VERIFYCUSTOMIZATION_API int  VerifyCertifyCode(const char* addr, const char* val, void* callback);
		BOE_CB_OUTLog_Default("Target value:" + CERTIFY_CODE);
		resultSetFP(VerifyCertifyCode(CommonParam["DUTCom"].c_str(), CERTIFY_CODE.c_str(), pHonor_callback) == 0, "校验CertifyCode");
		break;
	}
	case U("CheckKeyAttestation"):		//29	校验锁卡表谷歌设备证书
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (SPECIAL_DATA_SWITCH.empty())
		{
			resultSetEx(false, "Error:SPECIAL_DATA_SWITCH为空,检查锁卡表数据。");
			break;
		}
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 1))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SPECIAL_DATA_SWITCH[" + SPECIAL_DATA_SWITCH + "] Don't need to check value!");
			break;
		}
		// VERIFYCUSTOMIZATION_API int  VerifyKeyAttestation(const char* addr, const char* keyVD, void* callback);
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.GoogleKey.A_KeyAtte_G_Verify);
		if (lastResponseData.GoogleKey.A_KeyAtte_G_Verify.empty())
		{
			resultSetEx(false, "Error:MES返回的GoogleKey.A_KeyAtte_G_Verify值为空，检查MES。");
			break;
		}
		resultSetFP(VerifyKeyAttestation(CommonParam["DUTCom"].c_str(), lastResponseData.GoogleKey.A_KeyAtte_G_Verify.c_str(), pHonor_callback) == 0, "校验KeyAttestation");
		break;
	}
	case U("CheckTrustDeviceIDS"):		//30	校验锁卡表TRUST_DEVICE_IDS字段
	{
		if (StationData.customInfos.find("TRUST_DEVICE_IDS") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[TRUST_DEVICE_IDS]配置，跳过当前测试。");
			break;
		}
		string TrustDeviceIDS = StationData.customInfos["TRUST_DEVICE_IDS"].Value;
		BOE_CB_OUTLog_Default("Target value:" + TrustDeviceIDS);
		if (TrustDeviceIDS.empty())
		{
			resultSetEx(false, "Error:TrustDeviceIDS为空,检查锁卡表数据。");
			break;
		}
		BOE_CB_OUTLog_Default("lastResponseData.MSN:" + lastResponseData.MSN);
		// VERIFYCUSTOMIZATION_API int  VerifyTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
		resultSetFP(VerifyTrustDeviceIDS(CommonParam["DUTCom"].c_str(), TrustDeviceIDS.c_str(), lastResponseData.MSN.c_str(),
			nullptr,
			nullptr,
			nullptr,
			pHonor_callback) == 0, "校验TrustDeviceIDS");
		break;
	}
	case U("CheckIDSAttestation"):		//31	校验锁卡表IDS_ATTESTATION字段
	{
		if (StationData.customInfos.find("IDS_ATTESTATION") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[IDS_ATTESTATION]配置，跳过当前测试。");
			break;
		}
		string AttestationIDS = StationData.customInfos["IDS_ATTESTATION"].Value;
		if (AttestationIDS.empty())
		{
			resultSetEx(false, "Error:IDS_ATTESTATION为空,检查锁卡表数据。");
			break;
		}
		BOE_CB_OUTLog_Default("Target value:" + AttestationIDS);
		// VERIFYCUSTOMIZATION_API int  VerifyAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
		resultSetFP(VerifyAttestationIDS(CommonParam["DUTCom"].c_str(), AttestationIDS.c_str(), lastResponseData.MSN.c_str(),
			nullptr,
			nullptr,
			nullptr,
			pHonor_callback) == 0, "检查AttestationIDS");
		break;
	}
	case U("CheckDeviceCerts"):			//32	校验锁卡表荣耀设备证书
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (SPECIAL_DATA_SWITCH.empty())
		{
			resultSetEx(false, "Error:SPECIAL_DATA_SWITCH为空,检查锁卡表数据。");
			break;
		}
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 4))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SPECIAL_DATA_SWITCH[" + SPECIAL_DATA_SWITCH + "] Don't need to check value!");
			break;
		}
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.DeviceKey.Hw_Device_Certs_VD);
		if (lastResponseData.DeviceKey.Hw_Device_Certs_VD.empty())
		{
			resultSetEx(false, "Error:MES返回的DeviceKey.Hw_Device_Certs_VD值为空，检查MES。");
			break;
		}
		// VERIFYCUSTOMIZATION_API int  VerifyDeviceCerts(const char* addr, const char* certVD, void* callback);
		resultSetFP(VerifyDeviceCerts(CommonParam["DUTCom"].c_str(), lastResponseData.DeviceKey.Hw_Device_Certs_VD.c_str(), pHonor_callback) == 0, "校验DeviceCerts");
		break;
	}
	case U("CheckHardwareSize"):		//36	校验锁卡表HARDWARESIZE字段
	{
		CheckHardwareSize(paraData, retData, errData);
		break;
	}
	case U("CheckQfuseRegisterData"):	//37	校验锁卡表QFUSE_REGISTER_DATA字段的值，即熔丝标志位
	{
		CheckQfuseRegisterData(paraData, retData, errData);
		break;
	}
	case U("CheckRPMB"):				//38	校验RPMB：MTK平台校验锁卡表RSN字段
	{
		CheckRPMB(paraData, retData, errData);
		break;
	}
	case U("CheckFuseGid"):				//39	校验GID数据
	{
		if (StationData.customInfos.find("FUSE_GID") == this->StationData.customInfos.end()) {
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[FUSE_GID]配置，跳过当前测试。");
			break;
		}
		string FUSE_GID = StationData.customInfos["FUSE_GID"].Value;
		if (FUSE_GID.empty())
		{
			resultSetEx(false, "Error:FUSE_GID为空,检查锁卡表数据。");
			break;
		}
		BOE_CB_OUTLog_DefaultAndShowInfo("Try To Check FUSE_GID:" + FUSE_GID);
		resultSetFP(CheckFuseGid(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, FUSE_GID.c_str(), pHonor_callback) == 0, "检查FuseGid");
		break;
	}
	case U("CheckEmmcID"):				//40	校验EMMCID
	{
		if (StationData.customInfos.find("EMMC_ID") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[EMMC_ID]配置，跳过当前测试。");
			break;
		}

		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.EMMCID);
		if (lastResponseData.EMMCID.empty())
		{
			resultSetEx(false, "Error:MES返回的EMMCID值为空，检查MES。");
			break;
		}
		string strReadEmmcID;
		resultSetFP(ReadEMMCID(strReadEmmcID) == 0, "从DUT中读取EMMCID");
		if (!retBool) break;
		BOE_CB_OUTLog_Default("ReadEmmcID:" + strReadEmmcID);
		resultSetFP(strReadEmmcID == lastResponseData.EMMCID, "比较MES和DUT中的EmmcID数据");
		break;
	}
	case U("CheckPublicKey"):			//41	校验PUBLICKEY
	{
		if (StationData.customInfos.find("PUBLICKEY") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[PUBLICKEY]配置，跳过当前测试。");
			break;
		}
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.PUBLICKEY);
		if (lastResponseData.PUBLICKEY.empty())
		{
			resultSetEx(false, "Error:MES返回的PublicKey为空，检查MES.");
			break;
		}
		resultSetFP(VerifyPublicKey(CommonParam["DUTCom"].c_str(), lastResponseData.PUBLICKEY.c_str(), pHonor_callback) == 0, "校验PublicKey");
		break;
	}
	case U("CheckSecretType"):			//42	校验锁卡表SECRETTYPE字段
	{
		if (StationData.customInfos.find("SECRETTYPE") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SECRETTYPE]配置，跳过当前测试。");
			break;
		}
		string  SECRETTYPE = StationData.customInfos["SECRETTYPE"].Value;
		if (SECRETTYPE.empty())
		{
			resultSetEx(false, "Error:SECRETTYPE为空,检查锁卡表数据。");
			break;
		}
		resultSetFP(VerifySecretType(CommonParam["DUTCom"].c_str(), StationData.customInfos["SECRETTYPE"].Value.c_str(), pHonor_callback) == 0, "CheckSecretType");
		break;
	}
	case U("CheckFRPKey"):				//43	校验FRP_KEY
	{
		if (StationData.customInfos.find("FRP_KEY") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[FRP_KEY]配置，跳过当前测试。");
			break;
		}
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.FRP_KEY);
		if (lastResponseData.FRP_KEY.empty())
		{
			resultSetEx(false, "Error:MES返回的FRP_KEY为空，检查MES.");
			break;
		}
		resultSetFP(VerifyFrpKey(CommonParam["DUTCom"].c_str(), lastResponseData.FRP_KEY.c_str(), pHonor_callback) == 0, "校验FrpKey");
		break;
	}
	case U("CheckUserlock"):			//44	校验USERLOCK	LOCKTYPE
	{
		if (StationData.customInfos.find("LOCKTYPE") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[LOCKTYPE]配置，跳过当前测试。");
			break;
		}
		string LOCKTYPE = StationData.customInfos["LOCKTYPE"].Value;
		BOE_CB_OUTLog_DefaultAndShowInfo("Try To Check Userlock and LOCKTYPE:" + LOCKTYPE);
		// VERIFYCUSTOMIZATION_API int  VerifyUserLock(const char* addr, const char* lockType, void* callback);
		resultSetFP(VerifyUserLock(CommonParam["DUTCom"].c_str(), LOCKTYPE.c_str(), pHonor_callback) == 0, "校验UserLock(LOCKTYPE)");
		break;
	}
	case U("CheckAcclock"):				//45	校验ACCLOCK		NCK_DIAGUNLOCK
	{
		if (StationData.customInfos.find("NCK_DIAGUNLOCK") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[NCK_DIAGUNLOCK]配置，跳过当前测试。");
			break;
		}
		BOE_CB_OUTLog_Default("Target value:" + lastResponseData.NCK_DIAGUNLOCK);
		if (lastResponseData.NCK_DIAGUNLOCK.empty())
		{
			resultSetEx(false, "Error:MES返回的NCK_DIAGUNLOCK为空，检查MES.");
			break;
		}
		resultSetFP(VerifyAccLock(CommonParam["DUTCom"].c_str(), lastResponseData.NCK_DIAGUNLOCK.c_str(), pHonor_callback) == 0, "检查AccLock(NCK_DIAGUNLOCK)");
		break;
	}
	case U("CheckBatteryAntiFake"):     //47    电池防伪
	{
		char rsp[512]{ 0 };
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^BATTCTINFO=OFFICAL\r", "BATTCTINFO:\\s*OK", rsp, 512, pHonor_callback) == 0, "检查电池激活状态");
		if (!retBool)break;
		memset(rsp, 0, sizeof(rsp));
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^BDRTFUNC=SETTIMER,1,0\r", "BDRTFUNC:1,0\\s*OK", rsp, 512, pHonor_callback) == 0, "电池防伪");
		break;
	}
	case U("CheckKeyBox"):				//48	校验KeyBox
	{
		if (StationData.customInfos.find("SPECIAL_DATA_SWITCH") == this->StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SPECIAL_DATA_SWITCH]配置，跳过当前测试。");
			break;
		}
		string SPECIAL_DATA_SWITCH = StationData.customInfos["SPECIAL_DATA_SWITCH"].Value;
		if (!DataCalute((char*)SPECIAL_DATA_SWITCH.c_str(), 0))
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; SPECIAL_DATA_SWITCH[" + SPECIAL_DATA_SWITCH + "] Don't need to write value!");
			break;
		}

		// CRC校验
		string error = "";
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey CRC Check...");
		if (!WidevineKeyCRCCheck(lastResponseData.WidevineKey, error))
		{
			resultSetEx(false, "Error:" + error);
			break;
		}
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey CRC Check Pass.");

		// 数据解密
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey Data Decrypt...");
		string outDecryptData = "";
		//string error = "";
		int outLength = 0;
		if (!WidevineKeyDecryptData(lastResponseData.WidevineKey, outDecryptData, outLength, error))
		{
			resultSetEx(false, "Error:" + error);
			break;
		}
		BOE_CB_OUTLog_DefaultAndShowInfo("WidevineKey Data Decrypt Pass.");

		// 写入KeyBox
		BOE_CB_OUTLog_DefaultAndShowInfo("Write WidevineKey Data...");
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), string("AT^KEYBOXDATA=STORE," + outDecryptData + "\r").c_str(), "^KEYBOXDATA:1\\s*OK", nullptr, 0, pHonor_callback) == 0, "写入KeyBox");
		if (!retBool) break;

		// 校验KeyBox
		resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), string("AT^KEYBOXDATA=VERIFY," + outDecryptData + "\r").c_str(), "^KEYBOXDATA:1\\s*OK", nullptr, 0, pHonor_callback) == 0, "校验KeyBox");
		break;
	}
	case U("BackupNVandReset"):			//49	删除adb抓log脚本 设置LT标志位	回读校验LT标志位	恢复出厂设置
	{
		char rsp[512];
		int ret = RequestString(CommonParam["DUTCom"].c_str(), "AT^DELEXTLOGBAT\r", nullptr, rsp, 512, pHonor_callback);
		resultSetFP(ret == 0, "Send AT Command ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:删除adb抓log脚本失败！");
			break;
		}
		string retStr(rsp);
		resultSetFP(retStr.find("OK") != string::npos, "QualDelLogbat ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:删除adb抓log脚本失败！");
			break;
		}

		// 功能: Q平台特有逻辑，用于删除adb抓log脚本。脚本路径：/log/GetAdblog.bat
		// 返回: -1 表示失败，0 表示成功
		// CUSTOMIZATIONKEYACTION_API int  QualDelLogbat(const char* addr, void* callback);
		resultSet(QualDelLogbat(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0);
		if (!retBool) break;
		// 设置LT标志位
		resultSetFP(SetCWFlag(CommonParam["DUTCom"].c_str(), "LT P", pHonor_callback) == 0, "写入\"LT P\"标志位");
		if (!retBool) break;
		// 回读校验LT标志位
		resultSetFP(CheckCWFlag(CommonParam["DUTCom"].c_str(), "LT P", pHonor_callback) == 0, "校验\"LT P\"标志位");
		// 恢复出厂设置（需要兼容DEMO演示样机的场景）
		string Vendor = (StationData.customInfos.find("VENDOR") != StationData.customInfos.end()) ? StationData.customInfos["VENDOR"].Value : "";
		std::transform(Vendor.begin(), Vendor.end(), Vendor.begin(), ::toupper);
		if (Vendor == "DEMO")
		{
			BOE_CB_OUTLog_DefaultAndShowInfo("Warning:这是一台演示样机。");
			resultSetFP(FactoryResetForDemo(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "FactoryResetForDemo");
			break;
		}
		resultSetFP(FactoryReset(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "FactoryReset");
		break;
	}
	case U("NVCheck")://M4新增2 检查射频NV是否异常
	{
		resultSetFP(QualCheckNVStatus(CommonParam["DUTCom"].c_str(), 0, pHonor_callback) == 0, "QualCheckNVStatus");
		if (!retBool)break;
		break;
	}
	case U("CheckThemeColor")://M4新增3 主题颜色校验 不测试
	{
		break;
	}
	case U("CheckPhyno")://M4新增4 校验OEMinfo物理号信息
	{
		const PhyNumInfo* phyNumInfo;
		resultSetFP(QualCheckPhysicalNumber(CommonParam["DUTCom"].c_str(), phyNumInfo, pHonor_callback) == 0, "校验CheckPhyno");
		if (!retBool) break;
	}
	case U("CheckSimlock")://M4新增5 校验SIMLock信息
	{
		string strPassword;
		string strHash;
		if (StationData.customInfos.find("NCK_NCKNSCKSPCKRESET") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[NCK_NCKNSCKSPCKRESET]配置，Password默认nullptr。");
			strPassword = nullptr;
		}
		else
			strPassword = StationData.customInfos["NCK_NCKNSCKSPCKRESET"].Value;
		if (StationData.customInfos.find("INI_HASH") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[INI_HASH]配置，Hash默认nullptr。");
			strHash = nullptr;
		}
		else
			strHash = StationData.customInfos["INI_HASH"].Value;
		resultSetFP(MetkCheckSimlock(CommonParam["DUTCom"].c_str(), 0, nullptr, pHonor_callback) == 0, "CheckSimlock");
		if (!retBool) break;
		break;
	}
	case U("CheckSimcardMode")://M4新增6 校验单双卡模式
	{
		if (StationData.customInfos.find("SIMCARD_MODE") == StationData.customInfos.end())
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有[SIMCARD_MODE]配置，跳过当前测试。");
			break;
		}
		string SIMCARD_MODE = StationData.customInfos["SIMCARD_MODE"].Value;
		BOE_CB_OUTLog_Default("Try To Write SIMCARD_MODE(" + SIMCARD_MODE);
		resultSetFP(VerifySimcardMode(CommonParam["DUTCom"].c_str(), SIMCARD_MODE.c_str(), pHonor_callback) == 0, "校验VerifySimcardMode");
		if (!retBool) break;
		break;

	}
	case U("WriteSIMICCID")://M4新增7 读取并上传SIM_ICCID 不测试
	{
		break;
	}
	case U("CheckESIM")://M4新增8 校验ESim功能 不测试
	{
		break;
	}
	case U("CheckSecFlash")://M4新增9 校验安全芯片存储方案 不测试
	{
		break;
	}
	case U("CheckNfcInfo")://M4新增10 校验NFC信息擦除结果 不测试
	{
		break;
	}
	case U("CheckCPL")://M4新增11 校验CPL信息
	{
		break;
	}
	case U("CheckRKP")://M4新增12 校验RKP（谷歌证书新方案）
	{
		break;
	}
#ifdef OBA
	case U("ReadVendor"):				//      读取 VENDORCOUNTRY
	{
		BOE_CB_OUTLog_Default("Try to Read VENDORCOUNTRY");
		char rsp[512];
		int ret = RequestString(CommonParam["DUTCom"].c_str(), "AT^VENDORCOUNTRY?\r", nullptr, rsp, 512, pHonor_callback);
		resultSetFP(ret == 0, "Send AT Command(Read VENDORCOUNTRY) ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:发送读取 VENDORCOUNTRY 指令失败！");
			break;
		}
		string retStr(rsp);
		resultSetFP(retStr.find("OK") != string::npos, "Read VENDORCOUNTRY ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:读取 VENDORCOUNTRY 失败！");
			break;
		}
		string text = rsp;
		regex pattern("^\\^VENDORCOUNTRY:(.*),.*");
		smatch results;
		resultSetFP(regex_search(text, results, pattern), "regex_search vendor value ");
		if (!retBool)
		{
			BOE_CB_ShowInfo("Error:正则匹配获取 vendor value 失败！");
			break;
		}
		CustomInfo customInfo;
		customInfo.Name = "VENDOR";
		customInfo.Value = (*--results.end()).str();
		StationData.customInfos["VENDOR"] = customInfo;
		BOE_CB_OUTLog_Default("Vendor value is " + StationData.customInfos["VENDOR"].Value);
		BOE_CB_ShowInfo("Vendor value is " + StationData.customInfos["VENDOR"].Value);
		break;
	}
	case U("FactoryReset"):			//49	恢复出厂设置
	{
		// 读取vendor 判断手机是否为演示样机	
		string Vendor = (StationData.customInfos.find("VENDOR") != StationData.customInfos.end()) ? StationData.customInfos["VENDOR"].Value : "";
		std::transform(Vendor.begin(), Vendor.end(), Vendor.begin(), ::toupper);
		if (Vendor == "DEMO")
		{
			BOE_CB_OUTLog_DefaultAndShowInfo("Warning:这是一台演示样机。");
			resultSetFP(FactoryResetForDemo(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "FactoryResetForDemo");
			break;
		}
		resultSetFP(FactoryReset(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "FactoryReset");
		break;
	}
#endif // OBA

	case U("CheckFactoryResetFinished")://54	等待恢复出厂设置完成
	{
		resultSetFP(CheckFactoryResetFinished(CommonParam["DUTCom"].c_str(), StationData.timeOut, pHonor_callback) == 0, "等待恢复出厂设置完成");
		if (!retBool) break;

		//重新鉴权
		memset(dogInfoPtr->hun, 0, sizeof(dogInfoPtr->hun));
		memset(dogInfoPtr->outKeyID, 0, sizeof(dogInfoPtr->outKeyID));
		resultSetFP(Authenticate(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->hun,
			dogInfoPtr->size, dogInfoPtr->outKeyID, dogInfoPtr->keySize, pHonor_callback) == 0, "重新鉴权");
		break;
	}

	case U("EnableRetread"):			//55	重置翻新机并校验
	{
		// 功能: 重置翻新机方案，MC工位使用
		// 返回: -1 表示失败，0 表示成功
		// CUSTOMIZATIONKEYACTION_API int  EnableRetread(const char* addr, void* callback);
		resultSetFP(EnableRetread(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "重置翻新机并校验");
		break;
	}
	case U("RebootDut"):				//56	重启手机（DEMO演示样机不需要），重启后手机关机
	{
		string Vendor = (StationData.customInfos.find("VENDOR") != StationData.customInfos.end()) ? StationData.customInfos["VENDOR"].Value : "";
		std::transform(Vendor.begin(), Vendor.end(), Vendor.begin(), ::toupper);
		if (Vendor == "DEMO")
		{
			resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 演示样机MC不执行重启并关机操作。");
			break;
		}
		// 功能: 重启 DUT，MC工位最后使用。发送指令AT^TMODE=3，发完后MC测试结束。 DUT会重启开机在进入导航界面前自动关机，目的是在工厂执行首次开机，避免用户首次开机慢导致体验不好
		// 返回: -1 表示失败，0 表示成功
		// CUSTOMIZATIONKEYACTION_API int  RestartDevice(const char* addr, void* callback);
		resultSetFP(RestartDevice(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "RestartDevice");
		break;
	}
	case U("UploadInformation"):
	{
		//获取加密狗剩余时间
		long remainDays = GetNetDogRemainDays(dogInfoPtr->dog);
		if (remainDays < 30)
		{
			BOE_CB_OUTLog_Default("获取加密狗剩余时间：" + to_string(remainDays) + "天");
			resultSet(false, "获取加密狗剩余时间：" + to_string(remainDays) + "天");
			resultSet(true, "设置为true");
		}
		else
		{
			BOE_CB_OUTLog_Default("获取加密狗剩余时间：" + to_string(remainDays) + "天");
			BOE_CB_ShowInfo("获取加密狗剩余时间：" + to_string(remainDays) + "天");
		}
		// 上传到MES
		resultSetFP(MesPostPass(), "UploadInformation");
		isRetFalsePostMes = false;
		break;
	}
	default:
	{

		BOE_CB_OUTLog_Default("Error:" + TestMathed + " does not exit!");
		BOE_CB_ShowInfo("Error:" + TestMathed + " does not exit!");
		BOE_CB_MessageBoxData(TestMathed + " does not exit!");
		resultSet(false);
		break;
	}
	}

#endif // 0

#ifndef OBA //OBA站点错误不上传MES
	if (!retBool && isRetFalsePostMes) MesPostFail(Code, ErrorMsg);
#endif // !OBA

	return retBool;
}

BOE_CW::BOE_CW()
{


}

BOE_CW::~BOE_CW()
{

}

void BOE_CW::resultSetEx(bool ret, string mesg, string errCode)
{
	retBool = ret;
	subErrcode = errCode;
	BOE_CB_OUTLog_Default(mesg);
	BOE_CB_ShowInfo(mesg);
	if (retBool)
	{
		HelpSetData(*pRetData, T_RetSuccessData, mesg);
		HelpSetData(*pErrData, T_NoError, mesg);
	}
	else
	{
		HelpSetData(*pRetData, T_RetFailData, mesg);
		HelpSetData(*pErrData, T_Error, mesg);
		//BOE_CB_MessageBoxData(mesg,"Fail","Error");
		ErrorMsg = "[" + TestMathed + "]" + mesg + ErrorMsg;
	}
}

void BOE_CW::resultSet(bool ret, string something)
{
	retBool = ret;
	if (retBool)
	{
		HelpSetData(*pRetData, T_RetSuccessData, something + " Is Pass!");
		HelpSetData(*pErrData, T_NoError, something + " Is Pass!");
		BOE_CB_OUTLog_Default(something + " Is Pass!");
	}
	else
	{
		HelpSetData(*pRetData, T_RetFailData, something + " Is FAIL!");
		HelpSetData(*pErrData, T_Error, something + " Is FAIL!");
		BOE_CB_OUTLog_Default(something + " Is FAIL!");
		BOE_CB_ShowInfo("error:" + something);
	}
}

void BOE_CW::resultSetFP(bool ret, string something)
{
	resultSetEx(ret, something + (ret ? " Is Pass!" : " Is Fail!"));
}

void BOE_CW::resultSet(bool ret)
{
	resultSetEx(ret, TestMathed + string(ret ? " Is Pass!" : " Is Fail!"));
}

#pragma region hornor
bool BOE_CW::initParam()
{
	std::vector<std::string> sp;
	if (CommonParam.find("AppRootPath") != CommonParam.end())
	{
		sp = split(CommonParam["AppRootPath"], "\\");
	}
	if (sp.size() > 0 && (sp[sp.size() - 1] == "" || sp[sp.size() - 1].empty()))
	{
		sp = std::vector<std::string>(sp.begin(), sp.end() - 1);
	}

	INIParser iniParser;
	string iniFilePath = join(sp, "\\") + "\\Tool\\" + CommonParam["StationName"] + "\\BOE_" + CommonParam["StationName"] + ".ini";
	cout << __FUNCTION__ << "-->>" << "iniFilePath:" << iniFilePath;
	static mutex mutexParam;
	std::lock_guard<std::mutex> m(mutexParam);
	if (!iniParser.ReadINI(iniFilePath))
	{
		BOE_CB_OUTLog_Default("Ini Parse Fail! " + iniFilePath + "\r\n" + iniParser.lastError);
		BOE_CB_ShowInfo("Ini Parse Fail! " + iniFilePath + "\r\n" + iniParser.lastError);
		return false;
	}
	BOE_CB_OUTLog_Default("Ini Parse successed! " + iniFilePath);
	//system("pause");
	StationData.IsEncryptLog = iniParser.GetBool("StationConfig", "IsEncryptLog", true);
	StationData.IsCheckAppVersion = iniParser.GetBool("StationConfig", "IsCheckAppVersion", true);
	StationData.CheckScanCode = iniParser.GetBool("StationConfig", "CheckScanCode", true);

	StationData.BatteryLevelLimit = iniParser.GetInt("TestParam", "BatteryLevelLimit", 45);
	StationData.BatteryLevelUpLimit = iniParser.GetInt("TestParam", "BatteryLevelUpLimit", 100);

	StationData.IsPostFailToMes = iniParser.GetBool("StationConfig", "IsPostFailToMes", true);
	if (!StationData.IsPostFailToMes)
	{
		BOE_CB_MessageBoxData("当前FAIL不上传MES，请确认处于调试状态而非生产环境。", "Warning", "Warning");
}
#ifdef MC
	StationData.timeOut = iniParser.GetInt("TestParam", "TimeOut", 15);
#endif // MC

	// AppConfig 锁卡表 软件版本信息表 都在这里读取 需要增加从AppConfig中读取和UserName;//stationName可能不从这里读
	{
#ifndef OBA // !OBA

#pragma region local_CustomInfo
		if (StationData.CustomInfoFile != CommonParam["CustomInfoFile"])
		{
			BOE_CB_OUTLog_Default("Parse local customInfos by Excel:" + CommonParam["CustomInfoFile"]);
			try
			{
				StationData.customInfos.clear();
				//BOE_CB_MessageBoxData("读取excel:"+ StationData.CustomInfoFile);
				if (ParseCustomInfoXls(StationData.customInfos, CommonParam["CustomInfoFile"]))
				{
					if (StationData.customInfos.size() == 0) {
						BOE_CB_OUTLog_Default("Error:本地锁卡表解析不到内容，比对即将失败。请确保原文件未被修改。");
						BOE_CB_ShowInfo("Error:本地锁卡表解析不到内容，比对即将失败。请确保原文件未被修改。");

						BOE_CB_MessageBoxData("本地锁卡表解析不到内容，比对即将失败。请确保原文件未被修改。 file:" + CommonParam["CustomInfoFile"], "ParseCustomInfoXls", "Error");
						return false;
					}
				}
				else
				{
					BOE_CB_OUTLog_Default("Parse customInfos is Fail! ");
					BOE_CB_ShowInfo("Parse customInfos is Fail! ");
					BOE_CB_MessageBoxData("ParseCustomInfoXls is Fail! file:" + CommonParam["CustomInfoFile"], "ParseCustomInfoXls", "Error");
					return false;
				}
				if (StationData.customInfos.size() == 0)
				{
					resultSetEx(false, "Error:锁卡表解析不到实际内容，请检查！");
					return false;
				}

			}
			catch (const std::exception& e)
			{
				BOE_CB_MessageBoxData("ParseCustomInfoXls:" + string(e.what()) + " file:" + CommonParam["CustomInfoFile"], "ParseCustomInfoXls error", "Error");
				return false;
			}
			StationData.CustomInfoFile = CommonParam["CustomInfoFile"];
		}
#pragma endregion

#endif // !OBA
		// 解析软件版本信息表
		if (StationData.SoftwareVerFile != CommonParam["SoftwareVerFile"])
		{
			BOE_CB_OUTLog_Default("Parse local SoftwareVerInfo by Excel:" + CommonParam["SoftwareVerFile"]);
			try
			{
				StationData.softwareVerInfos.clear();
				if (ParseSoftwareVerXls(StationData.softwareVerInfos, CommonParam["SoftwareVerFile"]))
				{
					if (StationData.softwareVerInfos.size() == 0) {
						BOE_CB_OUTLog_Default("Error:本地软件版本信息表解析不到内容，比对即将失败。请确保原文件未被修改。");
						BOE_CB_ShowInfo("Error:本地软件版本信息表解析不到内容，比对即将失败。请确保原文件未被修改。");
						BOE_CB_MessageBoxData("本地软件版本信息表解析不到内容，比对即将失败。请确保原文件未被修改。 file:" + CommonParam["SoftwareVerFile"], "ParseCustomInfoXls", "Error");
						return false;
					}
				}
				else
				{
					BOE_CB_OUTLog_Default("Parse SoftwareVerInfo is Fail! File:" + CommonParam["SoftwareVerFile"]);
					BOE_CB_ShowInfo("Parse SoftwareVerInfo is Fail! File:" + CommonParam["SoftwareVerFile"]);
					return false;
				}
				if (StationData.softwareVerInfos.size() == 0)
				{
					resultSetEx(false, "Error:软件版本信息表解析不到实际内容，请检查！");
					return false;
				}
			}
			catch (const std::exception& e)
			{
				BOE_CB_MessageBoxData(e.what(), "ParseSoftwareVerXls error", "Error");
				return false;
			}
			StationData.SoftwareVerFile = CommonParam["SoftwareVerFile"];
		}

	}
	return true;
}

bool BOE_CW::TestDutAddr(string addr)
{
	auto fd = OpenDevice(addr.c_str(), pHonor_callback);
	if (fd)
	{
		BOE_CB_OUTLog_Default("Test OpenDevice OK.");
		BOE_CB_ShowInfo("Test OpenDevice OK.");
		CloseDevice(fd, pHonor_callback);
		BOE_CB_OUTLog_Default("CloseDevice.");
		BOE_CB_ShowInfo("CloseDevice.");
		return true;
	}
	BOE_CB_OUTLog_Default("OpenDevice Fail!");
	BOE_CB_ShowInfo("OpenDevice Fail!");
	return false;
}



void BOE_CW::Init(ParamData paraData, RetData& retData, ErrData& errData)
{
	dataParam = DataParam();
	BOE_CB_GetSN(this->dataParam.ScanCode);
	if (dataParam.ScanCode.empty())
	{
		resultSetEx(false, "扫码为空！");
		return;
	}
	BOE_CB_OUTLog_DefaultAndShowInfo(dataParam.ScanCode);
	// BOE_CB_OUTLog_Default(initFlag ? "true" : "false");
	// 解析参数	只需解析一次 解析成功后下次不再解析
	// 重置对象
	if (!initFlag)
	{
		resultSetFP(initParam(), "initParam ");
		if (!retBool) return;
	}
	BOE_CB_OUTLog_Default("PcName:" + CommonParam["PcName"]);
#ifndef OBA	
	// 输出锁卡表
	BOE_CB_OUTLog_Default(StationData.CustomInfoFile);
	for (auto& item : StationData.customInfos)
	{
		BOE_CB_OUTLog_Default(item.second.toString());
	}
#endif // !OBA
	// 输出软件版本信息表
	BOE_CB_OUTLog_Default(StationData.SoftwareVerFile);
	for (auto& item : StationData.softwareVerInfos)
	{
		BOE_CB_OUTLog_Default(item.second.toString());
	}
	if (!retBool) return;
	retBool = false;
	BOE_CB_OUTLog_Default("Has been init param?" + string(initFlag ? "yes" : "no"));
	auto hasPort = false;
	int count = 10;
	BOE_CB_OUTLog_Default("Wait For DUT Port(等待获取设备端口)...");
	while (!hasPort && count)
	{
		hasPort = TestDutAddr(CommonParam["DUTCom"]);
		count--;
	}
	resultSetFP(hasPort, "获取DUT端口");
	return;
}

void BOE_CW::Authentication(ParamData paraData, RetData& retData, ErrData& errData)
{
	//std::lock_guard<std::mutex> m(dogInfoPtr->dog_mutex);
	if (!ResetDog())
	{
		resultSetEx(false, "ResetDog Is Fail");
		BOE_CB_ShowInfo("Error:加密狗创建失败！");
		return;
	}
	memset(dogInfoPtr->hun, 0, sizeof(dogInfoPtr->hun));
	memset(dogInfoPtr->outKeyID, 0, sizeof(dogInfoPtr->outKeyID));
	resultSetFP(Authenticate(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->hun,
		dogInfoPtr->size, dogInfoPtr->outKeyID, dogInfoPtr->keySize, pHonor_callback) == 0, "Authenticate");
	if (retBool) time(&dogInfoPtr->time);// 更新加密狗最近一次使用的时间
	if (!retBool) BOE_CB_ShowInfo("Error:鉴权失败，检查DUT、PC、USB等状态。");
	return;
}

void BOE_CW::CheckBarcode(ParamData paraData, RetData& retData, ErrData& errData)
{
	BOE_CB_OUTLog_DefaultAndShowInfo("读取单板SN...");
	// 读取BarCode
	char buff[128]{ 0 };
	resultSetFP(ReadBarcode(CommonParam["DUTCom"].c_str(), buff, 128, pHonor_callback) == 0, "读取单板SN");
	if (!retBool) {
		BOE_CB_OUTLog_DefaultAndShowInfo("Error:读取单板SN失败");
		return;
	}
	string readBarcode(buff);
	BOE_CB_OUTLog_DefaultAndShowInfo("Read BSN:" + readBarcode + ".");
	BOE_CB_SN(buff);
	// MES请求
	retBool = false;
	string err = "";
	retBool = getMesDataAndCheck(readBarcode, err);
	if (!retBool) {
		resultSetEx(false, "Error:" + err);
		return;
	}

	retBool = false;
	resultSetFP(lastResponseData.Barcode == readBarcode, "MES_BSN[" + lastResponseData.Barcode + "]与 READ_BSN[" + readBarcode + "]比较");
	if (!retBool) {
		BOE_CB_ShowInfo("Error: MES的BSN和读取的BSN对比失败。");
		isRetFalsePostMes = false;
		BOE_CB_OUTLog_Default("单板条码核验不一致，不上传MES");
		return;
	}
	return;
}

void BOE_CW::CheckSoftwareVersion(ParamData paraData, RetData& retData, ErrData& errData)
{
	//功能：新的校验软件版本号方案，版本号校验要求所有从手机中读取的版本号都要校验；
			//参数  stationFlag 为入参，以字符串形式传入，取值为MC、CW，
			//参数  softVerInfo 为出参， Size 为其大小
			//返回：-1 表示失败， 0 表示成功
			//CUSTOMIZATIONKEYACTION_API int  ReadSoftwareVer(const char* addr, const char* stationFlag, char* softVerInfo, int size, void* callback);
	char buff[4096]{ 0 };
	string StationName = CommonParam["StationName"];
#ifdef CW
	StationName = "CW";
#else
	StationName = "MC";
#endif // DEBUG

	resultSetFP(ReadSoftwareVer(CommonParam["DUTCom"].c_str(), StationName.c_str(), buff, 4096, pHonor_callback) == 0, "ReadSoftwareVer ");
	if (!retBool) {
		BOE_CB_ShowInfo("Error: 从DUT读取软件版本信息失败。");
	}
	if (!retBool) return;

	string verInfoListStr = string(buff);
	BOE_CB_OUTLog_Default("ReadSoftwareVer OK! softVerInfo:\r\n" + verInfoListStr);
	// 解析DUT中软件版本
	unordered_map<string, string> DUTSoftwareVer;
	auto strList = split(verInfoListStr, "\r\n");
	for (auto str : strList)
	{
		//auto strVector = split(str, ":");
		if (str.empty()) continue;
		vector<string> strVector;
		strVector.push_back(str.substr(0, str.find(":")));
		strVector.push_back(str.substr(str.find(":") + 1));
		if (strVector.size() == 2)
		{
			DUTSoftwareVer[strVector[0]] = strVector[1];
		}
	}

	// 与本地信息表比较
	for (auto dutVersion : DUTSoftwareVer)
	{
		if (StationData.softwareVerInfos.find(dutVersion.first) == StationData.softwareVerInfos.end())//设备中的值在本地没有
		{
			resultSetEx(false, "Error:DUT中的软件版本信息与软件版本信息表中内容不一致，Excel文件中没有DUT的数据[" + dutVersion.first + ":" + dutVersion.second + "]");
			return;
		}
		else if (StationData.softwareVerInfos[dutVersion.first].ModuleInfo.compare(dutVersion.second) != 0)// 设备中的值与本地不一致
		{
			resultSetEx(false, "Error:Dut读取的数据与Excel中数据不一致.DUT[" + dutVersion.first + ":" + dutVersion.second + "] Excel[" + dutVersion.first + ":" + StationData.softwareVerInfos[dutVersion.first].ModuleInfo + "].");
			if (!retBool) {
				BOE_CB_ShowInfo("Error:对比软件版本信息表失败，请检查MES数据与本地所选Excel是否一致。当前设备软件版本信息在所选软件版本信息表中没有。");
			}
			return;
		}
	}
	BOE_CB_OUTLog_DefaultAndShowInfo("CheckSoftwareVersion Is Pass.");
	return;
}

void BOE_CW::CheckMaintenance(ParamData paraData, RetData& retData, ErrData& errData)
{
	if (dataParam.isDGSlaveServer)// 备板跳过非法维修和电量检查
	{
		resultSetEx(true, "[" + TestMathed + "] This Test Item is Skiped; 判定当前为服务备板，跳过当前测试。");
		return;
	}
	//功能：非法维修检测, 从手机读取关键器件列表, 比较读取的关键器件列表和数量是否与预期一致
	BOE_CB_OUTLog_Default("Target Value:MB|FCAM|RCAM");
	BOE_CB_ShowInfo("目标值关键器件: MB|FCAM|RCAM");
	char buff[2048]{ 0 };
	auto ret = ReadMaintenance(CommonParam["DUTCom"].c_str(), buff, 2048, pHonor_callback);
	// MB|FCAM|RCAM|TPLCD
	if (ret == 0)
	{
		string strTestItem = buff;

		//strTestItem.find("MB|FCAM|RCAM|TPLCD") != string::npos;

		auto strList = split(strTestItem, ":");
		if (strList.size() < 3) resultSetFP(false, "ReadMaintenance 返回值存在错误(返回结构不对)。" + strTestItem);
		BOE_CB_OUTLog_Default("ReadMaintenance:" + strList[2] + " Commpare:" + "MB|FCAM|RCAM");
		BOE_CB_ShowInfo("当前关键器件: " + strList[2]);
		resultSetFP(strList[2] == "MB|FCAM|RCAM", "Compare Maintenance（比对关键器件）");

		if (!retBool) return;

		//BOE_CB_OUTLog_Default("ReadMaintenance:" + string(buff) + " Commpare:" + dataParam.testItem);
		//if (dataParam.testItem != string(buff))
		//{
		//	BOE_CB_OUTLog_Default("关键器件列表比对失败!");
		//	BOE_CB_ShowInfo("关键器件列表比对失败!");
		//	resultSet(false);
		//	return;
		//}
	}
	else
	{
		BOE_CB_OUTLog_Default("ReadMaintenance Fail!");
		BOE_CB_ShowInfo("Error:读取关键器件失败!");
		resultSet(false);
		return;
	}
	resultSet(true);
}

void BOE_CW::EraseModem(ParamData paraData, RetData& retData, ErrData& errData)
{
	// 功能: Q平台特有逻辑，获取手机模式(0 返工模式，1 正常模式)
	// 参数  NRWFlag 为出参
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int  QualGetNRWFlag(const char* addr, int& NRWFlag, void* callback);
	int NRWFlag = 0;
	resultSetEx(QualGetNRWFlag(CommonParam["DUTCom"].c_str(), NRWFlag, pHonor_callback) == 0, "QualGetNRWFlag exec is successed!");
	if (!retBool) return;
	BOE_CB_OUTLog_Default("QualGetNRWFlag:" + std::to_string(NRWFlag) + (NRWFlag ? "正常模式" : "返工模式"));
	if (NRWFlag) return;/// 正常模式退出
	BOE_CB_OUTLog_Default("进入返工流程...");

	string headLog = "返工流程：";
	// 返工手机进行OEMINFO信息擦除
	// 功能: 擦除OEMINFO PhyNum信息，包含OEMINFO_IMEI2、OEMINFO_IMEI、OEMINFO_MEID、OEMINFO_ESN，CW/降级工位调用
	// 参数: void* dog libBaseSafedog.dll提供的网络加密狗接口返回的加密狗指针
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int  EraseOEMPhyNum(const char* addr, void* dog, int keyID, void* callback);
	resultSetFP(EraseOEMPhyNum(CommonParam["DUTCom"].c_str(), dogInfoPtr->dog, dogInfoPtr->outKeyID[2], pHonor_callback) == 0, headLog + " EraseOEMPhyNum ");
	if (!retBool) return;

	// 返工手机设置offline模式
	// 功能: Q平台特有逻辑，设置手机为offline模式并回读校验设置是否ok，返工流程中使用
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int  QualSetDutOffline(const char* addr, void* callback);
	resultSetFP(QualSetDutOffline(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, headLog + " QualSetDutOffline ");
	if (!retBool) return;

	// 返工手机清除modemst1, modemst2
	// 
	// 功能: Q平台特有逻辑，清除手机中运行态使用的NV数据（保存在modemst1 和modemst2分区中，指令发送完重启生效）
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int  QualEraseModem(const char* addr, void* callback);
	resultSetFP(QualEraseModem(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, headLog + " QualEraseModem ");
	if (!retBool) return;

	// 将返工手机设置模式为非返工模式（信息清除之后要设置成非返工模式，后面组件正常写入信息）
	// 
	// 功能: Q平台特有逻辑，设置手机为NRW模式(非返工模式，即正常模式)
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int  QualSetNRWFlag(const char* addr, void* callback);
	resultSetFP(QualSetNRWFlag(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, headLog + " QualSetNRWFlag ");
	if (!retBool) return;

	// 重启modem子系统（清除信息后需要重启Modem子系统）
	// 功能: Q平台特有逻辑，AP侧触发modem子系统重启（支持5.0 R上qcom产品）
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int  QualRebootModem(const char* addr, void* callback);
	resultSetFP(QualRebootModem(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, headLog + " QualRebootModem ");
	if (!retBool) return;

	// 等待15秒 不用线程等待了 H的接口中有相关函数
	// std::this_thread::sleep_for(std::chrono::milliseconds(15000));


	// 功能: Q/M平台通用，判断手机在timeout时间内是否完全启动
	// 参数: int timeout 判断手机完全启动的超时时间
	// 返回: -1 表示失败，0 表示成功
	resultSetFP(CheckBootState(CommonParam["DUTCom"].c_str(), 15, pHonor_callback) == 0, headLog + " CheckBootState ");
	if (!retBool) return;

	// 重新鉴权
	Authentication(paraData, retData, errData);
	if (!retBool) return;
	return;
}

void BOE_CW::CheckBatteryLevel(ParamData paraData, RetData& retData, ErrData& errData)
{
	if (dataParam.isDGSlaveServer)// 备板跳过非法维修和电量检查
	{
		resultSetEx(true, "[" + TestMathed + "] This Test Item is Skiped; 判定当前为服务备板，跳过当前测试。");
		return;
	}
	// 功能: 关闭自动充电
			// 返回: -1 表示失败，0 表示成功
			// CUSTOMIZATIONKEYACTION_API int StopAutoCharge(const char* addr, void* callback);
	auto ret = StopAutoCharge(CommonParam["DUTCom"].c_str(), pHonor_callback);
	if (ret != 0)
	{
		BOE_CB_ShowInfo("Error: 关闭自动充电失败。");
		resultSetEx(false, "StopAutoCharge Fail!");
		return;
	}
	BOE_CB_OUTLog_Default("StopAutoCharge OK!");

	//功能：读取电池电量
	//参数  value 为出参，表示读取到的电量值     
	//返回：-1 表示失败， 0 表示成功
	//CUSTOMIZATIONKEYACTION_API int  ReadBatteryPower(const char* addr, int& value, void* callback);
	int value = 0;
	ret = ReadBatteryPower(CommonParam["DUTCom"].c_str(), value, pHonor_callback);
	if (ret != 0)
	{
		ErrorMsg = "无法识别电量";
		BOE_CB_ShowInfo("Error: 无法识别电量。");
		resultSetEx(false, "ReadBatteryPower Fail!");
		return;
	}
	BOE_CB_OUTLog_Default("ReadBatteryPower:" + std::to_string(value) + " BatteryLevelLimit[" + std::to_string(StationData.BatteryLevelLimit) + "," + std::to_string(StationData.BatteryLevelUpLimit) + "].");
	BOE_CB_ShowInfo("ReadBatteryPower:" + std::to_string(value) + " BatteryLevelLimit[" + std::to_string(StationData.BatteryLevelLimit) + "," + std::to_string(StationData.BatteryLevelUpLimit) + "].");

	/// 检查电池电量
	if (value < StationData.BatteryLevelLimit)
	{
		ErrorMsg = "电量过低";
		BOE_CB_ShowInfo("Error: 电量过低，请进行充电。");
		resultSetEx(false, "Error:Out of limit.(low)");
		isRetFalsePostMes = false;
	}
	else if (value > StationData.BatteryLevelUpLimit)
	{
		ErrorMsg = "电量过高";
		BOE_CB_ShowInfo("Error: 电量过高，请先释放电量。");
		resultSetEx(false, "Error:Out of limit.(high)");
		isRetFalsePostMes = false;
	}
	else
	{
		resultSet(true);
	}
	// 功能: 开启自动充电
	// 返回: -1 表示失败，0 表示成功
	// CUSTOMIZATIONKEYACTION_API int StartAutoCharge(const char* addr, void* callback);
	ret = StartAutoCharge(CommonParam["DUTCom"].c_str(), pHonor_callback);
	if (ret != 0)
	{
		resultSetEx(false, "StartAutoCharge Fail!");
		BOE_CB_ShowInfo("Error: 开启自动充电失败。");
		return;
	}
	BOE_CB_OUTLog_Default("StartAutoCharge OK!");
	//resultSet(true);
}

void BOE_CW::CheckSubBoardFlag(ParamData paraData, RetData& retData, ErrData& errData)
{
	char rsp[512]{ 0 };
	resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^CONTROLBIT?\r", nullptr, rsp, 512, pHonor_callback) == 0, "读取背板标志位");
	if (!retBool) return;
	dataParam.isDGSlaveServer = std::regex_search(rsp, std::regex(".*TS463\\|P.*"));
	if (dataParam.isDGSlaveServer)
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("当前平板包含TS463|P标志位，判定为服务备板");
		dataParam.isDGSlaveServer = true;

		BOE_CB_OUTLog_DefaultAndShowInfo("检查MMIBB标志位...");
		char buff[512]{ 0 };
		resultSetFP(ReadMMIFlag(CommonParam["DUTCom"].c_str(), buff, 512, pHonor_callback) == 0, "读取MMI组合标志位");
		if (!retBool) return;
		string MMIFlagList = buff;
		BOE_CB_OUTLog_Default("MMIFlagList:" + MMIFlagList);
		int num = HexStrToInt(MMIFlagList);
		BOE_CB_OUTLog_Default("MMIFlagList To DEC:" + std::to_string(num));
		resultSetFP((num & 2048) == 2048, "检查MMIBB标志位");
		if (!retBool) isRetFalsePostMes = false;
	}
	else
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("当前平板不包含TS463|P标志位，判定为非服务备板");
	}
	return;

	// 读取MMI组合标志位 通过MMIBB标志位判断是否为服务备板
	BOE_CB_OUTLog_Default("使用MMIBB标志位判断是否为服务备板");
	char buff[512]{ 0 };
	resultSetFP(ReadMMIFlag(CommonParam["DUTCom"].c_str(), buff, 512, pHonor_callback) == 0, "读取MMI组合标志位");
	if (!retBool) return;
	string MMIFlagList = buff;
	BOE_CB_OUTLog_Default("MMIFlagList:" + MMIFlagList);
	int num = HexStrToInt(MMIFlagList);
	BOE_CB_OUTLog_Default("MMIFlagList To DEC:" + std::to_string(num));
	if ((num & 2054) > 2048) // 说明除了写入了MMIBB 还写入了MMIT或者MMIS标志，此时需要报错
	{
		resultSetEx(false, "Error:MMI标志位混乱，MMIBB不能与MMIT或MMIS同时存在");
		isRetFalsePostMes = false;
		if (!retBool) return;
	}
	if ((num & 2048) == 2048)
	{
		dataParam.isDGSlaveServer = true;
		BOE_CB_ShowInfo("Warning:请注意这是一个服务备板！");
		BOE_CB_OUTLog_Default("This DUT is a StandbyBoard");
	}
	else
	{
		dataParam.isDGSlaveServer = false;
		BOE_CB_ShowInfo("这不是一个服务备板！");
		BOE_CB_OUTLog_Default("This DUT is not a StandbyBoard");
	}
}

void BOE_CW::WriteCWFFlag(ParamData paraData, RetData& retData, ErrData& errData)
{
	// 写入CW F标志位
	BOE_CB_OUTLog_Default("Try To Write \"CW F\" Flag.");
	resultSetFP(SetCWFlag(CommonParam["DUTCom"].c_str(), "CW F", pHonor_callback) == 0, "Write \"CW F\" Flag");
	if (!retBool) return;
	BOE_CB_OUTLog_Default("Try To Check \"CW F\" Flag.");
	resultSetFP(CheckCWFlag(CommonParam["DUTCom"].c_str(), "CW F", pHonor_callback) == 0, "Check \"CW F\" Flag");
	if (!retBool) return;
	return;
}

void BOE_CW::CheckDevBootState(ParamData paraData, RetData& retData, ErrData& errData)
{
	//AT^DEVBOOTSTATE? 
	char rsp[512]{ 0 };
	resultSetFP(RequestString(CommonParam["DUTCom"].c_str(), "AT^DEVBOOTSTATE?\r", "1", rsp, 512, pHonor_callback) == 0, "DevBootState");
	return;
}

void BOE_CW::CheckHardwareSize(ParamData paraData, RetData& retData, ErrData& errData)
{
	if (StationData.customInfos.find("HARDWARESIZE") == this->StationData.customInfos.end())
	{
		resultSetEx(true, "[" + TestMathed + "] This Test Item is Skiped; 锁卡表没有HARDWARESIZE配置，跳过当前测试。");
		return;
	}
	string HARDWARESIZE = StationData.customInfos["HARDWARESIZE"].Value;
	//if(StationData.customInfos)
	// 把 若只有"\r"或者"\n"要换成"\r\n"
	if (HARDWARESIZE.find("\r") != string::npos && HARDWARESIZE.find("\r\n") == string::npos)
	{
		HARDWARESIZE = HARDWARESIZE.replace(HARDWARESIZE.find("\r"), 1, "\r\n");
	}
	else if (HARDWARESIZE.find("\n") != string::npos && HARDWARESIZE.find("\r\n") == string::npos)
	{
		HARDWARESIZE = HARDWARESIZE.replace(HARDWARESIZE.find("\n"), 1, "\r\n");
	}
	BOE_CB_OUTLog_Default("Target HardwareSize:\r\n" + HARDWARESIZE);
	BOE_CB_ShowInfo("Target HardwareSize:\r\n" + HARDWARESIZE);
	resultSetFP(VerifyHardwareSize(CommonParam["DUTCom"].c_str(), HARDWARESIZE.c_str(), pHonor_callback) == 0, "VerifyHardwareSize");
	if (!retBool) {
		BOE_CB_ShowInfo("Error:校验HardwareSize失败，检查锁卡表与当前DUT是否匹配。");
	}
}

void BOE_CW::CheckQfuseRegisterData(ParamData paraData, RetData& retData, ErrData& errData)
{
	if (StationData.customInfos.find("QFUSE_REGISTER_DATA") == this->StationData.customInfos.end())
	{
		resultSetEx(true, "[" + TestMathed + "] This Test Item is Skiped; 锁卡表没有QFUSE_REGISTER_DATA配置，跳过当前测试。");
		return;
	}
	string QFUSE_REGISTER_DATA = StationData.customInfos["QFUSE_REGISTER_DATA"].Value;
	BOE_CB_OUTLog_Default("QFUSE_REGISTER_DATA:" + QFUSE_REGISTER_DATA);
	if (QFUSE_REGISTER_DATA != "1")
	{
		resultSetEx(false, "锁卡表中QFUSE_REGISTER_DATA配置错误，该字段要么不配置配置的话则值为1。");
		return;
	}
	resultSetFP(VerifyQfuseRegisterData(CommonParam["DUTCom"].c_str(), QFUSE_REGISTER_DATA.c_str(), pHonor_callback) == 0, "VerifyQfuseRegisterData");
	if (!retBool) return;
	return;
}

void BOE_CW::CheckRPMB(ParamData paraData, RetData& retData, ErrData& errData)
{
	if (StationData.customInfos.find("RSN") == this->StationData.customInfos.end())
	{
		resultSetEx(true, "[" + TestMathed + "] This Test Item Is Skiped; 锁卡表没有RSN配置，跳过当前测试。");
		return;
	}
	string RSN = StationData.customInfos["RSN"].Value;
	BOE_CB_OUTLog_Default("RSN:" + RSN);
	if (RSN != "1")
	{
		resultSetEx(false, "锁卡表中RSN配置错误，该字段要么不配置配置的话则值为1。");
		return;
	}
	resultSetFP(VerifyRSN(CommonParam["DUTCom"].c_str(), pHonor_callback) == 0, "VerifyRSN");
	return;
}


int BOE_CW::ReadEMMCID(string& rspEMMCID)
{
	char rsp[512]{ 0 };
	int ret = RequestString(CommonParam["DUTCom"].c_str(), "AT^GETDEVINFO=EMMC\r", nullptr, rsp, 512, pHonor_callback);
	if (ret == -1)
	{
		BOE_CB_ShowInfo("Error: 读取EMMCID失败。");
		return ret;
	}
	string strRsp = rsp;
	auto vecStr = split(strRsp, ",");
	if (vecStr.size() > 3)
	{
		rspEMMCID = split(strRsp, ",")[3];
		for (size_t i = rspEMMCID.length(); i < 48; i++)
		{
			rspEMMCID += " ";
		}
	}
	else
	{
		BOE_CB_ShowInfo("Error: 读取EMMCID失败。");
		ret = -1;
	}
	return ret;
}

bool BOE_CW::WidevineKeyCRCCheck(const StructWidevineKey& widevineKey, string& error)
{
	if (widevineKey.WIDEVINEDRM_KEY.empty()) {
		error = "MES返回的WidevineKey.WIDEVINEDRM_KEY为空，检查MES.";
		return false;
	}
	std::vector<string> strList;
	for (size_t i = 0; i < widevineKey.WIDEVINEDRM_KEY.length() / 2; i++)
	{
		strList.push_back(widevineKey.WIDEVINEDRM_KEY.substr(i * 2, 2));
	}
	string strTest = join(strList, " ");

	auto calcullateKeyCRC = GetCRC16AndTransform(strTest);

	BOE_CB_ShowInfo("CalcullateKeyCRC = " + calcullateKeyCRC + " TargetCRC = " + widevineKey.WIDEVINE_KEY_CRC);
	BOE_CB_OUTLog_Default("CalcullateKeyCRC = " + calcullateKeyCRC + " TargetCRC = " + widevineKey.WIDEVINE_KEY_CRC);
	if (calcullateKeyCRC != widevineKey.WIDEVINE_KEY_CRC)
	{
		error = "CRC 检查失败！请检查MES中的WidevineKey数据。";
		return false;
	}
	return true;
}

bool BOE_CW::WidevineKeyDecryptData(const StructWidevineKey& widevineKeyStruct, string& outDecryptData, int& outlength, string& error)
{
	//std::lock_guard<std::mutex> guard(dogInfoPtr->dog_mutex);
	// 数据解密
	char decryptData[8192]{ 0 };
	long pulOutLen = 8192;
	{
		if (0 != SetCommandID(dogInfoPtr->dog, "0XEED60180000"))
		{
			error = "H客户接口SetCommandID返回错误。";
			isRetFalsePostMes = false;
			return false;
		}
		BOE_CB_OUTLog_Default("Try to DecryptData. Call RSA_PriDecryptData_Ext.");

		//char* pucIn = //dataParam.WIDEVINEDRM_KEY.length()

		string keyBoxData = "";
		for (size_t i = 0; i < lastResponseData.WidevineKey.WIDEVINEDRM_KEY.length(); i += 2)
		{
			if (i == lastResponseData.WidevineKey.WIDEVINEDRM_KEY.length() - 2)
				keyBoxData += lastResponseData.WidevineKey.WIDEVINEDRM_KEY.substr(i, 2);
			else
				keyBoxData += lastResponseData.WidevineKey.WIDEVINEDRM_KEY.substr(i, 2) + " ";
		}
		//unsigned char *pucIn = new unsigned char[8192]{ 0 };
		shared_ptr<unsigned char> punInptr(new unsigned char[8192] { 0 }, std::default_delete<unsigned char[]>());
		int ulInLen = Str2UnsignedChar(keyBoxData, punInptr.get());

		//BOE_CB_ShowInfo("byte len:" + std::to_string(ulInLen) + " byte:" + format("%s",pucIn));
		if (RSA_PriDecryptData_Ext(dogInfoPtr->dog, (char*)punInptr.get(), ulInLen, decryptData, &pulOutLen, dogInfoPtr->outKeyID[3]) != 0) {
			error = "H客户接口RSA_PriDecryptData_Ext返回错误。";
			isRetFalsePostMes = false;
			return false;
		}
		BOE_CB_OUTLog_Default("RSA_PriDecryptData_Ext rspl：" + std::to_string(pulOutLen) + " ret：" + string(decryptData));
		//BOE_CB_ShowInfo("RSA_PriDecryptData_Ext 返回的结果长度：" + std::to_string(pulOutLen) + " 内容：" + string(decryptData));
	}
	outDecryptData = decryptData;
	outlength = pulOutLen;
	return true;
}

bool BOE_CW::getMesDataAndCheck(string Barcode, string& err)
{
	BOE_CB_OUTLog_DefaultAndShowInfo("从MES请求数据...");
	bool ret = true;
	if (CommonParam["MesIsOnline"] != "true")
	{
		BOE_CB_OUTLog_Default("Mes Offline!");
		BOE_CB_MessageBoxData("Mes Offline!", "警告！", "Warning");
		return ret;
	}
	lastResponseData = ResponseData();
	ret = MesRequest(Barcode, lastResponseData);

	if (!ret)
	{
		err = "从MES请求数据失败:" + mes_last_error;
		isRetFalsePostMes = false;
		return ret;
	}
	BOE_CB_OUTLog_DefaultAndShowInfo("从MES请求数据完成。");
#pragma region Tool版本校验
	if (StationData.IsCheckAppVersion)
	{
		BOE_CB_ShowInfo("校验Tool版本...");
		BOE_CB_OUTLog_Default("校验Tool版本...");
		BOE_CB_ShowInfo("MES AppVersion : " + lastResponseData.APVersion + " Local AppVersion : " + CommonParam["AppVersion"]);
		BOE_CB_OUTLog_Default("MES AppVersion : " + lastResponseData.APVersion + " Local AppVersion : " + CommonParam["AppVersion"]);
		if (CommonParam["AppVersion"] != lastResponseData.APVersion)
		{
			err = "工具版本不一致。MES AppVersion:" + lastResponseData.APVersion + " Local AppVersion:" + CommonParam["AppVersion"] + "。请检查MES和本地工具版本。";
			ret = false;
			return false;
		}
	}
	else
	{
		BOE_CB_ShowInfo("Skip:跳过程序版本校验，请注意只允许测试环境使用。");
		BOE_CB_MessageBoxData("Skip:跳过程序版本校验，请注意只允许测试环境使用。");
	}
#pragma endregion
#pragma region 锁卡表校验
	BOE_CB_OUTLog_DefaultAndShowInfo("锁卡表校验...");
	//CW站校验本地锁卡表，MC站不校验本地锁卡表
	// 检查锁卡表

	// 去掉所卡表字段大小比对 比对宗旨：本地有的和MES必须一致，本地没有的MES必须为空
	// (1) 确保本地字段在MES上都有
	for (auto localData : StationData.customInfos)
	{
		if (lastResponseData.lockCardTableDto.find(localData.first) == lastResponseData.lockCardTableDto.end())// MES没有本地数据
		{
			err = "锁卡表不一致。MES上没有该锁卡表字段值[" + localData.first + ":" + localData.second.Value + "].";
			BOE_CB_OUTLog_DefaultAndShowInfo(err);
			ret = false;
			break;
		}
	}
	if (!ret)return ret;
	// (2) 在(1)的基础上确保本地数据与MES上一致，并且若是MES上数据多出来，必须为空 前期为空可以过，现在改成不一样不许过
	for (auto item : lastResponseData.lockCardTableDto) {
		if (StationData.customInfos.find(item.first) == StationData.customInfos.end())// 本地没有MES数据
		{
			err = "锁卡表不一致。本地没有该所卡表字段值" + item.first + ":\r\n" + item.second + "";
			ret = false;
			break;
		}
		else if (StationData.customInfos.find(item.first) != StationData.customInfos.end()
			&& (StationData.customInfos[item.first].Value.compare(item.second) != 0)) {// 本地和MES都有时，本地值和MES值不一致报错
			err = "锁卡表不一致。MES值" + item.first + ":\r\n" + item.second + "\r\n与本地值" + item.first + ":\r\n" + StationData.customInfos[item.first].Value + "\r\n不一致.";
			ret = false;
			break;
		}
	}
	if (!ret)return ret;
	BOE_CB_OUTLog_DefaultAndShowInfo("锁卡表校验通过.");
#pragma endregion 锁卡表校验
#pragma region 检查软件版本信息表
	BOE_CB_OUTLog_DefaultAndShowInfo("软件版本信息表校验...");
	if (lastResponseData.VersionList.size() == StationData.softwareVerInfos.size())
	{
		for (auto item : lastResponseData.VersionList)
		{
			if (StationData.softwareVerInfos.find(item.KeyName) == StationData.softwareVerInfos.end())
			{
				err = "软件版本信息表不一致。本地没有该字段值[" + item.KeyName + ":" + item.KeyValue + "].";
				ret = false;
				break;
			}
			if ((StationData.softwareVerInfos[item.KeyName].ModuleInfo.compare(item.KeyValue) != 0))// MES上有的key值和本地没有，或者本地的value与MES的值不一致
			{
				err = "软件版本信息表不一致。MES[" + item.KeyName + ":" + item.KeyValue + "]与本地[" + item.KeyName + ":" + StationData.softwareVerInfos[item.KeyName].ModuleInfo + "]的数据不一致";
				resultSetEx(false, "CheckSoftwareVersion is Fail. Error:Mes SoftwareVersionList[" + item.KeyName + ":" + item.KeyValue + "] is not the same as localdata[" + item.KeyName + ":" + StationData.softwareVerInfos[item.KeyName].ModuleInfo + "].");
				ret = false;
				break;
			}
		}
	}
	else
	{
		err = "软件版本信息表不一致。MES数据与本地数据的条目数目不一致。";
		ret = false;
	}
	if (!ret) return ret;
	BOE_CB_OUTLog_DefaultAndShowInfo("软件版本信息表校验通过.");
#pragma endregion



	if (StationData.CheckScanCode && ret)
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("整机SN校验...");
		BOE_CB_ShowInfo("ScanCode:" + dataParam.ScanCode + " Mes MSN:" + lastResponseData.MSN);
		BOE_CB_OUTLog_Default("ScanCode:" + dataParam.ScanCode + " Mes MSN:" + lastResponseData.MSN);
		if (dataParam.ScanCode != lastResponseData.MSN)
		{
			err = "扫码错误。扫码[" + dataParam.ScanCode + "]与MES下发数据[" + lastResponseData.MSN + "]不一致";
			isRetFalsePostMes = false;
			ret = false;
		}
		if (!ret) return ret;
		BOE_CB_OUTLog_DefaultAndShowInfo("整机SN校验通过.");
	}
	return ret;
}
bool BOE_CW::MesRequest(string Barcode, ResponseData& responseData)
{
	RequestData requestData;
	requestData.Barcode = Barcode;
	requestData.BarcodeType = "PSN";
	if (CommonParam.find("BarcodeType") != CommonParam.end())
	{
		requestData.BarcodeType = CommonParam["BarcodeType"];
	}
	if (CommonParam.find("BarcodeType") != CommonParam.end())
	{
		requestData.BarcodeType = CommonParam["BarcodeType"];
	}
	requestData.StationID = CommonParam["StationName"];
	if (CommonParam.find("TaskOrder") != CommonParam.end())
	{
		requestData.TaskOrder = CommonParam["TaskOrder"];
	}
	if (CommonParam.find("FactoryCode") != CommonParam.end())
	{
		requestData.FactoryCode = CommonParam["FactoryCode"];
	}
	if (CommonParam.find("VersionListType") != CommonParam.end())
	{
		requestData.VersionListType = CommonParam["VersionListType"];
	}
	else
	{
		requestData.VersionListType = CommonParam["StationName"];
	}
	if (CommonParam.find("Operator") != CommonParam.end())
	{
		requestData.UserName = CommonParam["Operator"];
	}
	if (CommonParam.find("LineName") != CommonParam.end())
	{
		requestData.Line = CommonParam["LineName"];
	}
	return MesRequest(requestData, responseData);
}
mutex mutexMes;
bool BOE_CW::MesRequest(RequestData requestData, ResponseData& responseData)
{
	ajson::string_stream ss;
	ajson::save_to(ss, requestData);
	string req = ss.str();
	BOE_CB_OUTLog_Default("MES请求:\r\n" + req);
	shared_ptr<char> retPtr(new char[8192 * 4] { 0 }, std::default_delete<char[]>());
	shared_ptr<char> errPtr(new char[8192 * 4] { 0 }, std::default_delete<char[]>());
	mes_last_error = "";
	std::lock_guard<std::mutex> m(mutexMes);
	bool retBL = BOE_Common_Request((char*)req.c_str(), retPtr.get(), errPtr.get());
	std::cout << __FUNCTION__ << "-->>" << retPtr.get();
	// 设置对应参数
	if (retBL)
	{
		auto retStrig = string_To_UTF8(string(retPtr.get()));
		BOE_CB_OUTLog_Default("MES回复:\r\n" + retStrig);
		try
		{
			ajson::load_from_buff(responseData, retStrig.c_str(), strlen(retPtr.get()));
		}
		catch (const std::exception& e)
		{
			BOE_CB_MessageBoxData("解析MES回复值错误:\r\n" + string(e.what()), "Error", "Error");
			retBL = false;
		}
		ajson::string_stream ss;
		ajson::save_to(ss, responseData);
		string rsp = ss.str();
		BOE_CB_OUTLog_Default("解析重生成Json:\r\n" + rsp);
	}
	else
	{
		mes_last_error = string_To_UTF8(string(errPtr.get()));
		BOE_CB_OUTLog_Default("MES返回Error:\r\n" + mes_last_error);
		BOE_CB_ShowInfo("MES返回Error:\r\n" + mes_last_error);
	}
	return retBL;
}

bool BOE_CW::MesPostPass()
{
	PostData postData;
#ifndef OBA
	postData.Barcode = lastResponseData.Barcode;
	postData.StationID = CommonParam["StationName"];
	postData.BarcodeType = "PSN";
	if (CommonParam.find("BarcodeType") != CommonParam.end())
	{
		postData.BarcodeType = CommonParam["BarcodeType"];
	}
	postData.Line = CommonParam["LineName"];
	postData.UserName = CommonParam["Operator"];
	postData.PcName = CommonParam["PcName"];
	postData.Fixture = CommonParam["FixtureID"];
	postData.AteName = "";
	postData.Result = "OK";
	postData.BugCode = "";
	postData.ErrorMsg = "";
	// PASS
#ifdef CW // CW站点要上传的数据
	postData.EMMCID = dataParam.EMMC_ID;
	postData.UDID = dataParam.UDID;
	postData.PUBLICKEY = dataParam.PublicKey;
	postData.NCK_DIAGUNLOCK = dataParam.NCK_DIAGUNLOCK;
	postData.NCK_NCKNSCKSPCKRESET = "";
	postData.FRP_KEY = dataParam.FRP_KEY;

	postData.RKP_DATA_1 = dataParam.RKP_DATA_1;
	postData.RKP_DATA_2 = dataParam.RKP_DATA_2;
	postData.RKP_DATA_VD = dataParam.RKP_DATA_VD;
#endif // CW
#endif // !OBA
#ifdef OBA
	postData.Barcode = this->dataParam.ScanCode;
	postData.BarcodeType = "PSN";
	if (CommonParam.find("BarcodeType") != CommonParam.end())
	{
		postData.BarcodeType = CommonParam["BarcodeType"];
	}
	postData.TaskOrder = "";
	if (CommonParam.find("TaskOrder") != CommonParam.end())
	{
		postData.BarcodeType = CommonParam["TaskOrder"];
	}
	postData.UserName = CommonParam["Operator"];
	postData.PCName = CommonParam["PcName"];
	postData.StationID = CommonParam["StationName"];
	if (CommonParam.find("FactoryCode") != CommonParam.end())
	{
		postData.FactoryCode = CommonParam["FactoryCode"];
	}
#endif // OBA


	return MesPost(postData);
}

bool BOE_CW::MesPostFail(string BugCode, string ErrorMsg)
{
	PostData postData;
#ifndef OBA
	postData.AteName = "";
	postData.Barcode = lastResponseData.Barcode;
	postData.BarcodeType = "PSN";
	if (CommonParam.find("BarcodeType") != CommonParam.end())
	{
		postData.BarcodeType = CommonParam["BarcodeType"];
	}
	postData.Line = CommonParam["LineName"];
	postData.UserName = CommonParam["Operator"];
	postData.PcName = CommonParam["PcName"];
	postData.Fixture = CommonParam["FixtureID"];
	postData.Result = "NG";
	postData.BugCode = BugCode;
	postData.ErrorMsg = ErrorMsg;
	postData.StationID = CommonParam["StationName"];
	// FAIL
#endif // !OBA
#ifdef OBA
	return false;// OBA不上传错误
	postData.Barcode = this->dataParam.ScanCode;
	postData.BarcodeType = "PSN";
	if (CommonParam.find("BarcodeType") != CommonParam.end())
	{
		postData.BarcodeType = CommonParam["BarcodeType"];
	}
	postData.TaskOrder = "";
	if (CommonParam.find("TaskOrder") != CommonParam.end())
	{
		postData.BarcodeType = CommonParam["TaskOrder"];
	}
	postData.UserName = CommonParam["Operator"];
	postData.PCName = CommonParam["PcName"];
	postData.StationID = CommonParam["StationName"];
	if (CommonParam.find("FactoryCode") != CommonParam.end())
	{
		postData.FactoryCode = CommonParam["FactoryCode"];
	}
#endif // OBA
	// FAIL

	return MesPost(postData);
}

bool BOE_CW::MesPost(PostData postData)
{
#ifdef OBA	// OBA使用整机SN，打印的背贴条码进行上传MES;
	postData.Barcode = this->dataParam.ScanCode;
#endif // OBA

	ajson::string_stream ss;
	ajson::save_to(ss, postData);
	string post = ss.str();
	BOE_CB_OUTLog_Default("mes post:" + string_To_UTF8(unicodeToCHI(post)));
	mes_last_error = "";
	if (CommonParam["MesIsOnline"] != "true")
	{
		if (postData.Result == "NG")
		{
			BOE_CB_OUTLog_DefaultAndShowInfo("MES离线SKIP : NG 离线未上传MES!");
			return true;
		}
		else {
			BOE_CB_OUTLog_DefaultAndShowInfo("MES离线SKIP : OK 离线未上传MES!");
			return true;
		}
	}
	if (!StationData.IsPostFailToMes && postData.Result == "NG")
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("MES SKIP : NG 测试环境Fail 不上传MES!");
		return true;
	}
	if (CommonParam.find("TestModel") != CommonParam.end() && CommonParam["TestModel"] == "StressTesting")
	{
		BOE_CB_OUTLog_DefaultAndShowInfo("Warning:压测模式，不进行NG和OK上传，程序直接返回。");
		return true;
	}
	shared_ptr<char> retPtr(new char[8192 * 4] { 0 }, std::default_delete<char[]>());
	shared_ptr<char> errPtr(new char[8192 * 4] { 0 }, std::default_delete<char[]>());

	retBool = BOE_Common_Post((char*)post.c_str(), retPtr.get(), errPtr.get());

	// 设置对应参数
	if (!retBool)
	{
		mes_last_error = string_To_UTF8(string(errPtr.get()));
		BOE_CB_OUTLog_Default("Mes post error:" + mes_last_error);
		BOE_CB_ShowInfo("Mes post error:" + mes_last_error);
	}
	else
	{
		string retStr = string_To_UTF8(string(retPtr.get()));
		BOE_CB_OUTLog_Default("Mes post ret:" + retStr);
	}
	return retBool;
}

#pragma endregion hornor

#pragma region BOE_CB
void BOE_CW::BOE_Callback(CallbackData callbackData)
{
	//cout << __FUNCTION__ << endl;
	if (this->callBackObj == nullptr)
	{
		return;
	}
	else
	{
		return this->callBackObj->BOE_CallbackFunctin(callbackData);
	}
}

void BOE_CW::BOE_Callback(int dataType, string str)
{
	CallbackData callbackData;
	callbackData.boeDataTypeID = dataType;
	callbackData.boeData = std::shared_ptr<char>(new char[str.length() + 1] { 0 }, std::default_delete<char[]>());
	strcpy((char*)callbackData.boeData.get(), str.c_str());
	((char*)(callbackData.boeData.get()))[str.length()] = '\0';
	BOE_Callback(callbackData);
}

void BOE_CW::BOE_CB_ShowInfo(string info)
{
	constexpr auto T_ShowTestInfo = 9;
	BOE_Callback(T_ShowTestInfo, info);
}

void BOE_CW::BOE_CB_OUTLog(string str)
{
	//cout << __FUNCTION__ << ":" << str << endl;
	BOE_Callback(T_LogData, str);
}

void BOE_CW::BOE_CB_OUTLog_Default(string str)
{
	cout << __FUNCTION__ << ":" << UTF8_To_string(str) << endl;
	if (this->StationData.IsEncryptLog)
	{
		BOE_CB_OUTLog("Default-Encrypt:" + encryptStr_ECB_AES("BOE_TSD_TC823_2023", str));
	}
	else
	{
		BOE_CB_OUTLog("Default-" + str);
	}
}

void BOE_CW::BOE_CB_OUTLog_DefaultAndShowInfo(string str)
{
	BOE_CB_OUTLog_Default(str);
	BOE_CB_ShowInfo(str);
}

void BOE_CW::BOE_CB_OUTLog_Command(string str)
{
	BOE_CB_OUTLog("Command-" + str);
}

void BOE_CW::BOE_CB_OUTLog_Operation(string str)
{
	BOE_CB_OUTLog("Operation-" + str);
}

void BOE_CW::BOE_CB_Warning(string str)
{
	BOE_Callback(T_WarningData, str);
}

void BOE_CW::BOE_CB_Error(string str)
{
	BOE_Callback(T_ErrorData, str);
}

void BOE_CW::BOE_CB_MessageBoxData(string content, string title, string level)
{
	nlohmann::json j{
		{ "Title", title},
		{ "Level", level },
		{ "Content", content }
	};
	BOE_Callback(T_MessgeBoxData, j.dump());
}

void BOE_CW::BOE_CB_SN(string SN)
{
	BOE_Callback(T_SN, SN);
}

bool BOE_CW::BOE_CB_GetSN(string& SN)
{
	SN = "";
	constexpr auto T_GETSN = 2001;
	CallbackData callbackData;
	callbackData.boeDataTypeID = T_GETSN;
	callbackData.boeData = std::shared_ptr<char>(new char[1024] { 0 }, std::default_delete<char[]>());
	BOE_Callback(callbackData);
	string value = (char*)callbackData.boeData.get();
	if (value.find("error") != string::npos)
	{
		return false;
	}
	else
	{
		SN = value;
	}
	return true;
}
#pragma endregion BOE_CB

bool BOE_CW::ResetDog()
{
	time_t currentTime;
	time(&currentTime);
	if (difftime(currentTime, dogInfoPtr->time) < (1.5 * 60 * 60) && dogInfoPtr->dog != nullptr)// 判定为超时
	{
		return true;
	}

	assert(handleLibBaseSafedog != nullptr);
	// 重置加密狗
	if (dogInfoPtr->dog != nullptr)
	{
		BOE_CB_OUTLog_Default("DestroySafeDog");
		DestroySafeDog(dogInfoPtr->dog);
		dogInfoPtr->dog = nullptr;
	}
	string key = "";
	fstream ofs;
	string dogFileName = "SafeDog.dat";
	if (CommonParam.find("FactoryCode") != CommonParam.end()) dogFileName = "SafeDog_" + CommonParam["FactoryCode"] + ".dat";
	if (!ifstream(dogFileName).good())
	{
		BOE_CB_MessageBoxData("加密信息文件[" + dogFileName + "]丢失，请重新配置相关加密狗信息。");
		return false;
	}
	ofs.open(dogFileName, ios::in);
	string encryptStr;
	ofs >> encryptStr;
	ofs.close();
	SafeDogLoginInfo safeDogLoginInfo;
	ajson::load_from_buff(safeDogLoginInfo, decryptStr_ECB_AES(key, encryptStr).c_str());
	string SafeDog_UserName = safeDogLoginInfo.UserName, SafeDog_Password = safeDogLoginInfo.Password;
	if (SafeDog_UserName.empty() || SafeDog_Password.empty())
	{
		BOE_CB_MessageBoxData("加密狗账号信息为空，请查验加密狗设置。");
		return false;
	}

	//std::cout << "输出加密狗UserName：" << safeDogLoginInfo.UserName << endl;
	//std::cout << "输出加密狗Password：" << safeDogLoginInfo.Password << endl;

	//static string DBG_SafeDog_UserName = "CM6RAteManager1111";
	//static string DBG_SafeDog_Password = "6f2435bbT(7";
	//static string BOE_SafeDog_UserName = "CMUNATEUSER22";
	//static string BOE_SafeDog_Password = "41071a00K!9";
	//if (CommonParam.find("Factory") != CommonParam.end())
	//{
	//	if (CommonParam["Factory"] == "BOE")
	//	{
	//		SafeDog_UserName = BOE_SafeDog_UserName;
	//		SafeDog_Password = BOE_SafeDog_Password;
	//	}
	//	else if (CommonParam["Factory"] == "DBG")
	//	{
	//		SafeDog_UserName = DBG_SafeDog_UserName;
	//		SafeDog_Password = DBG_SafeDog_Password;
	//	}
	//	else
	//	{
	//		this->ErrorMsg = "未能得到工厂[" + CommonParam["Factory"] + "]的加密狗信息！";
	//		BOE_CB_MessageBoxData("未能得到工厂["+ CommonParam["Factory"] +"]的加密狗信息！");
	//		BOE_CB_OUTLog_Default("未能得到工厂[" + CommonParam["Factory"] + "]的加密狗信息！");
	//		return false;
	//	}

	//	BOE_CB_OUTLog_Default("使用[" + CommonParam["Factory"] + "]的加密狗信息！");
	//}
	//else
	//{

	//	BOE_CB_OUTLog_Default("使用默认BOE加密狗信息！");
	//	SafeDog_UserName = BOE_SafeDog_UserName;
	//	SafeDog_Password = BOE_SafeDog_Password;
	//}

	// 创建加密狗 
	char token[2048] = "";
	dogInfoPtr->dog = CreateSafeDog(pHonor_callback);
	if (dogInfoPtr->dog != nullptr) {
		//cout << "dog is not null" << endl;


		if (GetNetDogToken(SafeDog_UserName.c_str(), SafeDog_Password.c_str(),
			"http://atetoken.pki.hihonor.com/api/ATECenterToken/GenerateToken",
			token, 2048, pHonor_callback) != 0) {
			BOE_CB_OUTLog_Default("GetNetDogToken Fail!");
			BOE_CB_ShowInfo("GetNetDogToken Fail!");
			return false;
		}
		else
		{
			BOE_CB_OUTLog_Default("GetNetDogToken Pass!");
		}

		if (InitNetDogPara(dogInfoPtr->dog, SafeDog_UserName.c_str(), token,
			"http://dongle.pki.hihonor.com:80/cdic/services/encryption/center", "ATE", true) != 0) {
			BOE_CB_OUTLog_Default("InitNetDogPara Fail!");
			return false;
		}
		else
		{
			BOE_CB_OUTLog_Default("InitNetDogPara Pass!");
		}
	}
	else
	{
		BOE_CB_OUTLog_Default("CreateSafeDog Fail!");
		return false;
	}
	time(&dogInfoPtr->time);
	return true;
}

string BOE_CW::getConfigJson() {
	//string ret;
	//ret = "{\n    \"TestMathed\": \""+ TestMathed +"\"\n}\n";
	ajson::string_stream ss;
	ajson::save_to(ss, *this);
	return ss.str();
}

bool BOE_CW::setConfigJson(string value)
{
	if (value.empty()) return true;

	// 设置测试方法
	nlohmann::json js = nlohmann::json::parse(value, nullptr, false);
	if (js.is_discarded())
	{
		return false;
	}
	if (js.contains("TestMathed"))
	{
		this->TestMathed = js["TestMathed"].get<string>();
	}
	else
	{
		if ((*js.begin()).contains("TestMathed"))
		{
			this->TestMathed = (*js.begin())["TestMathed"].get<string>();
		}
	}

	// 设置对应参数
	ajson::load_from_buff(*this, value.c_str());

	//PramaInterface paramInterface;
	//ajson::load_from_buff(paramInterface, value.c_str());
	//this->TestMathed = paramInterface.TestMathed;
	//BOE_CB_MessgeBoxData("****** SetConfigJson " + value+" findRet "+std::to_string( findRet)+" "+ std::to_string(value.find(",", findRet)));
	return true;
}

int BOE_CW::VerifySN(const char* addr, const char* val, void* callback)
{
	int size = 256;
	char* data = new char[size] {0};
	auto ret = ReadSN(addr, data, size, callback);
	BOE_CB_OUTLog_Default("ReadSN Ret:" + std::to_string(ret));
	if (ret == 0)
	{
		if (string(val) == string(data))
		{
			ret = 0;
		}
		else
		{
			ret = -1;
		}
	}
	delete[]data;
	return ret;
}

int BOE_CW::VerifyUDID(const char* addr, const char* val, void* callback)
{
	int size = 256;
	char* buff = new char[size] {0};
	auto ret = ReadUDID(addr, buff, size, callback);
	BOE_CB_OUTLog_Default("ReadUDID Ret:" + std::to_string(ret));
	if (ret == 0)
	{
		if (string(val) == string(buff))
		{
			ret = 0;
		}
		else
		{
			ret = -1;
		}
	}
	delete[]buff;
	return ret;

	return 0;
}

TestDllInterface* NewTestDllInstance()
{
	return new BOE_CW();
}