#include "stdafx.h"
#include "image.h"


image::image()
	: _backBuffer(NULL)
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	if (_backBuffer != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_backBuffer = new IMAGE_INFO;
	_backBuffer->hMemDC = CreateCompatibleDC(hdc);
	_backBuffer->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_backBuffer->hOBit = (HBITMAP)SelectObject(_backBuffer->hMemDC, _backBuffer->hBit);
	_backBuffer->width = width;
	_backBuffer->height = height;

	
	if (_backBuffer == NULL)
	{
		release();

		return E_FAIL;
	}



	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

void image::release()
{
	if (_backBuffer)
	{
		SelectObject(_backBuffer->hMemDC, _backBuffer->hOBit);
		DeleteObject(_backBuffer->hBit);
		DeleteDC(_backBuffer->hMemDC);

		SAFE_DELETE(_backBuffer);
	}

}

void image::render(HDC hdc, int destX, int destY)
{
	//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
	BitBlt(hdc,					//복사할 DC
		destX,					//복사할 좌표 X (left)
		destY,					//복사할 좌표 Y (top)
		_backBuffer->width,		//복사할 크기
		_backBuffer->height,	
		_backBuffer->hMemDC,	//복사될 DC
		0, 0,					//복사될 기준점 (left, top)
		SRCCOPY);				//변형없이 복사할거임
}
