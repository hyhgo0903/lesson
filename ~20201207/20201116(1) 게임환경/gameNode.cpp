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
	/*SetTimer(�������ڵ鰪,
	Ÿ�̸Ӿ��̵�(�̹� ������ ���),
	�ݺ��� �ð�(1000millisecond = 1s) 10~2145483647,
	������ �ð��������� ȣ��� �Լ��� �ּ�
	���η��ϰ� WM_TIMER�޽����� ����ص� ��
	�������ð� ���� WM_TIMER �޽����� �߻�
	��WM_TIMER �޽����� �߻��ϸ� OnTimer �Լ��� ȣ��
	)*/

	return S_OK;
	// �� ���������� S_OK��ȯ
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
	HDC			hdc;	//<-- �� ��¥ �߿���

	switch (iMessage)
	{
		case WM_TIMER:
			this->update();
			// this : ��ü �ڱ� �ڽ��� �ǹ�
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
