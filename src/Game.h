#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include <SDL/SDL.h>

#include "ECS/ECS.h"
#include "ECS/Systems/AABBSystem.h"
#include "ECS/Systems/SpriteRenderSystem.h"
#include "ECS/Systems/PhysicsSystem.h"


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Game
{
public:
    Game() = default;
    ~Game() = default;

    void init(const char* name, int width, int height)
    {

        // Initilize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
        {
            window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawColor(renderer, 0, 25, 25, 255);
            is_running = true;
        }
        else
        {
            std::cout << "SDL init failed" << std::endl;
            is_running = false;
        }

        // ECS 
        auto& manager = ECS::ECSManager::get_instance();

        // Register Components
        manager.register_component<Transform>();
        manager.register_component<Sprite>();
        manager.register_component<Collision>();
        manager.register_component<RigidBody>();

        // Register Systems
        render_system = manager.register_system<SpriteRenderSystem>();
        aabb_system = manager.register_system<AABBSystem>();
        physics_system = manager.register_system<PhysicsSystem>();

        // Set System signatures
        {
            // Render
            ECS::Signature signature;
            signature.set(manager.get_component_type<Transform>(), true);
            signature.set(manager.get_component_type<Sprite>(), true);

            manager.set_system_signature<SpriteRenderSystem>(signature);
        }

        {
            // Collision
            ECS::Signature signature;
            signature.set(manager.get_component_type<Transform>(), true);
            signature.set(manager.get_component_type<Collision>(), true);

            manager.set_system_signature<AABBSystem>(signature);
        }
        {
            // Physics
            ECS::Signature signature;
            signature.set(manager.get_component_type<Transform>(), true);
            signature.set(manager.get_component_type<RigidBody>(), true);

            manager.set_system_signature<PhysicsSystem>(signature);
        }



        int entities = 200;

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

           manager.add_component<Transform>(e);
           manager.add_component<Sprite>(e);
           manager.add_component<Collision>(e);
           manager.add_component<RigidBody>(e);

           manager.get_component<Transform>(e).position = { (float)x, (float)y };
           manager.get_component<Sprite>(e).color = rand_color;
        }

    }
    void clean()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
    }

    void run()
    {
        float delta_time = 0.f;
        Uint64 previous_ticks = 0;

        while (is_running)
        {
            Uint64 ticks = SDL_GetPerformanceCounter();
            Uint64 delta_ticks = ticks - previous_ticks;
            previous_ticks = ticks;
            delta_time = (float)delta_ticks / SDL_GetPerformanceFrequency();

            handle_events();
            update(delta_time);
            render();

            std::cout << delta_ticks << std::endl;
        }
    }

private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running = false;

    std::shared_ptr<SpriteRenderSystem> render_system;
    std::shared_ptr<AABBSystem> aabb_system;
    std::shared_ptr<PhysicsSystem> physics_system;

    void handle_events()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            is_running = false;
        }
    }
    void update(float delta_time)
    {
        physics_system->update(delta_time);
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

