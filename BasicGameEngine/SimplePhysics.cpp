#include <iostream>

#include "SimplePhysics.h"

// replace tickTime with an actual delta time for proper physics stuff.
const float tickTime = 0.16f;
const float gravityConst = 9.8f;

void ApplyGravity(SceneView<Velocity>& sceneView)
{
	auto& scene = sceneView.pScene;
	auto sceneIter = sceneView.begin();
	while (sceneIter != sceneView.end())
	{
		Velocity* vel = scene->Get<Velocity>(*sceneIter);
		vel->y -= (tickTime * gravityConst);
		++sceneIter;
	}
}

void ApplyVelocity(SceneView<Velocity, Transform>& sceneView)
{
	auto& scene = sceneView.pScene;
	auto sceneIter = sceneView.begin();
	while (sceneIter != sceneView.end())
	{
		Velocity* vel = scene->Get<Velocity>(*sceneIter);
		Transform* tf = scene->Get<Transform>(*sceneIter);
		tf->x += vel->x;
		tf->y += vel->y;
		tf->z += vel->z;
		++sceneIter;
	}
}

void PrintPhysicsStuff(SceneView<Velocity, Transform, Name>& sceneView)
{
	auto& scene = sceneView.pScene;
	auto sceneIter = sceneView.begin();
	while (sceneIter != sceneView.end())
	{
		Velocity* vel = scene->Get<Velocity>(*sceneIter);
		Transform* tf = scene->Get<Transform>(*sceneIter);
		Name* name = scene->Get<Name>(*sceneIter);
		std::cout << "Name: " << name->name << std::endl;
		std::cout << "Velocity: " << vel->x << " " << vel->y << " " << vel->z << std::endl;
		std::cout << "Transform: " << tf->x << " " << tf->y << " " << tf->z << std::endl;
		++sceneIter;
	}
}
