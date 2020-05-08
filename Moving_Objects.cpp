#include "Moving_Objects.h"


Moving_object::Moving_object() {
	sprite = NULL;
	swim = 0;
	danger = 0;
	turtle = 0;
	row = 0;
	group = 0;
	speed = 0;
	direction = 0;
	type[2] = '\n';
	objects_in_row = 0;
	texture = { 0,0,0,0 };
	position = { 0,0,0,0 };
}
void Moving_object::spawn(int pos_x, int pos_y) {
	//cout << type << " ";
	position.x = pos_x;
	position.y = pos_y;
	position.w = sprite->w;
	position.h = sprite->h;
}
void Moving_object::move(double time) {
	//cout << position.x << endl;
	//cout << time * (speed) * direction;
	if (direction == -1) {
		this->position.x += time * speed * (-5);
	}
	else {
		this->position.x += time * speed * 5 + 1;
	}
	//this->position.x += time * speed * 7 * direction;
	int tmp = position.x, w = SCREEN_WIDTH;
	if (position.x >= SCREEN_WIDTH) {
		position.x = 1;
	}
	if ((int)position.x <= 0)
		position.x = SCREEN_WIDTH - texture.w;
}
void Moving_object::render(SDL_Surface* screen) {
	DrawSurface(screen, sprite, position.x, position.y);
}

int Moving_object::show_row() { return row; }

int Moving_object::show_group() { return group; }

bool Moving_object::if_turtle() { return turtle; }

double Moving_object::show_speed() {
	if (direction == -1) {
		return speed * (-5);
	}
	else {
		return (speed * 10 + 1);
	}
}

int Moving_object::show_swim() { return swim; }

int Moving_object::show_pos_x() { return position.x; }

SDL_Surface* Moving_object::show_Surface() { return sprite; }

void Moving_object::get_info(char type[], int config[]) {
	this->type[0] = type[0];
	this->type[1] = type[1];
	this->type[2] = type[2];
	direction = config[0];
	speed = config[1];
	row = config[2];
	group = config[3];
	if (type[0] == 'T') {
		sprite = SDL_LoadBMP("assets/turtle.bmp");
		turtle = 1;
		danger = 0;
		swim = 1;
	}
	else if (type[0] == 'W') {
		swim = 1;
		danger = 0;
		turtle = 0;
		switch (type[1]) {
		case('1'):
			sprite = SDL_LoadBMP("assets/wood1.bmp");
			break;
		case('2'):
			sprite = SDL_LoadBMP("assets/wood2.bmp");
			break;
		case('3'):
			sprite = SDL_LoadBMP("assets/wood3.bmp");
			break;
		}
	}
	else if (type[0] == 'C') {
		danger = 1;
		swim = 0;
		turtle = 0;
		switch (type[1]) {
		case('B'):
			sprite = SDL_LoadBMP("assets/carbig.bmp");
			break;
		case('1'):
			sprite = SDL_LoadBMP("assets/car1.bmp");
			break;
		case('2'):
			sprite = SDL_LoadBMP("assets/car2.bmp");
			break;
		case('3'):
			sprite = SDL_LoadBMP("assets/car4.bmp");
			break;
		case('4'):
			sprite = SDL_LoadBMP("assets/car3.bmp");
			break;

		}
	}
}