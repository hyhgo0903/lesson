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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//WPARAM : 키보드 눌르는 것이든, 마우스 좌,우,휠 클릭하면 얘가 감지함
	//LPARAM : 마우스 좌표를 감지함

	PAINTSTRUCT ps;
	HDC			hdc;	//<-- 얘 진짜 중요함

	static RECT rc; // 전역으로 설정해줘야함
	static RECT rc2;

	switch (iMessage)
	{		
		case WM_CREATE: // 윈도우 창이 생성될때 딱 한번 실행됨
			// rc = { 100,100,200,200 }; // 공간만 잡았지 이것만으로 실제로는 안보임
			rc = RectMakeCenter(WINSIZEX / 2-100, WINSIZEX / 2, 100, 100);
			rc2 = RectMakeCenter(WINSIZEX / 2 +100, WINSIZEX / 2 , 100, 100);
			break;
		case WM_PAINT:
		{
			//윈도우창을 옮기거나 크기를 줄이거나할때 갱신이됨
			hdc = BeginPaint(hWnd, &ps);

			Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
			// 이게 있어야 그려짐
			Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);

			//LineMake(hdc, 100, 100, 300, 400);
			//RectangleMake(hdc, WINSIZEX / 2, WINSIZEY / 2, 100, 100);
			//RectangleMakeCenter(hdc, WINSIZEX / 2, WINSIZEY / 2, 100, 100);
			
			//EllipseMakeCenter(hdc, WINSIZEX / 2, WINSIZEY / 2, 400, 400);
			//EllipseMakeCenter(hdc, WINSIZEX / 2, WINSIZEY / 2, 350, 350);




			EndPaint(hWnd, &ps);
		}
		break;

		case WM_KEYDOWN: // 키를 눌렀을때
			switch (wParam)
			{
				case VK_LEFT:
					if (rc.left <= 0) break; // 탈출방지
					rc.left -= 5;
					rc.right -= 5;
					InvalidateRect(hWnd, NULL, true);
					// 핸들, 윈도우에서 얼만큼갱신, 지울래안지울래
				break;
				case VK_RIGHT:
					rc.left += 5;
					rc.right += 5;
					
					if (rc.right >= rc2.left)
					{
						int width = rc2.right - rc2.left;
						rc2.left = rc.right;
						rc2.right = rc2.left + width;
					}

					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_UP:
					rc.top -= 5;
					rc.bottom -= 5;
					InvalidateRect(hWnd, NULL, true);
				break;
				case VK_DOWN:
					rc.top += 5;
					rc.bottom += 5;
					InvalidateRect(hWnd, NULL, true);
				break;
			}

		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
// 윈도우 창에 위엣줄 감안하려고(0,0)이면 짤리는 문제
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
