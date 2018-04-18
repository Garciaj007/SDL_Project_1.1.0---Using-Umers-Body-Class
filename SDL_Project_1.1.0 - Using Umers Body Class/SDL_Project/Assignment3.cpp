#include "Assignment3.h"
#include "Body.h"
#include <SDL.h>
#include "VMath.h"
#include <iostream>
Assignment3::Assignment3(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;

	for each (Body* body in bodies)
	{
		body = nullptr;
	}
}

bool Assignment3::OnCreate() {
	int w, h;
	Vec3 ScreenSize;

	SDL_GetWindowSize(window, &w, &h);
	ScreenSize = Vec3(28.5f, 16.0f, 0.0f);
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 30.0f, 0.0f, 15.0f, 0.0f, 1.0f);


	//if the sun weighed 1000000 units, our planets would be 3.00300 units, or moon, weights 0.0370741 and small objects 0.0002625
	bodies[0] = new Body("Sun", "Sun.bmp", 1000000.0f, Vec3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[1] = new Body("Planet1", "Mars.bmp", 3.00300f, Vec3(ScreenSize.x/2 - 4.0f, ScreenSize.y / 2, 0.0f), Vec3(0.0f, -500.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[2] = new Body("Planet2", "Mars.bmp", 3.00300f, Vec3(ScreenSize.x / 2 + 4.0f, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 500.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[3] = new Body("Small moon1", "Moon.bmp", 0.037074f, Vec3(2.0f, 4.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[4] = new Body("Small moon2", "Moon.bmp", 0.037074f, Vec3(ScreenSize.x + 3.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[5] = new Body("Smallobject1","Asteroid.bmp", 0.0002625f, Vec3(5.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[6] = new Body("Smallobject2","Asteroid.bmp", 0.0002625f, Vec3(6.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	bodies[7] = new Body("Smallobject3","Asteroid.bmp", 0.0002625f, Vec3(7.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < NUM_BODIES; i++) {
		imagesSize[i] = Vec3(bodies[i]->getImage()->w, bodies[i]->getImage()->h, 0.0f);
		//imagesSize[i] = MMath::unOrtho(projectionMatrix) * imagesSize[i];
		imagesSize[i].print();
	}

	if (bodies[0] == nullptr) {
		return false;
	}
	return true;
}

void Assignment3::OnDestroy() {
	for each(Body* body in bodies) {
		if (body) {
			delete body;
			body = nullptr;
		}
	}
}

void Assignment3::Update(const float time) {

	if (btnPressed) {
		elapsedTime += time;

		Gravity();

		for each(Body* body in bodies) {
			if (body) body->Update(time);
		}
		frameCount++;
	}
}

void Assignment3::Gravity() {
	/*
	//bodies[1] is being attracted;
	Vec3 a, b;
	float a_Mag, b_Mag, gravityA, gravityB;

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
	*/

	for each(Body* body in bodies) {
		if (body->name != "Sun") {
			Vec3 a;
			float a_Mag, gravityA;

			a = bodies[0]->pos - body->pos;

			a_Mag = VMath::mag(a);
			a = VMath::normalize(a);

			gravityA = (bodies[0]->mass * body->mass) / pow(a_Mag, 2);
			a = a* gravityA;

			body->ApplyForce(a);
		}
	}
	/*
	Vec3 a;
	float a_Mag, gravityA;

	a = bodies[0]->pos - bodies[1]->pos; //A^Vector = otherBody.position - this.position

	a_Mag = VMath::mag(a); //the distance between object = |(A^Vector)|;
	a = VMath::normalize(a); // the direction = ^(A^Vector)

	gravityA = (bodies[0]->mass * bodies[1]->mass) / pow(a_Mag, 2); // the magnitude of gravity = otherbody.mass - thisbody.mass / |A|^2 
	a = a * gravityA; //the final force is the direction * the magnitude of the force of gravity

	bodies[1]->ApplyForce(a);
	*/
}

void Assignment3::Render() {
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

void Assignment3::HandleEvents(const SDL_Event &e) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.scancode != SDL_SCANCODE_F1 && e.key.keysym.scancode != SDL_SCANCODE_F2 && e.key.keysym.scancode != SDL_SCANCODE_F3) {
		btnPressed = true;
	}
	else if (e.type == SDL_KEYUP) {
		printf("Key Was Released \n");
	}
}