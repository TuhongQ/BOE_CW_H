#include "pch.h"
#include "HonorInterface.h"

HINSTANCE handleLibBaseSafedog = LoadLibraryA("libBaseSafedog.dll");
HINSTANCE handleLibMetkCheckNV = LoadLibraryA("libMetkCheckNV.dll");
HINSTANCE handlelibBaseCommunicate = LoadLibraryA("libBaseCommunicate.dll");
HINSTANCE handleLibVerifyCustomization = LoadLibraryA("libVerifyCustomization.dll");
HINSTANCE handleLibWriteCustomization = LoadLibraryA("libWriteCustomization.dll");
HINSTANCE handleLibCustomizationKeyAction = LoadLibraryA("libCustomizationKeyAction.dll");
HINSTANCE handleLibReadCustomization = LoadLibraryA("libReadCustomization.dll");
HINSTANCE handleLibAuthenticate = LoadLibraryA("libAuthenticate.dll");
HINSTANCE handleLibWriteCiphertextCustomization = LoadLibraryA("libWriteCiphertextCustomization.dll");
HINSTANCE handleLibMetkPhysicalNumber = LoadLibraryA("libMetkPhysicalNumber.dll");
HINSTANCE handleLibMetkSimlock = LoadLibraryA("libMetkSimlock.dll");
HINSTANCE handleLibCreateCustomization = LoadLibraryA("libcreatecustomization.dll");
HINSTANCE handleLibQualSimlock = LoadLibraryA("libQualSimlock.dll");
#include <mutex>

int GetRkpAndVdData(const char* addr, char* rkpData, int size1, char* verifyData, int size2, void* callback)
{
	typedef int (*pGetRkpAndVdData)(const char* addr, char* rkpData, int size1, char* verifyData, int size2, void* callback);
	pGetRkpAndVdData GetRkpAndVdData_h = (pGetRkpAndVdData)GetProcAddress(handleLibCreateCustomization, "GetRkpAndVdData");
	return GetRkpAndVdData_h(addr, rkpData,size1,verifyData,size2,callback);
}
int VerifyRkpData(const char* addr, char* verifyData, void* callback) 
{
	typedef int (*pVerifyRkpData)(const char* addr, char* verifyData, void* callback);
	pVerifyRkpData VerifyRkpData_h = (pVerifyRkpData)GetProcAddress(handleLibCreateCustomization, "VerifyRkpData");
	return VerifyRkpData_h(addr, verifyData,callback);
}
int QualUnlockSimlock(const char* addr, void* callback)
{
	typedef int (*pQualUnlockSimlock)(const char* addr, void* callback);
	pQualUnlockSimlock QualUnlockSimlock_h = (pQualUnlockSimlock)GetProcAddress(handleLibQualSimlock, "QualUnlockSimlock");
	return QualUnlockSimlock_h(addr, callback);
}
int  QualWriteSimlock(const char* addr, const char* password, const char* hash, const char* cfg, void* callback) 
{
	typedef int (*pQualWriteSimlock)(const char* addr, const char* password, const char* hash, const char* cfg, void* callback);
	pQualWriteSimlock QualWriteSimlock_h = (pQualWriteSimlock)GetProcAddress(handleLibQualSimlock, "QualWriteSimlock");
	return QualWriteSimlock_h(addr,password,hash,cfg, callback);
}
int  QualCheckSimlock(const char* addr, char simlockFlag, const char* cfg, void* callback) 
{
	typedef int (*pQualCheckSimlock)(const char* addr, char simlockFlag, const char* cfg, void* callback);
	pQualCheckSimlock QualCheckSimlock_h = (pQualCheckSimlock)GetProcAddress(handleLibQualSimlock, "QualCheckSimlock");
	return QualCheckSimlock_h(addr,simlockFlag,cfg, callback);
}
//std::mutex g_mutex;
// 参数: char simlockFlag 锁卡表中SIMLOCK_WRITE字段的值，为"0"或者"1"。为"0"时，const char* cfg 为nullptr，为"1"时const char* cfg传入表格路径
// 参数: const char* cfg 配置SIMLOCK信息的表格路径，没有时，可以为nullptr
// 返回: -1 表示失败，0 表示成功
int  MetkCheckSimlock(const char* addr, char simlockFlag, const char* cfg, void* callback)
{
	typedef int (*pMetkCheckSimlock)(const char* addr, char simlockFlag, const char* cfg, void* callback);
	pMetkCheckSimlock MetkCheckSimlock_h = (pMetkCheckSimlock)GetProcAddress(handleLibMetkCheckNV, "MetkCheckSimlock");
	return MetkCheckSimlock_h(addr, simlockFlag, cfg, callback);
}
int  MetkWriteSimlock(const char* addr, const char* password, const char* hash, const char* cfg, void* callback)
{
	typedef int (*pMetkWriteSimlock)(const char* addr, const char* password, const char* hash, const char* cfg, void* callback);
	pMetkWriteSimlock MetkWriteSimlock_h = (pMetkWriteSimlock)GetProcAddress(handleLibMetkCheckNV, "MetkWriteSimlock");
	return MetkWriteSimlock_h(addr, password, hash, cfg, callback);
}
int  MetkCheckNVChecksum(const char* addr, void* callback)
{
	typedef int (*pMetkCheckNVChecksum)(const char* addr, void* callback);
	pMetkCheckNVChecksum MetkCheckNVChecksum_h = (pMetkCheckNVChecksum)GetProcAddress(handleLibMetkCheckNV, "MetkCheckNVChecksum");
	return MetkCheckNVChecksum_h(addr, callback);
}

int  MetkCheckNVStatus(const char* addr, void* callback)
{
	typedef int (*pMetkCheckNVStatus)(const char* addr, void* callback);
	static pMetkCheckNVStatus MetkCheckNVStatus_h = (pMetkCheckNVStatus)GetProcAddress(handleLibMetkCheckNV, "MetkCheckNVStatus");
	return MetkCheckNVStatus_h(addr, callback);
}

int QualtoATCheckNVStatus(const char* addr, void* callback)
{
	typedef int (*pQualtoATCheckNVStatus)(const char* addr, void* callback);
	static pQualtoATCheckNVStatus QualtoATCheckNVStatus_h = (pQualtoATCheckNVStatus)GetProcAddress(handleLibMetkCheckNV, "QualtoATCheckNVStatus");
	return QualtoATCheckNVStatus_h(addr, callback);
}
void* DestroySafeDog(void* dog)
{
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef void* (*pDestroySafeDog)(void* dog);
	pDestroySafeDog DestroySafeDog_h = (pDestroySafeDog)GetProcAddress(handleLibBaseSafedog, "DestroySafeDog");
	return DestroySafeDog_h(dog);
}

long GetNetDogRemainDays(void* dog)
{
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef long (*pGetNetDogRemainDays)(void* dog);
	pGetNetDogRemainDays GetNetDogRemainDays_h = (pGetNetDogRemainDays)GetProcAddress(handleLibBaseSafedog, "GetNetDogRemainDays");
	return GetNetDogRemainDays_h(dog);
}

int GetNetDogToken(const char* userName, const char* password, const char* tokenUrl, char* token, int size, void* callback)
{
	typedef int (*pGetNetDogToken)(const char* userName, const char* password, const char* tokenUrl, char* token, int size, void* callback);
	pGetNetDogToken GetNetDogToken_h = (pGetNetDogToken)GetProcAddress(handleLibBaseSafedog, "GetNetDogToken");
	return GetNetDogToken_h(userName, password, tokenUrl, token, size, callback);
}

int InitNetDogPara(void* dog, const char* userName, const char* token, const char* serviceUrl, const char* platType, bool isFactory)
{
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef int (*pInitNetDogPara)(void* dog, const char* userName, const char* token, const char* serviceUrl, const char* platType, bool isFactory);
	pInitNetDogPara InitNetDogPara_h = (pInitNetDogPara)GetProcAddress(handleLibBaseSafedog, "InitNetDogPara");
	return InitNetDogPara_h(dog, userName, token, serviceUrl, platType, isFactory);
}

int SetCommandID(void* dog, const char* commandID)
{
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef int  (*pSetCommandID)(void* dog, const char* commandID);
	pSetCommandID SetCommandID1 = (pSetCommandID)GetProcAddress(handleLibBaseSafedog, "SetCommandID");
	return SetCommandID1(dog, commandID);
}

int RSA_PriDecryptData_Ext(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid)
{
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef int  (*pRSA_PriDecryptData_Ext)(void* dog, const char* pucIn, long ulInLen, char* pucOut, long* pulOutLen, long uKeyid);
	pRSA_PriDecryptData_Ext RSA_PriDecryptData_Ext1 = (pRSA_PriDecryptData_Ext)GetProcAddress(handleLibBaseSafedog, "RSA_PriDecryptData_Ext");
	return RSA_PriDecryptData_Ext1(dog, pucIn, ulInLen, pucOut, pulOutLen, uKeyid);
}

void* CreateSafeDog(void* callback) {
	typedef  void* (*pCreateSafeDog)(void* callback);
	pCreateSafeDog CreateSafeDog_h = (pCreateSafeDog)GetProcAddress(handleLibBaseSafedog, "CreateSafeDog");
	return	CreateSafeDog_h(callback);
}

void* OpenDevice(const char* addr, void* callback) {
	typedef  void* (*pOpenDevice)(const char* addr, void* callback);
	pOpenDevice OpenDevice_h = (pOpenDevice)GetProcAddress(handlelibBaseCommunicate, "OpenDevice");
	return	OpenDevice_h(addr, callback);
}

void  CloseDevice(void* fd, void* callback) {
	typedef  void  (*pCloseDevice)(void* fd, void* callback);
	pCloseDevice CloseDevice_h = (pCloseDevice)GetProcAddress(handlelibBaseCommunicate, "CloseDevice");
	return	CloseDevice_h(fd, callback);
}

int RequestString(const char* addr, const char* req, const char* expect, char* rsp, int size, void* callback) {
	typedef  int (*pRequestString)(const char* addr, const char* req, const char* expect, char* rsp, int size, void* callback);
	pRequestString RequestString_h = (pRequestString)GetProcAddress(handlelibBaseCommunicate, "RequestString");
	return	RequestString_h(addr, req, expect, rsp, size, callback);
}

int RequestBuffer(const char* addr, const char* req, int reql, const char* expect, int expl, char* rsp, int size, int& rspl, void* callback) {
	typedef  int (*pRequestBuffer)(const char* addr, const char* req, int reql, const char* expect, int expl, char* rsp, int size, int& rspl, void* callback);
	pRequestBuffer RequestBuffer_h = (pRequestBuffer)GetProcAddress(handlelibBaseCommunicate, "RequestBuffer");
	return	RequestBuffer_h(addr, req, reql, expect, expl, rsp, size, rspl, callback);
}

int  Authenticate(const char* addr, void* dog, char* hun, int size, uint64_t* outKeyID, int keySize, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pAuthenticate)(const char* addr, void* dog, char* hun, int size, uint64_t* outKeyID, int keySize, void* callback);
	pAuthenticate Authenticate_h = (pAuthenticate)GetProcAddress(handleLibAuthenticate, "Authenticate");
	return	Authenticate_h(addr, dog, hun, size, outKeyID, keySize, callback);
}

int WriteSN(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int (*pWriteSN)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
	pWriteSN WriteSN_h = (pWriteSN)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteSN");
	return	WriteSN_h(addr, dog, keyID, val, isQualPlat, callback);
}

int  CreateUDID(const char* addr, const char* sn, const char* bt, const char* wlan, char* udid, int size, void* callback) {
	typedef  int  (*pCreateUDID)(const char* addr, const char* sn, const char* bt, const char* wlan, char* udid, int size, void* callback);
	pCreateUDID CreateUDID_h = (pCreateUDID)GetProcAddress(handleLibWriteCiphertextCustomization, "CreateUDID");;
	return	CreateUDID_h(addr, sn, bt, wlan, udid, size, callback);
}

int  WriteUDID(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteUDID)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
	pWriteUDID WriteUDID_h = (pWriteUDID)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteUDID");
	return	WriteUDID_h(addr, dog, keyID, val, isQualPlat, callback);
}

int  WriteBTMAC(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteBTMAC)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
	pWriteBTMAC WriteBTMAC_h = (pWriteBTMAC)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteBTMAC");
	return	WriteBTMAC_h(addr, dog, keyID, val, isQualPlat, callback);
}

int  WriteWifiMAC(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteWifiMAC)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
	pWriteWifiMAC WriteWifiMAC_h = (pWriteWifiMAC)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteWifiMAC");
	return	WriteWifiMAC_h(addr, dog, keyID, val, isQualPlat, callback);
}

int  WriteVendorCountry(const char* addr, void* dog, int keyID, const char* vendor, const char* country, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteVendorCountry)(const char* addr, void* dog, int keyID, const char* vendor, const char* country, void* callback);
	pWriteVendorCountry WriteVendorCountry_h = (pWriteVendorCountry)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteVendorCountry");
	return	WriteVendorCountry_h(addr, dog, keyID, vendor, country, callback);
}

int  WriteSimcardMode(const char* addr, void* dog, int keyID, const char* vendor, bool isQualPlat, void* callback)
{
	typedef  int  (*pWriteSimcardMode)(const char* addr, void* dog, int keyID, const char* vendor, bool isQualPlat, void* callback);
	pWriteSimcardMode WriteSimcardMode_h = (pWriteSimcardMode)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteSimcardMode");
	return	WriteSimcardMode_h(addr, dog, keyID, vendor, isQualPlat, callback);
}
int  MetkWritePhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback)
{
	typedef  int (*pMetkWritePhysicalNumber)(const char* addr, const PhyNumInfo* phynum, void* callback);
	pMetkWritePhysicalNumber MetkWritePhysicalNumber_h = (pMetkWritePhysicalNumber)GetProcAddress(handleLibMetkPhysicalNumber, "MetkWritePhysicalNumber");
	return MetkWritePhysicalNumber_h(addr, phynum, callback);
}
int  QualCheckPhysicalNumber(const char* addr, const PhyNumInfo* phynum, void* callback)
{
	typedef  int (*pQualCheckPhysicalNumber)(const char* addr, const PhyNumInfo* phynum, void* callback);
	pQualCheckPhysicalNumber QualCheckPhysicalNumber_h = (pQualCheckPhysicalNumber)GetProcAddress(handleLibMetkPhysicalNumber, "QualCheckPhysicalNumber");
	return QualCheckPhysicalNumber_h(addr, phynum, callback);
}
int  WriteProductName(const char* addr, void* dog, int keyID, const char* val, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteProductName)(const char* addr, void* dog, int keyID, const char* val, void* callback);
	pWriteProductName WriteProductName_h = (pWriteProductName)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteProductName");
	return	WriteProductName_h(addr, dog, keyID, val, callback);
}

int  WriteAccLock(const char* addr, void* dog, int keyID, const char* nckDiagUnlock, const char hun[8], bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteAccLock)(const char* addr, void* dog, int keyID, const char* nckDiagUnlock, const char hun[8], bool isQualPlat, void* callback);
	pWriteAccLock WriteAccLock_h = (pWriteAccLock)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteAccLock");
	return	WriteAccLock_h(addr, dog, keyID, nckDiagUnlock, hun, isQualPlat, callback);
}

int  WriteUserLock(const char* addr, void* dog, int keyID, const char* lockType, const char hun[8], bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteUserLock)(const char* addr, void* dog, int keyID, const char* lockType, const char hun[8], bool isQualPlat, void* callback);
	pWriteUserLock WriteUserLock_h = (pWriteUserLock)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteUserLock");
	return	WriteUserLock_h(addr, dog, keyID, lockType, hun, isQualPlat, callback);
}

int WriteFrpKey(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int (*pWriteFrpKey)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
	pWriteFrpKey WriteFrpKey_h = (pWriteFrpKey)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteFrpKey");
	return	WriteFrpKey_h(addr, dog, keyID, val, isQualPlat, callback);
}

int WriteFuseGid(const char* addr, void* dog, const char* chipid, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int (*pWriteFuseGid)(const char* addr, void* dog, const char* chipid, void* callback);
	pWriteFuseGid WriteFuseGid_h = (pWriteFuseGid)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteFuseGid");
	return	WriteFuseGid_h(addr, dog, chipid, callback);
}

int  CheckFuseGid(const char* addr, void* dog, const char* chipid, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pCheckFuseGid)(const char* addr, void* dog, const char* chipid, void* callback);
	pCheckFuseGid CheckFuseGid_h = (pCheckFuseGid)GetProcAddress(handleLibWriteCiphertextCustomization, "CheckFuseGid");
	return	CheckFuseGid_h(addr, dog, chipid, callback);
}

int  WriteBarcode(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pWriteBarcode)(const char* addr, void* dog, int keyID, const char* val, bool isQualPlat, void* callback);
	pWriteBarcode WriteBarcode_h = (pWriteBarcode)GetProcAddress(handleLibWriteCiphertextCustomization, "WriteBarcode");
	return	WriteBarcode_h(addr, dog, keyID, val, isQualPlat, callback);
}

int  VerifyQfuseRegisterData(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyQfuseRegisterData)(const char* addr, const char* val, void* callback);
	pVerifyQfuseRegisterData  VerifyQfuseRegisterData_h = (pVerifyQfuseRegisterData)GetProcAddress(handleLibVerifyCustomization, "VerifyQfuseRegisterData");;
	return	VerifyQfuseRegisterData_h(addr, val, callback);
}

int  VerifyBTMAC(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyBTMAC)(const char* addr, const char* val, void* callback);
	pVerifyBTMAC VerifyBTMAC_h = (pVerifyBTMAC)GetProcAddress(handleLibVerifyCustomization, "VerifyBTMAC");
	return	VerifyBTMAC_h(addr, val, callback);
}

int  VerifyWifiMAC(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyWifiMAC)(const char* addr, const char* val, void* callback);
	pVerifyWifiMAC VerifyWifiMAC_h = (pVerifyWifiMAC)GetProcAddress(handleLibVerifyCustomization, "VerifyWifiMAC");
	return	VerifyWifiMAC_h(addr, val, callback);
}

int  VerifyRSN(const char* addr, void* callback) {
	typedef  int  (*pVerifyRSN)(const char* addr, void* callback);
	pVerifyRSN VerifyRSN_h = (pVerifyRSN)GetProcAddress(handleLibVerifyCustomization, "VerifyRSN");
	return	VerifyRSN_h(addr, callback);
}
int  VerifySimcardMode(const char* addr, const char* val, void* callback)
{
	typedef  int  (*pVerifySimcardMode)(const char* addr, const char* val, void* callback);
	pVerifySimcardMode VerifySimcardMode_h = (pVerifySimcardMode)GetProcAddress(handleLibVerifyCustomization, "VerifySimcardMode");
	return	VerifySimcardMode_h(addr, val, callback);
}

int  VerifyHardwareSize(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyHardwareSize)(const char* addr, const char* val, void* callback);
	pVerifyHardwareSize VerifyHardwareSize_h = (pVerifyHardwareSize)GetProcAddress(handleLibVerifyCustomization, "VerifyHardwareSize");
	return	VerifyHardwareSize_h(addr, val, callback);
}

int  VerifyVendorCountry(const char* addr, const char* vendor, const char* country, void* callback) {
	typedef  int  (*pVerifyVendorCountry)(const char* addr, const char* vendor, const char* country, void* callback);
	pVerifyVendorCountry VerifyVendorCountry_h = (pVerifyVendorCountry)GetProcAddress(handleLibVerifyCustomization, "VerifyVendorCountry");
	return	VerifyVendorCountry_h(addr, vendor, country, callback);
}

int  VerifyProductName(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyProductName)(const char* addr, const char* val, void* callback);
	pVerifyProductName VerifyProductName_h = (pVerifyProductName)GetProcAddress(handleLibVerifyCustomization, "VerifyProductName");
	return	VerifyProductName_h(addr, val, callback);
}

int  VerifyCertifyCode(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyCertifyCode)(const char* addr, const char* val, void* callback);
	pVerifyCertifyCode VerifyCertifyCode_h = (pVerifyCertifyCode)GetProcAddress(handleLibVerifyCustomization, "VerifyCertifyCode");
	return	VerifyCertifyCode_h(addr, val, callback);
}

int  VerifySecretType(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifySecretType)(const char* addr, const char* val, void* callback);
	pVerifySecretType VerifySecretType_h = (pVerifySecretType)GetProcAddress(handleLibVerifyCustomization, "VerifySecretType");
	return	VerifySecretType_h(addr, val, callback);
}

int  VerifyMarketingName(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyMarketingName)(const char* addr, const char* val, void* callback);
	pVerifyMarketingName VerifyMarketingName_h = (pVerifyMarketingName)GetProcAddress(handleLibVerifyCustomization, "VerifyMarketingName");
	return	VerifyMarketingName_h(addr, val, callback);
}

int  VerifyBenchmarkFlag(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyBenchmarkFlag)(const char* addr, const char* val, void* callback);
	pVerifyBenchmarkFlag VerifyBenchmarkFlag_h = (pVerifyBenchmarkFlag)GetProcAddress(handleLibVerifyCustomization, "VerifyBenchmarkFlag");
	return	VerifyBenchmarkFlag_h(addr, val, callback);
}

int  VerifyAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback) {
	typedef  int  (*pVerifyAttestationIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
	pVerifyAttestationIDS VerifyAttestationIDS_h = (pVerifyAttestationIDS)GetProcAddress(handleLibVerifyCustomization, "VerifyAttestationIDS");
	return	VerifyAttestationIDS_h(addr, ids, sn, meid, imei1, imei2, callback);
}

int  VerifyKeyAttestation(const char* addr, const char* keyVD, void* callback) {
	typedef  int  (*pVerifyKeyAttestation)(const char* addr, const char* keyVD, void* callback);
	pVerifyKeyAttestation VerifyKeyAttestation_h = (pVerifyKeyAttestation)GetProcAddress(handleLibVerifyCustomization, "VerifyKeyAttestation");
	return	VerifyKeyAttestation_h(addr, keyVD, callback);
}

int  VerifyTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback) {
	typedef  int  (*pVerifyTrustDeviceIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
	pVerifyTrustDeviceIDS VerifyTrustDeviceIDS_h = (pVerifyTrustDeviceIDS)GetProcAddress(handleLibVerifyCustomization, "VerifyTrustDeviceIDS");
	return	VerifyTrustDeviceIDS_h(addr, ids, sn, meid, imei1, imei2, callback);
}

int  VerifyDeviceCerts(const char* addr, const char* Hw_Device_Certs_VD, void* callback) {
	typedef  int  (*pVerifyDeviceCerts)(const char* addr, const char* Hw_Device_Certs_VD, void* callback);
	pVerifyDeviceCerts VerifyDeviceCerts_h = (pVerifyDeviceCerts)GetProcAddress(handleLibVerifyCustomization, "VerifyDeviceCerts");
	return	VerifyDeviceCerts_h(addr, Hw_Device_Certs_VD, callback);
}

int VerifyAccLock(const char* addr, const char* nckDiagUnlock, void* callback) {
	typedef  int (*pVerifyAccLock)(const char* addr, const char* nckDiagUnlock, void* callback);
	pVerifyAccLock VerifyAccLock_h = (pVerifyAccLock)GetProcAddress(handleLibVerifyCustomization, "VerifyAccLock");
	return	VerifyAccLock_h(addr, nckDiagUnlock, callback);
}

int  VerifyUserLock(const char* addr, const char* lockType, void* callback) {
	typedef  int  (*pVerifyUserLock)(const char* addr, const char* lockType, void* callback);
	pVerifyUserLock VerifyUserLock_h = (pVerifyUserLock)GetProcAddress(handleLibVerifyCustomization, "VerifyUserLock");
	return	VerifyUserLock_h(addr, lockType, callback);
}

int  VerifyFrpKey(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyFrpKey)(const char* addr, const char* val, void* callback);
	pVerifyFrpKey VerifyFrpKey_h = (pVerifyFrpKey)GetProcAddress(handleLibVerifyCustomization, "VerifyFrpKey");
	return	VerifyFrpKey_h(addr, val, callback);
}

int  VerifyEmmcID(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyEmmcID)(const char* addr, const char* val, void* callback);
	pVerifyEmmcID VerifyEmmcID_h = (pVerifyEmmcID)GetProcAddress(handleLibVerifyCustomization, "VerifyEmmcID");
	return	VerifyEmmcID_h(addr, val, callback);
}

int  VerifyPublicKey(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyPublicKey)(const char* addr, const char* val, void* callback);
	pVerifyPublicKey VerifyPublicKey_h = (pVerifyPublicKey)GetProcAddress(handleLibVerifyCustomization, "VerifyPublicKey");
	return	VerifyPublicKey_h(addr, val, callback);
}

int  VerifyBarcode(const char* addr, const char* val, void* callback) {
	typedef  int  (*pVerifyBarcode)(const char* addr, const char* val, void* callback);
	pVerifyBarcode VerifyBarcode_h = (pVerifyBarcode)GetProcAddress(handleLibVerifyCustomization, "VerifyBarcode");
	return	VerifyBarcode_h(addr, val, callback);
}

int  WriteRSN(const char* addr, const char* val, void* callback) {
	typedef  int  (*pWriteRSN)(const char* addr, const char* val, void* callback);
	pWriteRSN WriteRSN_h = (pWriteRSN)GetProcAddress(handleLibWriteCustomization, "WriteRSN");
	return	WriteRSN_h(addr, val, callback);
}

int  WriteCPL(const char* addr, const char* cpl, void* callback) {
	typedef  int  (*pWriteCPL)(const char* addr, const char* val, void* callback);
	pWriteCPL WriteCPL_h = (pWriteCPL)GetProcAddress(handleLibWriteCustomization, "WriteCPL");
	return	WriteCPL_h(addr, cpl, callback);
}
int  WriteSecretType(const char* addr, const char* val, void* callback) {
	typedef  int  (*pWriteSecretType)(const char* addr, const char* val, void* callback);
	pWriteSecretType WriteSecretType_h = (pWriteSecretType)GetProcAddress(handleLibWriteCustomization, "WriteSecretType");
	return	WriteSecretType_h(addr, val, callback);
}

int  WriteCertifyCode(const char* addr, const char* val, void* callback) {
	typedef  int  (*pWriteCertifyCode)(const char* addr, const char* val, void* callback);
	pWriteCertifyCode WriteCertifyCode_h = (pWriteCertifyCode)GetProcAddress(handleLibWriteCustomization, "WriteCertifyCode");
	return	WriteCertifyCode_h(addr, val, callback);
}

int  WriteMarketingName(const char* addr, const char* val, void* callback) {
	typedef  int  (*pWriteMarketingName)(const char* addr, const char* val, void* callback);
	pWriteMarketingName WriteMarketingName_h = (pWriteMarketingName)GetProcAddress(handleLibWriteCustomization, "WriteMarketingName");
	return	WriteMarketingName_h(addr, val, callback);
}

int  WriteBenchmarkFlag(const char* addr, const char* val, void* callback) {
	typedef  int  (*pWriteBenchmarkFlag)(const char* addr, const char* val, void* callback);
	pWriteBenchmarkFlag WriteBenchmarkFlag_h = (pWriteBenchmarkFlag)GetProcAddress(handleLibWriteCustomization, "WriteBenchmarkFlag");
	return	WriteBenchmarkFlag_h(addr, val, callback);
}

int  WriteAttestationIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback) {
	typedef  int  (*pWriteAttestationIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
	pWriteAttestationIDS WriteAttestationIDS_h = (pWriteAttestationIDS)GetProcAddress(handleLibWriteCustomization, "WriteAttestationIDS");
	return	WriteAttestationIDS_h(addr, ids, sn, meid, imei1, imei2, callback);
}

int  WriteKeyAttestation(const char* addr, const char* key1, const char* key2, const char* key3, const char* key4, void* callback) {
	typedef  int  (*pWriteKeyAttestation)(const char* addr, const char* key1, const char* key2, const char* key3, const char* key4, void* callback);
	pWriteKeyAttestation WriteKeyAttestation_h = (pWriteKeyAttestation)GetProcAddress(handleLibWriteCustomization, "WriteKeyAttestation");
	return	WriteKeyAttestation_h(addr, key1, key2, key3, key4, callback);
}

int  WriteTrustDeviceIDS(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback) {
	typedef  int  (*pWriteTrustDeviceIDS)(const char* addr, const char* ids, const char* sn, const char* meid, const char* imei1, const char* imei2, void* callback);
	pWriteTrustDeviceIDS WriteTrustDeviceIDS_h = (pWriteTrustDeviceIDS)GetProcAddress(handleLibWriteCustomization, "WriteTrustDeviceIDS");
	return	WriteTrustDeviceIDS_h(addr, ids, sn, meid, imei1, imei2, callback);
}

int  WriteDeviceCerts(const char* addr, const char* cert1, const char* cert2, const char* cert3, const char* cert4, const char* cert5, void* callback) {
	typedef  int  (*pWriteDeviceCerts)(const char* addr, const char* cert1, const char* cert2, const char* cert3, const char* cert4, const char* cert5, void* callback);
	pWriteDeviceCerts WriteDeviceCerts_h = (pWriteDeviceCerts)GetProcAddress(handleLibWriteCustomization, "WriteDeviceCerts");
	return	WriteDeviceCerts_h(addr, cert1, cert2, cert3, cert4, cert5, callback);
}

int NVBackup(const char* addr, void* callback)
{
	typedef int  (*pNVBackup)(const char* addr, void* callback);
	pNVBackup NVBackup_h = (pNVBackup)GetProcAddress(handleLibCustomizationKeyAction, "NVBackup");
	return NVBackup_h(addr, callback);
}

int  ReadSubBoardFlag(const char* addr, char* boardFlag, int size, void* callback) {
	typedef  int  (*pReadSubBoardFlag)(const char* addr, char* boardFlag, int size, void* callback);
	pReadSubBoardFlag ReadSubBoardFlag_h = (pReadSubBoardFlag)GetProcAddress(handleLibCustomizationKeyAction, "ReadSubBoardFlag");
	return	ReadSubBoardFlag_h(addr, boardFlag, size, callback);
}

int CheckMode(const char* addr, void* callback) {
	typedef  int (*pCheckMode)(const char* addr, void* callback);
	pCheckMode CheckMode_h = (pCheckMode)GetProcAddress(handleLibCustomizationKeyAction, "CheckMode");
	return	CheckMode_h(addr, callback);
}

int SetMMI2AutoRunFlag(const char* addr, void* dog, int keyID, const char hun[8], bool isQualPlat, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int (*pSetMMI2AutoRunFlag)(const char* addr, void* dog, int keyID, const char hun[8], bool isQualPlat, void* callback);
	pSetMMI2AutoRunFlag SetMMI2AutoRunFlag_h = (pSetMMI2AutoRunFlag)GetProcAddress(handleLibCustomizationKeyAction, "SetMMI2AutoRunFlag");
	return	SetMMI2AutoRunFlag_h(addr, dog, keyID, hun, isQualPlat, callback);
}

int  CheckMMI2AutoRunFlagClear(const char* addr, void* callback) {
	typedef  int  (*pCheckMMI2AutoRunFlagClear)(const char* addr, void* callback);
	pCheckMMI2AutoRunFlagClear CheckMMI2AutoRunFlagClear_h = (pCheckMMI2AutoRunFlagClear)GetProcAddress(handleLibCustomizationKeyAction, "CheckMMI2AutoRunFlagClear");
	return	CheckMMI2AutoRunFlagClear_h(addr, callback);
}

int  MtkCheckSimTray(const char* addr, void* callback) {
	typedef  int  (*pMtkCheckSimTray)(const char* addr, void* callback);
	pMtkCheckSimTray MtkCheckSimTray_h = (pMtkCheckSimTray)GetProcAddress(handleLibCustomizationKeyAction, "MtkCheckSimTray");
	return	MtkCheckSimTray_h(addr, callback);
}

int  ErasePowerOnTime(const char* addr, void* callback) {
	typedef  int  (*pErasePowerOnTime)(const char* addr, void* callback);
	pErasePowerOnTime ErasePowerOnTime_h = (pErasePowerOnTime)GetProcAddress(handleLibCustomizationKeyAction, "ErasePowerOnTime");
	return	ErasePowerOnTime_h(addr, callback);
}

int  SetFactoryVer(const char* addr, void* callback) {
	typedef  int  (*pSetFactoryVer)(const char* addr, void* callback);
	pSetFactoryVer SetFactoryVer_h = (pSetFactoryVer)GetProcAddress(handleLibCustomizationKeyAction, "SetFactoryVer");
	return	SetFactoryVer_h(addr, callback);
}

int  CheckFactoryVer(const char* addr, void* callback) {
	typedef  int  (*pCheckFactoryVer)(const char* addr, void* callback);
	pCheckFactoryVer CheckFactoryVer_h = (pCheckFactoryVer)GetProcAddress(handleLibCustomizationKeyAction, "CheckFactoryVer");
	return	CheckFactoryVer_h(addr, callback);
}

int  CheckUTFlag(const char* addr, void* callback) {
	typedef  int  (*pCheckUTFlag)(const char* addr, void* callback);;
	pCheckUTFlag CheckUTFlag_h = (pCheckUTFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckUTFlag");
	return	CheckUTFlag_h(addr, callback);;
}

int  CheckPTFlag(const char* addr, void* callback) {
	typedef  int  (*pCheckPTFlag)(const char* addr, void* callback);
	pCheckPTFlag CheckPTFlag_h = (pCheckPTFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckPTFlag");
	return	CheckPTFlag_h(addr, callback);
}

int  ReadSoftwareVer(const char* addr, const char* stationFlag, char* softVerInfo, int size, void* callback) {
	typedef  int  (*pReadSoftwareVer)(const char* addr, const char* stationFlag, char* softVerInfo, int size, void* callback);
	pReadSoftwareVer ReadSoftwareVer_h = (pReadSoftwareVer)GetProcAddress(handleLibCustomizationKeyAction, "ReadSoftwareVer");
	return	ReadSoftwareVer_h(addr, stationFlag, softVerInfo, size, callback);
}

int  ReadSDCardState(const char* addr, int& sdCardState, void* callback) {
	typedef  int  (*pReadSDCardState)(const char* addr, int& sdCardState, void* callback);
	pReadSDCardState ReadSDCardState_h = (pReadSDCardState)GetProcAddress(handleLibCustomizationKeyAction, "ReadSDCardState");
	return	ReadSDCardState_h(addr, sdCardState, callback);
}
int  ReadSIMCardState(const char* addr, int& simCardState, void* callback) {
	typedef  int  (*pReadSIMCardState)(const char* addr, int& sdCardState, void* callback);
	pReadSIMCardState ReadSIMCardState_h = (pReadSIMCardState)GetProcAddress(handleLibCustomizationKeyAction, "ReadSIMCardState");
	return	ReadSIMCardState_h(addr, simCardState, callback);
}
int  ReadBoardId(const char* addr, char* strBoardId, int size, void* callback) {
	typedef  int  (*pReadBoardId)(const char* addr, char* strBoardId, int size, void* callback);
	pReadBoardId ReadBoardId_h = (pReadBoardId)GetProcAddress(handleLibCustomizationKeyAction, "ReadBoardId");
	return	ReadBoardId_h(addr, strBoardId, size, callback);
}

int  ReadMaintenance(const char* addr, const char* testItem, int size, void* callback) {
	typedef  int  (*pReadMaintenance)(const char* addr, const char* testItem, int size, void* callback);
	pReadMaintenance ReadMaintenance_h = (pReadMaintenance)GetProcAddress(handleLibCustomizationKeyAction, "ReadMaintenance");
	return	ReadMaintenance_h(addr, testItem, size, callback);
}

int  EraseAccount(const char* addr, void* dog, int keyID, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pEraseAccount)(const char* addr, void* dog, int keyID, void* callback);
	pEraseAccount EraseAccount_h = (pEraseAccount)GetProcAddress(handleLibCustomizationKeyAction, "EraseAccount");
	return	EraseAccount_h(addr, dog, keyID, callback);
}

int  EraseCustInfo(const char* addr, void* dog, int keyID, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pEraseCustInfo)(const char* addr, void* dog, int keyID, void* callback);
	pEraseCustInfo EraseCustInfo_h = (pEraseCustInfo)GetProcAddress(handleLibCustomizationKeyAction, "EraseCustInfo");
	return	EraseCustInfo_h(addr, dog, keyID, callback);
}

int StopAutoCharge(const char* addr, void* callback) {
	typedef  int (*pStopAutoCharge)(const char* addr, void* callback);
	pStopAutoCharge StopAutoCharge_h = (pStopAutoCharge)GetProcAddress(handleLibCustomizationKeyAction, "StopAutoCharge");
	return	StopAutoCharge_h(addr, callback);
}

int StartAutoCharge(const char* addr, void* callback) {
	typedef  int (*pStartAutoCharge)(const char* addr, void* callback);
	pStartAutoCharge StartAutoCharge_h = (pStartAutoCharge)GetProcAddress(handleLibCustomizationKeyAction, "StartAutoCharge");
	return	StartAutoCharge_h(addr, callback);
}

int  ReadBatteryPower(const char* addr, int& value, void* callback) {
	typedef  int  (*pReadBatteryPower)(const char* addr, int& value, void* callback);
	pReadBatteryPower ReadBatteryPower_h = (pReadBatteryPower)GetProcAddress(handleLibCustomizationKeyAction, "ReadBatteryPower");
	return	ReadBatteryPower_h(addr, value, callback);
}

int  SetCWFlag(const char* addr, const char* CWflag, void* callback) {
	typedef  int  (*pSetCWFlag)(const char* addr, const char* CWflag, void* callback);
	pSetCWFlag SetCWFlag_h = (pSetCWFlag)GetProcAddress(handleLibCustomizationKeyAction, "SetCWFlag");
	return	SetCWFlag_h(addr, CWflag, callback);
}

int  CheckCWFlag(const char* addr, const char* CWflag, void* callback) {
	typedef  int  (*pCheckCWFlag)(const char* addr, const char* CWflag, void* callback);
	pCheckCWFlag CheckCWFlag_h = (pCheckCWFlag)GetProcAddress(handleLibCustomizationKeyAction, "CheckCWFlag");
	return	CheckCWFlag_h(addr, CWflag, callback);
}

int  SDUpdate(const char* addr, void* callback) {
	typedef  int  (*pSDUpdate)(const char* addr, void* callback);
	pSDUpdate SDUpdate_h = (pSDUpdate)GetProcAddress(handleLibCustomizationKeyAction, "SDUpdate");
	return	SDUpdate_h(addr, callback);
}

int  ReadMMIFlag(const char* addr, char* MMIFlagList, int size, void* callback) {
	typedef  int  (*pReadMMIFlag)(const char* addr, char* MMIFlagList, int size, void* callback);
	pReadMMIFlag ReadMMIFlag_h = (pReadMMIFlag)GetProcAddress(handleLibCustomizationKeyAction, "ReadMMIFlag");
	return	ReadMMIFlag_h(addr, MMIFlagList, size, callback);
}

int  CheckRoot(const char* addr, void* callback) {
	typedef  int  (*pCheckRoot)(const char* addr, void* callback);
	pCheckRoot CheckRoot_h = (pCheckRoot)GetProcAddress(handleLibCustomizationKeyAction, "CheckRoot");
	return	CheckRoot_h(addr, callback);
}

int  FactoryReset(const char* addr, void* callback) {
	typedef  int  (*pFactoryReset)(const char* addr, void* callback);
	pFactoryReset FactoryReset_h = (pFactoryReset)GetProcAddress(handleLibCustomizationKeyAction, "FactoryReset");
	return	FactoryReset_h(addr, callback);
}

int  FactoryResetCW(const char* addr, void* callback) {
	typedef  int  (*pFactoryResetCW)(const char* addr, void* callback);
	pFactoryResetCW FactoryResetCW_h = (pFactoryResetCW)GetProcAddress(handleLibCustomizationKeyAction, "FactoryResetCW");
	return	FactoryResetCW_h(addr, callback);
}

int  FactoryResetForDemo(const char* addr, void* callback) {
	typedef  int  (*pFactoryResetForDemo)(const char* addr, void* callback);
	pFactoryResetForDemo FactoryResetForDemo_h = (pFactoryResetForDemo)GetProcAddress(handleLibCustomizationKeyAction, "FactoryResetForDemo");
	return	FactoryResetForDemo_h(addr, callback);
}

int  CheckFactoryResetFinished(const char* addr, int timeOut, void* callback) {
	typedef  int  (*pCheckFactoryResetFinished)(const char* addr, int timeOut, void* callback);
	pCheckFactoryResetFinished CheckFactoryResetFinished_h = (pCheckFactoryResetFinished)GetProcAddress(handleLibCustomizationKeyAction, "CheckFactoryResetFinished");
	return	CheckFactoryResetFinished_h(addr, timeOut, callback);
}

int  EnableRetread(const char* addr, void* callback) {
	typedef  int  (*pEnableRetread)(const char* addr, void* callback);
	pEnableRetread EnableRetread_h = (pEnableRetread)GetProcAddress(handleLibCustomizationKeyAction, "EnableRetread");
	return	EnableRetread_h(addr, callback);
}

int  RestartDevice(const char* addr, void* callback) {
	typedef  int  (*pRestartDevice)(const char* addr, void* callback);
	pRestartDevice RestartDevice_h = (pRestartDevice)GetProcAddress(handleLibCustomizationKeyAction, "RestartDevice");
	return	RestartDevice_h(addr, callback);
}

int  DeleteSoftwareLog(const char* addr, void* callback) {
	typedef  int  (*pDeleteSoftwareLog)(const char* addr, void* callback);
	pDeleteSoftwareLog DeleteSoftwareLog_h = (pDeleteSoftwareLog)GetProcAddress(handleLibCustomizationKeyAction, "DeleteSoftwareLog");
	return	DeleteSoftwareLog_h(addr, callback);
}

int  QualCheckNV453(const char* addr, void* callback) {
	typedef  int  (*pQualCheckNV453)(const char* addr, void* callback);
	pQualCheckNV453 QualCheckNV453_h = (pQualCheckNV453)GetProcAddress(handleLibCustomizationKeyAction, "QualCheckNV453");
	return	QualCheckNV453_h(addr, callback);
}

int  QualCheckRWFlag(const char* addr, void* callback) {
	typedef  int  (*pQualCheckRWFlag)(const char* addr, void* callback);
	pQualCheckRWFlag QualCheckRWFlag_h = (pQualCheckRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualCheckRWFlag");
	return	QualCheckRWFlag_h(addr, callback);
}

int  QualDelLogbat(const char* addr, void* callback) {
	typedef  int  (*pQualDelLogbat)(const char* addr, void* callback);
	pQualDelLogbat QualDelLogbat_h = (pQualDelLogbat)GetProcAddress(handleLibCustomizationKeyAction, "QualDelLogbat");
	return	QualDelLogbat_h(addr, callback);
}

int  WriteOptimizeFlag(const char* addr, const char* optimizeMode, const char* optimizeValue, void* callback) {
	typedef  int  (*pWriteOptimizeFlag)(const char* addr, const char* optimizeMode, const char* optimizeValue, void* callback);
	pWriteOptimizeFlag WriteOptimizeFlag_h = (pWriteOptimizeFlag)GetProcAddress(handleLibCustomizationKeyAction, "WriteOptimizeFlag");
	return	WriteOptimizeFlag_h(addr, optimizeMode, optimizeValue, callback);
}

int  EraseOEMPhyNum(const char* addr, void* dog, int keyID, void* callback) {
	//std::lock_guard<std::mutex> m(g_mutex);
	typedef  int  (*pEraseOEMPhyNum)(const char* addr, void* dog, int keyID, void* callback);
	pEraseOEMPhyNum EraseOEMPhyNum_h = (pEraseOEMPhyNum)GetProcAddress(handleLibCustomizationKeyAction, "EraseOEMPhyNum");
	return	EraseOEMPhyNum_h(addr, dog, keyID, callback);
}

int  QualSetNRWFlag(const char* addr, void* callback) {
	typedef  int  (*pQualSetNRWFlag)(const char* addr, void* callback);
	pQualSetNRWFlag QualSetNRWFlag_h = (pQualSetNRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualSetNRWFlag");
	return	QualSetNRWFlag_h(addr, callback);
}

int  QualRebootModem(const char* addr, void* callback) {
	typedef  int  (*pQualRebootModem)(const char* addr, void* callback);
	pQualRebootModem QualRebootModem_h = (pQualRebootModem)GetProcAddress(handleLibCustomizationKeyAction, "QualRebootModem");
	return	QualRebootModem_h(addr, callback);
}

int  QualEraseNRWFlag(const char* addr, void* callback) {
	typedef  int  (*pQualEraseNRWFlag)(const char* addr, void* callback);
	pQualEraseNRWFlag QualEraseNRWFlag_h = (pQualEraseNRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualEraseNRWFlag");
	return	QualEraseNRWFlag_h(addr, callback);
}

int  QualSetDutOffline(const char* addr, void* callback) {
	typedef  int  (*pQualSetDutOffline)(const char* addr, void* callback);
	pQualSetDutOffline QualSetDutOffline_h = (pQualSetDutOffline)GetProcAddress(handleLibCustomizationKeyAction, "QualSetDutOffline");
	return	QualSetDutOffline_h(addr, callback);
}

int  QualCheckOnlineAndSetOffline(const char* addr, void* callback) {
	typedef  int  (*pQualCheckOnlineAndSetOffline)(const char* addr, void* callback);
	pQualCheckOnlineAndSetOffline QualCheckOnlineAndSetOffline_h = (pQualCheckOnlineAndSetOffline)GetProcAddress(handleLibCustomizationKeyAction, "QualCheckOnlineAndSetOffline");
	return	QualCheckOnlineAndSetOffline_h(addr, callback);
}

int  QualEraseModem(const char* addr, void* callback) {
	typedef  int  (*pQualEraseModem)(const char* addr, void* callback);
	pQualEraseModem QualEraseModem_h = (pQualEraseModem)GetProcAddress(handleLibCustomizationKeyAction, "QualEraseModem");
	return	QualEraseModem_h(addr, callback);
}

int  QualEraseCPPhyNum(const char* addr, void* callback) {
	typedef  int  (*pQualEraseCPPhyNum)(const char* addr, void* callback);
	pQualEraseCPPhyNum QualEraseCPPhyNum_h = (pQualEraseCPPhyNum)GetProcAddress(handleLibCustomizationKeyAction, "QualEraseCPPhyNum");
	return	QualEraseCPPhyNum_h(addr, callback);
}

int  CheckBootState(const char* addr, int timeout, void* callback) {
	typedef  int  (*pCheckBootState)(const char* addr, int timeout, void* callback);
	pCheckBootState CheckBootState_h = (pCheckBootState)GetProcAddress(handleLibCustomizationKeyAction, "CheckBootState");
	return	CheckBootState_h(addr, timeout, callback);
}

int  QualGoldenCopy(const char* addr, void* callback) {
	typedef  int  (*pQualGoldenCopy)(const char* addr, void* callback);
	pQualGoldenCopy QualGoldenCopy_h = (pQualGoldenCopy)GetProcAddress(handleLibCustomizationKeyAction, "QualGoldenCopy");
	return	QualGoldenCopy_h(addr, callback);
}

int  QualGetNRWFlag(const char* addr, int& NRWFlag, void* callback) {
	typedef  int  (*pQualGetNRWFlag)(const char* addr, int& NRWFlag, void* callback);
	pQualGetNRWFlag QualGetNRWFlag_h = (pQualGetNRWFlag)GetProcAddress(handleLibCustomizationKeyAction, "QualGetNRWFlag");
	return	QualGetNRWFlag_h(addr, NRWFlag, callback);
}

int  CheckSimSlot(const char* addr, void* callback) {
	typedef  int  (*pCheckSimSlot)(const char* addr, void* callback);
	pCheckSimSlot CheckSimSlot_h = (pCheckSimSlot)GetProcAddress(handleLibCustomizationKeyAction, "CheckSimSlot");
	return	CheckSimSlot_h(addr, callback);
}

int  QualNVEMMCSync(const char* addr, void* callback) {
	typedef  int  (*pQualNVEMMCSync)(const char* addr, void* callback);
	pQualNVEMMCSync QualNVEMMCSync_h = (pQualNVEMMCSync)GetProcAddress(handleLibCustomizationKeyAction, "QualNVEMMCSync");
	return	QualNVEMMCSync_h(addr, callback);
}

int  QualWriteNVItem(const char* addr, uint16_t nvid, void* callback) {
	typedef  int  (*pQualWriteNVItem)(const char* addr, uint16_t nvid, void* callback);
	pQualWriteNVItem QualWriteNVItem_h = (pQualWriteNVItem)GetProcAddress(handleLibCustomizationKeyAction, "QualWriteNVItem");
	return	QualWriteNVItem_h(addr, nvid, callback);
}

int  ReadUDID(const char* addr, char* buff, int size, void* callback) {
	typedef  int  (*pReadUDID)(const char* addr, char* buff, int size, void* callback);
	pReadUDID ReadUDID_h = (pReadUDID)GetProcAddress(handleLibReadCustomization, "ReadUDID");
	return	ReadUDID_h(addr, buff, size, callback);
}

int  ReadEmmcID(const char* addr, char* buff, int size, void* callback) {
	typedef  int  (*pReadEmmcID)(const char* addr, char* buff, int size, void* callback);
	pReadEmmcID ReadEmmcID_h = (pReadEmmcID)GetProcAddress(handleLibReadCustomization, "ReadEmmcID");
	return	ReadEmmcID_h(addr, buff, size, callback);
}

int  ReadPublicKey(const char* addr, char* buff, int size, void* callback) {
	typedef  int  (*pReadPublicKey)(const char* addr, char* buff, int size, void* callback);
	pReadPublicKey ReadPublicKey_h = (pReadPublicKey)GetProcAddress(handleLibReadCustomization, "ReadPublicKey");
	return	ReadPublicKey_h(addr, buff, size, callback);
}

int  CreatePublicKey(const char* addr, void* callback) {
	typedef  int  (*pCreatePublicKey)(const char* addr, void* callback);
	pCreatePublicKey CreatePublicKey_h = (pCreatePublicKey)GetProcAddress(handleLibReadCustomization, "CreatePublicKey");
	return	CreatePublicKey_h(addr, callback);
}

int  ReadBarcode(const char* addr, char* buff, int size, void* callback) {
	typedef  int  (*pReadBarcode)(const char* addr, char* buff, int size, void* callback);
	pReadBarcode ReadBarcode_h = (pReadBarcode)GetProcAddress(handleLibReadCustomization, "ReadBarcode");
	return	ReadBarcode_h(addr, buff, size, callback);
}

int  ReadRunMode(const char* addr, char* buff, int size, void* callback) {
	typedef  int  (*pReadRunMode)(const char* addr, char* buff, int size, void* callback);
	pReadRunMode ReadRunMode_h = (pReadRunMode)GetProcAddress(handleLibReadCustomization, "ReadRunMode");
	return	ReadRunMode_h(addr, buff, size, callback);
}

int  ReadSN(const char* addr, char* data, int size, void* callback) {
	typedef  int  (*pReadSN)(const char* addr, char* data, int size, void* callback);
	pReadSN ReadSN_h = (pReadSN)GetProcAddress(handleLibReadCustomization, "ReadSN");
	return	ReadSN_h(addr, data, size, callback);
}

