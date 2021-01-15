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
	
	//없으면 새로 하나 할당해줘서 널반환
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return nullptr; // 초기화하는데 실패한거면 삭제후 널반환
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}
// 댕글링포인터???? 손코딩도 시킨다함
image* imageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//해당 이미지가 있으면 그 이미지를 반환해라
	if (img) return img;

	//없으면 새로 하나 할당해줘서 널반환
	img = new image;

	if (FAILED(img->init(fileName, width, height, trans, transColor)))
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
	//맵이미지리스트에서 키를 찾아서

	//끝까지 갈때까지 찾으면
	if (key != _mImageList.end())
	{
		return key->second;
	} // 해당키값으로 있으면 그 이미지 반환
	//   (이터레이터가 해당키값 반환)

	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{ // 키값 찾으면 이미지를 삭제하고 true아니면 false로 반환
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
	{//널이 아니면 삭제를 하고 아니면 이터를 올린다.
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
			// 삭제된 공간을 가리키는 일이 없도록 이터레이터를 삭제해줘야함
		}
		else ++iter; // 전치가 빠름
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
