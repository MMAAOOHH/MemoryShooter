#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

#include <SDL/SDL.h>

#include "Common.h"
#include "ECS/ECS.h"

#include "Systems/CollisionSystem.h"
#include "Systems/SpriteRenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/BackgroundSystem.h"
#include "Systems/DamageSystem.h"
#include "Systems/EnemySystem.h"
#include "Components/PlayerController.h"

class Game
{
public:
    Game() = default;
    ~Game() = default;

    void init(const char* name, int width, int height);
    void clean();
    void run();

private:

    void handle_events();
    void update(float delta_time);
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool is_running = false;

    PlayerController* player_controller;

    std::shared_ptr<EnemySystem> enemy_system;
    std::shared_ptr<PhysicsSystem> physics_system;
    std::shared_ptr<DamageSystem> damage_system;
    std::shared_ptr<CollisionSystem> collision_system;
    std::shared_ptr<SpriteRenderSystem> render_system;
    std::shared_ptr<BackgroundSystem> background;
};
