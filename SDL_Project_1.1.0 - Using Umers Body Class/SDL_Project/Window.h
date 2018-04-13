#ifndef WINDOW_H
#define WINDOW_H

#include "Vector.h";
using namespace MATH;

class Window {
private:
	struct SDL_Window* window;   
	struct SDL_Surface* screenSurface;
	Vec3 windowSize;
	Vec3 windowPos;
	
public:
	Window(int width_, int height_ );
	~Window();
	bool OnCreate();
	void OnDestroy();
	SDL_Window* GetSDL_Window();
};
#endif

