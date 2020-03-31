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
				stone[i][j] = 0; //��� �迭���� 0���� �ʱ�ȭ
}

void omok::swap() //��� ���� �ٲٱ�
{
	if (next_Stone == true)
		next_Stone = false; 
	else
		next_Stone = true;
}

void omok::get_down_Black(int row, int col) { stone[row][col] = 1; } //�浹 ����
void omok::get_down_White(int row, int col) { stone[row][col] = 2; } //�鵹 ����

bool omok::next() { return next_Stone; } //�浹, �鵹�� ���� �� ���ʸ���

bool omok::win_Check(int row, int col) //�¸�����

{
	int num; //�ֺ��� ����ִ� ���� ���� ������ �Ǵ��ϱ����� ����(���� �� ��ġ�� ���� ���� �����´�) -35��-
	int cnt; //���� ī��Ʈ
	int tmp; //�ӽú���(���� �� �ڸ��� ��ġ���� ����Ѵ�)

	num = get_State(row, col);  //���� �� ��ġ�� ���� �� ���
	tmp = row; //�ӽú����� ���� �� �ڸ� ��ġ�� ����
	cnt = 0;  //ī��Ʈ �ʱ�ȭ
	while (1)
	{
		while (1)
		{
			if (get_State(row, col) == num) //�ľ��� ��ġ�� ���� ���� �� ���� ���������� ���� ���
			{
				cnt++; //ī��Ʈ ����
				row -= 1; //�������� x��ǥ�� -1������(���� �񱳿��� �����ǿ��� ������ ���� ���ϱ� ����) 
			}
			else break; //�ľ��� ��ġ�� ���� ���� �� ���� �ٸ��� Ż��

			if (cnt == 5 || row == 0)break; //������ �Ǿ��ų� ������ ���ʳ��� ������� Ż��
		}
		if (cnt == 5) //������ �Ǿ��� ���
			return true; //true �� ����

		row = tmp + 1; //�������� x��ǥ�� ������ǥ +1 ������(���� �񱳿��� �����ǿ��� �������� ���� ���ϱ� ����)
		while (1)
		{
			if (get_State(row, col) == num)
			{
				cnt++;
				row += 1;//�������� x��ǥ�� +1������(���� �񱳿��� �����ǿ��� �������� ���� ���ϱ� ����)
			}
			else break;

			if (cnt == 5 || row == ROW)break; // ������ �Ǿ��ų� ������ �����ʳ��� ������� Ż��
		}
		if (cnt == 5) //������ �Ǿ��� ���
			return true; //true �� ����
		//�谡�λ�Ȳ���� ������ ����� Ȯ���ϴ� �۾�
		//���� �Ǵܳ�

		row = tmp; //���ߴ� ��ǥ���� �ʱ� ��ǥ������ �ٲ�
		tmp = col; 
		cnt = 0;
		while (1)
		{
			while (1)
			{
				if (get_State(row, col) == num)
				{
					cnt++;
					col -= 1; //�������� y��ǥ�� -1������(���� �񱳿��� �����ǿ��� ������ ���� ���ϱ� ����)
				}
				else break;

				if (cnt == 5 || col < 0)break; // ������ �Ǿ��ų� ������ ���ʳ��� ������� Ż��
			}
			if (cnt == 5)
				return true;

			col = tmp + 1; //�������� y��ǥ�� ������ǥ +1 ������(���� �񱳿��� �����ǿ��� �Ʒ����� ���� ���ϱ� ����)
			while (1)
			{
				if (get_State(row, col) == num)
				{
					cnt++;
					col += 1; //�������� y��ǥ�� +1������(���� �񱳿��� �����ǿ��� �Ʒ����� ���� ���ϱ� ����)
				}
				else break;

				if (cnt == 5 || col == COL)break; // ������ �Ǿ��ų� ������ �Ʒ��ʳ��� ������� Ż��
			}
			if (cnt == 5)return true;
			//�輼�λ�Ȳ���� ������ ����� Ȯ���ϴ� �۾�
			//���� �Ǵ� ��

			int tmp2; //�밢���� x,y��ǥ���� ���ÿ� �ٲٰ��鼭 ���ؾ��ϱ� ������ �ӽú��� �ϳ� �߰� ����
			col = tmp; //���ߴ� ��ǥ���� �ʱ� ��ǥ������ �ٲ�
			tmp2 = row; //���� ���� �ӽú����� ���� �� ���� x��ǥ ����Ŵ
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
						//��
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
						//��
					}
					else break;

					if (cnt == 5 || row == ROW || col == COL)break;
				}
				if (cnt == 5)return true;
				//��밢����Ȳ���� ������ ����� Ȯ���ϴ� �۾�  �آ�

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
							//��
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
							//��
						}
						else break;

						if (cnt == 5 || col < 0 || row == ROW)break;
					}
					if (cnt == 5)return true;
					else return false;
					//��밢����Ȳ���� ������ ����� Ȯ���ϴ� �۾�  �֢�
					//�밢�� �Ǵ� ��
				}
			}
		}
	}
}