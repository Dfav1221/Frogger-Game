#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>

#include "Sdl.h"
#include "Moving_Objects.h"
#include "Player.h"
#include "Draw_functions.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

using namespace std;

// main
#ifdef __cplusplus
extern "C"
#endif


void game(Sdl &sdl);

int main(int argc, char **argv) {

	bool quit = 0,play = 0;

	Load_Surfaces();
	
	Sdl sdl;
	char menu_textPlay[] = "Press P to Play";
	char menu_textScores[] = "Press H to go to High Scores";
	char menu_textQuit[] = "Press Q to Quit";

	while (!quit) {
		SDL_FillRect(sdl.screen, NULL, sdl.czarny);

		DrawString(sdl.screen, 350, 200, menu_textPlay, sdl.charset);
		DrawString(sdl.screen, 300, 232, menu_textScores, sdl.charset);
		DrawString(sdl.screen, 350, 264, menu_textQuit, sdl.charset);
		sdl.render();

		if (play) {
			play = 0;
			game(sdl);
		}

		while (SDL_PollEvent(&sdl.event)) {
			switch (sdl.event.type) {
			case SDL_KEYDOWN:
				if (sdl.event.key.keysym.sym == SDLK_ESCAPE) { quit = 1; }
				else if (sdl.event.key.keysym.sym == SDLK_p) play = 1;
				else if (sdl.event.key.keysym.sym == SDLK_q) { quit = 1; }
				else if (sdl.event.key.keysym.sym == SDLK_h)break; /*high_scores(sdl);*/
			case SDL_KEYUP:
				break;
			case SDL_QUIT:
				quit = 1;
				break;
			};
		};

	}
	return 0;
};


void game(Sdl &sdl) {

	int t1, t2, quit = 0, frames, rc,config[4],entity_number = 0,pause = 0;
	double delta , life_time = 50;
	char text[128],type[3];
	bool point = 0, colision = 0;

	Player frog;
	Moving_object field[100];
	FILE* Actual_level;
	Actual_level = fopen("level1.txt", "r");

	//-----------Wczytywanie ustawien poziomu z pliku-----------------------------------------
	while (fscanf(Actual_level, "%s", type) != EOF) {
		entity_number++;
		for (int i = 0; i < 4; i++) {
			fscanf(Actual_level, "%d", &config[i]);
		}
		if (type[0] == 'T') {
			for (int z = 0; z < config[3] - 1; z++) {
				field[entity_number - 1].get_info(type, config);
				entity_number = entity_number + 1;
			}
		}
		field[entity_number - 1].get_info(type, config);
	}

	///---------------------Spawnowanie obiektów--------------------
	int k = 0, spawn_x = 0, j = 0, step = 0, spawn_y = 100, p = 0;
	for (int i = 0; i <= 10; i++) {
		j = 0;
		if (i == 5) {
			i++;
			spawn_y += 32;
		}

		while (field[j + k].show_row() == i) { j++; }
		cout << endl;
		spawn_x = 0;
		int if_turtle = 0;
		if (field[k].if_turtle() == 1) {
			if_turtle = field[k].show_group();
			step = SCREEN_WIDTH / (j / if_turtle) - if_turtle * 32;
			for (int q = 0; q < j / if_turtle; q++) {
				for (int t = 0; t < if_turtle; t++) {
					field[q * if_turtle + t + k].spawn(spawn_x, spawn_y);
					spawn_x += 34;
				}
				p += if_turtle;
				spawn_x += step;
				spawn_x %= SCREEN_WIDTH;
			}
		}
		else {
			step = SCREEN_WIDTH / j;
			for (int q = 0; q < j; q++) {
				field[q + k].spawn(spawn_x, spawn_y);
				spawn_x += step;
				spawn_x %= (2 * SCREEN_WIDTH);
			}
		}
		k += j;
		spawn_y += 32;
	}



	t1 = SDL_GetTicks();

	while (!quit && frog.show_num_of_lifes() > 0) {

		t2 = SDL_GetTicks();

		delta = (t2 - t1) * 0.001;

		if (life_time <= 0) {
			//koniec czasu
			life_time = 50;
			frog.died();
			sdl.time_color = sdl.zielony;
		}
		t1 = t2;
		if (pause == 0) {

			//-----------Rysowanie mapy gry

			SDL_FillRect(sdl.screen, NULL, sdl.granatowy);
			DrawMap(sdl.screen, sdl.czarny);

			//-----------Rysowanie licznika czasu
			if (life_time <= 10)
				sdl.time_color = sdl.czerwony;
			DrawRectangle(sdl.screen, 395 + (50 - life_time) * 4, 485, life_time * 4, 30,
				sdl.time_color, sdl.time_color);
			life_time -= delta;

			//-----------Rysowanie poruszajacych sie obiektow i sprawdzanie kolizji 
			int lock = 0;
			int f = 0, l = 0, q = 0;
			while (field[f + 1].show_row() != frog.show_row() && f < entity_number - 1) f++;
			l = f;
			if (f != entity_number - 1) {
				while (field[l + 1].show_row() == frog.show_row() && l < entity_number - 1) l++;
				//cout << l << endl;

				for (; f <= l; f++) {
					//cout << f << endl;
					colision = frog.check_colision(field[f].show_pos_x(), field[f].show_Surface(),
						field[f].if_turtle(), field[f].show_group());
					//cout << colision<<endl;
					if (colision == 1 && field[f].show_row() == frog.show_row()) {
						if (field[f].show_swim() == 1 && lock != 1) {
							frog.swim(field[f].show_speed() * delta);
							lock = 1;
							break;
						}
						else {
							life_time = 50;
							sdl.time_color = sdl.zielony;
							frog.died();
						}
						q = 1;
					}

					colision = 0;
				}
				if (lock == 0 && frog.show_row() <= 4) {
					frog.died();
					life_time = 50;
					sdl.time_color = sdl.zielony;
				}
				lock = 0;
			}

			for (int i = 0; i < entity_number; i++) {
				field[i].move(delta);
				field[i].render(sdl.screen);
			}

			//-----------Rysowanie zaby ,wyniku oraz zyc
			frog.drawfrogs(sdl.screen);
			if (frog.show_row() == -1) {
				point = frog.end_points(sdl.screen);
				if (point == 1) {
					frog.increment_score(50 + life_time * 10);
					frog.add_life();
				}
				life_time = 50;
				sdl.time_color = sdl.zielony;
				frog.died();
			}
			else {
				if (frog.exceptions() == 0)
					frog.render(sdl.screen);
				else {
					life_time = 50;
					sdl.time_color = sdl.zielony;
				}

			}
			frog.show_lifes(sdl.screen);
			frog.show_score(sdl.screen, sdl.charset);
			if(frog.end())
				quit = 1;
			//-----------Rysowanie ramek po bokach
			DrawRectangle(sdl.screen, 0, 0, 200, SCREEN_HEIGHT, sdl.czarny, sdl.czarny);
			DrawRectangle(sdl.screen, 599, 0, 201, SCREEN_HEIGHT, sdl.czarny, sdl.czarny);
		}
		else {
			char P[] = "Pauza";
			DrawString(sdl.screen, 400, 200, P, sdl.charset);
		}

		sdl.render();

		while (SDL_PollEvent(&sdl.event)) {
			switch (sdl.event.type) {
			case SDL_KEYDOWN:
				if (sdl.event.key.keysym.sym == SDLK_ESCAPE) { quit = 1; pause = 0; }
				else if (sdl.event.key.keysym.sym == SDLK_UP) frog.move(2);
				else if (sdl.event.key.keysym.sym == SDLK_DOWN) frog.move(1);
				else if (sdl.event.key.keysym.sym == SDLK_LEFT) frog.move(4);
				else if (sdl.event.key.keysym.sym == SDLK_RIGHT) frog.move(3);
				else if (sdl.event.key.keysym.sym == SDLK_q) { quit = 1; }
				else if (sdl.event.key.keysym.sym == SDLK_p) {
					if (pause == 0)
						pause = 1;
					else pause = 0;
				}
				break;
			case SDL_KEYUP:
				break;
			case SDL_QUIT:
				pause = 0;
				quit = 1;
				break;
			};
		};
	}

	frog.~Player();
	field->~Moving_object();
}
