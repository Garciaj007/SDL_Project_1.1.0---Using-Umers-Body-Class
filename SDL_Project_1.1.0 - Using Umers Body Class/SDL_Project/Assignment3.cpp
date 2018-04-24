#include "Assignment3.h"
#include "Body.h"
#include <SDL.h>
#include "VMath.h"
#include <iostream>
#include "Collider.h"


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
	SDL_GetWindowSize(window, &w, &h);
	float aspectRatio = (float)h / (float)w;
	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 60.0f, 0.0f * aspectRatio, 60.0f *aspectRatio , 0.0f, 1.0f);
	ipm = MMath::inverse(projectionMatrix);
	Vec3 ScreenSize(60.0f, 60 * aspectRatio, 0.0f);

	//if the sun weighed 1000000 units, our planets would be 3.00300 units, or moon, weights 0.0370741 and small objects 0.0002625
	bodies[0] = new Body("Sun", "SunBlue.bmp", 1000000.0f, Vec3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 0.00f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	/*for (int i = 1; i < NUM_BODIES; i++) {
		bodies[i] = new Body("Smallobject3" + i, "Moon.bmp", 0.0002625f, Vec3((float)i + 2, ScreenSize.y - ((float)i + 2), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}*/
	/// for 1 < i < 10 
	for (int i = 0; i < 20; i++) {
		bodies[i + 1] = new Body("Mars.bmp", 3.00300f, Vec3(ScreenSize.x / 2 - ((float) i * 4) - 4.0f, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 600.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}
	/// for 10 < i < 20
	for (int i = 0; i < 20; i++) {
		bodies[i + 20] = new Body("Mars.bmp", 3.00300f, Vec3(ScreenSize.x / 2 + ((float) i * 4) + 4.0f, ScreenSize.y / 2, 0.0f), Vec3(0.0f, -600.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}
	///for 20 < i < 30
	for (int i = 0; i < 20; i++) {
		bodies[i + 40] = new Body("Moon.bmp", 0.037074f, Vec3(ScreenSize.x / 2, ScreenSize.y / 2 - (float) i - 4, 0.0f), Vec3(500.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}
	/// for 30 < i < 40
	for (int i = 0; i < 20; i++) {
		bodies[i + 60] = new Body("Moon.bmp", 0.037074f, Vec3(ScreenSize.x / 2, ScreenSize.y / 2 + (float) i + 4, 0.0f), Vec3(-500.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}
	for (int i = 80; i < NUM_BODIES; i++) {
		bodies[i] = new Body("Asteroid.bmp", 0.0002625f, Vec3(i - 80, 1.5f, 0.0f), Vec3(500.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	}


	//bodies[1] = new Body("Planet1", "Mars.bmp", 3.00300f, Vec3(ScreenSize.x/2 - 4.0f, ScreenSize.y / 2, 0.0f), Vec3(0.0f, -500.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	//bodies[2] = new Body("Planet2", "Mars.bmp", 3.00300f, Vec3(ScreenSize.x / 2 + 4.0f, ScreenSize.y / 2, 0.0f), Vec3(0.0f, 500.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	//bodies[3] = new Body("Small moon1", "Moon.bmp", 0.037074f, Vec3(2.0f, 4.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	//bodies[4] = new Body("Small moon2", "Moon.bmp", 0.037074f, Vec3(ScreenSize.x + 3.0f, 10.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	//bodies[5] = new Body("Smallobject1","Asteroid.bmp", 0.0002625f, Vec3(5.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	//bodies[6] = new Body("Smallobject2","Asteroid.bmp", 0.0002625f, Vec3(6.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
	//bodies[7] = new Body("Smallobject3","Asteroid.bmp", 0.0002625f, Vec3(7.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < NUM_BODIES; i++) {
		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 lowerRight(bodies[i]->getImage()->w, bodies[i]->getImage()->h, 0.0f);

		upperLeft = ipm * upperLeft;
		lowerRight = ipm * lowerRight;

		float radius = (lowerRight.x - upperLeft.x) / 2.0f;

		bodies[i]->radius = radius;
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

		Gravity(bodies, NUM_BODIES);

		for (int i = 0; i < NUM_BODIES; i++) {
			for (int j = 0; j < NUM_BODIES; j++) {
				if (i != j) {
					if (Collider::Collided(*bodies[i], *bodies[j])) {
						Collider::HandleCollision(*bodies[i], *bodies[j]);
					}
				}
			}
		}

		for each(Body* body in bodies) {
			if (body) body->Update(time);
		}
		frameCount++;
	}
}

void Assignment3::Gravity(Body* objects[], int num_Objects) {
	for (int j = 0; j < num_Objects; j++) {
		Vec3* force = new Vec3[num_Objects];
		for (int i = 0; i < num_Objects; i++) {
			if (i != j) { 
				Vec3 direction = bodies[i]->pos - bodies[j]->pos;

				float mag = pow(direction.x, 2) + pow(direction.y, 2);
				Vec3 normal = VMath::normalize(direction);

				float gravityForce = (bodies[i]->mass * bodies[j]->mass) / mag;
				force[i] = direction * gravityForce;

				force[0] += force[i];
			}
		}
		objects[j]->ApplyForce(force[0]);
	}
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
		imageRectangle.x = screenCoords.x - body->getImage()->w / 2.0f; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y - body->getImage()->w / 2.0f; /// implicit type conversions BAD - probably causes a compiler warning

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