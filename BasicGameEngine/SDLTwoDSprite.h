#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "Util.h"

/// <summary>
/// Struct for storing SDL renderer sprite info
/// Sprite data is stored on-disk in .png and .anim files.
/// PNG is obvious, anim is space-separated SDL_Rect params,
/// one per line. Simple as.
/// </summary>

struct SDLTwoDSprite
{
	SpriteID id;
	SDL_Texture* texture;
	std::vector<SDL_Rect> frames;
	SDLTwoDSprite(SpriteID id, SDL_Texture* texture, std::vector<SDL_Rect>& frames) : id(id), texture(texture), frames(frames) {};
	SDLTwoDSprite(SpriteID id, SDL_Renderer* renderer) : id(id)
	{
		texture = nullptr;
		auto filename = NameToString<SpriteID>("sprites", id, ".png");
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (surface == nullptr)
		{
			std::cout << "couldn't load file?" << std::endl;
		}
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		// TODO: actually load the rects lol
		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = 32;
		rect.h = 32;
		frames.push_back(rect);

	};
	
	// THIS SHOULD NOT EXIST!
	//SDLTwoDSprite(SpriteID id)
	//{
	//	texture = nullptr;
	//	return;
	//}

	~SDLTwoDSprite()
	{
		SDL_DestroyTexture(texture);
	};
};

