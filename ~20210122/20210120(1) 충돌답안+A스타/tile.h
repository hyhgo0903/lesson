#pragma once
#include "gameNode.h"

class tile : public gameNode
{
private:
	int _idX;		//Ÿ���� �ε��� X
	int _idY;		//Ÿ���� �ε��� Y
	int _number;

	POINT _center;	//Ÿ���� ���� ��
	RECT _rc;

	//F = G + H
	//F == TotalCost (�� ���)
	//G == ���������κ��� ���� �������� ���
	//H == ������κ��� ������������ ���

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//�����ִ� Ÿ���̴�?

	tile* _parentNode;	//���� ���� ���(����Ÿ��)

	COLORREF _color;
	HBRUSH _brush;
	HPEN _pen;
	
	string _attribute;	//Ÿ�� �Ӽ�

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release();
	void update();
	void render();

	int getIdx() { return _idX; }
	int getIdy() { return _idY; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect() { return _rc; }


	//================ ������, ������ �� ================
	void setCenter(POINT center) { _center = center; }
	POINT getCenter() { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen() { return _isOpen; }
	
	void setNumber(int number) { _number = number; }
};

