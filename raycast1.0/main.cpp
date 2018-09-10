#include "SDL.h"

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	int r, g, b;
	for (int i = 0; i < 200; i += 5)
	{
		r = 200 - i;
		g = 120 - i;
		b = 43 - i;
		if (r < 0) r = 0;
		if (g < 0) g = 0;
		if (b < 0) b = 0;
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_Rect rect_u = { 0, i, 600, 5 };
		SDL_Rect rect_l = { 0, 399 - i, 600, 5 };
		SDL_RenderFillRect(renderer, &rect_u);
		SDL_RenderFillRect(renderer, &rect_l);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect rect_m = { 0, 199, 600, 5 };
	SDL_RenderFillRect(renderer, &rect_m);
	SDL_RenderPresent(renderer);
	
	SDL_Delay(5000);

	return 0;
}

