#pragma once
#include <string>
#include <mutex>

#ifdef BOEMES_EXPORT
#define BOEMES_API __declspec(dllexport)
#else
#define BOEMES_API __declspec(dllimport)
#endif

class BOEMES_API BOE_MES
{
public:
	BOE_MES();
	~BOE_MES();

private:

};


#ifdef __cplusplus 
extern "C" {
#endif // _cplusplus
	/// <summary>
	///  向MES请求数据
	/// </summary>
	/// <param name="reqJson"></param>
	/// <param name="retJson"></param>
	/// <param name="strErr"></param>
	/// <returns></returns>
	BOEMES_API bool BOE_Common_Request(char* reqJson, char* retJson, char* strErr);
	/// <summary>
	/// MES过站 向MES提交数据
	/// </summary>
	/// <param name="subJson"></param>
	/// <param name="strErr"></param>
	/// <returns></returns>
	BOEMES_API bool BOE_Common_Post(char* subJson, char* retJson, char* strErr);
	//BOECWH_API TestDllInterface* NewTestDllInstance();//BOECWH_API

	/// <summary>
	/// 向MES上传数据，不过站
	/// </summary>
	/// <param name="reqJson"></param>
	/// <param name="retJson"></param>
	/// <param name="strErr"></param>
	/// <returns></returns>
	BOEMES_API bool BOE_Common_Upload(char* subJson, char* retJson, char* strErr);
	/// <summary>
	/// 单独从MES下载数据
	/// </summary>
	/// <param name="subJson"></param>
	/// <param name="retJson"></param>
	/// <param name="strErr"></param>
	/// <returns></returns>
	BOEMES_API bool BOE_Common_Download(char* reqJson, char* retJson, char* strErr);
#ifdef __cplusplus 
}
#endif // _cplusplus