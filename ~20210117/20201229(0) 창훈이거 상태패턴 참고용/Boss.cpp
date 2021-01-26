#include "stdafx.h"
#include "Boss.h"
#include "Appeal.h"
#include "Move.h"
#include"BAttack.h"
#include "BJump.h"
#include "DJump.h"
#include "SPattern.h"
#include "BDead.h"
Boss::Boss()
{
}

Boss::~Boss()
{
}

HRESULT Boss::init()
{
	setState(APPEAL);
	_currentX = 0;
	AtkImg = IMAGEMANAGER->findImage("보스공격이펙트");
	subAtk = IMAGEMANAGER->findImage("보스공격이펙트");
	direc = 0;
	count = 0;
	bossLoc.x = 600;
	bossLoc.y = WINSIZEY - 200;
	canAtt = false;
	Fire = false;
	comeback = false;
	timer = 0;
	HP = 10;
	damaged = false;
	alpha = 255;
	isdead = false;
	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	BossSta->updateState();
	if(!SPtrn)NPattern();
	_rc = RectMake(bossLoc.x, bossLoc.y, BossImg->getFrameWidth(), BossImg->getFrameHeight());
	if(!isdead)Bdamaged();
	if (HP <= 0&&!isdead)/*setState(DEAD);*/
	{
		alpha = 255;
		setState(DEAD);
		isdead = true;
	}
}

void Boss::render(POINT camera)
{
	if(!damaged/*&&!isdead*/)BossImg->frameRender(getMemDC(), bossLoc.x, bossLoc.y, camera, _currentX, direc);
	if (damaged)BossImg->alphaframeRender(getMemDC(), bossLoc.x, bossLoc.y, _currentX, direc, alpha, camera);
	if (Fire)AtkImg->frameRender(getMemDC(), ATTRC.left, ATTRC.top, camera);
	if (SPtrn)subAtk->frameRender(getMemDC(), subATTRC.left, subATTRC.top, camera);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _rc, camera);
		Rectangle(getMemDC(), ATTRC, camera);
	}
}

void Boss::animaiton(int x)
{
	count++;
	if (count % x == 0)
	{
		if (direc == 1)
		{
			BossImg->setFrameX(_currentX);
			_currentX--;
			if (_currentX < 0)
			{
				_currentX = BossImg->getMaxFrameX();
				if (BossImg == IMAGEMANAGER->findImage("보스점프"))_currentX = 0;
			}
		}
		if (direc == 0)
		{
			BossImg->setFrameX(_currentX);
			_currentX++;

			if (_currentX > BossImg->getMaxFrameX())
			{
				_currentX= 0;
				if (BossImg == IMAGEMANAGER->findImage("보스점프"))_currentX =  BossImg->getMaxFrameX();
			}
		}
	}

}

void Boss::NPattern()
{
	if(Fire)timer++;
		if (Fire&&timer>150&&direc==0)
		{
			comeback = true;
			timer = 0;
		}
		if (Fire&&timer>150&&direc==1)
		{
			comeback = true;
			timer = 0;
		}
		if (comeback)
		{
			switch (direc)
			{
			case 0:
				OffsetRect(&ATTRC, 2, 0);
				break;
			case 1:
				OffsetRect(&ATTRC, -2, 0);
				break;
			}
		}
		if (!comeback)
		{
			switch (direc)
			{
			case 0:
				ATTRC.left -= 2;
				ATTRC.right -= 2;
				break;
			case 1:
				OffsetRect(&ATTRC, 2, 0);
				break;
			}
		}

}

void Boss::FIRE()
{
	if (direc == 0)ATTRC = RectMake(_rc.left - AtkImg->getFrameWidth() - 10, RND->getFromIntTo(_rc.top, _rc.bottom- AtkImg->getFrameHeight()), AtkImg->getFrameWidth(), AtkImg->getFrameHeight());
	if (direc == 1)ATTRC = RectMake(_rc.right +10 , RND->getFromIntTo(_rc.top, _rc.bottom- AtkImg->getFrameHeight()), AtkImg->getFrameWidth(), AtkImg->getFrameHeight());
}

void Boss::atkAni()
{
	count++;
	if (count % 10 == 0)
	{
		if (direc == 0)
		{
			BossImg->setFrameX(_currentX);
			_currentX++;
			if (_currentX >= BossImg->getMaxFrameX())
			{
				_currentX = 4;
				if (!Fire)
				{
					FIRE();
				}
				Fire = true;
			}

		}
		if (direc == 1)
		{
			BossImg->setFrameX(_currentX);
			_currentX--;
			if (_currentX <= 0)
			{
				_currentX = 1;
				if (!Fire)
				{
					FIRE();
				}
				Fire = true;
			}
		}
	}

	if (Fire&&!canAtt)
	{
		if (count % 5==0)
		{
			if (direc == 0)
			{
				_currentX--;
				BossImg->setFrameX(_currentX);
				if (_currentX <= 0)
				{
					comeback = false;
					timer = 0;
					setState(MOVE);
				}
			}
			if (direc == 1)
			{
				BossImg->setFrameX(_currentX);
				_currentX++;
				if (_currentX >= BossImg->getMaxFrameX())
				{
					comeback = false;
					timer = 0;
					setState(MOVE);
				}
			}
		}
	}
	if (count % 4 == 0)
	{
		AtkImg->setFrameX(_subIdx);
		_subIdx++;
		if (_subIdx >= AtkImg->getMaxFrameX())_subIdx = 0;
	}
}

void Boss::Bdamaged()
{
	if (damaged)
	{
		BossImg = IMAGEMANAGER->findImage("보스피격");
		_currentX = 0;
		Dtimer++;
		alpha = 100;
		if (Dtimer > 20)
		{
			Dtimer = 0;
			BossImg = IMAGEMANAGER->findImage("보스공격");
			_currentX = 5;
			damaged = false;
			alpha = 255;
		}
	}
}

void Boss::Jump()
{
	if(direc==0)bossLoc.x -= 2;
	if (direc == 1)bossLoc.x += 2;
	bossLoc.y -= JumpPower;
	JumpPower -= gravity;
}

void Boss::PStart()
{
	ATTRC = RectMake(WINSIZEX-100,RND->getFromIntTo(350,420), AtkImg->getFrameWidth(), AtkImg->getFrameHeight());
	subATTRC=RectMake(0, RND->getFromIntTo(400, 480), AtkImg->getFrameWidth(), AtkImg->getFrameHeight());
}

void Boss::PMove()
{
	if(BossImg==IMAGEMANAGER->findImage("보스패턴"))OffsetRect(&ATTRC, -3, 0);
	if(BossImg == IMAGEMANAGER->findImage("보스패턴"))OffsetRect(&subATTRC, 3, 0);
}

void Boss::PtAni()
{
	count++;
	if (count % 10 == 0)
	{	
		BossImg->setFrameX(_currentX);
		_currentX++;
		if (_currentX >= BossImg->getMaxFrameX())
		{
			_currentX = 4;
			if (!Fire)
			{
				PStart();
				Fire = true;
				SPtrn = true;
			}
		}
	}
	if (Fire && !SPtrn)
	{
		if (count % 5 == 0)
		{
			_currentX--;
			BossImg->setFrameX(_currentX);
			if (_currentX <= 0)
			{
				setState(BDJUMP);
			}
		}
	}
	if (count % 4 == 0)
	{
		AtkImg->setFrameX(_subIdx);
		_subIdx++;
		if (_subIdx >= AtkImg->getMaxFrameX())_subIdx = 0;
	}

}

void Boss::setState(BState BS)
{
	if (BossSta != NULL)BossSta->ExitState();
	switch (BS)
	{
	case APPEAL:
		BossSta = new Appeal;
		break;
	case MOVE:
		BossSta = new Move;
		break;
	case BATTACK:
		BossSta = new BAttack;
		break;
	case BJUMP:
		BossSta = new BJump;
		break;
	case SPATTERN:
		BossSta = new SPattern;
		break;
	case BDJUMP:
		BossSta = new DJump;
		break;
	case DEAD:
		BossSta = new BDead;
		break;
	}
	BossSta->LinkMemberAddress(this);
	BossSta->EnterState();
}
