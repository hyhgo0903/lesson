#pragma once
#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <iostream>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include "commonMacroFunction.h"

using namespace std;

//==================================
// ## 디파인 문 ## 20.11.12 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("25기 API"))
#define WINSTARTX 50		//윈도우 시작좌표 X지점
#define WINSTARTY 50		//윈도우 시작좌표 Y지점
#define WINSIZEX 800		//윈도우 가로크기
#define WINSIZEY 600		//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU