//
// Created by Thomas Gueutal on 03/01/2022.
//

#include "Game.h"


/*
 *      PUBLIC methods
 */

Game::Game(const unsigned int windowWidth, const unsigned int windowHeight)
    : _windowManager(std::make_unique<SFMLWindowManager>(windowWidth, windowHeight)) {

    // TODO  don't store this here, but in World??
    _entityFactory = std::make_unique<SFMLEntityFactory>(*this);


    _windowManager->textureManager->load(PLAYER_TEXTURE_ID, PLAYER_TEXTURE_PATH);
    _windowManager->textureManager->load(SPRING_TEXTURE_ID, SPRING_TEXTURE_PATH);
    _windowManager->textureManager->load(JETPACK_TEXTURE_ID, JETPACK_TEXTURE_PATH);
    _windowManager->fontManager->load(ARIAL_FONT_ID,ARIAL_FONT_PATH);

    auto& world = World::getInstance();
    Rect cameraArea{{{0, 0}, {1000, 0}, {1000, 1000}, {0, 1000}}};

    world->setIndependentDimensions(windowWidth, windowHeight);
    world->setCameraArea(cameraArea);
    world->assignEntityFactory(_entityFactory);
}

void Game::doGameLoop() {
    auto& stopwatch = Stopwatch::getInstance();

    while (true) {
        // CLEAR VIEW BUFFER
        _viewBuffer.clear();

        // POLL EVENTS
        dj::Event event = dj::NONE;
        while (_windowManager->pollEvent(event)) {
            switch (event) {
                case dj::NONE:
                    break;
                case (dj::Event::EXIT):
                    _windowManager->close();
                    // TODO Make world clean up ??
                    return;
                default:
                    // TODO  notify world of LEFT/RIGHT/SPACE_BAR event
                    break;
            }
        }

        // DRAW VIEWS
        auto& world = World::getInstance();
        const double delta = stopwatch->elapsedSeconds();
        stopwatch->update();

        world->processEntities(delta);
        world->clipEntities();
        world->requestViews();

        _windowManager->clear();
        for (auto& view : _viewBuffer) {
            _windowManager->draw(view);
        }
        _windowManager->display();


        if (world->roundHasEnded()) {
            // TODO  query (?) and draw round end text
        } else {
            // TODO  query and draw current Score
        }

    }
}

void Game::setFrameRateLimit(unsigned int limit) {
    _windowManager->setFrameRateLimit(limit);
}

void Game::update(EntityView &changed) {
    _viewBuffer.emplace_back(std::move(changed));
}




