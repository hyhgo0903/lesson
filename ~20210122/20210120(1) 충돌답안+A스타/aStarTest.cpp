#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{
}

HRESULT aStarTest::init()
{
	_count = _start = _stop = _numCount = 0;
	
	setTiles();

	return S_OK;
}

void aStarTest::setTiles()
{
	//���� Ÿ��. �Ӽ��� "start"�� ������
	_startTile = new tile;
	_startTile->init(4, 12);
	_startTile->setAttribute("start");

	//�� Ÿ��. �Ӽ��� "end"�� ������
	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");

	//���� Ÿ���� ����Ÿ�Ϸ�ٰ�
	_currentTile = _startTile;

	for (int i = 0; i < TILENUMY; ++i)
	{ // ��Ż����Ʈ�� ������ �����Ͽ� ����
		for (int j = 0; j < TILENUMX; ++j)
		{
			//���� Ÿ��
			if (j == _startTile->getIdx() && i == _startTile->getIdy())
			{
				_startTile->setColor(RGB(255, 0, 255));
				_startTile->setIsOpen(true);
				_vTotalList.push_back(_startTile);
				continue;
			}
			//�� Ÿ��
			if (j == _endTile->getIdx() && i == _endTile->getIdy())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_endTile->setIsOpen(true);
				_vTotalList.push_back(_endTile);
				continue;
			}

			//�� �� Ÿ��
			tile* node = new tile;
			node->init(j, i);
			node->setIsOpen(true);

			//��Ż���Ϳ� Ÿ���� �� �������
			_vTotalList.push_back(node);
		}
	}

}

vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdx() - 1;
	int startY = currentTile->getIdy() - 1;

	for (int i = 0; i < 3; ++i)
	{
		//// ############ ���� �������� #####################
		if (startY + i < 0)				continue;
		if (startY + i >= TILENUMY)		continue;
		for (int j = 0; j < 3; ++j)
		{
			// ############ ���׷� ��ô ���� #####################
			if (startX + j < 0)			continue;
			if (startX + j >= TILENUMX)	continue;

			int checkIndex = (startY * TILENUMX) + startX + j + (i * TILENUMX);
			tile* node = _vTotalList[checkIndex];

			//����ó��!
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			// ##################���� ����#############################
			string nodeTop;
			if (startY < 0)				nodeTop = "wall";
			else nodeTop = _vTotalList[(startY * TILENUMX) + startX + 1]->getAttribute();
			// ������������ �������� ������ ���� �������� i==0�� i==2�Ʒ� j==0�� j==2����
			if (i == 0 && nodeTop == "wall")	continue;
			string nodeBottom;
			if (startY + 2 >= TILENUMY)	nodeBottom = "wall";
			else nodeBottom = _vTotalList[(startY * TILENUMX) + startX + (2 * TILENUMX) + 1]->getAttribute();
			// �Ʒ����������� ���ʾƷ��� ������ �Ʒ��� ��������
			if (i == 2 && nodeBottom == "wall")	continue;			
			string nodeLeft;
			if (startX < 0)				nodeLeft = "wall";
			else nodeLeft = _vTotalList[(startY * TILENUMX) + startX + TILENUMX]->getAttribute();
			// ���ʸ��������� �������� ���ʾƷ��� ��������
			if (j == 0 && nodeLeft == "wall")	continue;
			string nodeRight;
			if (startX + 2 >= TILENUMX)	nodeRight = "wall";
			else nodeRight = _vTotalList[(startY * TILENUMX) + startX + TILENUMX + 2]->getAttribute();
			// �����ʸ��������� ���������� ������ �Ʒ��� ��������
			if (j == 2 && nodeRight == "wall")	continue;


			//���� Ÿ���� ��� �������ش�
			node->setParentNode(_currentTile);

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{ // �ִ°Ÿ� �߰�����
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			_vOpenList.push_back(node);

		}
	}

	return _vOpenList;
}

void aStarTest::pathFinder(tile* currentTile)
{
	//��κ���� �ſ� ���� �ϱ� ���ؼ� ������ ��κ���� ��
	float tempTotalCost = 5000;
	tile* tempTile = nullptr;

	bool changed = false;

	//���� �ִ� ���� ���� ���� ���ο��� ���� ���� ��θ� �̾ƾ��Ѵ�
	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{ // ���⼭ �ֺ����� ������ ���ÿ� �������� �ѿ��¸���Ʈ�� �������°�
		_vOpenList[i]->setCostToGoal( // H�� ���(�������� �����Ÿ�)
			(abs(_endTile->getIdx() - _vOpenList[i]->getIdx()) +
				abs(_endTile->getIdy() - _vOpenList[i]->getIdy())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		_vOpenList[i]->setCostFromStart((center1.x == center2.x ||
			center1.y == center2.y) ? 10 : 14);
		// �����̸�(x,y �����ϳ��� ���ٸ�) 10, �ƴϸ� �밢���̴� 14�� ���

		//F = G + H �ϱ�~ 
		_vOpenList[i]->setTotalCost(			//F
			_vOpenList[i]->getCostToGoal() +	//H
			_vOpenList[i]->getCostFromStart()); //G

		//��κ��(F)�� ���� ���� �ַ� ��� �������ش�
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		} // ��������Ʈ�� ��κ�� ���������ְ� Ž���Ǿ� ����Ÿ�Ϸ� ����

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{ // ��������Ʈ�� ����Ÿ���� �ִٸ� -> ���� ��������߿����� ��밪�� ������ ����?
				addObj = false;
				changed = true;
				break;
			} // �Ұ������ �������� ������ false�� ����� �������� �ȵ���������
		}
		_vOpenList[i]->setIsOpen(false); // ����
		if (!addObj) continue;

		_vOpenList.push_back(tempTile); // �߰��ؾߵȴٰ� ������ �߰��ϴ°�
	}

	// ############## ��� ��ã���� ������ �Լ� #####################
	if (!changed)
	{// �ƹ��͵� ������ϰ� ������ ������(?) ���Ҵٸ� ������
		_stop = true;
		return;
	}

	//�����ߴٸ�
	if (tempTile->getAttribute() == "end")
	{
		while (_currentTile->getParentNode() != NULL)
		{
			++_numCount;
			_currentTile->setNumber(_numCount); // ���ڸ� �������ټ� ����
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}
		_startTile->setNumber(_numCount + 1);
		_start = false;
		return;
	}

	_vCloseList.push_back(tempTile);
	// ����Ÿ���� ��������Ʈ�� �ְ� ���¸���Ʈ���� ����. �׸��� ����Ÿ�Ϸ� ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			(*_viOpenList)->setColor(RGB(100, 20, 10));
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;


	//�䷸�� �Լ� ���ο��� �ڱ� �ڽ��� �� ȣ���ϴ� ���� ����Լ�
	//ȣ��ɶ� ���� �ҷ��� �޸� ������ ���̴µ�
	//�̰� �� 1.2�ް� �̻� �Ѿ�� ������� �����
	//�װ��� �ٷ� ���� ���� �÷ο� ��� ��
	//�׸��� ��ʹ� �� ���� �ӵ��� 
	//���� ������ �ڵ尡 ���� �ٰ� ��������ϱ� 

	//����Ʈ�� 1.2�ް� ������ ��ɾ ���ؼ� �� �޸� ���÷��� �ø�������.
	//pathFinder(_currentTile);
}

void aStarTest::release()
{
}

void aStarTest::update()
{
	
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_start = true;
	}

	if (KEYMANAGER->isOnceKeyDown('A') && !_stop)
	{ // �� �ܰ辿 ������
		pathFinder(_currentTile);
	}

	if (KEYMANAGER->isOnceKeyDown('D'))
	{ // �� �濡 ������
		while (_numCount == 0 && !_stop) pathFinder(_currentTile);
	}
	
	if (_start && !_stop)
	{
		pathFinder(_currentTile);
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{ // �������� Ÿ�Ϸ� �ٲ�
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(230, 140, 200));

				break;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{ // �����ִ� Ÿ�Ϸ� �ٲ�(������ҿ�)
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(true);
				_vTotalList[i]->setAttribute("");
				_vTotalList[i]->setColor(RGB(250, 150, 0));

				break;
			}
		}
	}
}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); ++i)
	{
		_vTotalList[i]->render();
	}

	if (_stop)
	{ // ��θ� �� ã�Ҵٸ�
		for (int i = 0; i < _vTotalList.size(); ++i)
		{
			if (_vTotalList[i]->getAttribute() == "start") _vTotalList[i]->setColor(RGB(255, 0, 0));
			if (_vTotalList[i]->getAttribute() == "end") _vTotalList[i]->setColor(RGB(255, 0, 0));
		}
	}
	char str[128]; // Ŀ��ƮŸ���� ���� ����� ǥ���Ϸ���
	ZeroMemory(str, 126);
	sprintf_s(str, "cur");
	TextOut(getMemDC(), _currentTile->getRect().left, _currentTile->getRect().top, str, strlen(str));
}
