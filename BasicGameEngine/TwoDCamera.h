#pragma once

/// <summary>
/// Camera provides an orign/size of the view into the world.
/// Used as both an entity component and as a direct argument
/// for a TwoDRenderer.
/// </summary>
typedef struct {
	float x, y; //top-left corner of the projection of the world.
	float width, height;
} TwoDCamera;