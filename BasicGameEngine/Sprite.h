#pragma once

#include <cstdint>

/// <summary>
/// This stores a generic ID/Frame for an entity's current spritesheet/frame.
/// </summary>
typedef size_t SpriteID;
typedef size_t SpriteFrame;
typedef struct
{
	SpriteID id;
	SpriteFrame frame;
} Sprite;