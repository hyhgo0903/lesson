#pragma once
#include "gameNode.h"

struct location
{
	int ID; // ��¿� ��ǥ(ID��. ���� �ο��ǰ� �ȹٲ�)
	int xx, yy; // ��� �ִ��� (��� �ٲ�) x��ǥ y��ǥ
};

class playGround : public gameNode
{
private:
	image* _background; // ���� �׸�(-7-)
	image* _select; // ���°�(������)
	image* _thumbnail; // ���� �׸�
	int _size; //���� �Ҵ����. ������
	int _temp; //�ڸ��ٲٱ��

	int _xx, _yy; // �ӽ÷� �޴� x,y��ǥ(for������ �˻��ؼ� ����)
	int _number, _compare; // �ڸ�ã��� �ӽ�
	int _randNum; // �����¿� ����
	int _count; // �󸶳� �������
	int _tryCount; // �õ�Ƚ��. 1�̻��̾�� ����ó����(���϶� ����ó�� �Ǹ� �ȵǴϱ�..)

	location _location[100];

	char str[256]; // ���� ����ҋ�
	bool _changed; // �ѹ� �ٲ����� �׿� 4����˻� ���Ϸ��� �ִ� �Ұ�(break����)
	bool _isEnd; // ���� �ٸ������� ���ӳ�

	bool _isSelect; // ó���� ���ڰ��� �Լ�

public:
	playGround();
	~playGround();

	virtual HRESULT init();			//�ʱ�ȭ ���� �Լ�
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� ����
	virtual void render(HDC hdc);	//�׸��� ����

	int select();
	void selectInit();

	int up();
	int down();
	int left();
	int right(); // 4���� �˻��ؼ� ��ĭ�̸� �ڸ��ٲٴ� �Լ�

	void mix(); // ���� �Լ�. for���� mixTry�� ���� ��ĭ�� ������ �Ʒ��� ������ ����
	void mixTry(); // �ѹ� ������. �����¿��� �ϳ� �޾Ƽ� �ڸ��ٲ�
};

