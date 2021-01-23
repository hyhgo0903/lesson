#pragma once
#include "gameNode.h"
class STATE;
enum State {
	IDLE,
	JUMP,
	WALK,
	RUN
};

class player :
	public gameNode
{
private:
	float _imgX; float _imgY;		// �����ϸ� ����
	RECT _imgRc;
	float _groundX; float _groundY; // ���� �ٴ�RC
	RECT _groundRc;
	bool _left;					// ������ ���� �ִ���
	State _enumState;
	STATE* _statePattern;
	float _altitude;			// ������ ����
	char _str[128];
	int _directionChanged;		// �¿찡 ��� �ٲ������ ī��Ʈ(Ŀ�ǵ�)
	int _directionChangeCount;	// ī��Ʈüũ�ؼ� ����
	int _dirMemory;				// ���� ���(�뽬��)
	int _dirMemoryCount;		// ī��Ʈüũ�ؼ� ����

public:
	player();
	~player();
	HRESULT init();
	void release();
	void update();
	void render();

	void minusDirectionChanged();

	void rectRender();		//��Ʈ �׸���

	void setState(State state);
	RECT getGroundRc() { return _groundRc; }
	RECT getImgRc() { return _imgRc; }
	float& getGroundX() { return _groundX; }float& getGroundY() { return _groundY; }
	float& getImgX() { return _imgX; }		float& getImgY() { return _imgY; }
	bool& getLeft() { return _left; }
	State& getEnumState() { return _enumState; }
	void plusDirectionChanged() { ++_directionChanged; }
	int& getDirMemory() {return _dirMemory;}
};

