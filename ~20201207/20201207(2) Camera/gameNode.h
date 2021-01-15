#pragma once
#include "image.h"

class gameNode
{
private:
	image* _backBuffer;

public:
	gameNode();
	virtual ~gameNode();
	void setBackBuffer(int x, int y);

	//HRESULT�� ���� ���� ����� ��ȯ�� ��
	//S_OK, E_FAIL, SUCCEDED ������ return���� ����
	//����� �ʱ�ȭ �ƴ��� �ȵƴ��� ȣ������

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	//����� ������
	image* getBackBuffer() { return _backBuffer; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

