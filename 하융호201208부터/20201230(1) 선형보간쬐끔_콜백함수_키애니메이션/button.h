#pragma once
#include "gameNode.h"

typedef void(*CALLBACK_FUNCTION)(void);

//Lambda expression
//���� �غ��ñ��� �翬�� ������ ����ϸ� �̻ݹ޽��ϴ�
//���� �ȵƴµ� v11���� �߰�


//<functional> ���̺귯���� ����ϸ� �׾ȿ� move, bind, function���� 
//�Լ��� �ִµ� �̰��� ����ϸ� �ݹ��Լ� �Ķ���ͷ� �Ϲ� ������ ��밡���ϰ� ��
//�غ����� �غ��� ���ص� ��

//�ݹ��Լ��� �Լ������ʹ�. ������X(c#���� �����Ѱ� ��������Ʈ)
//�ݹ��Լ��� �Ἥ �ٸ����·� ȣ��.
//Ű�����Է¹����� �װ� �Ű��������ִ� �ݹ��Լ��������� �ش�ִϸ��̼��� ����ϰԸ����
//�����ΰ� ���� �ٸ� ��ü���� ��Ű��,
//�� ���� ������ ���� ��ٸ��� ���� �ƴ϶�
//�� ��ü�� ���� �ٽ� �θ�������
//�� ������ �ϰ� �ִ� ���̴�.

//�� �ݹ��Լ��� ���ٽ� �̾ ����ϴ°͵� ������
//���� �غ����� �ϰ� ���ҷ��� ���ص� �˴ϴ� ������ ����

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;

	const char* _imageName;
	image* _image;
	RECT _rc;

	float _x, _y;
	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;		//�ݹ��Լ� ����

public:
	button() {};
	~button() {};

	HRESULT init(const char* imageName, float x, float y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);

	void release();
	void update();
	void render();

};

