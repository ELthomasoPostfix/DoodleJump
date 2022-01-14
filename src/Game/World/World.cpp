//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "World.h"
#include "../GameObject/Entity/Player/Player.h"
#include "../AbstractEntityFactory/AbstractEntityFactory.h"

#include "Camera.h"
#include "Spawner.h"


/*
 *      PUBLIC methods
 */

std::unique_ptr<World>& World::getInstance() {
    static std::unique_ptr<World> world(new World);
    return world;
}

void World::processEntities(const double delta) {

    for (const auto& processable : _entities) {
        processable->process(delta);
    }
}

void World::refocusCamera() {
    double scrollY = _player->getPosition().second - _camera->getFocusY();

    if (!roundHasEnded() && scrollY <= 0)
        return;

    _camera->move(0, scrollY);
}

void World::handleSpawning() {
    _spawner->handleSpawning(*this);
}

void World::pushEvent(dj::Event event) {
    _receivedEvents[event] = true;

    if (roundHasEnded() && event == dj::Event::SPACE_BAR)
        signalRoundBegin();
}

bool World::pollEvent(dj::Event event) const {
    return _receivedEvents.count(event) && _receivedEvents.find(event)->second;
}

void World::clearEvents() {
    for (auto& event : _receivedEvents) {
        event.second = false;
    }
}

void World::clipEntities() {
    auto it = _entities.begin();
    while (it != _entities.end()) {
        if (!_camera->isVisible((*it)->getClipObject())) {
            //(*it)->move(0, 600);
            //++it;
                        it = _entities.erase(it); // TODO  uncomment and delete prev 2 lines
        } else {
            ++it;
        }
    }

    if (_player.use_count() == 1)
        signalRoundEnd();

    it = _bgEntities.begin();
    while (it != _bgEntities.end()) {
        if (!_camera->isVisible((*it)->getClipObject()))
            it = _bgEntities.erase(it);
        else
            ++it;
    }
}

void World::requestViews() {
    for (const auto& bgEntity : _bgEntities) {
        bgEntity->display();
    }

    for (auto fgEntity = _entities.rbegin(); fgEntity != _entities.rend(); ++fgEntity) {
        fgEntity->get()->display();
    }
}

int World::pollScore() const {
    return _scoreboard->getScore();
}

void World::requestRemoval(Entity &target) {
    auto cameraBB = getCameraBoundingBox();
    // Clipping will take care of the rest :)
    target.setPosition(
            cameraBB.at(2) + target.getClipObject().getBoundingWidth() * 5,
            cameraBB.at(1) - target.getClipObject().getBoundingHeight() * 5
    );
}

void World::resetWorld() {
    _entities.clear();
    _bgEntities.clear();
    _player.reset();
    _scoreboard->resetScore();
}

void World::setupWorld() {
    _spawner->spawnPlayer(*this);
}

bool World::addEntity(const std::shared_ptr<Entity>& entity) {
    return addEntity(entity, _entities);
}

bool World::removeEntity(const std::shared_ptr<Entity> &entity) {
    return removeEntity(entity, _entities);
}

bool World::addBGEntity(const std::shared_ptr<Entity> &entity) {
    return addEntity(entity, _bgEntities);
}

bool World::removeBGEntity(const std::shared_ptr<Entity> &entity) {
    return removeEntity(entity, _bgEntities);
}

std::vector<SolidCollisionInfo>
World::getSolidCollisions(Entity& movingBody, const std::pair<double, double> &moveDir) {

    std::vector<SolidCollisionInfo> collisions;
    auto mbCollShape = movingBody.getCollisionObject();

    for (const auto& staticBody : _entities) {
        CollisionObject& otherCollShape = staticBody->getCollisionObject();
        if (!otherCollShape.isSolid())
            continue;
        if (&mbCollShape != &otherCollShape && mbCollShape.checkCollision(otherCollShape)) {
            const auto pushback = mbCollShape.determinePushback(moveDir, otherCollShape, 1.001);

            // Pushback is valid
            if (pushback.first != 0.0 || pushback.second != 0.0) {
                SolidCollisionInfo info;
                info.collidedWith = staticBody;
                info.pushback = pushback;
                info.topCollision = mbCollShape.isAbove(info.collidedWith->getCollisionObject(),
                                                        info.pushback.second);
                info.sideCollision = !info.topCollision;
                collisions.emplace_back(std::move(info));
            }
        }
    }

    return std::move(collisions);
}

std::vector<NonSolidCollisionInfo>
World::getNonSolidCollisions(Entity& movingBody) {

    std::vector<NonSolidCollisionInfo> collisions;
    auto mbCollShape = movingBody.getCollisionObject();

    for (const auto& staticBody : _entities) {
        CollisionObject& otherCollShape = staticBody->getCollisionObject();
        if (otherCollShape.isSolid())
            continue;
        if (&mbCollShape != &otherCollShape && mbCollShape.checkCollision(otherCollShape)) {
                NonSolidCollisionInfo info;
                info.collidedWith = staticBody;
                collisions.emplace_back(std::move(info));
        }
    }

    return std::move(collisions);
}

void World::signalRoundEnd() {
    _roundOver = true;
    resetWorld();
}

void World::signalRoundBegin() {
    _roundOver = false;
    setupWorld();
}

bool World::roundHasEnded() {
    return _roundOver;
}

void World::setIndependentDimensions(unsigned int wWidth, unsigned int wHeight) {
    _camera->setIndependentDimensions(wWidth, wHeight);
}

std::pair<unsigned int, unsigned int> World::getCameraDimensions() const {
    return _camera->getDimensions();
}

const std::array<double, 4>& World::getCameraBoundingBox() const {
    return _camera->getBoundingBox();
}

void World::assignEntityFactory(std::unique_ptr<AbstractEntityFactory>& abstractEntityFactory) {
    _entityFactory = std::move(abstractEntityFactory);
}

void World::setCameraArea(Rect &cameraArea) {
    _camera->replaceCameraArea(cameraArea);
}

void World::projectViewArea(CollisionObject &viewArea) const {
    _camera->project(viewArea);
}



/*
 *      PRIVATE methods
 */

bool World::addEntity(const std::shared_ptr<Entity> &entity, std::vector<std::shared_ptr<Entity>>& vec) {
    auto it = std::find(vec.begin(), vec.end(), entity);

    if (it != vec.end() && &(**it) == &(*entity))
        return false;

    vec.emplace_back(entity);
    return true;
}

bool World::removeEntity(const std::shared_ptr<Entity> &entity, std::vector<std::shared_ptr<Entity>>& vec) {
    auto it = std::find(vec.begin(), vec.end(), entity);

    if (it != vec.end() && &(**it) == &(*entity)) {
        vec.erase(it);
        return true;
    }

    return false;
}

World::World() {
    _scoreboard = std::make_unique<Scoreboard>();
    Rect tempCameraArea{DEFAULT_CAMERA_AREA};
    _camera = std::make_unique<Camera>(_scoreboard,
                                       DEFAULT_CAMERA_WIDTH,
                                       DEFAULT_CAMERA_HEIGHT,
                                       tempCameraArea);
    _spawner = std::make_unique<Spawner>(*this);
    _roundOver = true;
}


