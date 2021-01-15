#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	SetTimer(_hWnd, 1, 10, NULL);
	/*SetTimer(윈도우핸들값,
	타이머아이디(이미 있으면 덮어씀),
	반복할 시간(1000millisecond = 1s) 10~2145483647,
	설정한 시간간격으로 호출될 함수의 주소
	ㄴ널로하고 WM_TIMER메시지를 사용해도 됨
	ㄴ일정시간 마다 WM_TIMER 메시지를 발생
	ㄴWM_TIMER 메시지가 발생하면 OnTimer 함수를 호출
	)*/

	return S_OK;
	// 잘 실행했으면 S_OK반환
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, true);
}

void gameNode::render(HDC hdc)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC			hdc;	//<-- 얘 진짜 중요함

	switch (iMessage)
	{
		case WM_TIMER:
			this->update();
			// this : 객체 자기 자신을 의미
		break;
		case WM_PAINT:
		{
			hdc = BeginPaint(_hWnd, &ps);

			this->render(hdc);

			EndPaint(_hWnd, &ps);
		}
		break;


		case WM_MOUSEMOVE:
			_ptMouse.x = LOWORD(lParam);
			_ptMouse.y = HIWORD(lParam);


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
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
