#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Images", 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

	SDL_Surface* surface = IMG_Load("C:/Users/banko/OneDrive/Desktop/TODAY'S 13th REASON/IMG_1525 (1).jpg");
	SDL_Surface* surface1 = IMG_Load("C:/Users/banko/OneDrive/Desktop/TODAY'S 13th REASON/Photo_1755722219899.jpg");
	SDL_Surface* surface2 = IMG_Load("C:/Users/banko/OneDrive/Desktop/TODAY'S 13th REASON/Photo_1766403866299.jpg");
	SDL_Surface* surface3 = IMG_Load("C:/Users/banko/OneDrive/Desktop/TODAY'S 13th REASON/IMG_0581 (1).jpg");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Texture* texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, surface3);

	SDL_DestroySurface(surface);
	SDL_DestroySurface(surface1);
	SDL_DestroySurface(surface2);
	SDL_DestroySurface(surface3);
	int width = 100;
	int height = 100;


	SDL_FRect top = { 350,   125, width, height }; // full width, top
	SDL_FRect midL = { 225, 250, width, height }; // left half, middle
	SDL_FRect midR = { 475, 250, width, height }; // right half, middle
	SDL_FRect bottom = { 350, 375, width, height }; // full width, bottom

	SDL_RenderTexture(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);


	SDL_Event event;
	bool running = true;

	float x = 1.0f;
	float y = 2.0f;
	float speed = 150.0f;

	Uint64 lastTime = SDL_GetTicks();

	while (running) {

		Uint64 currentTime = SDL_GetTicks();

		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;

		//Poll Events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) 
				running = false;

			if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
				running = false;

			if (!surface) {
				SDL_Log("Failed to load image: %s", SDL_GetError());
				return 1;
			}

			x += speed * deltaTime;
			if (x > 1000) x = 0;

			y += speed * deltaTime;
			if (y > 1000) y = 0;

		}
		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, texture, NULL, &top);
		SDL_RenderTexture(renderer, texture1, NULL, &midL);
		SDL_RenderTexture(renderer, texture2, NULL, &midR);
		SDL_RenderTexture(renderer, texture3, NULL, &bottom);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);
	SDL_DestroyTexture(texture3);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}