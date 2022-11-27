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
            SDL_SetRenderDrawColor(renderer, 0, 25, 25, 255);
            is_running = true;
        }
        else
        {
            std::cout << "SDL init failed" << std::endl;
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

struct Vec2
{
    float x, y;
};
struct Vec3
{
    float x, y, z;
};

struct Entity
{
    unsigned int id;
};

class Entity_Manager
{
public:
    Entity create()
    {
        last_id++;
        return { last_id };
    }
    void destroy(Entity e); // how to destroy entities
private:
    unsigned int last_id = 0;
};

struct Component_Mask
{
    unsigned int mask = 0;

    void add_component();
    void remove_component();
    bool matches();
};

class World
{
	
};
int main(int argc, char* argv[])
{
    auto awesome = std::make_unique<Game>();
    awesome->init(NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
    awesome->run();
    awesome->clean();
	return 0;
}
