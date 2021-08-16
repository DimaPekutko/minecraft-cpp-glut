#include "ItemSlot.hpp"  
	
ItemSlot::ItemSlot(BlockType itemsType, int itemsCount)
{
    _itemsType = itemsType;
    _itemsCount = itemsCount;
}

bool ItemSlot::pop() {
    if(_itemsCount) {
        if(!GameConfigs::PLAYER_INFINITE_ITEMS_MODE)
            _itemsCount--;
        return true;
    }
    else
        return false;
}

BlockType ItemSlot::getItemsType() {
    return _itemsType;
}

ItemSlot::~ItemSlot()
{
	
}