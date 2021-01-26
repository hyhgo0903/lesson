#pragma once
#include "gameNode.h"

//�� Ÿ���� ������ 32�� 32 X 32
#define TILESIZE 32

//Ÿ�� ���� ���� 20�� ���� 20��
#define TILEX 20
#define TILEY 20

//640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//Ÿ�ϼ�(����Ÿ��) ����
#define SAMPLETILEX 20
#define SAMPLETILEY 9

enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//��ġ(������, ���� ��ġ ���)
enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//����
	OBJECT obj;				//������Ʈ
	RECT rc;				//��Ʈ
	int terrainFrameX;		//Ÿ�� ��ȣ(�ִϸ��̼� ������ ��ȣ �����ϸ��)
	int terrainFrameY;
	int objFrameX;			//������Ʈ ��ȣ (���� ����)
	int objFrameY;
};

//���� Ÿ�� ����ü(�ȷ�Ʈ Ÿ��)
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ŭ���� ���� Ÿ���� ���� ������ ����ü
struct tagCurrentTile
{
	int x;
	int y;
};

class playGround : public gameNode
{
private:
	HWND _btnSave;			//���̺�
	HWND _btnLoad;			//�ε�
	HWND _btnTerrainDraw;	//����
	HWND _btnObjectDraw;	//������Ʈ
	HWND _btnEraser;		//���찳
	HWND _twoByTwo;
	HWND _fourByFour;
	HWND _crtlZ;

	tagCurrentTile	_currentTile;
	tagSampleTile	_sampleTile[SAMPLETILEX * SAMPLETILEY];
	tagTile			_tiles[TILEX * TILEY];

	int _pos[2];

public:
	playGround();
	~playGround();

	virtual HRESULT init();	//�ʱ�ȭ ���� �Լ�
	virtual void release();	//�޸� ���� �Լ�
	virtual void update();	//���� ����
	virtual void render();	//�׸��� ����

	void setup();		//��ư �� Ÿ�� ���ÿ� �Լ�

	virtual void setMap();
	virtual void save();
	virtual void load();

	virtual void tempSave();
	virtual void tempLoad();

	TERRAIN terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);

};

