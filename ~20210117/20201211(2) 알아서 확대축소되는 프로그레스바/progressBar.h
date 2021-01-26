#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;
	float _x, _y; // ����
	float _width; // �ʺ�ƴ�
	float _height;// ����

	float _currentHPWidth;	// ����ü���� �ʺ�ƴ�

	image* _progressBarFront;		//�տ� ���� ������ �̹���
	image* _progressBarBack;	//�ڿ� �׷��� ������ �̹���

	bool _needToBeResized; // ũ�� �����Ұ�����

public:
	progressBar() {};
	~progressBar() {};

	HRESULT init(int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(float x) { _x = x; }
	void setY(float y) { _y = y; }

	void setPoint(float x, float y) { _x = x; _y = y; }
	void setPoint(POINT point) { _x = point.x; _y = point.y; }
	// �ϳ��� �ϸ� ���� ������ �; SetPoint �Լ� ����
	// ������ _x,_y�� RectMakeCenter(�� RectMake�ƴ� �Ϳ� ����!)
};

