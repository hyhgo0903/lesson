#pragma once
#include "singletonBase.h"

class groundDestroyManager : public singletonBase<groundDestroyManager>
{
public:
	groundDestroyManager();
	~groundDestroyManager();

	HRESULT init();
	virtual void release();

	// ���ʴ� playGround.cpp��..

	// �������� �ڻ�(�̹���key, x��ǥ, y��ǥ, ������)
	void destroyElipse(string strKey, float x, float y, float radius);
	// �̰� ���� ����Ͱ���

	// �������� �ڻ� ����(�̹���key, x��ǥ, y��ǥ, ������)
	void destroyElipseCenter(string strKey, float x, float y, float radius);

	// ��Ʈ �ڻ�(�̹���key, x��ǥ, y��ǥ, �ʺ�, ����)
	void destroyRect(string strKey, float x, float y, float width, float height);

	// ��Ʈ �ڻ� ����(�̹���key, x��ǥ, y��ǥ, �ʺ�, ����)
	void destroyRectCenter(string strKey, float x, float y, float width, float height);

};

