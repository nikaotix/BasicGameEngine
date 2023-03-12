#pragma once


#include <SDL.h>
#include <string>
#include <vector>
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
private:
    SDL_Window* window { nullptr };
    SDL_Renderer* renderer{ nullptr };
    std::vector<SDLTwoDSprite> sprites;
};
