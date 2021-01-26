#include "stdafx.h"
#include "groundDestroyManager.h"

groundDestroyManager::groundDestroyManager()
{
}

groundDestroyManager::~groundDestroyManager()
{
}

HRESULT groundDestroyManager::init()
{
	return S_OK;
}

void groundDestroyManager::release()
{
}

void groundDestroyManager::destroyElipse(string strKey, float x, float y, float radius)
{
	if (IMAGEMANAGER->findImage(strKey)) // 키값의 이미지가 있어야만 작동(뻑나는거 방지)
	{
		RECT temp = RectMake(x, y, 2 * radius, 2 * radius);		// 만든다 사각형
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));				// HBRUSH만 해도 현기증나는데 HPEN까지 쓴다고?!
		HBRUSH oldbrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), brush);
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), pen);
		Ellipse(IMAGEMANAGER->findImage(strKey)->getMemDC(), temp);		// 그린다 사각형		
		pen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldpen);		DeleteObject(pen);
		brush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldbrush);		DeleteObject(brush);
	}
}

void groundDestroyManager::destroyElipseCenter(string strKey, float x, float y, float radius)
{
	if (IMAGEMANAGER->findImage(strKey))
	{
		RECT temp = RectMakeCenter(x, y, 2 * radius, 2 * radius);
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldbrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), brush);
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), pen);
		Ellipse(IMAGEMANAGER->findImage(strKey)->getMemDC(),temp);
		pen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldpen);		DeleteObject(pen);		
		brush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldbrush);		DeleteObject(brush);
	}
}

void groundDestroyManager::destroyRect(string strKey, float x, float y, float width, float height)
{
	if (IMAGEMANAGER->findImage(strKey))
	{
		RECT temp = RectMake(x, y, width, height);
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldbrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), brush);
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), pen);
		Rectangle(IMAGEMANAGER->findImage(strKey)->getMemDC(), temp);
		pen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldpen);		DeleteObject(pen);
		brush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldbrush);		DeleteObject(brush);
	}
}

void groundDestroyManager::destroyRectCenter(string strKey, float x, float y, float width, float height)
{
	if (IMAGEMANAGER->findImage(strKey))
	{
		RECT temp = RectMakeCenter(x, y, width, height);
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldbrush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), brush);
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldpen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(), pen);
		Rectangle(IMAGEMANAGER->findImage(strKey)->getMemDC(), temp);
		pen = (HPEN)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldpen);		DeleteObject(pen);
		brush = (HBRUSH)SelectObject(IMAGEMANAGER->findImage(strKey)->getMemDC(),oldbrush);		DeleteObject(brush);
	}
}

