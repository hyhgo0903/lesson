#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{
}

HRESULT iniDataManager::init()
{
	return S_OK;
}

void iniDataManager::addData(const char * subject, const char * title, const char * body)
{ // ex ) INIDATA->addData("동현", "드립력", "1300");
	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData; // 태그넣는거 (data's'가 arr)
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData); // arr에 넣는거

}

void iniDataManager::iniSave(const char * fileName)
{ // ex) INIDATA->iniSave("25기");
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title,
			vData[0].body, str); // 데이터들이 대괄호 안에 들어가서 차곡차곡 담김
		vData.clear(); // 한번쓰면 날려줘야(clear)
	}

	_vIniData.clear();

}

string iniDataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{ // ex) _str = INIDATA->loadDataString("25기", "동현", "드립력");
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {}; // 64는 버퍼 나중에 늘리든가 줄이든가
	GetPrivateProfileString(subject, title, "", data, 64, str);

	string strData = data;

	return strData;
}

int iniDataManager::loadDataInterger(const char * fileName, const char * subject, const char * title)
{ // ex) _int = INIDATA->loadDataInterger("25기", "동현", "드립력");
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	
	return GetPrivateProfileInt(subject, title, 0, str);
}
