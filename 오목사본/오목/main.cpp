#include <windows.h>	// ������ �������
#include <math.h>
#include "omok.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//CALLBACK ��ũ��
HINSTANCE g_hInst;					//�ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("����_�����(2015032021)");	 //���� ǥ���ٿ� ǥ�õǴ� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam, int nCmdShow)   //main �Լ�
{
	HWND hWnd;		//������ �ڵ� ����
	MSG Message;		 //�޼��� ����ü ���� ����
	WNDCLASS WndClass;	 //Windows Class ����ü ���� ����
	g_hInst = hInstance;    //hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

	WndClass.cbClsExtra = 0;	//���� ����. ������ ���X
	WndClass.cbWndExtra = 0;	//���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// �������� ��� ������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //�������� Ŀ��(���콺������) ����� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //�������� Ŀ�� ������ ��� ����
	WndClass.hInstance = hInstance;		 //������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass.lpfnWndProc = WndProc;		//������ �޼��� ó�� �Լ� ����
	WndClass.lpszClassName = lpszClass;		//������ Ŭ������ �̸� ����
	WndClass.lpszMenuName = NULL;		//�� ���α׷��� �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//�������� ��Ÿ���� ����

	RegisterClass(&WndClass);			//WNDCLASS ����ü�� ������ ����


	//�����츦 �����ϰ� â�� ǥ���ϴ� ����� ����
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//�޼��� ������ ����
	while (GetMessage(&Message, NULL, 0, 0)) {	//Queue�� �ִ� �޼����� �о���δ�
		TranslateMessage(&Message);   //Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ���� ����� �� �ֵ���
		DispatchMessage(&Message);   //�޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
	}
	return (int)Message.wParam;				//Ż�� �ڵ�. ���α׷� ����
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	HDC hdc; // HDC ����
	PAINTSTRUCT ps;//����Ʈ��Ʈ��Ʈ ������ ����
	static int x, y;
	static omok *OMOK;
	static bool win = false;
	HBRUSH hBrush, oldBrush, bBrush, wBrush;
	// �������� ����� �귯�ø� �����Ѵ�. 

	switch (iMessage) { // iMessage Ȯ��

	case WM_CREATE:
		OMOK = new omok;
		break;

	case WM_DESTROY: // �����ư ������
		delete OMOK;
		PostQuitMessage(0); // ����
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam); //x��ǥ
		y = HIWORD(lParam); //y��ǥ
		if (x > (OMOK->get_Row(0) - STONE_INTERVAL) && y > (OMOK->get_Col(0) - STONE_INTERVAL) && x < (OMOK->get_Row(ROW - 1) + STONE_INTERVAL) && y < (OMOK->get_Col(COL - 1) + STONE_INTERVAL))
		{
			x = (x - OMOK->get_Row(0) + STONE_INTERVAL) / FIELD_INTERVAL;
			y = (y - OMOK->get_Col(0) + STONE_INTERVAL) / FIELD_INTERVAL;
			if (OMOK->get_State(x, y) == 0) //���� �������� �ʴٸ�
			{
				if (OMOK->next())
					OMOK->get_down_Black(x, y); //�浹 �����϶� �浹 ����
				else
					OMOK->get_down_White(x, y); //�鵹 �����϶� �鵹 ����

				if (OMOK->win_Check(x, y))
					win = true;
				
				OMOK->swap(); //��,�� ���� �ٲٱ�
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;

	case WM_PAINT: // �׸���
		static HDC MemDC, tmpDC;
		static HBITMAP BackBit, oldBackBit;
		static RECT bufferRT;
		hdc = BeginPaint(hWnd, &ps);

		//******************************************************************************
		GetClientRect(hWnd, &bufferRT);
		MemDC = CreateCompatibleDC(hdc);
		BackBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
		oldBackBit = (HBITMAP)SelectObject(MemDC, BackBit);
		PatBlt(MemDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		//******************************************************************************
		//����� ���۸� ó��

		hBrush = CreateSolidBrush(RGB(244, 176, 77));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, OMOK->get_Row(0) - FIELD_INTERVAL, OMOK->get_Col(0) - FIELD_INTERVAL, OMOK->get_Row(ROW - 1) + FIELD_INTERVAL, OMOK->get_Col(COL - 1) + FIELD_INTERVAL);
		SelectObject(hdc, oldBrush); //old�귯��(�����귯��)�� ������
		DeleteObject(hBrush); //hBrush�� ����

		for (int i = 0; i < ROW; i++)
		{
			MoveToEx(hdc, OMOK->get_Row(0), OMOK->get_Col(i), NULL);
			LineTo(hdc, OMOK->get_Row(ROW - 1), OMOK->get_Col(i));
		}
		for (int i = 0; i < COL; i++)
		{
			MoveToEx(hdc, OMOK->get_Row(i), OMOK->get_Col(0), NULL);
			LineTo(hdc, OMOK->get_Row(i), OMOK->get_Col(COL - 1));
		}
		//������ �� �߱�

		bBrush = CreateSolidBrush(RGB(0, 0, 0)); //������
		wBrush = CreateSolidBrush(RGB(255, 255, 255)); //���
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
		//ȭ��

		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (OMOK->get_State(i, j) > 0) // �ٵϵ��� ������ �ִ� ��� (1:�浹, 2:��) 
				{
					if (OMOK->get_State(i, j) == 1)
						SelectObject(hdc, bBrush); //�浹
					else
						SelectObject(hdc, wBrush); //��

					Ellipse(hdc, OMOK->get_Row(i) - STONE_INTERVAL, OMOK->get_Col(j) - STONE_INTERVAL, OMOK->get_Row(i) + STONE_INTERVAL, OMOK->get_Col(j) + STONE_INTERVAL);
				}
			}
		}

		if (win && OMOK->get_State(x, y) == 1) //�浹�� �¸���
		{
				if (MessageBox(hWnd, TEXT("�� �¸�!!"), TEXT("�浹�� �̰���ϴ�!"), MB_OK) == IDOK)
				{
					delete OMOK;
					PostQuitMessage(0); // ����
				}
		}

		if (win && OMOK->get_State(x, y) == 2) //�鵹�� �¸���
		{
				if (MessageBox(hWnd, TEXT("�� �¸�!!"), TEXT("�鵹�� �̰���ϴ�!"), MB_OK) == IDOK)
				{
					delete OMOK;
					PostQuitMessage(0); // ����
				}
		}
		//***************************************************************************
		tmpDC = hdc;
		hdc = MemDC;
		MemDC = tmpDC;
		GetClientRect(hWnd, &bufferRT);
		BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, MemDC, 0, 0, SRCCOPY);
		SelectObject(MemDC, oldBackBit);
		DeleteObject(BackBit);
		DeleteDC(MemDC);
		//****************************************************************************
		//����� ���۸� ó��

		SelectObject(hdc, oldBrush); //old�귯��(�����귯��)�� ������
		DeleteObject(bBrush); //bBrush�� ����
		DeleteObject(wBrush); //wBrush�� ����
		EndPaint(hWnd, &ps); //����Ʈ ����
		break;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
