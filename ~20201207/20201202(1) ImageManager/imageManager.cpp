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

	//�ش� �̹����� ������ �� �̹����� ��ȯ�ض�
	if (img) return img;
	
	//������ ���� �ϳ� �Ҵ����༭ �ι�ȯ
	img = new image;

	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);

		return nullptr; // �ʱ�ȭ�ϴµ� �����ѰŸ� ������ �ι�ȯ
	}

	_mImageList.insert(make_pair(strKey, img));

	return img;
}
// ��۸�������???? ���ڵ��� ��Ų����
image* imageManager::addImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	image* img = findImage(strKey);

	//�ش� �̹����� ������ �� �̹����� ��ȯ�ض�
	if (img) return img;

	//������ ���� �ϳ� �Ҵ����༭ �ι�ȯ
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
	//���̹�������Ʈ���� Ű�� ã�Ƽ�

	//������ �������� ã����
	if (key != _mImageList.end())
	{
		return key->second;
	} // �ش�Ű������ ������ �� �̹��� ��ȯ
	//   (���ͷ����Ͱ� �ش�Ű�� ��ȯ)

	return nullptr;
}

BOOL imageManager::deleteImage(string strKey)
{ // Ű�� ã���� �̹����� �����ϰ� true�ƴϸ� false�� ��ȯ
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
	{//���� �ƴϸ� ������ �ϰ� �ƴϸ� ���͸� �ø���.
		if (iter->second != NULL)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
			// ������ ������ ����Ű�� ���� ������ ���ͷ����͸� �����������
		}
		else ++iter; // ��ġ�� ����
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
