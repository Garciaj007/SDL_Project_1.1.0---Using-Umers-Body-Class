#ifndef CollisionsTest_H
#define CollisionsTest_H

#include "MMath.h"
#include "Scene.h"
#include <SDL.h>

#define NUM_BODIES 2

using namespace MATH;
class CollisionsTest : public Scene {
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
	CollisionsTest(SDL_Window* sdlWindow);
	//float RandomInRange(float width, float height);
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event &e);
};

#endif