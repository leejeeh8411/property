#pragma once

#include <map>
#include <vector>
#include <string>
#include "ini.h"

using namespace std;

enum DataType
{
	TYPE_BOOLEAN = 0,
	TYPE_INT = 1,
	TYPE_DOUBLE = 2,
	TYPE_STRING = 3
};

static const int STRING_DATA_LENGTH = 50;

struct PARAM {
	int nDataType;
	bool bValue;
	int nValue;
	double dValue;
	char chGroupName[STRING_DATA_LENGTH];
	char chValue[STRING_DATA_LENGTH];
	PARAM() {
		nDataType = 0;
		bValue = 0;
		nValue = 0;
		dValue = 0;
		memset(chGroupName, NULL, STRING_DATA_LENGTH);
		memset(chValue, NULL, STRING_DATA_LENGTH);
	}
};


class gParameter
{
public:
	gParameter();
	~gParameter();

	void LoadParam();
	void SaveParam();
	string	GetParameterPath();
	void	SetParameterPath(CString strPath);

	pair<string, PARAM> MakeParam(CString strGroupName, CString _strKey, bool bVal);
	pair<string, PARAM> MakeParam(CString strGroupName, CString _strKey, int nVal);
	pair<string, PARAM> MakeParam(CString strGroupName, CString _strKey, float fVal);
	pair<string, PARAM> MakeParam(CString strGroupName, CString _strKey, double dVal);
	pair<string, PARAM> MakeParam(CString strGroupName, CString _strKey, CString strVal);

	shared_ptr<pair<string, PARAM>> GetParam(string strKey);
	pair<string, PARAM> gParameter::GetParam_old(string strKey);

	CString             GetValueString(string strKey);
	bool				SetParam(pair<string, PARAM> data);
	bool				SetParam(pair<string, PARAM> data, string value);

	vector<string>		GetListParam();
	vector<string>		GetListParamFromGroupName(string search_group_name);
	vector<string>		GetListGroup();

	int					GetMaxStrLength();


private:
	map<string, PARAM>	m_map;
	string _parameter_path;

};

