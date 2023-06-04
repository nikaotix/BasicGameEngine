#pragma once


#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <vector>
#include "ResourceManagerWithOwner.h"
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
    virtual void LoadSprite(SpriteID& sprite);

private:

    SDL_Window* window { nullptr };
    SDL_Renderer* renderer{ nullptr };
    ResourceManagerWithOwner<SpriteID, SDLTwoDSprite, SDL_Renderer> spriteRsrcMgr;


};