#include "stdafx.h"
#include "playerManager.h"

void playerManager::animationUpdate()
{
	if (_tank.aniCount < 6) _tank.aniCount++; // 60�ɋ����� 1�ʴϱ� 6�ɶ����ٸ� 0.1�ʸ��� ����
	else
	{
		_tank.aniCount = 0;
		switch (_tank.type)
		{
		case CANNON:
			switch (_tank.state)
			{
			case RIGHTIDLE: ++_tank.frameX;			if (_tank.frameX >= 39) _tank.frameX = 0; break;
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 7) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 5)
				{	_tank.state = RIGHTIDLE; stateChange();	}	break;
			case LEFTIDLE: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 38; break;
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 6; break;
			case LEFTATTACK: --_tank.frameX;		
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		case MISSILE:
			switch (_tank.state)
			{
			case RIGHTIDLE: ++_tank.frameX;			if (_tank.frameX >= 24) _tank.frameX = 0; break;
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 4) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 7)
				{
					_tank.state = RIGHTIDLE; stateChange();
				}	break;
			case LEFTIDLE: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 23; break;
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 3; break;
			case LEFTATTACK: --_tank.frameX;
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		case MULTI:
			switch (_tank.state)
			{
			case RIGHTIDLE: ++_tank.frameX;			if (_tank.frameX >= 10) _tank.frameX = 0; break;
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 8) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 13)
				{
					_tank.state = RIGHTIDLE; stateChange();
				}	break;
			case LEFTIDLE: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 9; break;
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 7; break;
			case LEFTATTACK: --_tank.frameX;
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		case SUPER:
			switch (_tank.state)
			{
			case RIGHTIDLE:
			case RIGHTRUN: ++_tank.frameX;			if (_tank.frameX >= 7) _tank.frameX = 0; break;
			case RIGHTATTACK: ++_tank.frameX;
				if (_tank.frameX >= 8)
				{
					_tank.state = RIGHTIDLE; stateChange();
				}	break;
			case LEFTIDLE:
			case LEFTRUN: --_tank.frameX;			if (_tank.frameX < 0) _tank.frameX = 6; break;
			case LEFTATTACK: --_tank.frameX;
				if (_tank.frameX < 0) { _tank.state = LEFTIDLE;	stateChange(); }	break;
			}
			break;
		}
	}
}

// ���� �ٲ𶧸��� ��ȯ�� ��. ���� �ٲܶ� �ʱ� ������ �����ִ� �Լ�
void playerManager::stateChange()
{
	switch (_tank.type)
	{
	case CANNON:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:
		case RIGHTATTACK:		_tank.frameX = 0;	break;
		case LEFTIDLE:			_tank.frameX = 38;	break;
		case LEFTRUN:			_tank.frameX = 6;	break;
		case LEFTATTACK:		_tank.frameX = 4;	break;
		}
		break;
	case MISSILE:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:
		case RIGHTATTACK:		_tank.frameX = 0;	break;
		case LEFTIDLE:			_tank.frameX = 23;	break;
		case LEFTRUN:			_tank.frameX = 3;	break;
		case LEFTATTACK:		_tank.frameX = 6;	break;
		}
		break;
	case MULTI:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:	_tank.frameX = 0; break;
		case RIGHTATTACK:		_tank.frameX = 5;	break;
		case LEFTIDLE:			_tank.frameX = 9;	break;
		case LEFTRUN:			_tank.frameX = 7;	break;
		case LEFTATTACK:		_tank.frameX = 7;	break;
		}
		break;
	case SUPER:
		switch (_tank.state)
		{
		case RIGHTIDLE:			case RIGHTRUN:
		case RIGHTATTACK:		_tank.frameX = 0;	break;
		case LEFTIDLE:	case LEFTRUN:	_tank.frameX = 6;	break;
		case LEFTATTACK:		_tank.frameX = 7;	break;
		}
		break;
	}
}