#include "stdafx.h"

//API : Application Programming Interface

HINSTANCE	_hInstance;	//인스턴스 
HWND		_hWnd;		//윈도우 핸들
LPCTSTR		_lpszClass = TEXT("25기");

//함수 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszClass, int cmdShow)
{
	MSG		message;	//윈도우 메시지를 담은 구조체
	WNDCLASS wndClass;	//윈도우 클래스 구조체

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//윈도우 클래스 여분 메모리
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//윈도우 창 백그라운드 색깔
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//커서 모양
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//아이콘 모양
	wndClass.hInstance = hInstance;									//인스턴스 등록
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = WINNAME;								//윈도우 클래스 등록
	wndClass.lpszMenuName = NULL;									//메뉴 여부
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 스타일~

	RegisterClass(&wndClass);										//윈도우 정보 등록

	_hWnd = CreateWindow(				//정보를 토대로 윈도우 창 만든다
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,			//윈도우 창 스타일
		WINSTARTX,						//윈도우 시작좌표 X
		WINSTARTY,						//윈도우 시작좌표 Y
		WINSIZEX,						//윈도우 가로크기
		WINSIZEY,						//윈도우 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(_hWnd, cmdShow);			//얘가 있어야 윈도우 창이 나타남

	//GetMessage : 윈도우에서 어떠한 메시지가 발생하면 그때 처리함
	//PeekMessage : 메시지가 있든 없든 상시 돌고 있음
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);	//윈도우 메시지를 받아옴
		DispatchMessage(&message);	//위에 받아온 메시지를 직접 컴퓨터에게 전달함
	}

	return message.wParam;
}

//여기 쓰면 전역변수가 됨
enum BOX
{
	BOX_FIRST,	//0
	BOX_SECOND,	//1
	BOX_END		//2
};

BOX CURRENTBOX;		//이넘문을 CURRENTBOX라 부를꺼임

//rc[2]개
RECT rc[BOX_END], rcIN;


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : 키보드 눌르는 것이든, 마우스 좌,우,휠 클릭하면 얘가 감지함
	//LPARAM : 마우스 좌표를 감지함

	PAINTSTRUCT ps;
	HDC			hdc;	//<-- 얘 진짜 중요함

	switch (iMessage)
	{
		//윈도우 창이 생성될때 따악~ 한 번 실행됨
		case WM_CREATE:
			rc[BOX_FIRST] = RectMakeCenter(WINSIZEX / 2 - 150, WINSIZEY / 2, 100, 100);
			rc[BOX_SECOND] = RectMakeCenter(WINSIZEX / 2 + 150, WINSIZEY / 2, 100, 100);
			rcIN = RectMakeCenter(WINSIZEX / 2 - 150, WINSIZEY / 2, 50, 50);

			CURRENTBOX = BOX_FIRST;
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			for (int i = 0; i < BOX_END; ++i)
			{
				Rectangle(hdc, rc[i].left, rc[i].top, rc[i].right, rc[i].bottom);
			}
			Rectangle(hdc, rcIN.left, rcIN.top, rcIN.right, rcIN.bottom);
		

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_LEFT:
					rc[CURRENTBOX].left -= 5;
					rc[CURRENTBOX].right -= 5;

					if (rcIN.right > rc[CURRENTBOX].right)
					{
						int width = rcIN.right - rcIN.left;

						rcIN.right = rc[CURRENTBOX].right;
						rcIN.left = rcIN.right - width;
					}

				break;
				case VK_RIGHT:
					rc[CURRENTBOX].left += 5;
					rc[CURRENTBOX].right += 5;

					if (rcIN.left < rc[CURRENTBOX].left)
					{
						int width = rcIN.right - rcIN.left;

						rcIN.left = rc[CURRENTBOX].left;
						rcIN.right = rcIN.left + width;
					}
				break;
				case VK_UP:
					rc[CURRENTBOX].top -= 5;
					rc[CURRENTBOX].bottom -= 5;

					if (rcIN.bottom > rc[CURRENTBOX].bottom)
					{
						int height = rcIN.bottom - rcIN.top;

						rcIN.bottom = rc[CURRENTBOX].bottom;
						rcIN.top = rcIN.bottom - height;
					}

				break;
				case VK_DOWN:
					rc[CURRENTBOX].top += 5;
					rc[CURRENTBOX].bottom += 5;

					if (rcIN.top < rc[CURRENTBOX].top)
					{
						int height = rcIN.bottom - rcIN.top;

						rcIN.top = rc[CURRENTBOX].top;
						rcIN.bottom = rcIN.top + height;		
					}
				break;
				case VK_ESCAPE:
					PostQuitMessage(0);
					// esc누르면 꺼지도록
				break;
			}
			RECT temp;
			if (IntersectRect(&temp, &rc[BOX_FIRST], &rc[BOX_SECOND]))
			{ // temp에 두 사각형 교차점을 저장
				switch (CURRENTBOX)
				{
					case BOX_FIRST:
						CURRENTBOX = BOX_SECOND;
					break;
					case BOX_SECOND:
						CURRENTBOX = BOX_FIRST;
					break;

				}

				rcIN = RectMakeCenter((rc[CURRENTBOX].right + rc[CURRENTBOX].left) / 2,
					(rc[CURRENTBOX].bottom + rc[CURRENTBOX].top) / 2, 50, 50);
			}

				/*
			if (rc[BOX_FIRST].right > rc[BOX_SECOND].left &&
				rc[BOX_FIRST].left  < rc[BOX_SECOND].right &&
				rc[BOX_FIRST].top   < rc[BOX_SECOND].bottom &&
				rc[BOX_FIRST].bottom > rc[BOX_SECOND].top)
			{
				switch (CURRENTBOX)
				{
					case BOX_FIRST:
						CURRENTBOX = BOX_SECOND;
					break;
					case BOX_SECOND:
						CURRENTBOX = BOX_FIRST;
					break;				
				}

				rcIN = RectMakeCenter((rc[CURRENTBOX].right + rc[CURRENTBOX].left) / 2,
					(rc[CURRENTBOX].bottom + rc[CURRENTBOX].top) / 2, 50, 50);
			}*/
			
			InvalidateRect(hWnd, NULL, true);
		break;


		case WM_DESTROY:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//클라이언트 영역 재조정을 위한!!!!
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	//얘가 실제로 영역 조정하는 거임
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}
