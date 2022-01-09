//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "World.h"
#include "../GameObject/Entity/Entity.h"
#include "../../View/AbstractEntityFactory/AbstractEntityFactory.h"


/*
 *      PUBLIC methods
 */

std::unique_ptr<World>& World::getInstance() {
    static std::unique_ptr<World> world(new World);
    return world;
}

void World::processEntities(const double delta) {

    for (const auto& go : _entities) {
        go->process(delta);
    }
}

void World::clipEntities() {
    for (auto& entity : _entities) {
        if (!_camera->isVisible(entity->getClipObject()))
            removeEntity(entity);
    }
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

CollisionInfo
World::checkCollision(Entity& movingBody, const std::pair<double, double> &moveDir) {

    std::vector<std::pair<double, double>> pushbackVectors;
    auto mbCollShape = movingBody.getCollisionShape();

    // TODO Wrap checkCollision() and determinePushback() into a getCollisionInfo method?
    //  Also think about difference between getCollisionInfo() and getCollisionsInfo().
    for (const auto& other : _entities) {
        CollisionObject& otherCollShape = other->getCollisionShape();
        if (&mbCollShape != &otherCollShape && mbCollShape.checkCollision(otherCollShape)) {
            const auto pushback = mbCollShape.determinePushback(moveDir, otherCollShape);

            // Pushback is valid
            if (pushback.first != 0.0 && pushback.second != 0.0)
                pushbackVectors.emplace_back(pushback);
        }
    }

    if (pushbackVectors.empty())
        return CollisionInfo{};

    // All pushback vectors have the same direction,
    // so the largest pushback will undo all collisions.
    unsigned int index = Utility::getLongestVectorIndex(pushbackVectors);

    CollisionInfo result;
    result.collidedWith = _entities.at(index);
    result.pushback = pushbackVectors.at(index);
    result.topCollision = mbCollShape.isAbove(result.collidedWith->getCollisionShape());
    result.sideCollision = !result.topCollision;
    return std::move(result);
}

void World::signalRoundEnd() {
    _roundOver = true;
}

bool World::roundHasEnded() {
    return _roundOver;
}

void World::setIndependentDimensions(unsigned int wWidth, unsigned int wHeight) {
    _camera->setIndependentDimensions(wWidth, wHeight);
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

    // TODO  Scroll camera down, go to end screen??
    if (roundHasEnded())
        _endAnimationFinished = false;

    return false;
}

World::World() {
    _roundOver = false;
    _endAnimationFinished = true;
}








