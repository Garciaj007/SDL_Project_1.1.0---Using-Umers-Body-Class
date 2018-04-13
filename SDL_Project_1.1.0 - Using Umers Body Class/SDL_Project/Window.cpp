#include "Window.h"
#include <SDL.h>
#include <iostream> /// Umer likes this over printf() - too bad

//Window Constructor
Window::Window(int width_, int height_){
	screenSurface = nullptr;
	window = nullptr;
	windowSize.Load(width_, height_, 0.0f);
	windowPos.Load(100.0f, 50.0f, 0.0f);
}

//Creates a Window
bool Window::OnCreate(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //if SDL_Init cant create an instance, return false;
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("My First Window", windowPos.x, windowPos.y, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
	if (window == nullptr) { // if you cant create a window return false;
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == nullptr) { //if Cant create
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Window::OnDestroy(){
	/// Kill the surface first
	if (screenSurface) {
		SDL_FreeSurface(screenSurface);
	}

	/// Now kill the window
	if (window){
		SDL_DestroyWindow(window);
	}
	
	///Exit the SDL subsystems
	SDL_Quit();
}

Window::~Window(){}

SDL_Window* Window::GetSDL_Window() {
	return window;
}