#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Assignment1.h"
#include <iostream>

GameManager::GameManager() {
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 920; //Const screen Width
	const int SCREEN_HEIGHT = 640; //Const screen Height

	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);//Creates a window and assigns it to a pointer
	if (ptr == nullptr) { //if there is no Window Created, call OnDestroyed & return false
		printf("Destroying...");
		OnDestroy();
		return false;
	}

	if (ptr->OnCreate() == false) { //go to the window class and call on create, if it returns false, then call OnDestroy, and return false
		OnDestroy();
		return false;
	}

	timer = new Timer(); //create a new timer and assign it to a ptr
	if (timer == nullptr) { // if timer wasnt created, OnDestroyed, return false
		OnDestroy();
		return false;
	}

	currentScene = new Assignment1(ptr->GetSDL_Window());//create a new scene 
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	return true;
}

/// Here's the whole game
void GameManager::Run() {
	timer->Start();
	while (isRunning) {
		if (SDL_PollEvent(&event) != 0) {

			switch (event.type) {
			case SDL_QUIT: isRunning = false;
				break;
			}
			currentScene->HandleEvents(event);
		}

		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){//Destroys and pointers that were created
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}