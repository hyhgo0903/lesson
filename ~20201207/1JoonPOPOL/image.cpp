#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	
	if (_imageInfo == NULL)
	{
		release();

		return E_FAIL;
	}



	ReleaseDC(_hWnd, hdc);


	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값

	//어떠한 색 반전을 주고싶다거나 할떄 쓰면 되는데... 음..
	//안쓰더라구
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의  DC
			0,						//복사될 좌표 X
			0,						//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 좌표 X, Y
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,					//복사할 DC
			0,						//복사할 좌표 X (left)
			0,						//복사할 좌표 Y (top)
			_imageInfo->width,		//복사할 크기
			_imageInfo->height,
			_imageInfo->hMemDC,		//복사될 DC
			0, 0,					//복사될 기준점 (left, top)
			SRCCOPY);				//변형없이 복사할거임
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	//
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의  DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			_imageInfo->width,		//복사될 크기 (가로)
			_imageInfo->height,		//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			0, 0,					//복사해올 좌표 X, Y
			_imageInfo->width,		//복사할 가로크기
			_imageInfo->height,		//복사할 세로크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,					//복사할 DC
			destX,					//복사할 좌표 X (left)
			destY,					//복사할 좌표 Y (top)
			_imageInfo->width,		//복사할 크기
			_imageInfo->height,
			_imageInfo->hMemDC,		//복사될 DC
			0, 0,					//복사될 기준점 (left, top)
			SRCCOPY);				//변형없이 복사할거임
	}


}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//복사될 영역의  DC
			destX,					//복사될 좌표 X
			destY,					//복사될 좌표 Y
			sourWidth,				//복사될 크기 (가로)
			sourHeight,				//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			sourX, sourY,			//복사해올 좌표 X, Y
			sourWidth,				//복사할 가로크기
			sourHeight,				//복사할 세로크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,					//복사할 DC
			destX,					//복사할 좌표 X (left)
			destY,					//복사할 좌표 Y (top)
			sourWidth,				//복사할 크기
			sourHeight,
			_imageInfo->hMemDC,		//복사될 DC
			sourX, sourY,			//복사될 기준점 (left, top)
			SRCCOPY);				//변형없이 복사할거임
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//범위를 구하자
	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;					
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//그려와야할 영역만큼을 구해줌
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//그려올 영역 구해줌
		sourHeight = rcSour.bottom - rcSour.top;

		//다시 뿌려야할 영역을 세팅해서 렌더로 뿌릴 예정임.
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//그려와야할 영역만큼을 구해줌
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}


}
