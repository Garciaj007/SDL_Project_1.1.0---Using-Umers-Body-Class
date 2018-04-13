#include "Assignment1.h"
#include "Body.h"
#include <SDL.h>
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

	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[i] = new Body("jetskiSmall.bmp", 2.0f, Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.00f, 0.0f));
		bodies[i]->gravity = true;
	}

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
	if (btnPressed) {
		elapsedTime += time;

		if (frameCount == 1) {
			for each(Body* body in bodies) {
				body->ApplyForce(Vec3(1000.0f, 1000.0f, 0.0f));
			}
		}

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
	if (e.type == SDL_KEYDOWN  && e.key.keysym.scancode != SDL_SCANCODE_F1 && e.key.keysym.scancode != SDL_SCANCODE_F2) {
		btnPressed = true;
	}
	else if (e.type == SDL_KEYUP) {
		printf("Key Was Released \n");
	}
}