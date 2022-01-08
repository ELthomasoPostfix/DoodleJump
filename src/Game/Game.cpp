//
// Created by Thomas Gueutal on 03/01/2022.
//

#include "Game.h"


/*
 *      PUBLIC methods
 */

Game::Game(unsigned int windowWidth, unsigned int windowHeight)
    : _windowManager(std::make_unique<SFMLWindowManager>(windowWidth, windowHeight)) {
}

void Game::draw(EntityView &view) {
    _windowManager->draw(view);
}

void Game::draw(const std::string &text, const size_t fontID) {
    _windowManager->draw(text, fontID);
}

void Game::setFrameRateLimit(unsigned int limit) {
    _windowManager->setFrameRateLimit(limit);
}


