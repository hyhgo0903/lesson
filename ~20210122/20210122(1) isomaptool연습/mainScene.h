#pragma once
#include "gameNode.h"
#include "tile.h"
#include "mapTool.h"

class mainScene :public gameNode
{
private:
	tile _tiles[TILENUMX*TILENUMY];
	RECT _zerling;
	float _destX, _destY, _x, _y, _angle;
	RECT _destRc;
	int _indexX, _indexY, _count;

public:
	mainScene();
	~mainScene();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void uiRender();
};

