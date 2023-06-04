#pragma once

#include <cstdint>
#include <vector>

/// <summary>
/// This stores a generic ID/Frame for an entity's current spritesheet/frame.
/// The SpriteID is the filename of the sprite, minus any extensions.
/// Renderer implementations should load whatever image/frame data from files
/// with that initial name and whatever proper extensions exist.
/// </summary>
typedef std::string SpriteID;
typedef size_t SpriteFrame;
typedef struct
{
	SpriteID id;
	SpriteFrame frame;
} Sprite;