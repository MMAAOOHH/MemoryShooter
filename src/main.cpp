#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

#include "Game.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char* NAME = "MemoryShooter";

int main(int argc, char* argv[])
{
    auto const awesome = std::make_unique<Game>();
    awesome->init(NAME, SCREEN_WIDTH, SCREEN_HEIGHT);
    awesome->run();
    awesome->clean();
	return 0;
}
