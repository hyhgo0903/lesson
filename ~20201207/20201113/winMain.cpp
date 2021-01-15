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

RECT _rc;
POINT _ptMouse;
bool _isIn;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : 키보드 눌르는 것이든, 마우스 좌,우,휠 클릭하면 얘가 감지함
	//LPARAM : 마우스 좌표를 감지함

	PAINTSTRUCT ps;
	HDC			hdc;	//<-- 얘 진짜 중요함

	char str[128];

	switch (iMessage)
	{
		//윈도우 창이 생성될때 따악~ 한 번 실행됨
		case WM_CREATE:
			_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(_hWnd, &ps);

			Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);

			sprintf_s(str, "마우스 X : %d, 마우스 Y : %d", _ptMouse.x, _ptMouse.y);
			TextOut(hdc, 15, 15, str, strlen(str));
			// 유니코드면 이게 안됨.(속성에서 문자집합)
			sprintf_s(str, "마우스 있니 : %d", _isIn);
			TextOut(hdc, 15, 30, str, strlen(str));
			

			EndPaint(_hWnd, &ps);
		}
		break;
		//마우스 왼쪽 버튼 눌렀다
		case WM_LBUTTONDOWN:

		break;
		//마우스 왼쪽 버튼 뗐다
		case WM_LBUTTONUP:

		break;
		//마우스 움직인다
		case WM_MOUSEMOVE:
			_ptMouse.x = LOWORD(lParam);
			_ptMouse.y = HIWORD(lParam);

			if (_rc.left < _ptMouse.x && _ptMouse.x < _rc.right &&
				_rc.top < _ptMouse.y && _ptMouse.y < _rc.bottom)
			{
				_isIn = true;
			}
			else _isIn = false;



			InvalidateRect(_hWnd, NULL, true);
		break;


		case WM_KEYDOWN:
			switch (wParam)
			{
				
				case VK_ESCAPE:
					PostQuitMessage(0);
				break;
			}
		break;

		case WM_DESTROY:
			PostMessage(_hWnd, WM_DESTROY, 0, 0);
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

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅 해주는 함수
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);

}
