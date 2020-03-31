#include "omok.h"
omok::omok()
{
		for (int i = 0; i < ROW; i++)
		{
			field_Row[i] = i * FIELD_INTERVAL + LEFT_SIDE;
			field_Col[i] = i * FIELD_INTERVAL + UP_SIDE;
		} 

		for (int i = 0; i < ROW; i++)
			for (int j = 0; j < COL; j++)
				stone[i][j] = 0; //모든 배열값을 0으로 초기화
}

void omok::swap() //흑백 순서 바꾸기
{
	if (next_Stone == true)
		next_Stone = false; 
	else
		next_Stone = true;
}

void omok::get_down_Black(int row, int col) { stone[row][col] = 1; } //흑돌 착수
void omok::get_down_White(int row, int col) { stone[row][col] = 2; } //백돌 착수

bool omok::next() { return next_Stone; } //흑돌, 백돌중 현재 둘 차례리턴

bool omok::win_Check(int row, int col) //승리조건

{
	int num; //주변에 깔려있는 돌이 같은 돌인지 판단하기위한 변수(현재 둔 위치의 정수 값을 가져온다) -35줄-
	int cnt; //오목 카운트
	int tmp; //임시변수(현재 둔 자리의 위치값을 기억한다)

	num = get_State(row, col);  //현재 둔 위치의 정수 값 기억
	tmp = row; //임시변수에 현재 둔 자리 위치값 저장
	cnt = 0;  //카운트 초기화
	while (1)
	{
		while (1)
		{
			if (get_State(row, col) == num) //파악할 위치의 돌이 현재 둔 돌과 같은색상의 돌일 경우
			{
				cnt++; //카운트 증가
				row -= 1; //오목판의 x좌표를 -1시켜줌(다음 비교에서 오목판에서 왼쪽의 돌과 비교하기 위함) 
			}
			else break; //파악할 위치의 돌이 현재 둔 돌과 다를시 탈출

			if (cnt == 5 || row == 0)break; //오목이 되었거나 오목판 왼쪽끝을 만날경우 탈출
		}
		if (cnt == 5) //오목이 되었을 경우
			return true; //true 값 리턴

		row = tmp + 1; //오목판의 x좌표를 기존좌표 +1 시켜줌(다음 비교에서 오목판에서 오른쪽의 돌과 비교하기 위함)
		while (1)
		{
			if (get_State(row, col) == num)
			{
				cnt++;
				row += 1;//오목판의 x좌표를 +1시켜줌(다음 비교에서 오목판에서 오른쪽의 돌과 비교하기 위함)
			}
			else break;

			if (cnt == 5 || row == ROW)break; // 오목이 되었거나 오목판 오른쪽끝을 만날경우 탈출
		}
		if (cnt == 5) //오목이 되었을 경우
			return true; //true 값 리턴
		//↑가로상황에서 오목이 됬는지 확인하는 작업
		//가로 판단끝

		row = tmp; //비교했던 좌표값을 초기 좌표값으로 바꿈
		tmp = col; 
		cnt = 0;
		while (1)
		{
			while (1)
			{
				if (get_State(row, col) == num)
				{
					cnt++;
					col -= 1; //오목판의 y좌표를 -1시켜줌(다음 비교에서 오목판에서 윗쪽의 돌과 비교하기 위함)
				}
				else break;

				if (cnt == 5 || col < 0)break; // 오목이 되었거나 오목판 윗쪽끝을 만날경우 탈출
			}
			if (cnt == 5)
				return true;

			col = tmp + 1; //오목판의 y좌표를 기존좌표 +1 시켜줌(다음 비교에서 오목판에서 아랫쪽의 돌과 비교하기 위함)
			while (1)
			{
				if (get_State(row, col) == num)
				{
					cnt++;
					col += 1; //오목판의 y좌표를 +1시켜줌(다음 비교에서 오목판에서 아랫쪽의 돌과 비교하기 위함)
				}
				else break;

				if (cnt == 5 || col == COL)break; // 오목이 되었거나 오목판 아랫쪽끝을 만날경우 탈출
			}
			if (cnt == 5)return true;
			//↑세로상황에서 오목이 됬는지 확인하는 작업
			//세로 판단 끝

			int tmp2; //대각선은 x,y좌표값을 동시에 바꾸가면서 비교해야하기 때문에 임시변수 하나 추가 선언
			col = tmp; //비교했던 좌표값을 초기 좌표값으로 바꿈
			tmp2 = row; //새로 만든 임시변수에 현재 둔 돌의 x좌표 기억시킴
			cnt = 0;
			while (1)
			{
				while (1)
				{
					if (get_State(row, col) == num)
					{
						cnt++;
						row -= 1;
						col -= 1;
						//↖
					}
					else break;

					if (cnt == 5 || row < 0 || col < 0)break;
				}
				if (cnt == 5)
					return true;

				col = tmp + 1;
				row = tmp2 + 1;

				while (1)
				{
					if (get_State(row, col) == num)
					{
						cnt++;
						row += 1;
						col += 1;
						//↘
					}
					else break;

					if (cnt == 5 || row == ROW || col == COL)break;
				}
				if (cnt == 5)return true;
				//↑대각선상황에서 오목이 됬는지 확인하는 작업  ↖↘

				col = tmp;
				row = tmp2;
				cnt = 0;
				while (1)
				{
					while (1)
					{
						if (get_State(row, col) == num)
						{
							cnt++;
							row -= 1;
							col += 1;
							//↙
						}
						else break;

						if (cnt == 5 || row < 0 || col == COL)break;
					}
					if (cnt == 5)
						return true;

					col = tmp - 1;
					row = tmp2 + 1;

					while (1)
					{
						if (get_State(row, col) == num)
						{
							cnt++;
							row += 1;
							col -= 1;
							//↗
						}
						else break;

						if (cnt == 5 || col < 0 || row == ROW)break;
					}
					if (cnt == 5)return true;
					else return false;
					//↑대각선상황에서 오목이 됬는지 확인하는 작업  ↗↙
					//대각선 판단 끝
				}
			}
		}
	}
}