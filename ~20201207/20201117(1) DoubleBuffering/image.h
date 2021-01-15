#pragma once
class image
{
public:

	typedef struct tagImageInfo
	{ // typedef 재정의할때 사용
		HDC hMemDC;
		HBITMAP hBit; // 빈 비트맵
		HBITMAP hOBit; // 올드 비트맵
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
	//접근자
};

