#ifndef Assignment1_H
#define Assignment1_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>

#define NUM_BODIES 2

using namespace MATH;
class Assignment1 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	class Body* bodies[NUM_BODIES];
	float elapsedTime;
	unsigned long frameCount;
	bool btnPressed = false;
public:
	Assignment1(SDL_Window* sdlWindow);
	~Assignment1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &e);
};

#endif