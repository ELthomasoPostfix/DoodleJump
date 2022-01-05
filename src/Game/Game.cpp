//
// Created by Thomas Gueutal on 03/01/2022.
//

#include "Game.h"



Game *Game::getInstance() {
    static Game* game = new Game();
    return game;
}



