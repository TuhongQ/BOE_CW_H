#include "pch.h"
#include "INIParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>

static void TrimString(string& str)
{
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1);
}

string& INIParser::replace_all(string& str, const string& old_value, const string& new_value)
{
	while (true)
	{
		string::size_type pos = 0;
		pos = str.find(old_value);
		if (pos == string::npos) break;

		str.replace(pos, old_value.length(), new_value);
	}
	return str;
}

string& INIParser::replace_all_distinct(string& str, const string& old_value, const string& new_value)
{
	for (size_t pos = 0; pos != string::npos; pos += new_value.length())
	{
		pos = str.find(old_value, pos);
		if (pos == string::npos) break;

		str.replace(pos, old_value.length(), new_value);
	}
	return str;
}
string INIParser::getStringFromFile(const string& file)
{
	std::string content;
	std::ifstream file_stream;
	//file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file_stream.open(file);
		std::stringstream string_stream;
		string_stream << file_stream.rdbuf();
		file_stream.close();
		
		content = string_stream.str();

		string_stream.clear();
		string_stream.str("");
	}
	catch (const std::exception& e)
	{
		lastError = "err:";
		lastError += e.what();
		std::cerr << e.what() << '\n';
		
	}
	return content;

	//std::string content;
	//std::ifstream file_stream;
	//file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//try
	//{
	//	file_stream.open(file);
	//	std::stringstream string_stream;
	//	string_stream << file_stream.rdbuf();
	//	file_stream.close();
	//	content = string_stream.str();
	//}
	//catch (const std::exception& e)
	//{
	//	lastError = e.what();
	//	std::cerr << e.what() << '\n';
	//}
	//return content;


	unsigned char* buffer = nullptr;
	size_t size = 0;
	size_t readsize;
	// Read the file from hardware
	FILE* fp = nullptr;
	fopen_s(&fp, file.c_str(), "rt");
	if (fp == nullptr)
	{
		return "";
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = (unsigned char*)malloc(sizeof(unsigned char) * (size + 1));
	buffer[size] = '\0';

	readsize = fread(buffer, sizeof(unsigned char), size, fp);
	fclose(fp);

	if (readsize < size)
	{
		buffer[readsize] = '\0';
	}

	string str((char*)buffer);
	free(buffer);
	return str;
}
bool INIParser::ReadINI(const string& fileName)
{
	stringstream in_conf_file;
	try
	{
		string content = getStringFromFile(fileName);
		if (!lastError.empty()) return false;
		replace_all_distinct(content, "\r", "\n");
		if (content.empty()) lastError = "\r\nReadIni content is empty;";
		if (content.empty()) return false;
		in_conf_file << content;
		string str_line = "";
		map<string, string>* kv_node = nullptr;
		size_t left_pos;
		size_t right_pos;
		size_t equal_div_pos;

		while (getline(in_conf_file, str_line))
		{
			if (str_line.empty()) continue;
			if ((string::npos != (left_pos = str_line.find("["))) &&
				(str_line.npos != (right_pos = str_line.find("]"))))
			{
				//配置头
				string root = str_line.substr(left_pos + 1, right_pos - left_pos - 1);
				TrimString(root);
				if (!root.empty())
				{
					_map_ini[root] = map<string, string>{};
					kv_node = &(_map_ini[root]);
				}
			}
			else if (string::npos != (equal_div_pos = str_line.find("=")))
			{
				//配置项，需要注意;为注释
				string key = str_line.substr(0, equal_div_pos);
				size_t notePos = str_line.find(";");
				string value;
				if (string::npos != notePos)
				{
					value = str_line.substr(equal_div_pos + 1, notePos - equal_div_pos - 1);
				}
				else
				{
					value = str_line.substr(equal_div_pos + 1, str_line.size() - 1);
				}
				TrimString(key);
				TrimString(value);
				if (kv_node != nullptr && !key.empty())
				{
					(*kv_node)[key] = value;
				}
			}
		}
		return true;
	}
	catch (exception e)
	{
		lastError = e.what();
		return false;
	}
}


void INIParser::View()
{
	for (auto it = _map_ini.begin(); it != _map_ini.end(); ++it)
	{
		printf(it->first.c_str());
		printf("\n");
		for (auto vit = it->second.begin(); vit != it->second.end(); ++vit)
		{
			printf(vit->first.c_str());
			printf(" = ");
			printf(vit->second.c_str());
			printf("\n");
		}
	}
}


string INIParser::GetString(const string& root, const string& key, const string& def) const
{
	auto itr = _map_ini.find(root);
	if (itr == _map_ini.end()) return "";

	auto sub_itr = itr->second.find(key);
	if (sub_itr == itr->second.end()) return "";

	if (!(sub_itr->second).empty()) return sub_itr->second;
	return def;
}

int INIParser::GetInt(const string& root, const string& key, int def) const
{
	string str = GetString(root, key, "");
	if (str.empty()) return def;

	int res;
	try
	{
		istringstream is(str);
		is >> res;
	}
	catch (...)
	{
		res = def;
	}
	return res;
}

double INIParser::GetDouble(const string& root, const string& key, double def) const
{
	string str = GetString(root, key, "");
	if (str.empty()) return def;

	double res;
	try
	{
		istringstream is(str);
		is >> res;
	}
	catch (...)
	{
		res = def;
	}
	return res;
}

bool INIParser::GetBool(const string& root, const string& key, bool def) const
{
	string str = GetString(root, key, "");
	if (str.empty()) return def;

	if (str == "1") return true;
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	if (str == "true") return true;
	return false;
}


bool INIParser::WriteINI(const string& path)
{
	ofstream out_conf_file(path.c_str());
	if (!out_conf_file) return false;

	for (auto itr = _map_ini.begin(); itr != _map_ini.end(); ++itr)
	{
		out_conf_file << "[" << itr->first << "]" << endl;
		for (map<string, string>::iterator sub_itr = itr->second.begin();
			sub_itr != itr->second.end(); ++sub_itr)
		{
			out_conf_file << sub_itr->first << "=" << sub_itr->second << endl;
		}
	}

	out_conf_file.close();
	out_conf_file.clear();
	return true;
}

void INIParser::SetValue(const string& root, const string& key, const string& value)
{
	auto itr = _map_ini.find(root);
	if (_map_ini.end() != itr)
	{
		map<string, string>::iterator it = itr->second.find(key);
		if (it != itr->second.end())
		{
			it->second = value;
		}
		else
		{
			itr->second[key] = value;
		}
	}
	else
	{
		map<string, string> m;
		m[key] = value;
		_map_ini[root] = std::move(m);
	}
}

void INIParser::SetString(const string& root, const string& key, const string& value)
{
	SetValue(root, key, value);
}

void INIParser::SetInt(const string& root, const string& key, int value)
{
	char buf[32];
	sprintf_s(buf, "%d", value);
	SetValue(root, key, buf);
}

void INIParser::SetDouble(const string& root, const string& key, double value)
{
	char buf[64];
	sprintf_s(buf, "%lf", value);
	SetValue(root, key, buf);
}

void INIParser::SetBool(const string& root, const string& key, bool value)
{
	if (value) SetValue(root, key, "1");
	else SetValue(root, key, "0");
}