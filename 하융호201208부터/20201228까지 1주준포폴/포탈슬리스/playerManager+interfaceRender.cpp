#include "stdafx.h"
#include "playerManager.h"

// �÷��̾� ���� ���� ���� �������̽��� �߰����ش�
void playerManager::interfaceRender()
{
	if (_tank.currentHP / _tank.maxHP > 0.3f)
	{
		FINDIMG("�ʷϹ�")->render(getMemDC(), GETCAM + 279, 452, 0, 0, 403.0f*_tank.currentHP / _tank.maxHP, 20);
	}
	else // ���Ǵ� �Ŀ� ��Ȱ��
	{
		FINDIMG("������")->render(getMemDC(), GETCAM + 279, 452, 0, 0, 403.0f*_tank.currentHP / _tank.maxHP, 20);
	}
	FINDIMG("������")->render(getMemDC(), GETCAM + 279, 475, 0, 0, 403.0f*_tank.currentPower / _tank.maxPower, 20);
	FINDIMG("�Ķ���")->render(getMemDC(), GETCAM + 279, 497, 0, 0, 403.0f*_tank.currentDelay / _tank.maxDelay, 20);

	// ���� �ٴ�
	HPEN pen; HPEN oldPen;
	if (_tank.angle < PI / 2)
	{

		HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 150, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(0.17453f),
			462 - 10 * sinf(0.17453f), GETCAM + 92 + 55 * cosf(0.17453f),
			462 - 55 * sinf(0.17453f));
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(1.3963f),
			462 - 10 * sinf(1.3963f), GETCAM + 92 + 55 * cosf(1.3963f),
			462 - 55 * sinf(1.3963f));
		SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
	}
	else
	{
		HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 150, 0));
		HPEN oldPen = (HPEN)SelectObject(getMemDC(), pen);
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(1.7453f),
			462 - 10 * sinf(1.7453f), GETCAM + 92 + 55 * cosf(1.7453f),
			462 - 55 * sinf(1.7453f));
		LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(2.967f),
			462 - 10 * sinf(2.967f), GETCAM + 92 + 55 * cosf(2.967f),
			462 - 55 * sinf(2.967f));
		SelectObject(getMemDC(), oldPen);	DeleteObject(pen);
	}
	pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(getMemDC(), pen);
	LineMake(getMemDC(), GETCAM + 92 + 10 * cosf(_tank.angle),
		462 - 10 * sinf(_tank.angle), GETCAM + 92 + 55 * cosf(_tank.angle),
		462 - 55 * sinf(_tank.angle));
	SelectObject(getMemDC(), oldPen);	DeleteObject(pen);

	// �Ϲݰ������� Ư����������
	if (_specialCount == 2)
	{
		FINDIMG("���")->render(getMemDC(), GETCAM + 152, 496);
	}
	else	FINDIMG("���")->render(getMemDC(), GETCAM + 4, 496);

	// ���� ���� ��ũ����
	switch (_tank.type)
	{
	case CANNON:FINDIMG("������ũ")->frameRender(getMemDC(), GETCAM + 200, 422, 2, 0);	break;
	case MISSILE:FINDIMG("������ũ")->frameRender(getMemDC(), GETCAM + 200, 422, 0, 0);	break;
	case MULTI:FINDIMG("������ũ")->frameRender(getMemDC(), GETCAM + 200, 422, 1, 0);	break;
	case SUPER:FINDIMG("������ũ")->frameRender(getMemDC(), GETCAM + 200, 422, 3, 0);	break;
	}

	// ���� �ȳ�
	char str[256];
	SetBkMode(getMemDC(), TRANSPARENT);
	int angle = _tank.angle * 180 / PI;
	if (angle == 9) angle = 10;
	else if (angle == 99) angle = 100;
	else if (angle == 169) angle = 170; // �� �������������� ǥ�� �����ϰ�
	sprintf_s(str, "%d", angle);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), GETCAM + 82, 476, str, strlen(str));
	SetTextColor(getMemDC(), RGB(0, 150, 0));
	if (_tank.angle < PI / 2)
	{
		sprintf_s(str, "10");
		TextOut(getMemDC(), GETCAM + 52, 476, str, strlen(str));
		sprintf_s(str, "80");
		TextOut(getMemDC(), GETCAM + 117, 476, str, strlen(str));
	}
	else
	{
		sprintf_s(str, "170");
		TextOut(getMemDC(), GETCAM + 52, 476, str, strlen(str));
		sprintf_s(str, "100");
		TextOut(getMemDC(), GETCAM + 110, 476, str, strlen(str));
	}

}