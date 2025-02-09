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

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;
	
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

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
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
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//특정 칼라값을 날릴지 여부
	_transColor = transColor;	//그 날릴 칼라값

	//알파블렌드 설정
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = width;
	_blendImage->height = height;

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

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

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

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_imageInfo->hMemDC,		//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,					
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,						//복사할 DC
			destX,						//복사할 좌표 X (left)
			destY,						//복사할 좌표 Y (top)
			_imageInfo->frameWidth,			//복사할 크기
			_imageInfo->frameHeight,	
			_imageInfo->hMemDC,			//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 기준점 (left, top)
			SRCCOPY);					//변형없이 복사할거임
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//복사될 영역의  DC
			destX,						//복사될 좌표 X
			destY,						//복사될 좌표 Y
			_imageInfo->frameWidth,		//복사될 크기 (가로)
			_imageInfo->frameHeight,	//복사될 크기 (세로)
			_imageInfo->hMemDC,			//복사해올 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//복사할 가로크기
			_imageInfo->frameHeight,	//복사할 세로크기
			_transColor
		);
	}
	else
	{
		//얘가 그것입니다 DC영역 간의 고속복사를 해주는 함수
		BitBlt(hdc,						//복사할 DC
			destX,						//복사할 좌표 X (left)
			destY,						//복사할 좌표 Y (top)
			_imageInfo->frameWidth,			//복사할 크기
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,			//복사될 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 기준점 (left, top)
			SRCCOPY);					//변형없이 복사할거임
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//실제 이미지 소스에 알파블렌드를 적용 시켜주는 함수 BYTE == 투명도 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	//원본이미지를 알파렌더링할 DC(_blendImage->hMemDC)
	//로 옮겨서 마젠타를 날려

	// 무겁다(알파처리할 이미지 한 장을 더 그리기 때문)
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//실제 이미지 소스에 알파블렌드를 적용 시켜주는 함수 BYTE == 투명도 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//#########################################
//          과제부분 ( 이하 3함수)
// #########################################


// 활용예: spaceShip.cpp로
void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//여기는 여러분이 한 번 채워보세요~ *^^*
	//한 번 공부해보라고~

	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight, _transColor); // 위 둘에서 sour할 만큼만 그려줌

		AlphaBlend(hdc, destX, destY, sourWidth,
			sourHeight, _blendImage->hMemDC,
			0, 0, // 이미 hMemDC의 0,0에 그렸으므로 여기는 그냥 0,0 으로 갖고오면 되는 거였음
			sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth,
			sourHeight, _blendImage->hMemDC,
			0, 0,
			sourWidth, sourHeight, _blendFunc);
	}
}


// 활용예: enemy.cpp랑 bullets.cpp의 렉트 미사일 렌더
void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);
			
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC,	0,		0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
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
