#pragma once
#define FIELD_INTERVAL 26 //������ ���� �������� ����
#define STONE_INTERVAL (FIELD_INTERVAL/2) //���� ������
#define ROW 19 //��
#define COL 19 //��
#define LEFT_SIDE 300 //������ ������� ũ��
#define UP_SIDE 50 //���� ������� ũ��
#define FLOWER_SPOT 4 //ȭ���� ������

class omok
{
	int field_Row[ROW] = { 0 };
	int field_Col[COL] = { 0 };
	//�������� �� ��ġ�� �����ϴ� �迭

	int stone[ROW][COL]; //�ٵϵ��� ���� ���� ( 0 : �� �� ����, 1 : �浹 ����, 2: �鵹 ���� )
	bool next_Stone = true; //����� ���� true : �� flase : ��
public:
	omok();
	int get_Row(int row) { return field_Row[row]; }
	int get_Col(int col) { return field_Col[col]; }
	int get_State(int row, int col) { return stone[row][col]; } //�������� ����(������ ����) ����

	void swap(); //��� ��ȯ
	void get_down_Black(int row, int col); //�浹 ����
	void get_down_White(int row, int col); //�鵹 ����

	bool next();
	bool win_Check(int row, int col);
};

//int omok::stone[ROW][COL] = { 0 };
