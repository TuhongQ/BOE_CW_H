#include "pch.h"
#include "BOE_log.h"
#include<stdio.h>
#include<iostream>

#define SP_OK 0
#define SP_FAIL 1

bool BOE_log::CreateLog(const char* ManufactureName, const char* EquipmentManufactureName,
	const char* ToolName, const char* ToolVersion)
{	
	FILE* fp = fopen(m_pathReport, "w");
	if (fp != NULL)
	{
		fprintf(fp, "厂商名称,%s\n 设备厂商,%s\n 工具名称,%s\n 工具版本,%s\n", ManufactureName, EquipmentManufactureName, ToolName, ToolVersion);
		fprintf(fp, "%s,%s,%s,%s,%s,%s,%s\n", "ID", "TestItem", "LowerLimit", "Value", "UpperLimit", "Result", "TestTime");
	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
		return SP_OK;
	}
	return SP_FAIL;
}

bool BOE_log::CreateLogT(const char* strLog)
{
	FILE* fp = fopen(m_pathLog, "w");
	if (fp != NULL)
	{
		fprintf(fp, "%s\n", strLog);
	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
		return SP_OK;
	}
	return SP_FAIL;
}

bool BOE_log::AddLog(const char* TestItem, const char* LowerLimit, const char* UpperLimit, const char* Value,
	const char* Result, const char* TestTime)
{
	FILE* fp = fopen(m_pathReport, "a");
	m_iCountR += 1;
	if (fp != NULL)
	{
		fprintf(fp, "%d,", m_iCountR);
		fprintf(fp, "%s,%s,%s,%s,%s,%s\n", TestItem, LowerLimit, UpperLimit, Value, Result, TestTime);
	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
		return SP_OK;
	}
	return SP_FAIL;
}

bool BOE_log::AddLogT(const char* TestItem, const char* strLog)
{
	FILE* fp = fopen(m_pathLog, "a");
	time_t now = time(0);
	tm* info = localtime(&now);
	char buffer[80] = "";
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);

	if (fp != NULL)
	{
		fprintf(fp, "[%s]: [%s]", buffer, TestItem);
		fprintf(fp, " %s\n",strLog);
	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
		return SP_OK;
	}
	return SP_FAIL;
}

bool BOE_log::AddLogT(const char* strLog)
{
	FILE* fp = fopen(m_pathLog, "a");
	time_t now = time(0);
	tm* info = localtime(&now);
	char buffer[80] = "";
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);

	if (fp != NULL)
	{
		fprintf(fp, "[%s]: ", buffer);
		fprintf(fp, "%s\n", strLog);
	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
		return SP_OK;
	}
	return SP_FAIL;
}