#pragma once
#include "Scene.h"
#include "TwoDCamera.h"

/// <summary>
/// TwoDRenderer is an interface for rendering a 2D view into a scene.
/// </summary>
class TwoDRenderer {
public:
	virtual void RenderScene(Scene& scene, TwoDCamera& camera) = 0;
};