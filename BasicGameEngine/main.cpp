#include <SDL.h>

#include "Scene.h"
#include "SimplePhysics.h"
#include "SDLAudioServer.h"
#include "SDLTwoDRenderer.h"


size_t s_componentCounter = 0;

// super simple code to exercise simple physics + ECS
int main(int argc, char** argv)
{

	TwoDRenderer* twodrenderer = new SDLTwoDRenderer("Test window", 100, 100, 640, 480, 0);
	AudioServer* audioserver = new SDLAudioServer(); // Need to build the audio update stuff first.
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
	myScene.Assign<Sound>(myEntity);
	myScene.Assign<Music>(myEntity);

	auto* tf = myScene.Get<Transform>(myEntity);
	auto* vel = myScene.Get<Velocity>(myEntity);
	auto* name = myScene.Get<Name>(myEntity);
	auto* sprite = myScene.Get<Sprite>(myEntity);
	auto* sound = myScene.Get<Sound>(myEntity);
	auto* music = myScene.Get<Music>(myEntity);
	name->name = "Test Entity";
	vel->x = 0;
	vel->y = -10;
	vel->z = 0;
	tf->x = 100;
	tf->y = 115;
	tf->z = 0;
	sprite->frame = 0;
	sprite->id = "ball";
	sound->playNow = true;
	sound->soundID = "boing";
	music->playNow = true;
	music->MusicID = "Childs Nightmare";

	twodrenderer->LoadSprite(sprite->id);

	myScene.Init(SDL_GetPerformanceCounter());
	bool quit = false;
	while (!quit) {
		// Handle events
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		// update timebase (and eventually run time systems or whatever)
		myScene.Update(SDL_GetPerformanceCounter());

		// Run systems
		ApplyGravity(myScene);
		ApplyVelocity(myScene);
		PrintPhysicsStuff(myScene);

		// Render scene with camera

		audioserver->UpdateSounds(myScene);
		audioserver->UpdateMusic(myScene);
		twodrenderer->RenderScene(myScene, twodcamera);

	};
	SDL_Quit();
	exit(0);
}