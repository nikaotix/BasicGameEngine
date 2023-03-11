#pragma once
#include "Scene.h"

void ApplyGravity(SceneView<Velocity>& sceneView);

void ApplyVelocity(SceneView<Velocity, Transform>& sceneView);

void PrintPhysicsStuff(SceneView<Velocity, Transform, Name>& sceneView);