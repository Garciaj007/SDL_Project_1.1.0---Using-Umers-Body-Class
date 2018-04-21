#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "SDL.h"
#include <string>
using namespace MATH; 

class Body {
public:
	std::string name;
	float radius;
	Vec3 pos;
	Vec3 vel;
	float mass;
private:
	Vec3 accel;
	SDL_Surface *bodyImage;
	
public:
	bool gravity = false;
	Body(char* imageName ,float mass_, Vec3 pos_, Vec3 vel_, Vec3 accel_);
	Body(std::string _name, char* imageName, float mass_, Vec3 pos_, Vec3 vel_, Vec3 accel_);

	void Update(const float deltaTime);
	void ApplyForce(Vec3 force);
	std::string ToString();

	/// Just a little helper function
	SDL_Surface* getImage();
};


#endif
