#pragma once
#include "STATE.h"

//���� �޺� 1-1 Ȥ�� 2-1�� ��ȭ�ϴ� ���� �ſ� ���� �⺻�����Դϴ�.
class player;

class combo1 : public STATE
{
private:
public:

	void EnterState();
	void updateState();
	void ExitState();

};

