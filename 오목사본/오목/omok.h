#pragma once
#define FIELD_INTERVAL 26 //오목판 눈과 눈사이의 간격
#define STONE_INTERVAL (FIELD_INTERVAL/2) //돌의 반지름
#define ROW 19 //행
#define COL 19 //열
#define LEFT_SIDE 300 //오른쪽 여백공간 크기
#define UP_SIDE 50 //윗쪽 여백공간 크기
#define FLOWER_SPOT 4 //화점의 반지름

class omok
{
	int field_Row[ROW] = { 0 };
	int field_Col[COL] = { 0 }; 
	//오목판의 줄 위치를 저장하는 배열

	int stone[ROW][COL]; //바둑돌의 상태 정보 ( 0 : 안 둔 상태, 1 : 흑돌 존재, 2: 백돌 존재 )
	bool next_Stone = true; //흑백의 순서 true : 흑 flase : 백
public:
	omok();
	int get_Row(int row) { return field_Row[row]; }
	int get_Col(int col) { return field_Col[col]; }
	int get_State(int row, int col) { return stone[row][col]; } //오목판의 상태(돌들의 상태) 리턴

	void swap(); //흑백 교환
	void get_down_Black(int row, int col); //흑돌 착수
	void get_down_White(int row, int col); //백돌 착수

	bool next();
};

//int omok::stone[ROW][COL] = { 0 };
