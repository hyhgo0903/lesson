#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class aStarTest : public gameNode
{
private:
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	vector<tile*>			_vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//����Ÿ��
	tile* _endTile;			//����Ÿ��
	tile* _currentTile;		//����Ÿ��

	int _count;
	bool _start;
	bool _stop; // ��ã����
	int _numCount; // ���° Ÿ������
public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	
	void setTiles();

	//���� �ִ� ���� ã�Ƴ��� ����� �Լ�
	vector<tile*> addOpenList(tile* currentTile);

	//���� ��� ã�� �Լ�
	void pathFinder(tile* currentTile);

	void release();
	void update();
	void render();
};

