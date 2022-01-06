//
// Created by Thomas Gueutal on 03/01/2022.
//

#include "Game.h"



std::unique_ptr<Game>& Game::getInstance() {
    static std::unique_ptr<Game> game(new Game());
    return game;
}



