#pragma once
#include "gameNode.h"
#include "progressBar.h"


class enemy : public gameNode
{
protected:
	int _ID;			// ���� ����
	int _duration;		// ����ð�<-ī��Ʈ�ν� �������, �������͹� � ���Դϴ�.
	RECT _rc;			// �浹�� �簢��
	float _x, _y;		// ��ġ ��ǥ x, y ������
	int _width, _height; // ��Ʈ �׸���� �ʺ� ����
	int _alphaValue;	// �̰� �پ���� ���Ǿ ������. 255�ƴϸ� �浹����
	bool _appear;		// �����ߴ���?
	bool _arrived;		// �ʱ� ��ġ�� �����ߴ���? -- �����ؾ� ������ �����ϸ� ���ݹ��� ����(������)
	int _frameX;
	int _frameCount;
	float _currentHP, _maxHP; // ü��
	progressBar* _hpBar; // ü�¹�
	int _fireReady;		// �غ� �Ǹ� ���̾��ϰ� �̰� �ϳ��� �ٿ���

public:
	enemy() {};
	~enemy() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void commomInit();
	void commonUpdate();
	void commonRender();
	inline void dealDamage(float x) { _currentHP -= x; }
	inline RECT getRect() { return _rc; }
	inline bool getAppear() { return _appear; }
	inline int getAlpha() { return _alphaValue; }
	inline int& getFireReady() { return _fireReady; }
	inline int getID() { return _ID; }
};

