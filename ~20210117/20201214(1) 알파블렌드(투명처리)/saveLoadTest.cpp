#include "stdafx.h"
#include "saveLoadTest.h"

void saveLoadTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		save();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		load();
	}
}

void saveLoadTest::save()
{
	//���� ������� �پ��� ����� �����մϴ�
	//C - FILE* (����� ���´� ��û ����)
	//C++ - ifstream, ofstream(��� ¯¯��, ���� ����)
	//Win32API CreateFile() �Լ��� ����.

	HANDLE file;
	DWORD write;

	char str[256] = "������ ������ ȭ���� �Դϴ�";

	file = CreateFile("�������� ����.txt", GENERIC_WRITE, FALSE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	char str[256];

	file = CreateFile("�������� ����.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);
	
	CloseHandle(file);

	MessageBox(_hWnd, str, "ȭ���� 25��", MB_OK);

}
