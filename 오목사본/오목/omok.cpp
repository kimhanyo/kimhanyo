#include "omok.h"
omok::omok()
{
		for (int i = 0; i < ROW; i++)
		{
			field_Row[i] = i * FIELD_INTERVAL + LEFT_SIDE;
			field_Col[i] = i * FIELD_INTERVAL + UP_SIDE;
		} 
}