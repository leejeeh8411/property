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


struct PARAM {
	int nDataType;
	bool bValue;
	int nValue;
	double dValue;
	string strGroupName;
	string strValue;
	PARAM() {
		nDataType = 0;
		bValue = 0;
		nValue = 0;
		dValue = 0;
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
	void	SetParameterPath(string strPath);

	vector<string>		GetListParam();
	vector<string>		GetListParamFromGroupName(string search_group_name);
	vector<string>		GetListGroup();

	shared_ptr<pair<string, PARAM>> GetParam(string strKey);

	template <typename T>
	void CreateParam(string group_name, string key, DataType data_type, T value)
	{
		shared_ptr<pair<string, PARAM>> ptr_param = make_shared<pair<string, PARAM>>();

		PARAM stParam;
		stParam.strGroupName = group_name;
		stParam.nDataType = data_type;
		switch (data_type)
		{
		case DataType::TYPE_BOOLEAN:
		{
			SetParamValue(stParam, value);
			break;
		}
		case DataType::TYPE_INT:
		{
			SetParamValue(stParam, value);
			break;
		}
		case DataType::TYPE_DOUBLE:
		{
			SetParamValue(stParam, value);
			break;
		}
		case DataType::TYPE_STRING:
		{
			SetParamValue(stParam, value);
			break;
		}
		default:
		{
			break;
		}
		}

		ptr_param->first = key;
		ptr_param->second = stParam;

		SetParam(ptr_param);
	}

	void				SetParamValue(PARAM& stParam, bool value){ stParam.bValue = value; }
	void				SetParamValue(PARAM& stParam, int value) { stParam.nValue = value; }
	void				SetParamValue(PARAM& stParam, float value) { stParam.dValue = value; }
	void				SetParamValue(PARAM& stParam, double value) { stParam.dValue = value; }
	void				SetParamValue(PARAM& stParam, string value) { stParam.strValue = value; }

	
	bool				SetParam(shared_ptr<pair<string, PARAM>> data);
	bool				SetParamFromString(shared_ptr<pair<string, PARAM>> data, string value);

private:
	map<string, PARAM>	m_map;
	string _parameter_path;

	shared_ptr<pair<string, PARAM>> MakeParam(string strGroupName, string _strKey, bool bVal);
	shared_ptr<pair<string, PARAM>> MakeParam(string strGroupName, string _strKey, int nVal);
	shared_ptr<pair<string, PARAM>> MakeParam(string strGroupName, string _strKey, float fVal);
	shared_ptr<pair<string, PARAM>> MakeParam(string strGroupName, string _strKey, double dVal);
	shared_ptr<pair<string, PARAM>> MakeParam(string strGroupName, string _strKey, string strVal);


	string             GetValueString(string strKey);
};




