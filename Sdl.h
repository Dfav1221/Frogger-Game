#ifndef Sdl_h
#define Sdl_h

#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>

#include "Player.h"
#include "Draw_functions.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

class Sdl {
public:
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int rc;
	int granatowy;
	int zielony;
	int czerwony;
	int niebieski;
	int czarny;
	int time_color;

	Sdl();
	~Sdl();
	void render();
};

#endif

