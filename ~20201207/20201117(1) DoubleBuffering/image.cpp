#include "stdafx.h"
#include "image.h"
// hdc공간에 계속 갱신을 하므로 깜빡
//(invalidaterect)
// => 더블버퍼링(참고 유니티는 트리플버퍼링)

//백dc: 뒤에있는 dc영역을 만듦.연산을 여기서 하고
//복사해주는 함수(Bitblt)가 hdc에 쏴줌(자동 고속복사)

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
	//CreateCompatibleDC : 빈dc공간을 만들어줌
	_backBuffer->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	//CreateCompatibleBitmap : 빈비트맵공간을 만들어줌
	_backBuffer->hOBit = (HBITMAP)SelectObject(_backBuffer->hMemDC, _backBuffer->hBit);
	_backBuffer->width = width;
	_backBuffer->height = height;
	// 가로 세로크기는 윈도우에 맞출것
	
	if (_backBuffer == NULL)
	{ // 혹시 널값이면 예외처리
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
	} // 있으면 지우고 널값

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
