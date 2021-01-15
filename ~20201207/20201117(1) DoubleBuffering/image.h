#pragma once
class image
{
public:

	typedef struct tagImageInfo
	{ // typedef �������Ҷ� ���
		HDC hMemDC;
		HBITMAP hBit; // �� ��Ʈ��
		HBITMAP hOBit; // �õ� ��Ʈ��
		int width;
		int height;

		tagImageInfo()
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO _backBuffer;
public:

	image();
	~image();

	HRESULT init(int width, int height);
	void release();
	void render(HDC hdc, int destX, int destY);

	inline HDC getMemDC() { return _backBuffer->hMemDC; }
	//������
};

