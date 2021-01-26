#pragma once
#include "gameNode.h"

//한 타일의 사이즈 32다 32 X 32
#define TILESIZE 32

//타일 갯수 가로 20개 세로 20개
#define TILEX 20
#define TILEY 20

//640 X 640
#define TILESIZEX TILESIZE * TILEX
#define TILESIZEY TILESIZE * TILEY

//타일셋(샘플타일) 범위
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

//위치(리스폰, 진영 위치 등등)
enum POS
{
	POS_FLAG1, POS_FLAG2,
	POS_TANK1, POS_TANK2
};

struct tagTile
{
	TERRAIN terrain;		//지형
	OBJECT obj;				//오브젝트
	RECT rc;				//렉트
	int terrainFrameX;		//타일 번호(애니메이션 프레임 번호 생각하면됨)
	int terrainFrameY;
	int objFrameX;			//오브젝트 번호 (위와 같다)
	int objFrameY;
};

//샘플 타일 구조체(팔레트 타일)
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//내가 클릭한 현재 타일이 뭔지 저장할 구조체
struct tagCurrentTile
{
	int x;
	int y;
};

class playGround : public gameNode
{
private:
	HWND _btnSave;			//세이브
	HWND _btnLoad;			//로드
	HWND _btnTerrainDraw;	//지형
	HWND _btnObjectDraw;	//오브젝트
	HWND _btnEraser;		//지우개
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

	virtual HRESULT init();	//초기화 전용 함수
	virtual void release();	//메모리 해제 함수
	virtual void update();	//연산 전용
	virtual void render();	//그리기 전용

	void setup();		//버튼 및 타일 셋팅용 함수

	virtual void setMap();
	virtual void save();
	virtual void load();

	virtual void tempSave();
	virtual void tempLoad();

	TERRAIN terrainSelect(int frameX, int frameY);

	OBJECT objSelect(int frameX, int frameY);

};

