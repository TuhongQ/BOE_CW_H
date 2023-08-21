#include "pch.h"


#include "BOE_MES.h"

#include "pch.h"


#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <iostream>

using namespace System;
using namespace System::Runtime::InteropServices;

BOE_MES::BOE_MES()
{
}

BOE_MES::~BOE_MES()
{
}

//gcroot<IMSDLL::MESFUNCTION^> MES = gcnew IMSDLL::MESFUNCTION();

bool BOE_Common_Request(char* reqJson, char* retJson, char* strErr)
{
	String^ req = gcnew String(reqJson);
	String^ ret = gcnew String("");
	String^ err = gcnew String("");
	//IMSDLL::MESFUNCTION^ MES = gcnew IMSDLL::MESFUNCTION();
	BOE::MesInterface::MESFUNCTION^ MES = gcnew BOE::MesInterface::MESFUNCTION();
	auto retBool = MES->BOE_Data_In(req, ret, err);
	if (retBool) {
		//System::Console::WriteLine("BOE_Common_Request ret:" + ret);
		auto stdString = msclr::interop::marshal_as<std::string>(ret);
		strcpy_s(retJson, stdString.length()+1, stdString.c_str());
		//strcpy(retJson, stdString.c_str());
		//std::cout <<__FUNCTION__<<"-->>retJson:" << retJson;
	}
	else {
		//System::Console::WriteLine("BOE_Common_Request err:" + err);
		auto stdString = msclr::interop::marshal_as<std::string>(err);
		strcpy_s(strErr, stdString.length()+1, stdString.c_str());
		/*strcpy(strErr, stdString.c_str());*/
	}
	return retBool;
}

bool BOE_Common_Post(char* subJson, char* retJson, char* strErr)
{
	//std::string subJsonCPP = subJson;
	//subJsonCPP = std::regex_replace(subJsonCPP, std::regex("\r"), "\\u000d");
	//subJsonCPP = std::regex_replace(subJsonCPP, std::regex("\n"), "\\u000a");
	//subJsonCPP = std::regex_replace(subJsonCPP, std::regex("\r\n"), "\\u000d\\u000a");
	//String^ sub = gcnew String(subJsonCPP.c_str());
	String^ sub = gcnew String(subJson);
	sub = System::Text::RegularExpressions::Regex::Unescape(sub);
	String^ ret = gcnew String("");
	String^ err = gcnew String("");
	BOE::MesInterface::MESFUNCTION^ MES = gcnew BOE::MesInterface::MESFUNCTION();
	bool retBool = false;
	//sub = sub->Replace("\r", "\\u000d");
	//sub = sub->Replace("\n", "\\u000a");
	if (sub->Contains("\"StationID\":\"OBA\"")) // OBAӿ
	{
		retBool = MES->BOE_OBA(sub, err);
	}
	else
	{
		retBool = MES->BOE_Data_Out(sub, err);
	}
	if (retBool) {
		auto stdString = msclr::interop::marshal_as<std::string>(ret);
		strcpy_s(retJson, stdString.length() + 1, stdString.c_str());
	}
	else {
		auto stdString = msclr::interop::marshal_as<std::string>(err);
		strcpy_s(strErr, stdString.length() + 1, stdString.c_str());
	}
	return retBool;
}

