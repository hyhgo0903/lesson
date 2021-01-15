#pragma once
#include "singletonBase.h"
#include "image.h"
#include <map>

// 종전과달리(new image하고 이미지포인터에 넣고)
// 알아서 동적이미지에서 해당키값 부여하여 이미지찾고 출력해오기 편하게..

class imageManager : public singletonBase<imageManager>
{ // 싱글톤으로 생성하려고
private:
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;
	// 이미지에 해당키값을 부여하려고
public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);

	image* findImage(string strKey);

	BOOL deleteImage(string strKey);
	// 왜 대문자 bool인가 ? - > 맥 윈도우 호환성떄문에..
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
};

