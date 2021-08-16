#ifndef BLOCKTYPES_H
#define BLOCKTYPES_H
#pragma once

#include "Headers.h"

struct BlockType {
	std::string name;
	int textureAtlasPositions[6][2];	// texture x and y for every block edge
};

// static class for acces to all block types
class BlockTypes  
{
	public:
		static const BlockType GRASS_BLOCK_TYPE;
		static const BlockType DIRT_BLOCK_TYPE;
		static const BlockType STONE_BLOCK_TYPE;
		static const BlockType SAND_BLOCK_TYPE;
		static const BlockType COBBLESTONE_BLOCK_TYPE;
		static const BlockType BRICK_BLOCK_TYPE;
		static const BlockType STONEBRICK_BLOCK_TYPE;
		static const BlockType PLANKS_BLOCK_TYPE;
};
#endif