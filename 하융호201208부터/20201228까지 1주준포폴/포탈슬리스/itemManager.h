#pragma once
#include "gameNode.h"
#include <vector>
#include "droppedItem.h"
#include "effect.h"

class playerManager; // �̰� ��ȣ�������� ���漱��. ����� cpp���Ͽ� �߰�������

enum usingItemSlot
{
	DOUBLEFIRE, POWERUP, SHIELD, REPAIR, EMPTY
};

class itemManager : public gameNode
{
private:
	RECT _heliRC; // ���¾������� ����ϴ� �����ġ(�ϳ��� ���)
	bool _heliAppear; // ��Ⱑ ������ ��������
	bool _heliUp;		// ��Ⱑ �����ø�ŭ �����Դ���
	bool _heliArr[MAPSIZEX / 600]; // 600���� ��Ⱑ �����ߴ���
	int _heliRegenCount;
	float _wind;
	
	usingItemSlot _usingSlot[4];
	bool _stateSlot[4];

	vector<droppedItem*> _vDroppedItem;
	vector<droppedItem*>::iterator _viDroppedItem; // �ʵ��� �������� �����մϴ�
	effect* _spdUpEffect;
	effect* _powUpEffect;
	effect* _delDownEffect;
	effect* _scoreUpEffect;

	//���ϴ� ������ ����
	playerManager* _pm;
	int _itemScore;

public:
	itemManager();
	~itemManager();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void generateUsingItem(); // ȣ�� ������ ���������� ����Ѵ�
	void heliMove();		// ��Ⱑ �������� �����ϸ� �����۵��
	void dropUsingItem();
	void dropStateItem(float x, float y); // ȣ�� ������ ���¾������� �����
	void itemUpdate();
	void getItem(int x);
	void slotRender();

	int getScore() { return _itemScore; }
	void setWind(float wind) { _wind = wind; }

	void test();
	void _getEffect(int x); // ó�� �������� �����������ķ�(���� �ƴϰ� spd up, pow up, delay down)

	void setPmMemoryAddressLink(playerManager* pm) { _pm = pm; }
	
	bool getStateSlot(int x) { return _stateSlot[x]; } // ���⸸ �ҰŴϱ� ������ ���� ����
	usingItemSlot& getUsingSlot(int x) {	return _usingSlot[x];	} // �������ϴϱ� ������ �����ؼ�..
	vector<droppedItem*> getVDroppedItem() { return _vDroppedItem; }
	vector<droppedItem*>::iterator getViDroppedItem() { return _viDroppedItem; }
	RECT getRect() { return _heliRC; }
};

