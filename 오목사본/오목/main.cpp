#include <windows.h>	// 윈도우 헤더파일
#include <math.h>
#include "omok.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//CALLBACK 매크로
HINSTANCE g_hInst;					//인스턴스 핸들
LPCTSTR lpszClass = TEXT("오목_김요한(2015032021)");	 //제목 표시줄에 표시되는 내용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)   //main 함수
{
	HWND hWnd;		//윈도우 핸들 선언
	MSG Message;		 //메세지 구조체 변수 선언
	WNDCLASS WndClass;	 //Windows Class 구조체 변수 선언
	g_hInst = hInstance;    //hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

	WndClass.cbClsExtra = 0;	//예약 영역. 지금은 사용X
	WndClass.cbWndExtra = 0;	//예약 영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// 윈도우의 배경 색상을 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //윈도우의 커서(마우스포인터) 모양을 지정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //윈도우의 커서 아이콘 모양 지정
	WndClass.hInstance = hInstance;		 //윈도우 클래스를 등록하는 프로그램 번호
	WndClass.lpfnWndProc = WndProc;		//윈도우 메세지 처리 함수 지정
	WndClass.lpszClassName = lpszClass;		//윈도우 클래스의 이름 지정
	WndClass.lpszMenuName = NULL;		//이 프로그램의 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//윈도우의 스타일을 정의

	RegisterClass(&WndClass);			//WNDCLASS 구조체의 번지를 전달


	//윈도우를 생성하고 창에 표시하는 기능을 수행
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//메세지 루프를 실행
	while (GetMessage(&Message, NULL, 0, 0)) {	//Queue에 있는 메세지를 읽어들인다
		TranslateMessage(&Message);   //키보드 입력 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록
		DispatchMessage(&Message);   //메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
	}
	return (int)Message.wParam;				//탈출 코드. 프로그램 종료
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	HDC hdc; // HDC 선언
	PAINTSTRUCT ps;//페인트스트럭트 포인터 선언
	static int x, y;
	static omok *OMOK;
	HBRUSH hBrush, oldBrush, bBrush, wBrush;
	// 배경색으로 사용할 브러시를 생성한다. 

	switch (iMessage) { // iMessage 확인

	case WM_CREATE:
		OMOK = new omok;
		break;

	case WM_DESTROY: // 종료버튼 누르면
		delete OMOK;
		PostQuitMessage(0); // 종료
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam); //x좌표
		y = HIWORD(lParam); //y좌표
		if (x > (OMOK->get_Row(0) - STONE_INTERVAL) && y > (OMOK->get_Col(0) - STONE_INTERVAL) && x < (OMOK->get_Row(ROW - 1) + STONE_INTERVAL) && y < (OMOK->get_Col(COL - 1) + STONE_INTERVAL))
		{
			x = (x - OMOK->get_Row(0) + STONE_INTERVAL) / FIELD_INTERVAL;
			y = (y - OMOK->get_Col(0) + STONE_INTERVAL) / FIELD_INTERVAL;
			if (OMOK->get_State(x,y) == 0) //돌이 놓여있지 않다면
			{
				if (OMOK->next())
					OMOK->get_down_Black(x, y); //흑돌 차례일때 흑돌 착수
				else 
					OMOK->get_down_White(x, y); //백돌 차례일때 백돌 착수

				OMOK->swap(); //흑,백 순서 바꾸기
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT: // 그리기
		hdc = BeginPaint(hWnd, &ps); //dc핸들 선언
		hBrush = CreateSolidBrush(RGB(244, 176, 77));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, OMOK->get_Row(0) - FIELD_INTERVAL, OMOK->get_Col(0) - FIELD_INTERVAL, OMOK->get_Row(ROW - 1) + FIELD_INTERVAL, OMOK->get_Col(COL - 1) + FIELD_INTERVAL);
		SelectObject(hdc, oldBrush); //old브러쉬(기존브러쉬)를 선택함
		DeleteObject(hBrush); //hBrush를 삭제

		for(int i=0;i<ROW;i++)
		{
			MoveToEx(hdc, OMOK->get_Row(0), OMOK->get_Col(i), NULL);
			LineTo(hdc, OMOK->get_Row(ROW - 1), OMOK->get_Col(i));
		}
		for (int i = 0; i < COL; i++)
		{
			MoveToEx(hdc, OMOK->get_Row(i), OMOK->get_Col(0), NULL);
			LineTo(hdc, OMOK->get_Row(i), OMOK->get_Col(COL - 1));
		}
		//오목판 줄 긋기

		bBrush = CreateSolidBrush(RGB(0, 0, 0)); //검정색
		wBrush = CreateSolidBrush(RGB(255, 255, 255)); //흰색
		oldBrush = (HBRUSH)SelectObject(hdc, bBrush);

		Ellipse(hdc, OMOK->get_Row(3) - FLOWER_SPOT, OMOK->get_Col(3) - FLOWER_SPOT, OMOK->get_Row(3) + FLOWER_SPOT, OMOK->get_Col(3) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(9) - FLOWER_SPOT, OMOK->get_Col(3) - FLOWER_SPOT, OMOK->get_Row(9) + FLOWER_SPOT, OMOK->get_Col(3) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(15) - FLOWER_SPOT, OMOK->get_Col(3) - FLOWER_SPOT, OMOK->get_Row(15) + FLOWER_SPOT, OMOK->get_Col(3) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(3) - FLOWER_SPOT, OMOK->get_Col(9) - FLOWER_SPOT, OMOK->get_Row(3) + FLOWER_SPOT, OMOK->get_Col(9) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(9) - FLOWER_SPOT, OMOK->get_Col(9) - FLOWER_SPOT, OMOK->get_Row(9) + FLOWER_SPOT, OMOK->get_Col(9) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(15) - FLOWER_SPOT, OMOK->get_Col(9) - FLOWER_SPOT, OMOK->get_Row(15) + FLOWER_SPOT, OMOK->get_Col(9) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(3) - FLOWER_SPOT, OMOK->get_Col(15) - FLOWER_SPOT, OMOK->get_Row(3) + FLOWER_SPOT, OMOK->get_Col(15) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(9) - FLOWER_SPOT, OMOK->get_Col(15) - FLOWER_SPOT, OMOK->get_Row(9) + FLOWER_SPOT, OMOK->get_Col(15) + FLOWER_SPOT);
		Ellipse(hdc, OMOK->get_Row(15) - FLOWER_SPOT, OMOK->get_Col(15) - FLOWER_SPOT, OMOK->get_Row(15) + FLOWER_SPOT, OMOK->get_Col(15) + FLOWER_SPOT);
		//화점
		SelectObject(hdc, oldBrush); //old브러쉬(기존브러쉬)를 선택함

		for (int i = 0; i < ROW; i++) 
		{
			for (int j = 0; j < COL; j++) 
			{
				if (OMOK->get_State(i,j) > 0) // 바둑돌이 놓여져 있는 경우 (1:흑돌, 2:흰돌) 
				{  
					if (OMOK->get_State(i, j) == 1)
						SelectObject(hdc, bBrush); //흑돌
					else 
						SelectObject(hdc, wBrush); //흰돌

					Ellipse(hdc, OMOK->get_Row(x) - STONE_INTERVAL, OMOK->get_Col(y) - STONE_INTERVAL, OMOK->get_Row(x) + STONE_INTERVAL, OMOK->get_Col(y) + STONE_INTERVAL);
				}
			}
		}

		SelectObject(hdc, oldBrush); //old브러쉬(기존브러쉬)를 선택함
		DeleteObject(bBrush); //bBrush를 삭제
		DeleteObject(wBrush); //wBrush를 삭제
		EndPaint(hWnd, &ps);
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
