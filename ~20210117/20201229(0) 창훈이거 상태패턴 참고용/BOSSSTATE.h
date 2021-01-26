#pragma once
class Boss;
class BOSSSTATE
{
protected:
	Boss* _boss;
	int timer;
public:
	~BOSSSTATE() {};
	virtual void EnterState()=0;
	virtual void updateState() = 0;
	virtual void ExitState() = 0;

	void LinkMemberAddress(Boss* boss) { _boss = boss; }
};

