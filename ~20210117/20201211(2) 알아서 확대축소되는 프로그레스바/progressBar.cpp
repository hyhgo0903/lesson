#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(int width, int height)
{ // �� �ʺ� ���̸� �Է¹ް� ������ setX setY setPoint�Լ� ���Ŵ� �Ű����� �ٿ���
	_width = width;
	_height = height;
	_progressBarFront = IMAGEMANAGER->addImage("frontBar", "hpBarTop.bmp", 53, 5, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage("backBar", "hpBarBottom.bmp", 53, 5, true, RGB(255, 0, 255));

	if (width == _progressBarBack->getWidth() &&
		height == _progressBarBack->getHeight()) _needToBeResized = false;
	else _needToBeResized = true;
	// �̰� ���̸� ������ �ٸ����ϴµ� ������ �����ϸ� ���ϰ���

	
	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _width, _height);
}

void progressBar::render()
{
	if (!_needToBeResized) // ũ�� ������ �ʿ䰡 ���ٸ� ���� �׸��� ��ó�� �׸��ϴ�.
	{
		IMAGEMANAGER->render("backBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, 0, 0,
			_width, _height);

		IMAGEMANAGER->render("frontBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, 0, 0,
			_currentHPWidth, _height);
	}
	else
	{ // ũ�� ������ �ʿ䰡 �ִٸ� ���� �Ǹ鼭
	// ������ ���浵 �����Ǵ� TransparentBlt���� �������մϴ�.
	// ��Ҹ� : ���ʿ� �׳� ���ɷ� �ϸ� �����ʳ� ������ �ߴµ�
	// ����� ���� -> �����ٰ� �ϽŰ� ������ �ɷ����׸�..
		IMAGEMANAGER->resizedRender("backBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, 	_width, _height);

		IMAGEMANAGER->resizedRender("frontBar", getMemDC(),
			_rcProgress.left, _rcProgress.top, 	_currentHPWidth, _height);
	}
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{ // ����Ʈ��(���� ü��)�� �ʺ� ����
	_currentHPWidth = (currentGauge / maxGauge) * _width;
}
