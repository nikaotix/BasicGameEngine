#pragma once
/// <summary>
/// AABB is the width+height of an entity's axis-aligned bounding box.
/// Width and height are doubled so we can define the box as:
/// Xpos-width to Xpos+width and Ypos-height to Ypos+height
/// Hopefully we add more shapes for colliders eventually
/// </summary>
typedef struct
{
	float width, height;
} AABB;