#pragma once
#include "gameNode.h"

class animationTest : public gameNode
{
private:
	image* _camel;

	animation* _ani1;	//����Ʈ �����
	animation* _ani2;	//�迭 �����
	animation* _ani3;	//���� �����

public:
	animationTest() {};
	~animationTest() {};

	HRESULT init();
	void release();
	void update();
	void render();

};

