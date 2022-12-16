#pragma once
#include <SDL/SDL_scancode.h>
#include <SDL/SDL_render.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Renderer* RENDERER;
extern bool keys[SDL_NUM_SCANCODES];
extern float DEFAULT_SPRITE_W;
extern float DEFAULT_SPRITE_H;
