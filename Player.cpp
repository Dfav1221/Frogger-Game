#include "Player.h"


Player::Player() {
	sprite = SDL_LoadBMP("assets/frog_f1.bmp");
	lifes_display = SDL_LoadBMP("assets/frog_f1.bmp");
	coordinates.x = (SCREEN_WIDTH - 400) / 2 + 200;
	coordinates.y = SCREEN_HEIGHT - 82;
	coordinates.h = 16;
	coordinates.w = 20;
	score = 0;
	lifes = 5;
	row = 11;
	max_row = 11;
	for(int i = 0;i < 5;i++)
		end_point[i] = 0;
}

void Player::move(int k) {
	switch (k) {
	case(1): coordinates.y += 32;  row++;  break;
	case(2): coordinates.y -= 32;  row--;
		if (max_row > row) {
			score += 10;
			max_row--;
		}
		break;
	case(3): coordinates.x += 32;  break;
	case(4): coordinates.x -= 32;  break;
	}
}
void Player::swim(double q) { coordinates.x += q; }

void Player::render(SDL_Surface* screen) { DrawSurface(screen, sprite, coordinates.x, coordinates.y); }

void Player::decrese_lifes() { this->lifes -= 1; }
void Player::add_life() { this->lifes += 1; }

void Player::drawfrogs(SDL_Surface* screen) {
	for (int i = 0; i < 5; i++) {
		if (end_point[i] == 1)
			DrawSurface(screen, lifes_display, 230 + 85 * i, 60);
		//DrawRectangle(screen, 212 + 85 * i, 60, 32, 32, 0, 0);
	}
}

bool Player::end_points(SDL_Surface* screen) {
	int x = coordinates.x;
	for (int i = 0; i < 5; i++) {
		if (!end_point[i] && x >= 212+85*i && x <= 247+85*i) { end_point[i] = 1; return 1; }
	}
	return 0;
}


bool Player::check_colision(int x, SDL_Surface* entity,bool t,int group) {
	if (abs(coordinates.x - x) < ((sprite->w + entity->w) / 2)-5) {
		return 1;
	}
}

bool Player::exceptions() {
	if (coordinates.x <= 200 || coordinates.x >= 600 || row > 11) {
		//wyjscie poza ekran w poziomie i pionie
		this->died();
		return 1;
	}
	return 0;
}

void Player::died() {
	coordinates.x = (SCREEN_WIDTH - 400) / 2 + 200;
	coordinates.y = SCREEN_HEIGHT - 82;
	row = 11;
	lifes -= 1;
}
void Player::increment_score(int add) { score += add; }


int Player::show_num_of_lifes() { return lifes; }

int Player::show_row() { return row; }

void Player::show_lifes(SDL_Surface* screen) {
	int step = 32;
	for (int i = 0; i < lifes; i++) {
		DrawSurface(screen, lifes_display, life_x + step*i, life_y);
	}
}

void Player::show_score(SDL_Surface* screen, SDL_Surface* charset) {
	char text[50];
	sprintf(text, "%d", score);
	DrawString(screen, 205, 10, text, charset);
}

bool Player::end() {
	int q = 0;
	for (int i = 0; i < 5; i++) {
		if (!end_point[i])
			q++;
		return q > 4;
	}
}