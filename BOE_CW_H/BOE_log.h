#pragma once
#include<iostream>

class BOE_log
{
public:
	BOE_log() {
		m_pathReport = "";
		m_pathLog = "";
		m_iCountR = 0;
		//m_iCountL = 0;
	};
	virtual ~BOE_log()
	{
		m_pathReport = "";
		m_pathLog = "";
		m_iCountR = 0;
		//m_iCountL = 0;
	}
public:
	const char* m_pathReport;
	const char* m_pathLog;
	int m_iCountR;
	//int m_iCountL;
public:
	bool CreateLog( const char* ManufactureName, const char* EquipmentManufactureName,
		const char* ToolName, const char* ToolVersion);

	bool CreateLogT(const char* strLog);

	bool AddLog(const char* TestItem, const char* LowerLimit, const char* UpperLimit, const char* Value,
		const char* Result, const char* TestTime);

	bool AddLogT(const char* strLog);
	bool AddLogT(const char* TestItem, const char* strLog);
};

