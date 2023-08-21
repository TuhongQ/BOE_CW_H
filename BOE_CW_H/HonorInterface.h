#pragma once
#include <string>
#include <mutex>
#include "../inc/BaseShowInformationDefine.h"
#include "../inc/MetkPhysicalNumberDefine.h"
#include <map>
#include <unordered_map>
#include <list>
#include <vector>

class HonorInterface
{
};

class CallbackParamObjSet
{

private:
	static std::mutex& getMutex()
	{
		static std::mutex mutex;
		return mutex;
	}

public:
	static CallbackParam* getCallbackParamObj(std::string key)
	{
		std::lock_guard<std::mutex> guard(getMutex());
		static std::map<std::string, CallbackParam> mapCallbackParam;
		if (mapCallbackParam.find(key) == mapCallbackParam.end())
		{
			mapCallbackParam[key] = CallbackParam{ nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr ,nullptr,nullptr,nullptr ,nullptr,nullptr,nullptr ,nullptr,nullptr,nullptr ,nullptr };

		}
		return &mapCallbackParam[key];
	}
private:

};
int GetRkpAndVdData(const char* addr, char* rkpData, int size1, char* verifyData, int size2, void* callback);
int VerifyRkpData(const char* addr, char* verifyData, void* callback);
int  WriteCPL(const char* addr, const char* cpl, void* callback);
int  WriteRSN(const char* addr, const char* val, void* callback);
int QualUnlockSimlock(const char* addr, void* callback);
int  QualWriteSimlock(const char* addr, const char* password, const char* hash, const char* cfg, void* callback);
int  QualCheckSimlock(const char* addr, char simlockFlag, const char* cfg, void* callback);
int  MetkCheckSimlock(const char* addr, char simlockFlag, const char* cfg, void* callback);
int  MetkWriteSimlock(const char* addr, const char* password, const char* hash, const char* cfg, void* callback);
int  QualCheckPhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback);
int  MetkWritePhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback);
int  VerifySimcardMode(const char* addr, const char* val, void* callback);
int  WriteSimcardMode(const char* addr, void* dog, int keyID, const char* vendor, bool isQualPlat, void* callback);
int  MetkCheckNVChecksum(const char* addr, void* callback);
int  MetkCheckNVStatus(const char* addr, void* callback);
int  QualCheckNVStatus(const char* addr, int nvsetmask, void* callback);
void* CreateSafeDog(void* callback);
void* DestroySafeDog(void* dog);
long GetNetDogRemainDays(void* dog);
int GetNetDogToken(const char* userName, const char* password, const char* tokenUrl, char* token, int size, void* callback);
int InitNetDogPara(void* dog, const char* userName, const char* token, const char* serviceUrl, const char* platType, bool isFactory);
int SetCommandID(void* dog, const char* commandID);
int RSA_PriDecryptData_Ext(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);
void* OpenDevice(const char* addr, void* callback);
void  CloseDevice(void* fd, void* callback);
int RequestString(const char* addr, const char* req, const char* expect, char* rsp, int size, void* callback);
int RequestBuffer(const char* addr, const char* req, int reql, const char* expect, int expl, char* rsp, int size, int& rspl, void* callback);
int Authenticate(const char* addr, void* dog, char* hun, int size, uint64_t* outKeyID, int keySize, void* callback);
int WriteSN(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
int CreateUDID(const char* addr, const char* sn, const char* bt, const char* wlan, char* udid, int size, void* callback);
int WriteUDID(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
int WriteBTMAC(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
int WriteWifiMAC(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
int WriteVendorCountry(const char* addr, void* dog, int keyID, const char* vendor, const char* country, void* callback);
int WriteProductName(const char* addr, void* dog, int keyID, const char* val, void* callback);
int WriteAccLock(const char* addr, void* dog, int keyID, const char* nckDiagUnlock, const char hun[8], bool isQualPlat, void* callback);
int WriteUserLock(const char* addr, void* dog, int keyID, const char* lockType, const char hun[8], bool isQualPlat, void* callback);
int WriteFrpKey(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
int WriteFuseGid(const char* addr, void* dog, const char* chipid, void* callback);
int CheckFuseGid(const char* addr, void* dog, const char* chipid, void* callback);
int WriteBarcode(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
//行 59: //typedef int VerifySN(const char* addr, const char* val, void* callback);
int VerifyQfuseRegisterData(const char* addr, const char* val, void* callback);
//行 64: //typedef int VerifyUDID(const char* addr, const char* val, void* callback);
int VerifyBTMAC(const char* addr, const char* val, void* callback);
int VerifyWifiMAC(const char* addr, const char* val, void* callback);
int VerifyRSN(const char* addr, void* callback);
int VerifyHardwareSize(const char* addr, const char* val, void* callback);
int VerifyVendorCountry(const char* addr, const char* vendor, const char* country, void* callback);
int VerifyProductName(const char* addr, const char* val, void* callback);
int VerifyCertifyCode(const char* addr, const char* val, void* callback);
int VerifySecretType(const char* addr, const char* val, void* callback);
int VerifyMarketingName(const char* addr, const char* val, void* callback);
int VerifyBenchmarkFlag(const char* addr, const char* val, void* callback);
int VerifyAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
int VerifyKeyAttestation(const char* addr, const char* keyVD, void* callback);
int VerifyTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
int VerifyDeviceCerts(const char* addr, const char* Hw_Device_Certs_VD, void* callback);
int VerifyAccLock(const char* addr, const char* nckDiagUnlock, void* callback);
int VerifyUserLock(const char* addr, const char* lockType, void* callback);
int VerifyFrpKey(const char* addr, const char* val, void* callback);
int VerifyEmmcID(const char* addr, const char* val, void* callback);
int VerifyPublicKey(const char* addr, const char* val, void* callback);
int VerifyBarcode(const char* addr, const char* val, void* callback);
//行 106: //typedef int CheckDGSlaveServerFlag(const char* addr, void* callback);
int WriteSecretType(const char* addr, const char* val, void* callback);
int WriteCertifyCode(const char* addr, const char* val, void* callback);
int WriteMarketingName(const char* addr, const char* val, void* callback);
int WriteBenchmarkFlag(const char* addr, const char* val, void* callback);
int WriteAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
int WriteKeyAttestation(const char* addr, const char* key1, const char* key2, const char* key3, const char* key4, void* callback);
int WriteTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
int WriteDeviceCerts(const char* addr, const char* cert1, const char* cert2, const char* cert3, const char* cert4, const char* cert5, void* callback);
int ReadSubBoardFlag(const char* addr, char* boardFlag, int size, void* callback);
int CheckMode(const char* addr, void* callback);
int SetMMI2AutoRunFlag(const char* addr, void* dog, int keyID, const char hun[8], bool isQualPlat, void* callback);
int CheckMMI2AutoRunFlagClear(const char* addr, void* callback);
int NVBackup(const char* addr, void* callback);
int MtkCheckSimTray(const char* addr, void* callback);
int ErasePowerOnTime(const char* addr, void* callback);
int SetFactoryVer(const char* addr, void* callback);
int CheckFactoryVer(const char* addr, void* callback);
int CheckUTFlag(const char* addr, void* callback);;
int CheckPTFlag(const char* addr, void* callback);
int ReadSoftwareVer(const char* addr, const char* stationFlag, char* softVerInfo, int size, void* callback);
//行 154: //typedef int CheckSoftwareVer(const char* addr, const char* excelVerInfo, void* callback);
int ReadSDCardState(const char* addr, int& sdCardState, void* callback);
//行 159: //typedef int CheckSDCard(const char* addr, void* callback);
int ReadBoardId(const char* addr, char* strBoardId, int size, void* callback);
//行 164: //typedef int CheckBoardId(const char* addr, const char* BoardId, void* callback);
int ReadMaintenance(const char* addr, const char* testItem, int size, void* callback);
int EraseAccount(const char* addr, void* dog, int keyID, void* callback);
int EraseCustInfo(const char* addr, void* dog, int keyID, void* callback);
int StopAutoCharge(const char* addr, void* callback);
int StartAutoCharge(const char* addr, void* callback);
int ReadBatteryPower(const char* addr, int& value, void* callback);
//行 179: //typedef int CheckBetteryPower(const char* addr, int BatteryLevelLimit, void* callback);
int SetCWFlag(const char* addr, const char* CWflag, void* callback);
int CheckCWFlag(const char* addr, const char* CWflag, void* callback);
int SDUpdate(const char* addr, void* callback);
int ReadMMIFlag(const char* addr, char* MMIFlagList, int size, void* callback);
//行 189: //typedef int CheckMMIFlag(const char* addr, const char* MMIFlagList, void* callback);
int CheckRoot(const char* addr, void* callback);
int FactoryReset(const char* addr, void* callback);
int FactoryResetCW(const char* addr, void* callback);
int FactoryResetForDemo(const char* addr, void* callback);
int CheckFactoryResetFinished(const char* addr, int timeOut, void* callback);
int EnableRetread(const char* addr, void* callback);
int RestartDevice(const char* addr, void* callback);
int DeleteSoftwareLog(const char* addr, void* callback);
int QualCheckNV453(const char* addr, void* callback);
int QualCheckRWFlag(const char* addr, void* callback);
int QualDelLogbat(const char* addr, void* callback);
int WriteOptimizeFlag(const char* addr, const char* optimizeMode, const char* optimizeValue, void* callback);
int EraseOEMPhyNum(const char* addr, void* dog, int keyID, void* callback);
int QualSetNRWFlag(const char* addr, void* callback);
int QualRebootModem(const char* addr, void* callback);
int QualEraseNRWFlag(const char* addr, void* callback);
int QualSetDutOffline(const char* addr, void* callback);
int QualCheckOnlineAndSetOffline(const char* addr, void* callback);
int QualEraseModem(const char* addr, void* callback);
int QualEraseCPPhyNum(const char* addr, void* callback);
int CheckBootState(const char* addr, int timeout, void* callback);
int QualGoldenCopy(const char* addr, void* callback);
int QualGetNRWFlag(const char* addr, int& NRWFlag, void* callback);
int CheckSimSlot(const char* addr, void* callback);
int QualNVEMMCSync(const char* addr, void* callback);
int QualWriteNVItem(const char* addr, uint16_t nvid, void* callback);
int ReadUDID(const char* addr, char* buff, int size, void* callback);
int ReadEmmcID(const char* addr, char* buff, int size, void* callback);
int ReadPublicKey(const char* addr, char* buff, int size, void* callback);
int CreatePublicKey(const char* addr, void* callback);
int ReadBarcode(const char* addr, char* buff, int size, void* callback);
int ReadRunMode(const char* addr, char* buff, int size, void* callback);
int ReadSN(const char* addr, char* data, int size, void* callback);

#if 0

#pragma region 荣耀库定义
HINSTANCE handleLibBaseSafedog = LoadLibraryA("libBaseSafedog.dll");
HINSTANCE handleLibMetkCheckNV = LoadLibraryA("libMetkCheckNV.dll");
HINSTANCE handlelibBaseCommunicate = LoadLibraryA("libBaseCommunicate.dll");
HINSTANCE handleLibVerifyCustomization = LoadLibraryA("libVerifyCustomization.dll");
HINSTANCE handleLibWriteCustomization = LoadLibraryA("libWriteCustomization.dll");
HINSTANCE handleLibCustomizationKeyAction = LoadLibraryA("libCustomizationKeyAction.dll");
HINSTANCE handleLibReadCustomization = LoadLibraryA("libReadCustomization.dll");
HINSTANCE handleLibAuthenticate = LoadLibraryA("libAuthenticate.dll");
HINSTANCE handleLibWriteCiphertextCustomization = LoadLibraryA("libWriteCiphertextCustomization.dll");

//libBaseSafedog.dll
typedef int  (*pSetCommandID)(void* dog, const char* commandID);
pSetCommandID SetCommandID = (pSetCommandID)GetProcAddress(handleLibBaseSafedog, "SetCommandID");
typedef int  (*pRSA_PriDecryptData_Ext)(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);
pRSA_PriDecryptData_Ext RSA_PriDecryptData_Ext = (pRSA_PriDecryptData_Ext)GetProcAddress(handleLibBaseSafedog, "RSA_PriDecryptData_Ext");

typedef int (*pRequestString)(const char* addr, const char* req, const char* expect, char* rsp, int size, void* callback);
pRequestString RequestString = (pRequestString)GetProcAddress(handlelibBaseCommunicate, "RequestString");
typedef int (*pRequestBuffer)(const char* addr, const char* req, int reql, const char* expect, int expl, char* rsp, int size, int& rspl, void* callback);
pRequestBuffer RequestBuffer = (pRequestBuffer)GetProcAddress(handlelibBaseCommunicate, "RequestBuffer");

typedef int  (*pAuthenticate)(const char* addr, void* dog, char* hun, int size, uint64_t* outKeyID, int keySize, void* callback);
pAuthenticate Authenticate = (pAuthenticate)GetProcAddress(handleLibAuthenticate, "Authenticate");


typedef int  (*pCreateUDID)(const char* addr, const char* sn, const char* bt, const char* wlan, char* udid, int size, void* callback);
pCreateUDID CreateUDID = (pCreateUDID)GetProcAddress(handleLibWriteCiphertextCustomization, "CreateUDID");;
typedef int  (*pWriteUDID)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
pWriteUDID WriteUDID = (pWriteUDID)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteUDID");
typedef int  (*pWriteBTMAC)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
pWriteBTMAC WriteBTMAC = (pWriteBTMAC)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteBTMAC");
typedef int  (*pWriteWifiMAC)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
pWriteWifiMAC WriteWifiMAC = (pWriteWifiMAC)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteWifiMAC");
typedef int  (*pWriteVendorCountry)(const char* addr, void* dog, int keyID, const char* vendor, const char* country, void* callback);
pWriteVendorCountry WriteVendorCountry = (pWriteVendorCountry)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteVendorCountry");
typedef int  (*pWriteProductName)(const char* addr, void* dog, int keyID, const char* val, void* callback);
pWriteProductName WriteProductName = (pWriteProductName)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteProductName");
typedef int  (*pWriteAccLock)(const char* addr, void* dog, int keyID, const char* nckDiagUnlock, const char hun[8], bool isQualPlat, void* callback);
pWriteAccLock WriteAccLock = (pWriteAccLock)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteAccLock");
typedef int  (*pWriteUserLock)(const char* addr, void* dog, int keyID, const char* lockType, const char hun[8], bool isQualPlat, void* callback);
pWriteUserLock WriteUserLock = (pWriteUserLock)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteUserLock");
typedef int (*pWriteFrpKey)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
pWriteFrpKey WriteFrpKey = (pWriteFrpKey)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteFrpKey");
typedef int (*pWriteFuseGid)(const char* addr, void* dog, const char* chipid, void* callback);
pWriteFuseGid WriteFuseGid = (pWriteFuseGid)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteFuseGid");
typedef int  (*pCheckFuseGid)(const char* addr, void* dog, const char* chipid, void* callback);
pCheckFuseGid CheckFuseGid = (pCheckFuseGid)GetProcAddress(handleLibWriteCiphertextCustomization, "CheckFuseGid");
typedef int  (*pWriteBarcode)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
pWriteBarcode WriteBarcode = (pWriteBarcode)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteBarcode");



/// <summary>
///  暂不支持该函数
/// </summary>
//typedef int  (*pVerifySN)(const char* addr, const char* val, void* callback);
//pVerifySN VerifySN = (pVerifySN)GetProcAddress(handleLibVerifyCustomization, "VerifySN");

typedef int  (*pVerifyQfuseRegisterData)(const char* addr, const char* val, void* callback);
pVerifyQfuseRegisterData  VerifyQfuseRegisterData = (pVerifyQfuseRegisterData)GetProcAddress(handleLibVerifyCustomization, "VerifyQfuseRegisterData");;
//typedef int  (*pVerifyUDID)(const char* addr, const char* val, void* callback);
//pVerifyUDID  VerifyUDID = (pVerifyUDID)GetProcAddress(handleLibVerifyCustomization, "VerifyUDID");

typedef int  (*pVerifyBTMAC)(const char* addr, const char* val, void* callback);
pVerifyBTMAC VerifyBTMAC = (pVerifyBTMAC)GetProcAddress(handleLibVerifyCustomization, "VerifyBTMAC");
typedef int  (*pVerifyWifiMAC)(const char* addr, const char* val, void* callback);
pVerifyWifiMAC VerifyWifiMAC = (pVerifyWifiMAC)GetProcAddress(handleLibVerifyCustomization, "VerifyWifiMAC");
typedef int  (*pVerifyRSN)(const char* addr, void* callback);
static pVerifyRSN VerifyRSN = (pVerifyRSN)GetProcAddress(handleLibVerifyCustomization, "VerifyRSN");
typedef int  (*pVerifyHardwareSize)(const char* addr, const char* val, void* callback);
pVerifyHardwareSize VerifyHardwareSize = (pVerifyHardwareSize)GetProcAddress(handleLibVerifyCustomization, "VerifyHardwareSize");
typedef int  (*pVerifyVendorCountry)(const char* addr, const char* vendor, const char* country, void* callback);
pVerifyVendorCountry VerifyVendorCountry = (pVerifyVendorCountry)GetProcAddress(handleLibVerifyCustomization, "VerifyVendorCountry");
typedef int  (*pVerifyProductName)(const char* addr, const char* val, void* callback);
pVerifyProductName VerifyProductName = (pVerifyProductName)GetProcAddress(handleLibVerifyCustomization, "VerifyProductName");
typedef int  (*pVerifyCertifyCode)(const char* addr, const char* val, void* callback);
pVerifyCertifyCode VerifyCertifyCode = (pVerifyCertifyCode)GetProcAddress(handleLibVerifyCustomization, "VerifyCertifyCode");
typedef int  (*pVerifySecretType)(const char* addr, const char* val, void* callback);
pVerifySecretType VerifySecretType = (pVerifySecretType)GetProcAddress(handleLibVerifyCustomization, "VerifySecretType");
typedef int  (*pVerifyMarketingName)(const char* addr, const char* val, void* callback);
pVerifyMarketingName VerifyMarketingName = (pVerifyMarketingName)GetProcAddress(handleLibVerifyCustomization, "VerifyMarketingName");
typedef int  (*pVerifyBenchmarkFlag)(const char* addr, const char* val, void* callback);
pVerifyBenchmarkFlag VerifyBenchmarkFlag = (pVerifyBenchmarkFlag)GetProcAddress(handleLibVerifyCustomization, "VerifyBenchmarkFlag");
typedef int  (*pVerifyAttestationIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
pVerifyAttestationIDS VerifyAttestationIDS = (pVerifyAttestationIDS)GetProcAddress(handleLibVerifyCustomization, "VerifyAttestationIDS");
typedef int  (*pVerifyKeyAttestation)(const char* addr, const char* keyVD, void* callback);
pVerifyKeyAttestation VerifyKeyAttestation = (pVerifyKeyAttestation)GetProcAddress(handleLibVerifyCustomization, "VerifyKeyAttestation");
typedef int  (*pVerifyTrustDeviceIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
pVerifyTrustDeviceIDS VerifyTrustDeviceIDS = (pVerifyTrustDeviceIDS)GetProcAddress(handleLibVerifyCustomization, "VerifyTrustDeviceIDS");
typedef int  (*pVerifyDeviceCerts)(const char* addr, const char* Hw_Device_Certs_VD, void* callback);
pVerifyDeviceCerts VerifyDeviceCerts = (pVerifyDeviceCerts)GetProcAddress(handleLibVerifyCustomization, "VerifyDeviceCerts");
typedef int (*pVerifyAccLock)(const char* addr, const char* nckDiagUnlock, void* callback);
pVerifyAccLock VerifyAccLock = (pVerifyAccLock)GetProcAddress(handleLibVerifyCustomization, "VerifyAccLock");
typedef int  (*pVerifyUserLock)(const char* addr, const char* lockType, void* callback);
pVerifyUserLock VerifyUserLock = (pVerifyUserLock)GetProcAddress(handleLibVerifyCustomization, "VerifyUserLock");
typedef int  (*pVerifyFrpKey)(const char* addr, const char* val, void* callback);
pVerifyFrpKey VerifyFrpKey = (pVerifyFrpKey)GetProcAddress(handleLibVerifyCustomization, "VerifyFrpKey");
typedef int  (*pVerifyEmmcID)(const char* addr, const char* val, void* callback);
pVerifyEmmcID VerifyEmmcID = (pVerifyEmmcID)GetProcAddress(handleLibVerifyCustomization, "VerifyEmmcID");
typedef int  (*pVerifyPublicKey)(const char* addr, const char* val, void* callback);
pVerifyPublicKey VerifyPublicKey = (pVerifyPublicKey)GetProcAddress(handleLibVerifyCustomization, "VerifyPublicKey");
typedef int  (*pVerifyBarcode)(const char* addr, const char* val, void* callback);
pVerifyBarcode VerifyBarcode = (pVerifyBarcode)GetProcAddress(handleLibVerifyCustomization, "VerifyBarcode");
//typedef int  (*pCheckDGSlaveServerFlag)(const char* addr, void* callback);
//pCheckDGSlaveServerFlag CheckDGSlaveServerFlag = (pCheckDGSlaveServerFlag)GetProcAddress(handleLibVerifyCustomization, "CheckDGSlaveServerFlag");


typedef int  (*pWriteSecretType)(const char* addr, const char* val, void* callback);
pWriteSecretType WriteSecretType = (pWriteSecretType)GetProcAddress(handleLibWriteCustomization, "WriteSecretType");
typedef int  (*pWriteCertifyCode)(const char* addr, const char* val, void* callback);
pWriteCertifyCode WriteCertifyCode = (pWriteCertifyCode)GetProcAddress(handleLibWriteCustomization, "WriteCertifyCode");
typedef int  (*pWriteMarketingName)(const char* addr, const char* val, void* callback);
pWriteMarketingName WriteMarketingName = (pWriteMarketingName)GetProcAddress(handleLibWriteCustomization, "WriteMarketingName");
typedef int  (*pWriteBenchmarkFlag)(const char* addr, const char* val, void* callback);
pWriteBenchmarkFlag WriteBenchmarkFlag = (pWriteBenchmarkFlag)GetProcAddress(handleLibWriteCustomization, "WriteBenchmarkFlag");
typedef int  (*pWriteAttestationIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
pWriteAttestationIDS WriteAttestationIDS = (pWriteAttestationIDS)GetProcAddress(handleLibWriteCustomization, "WriteAttestationIDS");
typedef int  (*pWriteKeyAttestation)(const char* addr, const char* key1, const char* key2, const char* key3, const char* key4, void* callback);
pWriteKeyAttestation WriteKeyAttestation = (pWriteKeyAttestation)GetProcAddress(handleLibWriteCustomization, "WriteKeyAttestation");
typedef int  (*pWriteTrustDeviceIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
pWriteTrustDeviceIDS WriteTrustDeviceIDS = (pWriteTrustDeviceIDS)GetProcAddress(handleLibWriteCustomization, "WriteTrustDeviceIDS");
typedef int  (*pWriteDeviceCerts)(const char* addr, const char* cert1, const char* cert2, const char* cert3, const char* cert4, const char* cert5, void* callback);
pWriteDeviceCerts WriteDeviceCerts = (pWriteDeviceCerts)GetProcAddress(handleLibWriteCustomization, "WriteDeviceCerts");


typedef int  (*pReadSubBoardFlag)(const char* addr, char* boardFlag, int size, void* callback);
pReadSubBoardFlag ReadSubBoardFlag = (pReadSubBoardFlag)GetProcAddress(handleLibCustomizationKeyAction, "ReadSubBoardFlag");
typedef int (*pCheckMode)(const char* addr, void* callback);
pCheckMode CheckMode = (pCheckMode)GetProcAddress(handleLibCustomizationKeyAction, "CheckMode");

typedef int (*pSetMMI2AutoRunFlag)(const char* addr, void* dog, int keyID, const char hun[8], bool isQualPlat, void* callback);
pSetMMI2AutoRunFlag SetMMI2AutoRunFlag = (pSetMMI2AutoRunFlag)GetProcAddress(handleLibCustomizationKeyAction, "SetMMI2AutoRunFlag");
typedef int  (*pCheckMMI2AutoRunFlagClear)(const char* addr, void* callback);
pCheckMMI2AutoRunFlagClear CheckMMI2AutoRunFlagClear = (pCheckMMI2AutoRunFlagClear)GetProcAddress(handleLibCustomizationKeyAction, "CheckMMI2AutoRunFlagClear");
typedef int  (*pNVBackup)(const char* addr, void* callback);
pNVBackup NVBackup = (pNVBackup)GetProcAddress(handleLibCustomizationKeyAction, "NVBackup");
typedef int  (*pMtkCheckSimTray)(const char* addr, void* callback);
pMtkCheckSimTray MtkCheckSimTray = (pMtkCheckSimTray)GetProcAddress(handleLibCustomizationKeyAction, "MtkCheckSimTray");
typedef int  (*pErasePowerOnTime)(const char* addr, void* callback);
pErasePowerOnTime ErasePowerOnTime = (pErasePowerOnTime)GetProcAddress(handleLibCustomizationKeyAction, "ErasePowerOnTime");

typedef int  (*pSetFactoryVer)(const char* addr, void* callback);
typedef int  (*pCheckFactoryVer)(const char* addr, void* callback);

typedef int  (*pCheckUTFlag)(const char* addr, void* callback);;
pCheckUTFlag CheckUTFlag = (pCheckUTFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckUTFlag");
typedef int  (*pCheckPTFlag)(const char* addr, void* callback);
pCheckPTFlag CheckPTFlag = (pCheckPTFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckPTFlag");
typedef int  (*pReadSoftwareVer)(const char* addr, const char* stationFlag, char* softVerInfo, int size, void* callback);
pReadSoftwareVer ReadSoftwareVer = (pReadSoftwareVer)GetProcAddress(handleLibCustomizationKeyAction, "ReadSoftwareVer");

//typedef int  (*pCheckSoftwareVer)(const char* addr, const char* excelVerInfo, void* callback);
//pCheckSoftwareVer CheckSoftwareVer = (pCheckSoftwareVer)GetProcAddress(handleLibCustomizationKeyAction, "CheckSoftwareVer");
typedef int  (*pReadSDCardState)(const char* addr, int& sdCardState, void* callback);
pReadSDCardState ReadSDCardState = (pReadSDCardState)GetProcAddress(handleLibCustomizationKeyAction, "ReadSDCardState");

//typedef int  (*pCheckSDCard)(const char* addr, void* callback);
//pCheckSDCard CheckSDCard = (pCheckSDCard)GetProcAddress(handleLibCustomizationKeyAction, "CheckSDCard");
typedef int  (*pReadBoardId)(const char* addr, char* strBoardId, int size, void* callback);
pReadBoardId ReadBoardId = (pReadBoardId)GetProcAddress(handleLibCustomizationKeyAction, "ReadBoardId");

//typedef int  (*pCheckBoardId)(const char* addr, const char* BoardId, void* callback);
//pCheckBoardId CheckBoardId = (pCheckBoardId)GetProcAddress(handleLibCustomizationKeyAction, "CheckBoardId");
typedef int  (*pReadMaintenance)(const char* addr, const char* testItem, int size, void* callback);
pReadMaintenance ReadMaintenance = (pReadMaintenance)GetProcAddress(handleLibCustomizationKeyAction, "ReadMaintenance");
typedef int  (*pEraseAccount)(const char* addr, void* dog, int keyID, void* callback);
pEraseAccount EraseAccount = (pEraseAccount)GetProcAddress(handleLibCustomizationKeyAction, "EraseAccount");
typedef int  (*pEraseCustInfo)(const char* addr, void* dog, int keyID, void* callback);
pEraseCustInfo EraseCustInfo = (pEraseCustInfo)GetProcAddress(handleLibCustomizationKeyAction, "EraseCustInfo");
typedef int (*pStopAutoCharge)(const char* addr, void* callback);
pStopAutoCharge StopAutoCharge = (pStopAutoCharge)GetProcAddress(handleLibCustomizationKeyAction, "StopAutoCharge");
typedef int (*pStartAutoCharge)(const char* addr, void* callback);
pStopAutoCharge StartAutoCharge = (pStopAutoCharge)GetProcAddress(handleLibCustomizationKeyAction, "StartAutoCharge");
typedef int  (*pReadBatteryPower)(const char* addr, int& value, void* callback);
pReadBatteryPower ReadBatteryPower = (pReadBatteryPower)GetProcAddress(handleLibCustomizationKeyAction, "ReadBatteryPower");

//typedef int  (*pCheckBetteryPower)(const char* addr, int BatteryLevelLimit, void* callback);
//pCheckBetteryPower CheckBetteryPower = (pCheckBetteryPower)GetProcAddress(handleLibCustomizationKeyAction, "CheckBetteryPower");
typedef int  (*pSetCWFlag)(const char* addr, const char* CWflag, void* callback);
pSetCWFlag SetCWFlag = (pSetCWFlag)GetProcAddress(handleLibCustomizationKeyAction, "SetCWFlag");
typedef int  (*pCheckCWFlag)(const char* addr, const char* CWflag, void* callback);
pCheckCWFlag CheckCWFlag = (pCheckCWFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckCWFlag");
typedef int  (*pSDUpdate)(const char* addr, void* callback);
pSDUpdate SDUpdate = (pSDUpdate)GetProcAddress(handleLibCustomizationKeyAction, "SDUpdate");
typedef int  (*pReadMMIFlag)(const char* addr, char* MMIFlagList, int size, void* callback);
pReadMMIFlag ReadMMIFlag = (pReadMMIFlag)GetProcAddress(handleLibCustomizationKeyAction, "ReadMMIFlag");
//typedef int  (*pCheckMMIFlag)(const char* addr, const char* MMIFlagList, void* callback);
//pCheckMMIFlag CheckMMIFlag = (pCheckMMIFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckMMIFlag");
typedef int  (*pCheckRoot)(const char* addr, void* callback);
pCheckRoot CheckRoot = (pCheckRoot)GetProcAddress(handleLibCustomizationKeyAction, "CheckRoot");
typedef int  (*pFactoryReset)(const char* addr, void* callback);
pFactoryReset FactoryReset = (pFactoryReset)GetProcAddress(handleLibCustomizationKeyAction, "FactoryReset");
typedef int  (*pFactoryResetCW)(const char* addr, void* callback);
pFactoryResetCW FactoryResetCW = (pFactoryResetCW)GetProcAddress(handleLibCustomizationKeyAction, "FactoryResetCW");
typedef int  (*pFactoryResetForDemo)(const char* addr, void* callback);
pFactoryResetForDemo FactoryResetForDemo = (pFactoryResetForDemo)GetProcAddress(handleLibCustomizationKeyAction, "FactoryResetForDemo");
typedef int  (*pCheckFactoryResetFinished)(const char* addr, int timeOut, void* callback);
pCheckFactoryResetFinished CheckFactoryResetFinished = (pCheckFactoryResetFinished)GetProcAddress(handleLibCustomizationKeyAction, "CheckFactoryResetFinished");
typedef int  (*pEnableRetread)(const char* addr, void* callback);
pEnableRetread EnableRetread = (pEnableRetread)GetProcAddress(handleLibCustomizationKeyAction, "EnableRetread");
typedef int  (*pRestartDevice)(const char* addr, void* callback);
pRestartDevice RestartDevice = (pRestartDevice)GetProcAddress(handleLibCustomizationKeyAction, "RestartDevice");
typedef int  (*pDeleteSoftwareLog)(const char* addr, void* callback);
pDeleteSoftwareLog DeleteSoftwareLog = (pDeleteSoftwareLog)GetProcAddress(handleLibCustomizationKeyAction, "DeleteSoftwareLog");
typedef int  (*pQualCheckNV453)(const char* addr, void* callback);
pQualCheckNV453 QualCheckNV453 = (pQualCheckNV453)GetProcAddress(handleLibCustomizationKeyAction, "QualCheckNV453");
typedef int  (*pQualCheckRWFlag)(const char* addr, void* callback);
pQualCheckRWFlag QualCheckRWFlag = (pQualCheckRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualCheckRWFlag");
typedef int  (*pQualDelLogbat)(const char* addr, void* callback);
pQualDelLogbat QualDelLogbat = (pQualDelLogbat)GetProcAddress(handleLibCustomizationKeyAction, "QualDelLogbat");
typedef int  (*pWriteOptimizeFlag)(const char* addr, const char* optimizeMode, const char* optimizeValue, void* callback);
pWriteOptimizeFlag WriteOptimizeFlag = (pWriteOptimizeFlag)GetProcAddress(handleLibCustomizationKeyAction, "WriteOptimizeFlag");
typedef int  (*pEraseOEMPhyNum)(const char* addr, void* dog, int keyID, void* callback);
pEraseOEMPhyNum EraseOEMPhyNum = (pEraseOEMPhyNum)GetProcAddress(handleLibCustomizationKeyAction, "EraseOEMPhyNum");
typedef int  (*pQualSetNRWFlag)(const char* addr, void* callback);
pQualSetNRWFlag QualSetNRWFlag = (pQualSetNRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualSetNRWFlag");
typedef int  (*pQualRebootModem)(const char* addr, void* callback);
pQualRebootModem QualRebootModem = (pQualRebootModem)GetProcAddress(handleLibCustomizationKeyAction, "QualRebootModem");
typedef int  (*pQualEraseNRWFlag)(const char* addr, void* callback);
pQualEraseNRWFlag QualEraseNRWFlag = (pQualEraseNRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualEraseNRWFlag");
typedef int  (*pQualSetDutOffline)(const char* addr, void* callback);
pQualSetDutOffline QualSetDutOffline = (pQualSetDutOffline)GetProcAddress(handleLibCustomizationKeyAction, "QualSetDutOffline");
typedef int  (*pQualCheckOnlineAndSetOffline)(const char* addr, void* callback);
pQualCheckOnlineAndSetOffline QualCheckOnlineAndSetOffline = (pQualCheckOnlineAndSetOffline)GetProcAddress(handleLibCustomizationKeyAction, "QualCheckOnlineAndSetOffline");
typedef int  (*pQualEraseModem)(const char* addr, void* callback);
pQualEraseModem QualEraseModem = (pQualEraseModem)GetProcAddress(handleLibCustomizationKeyAction, "QualEraseModem");
typedef int  (*pQualEraseCPPhyNum)(const char* addr, void* callback);
pQualEraseCPPhyNum QualEraseCPPhyNum = (pQualEraseCPPhyNum)GetProcAddress(handleLibCustomizationKeyAction, "QualEraseCPPhyNum");
typedef int  (*pCheckBootState)(const char* addr, int timeout, void* callback);
pCheckBootState CheckBootState = (pCheckBootState)GetProcAddress(handleLibCustomizationKeyAction, "CheckBootState");
typedef int  (*pQualGoldenCopy)(const char* addr, void* callback);
pQualGoldenCopy QualGoldenCopy = (pQualGoldenCopy)GetProcAddress(handleLibCustomizationKeyAction, "QualGoldenCopy");
typedef int  (*pQualGetNRWFlag)(const char* addr, int& NRWFlag, void* callback);
pQualGetNRWFlag QualGetNRWFlag = (pQualGetNRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualGetNRWFlag");
typedef int  (*pCheckSimSlot)(const char* addr, void* callback);
pCheckSimSlot CheckSimSlot = (pCheckSimSlot)GetProcAddress(handleLibCustomizationKeyAction, "CheckSimSlot");
typedef int  (*pQualNVEMMCSync)(const char* addr, void* callback);
pQualNVEMMCSync QualNVEMMCSync = (pQualNVEMMCSync)GetProcAddress(handleLibCustomizationKeyAction, "QualNVEMMCSync");
typedef int  (*pQualWriteNVItem)(const char* addr, uint16_t nvid, void* callback);
pQualWriteNVItem QualWriteNVItem = (pQualWriteNVItem)GetProcAddress(handleLibCustomizationKeyAction, "QualWriteNVItem");


typedef int  (*pReadUDID)(const char* addr, char* buff, int size, void* callback);
pReadUDID ReadUDID = (pReadUDID)GetProcAddress(handleLibReadCustomization, "ReadUDID");
typedef int  (*pReadEmmcID)(const char* addr, char* buff, int size, void* callback);
pReadEmmcID ReadEmmcID = (pReadEmmcID)GetProcAddress(handleLibReadCustomization, "ReadEmmcID");
typedef int  (*pReadPublicKey)(const char* addr, char* buff, int size, void* callback);
typedef int  (*pCreatePublicKey)(const char* addr, void* callback);
typedef int  (*pReadBarcode)(const char* addr, char* buff, int size, void* callback);
pReadBarcode ReadBarcode = (pReadBarcode)GetProcAddress(handleLibReadCustomization, "ReadBarcode");
typedef int  (*pReadRunMode)(const char* addr, char* buff, int size, void* callback);
pReadRunMode ReadRunMode = (pReadRunMode)GetProcAddress(handleLibReadCustomization, "ReadRunMode");
typedef int  (*pReadSN)(const char* addr, char* data, int size, void* callback);
pReadSN ReadSN = (pReadSN)GetProcAddress(handleLibReadCustomization, "ReadSN");
#pragma endregion

#endif // 0
