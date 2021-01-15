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
	KEYMANAGER->init();

	return S_OK;
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);

	KEYMANAGER->releaseSingleton();
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
