#include <iostream>
#include "SDLTwoDRenderer.h"
#include "SDLUtil.h"

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
	surface = SDL_GetWindowSurface(window);

	//Fill the surface white
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

	//Update the surface
	SDL_UpdateWindowSurface(window);

	//Warning: need to initialize the SDL event loop after this!
}

SDLTwoDRenderer::~SDLTwoDRenderer()
{
	SDL_DestroyWindow(window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	
	//Warning: still need to call SDL_Quit somewhere!
}

void SDLTwoDRenderer::RenderScene(Scene& scene, TwoDCamera& camera)
{
}
