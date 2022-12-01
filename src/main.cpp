#include <iostream>
#include <SDL/SDL.h>
#include <chrono>

#include "ECS/EntityManager.h"
#include "ECS/Component.h"
#include <cstdlib>
#include <string>
#include <ctime>

#include "ECS/Systems/AABBSystem.h"
#include "ECS/Systems/SpriteRenderSystem.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char* NAME = "MemoryShooter";

namespace ECS
{
struct TestComponent1 : ECS::Component
{
};
struct TestComponent2 : ECS::Component
{
};
struct TestComponent3 : ECS::Component
{
};
struct TestComponent4 : ECS::Component
{
};

struct TestComponent5 : ECS::Component
{
};
struct TestComponent6 : ECS::Component
{
};

struct TestSystem1 : ECS::System
{
	TestSystem1()
	{
        add_component_signature<TestComponent1>();
        add_component_signature<TestComponent2>();
        add_component_signature<TestComponent3>();
        add_component_signature<TestComponent4>();
        add_component_signature<TestComponent5>();
        add_component_signature<TestComponent6>();

        std::cout << "Sysem signature: ";
        for (auto const& s : signature)
        {
            std::cout << s << ' ';
        }
        std::cout << std::endl;
	}
};
struct TestSystem2 : ECS::System
{
    TestSystem2()
    {
        add_component_signature<TestComponent1>();
        add_component_signature<TestComponent2>();
        add_component_signature<TestComponent3>();
        add_component_signature<TestComponent4>();
        add_component_signature<TestComponent5>();
        add_component_signature<TestComponent6>();

        std::cout << "Sysem signature: ";
        for (auto const& s : signature)
        {
            std::cout << s << ' ';
        }
        std::cout << std::endl;
    }
};
struct TestSystem3 : ECS::System
{
    TestSystem3()
    {
	    
    add_component_signature<TestComponent1>();
    add_component_signature<TestComponent3>();

	std::cout << "Sysem signature: ";
    for (auto const& s : signature)
    {
        std::cout << s << ' ';
    }
    std::cout << std::endl;
    }
};


}


class Game
{
public:
    Game() {}
    ~Game() {}

    void run()
    {
        while (is_running)
        {
            Uint64 start = SDL_GetPerformanceCounter();

            handle_events();
            update();
            render();

            Uint64 end = SDL_GetPerformanceCounter();
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            //std::cout << "FPS: " << std::to_string(1.0f / elapsed) << std::endl;
        }
    }

    void init(const char* name, int width, int height)
    {
        // Initilize SDL
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


    	////////////
        // ECS test
        // Register systems

        //ECS::EntityManager::get_instance().register_system<ECS::SpriteRenderSystem>();
        ECS::EntityManager::get_instance().register_system<ECS::TestSystem1>();
        ECS::EntityManager::get_instance().register_system<ECS::TestSystem2>();
        ECS::EntityManager::get_instance().register_system<ECS::TestSystem3>();
        //ECS::EntityManager::get_instance().register_system<ECS::AABBSystem>();

        //auto start = std::chrono::steady_clock::now();

        int entities = 100;

        srand(time(NULL));
        rand();
        for (int i = 0; i < entities; ++i)
        {
            int x = rand() % SCREEN_WIDTH;
            int y = rand() % SCREEN_HEIGHT;

            SDL_Color rand_color;
            rand_color.r = rand() % 255;
            rand_color.g = rand() % 255;
            rand_color.b = rand() % 255;
            rand_color.a = 255;


            const auto e = ECS::EntityManager::get_instance().add_new_entity();
            
            //ECS::EntityManager::get_instance().add_component<TestComponent1>(e);

            /*
            ECS::EntityManager::get_instance().add_component<ECS::Transform>(e);

            ECS::EntityManager::get_instance().get_component<ECS::Sprite>(e).color = rand_color;
            ECS::EntityManager::get_instance().get_component<ECS::Transform>(e).position = { x, y };
            */
        }
        /*
        auto entity2 = ECS::EntityManager::get_instance().add_new_entity();


        ECS::EntityManager::get_instance().add_component<ECS::Transform>(entity2);
        //ECS::EntityManager::get_instance().get_component<ECS::Transform>(entity2);



        ECS::EntityManager::get_instance().add_component<ECS::Sprite>(entity2, renderer);

*/

        //auto end = std::chrono::steady_clock::now();
        //std::cout << "Start to end took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms.\n";
    	// 
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
        ECS::EntityManager::get_instance().update();
    }
    void render()
    {
        // Set background colour and clear 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);

        // Render entities
        ECS::EntityManager::get_instance().render();

        // Swap buffers
        SDL_RenderPresent(renderer);
    }
};



int main(int argc, char* argv[])
{
    ////////////
    auto const awesome = std::make_unique<Game>();
    awesome->init(NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
    awesome->run();
    awesome->clean();
	return 0;
}
