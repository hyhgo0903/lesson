#pragma once
#include "gameNode.h"

enum playMode
{
	CIRCULATE, // ���� �ݺ�
	ONLYONE, // �Ѱ �÷���
	NOCIRCULATE // �ݺ�����
};


class myLittleMP3 :
	public gameNode
{
private:
	int _nowPlay;
	char _str[128];
	bool _randomOn;
	float _volume; // 0~1
	float _playingTime; // 0~1 ��������
	playMode _playMode;
	bool _stopped; // ������ ������ ���(���� ���� �˾ƺ��ų� �������� Ʋ�� ���� �ʿ�)
	bool _silenced;

public:
	myLittleMP3() {};
	~myLittleMP3() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
		
	void clickedList();// �������� ���� ���
	void clickButtons();// ���� ��ư���� ���� ���
	void nextMusic(); // �������� �Ѿ
};

