#include <iostream>

#include "Game.h"

int main()
{
        const std::unique_ptr<Game>& game = std::make_unique<Game>(600, 800);
        game->setFrameRateLimit(60);
        game->start();

        return 0;
}
