#include "Scene.h"
#include "SimplePhysics.h"

size_t s_componentCounter = 0;

// super simple code to exercise simple physics + ECS
int main(int argc, char* argv)
{
	Scene myScene;
	EntityID myEntity = myScene.NewEntity();
	myScene.Assign<Name>(myEntity);
	myScene.Assign<Transform>(myEntity);
	myScene.Assign<Velocity>(myEntity);

	auto* tf = myScene.Get<Transform>(myEntity);
	auto* vel = myScene.Get<Velocity>(myEntity);
	auto* name = myScene.Get<Name>(myEntity);
	name->name = "Test Entity";
	vel->x = 0;
	vel->y = 10;
	vel->z = 0;
	tf->x = 0;
	tf->y = 15;
	tf->z = 0;



	for (int i = 0; i < 10; i++) {
		ApplyGravity(myScene);
		ApplyVelocity(myScene);
		PrintPhysicsStuff(myScene);
	}

	while (1) {};
}