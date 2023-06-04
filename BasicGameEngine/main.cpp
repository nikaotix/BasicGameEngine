#include <SDL.h>

#include "Scene.h"
#include "SimplePhysics.h"
#include "SDLAudioServer.h"
#include "SDLTwoDRenderer.h"

size_t s_componentCounter = 0;

// super simple code to exercise simple physics + ECS
int main(int argc, char** argv)
{

	TwoDRenderer* twodrenderer = new SDLTwoDRenderer("Test window", 0, 0, 640, 480, 0);
	//AudioServer* audioserver = new SDLAudioServer(); // Need to build the audio update stuff first.
	TwoDCamera twodcamera;
	twodcamera.height = 480;
	twodcamera.width = 640;
	twodcamera.x = 0;
	twodcamera.y = 0;

	Scene myScene;

	EntityID myEntity = myScene.NewEntity();
	myScene.Assign<Name>(myEntity);
	myScene.Assign<Transform>(myEntity);
	myScene.Assign<Velocity>(myEntity);
	myScene.Assign<Sprite>(myEntity);

	auto* tf = myScene.Get<Transform>(myEntity);
	auto* vel = myScene.Get<Velocity>(myEntity);
	auto* name = myScene.Get<Name>(myEntity);
	auto* sprite = myScene.Get<Sprite>(myEntity);
	name->name = "Test Entity";
	vel->x = 0;
	vel->y = 10;
	vel->z = 0;
	tf->x = 100;
	tf->y = 115;
	tf->z = 0;
	sprite->frame = 0;
	sprite->id = "ball";

	twodrenderer->LoadSprite(sprite->id);


	for (int i = 0; i < 10; i++) {
		ApplyGravity(myScene);
		ApplyVelocity(myScene);
		PrintPhysicsStuff(myScene);
		twodrenderer->RenderScene(myScene, twodcamera);
	}

	while (1) {};
	return 0;
}