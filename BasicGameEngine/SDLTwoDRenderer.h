#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <vector>
#include "RefCountedResource.h"
#include "TwoDRenderer.h"
#include "SDLTwoDSprite.h"

/// <summary>
/// 2D renderer using SDL_Renderer as a backend.
/// </summary>
class SDLTwoDRenderer :
    public TwoDRenderer
{
public:
    // just the args for the SDL window.
    SDLTwoDRenderer(const std::string& title , int x, int y, int w, int h, uint32_t flags);
    ~SDLTwoDRenderer();
    virtual void RenderScene(Scene& scene, TwoDCamera& camera);

    // TODO: figure out a better way to handle loading resources!
    // Load a sprite from a simple-ish format description:
    // first line is the ID number of the sprite
    // second line is the filename of the sprite
    // following lines are frames in x y w h.
    void LoadSprite(const std::string& spriteInfo);
private:
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer{ nullptr };
    std::vector<RefCountedResource<SDLTwoDSprite>> sprites;
};
