#include "Game.h"

#include "Components/Controller.h"
#include "Components/PlayerController.h"
#include "Components/Enemy.h"
#include "Components/Star.h"

bool keys[SDL_NUM_SCANCODES]{ false };
float DEFAULT_SPRITE_W = 32;
float DEFAULT_SPRITE_H = 32;
SDL_Renderer* RENDERER;

void Game::init(const char* name, int width, int height)
{

    // Initilize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        RENDERER = renderer;
        SDL_SetRenderDrawColor(renderer, 0, 25, 25, 255);
        is_running = true;
    }
    else
    {
        std::cout << "SDL init failed" << std::endl;
        is_running = false;
    }

    // ECS setup
    auto& manager = ECS::ECSManager::get_instance();

    // Register Components
    manager.register_component<PlayerController>();
    manager.register_component<Enemy>();
    manager.register_component<Transform>();
    manager.register_component<Sprite>();
    manager.register_component<Collider>();
    manager.register_component<Collision>();
    manager.register_component<RigidBody>();
    manager.register_component<Controller>();
    manager.register_component<Weapon>();
    manager.register_component<Projectile>();
    manager.register_component<Health>();
    manager.register_component<Star>();

    // Register Systems
    render_system = manager.register_system<SpriteRenderSystem>();
    collision_system = manager.register_system<CollisionSystem>();
    physics_system = manager.register_system<PhysicsSystem>();
    damage_system = manager.register_system<DamageSystem>();
    enemy_system = manager.register_system<EnemySystem >();
    background = manager.register_system<BackgroundSystem>();

    // Initialize Systems
    render_system->init();
    collision_system->init();
    physics_system->init();
    damage_system->init();
    enemy_system->init();
    background->init();

    // Player Entity
    const auto p = ECS::ECSManager::get_instance().create_entity();
    manager.add_component<PlayerController>(p);
    player_controller = &manager.get_component<PlayerController>(p);
    player_controller->init();

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    window = nullptr;
    renderer = nullptr;
}

void Game::run()
{
    float delta_time = 0.f;
    Uint64 previous_ticks = 0;

    float time = 0;
    while (is_running)
    {
        Uint64 ticks = SDL_GetPerformanceCounter();
        Uint64 delta_ticks = ticks - previous_ticks;

        handle_events();
        update(delta_time);
        render();

        delta_time = static_cast<float>(delta_ticks) / static_cast<float>(SDL_GetPerformanceFrequency());
        if (delta_time > 1) delta_time = 0; // accounts for weird fluctuation at startup
        previous_ticks = ticks;

        // limit fps
        SDL_Delay(8);
        // Show fps
        std::cout << "FPS: " << std::to_string(1.0f / delta_time) << std::endl;
        //std::cout << "wave_time: " << std::to_string(wave_time) << std::endl;
    }
}

void Game::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
			case SDL_QUIT:
				is_running = false;
        	break;

        case SDL_KEYDOWN:
        {
            const int scan_code = event.key.keysym.scancode;
            keys[scan_code] = true;
            break;
        }

        case SDL_KEYUP:
        {
            const int scan_code = event.key.keysym.scancode;
            keys[scan_code] = false;
            break;
        }
        }
    }
}

void Game::update(float delta_time)
{
    background->update(delta_time);
    player_controller->update(delta_time);
    enemy_system->update(delta_time);
    physics_system->update(delta_time);
    collision_system->update();
    damage_system->update();

    ECS::ECSManager::get_instance().clean_destroyed();

}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    render_system->update(renderer);

    SDL_RenderPresent(renderer);
}