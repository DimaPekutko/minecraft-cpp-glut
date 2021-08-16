#include "PlayerInventory.hpp"  
	
PlayerInventory::PlayerInventory()
{
    _slotsCount = GameConfigs::PLAYER_INVENTORY_SLOTS_COUNT;
    // for(int i = 0; i < _slotsCount; i++) {
        
    // }
    _slots.push_back(new ItemSlot(BlockTypes::GRASS_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::DIRT_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::STONE_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::SAND_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::COBBLESTONE_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::BRICK_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::STONEBRICK_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
    _slots.push_back(new ItemSlot(BlockTypes::PLANKS_BLOCK_TYPE, GameConfigs::MAX_ITEMS_PER_SLOT));
}

bool PlayerInventory::getSelectedBlockType(BlockType* block) {
    *block = _slots[_selectedSlotIndex]->getItemsType();
    return _slots[_selectedSlotIndex]->pop();
}

bool PlayerInventory::getBlockTypeByIndex(BlockType* block, int index) {
    if(index < 0 || index > _slots.size())
        return false;
    *block = _slots[index]->getItemsType();
    return true;
}

int PlayerInventory::getSlotsCount() {
    return _slotsCount;
}

int PlayerInventory::getSelectedSlotIndex() {
    return _selectedSlotIndex;
}

void PlayerInventory::setSlotSelectedIndex(int index) {
    _selectedSlotIndex = index;
    if(index >= _slots.size()) {
        _selectedSlotIndex = 0;
    }
    if(index < 0) { 
        _selectedSlotIndex = _slots.size()-1;
    }
}

PlayerInventory::~PlayerInventory()
{
	
}