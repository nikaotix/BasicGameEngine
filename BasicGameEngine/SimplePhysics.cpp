#include <iostream>

// TODO: split out the SDL-specific time stuff
#include <SDL.h>
#include "SimplePhysics.h"


// TODO: figure out world units (how many pixels is 1 meter?
const int pixelsPerMeter = 10;
const float gravityConst = 9.8f;

inline float getTickTime(Scene& scene)
{
	return float(scene.getDeltaPerfCounter()) / float(SDL_GetPerformanceFrequency());
}

void ApplyGravity(Scene& scene)
{
	float tickTime = getTickTime(scene);
	auto sceneView = SceneView<Velocity>(scene);
	auto sceneIter = sceneView.begin();
	while (sceneIter != sceneView.end())
	{
		Velocity* vel = scene.Get<Velocity>(*sceneIter);
		vel->y += (tickTime * gravityConst * pixelsPerMeter);
		++sceneIter;
	}
}

void ApplyVelocity(Scene& scene)
{

	float tickTime = getTickTime(scene);
	auto sceneView = SceneView< Transform, Velocity>(scene);
	auto sceneIter = sceneView.begin();
	while (sceneIter != sceneView.end())
	{
		Velocity* vel = scene.Get<Velocity>(*sceneIter);
		Transform* tf = scene.Get<Transform>(*sceneIter);
		tf->x += vel->x * tickTime;
		tf->y += vel->y * tickTime;
		tf->z += vel->z * tickTime;
		++sceneIter;
	}
}

void PrintPhysicsStuff(Scene& scene)
{
	std::cout << "TickTime: " << getTickTime(scene) << std::endl;
	auto sceneView = SceneView<Name, Transform, Velocity>(scene);
	auto sceneIter = sceneView.begin();
	while (sceneIter != sceneView.end())
	{
		Velocity* vel = scene.Get<Velocity>(*sceneIter);
		Transform* tf = scene.Get<Transform>(*sceneIter);
		Name* name = scene.Get<Name>(*sceneIter);
		std::cout << "Name: " << name->name << std::endl;
		std::cout << "Velocity: " << vel->x << " " << vel->y << " " << vel->z << std::endl;
		std::cout << "Transform: " << tf->x << " " << tf->y << " " << tf->z << std::endl;
		++sceneIter;
	}
}
