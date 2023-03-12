#pragma once
#include "Scene.h"

/// <summary>
/// SimplePhysics contains a few basic systems used to test the ECS.
/// TODO - decide how we want to parallelize system execution.
/// probably combination of systems that can run in parallel (sound updates + physics are separate)
/// with systems that run themselves in parallel (physics system updates transforms in parallel).
/// </summary>

void ApplyGravity(Scene& scene);

void ApplyVelocity(Scene& scene);

void PrintPhysicsStuff(Scene& scene);