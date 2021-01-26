#pragma once
#include "gameNode.h"
// �ٶ�����, �⺻���� �������̽� Ʋ

class playerManager;

struct tagSnow
{
	float x, y; // x,y��ǥ
	float xSpd; // x���ǵ� �������ϰ� �����ǵ���
	int frame, count; // �ִϸ��̼� �����ӿ�
};

class UIManager : public gameNode
{
private:
	int _windCount;
	float _wind;
	tagSnow _snow[SNOWMAX];

public:

	UIManager() {};
	~UIManager() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void windChange();
	void snowSetting();
	void snowMove();
	float getWind() { return _wind; } // �ٶ����� �����ϱ� ����
};

