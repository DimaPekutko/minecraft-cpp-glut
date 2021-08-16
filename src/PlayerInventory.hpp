#ifndef PLAYERINVENTORY_H
#define PLAYERINVENTORY_H
#pragma once

#include "Headers.h"
#include "ItemSlot.hpp"

class PlayerInventory
{
	private:
		std::vector<ItemSlot*> _slots;
		int _slotsCount = 0;
		int _selectedSlotIndex = 0;
	public:
		PlayerInventory();
		bool getSelectedBlockType(BlockType* block);
		bool getBlockTypeByIndex(BlockType* block, int index);
		int getSlotsCount();
		int getSelectedSlotIndex();
		void setSlotSelectedIndex(int index);
		~PlayerInventory();

};
#endif