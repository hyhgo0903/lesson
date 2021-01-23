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
	// ifstream = input file stream , ofstrem = output~~
	//Win32API CreateFile() �Լ��� ����.

	HANDLE file;
	DWORD write;

	char str[256] = "������ ������ ȭ���� �Դϴ�";

	file = CreateFile("�������� ����.txt", GENERIC_WRITE, FALSE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// GENERIC_WRITE : ��ߵǴϱ�
	// FALSE : ������� X
	// NULL : ���ȼӼ�
	// CREATE_ALWAYS : �׻� ���� �������(���� ������ ���λ���)

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
	// GENERIC_READ
	// OPEN_EXISTING : �ѹ������� �ѹ��� �ҷ��´�?

	ReadFile(file, str, strlen(str), &read, NULL);
	
	CloseHandle(file);

	MessageBox(_hWnd, str, "ȭ���� 25��", MB_OK);

}
