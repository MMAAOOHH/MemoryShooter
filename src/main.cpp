#include <iostream>
#include <SDL/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char* NAME = "MemoryShooter";

class Game
{
public:
    Game() {}
    ~Game() {}

    void run()
    {
        while (is_running)
        {
            handle_events();
            update();
            render();
        }
    }

    void init(const char* name, int width, int height)
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
        {
            window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawColor(renderer, 0, 10, 10, 255);
            is_running = true;
        }
        else
        {
            is_running = false;
        }
    }
    void clean()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running = false;

    void handle_events()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }
    }
    void update()
    {
	    // do stuff
    }
    void render()
    {
        SDL_RenderClear(renderer);
        // render stuff
        SDL_RenderPresent(renderer);
    }
};

int main(int argc, char* argv[])
{
    auto game = std::make_unique<Game>();
    game->init(NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->run();
    game->clean();

	return 0;
}