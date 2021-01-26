#pragma once
#include "image.h"

//����۶�� �� ��Ʈ�� �̹����� �ϳ� �����صд�
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//���̺� ��ư �ν�
	CTRL_LOAD,			//�ε� ��ư �ν�
	CTRL_TERRAINDRAW,	//���� ��ư
	CTRL_OBJDRAW,		//������Ʈ ��ư
	CTRL_ERASER,		//���찳 ��ư
	CTRL_2X2,
	CTRL_4X4,
	CTRL_Z,
	CTRL_END
};


class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �Ҳ��� ����

public:
	gameNode();
	virtual ~gameNode();

	int _crtSelect;

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render();			//�׸��� ����

	virtual void setMap();

	virtual void save();
	virtual void load();
	virtual void tempSave();
	virtual void tempLoad();

	void setCtrlSelect(int num) { _crtSelect = num; }

	
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

