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
	_hdc = GetDC(_hWnd);
	_managerInit = false;


	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		//SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		//KillTimer(_hWnd, 1);

		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();
		TXTDATA->release();
		TXTDATA->releaseSingleton();
		INIDATA->releaseSingleton();
	}
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	SOUNDMANAGER->update();

}

void gameNode::render()
{

}

void gameNode::setMap()
{
}

void gameNode::save()
{
}

void gameNode::load()
{
}

void gameNode::tempSave()
{
}

void gameNode::tempLoad()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	PAINTSTRUCT ps;
	HDC			hdc;	//<-- 얘 진짜 중요함

	switch (iMessage)
	{
		case WM_PAINT:
			this->render();
		break;
		case WM_TIMER:
			this->update();
		break;

		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

			if (_leftButtonDown) this->setMap();
		break;

		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
			this->tempSave();
			this->setMap();
		break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;
		
		//마우스클릭을 신호로 반환해주는 애가 WM_COMMAND.
		case WM_COMMAND:

			switch (LOWORD(wParam))
			{
				case CTRL_SAVE:
					this->save();
				break;
				case CTRL_LOAD:
					this->load();
					InvalidateRect(hWnd, NULL, false);
				break;
				case CTRL_2X2:
					this->load();
				break;
				case CTRL_Z:
					this->tempLoad();
					InvalidateRect(hWnd, NULL, false);
				break;
				default:
					this->setCtrlSelect(LOWORD(wParam));
				break;
			}

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
