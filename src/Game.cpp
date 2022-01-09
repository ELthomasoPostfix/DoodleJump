//
// Created by Thomas Gueutal on 03/01/2022.
//

#include "Game.h"


/*
 *      PUBLIC methods
 */

Game::Game(unsigned int windowWidth, unsigned int windowHeight)
    : _windowManager(std::make_unique<SFMLWindowManager>(windowWidth, windowHeight)) {

    _entityFactory = std::make_unique<SFMLEntityFactory>(*this);

    _windowManager->textureManager->load(PLAYER_TEXTURE_ID, PLAYER_TEXTURE_PATH);
    _windowManager->textureManager->load(SPRING_TEXTURE_ID, SPRING_TEXTURE_PATH);
    _windowManager->textureManager->load(JETPACK_TEXTURE_ID, JETPACK_TEXTURE_PATH);
    _windowManager->fontManager->load(ARIAL_FONT_ID,ARIAL_FONT_PATH);
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

void Game::update(EntityView &changed) {
    // TODO  This is a weird implementation? Isn't the window cleared every frame???
    //  ==> Add to a buffer instead + Add a 'size_t layer' parameter??
    _windowManager->draw(changed);
}



