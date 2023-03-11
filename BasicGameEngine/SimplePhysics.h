#pragma once
#include "Scene.h"

/// <summary>
/// SimplePhysics contains a few basic systems used to test the ECS.
/// </summary>

void ApplyGravity(SceneView<Velocity>& sceneView);

void ApplyVelocity(SceneView<Velocity, Transform>& sceneView);

void PrintPhysicsStuff(SceneView<Velocity, Transform, Name>& sceneView);