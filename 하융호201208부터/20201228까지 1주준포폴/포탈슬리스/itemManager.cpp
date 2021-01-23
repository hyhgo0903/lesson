#include "stdafx.h"
#include "itemManager.h"
#include "playerManager.h"
// ������ ��� ������, ����Ⱦ����� ���ͷ� ���� ����� ���
itemManager::itemManager()
{
}

itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	_spdUpEffect = new effect;
	_spdUpEffect->init(IMAGEMANAGER->findImage("���ǵ��"), 45, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("spdup", "image/effectspeedup.bmp", 900, 29, 45, 29, 1.0f, 0.1f, 20);
	_powUpEffect = new effect;
	_powUpEffect->init(IMAGEMANAGER->findImage("�Ŀ���"), 49, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("powup", "image/effectpowerup.bmp", 980, 29, 49, 29, 1.0f, 0.1f, 20);
	_delDownEffect = new effect;
	_delDownEffect->init(IMAGEMANAGER->findImage("�����̴ٿ�"), 45, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("deldown", "image/effectdelaydown.bmp", 900, 29, 45, 29, 1.0f, 0.1f, 20);
	_scoreUpEffect = new effect;
	_scoreUpEffect->init(IMAGEMANAGER->findImage("���ھ��"), 45, 29, 1, 0.1f);
	EFFECTMANAGER->addEffect("scoreup", "image/effectscore.bmp", 900, 29, 45, 29, 1.0f, 0.1f, 20);

	_itemScore = 0;
	_wind = 0.f;
	_heliRegenCount = 0;
	_heliRC = {0,0,0,0};
	_heliAppear = _heliUp = false;
	for (int i = 0; i < MAPSIZEX/600; i++)
	{
		_heliArr[i] = false; 
	}
	for (int i = 0; i < 4; i++)
	{
		_usingSlot[i] = EMPTY; // �ʱ� ������ ����
		_stateSlot[i] = false;
	}

	return S_OK;
}

void itemManager::release()
{
	_vDroppedItem.clear();
	SAFE_RELEASE(_spdUpEffect);
	SAFE_DELETE(_spdUpEffect);
	SAFE_RELEASE(_powUpEffect);
	SAFE_DELETE(_powUpEffect);
	SAFE_RELEASE(_delDownEffect);
	SAFE_DELETE(_delDownEffect);
	SAFE_RELEASE(_scoreUpEffect);
	SAFE_DELETE(_scoreUpEffect);
}

void itemManager::update()
{
	heliMove();
	test();
	for (int i = 0; i< MAPSIZEX / 600; i++)
	{
		if (GETCAM > 600 * i && !_heliArr[i])
		{ // 600�Ÿ����� �Ұ����ְ�(������ �� �ȳ���) ��
			_heliArr[i] = true;
			generateUsingItem();
		}
	}
	if (GETCAM > MAPSIZEX - WINSIZEX - 5) // �ʳ� �����ϸ�(������) ���� �ð����� ����
	{
		if (_heliRegenCount < 480) _heliRegenCount++;
		else
		{
			_heliRegenCount = 0;
			_heliArr[0] = false;
		}
	}
	
	itemUpdate();
	if (_stateSlot[0] && _stateSlot[1] && _stateSlot[2]) _stateSlot[3] = true;	

	EFFECTMANAGER->update();
	_spdUpEffect->update();
	_powUpEffect->update();
	_delDownEffect->update();
}

void itemManager::render()
{
	if (_heliAppear)
	{
		FINDIMG("���")->render(getMemDC(), _heliRC.left, _heliRC.bottom - 52);
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			Rectangle(getMemDC(), _heliRC);
		}
	}
	
	for (_viDroppedItem = _vDroppedItem.begin(); _viDroppedItem != _vDroppedItem.end(); ++_viDroppedItem)
	{
		(*_viDroppedItem)->render();
	}
	slotRender();

	EFFECTMANAGER->render();
	_spdUpEffect->render();
	_powUpEffect->render();
	_delDownEffect->render();
}

void itemManager::generateUsingItem()
{ // �����ġ �����ϰ� �����ϰ� �ϴ� �Լ�
	if (_heliAppear) return;
	_heliAppear = true;
	_heliRC = RectMake(GETCAM + 300 + rand() % 200, 0,90,0);
}

void itemManager::heliMove()
{ // �� �Լ��� ������. �������ϸ� ���������� �����۶����� �ٽ� �ø��� �Լ�
	if (!_heliAppear) return;
	_heliRC.left += -2 + rand() % 5; // ��鸮�� ȿ��
	_heliRC.right = _heliRC.left + 90;
	if (_heliUp)
	{
		_heliRC.bottom -= 1; // ž�� 0���� �����Ǿ��� ���Ҹ� ������(�̴ϸʿ� �׷��ֱ� ����..)
		if (_heliRC.bottom <= 0)
		{
			_heliAppear = false;
			_heliUp = false;
		}
	}
	else
	{
		_heliRC.bottom += 1;
		if (_heliRC.bottom >= 52) // �������� ����������
		{
			dropUsingItem();
			_heliUp = true;
		}
	}	
}

void itemManager::dropUsingItem()
{ // ������� ������� ���ض�
	droppedItem* item;
	item = new droppedItem;
	item->init(false,(_heliRC.left+_heliRC.right)/2,_heliRC.bottom);
	_vDroppedItem.push_back(item);
}

void itemManager::dropStateItem(float x, float y)
{ // �������� ������� ���ض� x,y��ǥ��..
	droppedItem* item;
	item = new droppedItem;
	item->init(true, x, y);
	_vDroppedItem.push_back(item);
}

void itemManager::itemUpdate()
{
	for (int i = 0; i < _vDroppedItem.size(); ++i)
	{
		// ��������
		_vDroppedItem[i]->update();
		// ���ǵ带 �ٶ������� �����ֱ�
		_vDroppedItem[i]->getXSpd() = 2.f* _wind;
		// �浹
		RECT temp;
		if (IntersectRect(&temp, &_pm->getRect(), &_vDroppedItem[i]->getRect()))
		{
			_vDroppedItem[i]->getDisappear() = true;
			switch (_vDroppedItem[i]->getItemType())
			{
			case -1: // ���ڸ� �����Ÿ� ������ ������
				getItem(rand() % 4);
				break;
			case 0: if (!_stateSlot[0]) _getEffect(0);
				if (_stateSlot[0])
				{
					++_itemScore;
					EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
				}
				_stateSlot[0] = true;	break;
			case 1: if (!_stateSlot[1]) _getEffect(1);
				if (_stateSlot[1])
				{
					++_itemScore;
					EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
				}
				_stateSlot[1] = true;	break;
			case 2: if (!_stateSlot[2]) _getEffect(2);
				if (_stateSlot[2])
				{
					++_itemScore;
					EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
				}
				_stateSlot[2] = true;	break;
			}
		}
	}
	bool recheck;
	recheck = true;
	while (recheck)
	{
		recheck = false;
		for (int i = 0; i < _vDroppedItem.size(); ++i)
		{
			if (_vDroppedItem[i]->getDisappear())
			{ // �𽺾��Ǿ� ���������� ����(ȭ��� or ���ӽð� ��)
				SAFE_RELEASE(_vDroppedItem[i]);
				SAFE_DELETE(_vDroppedItem[i]);
				_vDroppedItem.erase(_vDroppedItem.begin() + i);
				recheck = true;
				break;
			}
		}
	}	
}

void itemManager::getItem(int x)
{
	int emptySlot = 4;
	for (int i = 0; i < 4; i++)
	{
		if (_usingSlot[i] == EMPTY)
		{
			emptySlot = i;
			break;
		}
	} // ������� ã�� �ݺ���
	if (emptySlot == 4)
	{
		++_itemScore;
		EFFECTMANAGER->play("scoreup", _pm->getRect().left + 23, _pm->getRect().top + 23);
		return; // �����Ŵϱ� �ȹ���.
	}		 

	switch (x)
	{ // ��ĭ�� �̳Ѱ��� �ٲ���
	case 0: _usingSlot[emptySlot] = DOUBLEFIRE;		break;
	case 1:	_usingSlot[emptySlot] = POWERUP;		break;
	case 2:	_usingSlot[emptySlot] = SHIELD;			break;
	case 3:	_usingSlot[emptySlot] = REPAIR;			break;
	}
}

void itemManager::slotRender()
{
	// ����â ������
	for (int i = 0; i < 4; i++)
	{
		if (_stateSlot[i])
		{
			FINDIMG("�����۽���")->frameRender(getMemDC(), GETCAM + 479 + 39 * i, 415, i, 0);
		}
	}
	// �����â ������
	for (int i = 0; i < 4; i++)
	{
		if (_usingSlot[i] == EMPTY) continue;
		FINDIMG("����۽���")->frameRender(getMemDC(), GETCAM+254 + 34 * i, 415 , _usingSlot[i], 0);
	} // �̳��� ���ں���(framex)���� ����
}

void itemManager::test() // �׽�Ʈ�� ������ ����� ġƮŰ
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		if (_heliAppear) return;
		_heliAppear = true;
		_heliRC = RectMake(GETCAM + 150, 0, 90, 0);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8)) dropStateItem(GETCAM + 150, 300);
}

void itemManager::_getEffect(int x)
{
	switch (x)
	{
	case 0:EFFECTMANAGER->play("powup", _pm->getRect().left+23, _pm->getRect().top + 23);		break;
	case 1:EFFECTMANAGER->play("spdup", _pm->getRect().left + 23, _pm->getRect().top + 23);		break;
	case 2:EFFECTMANAGER->play("deldown", _pm->getRect().left + 23, _pm->getRect().top + 23);	break;
	}
}
