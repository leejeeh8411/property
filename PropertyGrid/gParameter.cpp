﻿#include "stdafx.h"
#include "gParameter.h"


gParameter::gParameter()
{
}


gParameter::~gParameter()
{
}



//파라미터 리스트를 호출
vector<string> gParameter::GetListParam()
{
	int nSize = static_cast<int>(m_map.size());
	vector<string> vtParamList;

	for (const auto& pair : m_map)
	{
		string str = pair.first;
		vtParamList.emplace_back(str);
	}

	return vtParamList;
}

//그룹이름으로 하위 파라미터 리스트를 호출
vector<string> gParameter::GetListParamFromGroupName(string search_group_name)
{
	int nSize = static_cast<int>(m_map.size());
	vector<string> vtParamList;

	for (const auto& pair : m_map)
	{
		string key = pair.first;
		PARAM param = pair.second;
		string group = param.chGroupName;
		if (group == search_group_name) {
			vtParamList.emplace_back(key);
		}
	}

	return vtParamList;
}

//파라미터 그룹
vector<string> gParameter::GetListGroup()
{
	int nSize = static_cast<int>(m_map.size());
	vector<string> vtGroupList;

	for (const auto& pair : m_map){
		string key = pair.first;
		PARAM param = pair.second;

		string group = param.chGroupName;

		bool exist = false;
		for each (auto var in vtGroupList){
			if (var == group) {
				exist = true;
				break;
			}
		}

		if (exist == false) {
			vtGroupList.emplace_back(group);
		}
	}

	return vtGroupList;
}




pair<string, PARAM> gParameter::MakeParam(CString strGroupName, CString _strKey, bool bVal)
{

	pair<string, PARAM> pair_param;
	PARAM stParam;
	stParam.nDataType = TYPE_BOOLEAN;
	stParam.bValue = bVal;
	strncpy_s(stParam.chGroupName, strGroupName, STRING_DATA_LENGTH);

	string strKey = _strKey;

	pair_param.first = strKey;
	pair_param.second = stParam;

	return pair_param;
}

pair<string, PARAM> gParameter::MakeParam(CString strGroupName, CString _strKey, int nVal)
{
	pair<string, PARAM> pair_param;
	PARAM stParam;
	stParam.nDataType = TYPE_INT;
	stParam.nValue = nVal;
	strncpy_s(stParam.chGroupName, strGroupName, STRING_DATA_LENGTH);

	string strKey = _strKey;
	
	pair_param.first = strKey;
	pair_param.second = stParam;

	return pair_param;
}

pair<string, PARAM> gParameter::MakeParam(CString strGroupName, CString _strKey, float fVal)
{
	pair<string, PARAM> pair_param;
	PARAM stParam;
	stParam.nDataType = TYPE_DOUBLE;
	stParam.dValue = fVal;
	strncpy_s(stParam.chGroupName, strGroupName, STRING_DATA_LENGTH);

	string strKey = _strKey;

	pair_param.first = strKey;
	pair_param.second = stParam;


	return pair_param;
}



pair<string, PARAM> gParameter::MakeParam(CString strGroupName, CString _strKey, double dVal)
{
	pair<string, PARAM> pair_param;
	PARAM stParam;
	stParam.nDataType = TYPE_DOUBLE;
	stParam.dValue = dVal;
	strncpy_s(stParam.chGroupName, strGroupName, STRING_DATA_LENGTH);

	string strKey = _strKey;

	pair_param.first = strKey;
	pair_param.second = stParam;


	return pair_param;
}

pair<string, PARAM> gParameter::MakeParam(CString strGroupName, CString _strKey, CString strVal)
{
	pair<string, PARAM> pair_param;
	PARAM stParam;
	stParam.nDataType = TYPE_STRING;
	strncpy_s(stParam.chGroupName, strGroupName, STRING_DATA_LENGTH);

	strncpy_s(stParam.chValue, strVal, STRING_DATA_LENGTH);

	string strKey = _strKey;

	pair_param.first = strKey;
	pair_param.second = stParam;


	return pair_param;
}

pair<string, PARAM> gParameter::GetParam(string strKey)
{
	pair<string, PARAM> pair_param;

	for (const auto& pair : m_map) {
		string str = pair.first;
		if (strKey == str) {
			pair_param = pair;
			break;
		}
	}

	return pair_param;
}

CString gParameter::GetValueString(string strKey)
{
	CString str_val;

	pair<string, PARAM> pair_param = GetParam(strKey);
	
	if (pair_param.second.nDataType == TYPE_BOOLEAN) {
		if (pair_param.second.bValue == true) {
			str_val = "true";
		}
		else {
			str_val = "false";
		}
	}
	else if (pair_param.second.nDataType == TYPE_INT) {
		str_val.Format("%d", pair_param.second.nValue);
	}
	else if (pair_param.second.nDataType == TYPE_DOUBLE) {
		str_val.Format("%0.8f", pair_param.second.dValue);
	}
	else if (pair_param.second.nDataType == TYPE_STRING) {
		str_val.Format("%s", pair_param.second.chValue);
	}

	return str_val;
}


//map에 실제 넣는 함수
bool gParameter::SetParam(pair<string, PARAM> data)
{
	bool bRet = false;

	for (const auto& pair : m_map) {
		string strMapKey = pair.first;
		//기존에 있다면 set
		if (data.first == strMapKey) {
			PARAM stParam = pair.second;
			stParam = data.second;
			m_map[strMapKey] = stParam;
			bRet = true;
			break;
		}
	}

	//기존에 없다면 insert
	if (bRet == false) {
		m_map.insert(pair<string, PARAM>(data.first, data.second));
	}

	return true;
}

//value를 string 으로 주면 param 형식에 맞춰서 변환한 뒤, set 한다.
bool gParameter::SetParam(pair<string, PARAM> data, string value)
{
	bool bRet = false;

	for (const auto& pair : m_map) {
		string strMapKey = pair.first;
		//기존에 있다면 set
		if (data.first == strMapKey) {
			PARAM stParam = pair.second;

			if (stParam.nDataType == TYPE_BOOLEAN) {
				if (value == "true") {
					stParam.bValue = true;
				}
				else if (value == "false") {
					stParam.bValue = false;
				}
			}
			else if (stParam.nDataType == TYPE_INT) {
				stringstream ssInt(value);
				ssInt >> stParam.nValue;
			}
			else if (stParam.nDataType == TYPE_DOUBLE) {
				stringstream ssDouble(value);
				ssDouble >> stParam.dValue;
			}
			else if (stParam.nDataType == TYPE_STRING) {
				strncpy_s(stParam.chValue, value.c_str(), STRING_DATA_LENGTH);
			}
			m_map[strMapKey] = stParam;
			bRet = true;
			break;
		}
	}

	return true;
}

string gParameter::GetParameterPath()
{
	return _parameter_path;
}

void gParameter::SetParameterPath(CString strPath)
{
	_parameter_path = strPath;
}

void gParameter::LoadParam()
{
	// first, create a file instance
	mINI::INIFile file(_parameter_path);

	// next, create a structure that will hold data
	mINI::INIStructure ini;

	file.read(ini);

	//그룹리스트를 가져온다
	vector<string> vt_group_list = GetListGroup();

	for (int i = 0; i < vt_group_list.size(); i++) {
		string group_name = vt_group_list[i];

		//그룹이름으로 하위 리스트를 가져온다.
		vector<string> vt_param_in_group = GetListParamFromGroupName(group_name);

		for each (string key in vt_param_in_group){
			//ini에서 가져온 문자열 데이터를 해당 param에 reset

			//일단 파라미터 가져오자
			pair<string, PARAM> param = GetParam(key);
			
			//ini에서 읽은 데이터
			string& value = ini[group_name][key];

			//데이터타입에 맞춰 set 한다.
			bool ret = SetParam(param, value);

		}
	}
}

void gParameter::SaveParam()
{
	// first, create a file instance
	mINI::INIFile file(_parameter_path);

	// next, create a structure that will hold data
	mINI::INIStructure ini;

	//그룹리스트를 가져온다
	vector<string> vt_group_list = GetListGroup();

	for (int i = 0; i < vt_group_list.size(); i++) {
		string group_name = vt_group_list[i];

		//그룹이름으로 하위 리스트를 가져온다.
		vector<string> vt_param_in_group = GetListParamFromGroupName(group_name);

		for (int i = 0; i < vt_param_in_group.size(); i++) {
			string key = vt_param_in_group[i];
			//파라미터 변수 타입을 봐서 문자열로 변환해줘야 함
			CString str_val = GetValueString(key);
			ini[group_name][key] = str_val;
		}
	}
	
	file.write(ini);

}

void gParameter::TestIni()
{

	//일단 외부 함수에서 파라미터 초기화 작업을 해야한다. 아래처럼
	/*bool b = true;
	pair<string, PARAM> makedParam1 = m_param.MakeParam("param_key_bool", b);
	m_param.SetParam(makedParam1);
	int n = 34;
	pair<string, PARAM> makedParam2 = m_param.MakeParam("param_key_int", n);
	m_param.SetParam(makedParam2);
	float f = 2.4;
	pair<string, PARAM> makedParam3 = m_param.MakeParam("param_key_float", f);
	m_param.SetParam(makedParam3);
	double d = 3.56;
	pair<string, PARAM> makedParam4 = m_param.MakeParam("param_key_double", d);
	m_param.SetParam(makedParam4);
	CString str = "abcdefg";
	pair<string, PARAM> makedParam5 = m_param.MakeParam("param_key_string", str);
	m_param.SetParam(makedParam5);*/


	//// first, create a file instance
	//mINI::INIFile file("D:\\myfile.ini");

	//// next, create a structure that will hold data
	//mINI::INIStructure ini;

	//// now we can read the file
	//file.read(ini);

	//std::string strSection = "fruits";
	//std::string strDataName = "apples";
	//// read a value
	//std::string& amountOfApples = ini[strSection][strDataName];

	//// update a value
	//ini[strSection]["oranges"] = "20";

	//// add a new entry
	//ini[strSection]["bananas"] = "3.4";

	//// write updates to file
	//file.write(ini);
}

