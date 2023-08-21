// LogDecrypt.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <io.h>
#include <fstream>
#include <sstream>

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
#include <string>
int HexStrToInt(string hexStr)
{
	string upper;
	upper.resize(hexStr.size());
	transform(hexStr.begin(), hexStr.end(), upper.begin(), ::toupper);
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

using namespace CryptoPP;

#if _DEBUG
#pragma comment(lib,"../BOE_CW_H/cryptlib/Debug/cryptlib.lib")
#else
#pragma comment(lib,"../BOE_CW_H/cryptlib/Release/cryptlib.lib")
#endif // _DEBUG


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

int main()
{
	//std::cout << HexStrToInt("EE")<<endl;
	std::string psw = "BOE_TSD_TC823_2023";
	//std::cout << "请输入PSW:" << std::endl;
	//std::cin >> psw;
	while (true)
	{
		try
		{
			std::string filePathName;
			std::cout << "请输入File:" << std::endl;
			std::cin >> filePathName;
			std::ifstream fileStream(filePathName);
			std::stringstream buffer;
			buffer << fileStream.rdbuf();
			std::string contents(buffer.str());
			auto contentList = split(contents, "\n");
			vector<string> newContentList;
			for (auto line : contentList)
			{
				auto pos = line.find("Encrypt:");
				if (pos == string::npos)
				{
					newContentList.push_back(line);
					continue;
				}
				newContentList.push_back(line.substr(0, pos) + "Decrypt:" + decryptStr_ECB_AES(psw, line.substr(pos + 8)));
			}
			string newContents = join(newContentList, "\n");
			string targetFilePathName = filePathName.substr(0, filePathName.find_last_of(".")) + "_Decrypt" + filePathName.substr(filePathName.find_last_of("."));
			ofstream ofs;
			ofs.open(targetFilePathName, ios::out);
			ofs << newContents;
			ofs.close();
			std::cout << "文件解密位置:" << targetFilePathName << endl;

		}
		catch (const std::exception& e)
		{
			cout << e.what() << endl;
		}
	}	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
