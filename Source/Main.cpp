#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char **argv)
{
    bool success = Game::Instance().Initialize();
    if (success) Game::Instance().RunLoop();
    Game::Instance().Shutdown();
    return 0;
}
