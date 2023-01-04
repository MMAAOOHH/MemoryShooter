#include "Game.h"

#include <random>
#include <string>

#include "Components/Controller.h"
#include "Components/PlayerController.h"
#include "Components/Enemy.h"
#include "Components/Star.h"

#define FONT_SIZE 24

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

    
    
    // Initilize TTF
    if (TTF_Init() != 0)
    {
        std::cout << "TTF init failed" << std::endl;
    }
    // Text
	font = TTF_OpenFont("./res/roboto.ttf", FONT_SIZE);
    /*
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, "test", {255,0,0,255});
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    text_rect = { 20, 20, text_surface->w, text_surface->h };
    SDL_FreeSurface(text_surface);
    TTF_CloseFont(font);
    */

    // ECS setup
    // ---------
    auto& manager = ECS::World::get_instance();

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
    const auto p = ECS::World::get_instance().create_entity();
    manager.add_component<PlayerController>(p);
    player_controller = &manager.get_component<PlayerController>(p);
    player_controller->init();

}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    TTF_Quit();
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
        //std::cout << "FPS: " << std::to_string(1.0f / delta_time) << std::endl;
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

			//Quit with ESC
            if (scan_code == SDL_SCANCODE_ESCAPE)
            {
                is_running = false;
            }

			// Pause with P
            if (scan_code == SDL_SCANCODE_P)
                current_state == running ? current_state = pause : current_state = running;

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
    if (current_state == pause)
        return;

    background->update(delta_time);
    player_controller->update(delta_time);
    enemy_system->update(delta_time);
    physics_system->update(delta_time);
    collision_system->update();
    damage_system->update();
    collision_system->clean();

    // todo: change temp solution
    score += damage_system->kill_count;

    ECS::World::get_instance().clean_destroyed();
    //TODO: Update game state

}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 9, 15, 1);
    SDL_RenderClear(renderer);

    render_system->update(renderer);
    render_text("Score: " + std::to_string(score), 10, 10);

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_RenderPresent(renderer);
}

void Game::render_text(std::string text, int x, int y)
{
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect rect;
    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t, { 255,255,255,255 });
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = x;
    rect.y = y;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}
