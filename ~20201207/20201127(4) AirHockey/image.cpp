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

	_trans = trans;				//Ư�� Į���� ������ ����
	_transColor = transColor;	//�� ���� Į��

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
	_trans = trans;				//Ư�� Į���� ������ ����
	_transColor = transColor;	//�� ���� Į��

	//��� �� ������ �ְ�ʹٰų� �ҋ� ���� �Ǵµ�... ��..
	//�Ⱦ�����
}

void image::render(HDC hdc, int destX, int destY)
{
	//
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ������  DC
			destX,					//����� ��ǥ X
			destY,					//����� ��ǥ Y
			_imageInfo->width,		//����� ũ�� (����)
			_imageInfo->height,		//����� ũ�� (����)
			_imageInfo->hMemDC,		//�����ؿ� DC
			0, 0,					//�����ؿ� ��ǥ X, Y
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,		//������ ����ũ��
			_transColor
		);
	}
	else
	{
		//�갡 �װ��Դϴ� DC���� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc,					//������ DC
			destX,					//������ ��ǥ X (left)
			destY,					//������ ��ǥ Y (top)
			_imageInfo->width,		//������ ũ��
			_imageInfo->height,
			_imageInfo->hMemDC,		//����� DC
			0, 0,					//����� ������ (left, top)
			SRCCOPY);				//�������� �����Ұ���
	}


}
