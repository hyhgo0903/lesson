#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

// �������޸�(new image�ϰ� �̹��������Ϳ� �ְ�)
// �˾Ƽ� �����̹������� �ش�Ű�� �ο��Ͽ� �̹���ã�� ����ؿ��� ���ϰ�..

class imageManager : public singletonBase<imageManager>
{ // �̱������� �����Ϸ���
private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;
	// �̹����� �ش�Ű���� �ο��Ϸ���
public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);
	// �� �빮�� bool�ΰ� ? - > �� ������ ȣȯ��������..
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
};

