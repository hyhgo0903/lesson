#include "stdafx.h"
#include "playerManager.h"

//�ȼ� �������������� ���� ���½��ϴ� (�����ϱ⵵ �ϰ�)

void playerManager::stateRender()
{
	switch (_tank.type)
	{
	case CANNON:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("ĳ����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 19, _tank.rc.top - 68, _tank.frameX, 0, _alphaValue);		break;
		case LEFTIDLE:FINDIMG("ĳ����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 15, _tank.rc.top - 68, _tank.frameX, 1, _alphaValue);		break;
		case RIGHTRUN:FINDIMG("ĳ���̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 44, _tank.rc.top - 10 , _tank.frameX, 0, _alphaValue);		break;
		case LEFTRUN:FINDIMG("ĳ���̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 17, _tank.rc.top - 10 , _tank.frameX, 1, _alphaValue);		break;
		case RIGHTATTACK:FINDIMG("ĳ�����")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 60, _tank.rc.top - 35, _tank.frameX, 0, _alphaValue);		break;
		case LEFTATTACK:FINDIMG("ĳ�����")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 62, _tank.rc.top - 35, _tank.frameX, 1, _alphaValue);		break;
		}
		break;
	case MISSILE:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("���ʾ��̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 27, _tank.rc.top - 22, _tank.frameX, 0, _alphaValue);		break;
		case LEFTIDLE:FINDIMG("���ʾ��̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 4, _tank.rc.top - 22, _tank.frameX, 1, _alphaValue);		break;
		case RIGHTRUN:FINDIMG("�����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 55, _tank.rc.top - 22, _tank.frameX, 0, _alphaValue);		break;
		case LEFTRUN:FINDIMG("�����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 47, _tank.rc.top - 22, _tank.frameX, 1, _alphaValue);		break;
		case RIGHTATTACK:FINDIMG("���ʰ���")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 53, _tank.rc.top - 47, _tank.frameX, 0, _alphaValue);		break;
		case LEFTATTACK:FINDIMG("���ʰ���")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 30, _tank.rc.top - 47, _tank.frameX, 1, _alphaValue);		break;
		}
		break;
	case MULTI:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("���ʾ��̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left-2, _tank.rc.top-10, _tank.frameX, 0, _alphaValue);		break;
		case LEFTIDLE:FINDIMG("���ʾ��̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left, _tank.rc.top-10, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTRUN:FINDIMG("�����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left-2, _tank.rc.top-5, _tank.frameX, 0, _alphaValue);			break;
		case LEFTRUN:FINDIMG("�����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left, _tank.rc.top-5, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTATTACK:FINDIMG("���ʰ���")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 3, _tank.rc.top - 32, _tank.frameX, 0, _alphaValue);	break;
		case LEFTATTACK:FINDIMG("���ʰ���")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 2, _tank.rc.top - 32, _tank.frameX, 1, _alphaValue);	break;
		}
		break;
	case SUPER:
		switch (_tank.state)
		{
		case RIGHTIDLE:FINDIMG("���ʾ��̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 0, _alphaValue);			break;
		case LEFTIDLE:FINDIMG("���ʾ��̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTRUN:FINDIMG("�����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 0, _alphaValue);			break;
		case LEFTRUN:FINDIMG("�����̵�")->alphaFrameRender(getMemDC(),
			_tank.rc.left+3, _tank.rc.top, _tank.frameX, 1, _alphaValue);			break;
		case RIGHTATTACK:FINDIMG("���ʰ���")->alphaFrameRender(getMemDC(),
			_tank.rc.left +3 , _tank.rc.top - 28, _tank.frameX, 0, _alphaValue);	break;
		case LEFTATTACK:FINDIMG("���ʰ���")->alphaFrameRender(getMemDC(),
			_tank.rc.left - 15 , _tank.rc.top - 28, _tank.frameX, 1, _alphaValue);	break;
		}
		break;
	} // �ľ�..
}