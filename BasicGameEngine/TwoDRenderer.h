#pragma once
#include <string>
#include <unordered_map>
#include "Scene.h"
#include "TwoDCamera.h"

/// <summary>
/// TwoDRenderer is an interface for rendering a 2D view into a scene.
/// </summary>
class TwoDRenderer {
public:
	virtual void RenderScene(Scene& scene, TwoDCamera& camera) = 0;
	virtual void LoadSprite(SpriteID& sprite) = 0;
};