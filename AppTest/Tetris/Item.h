#ifndef __ITEM_H__
#define __ITEM_H__

typedef Item
{
	int type;
	int direct;
	int pointCount;
	int relOffset[4][2];
}CItem, *PItem;

enum ITEM_TYPE{
	/*
	 *##
	 *##
	 * */
	ITEM_TYPE_0,

	/*
	 *##
	 * ##
	 * */
	ITEM_TYPE_1,

	/*
	 *####
	 * */
	ITEM_TYPE_2,

	/*
	 * #
	 *###
	 * */
	ITEM_TYPE_3
};

void set_item_by_type(PItem pItem, int type, int direct);

void turn_item_by_direct(PItem pItem, int direct);

#endif

