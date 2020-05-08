#include "Draw_functions.h"

SDL_Surface* purple, * grass;

void Load_Surfaces() {
	//Surface->purple
	purple = SDL_LoadBMP("assets/purple.bmp");
	//Surface->grass
	grass = SDL_LoadBMP("assets/river_side.bmp");
}

void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt �rodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	SDL_Surface a;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// rysowanie linii o d�ugo�ci l w pionie (gdy dx = 0, dy = 1) 
// b�d� poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// rysowanie prostok�ta o d�ugo�ci bok�w l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void DrawMap(SDL_Surface* screen, int czarny) {
	SDL_Rect d, road;
	road.y = 440;
	road.x = 0;
	road.h = 160;
	road.w = 399;
	d.x = 399;
	d.y = 60;
	d.w = 399;
	d.h = 100;
	DrawSurface(screen, grass, d.x, d.y);
	//SDL_BlitSurface(assets, &grass, screen, &d);
	d.y += 124 + grass->h;
	d.h = purple->h;
	DrawSurface(screen, purple, d.x, d.y);
	//SDL_BlitSurface(assets, &purple, screen, &d);
	d.y += purple->h;
	d.h = road.h;
	DrawRectangle(screen, 200, 280, 399, 160, czarny, czarny);
	d.h += purple->h;
	d.y += 160;
	//SDL_BlitSurface(assets, &purple, screen, &d);
	DrawSurface(screen, purple, d.x, d.y);
}


