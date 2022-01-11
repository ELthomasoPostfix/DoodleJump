//
// Created by Thomas Gueutal on 03/01/2022.
//

#include "Game.h"


/*
 *      PUBLIC methods
 */

Game::Game(const unsigned int windowWidth, const unsigned int windowHeight)
    : _windowManager(std::make_unique<SFMLWindowManager>(windowWidth, windowHeight)) {

    _windowManager->textureManager->load(PLAYER_TEXTURE_ID, PLAYER_TEXTURE_PATH);
    _windowManager->textureManager->load(SPRING_TEXTURE_ID, SPRING_TEXTURE_PATH);
    _windowManager->textureManager->load(JETPACK_TEXTURE_ID, JETPACK_TEXTURE_PATH);
    _windowManager->fontManager->load(ARIAL_FONT_ID,ARIAL_FONT_PATH);

    _texturesInfo.playerTextureDims  = _windowManager->getTextureDimensions(PLAYER_TEXTURE_ID);
    _texturesInfo.springTextureDims  = _windowManager->getTextureDimensions(SPRING_TEXTURE_ID);
    _texturesInfo.jetpackTextureDims = _windowManager->getTextureDimensions(JETPACK_TEXTURE_ID);



    /*TODO
     * 1) load textures
     * 2) get texture dimensions
     * 3) store dimensions in informational struct
     * 4) assign struct to concrete factory
     * 5) created entities should make use of texture dimensions as to
     * be able to scale the sprite accordingly when drawing
     */

    std::unique_ptr<AbstractEntityFactory> entityFactory = std::make_unique<SFMLEntityFactory>(*this, _texturesInfo);

    auto& world = World::getInstance();
    Rect cameraArea{{{0, 0}, {1000, 0}, {1000, 1000}, {0, 1000}}};

    world->setIndependentDimensions(windowWidth, windowHeight);
    world->setCameraArea(cameraArea);
    world->assignEntityFactory(entityFactory);
}

void Game::start() {
    // Initial time passed set to essentially zero
    Stopwatch::getInstance()->update();
    doGameLoop();
    // TODO cleanup ???
}

void Game::setFrameRateLimit(unsigned int limit) {
    _windowManager->setFrameRateLimit(limit);
}


/*
 *      PROTECTED methods
 */

void Game::update(EntityView &changed) {
    _viewBuffer.emplace_back(std::move(changed));
}


/*
 *      PRIVATE methods
 */

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


        // TODO  ##########################################

        continue;
        // TODO  ##########################################


        // INCREMENT GAME STATE
        auto& world = World::getInstance();

        if (world->roundHasEnded()) {
            // TODO  query (?) and draw round end text
        } else {

            // DRAW VIEWS
            const double delta = stopwatch->elapsedSeconds();
            stopwatch->update();

            world->processEntities(delta);
            world->clipEntities();
            world->requestViews();

            _windowManager->clear();
            for (auto &view: _viewBuffer) {
                _windowManager->draw(view);
            }
            _windowManager->display();

            // TODO  query and draw current Score
        }
    }
}






