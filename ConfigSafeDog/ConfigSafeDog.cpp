// ConfigSafeDog.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <unordered_set>
#include "Tool.h"
#include "md5.h"

//#include "cryptlib/include/"
using namespace CryptoPP;
using namespace std;
#if _DEBUG
#pragma comment(lib,"cryptlib/Debug/cryptlib.lib")
#else
#pragma comment(lib,"cryptlib/Release/cryptlib.lib")
#endif // _DEBUG
#define MD5_CRYPT_LEN 16

string getMD5(string str)
{
    MD5 md5;
    byte digest[MD5_CRYPT_LEN] = { 0 };

    int len = str.length();
    byte* message = new byte[len + 1];
    message[len] = 0;
    memcpy(message, str.c_str(), len + 1);

    md5.CalculateDigest(digest, message, len);

    ostringstream osstr;
    /* 设置字符串流的格式：16进制，大写、不足位补0*/
    osstr << hex << uppercase << setfill('0');

    for (int i = 0; i < MD5_CRYPT_LEN; ++i)
    {
        /* 输入2位数据，输入F最终输出是0F*/
        osstr << setw(2) << int(digest[i]);
    }

    delete[]message;

    return osstr.str();
}

string getword() {
    string line;  //用来保存输入一行的密码的变量
    char ch;
    while (ch = _getch())  //单个字符的获取
    {
        if (ch == '\n' || ch == '\r')break;
        else if (ch == 8) {    //当输入退格符时    
            line = line.substr(0, line.length() - 1);  //删除字符串最后一个字符
            cout << "\b" << " " << "\b";  //  光标退一个显示为空，在退一格
        }
        else {
            _putch('*');
            line += ch;
        }
    }
    return line;
}

char seed[64] = {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z','a','b','c','d',
    'e','f','g','h','i','j','k','l','m','n',
    'o','p','q','r','s','t','u','v','w','x',
    'y','z','\0','\0'
};
string makeRandomString(int length)
{
    static std::random_device rd;  // 将用于为随机数引擎获得种子
    static std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    static std::uniform_int_distribution<> dis(0, 61);
    string name = "";
    for (int n = 0; n < length; ++n) {
        // 用 dis 变换 gen 所生成的随机 unsigned int 到 [0, 62] 中的 int
        int val = dis(gen);
        name += seed[val];
    }
    return name;
}

int main()
{
    SetConsoleTitleA("设置加密狗");
    std::cout << "请确保程序不测试状态，以免引起异常。"<<endl; 
    string FactoryCode = "";
    std::cout << "请输入工厂代码（例如BOE）:" << endl;
    std::cin >> FactoryCode;

    string randomString = makeRandomString(4);
    time_t now = time(0);
    auto day = ((gmtime(&now)->tm_mday) % 10);
    auto md5Str = getMD5(randomString);
    //std::cout <<"MD5:" << md5Str << " day:" << day << endl;
    auto targetPsw = md5Str.substr(day+8,6);
    string psw;
    int count = 0;
    label: 
    cout<<"随机字符串：" << randomString/* <<" psw:"<< targetPsw */<< endl;
    std::cout << "管理安全性验证："; psw = getword(); std::cout << endl;
    if (psw != targetPsw)
    {
        cout << "安全性验证失败！\r\n"<<endl;
        count++;
        if (count > 4) return 0;
        goto label;      
    }
    cout << "安全性验证通过，请继续。\r\n" << endl;

    string fileName = "SafeDog_" + FactoryCode + ".dat";
    cout << "即将生成加密狗文件："+fileName << endl;
    string key = "";
    if(ifstream(fileName).good())
    {
        fstream ofs;
        ofs.open(fileName, ios::in);
        string encryptStr;
        ofs >> encryptStr;
        ofs.close();
        SafeDogLoginInfo safeDogLoginInfo;
        ajson::load_from_buff(safeDogLoginInfo, decryptStr_ECB_AES(key, encryptStr).c_str());
        std::cout << "当前加密狗UserName：" << safeDogLoginInfo.UserName << endl;
        std::cout << "当前加密狗Password：" << safeDogLoginInfo.Password << endl;
    }
    std::cout << "\r\n";
    std::cout << "继续设置新的加密狗信息" << endl;
    {
        SafeDogLoginInfo safeDogLoginInfo;
        std::cout << "输入加密狗UserName："; std::cin >> safeDogLoginInfo.UserName;
        std::cout << "输入加密狗Password："; std::cin >> safeDogLoginInfo.Password;

        ajson::string_stream ss;
        ajson::save_to(ss, safeDogLoginInfo);
        string encryptStr = encryptStr_ECB_AES(key, ss.str());

        // 序列化成二进制文件
        fstream ofs;
        ofs.open(fileName, ios::out | ios::trunc);
        ofs << encryptStr;
        ofs.flush();
        ofs.close();
        std::cout << "加密狗账号设置成功！请重启主程序，以确保新加密狗信息生效。" << endl;
    }
    {
        fstream ofs;
        ofs.open(fileName, ios::in);
        string encryptStr;
        ofs >> encryptStr;
        ofs.close();
        SafeDogLoginInfo safeDogLoginInfo;
        ajson::load_from_buff(safeDogLoginInfo, decryptStr_ECB_AES(key, encryptStr).c_str());
        std::cout << "输出加密狗UserName："<< safeDogLoginInfo.UserName<<endl;
        std::cout << "输出加密狗Password："<< safeDogLoginInfo.Password<<endl;
    }
    system("pause");
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
