#pragma once
#include "image.h"

//백버퍼라는 빈 비트맵 이미지를 하나 생성해둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

enum CTRL
{
	CTRL_SAVE,			//세이브 버튼 인식
	CTRL_LOAD,			//로드 버튼 인식
	CTRL_TERRAINDRAW,	//지형 버튼
	CTRL_OBJDRAW,		//오브젝트 버튼
	CTRL_ERASER,		//지우개 버튼
	CTRL_2X2,
	CTRL_4X4,
	CTRL_Z,
	CTRL_END
};


class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//매니저 초기화 할껀지 유무

public:
	gameNode();
	virtual ~gameNode();

	int _crtSelect;

	virtual HRESULT init();			//초기화 전용 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render();			//그리기 전용

	virtual void setMap();

	virtual void save();
	virtual void load();
	virtual void tempSave();
	virtual void tempLoad();

	void setCtrlSelect(int num) { _crtSelect = num; }

	
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

