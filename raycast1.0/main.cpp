#include <chrono>
#include <vector>
#include "SDL.h"
#include "Windows.h"
using namespace std;

int mapW = 8;
int mapH = 8;
float posX = 3.0f;
float posY = 3.0f;
float theta = 0.0f;
float fov = 3.14159f / 4.0f;
float maxDist = 20.0f;
float walkSpeed = 5.0f;
bool game = true;

int main(int argc, char *argv[])
{
	//This block of code sets up an SDL window and does a test print of the color blue.
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	
	//This block sets up the map and several variables
	wstring map;
	map += L"########";
	map += L"#.#....#";
	map += L"#....#.#";
	map += L"#....#.#";
	map += L"#......#";
	map += L"#...####";
	map += L"##.....#";
	map += L"########";

	auto lastTime = chrono::system_clock::now();
	auto currTime = chrono::system_clock::now();
	while (game)
	{
		currTime = chrono::system_clock::now();
		chrono::duration<float> timeDiff = currTime - lastTime;
		lastTime = currTime;
		float timePassed = timeDiff.count();
		//Quits game if Q is pressed
		if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
		{
			game = false;
			break;
		}
		//Handles rotations
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			theta -= (walkSpeed * 0.25f) * timePassed;

		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			theta += (walkSpeed * 0.25f) * timePassed;

		if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
		{
			posX += sinf(theta) * walkSpeed * timePassed;
			posY += cosf(theta) * walkSpeed * timePassed;
			if (map.c_str()[(int)posX * 8 + (int)posY] != '.')
			{
				posX -= sinf(theta) * walkSpeed * timePassed;
				posY -= cosf(theta) * walkSpeed * timePassed;
			}
		}

		if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
		{
			posX -= sinf(theta) * walkSpeed * timePassed;
			posY -= cosf(theta) * walkSpeed * timePassed;
			if (map.c_str()[(int)posX * 8 + (int)posY] != '.')
			{
				posX += sinf(theta) * walkSpeed * timePassed;
				posY += cosf(theta) * walkSpeed * timePassed;
			}
		}

		//Display the background
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

		//Display the walls
		for (int i = 0; i < 600; i += 2)
		{
			float ray = (theta - fov / 2.0f) + ((float) i / (float)600.0)*fov;
			float step = 0.01f;
			float dist = 0.0f;
			bool wall = false;
			float rayX = sinf(ray);
			float rayY = cosf(ray);
			while (!wall && dist < maxDist)
			{
				dist += step;
				int newX = (int)(posX + rayX * dist);
				int newY = (int)(posY + rayY * dist);
				if (newX < 0 || newX > 599 || newY < 0 || newY > 399)
				{
					wall = true;
					dist = maxDist;
				}
				else
				{
					if (map.c_str()[newX * 8 + newY] != '.')
					{
						wall = true;
					}
				}
			}
			float scalar = dist * 30.0f;
			r = 198 - (int) scalar;
			g = 220 - (int) scalar;
			b = 255 - (int) scalar;
			if (r < 0) r = 0;
			if (g < 0) g = 0;
			if (b < 0) b = 0;
			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			SDL_Rect rect_w = { i, (int) scalar, 2, 400 - 2 * (int) scalar };
			SDL_RenderFillRect(renderer, &rect_w);

		}
		SDL_RenderPresent(renderer);
	
	}


	return 0;
}

