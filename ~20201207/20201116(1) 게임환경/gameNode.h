#pragma once

class gameNode
{
public:
	gameNode();
	virtual ~gameNode();
	// 버추얼로 둠 : 혹시나 자식들 메모리가 안없어질까봐

	//HRESULT는 마소 전용 디버깅 반환자 임
	//S_OK, E_FAIL, SUCCEDED 등으로 return값을 가짐
	//제대로 초기화 됐는지 안됐는지 호출해줌

	virtual HRESULT init();			//초기화 전용 함수
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 전용
	virtual void render(HDC hdc);	//그리기 전용

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};