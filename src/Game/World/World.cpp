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
    auto it = std::find(_entities.begin(), _entities.end(), entity);

    if (it != _entities.end() && &(**it) == &(*entity))
        return false;

    _entities.emplace_back(entity);
    return true;
}

bool World::removeEntity(const std::shared_ptr<Entity> &entity) {
    auto it = std::find(_entities.begin(), _entities.end(), entity);

    if (it != _entities.end() && &(**it) == &(*entity)) {
        _entities.erase(it);
        return true;
    }

    return false;
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



/*
 *      PRIVATE methods
 */


World::World() : _physicsEngine(PhysicsEngine::getInstance()) {}



