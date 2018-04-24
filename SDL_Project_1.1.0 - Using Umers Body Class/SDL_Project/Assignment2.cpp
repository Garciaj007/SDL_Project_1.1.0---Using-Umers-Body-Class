#include "Assignment2.h"
#include "Body.h"
#include <SDL.h>
#include "VMath.h"
#include <iostream>
#include "Collider.h"
Assignment2::Assignment2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;
	for each (Body* body in bodies)
	{
		body = nullptr;
	}
}

bool Assignment2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Vec3 ScreenSize = Vec3(60.0, 60.0, 0.0f);
	ScreenSize.print();
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 60.0f, 0.0f, 60.0f, 0.0f, 1.0f);
	Matrix4 ipm = MMath::inverse(projectionMatrix);

	bodies[0] = new Body("Sun.bmp", 1500.0f, Vec3(ScreenSize.x / 4, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[1] = new Body("Mars.bmp", 0.1f, Vec3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f), Vec3(7.0f, -14.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[2] = new Body("SunBlue.bmp", 2000.0f, Vec3(ScreenSize.x / 2 + ScreenSize.x / 4, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

	for each (Body* body in bodies)
	{
		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 lowerRight(body->getImage()->w, body->getImage()->h, 0.0f);

		upperLeft = ipm * upperLeft;
		lowerRight = ipm * upperLeft;

		float radius = (lowerRight.x - upperLeft.x) / 2.0f;
		body->radius = radius;

	}
	

	if (bodies[0] == nullptr) {
		return false;
	}
	return true;
}

void Assignment2::OnDestroy() {
	for each(Body* body in bodies) {
		if (body) {
			delete body;
			body = nullptr;
		}
	}
}

void Assignment2::Update(const float time) {
	Vec3 a, b;
	float a_Mag, b_Mag, gravityA, gravityB;

	if (btnPressed) {
		elapsedTime += time;
		for (int i = 0; i < NUM_BODIES; i++) {
			for (int j = 0; j < NUM_BODIES; j++) {
				if (i != j) {
					if (Collider::Collided(*bodies[i], *bodies[j])) {
						Collider::HandleCollision(*bodies[i], *bodies[j]);
					}
				}
			}
		}

		a = bodies[0]->pos - bodies[1]->pos;
		b = bodies[2]->pos - bodies[1]->pos;

		a_Mag = VMath::mag(a);
		b_Mag = VMath::mag(b);

		a = VMath::normalize(a);
		b = VMath::normalize(b);

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

void Assignment2::Render() {
	SDL_Rect imageRectangle;
	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));//clears the screen


	for each (Body* body in bodies)
	{
		Vec3 screenCoords = projectionMatrix * body->pos;
		imageRectangle.h = body->getImage()->h;
		imageRectangle.w = body->getImage()->w;
		imageRectangle.x = screenCoords.x - body->getImage()->w / 2.0f;; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y - body->getImage()->h / 2.0f;; /// implicit type conversions BAD - probably causes a compiler warning

		SDL_BlitSurface(body->getImage(), nullptr, screenSurface, &imageRectangle);
	}

	SDL_UpdateWindowSurface(window);
}

void Assignment2::HandleEvents(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode != SDL_SCANCODE_F1 && e.key.keysym.scancode != SDL_SCANCODE_F2 && e.key.keysym.scancode != SDL_SCANCODE_F3) {
		btnPressed = true;
	}
	else if (e.type == SDL_KEYUP) {
		printf("Key Was Released \n");
	}
}