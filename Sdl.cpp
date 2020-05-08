#include "Sdl.h"


Sdl::~Sdl() {
	SDL_FreeSurface(this->charset);
	SDL_FreeSurface(this->screen);
	SDL_DestroyTexture(this->scrtex);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	SDL_Quit();
}

Sdl::Sdl() {

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_RENDERER_PRESENTVSYNC,
		&window, &renderer);


	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_SetWindowTitle(window, "Frogger");
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	};
	SDL_SetColorKey(charset, true, 0x000000);

	granatowy = SDL_MapRGB(screen->format, 0x12, 0x36, 0x94);
	zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	time_color = zielony;
}

void Sdl::render() {
	SDL_UpdateTexture(this->scrtex, NULL, this->screen->pixels, this->screen->pitch);
			//SDL_RenderClear(this->renderer);
	SDL_RenderCopy(this->renderer, this->scrtex, NULL, NULL);
	SDL_RenderPresent(this->renderer);
}
