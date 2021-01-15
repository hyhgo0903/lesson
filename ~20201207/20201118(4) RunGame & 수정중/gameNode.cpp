#include "stdafx.h"
#include "gameNode.h"


void gameNode::setBackBuffer()
{
	_backBuffer = new image;
	_backBuffer->init(WINSIZEX, WINSIZEY);
}

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

	setBackBuffer();

	return S_OK;
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);

	KEYMANAGER->releaseSingleton();
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
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
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

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
