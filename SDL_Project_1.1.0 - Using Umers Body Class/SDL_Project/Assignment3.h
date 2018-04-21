#ifndef Assignment3_H
#define Assignment3_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>

#define NUM_BODIES 100

using namespace MATH;
class Assignment3 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	Matrix4 ipm;
	Vec3 imagesSize[NUM_BODIES];
	class Body* bodies[NUM_BODIES];
	float elapsedTime;
	unsigned long frameCount;
	bool btnPressed = false;
public:
	Assignment3(SDL_Window* sdlWindow);
	//float RandomInRange(float width, float height);
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Gravity();
	void AGravity(Body* bodies[], int length);
	void Render();
	void HandleEvents(const SDL_Event &e);
};

#endif