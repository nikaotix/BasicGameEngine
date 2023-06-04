#include <algorithm>
#include <iostream>
#include <SDL_image.h>
#include "SDLTwoDRenderer.h"
#include "SDLUtil.h"
#include "Util.h"

SDLTwoDRenderer::SDLTwoDRenderer(const std::string& title, int x, int y, int w, int h, uint32_t flags)
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		PrintSDLError("Couldn't init SDL video");
		return;
	}
	window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
	if (window == nullptr)
	{
		PrintSDLError("Couldn't create SDL window");
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);


	if (SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE))
	{
		PrintSDLError("Couldn't set SDL render draw color");
		return;
	}
	if (SDL_RenderClear(renderer) < 0)
	{
		PrintSDLError("Couldn't clear SDL renderer");
		return;
	}

	if (!(IMG_Init(IMG_INIT_PNG) && IMG_INIT_PNG))
	{
		PrintSDLError("Couldn't initialize SDL_image for PNGs");
		return;
	}

	spriteRsrcMgr.Init(renderer);
}

SDLTwoDRenderer::~SDLTwoDRenderer()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	
	//Warning: still need to call SDL_Quit somewhere!
}

// TODO: add rotation/flipping to this struct
struct RenderCopyExCall
{
	SDL_Texture* texture;
	SDL_Rect src;
	SDL_Rect dst;
	float z;
	RenderCopyExCall(SDL_Texture* t, const SDL_Rect s, const SDL_Rect d, const float z) :
		texture(t), src(s), dst(d), z(z) {};

	void operator=(const RenderCopyExCall& r1)
	{
		texture = r1.texture;
		src = r1.src;
		dst = r1.dst;
		z = r1.z;
	}
	friend bool operator<(const RenderCopyExCall& r1, const RenderCopyExCall& r2)
	{
		return r1.z < r2.z;
	}

};
// it looks like a system, talks like a system, but isn't really a system
// since it touches a lot of its own internal state.
void SDLTwoDRenderer::RenderScene(Scene& scene, TwoDCamera& camera)
{

	//first we clear the screen
	if (SDL_RenderClear(renderer) < 0)
	{
		PrintSDLError("Couldn't clear SDL renderer");
		return;
	}

	std::vector<RenderCopyExCall> renderCalls;
	std::vector <std::shared_lock<std::shared_mutex>> spriteLocks;

	// create render calls for every sprite
	auto drawables = SceneView<Transform, Sprite>(scene);
	auto drawablesIter = drawables.begin();
	while (drawablesIter != drawables.end())
	{
		std::cout << "Creating render calls for sprites" << std::endl;
		// get the drawable info 
		const auto& sprite = scene.Get<Sprite>(*drawablesIter);
		const auto& transform = scene.Get<Transform>(*drawablesIter);

		float scaleX = 1;
		float scaleY = 1;
		// TODO: get scale factors from entity if it has them!

		// get the SDL texture/rect
		SDLTwoDSprite* sdl_sprite = nullptr;
		// need to lock each sprite resource we're going to use for this draw.
		
		auto lockedRsrc = spriteRsrcMgr.Get(sprite->id);
		spriteLocks.push_back(std::move(lockedRsrc.lock));
		sdl_sprite = lockedRsrc.rsrc;
		if (sdl_sprite != nullptr)
		{
			std::cout << "found a sprite to draw" << std::endl;
			SDL_Texture* texture = sdl_sprite->texture; //SDL_Texture is an incomplete class, can't use a reference
			const SDL_Rect& src = sdl_sprite->frames[sprite->frame];

			SDL_Rect dst{};
			// offset sprite world position by camera position
			// TODO: define the world coordinate system and have a clean conversion into SDL coords (top-left is 0,0)? 
			dst.x = int(transform->x - camera.x);
			dst.y = int(transform->y - camera.y);
			dst.w = int(src.w * scaleX);
			dst.h = int(src.h * scaleY);

			renderCalls.emplace_back(texture, src, dst, transform->z);
		}
		++drawablesIter;
	}

	// sort our render calls by z-depth - larger Z values first for back-to-front draw
	std::make_heap(renderCalls.begin(), renderCalls.end());

	//Why is this a while, just iterate from back to front you goof
	/*
	while (!renderCalls.empty())
	{
		std::cout << "Drawing sprite hopefully" << std::endl;
		RenderCopyExCall renderCall = renderCalls[renderCalls.size()-1]; //element at end is max (it's a heap)
		std::pop_heap(renderCalls.begin(), renderCalls.end());
		if (SDL_RenderCopyEx(renderer, renderCall.texture, &(renderCall.src), &(renderCall.dst),
			0, nullptr, SDL_FLIP_NONE) < 0)
		{
			PrintSDLError("RenderCopyEx failed");
		}
	}
	*/
	for (auto iter = renderCalls.rbegin(); iter != renderCalls.rend(); iter++)
	{
		if (SDL_RenderCopyEx(renderer, (*iter).texture, &(*iter).src, &(*iter).dst,
			0, nullptr, SDL_FLIP_NONE) < 0)
		{
			PrintSDLError("RenderCopyEx failed");
		}
	}

	SDL_RenderPresent(renderer);

}

void SDLTwoDRenderer::LoadSprite(SpriteID& sprite)
{
	spriteRsrcMgr.Load(sprite);
}
