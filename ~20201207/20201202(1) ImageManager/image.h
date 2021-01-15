#pragma once
class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//리소스 파일로부터
		LOAD_FILE,		//이미지 파일로부터
		LOAD_EMPTY,		//빈 비트맵 이미지를 만들수도 있고
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	//리소스를 불러올때 사용할 ID값
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;
		BYTE loadType;	//이미지 불러올 타입

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;	
	CHAR*			_fileName;		//파일 이름
	BOOL			_trans;			//특정 픽셀값을 제거할지 유무
	COLORREF		_transColor;	//제거할 픽셀값
public:

	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	void release();
	void setTransColor(BOOL trans, COLORREF transColor);


	void render(HDC hdc);
	//렌더함수(뿌릴DC, left, top)
	void render(HDC hdc, int destX, int destY);
	//렌더함수(뿌릴DC, 그려질 X(left), 그려질Y(top), 가져올X(left) 가져올Y(top), 가로, 세로 크기 (가져올) 
	void render(HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }
};

