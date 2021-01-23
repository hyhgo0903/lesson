#pragma once
#include "singletonBase.h"

class groundDestroyManager : public singletonBase<groundDestroyManager>
{
public:
	groundDestroyManager();
	~groundDestroyManager();

	HRESULT init();
	virtual void release();

	// 사용례는 playGround.cpp에..

	// 원형으로 박살(이미지key, x좌표, y좌표, 반지름)
	void destroyElipse(string strKey, float x, float y, float radius);
	// 이건 괜히 만든것같음

	// 원형으로 박살 센터(이미지key, x좌표, y좌표, 반지름)
	void destroyElipseCenter(string strKey, float x, float y, float radius);

	// 렉트 박살(이미지key, x좌표, y좌표, 너비, 높이)
	void destroyRect(string strKey, float x, float y, float width, float height);

	// 렉트 박살 센터(이미지key, x좌표, y좌표, 너비, 높이)
	void destroyRectCenter(string strKey, float x, float y, float width, float height);

};

