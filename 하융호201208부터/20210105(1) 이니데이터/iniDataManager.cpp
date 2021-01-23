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
{ // ex ) INIDATA->addData("����", "�帳��", "1300");
	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData; // �±׳ִ°� (data's'�� arr)
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData); // arr�� �ִ°�

}

void iniDataManager::iniSave(const char * fileName)
{ // ex) INIDATA->iniSave("25��");
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
			vData[0].body, str); // �����͵��� ���ȣ �ȿ� ���� �������� ���
		vData.clear(); // �ѹ����� �������(clear)
	}

	_vIniData.clear();

}

string iniDataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{ // ex) _str = INIDATA->loadDataString("25��", "����", "�帳��");
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {}; // 64�� ���� ���߿� �ø��簡 ���̵簡
	GetPrivateProfileString(subject, title, "", data, 64, str);

	string strData = data;

	return strData;
}

int iniDataManager::loadDataInterger(const char * fileName, const char * subject, const char * title)
{ // ex) _int = INIDATA->loadDataInterger("25��", "����", "�帳��");
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	
	return GetPrivateProfileInt(subject, title, 0, str);
}
