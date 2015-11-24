#include "Item.h"


void turn_item_by_direct(PItem pItem, int direct)
{
	int relOffset[4][2];
	switch(direct)
	{
		case 0:
			//default item direction state.
			return;
		break;

		case 1:
			//
		break;

		case 2:
		break;

		case 3:
		break;
	}
}

void set_item_by_type(PItem pItem, int type, int direct)
{
	switch(type)
	{
		case ITEM_TYPE_0:
			pItem->relOffset[0][0] = 0;
			pItem->relOffset[0][1] = 0;

			pItem->relOffset[1][0] = 1;
			pItem->relOffset[1][1] = 0;

			pItem->relOffset[2][0] = 0;
			pItem->relOffset[2][1] = 1;

			pItem->relOffset[3][0] = 1;
			pItem->relOffset[3][1] = 1;

		break;

		case ITEM_TYPE_1:

			pItem->relOffset[0][0] = 0;
			pItem->relOffset[0][1] = 0;

			pItem->relOffset[1][0] = 1;
			pItem->relOffset[1][1] = 0;

			pItem->relOffset[2][0] = 1;
			pItem->relOffset[2][1] = 1;

			pItem->relOffset[3][0] = 2;
			pItem->relOffset[3][1] = 1;
		break;

		case ITEM_TYPE_2:

			pItem->relOffset[0][0] = 0;
			pItem->relOffset[0][1] = 0;

			pItem->relOffset[1][0] = 1;
			pItem->relOffset[1][1] = 0;

			pItem->relOffset[2][0] = 2;
			pItem->relOffset[2][1] = 0;

			pItem->relOffset[3][0] = 3;
			pItem->relOffset[3][1] = 0;
		break;

		case ITEM_TYPE_3:

			pItem->relOffset[0][0] = 0;
			pItem->relOffset[0][1] = 0;

			pItem->relOffset[1][0] = -1;
			pItem->relOffset[1][1] = 1;

			pItem->relOffset[2][0] = 0;
			pItem->relOffset[2][1] = 1;

			pItem->relOffset[3][0] = 1;
			pItem->relOffset[3][1] = 1;
		break;

		default;
		break;
	}
}
