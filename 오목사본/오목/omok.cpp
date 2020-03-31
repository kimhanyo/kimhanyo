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
				stone[i][j] = 0;
}

void omok::swap()
{
	if (next_Stone == true)
		next_Stone = false; 
	else
		next_Stone = true;
}

void omok::get_down_Black(int row, int col) { stone[row][col] = 1; }
void omok::get_down_White(int row, int col) { stone[row][col] = 2; }

bool omok::next() { return next_Stone; }

/*bool omok::win_Check(int row,int col)

{
	int num;
	int cnt;
	int tmp;

	num = get_State(row, col);
	tmp = row;
	cnt = 0;
	while (1)
	{
		while (1)
		{
			if (get_State(row, col) == num)
			{
				cnt++;
				row -= 1;
			}
			else break;

			if (cnt == 5 || row < 0)break;
		}
		if (cnt == 5)
			return true;

		row = tmp + 1;
		while (1)
		{
			if (get_State(row, col) == num)
			{
				cnt++;
				row += 1;
			}
			else break;

			if (cnt == 5)break;
		}
		if (cnt == 5)return true;
		else return false;
		//↑가로상황에서 5목이 됬는지 확인하는 작업

	}

}*/