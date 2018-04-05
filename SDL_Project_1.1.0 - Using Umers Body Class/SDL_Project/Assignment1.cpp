#include "Assignment1.h"
#include "Body.h"
#include <SDL.h>
#include "VMath.h"
#include <iostream>
Assignment1::Assignment1(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;
	for each (Body* body in bodies)
	{
		body = nullptr;
	}
}

Assignment1::~Assignment1() {
}

bool Assignment1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);

	/*for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = new Body("jetskiSmall.bmp", 2.0f, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.00f, 0.0f));
	}*/

	bodies[0] = new Body("Sun.bmp", 150.0f, Vec3(5.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[1] = new Body("Mars.bmp", 1.0f, Vec3(16.0f, 9.0f, 0.0f), Vec3(6.0f, -3.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[2] = new Body("SunBlue.bmp", 200.0f, Vec3(20.0f, 13.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	
	if (bodies[0] == nullptr) {
		return false;
	}
	return true;
}

void Assignment1::OnDestroy() {
	for each(Body* body in bodies) {
		if (body) {
			delete body;
			body = nullptr;
		}
	}
}

void Assignment1::Update(const float time) {
	Vec3 a, b;
	float a_Mag, b_Mag, gravityA, gravityB;

	VMath math;

	if (btnPressed) {
		elapsedTime += time;

		a = bodies[0]->pos - bodies[1]->pos;
		b = bodies[2]->pos - bodies[1]->pos;

		a_Mag = math.mag(a);
		b_Mag = math.mag(b);

		a = math.normalize(a);
		b = math.normalize(b);

		gravityA = (bodies[0]->mass*bodies[1]->mass) / (a_Mag * a_Mag);
		gravityB = (bodies[2]->mass*bodies[1]->mass) / (b_Mag * b_Mag);
		
		a = a * gravityA;
		b = b * gravityB;

		a = a + b;

		bodies[1]->ApplyForce(a);

		for each(Body* body in bodies) {
			if (body) body->Update(time);
		}
		frameCount++;
	}
}

void Assignment1::Render() {
	SDL_Rect imageRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));//clears the screen


	for each (Body* body in bodies)
	{
		Vec3 screenCoords = projectionMatrix * body->pos;
		imageRectangle.h = body->getImage()->h;
		imageRectangle.w = body->getImage()->w;
		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

		SDL_BlitSurface(body->getImage(), nullptr, screenSurface, &imageRectangle);
	}

	SDL_UpdateWindowSurface(window);
}

void Assignment1::HandleEvents(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN) {
		btnPressed = true;
	}
	else if (e.type == SDL_KEYUP) {
		printf("Key Was Released \n");
	}
}