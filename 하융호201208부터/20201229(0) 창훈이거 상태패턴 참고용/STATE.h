#pragma once
class Messenger;
class STATE 
{
protected:
	Messenger* _messenger;
public:
	~STATE();
	virtual void EnterState()=0;
	virtual void updateState() = 0;
	virtual void ExitState() = 0;
	void LinkMemberAdress(Messenger* messenger)
	{
		_messenger = messenger;
	}
};

