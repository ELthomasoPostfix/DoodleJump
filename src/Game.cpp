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

    std::unique_ptr<AbstractEntityFactory> entityFactory = std::make_unique<SFMLEntityFactory>(*this, _texturesInfo);

    auto& world = World::getInstance();
    Rect cameraArea{{{0, 0}, {1000, 0}, {1000, 1000}, {0, 1000}}};

    world->setIndependentDimensions(windowWidth, windowHeight);
    world->setCameraArea(cameraArea);
    world->assignEntityFactory(entityFactory);

    // TODO  seed random
    Random::getInstance()->reseed(std::rand());
    Random::getInstance()->redistribute(0.6, 0.15);
    Random::getInstance()->reClamp(0.0, 1.0);
}

void Game::start() {
    // Initial time passed set to essentially zero
    Stopwatch::getInstance()->update();
    // TODO  ##########################################
    World::getInstance()->test();      // TODO  apply the Bonus observer pattern to platforms as wel??
    //  ==> generalize it into an Entity::notifyCollision(caller) method
    //  so that a concrete entity can check whether the passed caller
    //  matches its observable and can then work on its observable?
    //  But in principle, the observer should register itself with
    //  its observable, so their wouldn't be room for doubt if the
    //  observer stores only a single observable. But a check never hurts.
    // TODO  ##########################################
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

        // INCREMENT GAME STATE
        auto& world = World::getInstance();

        if (world->roundHasEnded()) {
            _windowManager->clear({255, 0, 0});
            _windowManager->draw("GAME OVER", ARIAL_FONT_ID);
        } else {


            // DRAW VIEWS
            const double delta = stopwatch->elapsedSeconds();
            stopwatch->update();

            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
            //goto piss;
            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO

            world->processEntities(delta);

            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
            piss:;
            // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO


            world->clipEntities();
            world->executeMurderBuffer();
            world->requestViews();

            _windowManager->clear({255, 0, 0});
            for (auto &view: _viewBuffer) {
                _windowManager->draw(view);
            }


            // TODO  query and draw current Score
        }

        _windowManager->display();
    }
}






