#pragma once
#include "image.h"

#define GRAVITY 0.2f
#define MAXWIND 1.0f
#define SNOWMAX 25

//����۶�� �� ��Ʈ�� �̹����� �ϳ� �����صд�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", MAPSIZEX, MAPSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �Ҳ��� ����

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual HRESULT init(int x);    //���⼭ ���������ϴ±���..
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����

	
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

