#pragma once
#include "gameNode.h"

#pragma warning(disable:4996)

class selectScene :	public gameNode
{
private:
	bool _manualPop;		//�Ŵ��� ������ ���̴�?
	bool _selectPhase;		//����������� �����ߴ�?
	bool _selected;			//���̵��� �����ߴ�? (��ũ�������� ����)
	int _data;//���õ� ���̵�(�����Ұ�)	//���õ� ��ũ(�����Ұ�)
	int _cursor[2];			//Ŀ��
public:
	selectScene();
	~selectScene();


	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����
};

