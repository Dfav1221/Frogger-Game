#ifndef Moving_objects_h
#define Moving_objects_h

#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>

#include "Sdl.h"
#include "Player.h"
#include "Draw_functions.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	540  

using namespace std;

class Moving_object {
private:
	SDL_Rect texture, position;
	SDL_Surface* sprite;
	bool swim;
	bool danger;
	bool turtle;
	int row;
	int group;
	double speed;
	int direction;
	char type[3];
	int objects_in_row = 0;

public:
	Moving_object();

	void spawn(int pos_x, int pos_y);
	void move(double time);
	void render(SDL_Surface* screen);
	
	void get_info(char type[], int config[]);

	int show_pos_x();
	int show_row();
	int show_group();
	int show_swim();
	double show_speed();

	bool if_turtle();

	SDL_Surface* show_Surface();
};

#endif
