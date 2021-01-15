#pragma once

class gameNode
{
public:
	gameNode();
	virtual ~gameNode();

	//HRESULT�� ���� ���� ����� ��ȯ�� ��
	//S_OK, E_FAIL, SUCCEDED ������ return���� ����
	//����� �ʱ�ȭ �ƴ��� �ȵƴ��� ȣ������

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

