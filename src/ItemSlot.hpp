#ifndef ITEMSLOT_H
#define ITEMSLOT_H
#pragma once

#include "Headers.h"
	
class ItemSlot  
{
	private:
		BlockType _itemsType;
		int _itemsCount = 0;
	public:

		ItemSlot(BlockType itemsType, int itemsCount);
		bool pop();
		BlockType getItemsType();
		~ItemSlot();

};
#endif