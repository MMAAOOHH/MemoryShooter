#include <iostream>
#include <SDL/SDL.h>

#include "ECS/Types.h"
#include "ECS/EntityManager.h"
#include "ECS/Entity.h"

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

struct TestComponentA : public ECS::Component
{
    int a = 69;
};

struct TestComponentB : public ECS::Component
{
    int a = 666;
};

struct TestSystemA : public ECS::System
{
    
	TestSystemA()
	{
        add_component_signature<TestComponentA>();
	}
	
};

struct TestSystemB : public ECS::System
{
    TestSystemB()
    {
        add_component_signature<TestComponentB>();
    }
    
};

struct TestSystemC : public ECS::System
{
    TestSystemC()
    {
        add_component_signature<TestComponentA>();
        add_component_signature<TestComponentB>();
    }
    
};


int main(int argc, char* argv[])
{
    ////////////
    // ECS test
    ////////////
    ECS::EntityManager manager;

    manager.register_system<TestSystemA>();
    manager.register_system<TestSystemB>();
    manager.register_system<TestSystemC>();

    auto entity1 = manager.add_new_entity();

    ECS::Entity ent(entity1, &manager);
    ent.add_component<TestComponentA>();

    auto entity2 = manager.add_new_entity();
    manager.add_component<TestComponentB>(entity2);

    auto entity3 = manager.add_new_entity();
    manager.add_component<TestComponentA>(entity3);
    manager.add_component<TestComponentB>(entity3);

    manager.update();
    ////////////


    auto const awesome = std::make_unique<Game>();
    awesome->init(NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
    awesome->run();
    awesome->clean();
	return 0;
}
