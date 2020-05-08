#ifndef Player_h
#define Player_h

#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>

#include "Sdl.h"
#include "Moving_Objects.h"
#include "Draw_functions.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	540  

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

class Player {
private:
	SDL_Surface* lifes_display;
	SDL_Surface* sprite;
	SDL_Rect coordinates;
	int const life_x = 220, life_y = SCREEN_HEIGHT-40;
	int lifes;
	int max_row;
	int points;
	int score;
	int row;
	bool end_point[5];

public:

	Player();

	void move(int k);
	void swim(double q);
	void render(SDL_Surface* screen);
	void died();

	bool check_colision(int x, SDL_Surface* entity,bool t ,int group);
	void decrese_lifes();
	bool end_points(SDL_Surface* screen);
	void increment_score(int add);
	void drawfrogs(SDL_Surface* screen);
	bool exceptions();
	void add_life();
	bool end();

	int show_row();
	void show_lifes(SDL_Surface* screen);
	int show_num_of_lifes();
	void show_score(SDL_Surface* screen, SDL_Surface* charset);
};


#endif
