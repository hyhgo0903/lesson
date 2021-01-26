#pragma once
class player;

class STATE 
{
protected:
	player* _pl;
public:
	~STATE();
	virtual void EnterState()=0;
	virtual void updateState() = 0;
	virtual void ExitState() = 0;
	void LinkMemberAdress(player* player)	{_pl = player;}
};

