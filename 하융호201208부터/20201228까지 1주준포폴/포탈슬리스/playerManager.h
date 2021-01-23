#pragma once
#include "gameNode.h"
#include "effect.h"


class itemManager;
class bulletManager;

#define TANKWIDTH 46
#define TANKHEIGHT 46
#define ITEMDURATION 600

enum state // �ִϸ��̼� ������ �̿�
{
	RIGHTIDLE, LEFTIDLE, RIGHTRUN, LEFTRUN, RIGHTATTACK, LEFTATTACK
};

enum type // ���� ��ũ ����
{
	CANNON,	MISSILE, MULTI, SUPER
};

struct tagTank
{	
	float x, y;			// _x, _y ����
	float gravity;
	int probeY;			// Y Ž����
	float angle;		// �ɴ� ����
	float jumpPower;
	bool isJump;
	RECT rc;			// �簢��
	state state;		// �÷��̾� ����
	type type;			// ���� ��ũ ����
	
	float currentHP, maxHP, currentDelay, maxDelay, currentPower, maxPower;
	int frameX, aniCount; // count�� �ϸ� ++������ count 60�ɶ��� 1������ ����ϰ� �� ��
};

class playerManager : public gameNode
{
private:
	tagTank _tank;
	// _im->getStateSlot(0~2) �̰� ��ũ ������ ���ʽ� ������ �ֱ� ���� ������ �� Ŭ���� ����������� ���� Ȱ���
	// 0�̸� ĳ��(��2��) 1�̸� �̻���(�ӵ����� �����º���) 2�̸� ����(���ݵ�����) ����������
	bool _usingItem[4];		// 4�� �����ۿ� ���� ��������� (�������̾� ������, �Ŀ��� ��2��, ���� ����, ����� ȸ�� ��)
	int _itemDuration[4];	// 4�� ���¿� ���� ���ӽð�
	int _effectFrameX[4];	// 4�� ����Ʈ�� ���� ������ (���ӽð��� �̿��ؼ� ���ŵ�)
	int _specialCount;		// ���ݸ��� ������ 2�϶� Ư������ �߻�
	float _damageCoefficient; // ���ݵ����
	int _difficulty;		// ó���� ������ -> 0���� 1���� 2�ϵ�(����� 2�� 1�� 1/2�� ü�� 5�� 1�� 1/2��)
	int _selectedTank;		// ó���� ������ -> 0ĳ�� 1�̻��� 2��Ƽ

	bool _autoChanged; // ó������ ���� ���� �����ϸ� �˾Ƽ� �ٲٰ�.. �����ϱ� �մϴ�.
	bool _isInvincible; // �������� ��� �Ǵ�����
	bool _isBlink;	// ������ ��������
	int _blinkCount; // �������� ���ӽð�

	bool _isGameOver; // ���ӿ��� ���ǿ� ����

	BYTE _alphaValue;
	effect* _changeEffect;

	// ���ϴ� ������ ���� �͵�
	itemManager* _im;
	bulletManager* _bm;

public:
	playerManager() {};
	~playerManager() {};

	virtual HRESULT init(int data);
	virtual void release();
	virtual void update();
	virtual void render();

	void keyInput();
	void tankMove();
	void stateChange();
	void interfaceRender();
	void delayReduce();

	void animationUpdate();
	void stateRender();
	void fire();

	void test();

	inline void dealDamage(float x) { _tank.currentHP -= x; }
	inline RECT getRect() { return _tank.rc; }
	inline bool getIsInvincible() {	return _isInvincible;}
	inline void setIsBlink() { _isBlink = true; }
	inline bool getIsGameOver() { return _isGameOver; }
	
	void setImMemoryAddressLink(itemManager* im) { _im = im; }
	void setBmMemoryAddressLink(bulletManager* bm) { _bm = bm; }
};

