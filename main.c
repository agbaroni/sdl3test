#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[]) {
    bool done = false;
    SDL_Renderer *renderer = NULL;
    SDL_Window *window = NULL;

    if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());

	return -1;
    }

    window = SDL_CreateWindow("Test", 1024, 768, SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	SDL_Quit();

	return -1;
    }

    if (!SDL_ShowWindow(window)) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();

	return -1;
    }

    renderer = SDL_CreateRenderer(window, NULL);

    if (renderer == NULL) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	SDL_DestroyWindow(window);
	SDL_Quit();

	return -1;
    }

    if (!SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255)) {
	SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return -1;
    }

    while (!done) {
	SDL_Event event;

	if (!SDL_RenderClear(renderer)) {
	    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();

	    return -1;
	}

	while (SDL_PollEvent(&event)) {
	    if (event.type == SDL_EVENT_QUIT) {
		done = true;
	    }
        }

	if (!SDL_RenderPresent(renderer)) {
	    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s\n", SDL_GetError());
	    SDL_DestroyRenderer(renderer);
	    SDL_DestroyWindow(window);
	    SDL_Quit();

	    return -1;
	}
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
