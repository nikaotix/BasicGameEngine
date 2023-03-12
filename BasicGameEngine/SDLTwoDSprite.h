#pragma once

#include <vector>
#include <SDL.h>

/// <summary>
/// Struct for storing SDL renderer sprite info
/// </summary>
typedef struct
{
	SDL_Texture* texture;
	std::vector<SDL_Rect> frames;
} SDLTwoDSprite;

