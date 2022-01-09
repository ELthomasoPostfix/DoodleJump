//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Entity.h"


/*
 *      PUBLIC methods
 */

Entity::Entity(Rect& rect)
    : GameObject(0, 0), _collisionObject(rect, true) {
    auto& boundingBox = _collisionObject.getBoundingBox();
    setPosition(boundingBox.at(0), boundingBox.at(1), false);
}

Entity::Entity(double positionX, double positionY)
    : GameObject(0, 0),
    _collisionObject({{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}}, true) {
    setPosition(positionX, positionY);
}

void Entity::display() {}

CollisionObject &Entity::getCollisionShape() {
    return _collisionObject;
}

CollisionObject &Entity::getClipObject() {
    return _collisionObject;
}

void Entity::process(double delta) {}

CollisionInfo Entity::checkCollision(const std::pair<double, double>& moveDir) {
    return std::move(World::getInstance()->checkCollision(*this, moveDir));
}

void Entity::moveBehaviour(double moveX, double moveY) {
    _collisionObject.move(moveX, moveY);
}

void Entity::setBehaviour(double moveX, double moveY, double prevX, double prevY) {
    _collisionObject.move(moveX, moveY);
}

/*
bool Entity::registerEntity(const std::shared_ptr<Entity> &entity) {
    // TODO check header
    return World::getInstance()->addEntity(entity);
}

bool Entity::unregisterEntity(const std::shared_ptr<Entity> &entity) {
    return World::getInstance()->removeEntity(entity);
}
*/
