#pragma once

#ifndef INI_PARSER_HPP
#define INI_PARSER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <map>
#include <string>
#include <mutex>

using namespace std;

class INIParser
{
private:
	map<string, map<string, string>> _map_ini;

	string& replace_all(string& str, const string& old_value, const string& new_value);
	string& replace_all_distinct(string& str, const string& old_value, const string& new_value);
public:
	string lastError = "";
	~INIParser() { Clear(); }
	size_t GetSize() const { return _map_ini.size(); }
	string getStringFromFile(const string& file);
	bool ReadINI(const string& fileName);
	string GetString(const string& root, const string& key, const string& def = "") const;
	int GetInt(const string& root, const string& key, int def = 0) const;
	double GetDouble(const string& root, const string& key, double def = 0) const;
	bool GetBool(const string& root, const string& key, bool def = false) const;

	void SetValue(const string& root, const string& key, const string& value);
	void SetString(const string& root, const string& key, const string& value);
	void SetInt(const string& root, const string& key, int value);
	void SetDouble(const string& root, const string& key, double value);
	void SetBool(const string& root, const string& key, bool value);

	bool WriteINI(const string& path);
	void Clear() { _map_ini.clear(); }
	void View();
};

#endif // INI_PARSER_HPP