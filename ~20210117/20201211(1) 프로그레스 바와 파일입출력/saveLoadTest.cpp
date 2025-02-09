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
	//파일 입출력은 다양한 방식이 존재합니다
	//C - FILE* (기능은 없는대 엄청 빠름)
	//C++ - ifstream, ofstream(기능 짱짱맨, 조금 느림)
	// ifstream = input file stream , ofstrem = output~~
	//Win32API CreateFile() 함수가 있음.

	HANDLE file;
	DWORD write;

	char str[256] = "여러분 준포폴 화이팅 입니다";

	file = CreateFile("참스승의 마음.txt", GENERIC_WRITE, FALSE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	// GENERIC_WRITE : 써야되니까
	// FALSE : 공유모드 X
	// NULL : 보안속성
	// CREATE_ALWAYS : 항상 새로 만들어줌(재차 눌러도 새로생성)

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);

}

void saveLoadTest::load()
{
	HANDLE file;
	DWORD read;

	char str[256];

	file = CreateFile("참스승의 마음.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// GENERIC_READ
	// OPEN_EXISTING : 한번만열고 한번만 불러온다?

	ReadFile(file, str, strlen(str), &read, NULL);
	
	CloseHandle(file);

	MessageBox(_hWnd, str, "화이팅 25기", MB_OK);

}
