#include "stdafx.h"
#include "Messenger.h"
#include "STATE.h"
#include "Idle.h"
#include "Sit.h"
#include "Dash.h"
#include "Jump.h"
#include"Climb.h"
#include"Damaged.h"
#include"Attack.h"

Messenger::Messenger()
{
}

Messenger::~Messenger()
{
}

HRESULT Messenger::init()
{
	MPosi.x = 100;
	MPosi.y = 1030;
	setState(IDLE);
	_currentIndex = 0;
	needSub = false;
	jumpPower = 0;
	gravity = 0.2;
	isDamaged = false;
	alpha = 255;
	timer = 0;
	HP = 6;
	MP = 0;
	isDead = false;
	isEnhanced=false;
	Enhancetime = 300;
	for (int i = 0;i < MAXHP;i++)
	{
		HPFilled[i] = IMAGEMANAGER->findImage("HPUIF");
		HPBlanked[i] = IMAGEMANAGER->findImage("HPUIB");
	}
	for (int i = 0;i < MAXMP;i++)
	{
		MPFilled[i] = IMAGEMANAGER->findImage("MPUIF");
		MPBlanked[i] = IMAGEMANAGER->findImage("MPUIB");
	}

	return S_OK;
}

HRESULT Messenger::init(bool check)
{
	vector<string> vStr2;
	vStr2 = TXTDATA->txtLoad("CheckPoint.txt");

	MPosi.x = (atoi(vStr2[0].c_str()));
	MPosi.y = (atoi(vStr2[1].c_str()));
	MP = (atoi(vStr2[2].c_str()));
	HP = 6;
	needSub = false;
	jumpPower = 0;
	gravity = 0.2;
	setState(IDLE);
	isDamaged = false;
	isDead = false;
	isEnhanced = false;
	Enhancetime = 300;
	alpha = 255;
	timer = 0;
	for (int i = 0;i < MAXHP;i++)
	{
		HPFilled[i] = IMAGEMANAGER->findImage("HPUIF");
		HPBlanked[i] = IMAGEMANAGER->findImage("HPUIB");
	}
	for (int i = 0;i < MAXMP;i++)
	{
		MPFilled[i] = IMAGEMANAGER->findImage("MPUIF");
		MPBlanked[i] = IMAGEMANAGER->findImage("MPUIB");
	}


	return S_OK;
}

HRESULT Messenger::init(POINT point)
{
	MPosi = point;
	setState(IDLE);
	_currentIndex = 0;
	needSub = false;
	jumpPower = 0;
	gravity = 0.2;
	isDamaged = false;
	alpha = 255;
	timer = 0;
	HP = 6;
	MP = 0;
	isDead = false;
	isEnhanced = false;
	damage = 1;
	Enhancetime = 300;
	for (int i = 0;i < MAXHP;i++)
	{
		HPFilled[i] = IMAGEMANAGER->findImage("HPUIF");
		HPBlanked[i] = IMAGEMANAGER->findImage("HPUIB");
	}
	for (int i = 0;i < MAXMP;i++)
	{
		MPFilled[i] = IMAGEMANAGER->findImage("MPUIF");
		MPBlanked[i] = IMAGEMANAGER->findImage("MPUIB");
	}
	vector<string> vStr;
	vStr = TXTDATA->txtLoad("MapChange.txt");

	HP=(atoi(vStr[0].c_str()));
	MP=(atoi(vStr[1].c_str()));
	isEnhanced= (atoi(vStr[2].c_str()));

	return S_OK;
}

void Messenger::release()
{
}

void Messenger::update(POINT camera)
{
	MessState->updateState();
	mainRC = RectMakeCenter(MPosi.x, MPosi.y, mainImg->getFrameWidth()/2, mainImg->getFrameHeight()/4*3);
	if (MPosi.x - mainImg->getFrameWidth() / 2 <= 0)MPosi.x = 0 + mainImg->getFrameWidth() / 2;
	if (MPosi.y + mainImg->getFrameHeight() / 2 > 1200)
	{
		HP = 0;
		setState(DAMAGED);
	}
	checkPosition();
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL)) { EFFECTMANAGER->play(effecName, (subRC.left+subRC.right)/2, (subRC.top+subRC.bottom)/2,camera);}
	EFFECTMANAGER->update();
	if(isDamaged)timer++;
	if (timer % 2 == 0)alpha = 100;
	if (timer % 5 == 0)alpha = 200;
	if (timer > 100)
	{
		isDamaged = false;
		timer = 0;
	}
	if (HP <= 0)isDead = true;
	Enhance();
}

void Messenger::render(POINT camera)
{
	if (needSub)subImg->frameRender(getMemDC(), MPosi.x - mainImg->getFrameWidth() / 2, MPosi.y - mainImg->getFrameHeight() / 2, camera, _currentIndex, isLeft);
	if(!isDamaged)mainImg->frameRender(getMemDC(), MPosi.x- mainImg->getFrameWidth() / 2, MPosi.y- mainImg->getFrameHeight() / 2, camera, _currentIndex, isLeft);
	if (isDamaged)mainImg->alphaframeRender(getMemDC(),MPosi.x - mainImg->getFrameWidth() / 2, MPosi.y - mainImg->getFrameHeight() / 2, _currentIndex, isLeft, alpha, camera);
	for (int i = 0;i < MAXHP;i++) { HPBlanked[i]->render(getMemDC(), 0+i*HPBlanked[i]->getWidth(), 0); }
	for (int i = 0;i < HP;i++) { HPFilled[i]->render(getMemDC(), 0+ i * HPBlanked[i]->getWidth(), 0); }
	for (int i = 0;i < MAXMP;i++) { MPBlanked[i]->render(getMemDC(), 72+i*MPBlanked[i]->getWidth(),
		HPBlanked[5]->getY() + HPBlanked[5]->getFrameHeight() / 2); }
	for (int i = 0;i < MP;i++) { MPFilled[i]->render(getMemDC(), 72+i*MPFilled[i]->getWidth(),MPBlanked[i]->getY()); }


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), mainRC,camera);
		if(isAttack)Rectangle(getMemDC(), subRC, camera);
	}
	EFFECTMANAGER->render();

}
void Messenger::Enhance()
{
	if (MP == 3)isEnhanced = true;
	if (isEnhanced)
	{
		Enhancetime--;
		damage = 2;
		if (Enhancetime < 0)
		{
			MP = 0;
			isEnhanced = false;
			Enhancetime = 300;
		}
	}
}


//상태설정

void Messenger::setState(State state)
{
	if(MessState!=NULL)MessState->ExitState();
	switch (state)
	{
	case IDLE:
		MessState = new Idle;
		break;
	case JUMP:
		MessState = new Jump;
		break;
	case SIT:
		MessState = new Sit;
		break;
	case CLIMB:
		MessState = new Climb;
		break;
	case DASH:
		MessState = new Dash;
		break;
	case ATTACK:
		MessState = new Attack;
		break;
	case DAMAGED:
		MessState = new Damaged;
		break;
	}
	MessState->LinkMemberAdress(this);
	MessState->EnterState();
}

void Messenger::setSubRC(int x, int y,int width,int height, int direc)
{
	if (direc == RIGHT)subRC = RectMakeCenter(MPosi.x + x, MPosi.y + y, width, height);
	if (direc == LEFT)subRC = RectMakeCenter(MPosi.x - x, MPosi.y + y, width, height);
}

void Messenger::animation()
{
	_count++;
	if (_count % 4 == 0)
	{
		if (isLeft == LEFT)
		{
			mainImg->setFrameX(_currentIndex);
			_currentIndex--;
			if (_currentIndex < 0)
			{
				_currentIndex = mainImg->getMaxFrameX();
				if (mainImg == IMAGEMANAGER->findImage("전령점프"))_currentIndex = 0;
				if (mainImg == IMAGEMANAGER->findImage("전령붙잡기"))_currentIndex = 1;
			}
		}
		if (isLeft == RIGHT)
		{
			mainImg->setFrameX(_currentIndex);
			_currentIndex++;
			if (_currentIndex > mainImg->getMaxFrameX())
			{
				_currentIndex = 0;
				if (mainImg == IMAGEMANAGER->findImage("전령점프"))_currentIndex = mainImg->getMaxFrameX();
				if (mainImg == IMAGEMANAGER->findImage("전령붙잡기"))_currentIndex = mainImg->getMaxFrameX() - 1;
			}
		}
	}
}

void Messenger::checkPosition()
{
	switch (nowPosi)
	{
	case GROUND:

		if (mainImg == IMAGEMANAGER->findImage("전령점프"))setState(IDLE);
		break;
	case AIR:
		MPosi.y -= jumpPower;
		jumpPower -= gravity;
		break;
	case CLIFF:
		if(mainImg!=IMAGEMANAGER->findImage("전령붙잡기")&&mainImg!=IMAGEMANAGER->findImage("붙잡고공격"))setState(CLIMB);
		break;
	}
}


