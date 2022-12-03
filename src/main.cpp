#include <iostream>
#include <SDL/SDL.h>
#include <chrono>

#include "ECS/ECS.h"
#include "ECS/Component.h"
#include <cstdlib>
#include <string>
#include <ctime>

#include "ECS/Systems/AABBSystem.h"
#include "ECS/Systems/SpriteRenderSystem.h"


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
            Uint64 start = SDL_GetPerformanceCounter();

            handle_events();
            update();
            render();

            Uint64 end = SDL_GetPerformanceCounter();
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            std::cout << "FPS: " << std::to_string(1.0f / elapsed) << std::endl;
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

        // Register Components
        ECS::ECSManager::get_instance().register_component<Transform>();
        ECS::ECSManager::get_instance().register_component<Sprite>();
        ECS::ECSManager::get_instance().register_component<Collision>();

    	// Register Systems
    	render_system = ECS::ECSManager::get_instance().register_system<SpriteRenderSystem>();
    	aabb_system = ECS::ECSManager::get_instance().register_system<AABBSystem>();

        // Set System signatures
        {
            ECS::Signature signature;
            signature.set(ECS::ECSManager::get_instance().get_component_type<Transform>(), true);
            signature.set(ECS::ECSManager::get_instance().get_component_type<Sprite>(), true);

            ECS::ECSManager::get_instance().set_system_signature<SpriteRenderSystem>(signature);
        }

        {
            ECS::Signature signature;
            signature.set(ECS::ECSManager::get_instance().get_component_type<Transform>(), true);
            signature.set(ECS::ECSManager::get_instance().get_component_type<Collision>(), true);

            ECS::ECSManager::get_instance().set_system_signature<AABBSystem>(signature);
        }

        //ECS::EntityManager::get_instance().register_system<ECS::AABBSystem>();

        //auto start = std::chrono::steady_clock::now();

        int entities = 1000;

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


            const auto e = ECS::ECSManager::get_instance().create_entity();
            
            ECS::ECSManager::get_instance().add_component<Transform>(e);
            ECS::ECSManager::get_instance().add_component<Sprite>(e);
            ECS::ECSManager::get_instance().add_component<Collision>(e);


            /*
            ECS::EntityManager::get_instance().add_component<ECS::Transform>(e);
			*/

            ECS::ECSManager::get_instance().get_component<Transform>(e).position = { x, y };
            ECS::ECSManager::get_instance().get_component<Sprite>(e).color = rand_color;
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

    std::shared_ptr<SpriteRenderSystem> render_system;
    std::shared_ptr<AABBSystem> aabb_system;

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

        aabb_system->update();

    }
    void render()
    {
        // Set background colour and clear 
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
        SDL_RenderClear(renderer);

        // Render entities
        render_system->update(renderer);

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
