#pragma once
#include "gameNode.h"

#define ITEMDURMAX 800 // �ִ� ���ӽð�

class droppedItem : public gameNode
{
private: //����ҰŸ� protected��
	bool _stateType; // ����������?
	bool _landed;	// �����ߴ���?
	int _frameX;	// ���ڸ� �����ӵ���
	int _itemType;	// �̳� �� ���ٰ� �ߺ�����..
	// 0,1,2,3 : ����� DOUBLEFIRE, POWERUP, SHIELD, REPAIR
	// 0,1,2 : ITEMCANNON, ITEMMISSILE, ITEMMULTI
	bool _disappear;
	RECT _rc;
	float _x, _y, _xSpd, _ySpd; // x,y������ �ӵ�
	int _durCount; // ���ӽð� (������ ������� �����) ���ڸ� ������ī��Ʈ�����ε� Ȱ��
	int _alphaValue; // ������پ�

public:
	droppedItem();
	~droppedItem();

	HRESULT init(bool stateType, float x, float y);
	void release();
	void update();
	void render();

	void move();

	//ȣ��!
	inline RECT getRect() { return _rc; } // �÷��̾�� �浹(?)��
	bool& getDisappear() { return _disappear; } // ������Ÿ� ������ٰ� �˷���
	float& getXSpd() {	return _xSpd;} // �ٶ��� ���� �ٲ��� ��
	int getItemType() { return _itemType; }
};