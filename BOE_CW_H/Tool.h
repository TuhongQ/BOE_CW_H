#pragma once
#include "windows.h"
#include "wincrypt.h"
#include "string"
#include "iostream"
#include "vector"
#include <io.h>
#include <list>
#include <direct.h>
#include <algorithm>
#include <chrono>
#include "ajson.hpp"
#include <map>
#include "libxls/include/xls.h"

#include "cryptlib.h"
#include "aes.h"
#include "osrng.h"
#include "modes.h"
#include "base64.h"
#include "files.h"
#include "filters.h"
#include "default.h"
#include "hex.h"
#include "rsa.h"
#include "randpool.h"

using namespace std;
using namespace CryptoPP;

#if _DEBUG
#pragma comment(lib,"cryptlib/Debug/cryptlib.lib")
#else
#pragma comment(lib,"cryptlib/Release/cryptlib.lib")
#endif // _DEBUG


#pragma comment(lib,"libiconv/lib/libiconv.lib")
#include "libxls/include/xls.h"
#pragma comment(lib,"libxls.lib")

//#using "../MES/BOE.MesInterface.dll"
//#include <vcclr.h>
//#include <msclr/marshal_cppstd.h>
//#include <msclr/marshal.h>
//using namespace System;
using namespace std;

#pragma region
const unsigned short crctab16[] =
{
	0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
	0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
	0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
	0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
	0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
	0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
	0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
	0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
	0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
	0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
	0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
	0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
	0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
	0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
	0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
	0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
	0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
	0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
	0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
	0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
	0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
	0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
	0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
	0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
	0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
	0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
	0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
	0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
	0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
	0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
	0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
	0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};
///modbus
const unsigned short crc16_ccitt_table[256] =
{
	0x0000, 0xc0c1, 0xc181, 0x0140, 0xc301, 0x03c0, 0x0280, 0xc241,
	0xc601, 0x06c0, 0x0780, 0xc741, 0x0500, 0xc5c1, 0xc481, 0x0440,
	0xcc01, 0x0cc0, 0x0d80, 0xcd41, 0x0f00, 0xcfc1, 0xce81, 0x0e40,
	0x0a00, 0xcac1, 0xcb81, 0x0b40, 0xc901, 0x09c0, 0x0880, 0xc841,
	0xd801, 0x18c0, 0x1980, 0xd941, 0x1b00, 0xdbc1, 0xda81, 0x1a40,
	0x1e00, 0xdec1, 0xdf81, 0x1f40, 0xdd01, 0x1dc0, 0x1c80, 0xdc41,
	0x1400, 0xd4c1, 0xd581, 0x1540, 0xd701, 0x17c0, 0x1680, 0xd641,
	0xd201, 0x12c0, 0x1380, 0xd341, 0x1100, 0xd1c1, 0xd081, 0x1040,
	0xf001, 0x30c0, 0x3180, 0xf141, 0x3300, 0xf3c1, 0xf281, 0x3240,
	0x3600, 0xf6c1, 0xf781, 0x3740, 0xf501, 0x35c0, 0x3480, 0xf441,
	0x3c00, 0xfcc1, 0xfd81, 0x3d40, 0xff01, 0x3fc0, 0x3e80, 0xfe41,
	0xfa01, 0x3ac0, 0x3b80, 0xfb41, 0x3900, 0xf9c1, 0xf881, 0x3840,
	0x2800, 0xe8c1, 0xe981, 0x2940, 0xeb01, 0x2bc0, 0x2a80, 0xea41,
	0xee01, 0x2ec0, 0x2f80, 0xef41, 0x2d00, 0xedc1, 0xec81, 0x2c40,
	0xe401, 0x24c0, 0x2580, 0xe541, 0x2700, 0xe7c1, 0xe681, 0x2640,
	0x2200, 0xe2c1, 0xe381, 0x2340, 0xe101, 0x21c0, 0x2080, 0xe041,
	0xa001, 0x60c0, 0x6180, 0xa141, 0x6300, 0xa3c1, 0xa281, 0x6240,
	0x6600, 0xa6c1, 0xa781, 0x6740, 0xa501, 0x65c0, 0x6480, 0xa441,
	0x6c00, 0xacc1, 0xad81, 0x6d40, 0xaf01, 0x6fc0, 0x6e80, 0xae41,
	0xaa01, 0x6ac0, 0x6b80, 0xab41, 0x6900, 0xa9c1, 0xa881, 0x6840,
	0x7800, 0xb8c1, 0xb981, 0x7940, 0xbb01, 0x7bc0, 0x7a80, 0xba41,
	0xbe01, 0x7ec0, 0x7f80, 0xbf41, 0x7d00, 0xbdc1, 0xbc81, 0x7c40,
	0xb401, 0x74c0, 0x7580, 0xb541, 0x7700, 0xb7c1, 0xb681, 0x7640,
	0x7200, 0xb2c1, 0xb381, 0x7340, 0xb101, 0x71c0, 0x7080, 0xb041,
	0x5000, 0x90c1, 0x9181, 0x5140, 0x9301, 0x53c0, 0x5280, 0x9241,
	0x9601, 0x56c0, 0x5780, 0x9741, 0x5500, 0x95c1, 0x9481, 0x5440,
	0x9c01, 0x5cc0, 0x5d80, 0x9d41, 0x5f00, 0x9fc1, 0x9e81, 0x5e40,
	0x5a00, 0x9ac1, 0x9b81, 0x5b40, 0x9901, 0x59c0, 0x5880, 0x9841,
	0x8801, 0x48c0, 0x4980, 0x8941, 0x4b00, 0x8bc1, 0x8a81, 0x4a40,
	0x4e00, 0x8ec1, 0x8f81, 0x4f40, 0x8d01, 0x4dc0, 0x4c80, 0x8c41,
	0x4400, 0x84c1, 0x8581, 0x4540, 0x8701, 0x47c0, 0x4680, 0x8641,
	0x8201, 0x42c0, 0x4380, 0x8341, 0x4100, 0x81c1, 0x8081, 0x4040
};

//************************************
  // Method:    strToHex 十六进制字符串转16进制
  // FullName:  CommUtil::strToHex
  // Access:    public 
  // Returns:   int XOR异或值
  // Qualifier:
  // Parameter: char * hexStr 十六进制字符串
  // Parameter: unsigned char * outData 存储16进制容器
  //************************************
int strToHex(char* hexStr, unsigned char* outData) {
	char* tmpStr = new char[strlen(hexStr)];
	strcpy(tmpStr, hexStr);
	char* res = strtok(tmpStr, " ");
	int tmpXor = 0x00;
	int i = 0;
	while (res != NULL) {
		int r = strtoull(res, NULL, 16);
		outData[i] = r;
		tmpXor ^= r;
		std::cout << res << "  " << r << " outData:" << ((int)outData[i]) << std::endl;
		i++;

		res = strtok(NULL, " ");
	}
	delete[]tmpStr;
	return tmpXor;
}
/**
 * 格式化字符串
 *
 * \param pszFmt 格式描述
 * \param ... 不定参数
 * \return 格式化的结果字符串
 */
std::string format(const char* pszFmt, ...)
{
	std::string str;
	va_list args;
	va_start(args, pszFmt);
	{
		int nLength = _vscprintf(pszFmt, args);
		nLength += 1;  //上面返回的长度是包含\0，这里加上
		std::vector<char> chars(nLength);
		_vsnprintf(chars.data(), nLength, pszFmt, args);
		str.assign(chars.data());
	}
	va_end(args);
	return str;
}
// CRCCal 消息处理程序

int Str2UnsignedChar(string s, unsigned char* h)//把cstring类型转换为byte[]类型
{
	char a[0x400 * 8];
	//_tcscpy((char *)a, s.GetBuffer(0));//vs2012 使用新函数
	strcpy_s((char*)a, sizeof(a) / sizeof(a[0]), s.c_str());


	size_t i;
	size_t l;
	int count = 0;
	char c, x;

	l = strlen(a);

	for (i = 0; i < l; i++)
	{
		c = a[i];
		if (c >= '0' && c <= '9')
		{
			x = c - '0';
		}
		else if (c >= 'a' && c <= 'f')
		{
			x = c - 'a' + 10;
		}
		else if (c >= 'A' && c <= 'F')
		{
			x = c - 'A' + 10;
		}
		else
		{
			continue;
		}
		if (!(count % 2))
		{
			h[count / 2] = (x << 4);
		}
		else
		{
			h[count / 2] |= x;
		}
		count++;
	}
	return count / 2;
}

unsigned short CRCAlgorithmX25(unsigned char* buffer, int len)//crc函数得到10进制数
{
	if (buffer && len > 0)
	{
		unsigned short crc_value = 0xFFFF;
		while (len--)
		{
			crc_value = (crc_value >> 8) ^ crctab16[(crc_value ^ *buffer++) & 0xff];
			//crc_value = (crc_value >> 8) ^ crc16_ccitt_table[(crc_value ^ *buffer++) & 0xff];
		}
		return (unsigned short)(~crc_value & 0xffff);
	}
	return 0;
}

string TransByteToHexString(const unsigned char* data, int len)
{
	string result;
	if (nullptr == data || 0 == len){
		return result;
	}for (int i = 0; i < len; i++)
	{
		char tmp[8] = { 0 };
		sprintf_s(tmp, sizeof(tmp), "%02x", data[i]);
		result += string(tmp);
	}
	return result;
}
/// <summary>
/// 获取CRC 并且进行高低位转换后的值
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
string GetCRC16AndTransform(string strTest)
{
	//BOE_CB_ShowInfo(std::to_string(strTest.length()));
	int iLen = (strTest.length() + 1) / 3;
	//BOE_CB_ShowInfo(std::to_string(iLen));
	unsigned char* buff = (unsigned char*)malloc(iLen);
	Str2UnsignedChar(strTest, buff);
	auto crc = CRCAlgorithmX25(buff, iLen);
	auto strCRC = format("%04X", crc);
	strCRC = strCRC.substr(2, 2) + strCRC.substr(0, 2);
	free(buff);
	return strCRC;
}
#pragma endregion

// 加密
string encryptStr_ECB_AES(std::string sKey, string strPlainText)
{
	string outstr;
	//填key    
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);
	AES::Encryption aesEncryption((CryptoPP::byte*)key, AES::MAX_KEYLENGTH);
	ECB_Mode_ExternalCipher::Encryption ecbEncryption(aesEncryption);
	StreamTransformationFilter ecbEncryptor(ecbEncryption, new HexEncoder(new StringSink(outstr)));
	ecbEncryptor.Put((CryptoPP::byte*)strPlainText.c_str(), strlen(strPlainText.c_str()));
	ecbEncryptor.MessageEnd();
	return outstr;
}
// 解密
string decryptStr_ECB_AES(string sKey, string cipherText)
{
	std::string outstr;
	//填key  
	SecByteBlock key(AES::MAX_KEYLENGTH);
	memset(key, 0x30, key.size());
	sKey.size() <= AES::MAX_KEYLENGTH ? memcpy(key, sKey.c_str(), sKey.size()) : memcpy(key, sKey.c_str(), AES::MAX_KEYLENGTH);
	ECB_Mode<AES>::Decryption ecbDecryption((CryptoPP::byte*)key, AES::MAX_KEYLENGTH);
	HexDecoder decryptor(new StreamTransformationFilter(ecbDecryption, new StringSink(outstr)));
	decryptor.Put((CryptoPP::byte*)cipherText.c_str(), strlen(cipherText.c_str()));
	decryptor.MessageEnd();
	return outstr;
}

// 路径检查及创建 多级
int createDirectory(std::string path)
{
	int len = path.length();
	char tmpDirPath[256] = { 0 };
	int ret = 0;
	if (_access(path.c_str(), 0) == -1)
	{
		for (int i = 0; i < len; i++)
		{
			tmpDirPath[i] = path[i];
			if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
			{
				if (_access(tmpDirPath, 0) == -1)
				{
					ret = _mkdir(tmpDirPath);
					cout << "ret:" << ret << " path: " << tmpDirPath << endl;
				}
				else
				{
					ret = 0;
					cout << "_access(tmpDirPath, 0) != -1: " << tmpDirPath << endl;
				}
			}
		}
	}
	else
	{
		cout << "(_access(path.c_str(), 0) == -1) " << path << endl;
	}
	return ret;

}


unsigned char Char2Hex(unsigned char ucTemp)
{
	unsigned char ucRes = 0;
	if (ucTemp >= '0' && ucTemp <= '9')
	{
		ucRes = ucTemp - '0';
	}
	if (ucTemp >= 'a' && ucTemp <= 'f')
	{
		ucRes = ucTemp - 'a' + 10;
	}
	if (ucTemp >= 'A' && ucTemp <= 'F')
	{
		ucRes = ucTemp - 'A' + 10;
	}
	//cout << hex << (unsigned int)ucTemp << " " << hex << (unsigned int)ucRes << endl;
	return ucRes;
}

//字符转换成整形
int hex2int(char c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		return c - 'A' + 10;
	}
	else if ((c >= 'a') && (c <= 'z'))
	{
		return c - 'a' + 10;
	}
	else if ((c >= '0') && (c <= '9'))
	{
		return c - '0';
	}
}
//char* hexStr   传进来的16进制支付串  如："0010"
//int index      选择bit位 一共0-15
//正常返回0或1  执行失败返回-1
int DataCalute(char* hexStr, int index)
{
	//const char* hexStr = "0010";
	int data[32] = { 0 };
	int count = 0;

	for (int i = 0; i < strlen(hexStr); i += 2)
	{
		int high = hex2int(hexStr[i]);   //高四位
		int low = hex2int(hexStr[i + 1]); //低四位
		data[count++] = (high << 4) + low;
	}

	for (int i = 0; i < strlen(hexStr) / 2; i++)
	{
		printf("%d ", data[i]);
		cout << endl;
	}
	int bitdata = -1;
	if (index >= 0 && index <= 7)
	{
		bitdata = ((data[1] >> index) & 1);
		printf("取bit%d:%d ", index, bitdata);
		cout << endl;
	}
	else
	{
		int index2 = index - 8;//高位的排位
		bitdata = ((data[0] >> index2) & 1);
		printf("取bit%d:%d ", index, bitdata);
		cout << endl;
	}
	return bitdata;
}

string HexToString(string hexString)
{
	if (hexString.length() == 2)
	{
		cout << "Fun:HexToString  Len=2" << endl;
		unsigned char  cret = 0;
		if (hexString[0] == '0' && hexString[1] != '0')
			cret = Char2Hex(hexString[1]);
		else if (hexString[0] == '0' && hexString[1] == '0')
			cret = 0;
		else
			cret = Char2Hex(hexString[0]) + Char2Hex(hexString[1]);
		string sret = format("%d", cret);
		return sret;
	}
	else
	{
		cout << "Fun:HexToString  Len=" << hexString.length() << endl;
		string strRet = "";
		if (hexString.empty())
		{
			return strRet;
		}
		cout << "hexString not empty" << endl;
		unsigned char ucRes = 0;
		for (int i = 0; i < hexString.size(); i += 3)
		{
			ucRes = Char2Hex(hexString[i]) * 0x10 + Char2Hex(hexString[i + 1]);
			strRet += ucRes;
		}

		return strRet;
	}
}

int HexStrToInt(string hexStr)
{
	string upper;
	upper.resize(hexStr.size());
	std::transform(hexStr.begin(), hexStr.end(), upper.begin(), ::toupper);
	hexStr = upper;
	int temp;
	long long sum = 0;             //用long long防止结果过大
	for (int i = 0; i < hexStr.length(); i++)         //最后一位是'\0'，不用算进去
	{
		switch (hexStr.c_str()[i])
		{
		case 'A': temp = 10; break;
		case 'B': temp = 11; break;
		case 'C': temp = 12; break;
		case 'D': temp = 13; break;
		case 'E': temp = 14; break;
		case 'F': temp = 15; break;
		default: temp = hexStr.c_str()[i] - '0'; break;
		}
		sum = sum + temp * pow(16, hexStr.length() - 1 - i);
	}
	return sum;
}

void hexToBytes(const std::string& hex, BYTE* bytes,int byteSize)
{
	int bytelen = hex.length() / 2;
	std::string strByte;
	unsigned int n;
	for (int i = 0; i < min(bytelen,byteSize); i++)
	{
		strByte = hex.substr(i * 2, 2);
		sscanf(strByte.c_str(), "%x", &n);
		bytes[i] = n;
	}
}

bool ProduceRandomNumberCrypt(string &ret)
{
	bool retBL = true;
	BYTE pbBuffer[16]{0};
	HCRYPTPROV Rnd = 0;
	retBL = CryptAcquireContext(&Rnd, NULL, NULL, PROV_RSA_FULL, 0);
	if (retBL) {
		retBL = CryptGenRandom(Rnd, 16, pbBuffer);
		if (retBL)
		{
			string str = "";
			string strCode = "";
			string strCodeUpper = "";
			for (int i = 0; i < 16; i++)
			{
				str = format("%d", pbBuffer[i]);
				int iret = atoi(str.c_str());
				switch (iret % 3)
				{
				case 0:
					strCode += to_string(iret % 10);//转成0-9的数字字符串
					break;
				case 1:
					strCode += format("%c", (iret % 26) + 'A');
					break;
				case 2:
					strCode += format("%c", (iret % 26) + 'a');
					break;
				default:
					break;
				}
			}
			std::transform(strCode.begin(), strCode.end(), back_inserter(strCodeUpper), ::toupper);
			ret = strCodeUpper;
		}
	}
	else {
		if (GetLastError() == NTE_BAD_KEYSET) {
			if (CryptAcquireContext(
				&Rnd,
				NULL,
				NULL,
				PROV_RSA_FULL,
				CRYPT_NEWKEYSET)) {
				printf("A new key container has been created.\n");
			}
			else {
				printf("Could not create a new key container.\n");

			}
		}
		else {
			printf("A cryptographic service handle could not be "
				"acquired.\n");
		}
	}
	if (Rnd) CryptReleaseContext(Rnd, 0);
	return retBL;
}

std::string UTF8_To_string(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}
#include <codecvt>
#include <locale>

string unicodeToCHI(string unicodeStr) {
	string uStr, value;
	int index, len;
	wstring_convert<codecvt_utf8<char32_t>, char32_t> converter;

	if (unicodeStr.length() <= 0)
	{
		return "";
	}

	//unicode转utf8
	while (1) {
		index = unicodeStr.find("\\u");
		if (index<0 || index>unicodeStr.length())
			break;

		//转换需要的地方
		uStr = unicodeStr.substr(index + 2, 4);
		for (size_t i = 0; i < uStr.length();) {
			char32_t uhan = strtol(uStr.substr(i, 4).c_str(), nullptr, 16);
			value = converter.to_bytes(uhan);
			i += 4;
		}

		//在原字符串中替换掉
		unicodeStr.replace(index, 6, value);
	}


	//utf8转ANSI
	len = ::MultiByteToWideChar(CP_UTF8, 0, unicodeStr.c_str(), -1, NULL, 0);
	WCHAR* wStr = new WCHAR[len + 1]{ 0 };
	len = MultiByteToWideChar(CP_UTF8, 0, unicodeStr.c_str(), -1, wStr, len);

	len = WideCharToMultiByte(CP_ACP, 0, wStr, -1, NULL, 0, NULL, NULL);
	char* szANSI = new char[len + 1]{ 0 };
	WideCharToMultiByte(CP_ACP, 0, wStr, -1, szANSI, len, NULL, NULL);


	unicodeStr = szANSI;


	delete[]wStr;
	delete[]szANSI;
	wStr = nullptr;
	szANSI = nullptr;

	return unicodeStr;
}

string showU8Str(const string& str) {
	std::string u8str;
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
	for (int i = 0; i < str.length(); ) {
		cout << str.substr(i, 4) << endl;
		unsigned int uhan = strtol(str.substr(i, 4).c_str(), nullptr, 16);
		u8str += converter.to_bytes(uhan);

		i += 4;
	}

	return u8str;
}

string GetPathDir(string filePath)
{
	string dirPath = filePath;
	size_t p = filePath.find_last_of('\\');
	if (p != -1)
	{
		dirPath.erase(p);
	}
	return dirPath;
}

void CreateMultiLevel(string dir)
{
	if (_access(dir.c_str(), 00) == 0)
	{
		return;
	}

	list <string> dirList;
	dirList.push_front(dir);

	string curDir = GetPathDir(dir);
	while (curDir != dir)
	{
		if (_access(curDir.c_str(), 00) == 0)
		{
			break;
		}

		dirList.push_front(curDir);

		dir = curDir;
		curDir = GetPathDir(dir);
	}

	for (auto it : dirList)
	{
		_mkdir(it.c_str());
	}
}


inline time_t getTimeStamp()
{
	std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp =
		std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
	time_t timestamp = tmp.count();
	return timestamp;
}
//获取时间 年-月-日 时-分-秒 毫秒
inline std::string gettm(__int64 timestamp)
{
	__int64 milli = timestamp + (__int64)8 * 60 * 60 * 1000;
	auto mTime = std::chrono::milliseconds(milli);
	auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
	auto tt = std::chrono::system_clock::to_time_t(tp);
	std::tm now;
	::gmtime_s(&now, &tt);
	char res[64] = { 0 };
	sprintf_s(res, _countof(res), "%4d%02d%02d%02d%02d%02d%03d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec, static_cast<int>(milli % 100));
	return std::string(res);
}

#include "BOE_log.h"

#pragma region 解析锁卡表

struct CustomInfo
{
	int ID;
	string Name;
	/// <summary>
	/// 字段长度
	/// </summary>
	string Length;
	string StationName;
	string Value;
	string toString()
	{
		return std::to_string(ID) + "\t" + Name + "\t\t\t" + Length + "\t" + StationName + "\t" + Value;
	}
};
#include <cstdio>
#include <unordered_map>

/// <summary>
/// 解析本地锁卡表
/// </summary>
/// <param name="fileName"></param>
bool ParseCustomInfoXls(unordered_map<string, CustomInfo>& retCustomInfos, string fileName)
{
	std::cout << __FUNCTION__ << " file:" << string_To_UTF8(fileName) << endl;
	xls::xls_error_t error = xls::LIBXLS_OK;
	xls::xlsWorkBook* wb = xls::xls_open_file(UTF8_To_string(fileName).c_str(), "UTF-8", &error);
	if (wb == NULL) {
		printf("Error reading file: %s\n", xls_getError(error));
		return false;
	}
	xls::xlsWorkSheet* work_sheet = xls_getWorkSheet(wb, 0);
	error = xls_parseWorkSheet(work_sheet);
	for (int j = 1; j <= work_sheet->rows.lastrow; j++) { // rows // 去掉首行
		CustomInfo customInfo;
		xls::xlsRow* row = xls_row(work_sheet, j);
		if (row->cells.cell[0].id == XLS_RECORD_BLANK) break; customInfo.ID = stoi(row->cells.cell[0].str);
		if (row->cells.cell[1].id == XLS_RECORD_BLANK) break; customInfo.Name = row->cells.cell[1].str;
		if (row->cells.cell[2].id == XLS_RECORD_BLANK) customInfo.Length ="";else customInfo.Length = row->cells.cell[2].str;
		if (row->cells.cell[3].id == XLS_RECORD_BLANK) customInfo.StationName = ""; else customInfo.StationName = row->cells.cell[3].str;
		if (row->cells.cell[4].id == XLS_RECORD_BLANK) customInfo.Value = ""; else customInfo.Value = row->cells.cell[4].str;
		retCustomInfos[customInfo.Name] = customInfo;
	}
	xls_close_WS(work_sheet);
	xls_close_WB(wb);
	return true;
	
}
#pragma endregion

#pragma region 解析软件版本
struct SoftwareVerInfo
{
	string VerID;
	string IDDescription;
	string ModuleInfo;
	string toString()
	{
		return VerID + "\t" + IDDescription + "\t" + ModuleInfo;
	}
};
/// <summary>
/// 解析本地软件版本
/// </summary>
/// <param name="fileName"></param>
bool ParseSoftwareVerXls(unordered_map<string, SoftwareVerInfo>& retSoftwareVer, string fileName)
{
	std::cout << __FUNCTION__ << " file:" << UTF8_To_string(fileName) << endl;
	xls::xls_error_t error = xls::LIBXLS_OK;
	xls::xlsWorkBook* wb = xls::xls_open_file(UTF8_To_string(fileName).c_str(), "UTF-8", &error);
	if (wb == NULL) {
		printf("Error reading file: %s\n", xls_getError(error));
		return false;
	}
	xls::xlsWorkSheet* work_sheet = xls_getWorkSheet(wb, 0);
	error = xls_parseWorkSheet(work_sheet);
	for (int j = 1; j <= work_sheet->rows.lastrow; j++) { // rows // 去掉首行
		SoftwareVerInfo softwareVer;
		xls::xlsRow* row = xls_row(work_sheet, j);
		if (row->cells.cell[0].id == XLS_RECORD_BLANK) break; softwareVer.VerID = row->cells.cell[0].str;
		if (row->cells.cell[1].id == XLS_RECORD_BLANK) break; softwareVer.IDDescription = row->cells.cell[1].str;
		if (row->cells.cell[2].id == XLS_RECORD_BLANK) softwareVer.ModuleInfo =""; else softwareVer.ModuleInfo = row->cells.cell[2].str;
		retSoftwareVer[softwareVer.IDDescription] = softwareVer;
	}
	xls_close_WS(work_sheet);
	xls_close_WB(wb);
	return true;
}

#pragma endregion

struct Version
{
	string KeyName;
	string KeyValue;
};
AJSON(Version, KeyName, KeyValue)

struct RequestData
{
	string Barcode = "";
	string FactoryCode = "";
	string BarcodeType = "";
	string TaskOrder = "";
	string StationID = "";
	string VersionListType = "";
	string Line = "";
	string UserName = "";

};
AJSON(RequestData, Barcode, FactoryCode, BarcodeType, TaskOrder, StationID, VersionListType,Line, UserName);

struct StructGoogleKey
{
	/*string KeyIDS;*/
	string A_KeyAttestation_G_1;
	string A_KeyAttestation_G_2;
	string A_KeyAttestation_G_3;
	string A_KeyAttestation_G_4;
	string A_KeyAtte_G_Verify;
};
AJSON(StructGoogleKey,/*KeyIDS,*/A_KeyAttestation_G_1,A_KeyAttestation_G_2,A_KeyAttestation_G_3,A_KeyAttestation_G_4, A_KeyAtte_G_Verify)

struct StructWidevineKey
{
	string WIDEVINE_KEY_NAME;
	string WIDEVINEDRM_KEY;
	string WIDEVINE_KEY_CRC;
};
AJSON(StructWidevineKey,/*KeyIDS,*/WIDEVINE_KEY_NAME, WIDEVINEDRM_KEY, WIDEVINE_KEY_CRC)


struct StructDeviceKey
{
	//string DevIDS;
	string Hw_Device_Certs_1;
	string Hw_Device_Certs_2;
	string Hw_Device_Certs_3;
	string Hw_Device_Certs_4;
	string Hw_Device_Certs_5;
	string Hw_Device_Certs_VD;
};
AJSON(StructDeviceKey,/*DevIDS,*/Hw_Device_Certs_1,Hw_Device_Certs_2,Hw_Device_Certs_3,Hw_Device_Certs_4,Hw_Device_Certs_5,Hw_Device_Certs_VD)

struct ResponseData
{
	string Barcode;
	string RESULT;
	string Fail_Msg;
	vector<Version> VersionList;
	string TaskOrder;
	string Model;
	string RAM;
	string MemorySize;
	string CPU;
	string BoardId;
	string BoardName;
	string ProductName;
	string SupportSD;// Y N
	string APName;
	string APVersion;
	string MemoryType;
	string MSN;
	map<string, string> lockCardTableDto;
	StructGoogleKey GoogleKey;
	StructDeviceKey DeviceKey;
	StructWidevineKey WidevineKey;
	string BTMAC;
	string WIFIMAC;
	string ZSN;
	string PSN;
	string EMMCID;
	string UDID;
	string PUBLICKEY;
	string NCK_DIAGUNLOCK;
	string FRP_KEY;
	string NCK_NCKNSCKSPCKRESET;

	string CPL_ID;
	string CPL_CONTENT;
	string RKP_DATA_1;
	string RKP_DATA_2;
	string RKP_DATA_VD;
	string MEID;
	string IMEI1;
	string IMEI2;
	string FIVE_G;

};
AJSON(ResponseData,
	Barcode,
	RESULT,
	Fail_Msg,
	VersionList,
	TaskOrder,
	Model,
	RAM,
	MemorySize,
	CPU,
	BoardId,
	BoardName,
	ProductName,
	SupportSD,
	APName,
	APVersion,
	MemoryType,
	MSN,
	lockCardTableDto,
	GoogleKey,
	DeviceKey,
	WidevineKey,
	BTMAC,
	WIFIMAC,
	ZSN,
	PSN,
	EMMCID,
	UDID,
	PUBLICKEY,
	NCK_DIAGUNLOCK,
	FRP_KEY,
	NCK_NCKNSCKSPCKRESET,

	CPL_ID,
    CPL_CONTENT,
	RKP_DATA_1,
    RKP_DATA_2,
    RKP_DATA_VD,
	MEID,
    IMEI1,
	IMEI2,
    FIVE_G
);

#ifndef OBA
struct PostData
{
	string Barcode = "";
	string StationID = "";
	string BarcodeType = " BSN";
	string Line = "";
	string UserName = "";
	string PcName = "";
	string Fixture = "";
	string AteName = "";
	string Result = "NG";
	string BugCode = "";
	string ErrorMsg = "";

	string EMMCID = "";
	string UDID = "";
	string PUBLICKEY = "";
	string NCK_DIAGUNLOCK = "";
	string NCK_NCKNSCKSPCKRESET = "";
	string FRP_KEY = "";

	string RKP_DATA_1 = "";
	string RKP_DATA_2 = "";
	string RKP_DATA_VD = "";
};
AJSON(PostData,
	Barcode,
	StationID,
	BarcodeType,
	Line,
	UserName,
	PcName,
	Fixture,
	AteName,
	Result,
	BugCode,
	ErrorMsg,

	EMMCID,
	UDID,
	PUBLICKEY,
	NCK_DIAGUNLOCK,
	NCK_NCKNSCKSPCKRESET,
	FRP_KEY,

	RKP_DATA_1,
	RKP_DATA_2,
	RKP_DATA_VD
);

#endif // !OBA


#ifdef OBA
struct PostData
{
	string Barcode;
	string BarcodeType;
	string TaskOrder;
	string PCName;
	string StationID;
	string UserName;
	string FactoryCode;
	// 暂时该字段值不在json中上传
	string Result;
};
AJSON(PostData,
	Barcode,
	BarcodeType,
	TaskOrder,
	PCName,
	StationID,
	UserName,
	FactoryCode
);
#endif // OBA

struct PostRetData
{
	string BARCODE;
	string RESULT;
	string FAIL_MSG;
};
AJSON(PostRetData,
	BARCODE,
	RESULT,
	FAIL_MSG
	);

struct SafeDogLoginInfo
{
	string UserName;
	string Password;
};
AJSON(SafeDogLoginInfo,
	UserName,
	Password
);