#pragma once
#include <SDL/SDL_scancode.h>
#include <SDL/SDL_render.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern int DEFAULT_SPRITE_W;
extern int DEFAULT_SPRITE_H;

extern bool keys[SDL_NUM_SCANCODES];
extern SDL_Renderer* RENDERER;
