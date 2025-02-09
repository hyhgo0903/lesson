#include "stdafx.h"
#include "imageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

image* imageManager::addImage(string strKey, int width, int height)
{
	image* img = findImage(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;
	
	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}
// 위 아래 두개 오버라이딩 하는 이유 : 단일로 있으면 죽일때나 고개돌때 배열내 하나씩 못하고 다같이 돌음
// 몇번쨰 프레임으로 하라고 지정
image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘라
	img = new image;

	if (FAILED(img->init(fileName, width, height, frameX, frameY, trans, transColor)))
	{
		SAFE_DELETE(img);

		return nullptr;
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}

image* imageManager::findImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	//찾았다
	if (key != _mImageList.end())
	{
		return key->second;
	}

	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;
}

BOOL imageManager::deleteAll()
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else ++iter;
	}

	_mImageList.clear();

	return 0;
}

void imageManager::render(string strKey, HDC hdc)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	image* img = findImage(strKey);

	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	image* img = findImage(strKey);

	if (img) img->loopRender(hdc, drawArea, offSetX, offSetY);
}
