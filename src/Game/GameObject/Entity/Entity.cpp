//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Entity.h"


/*
 *      PUBLIC methods
 */

Entity::Entity(Rect &rect, const bool isPhysical, const bool isSolid)
    : GameObject(0, 0), _collisionObject(rect, isPhysical, isSolid) {
    auto& boundingBox = _collisionObject.getBoundingBox();
    setPosition(boundingBox.at(0), boundingBox.at(1), false);
}

void Entity::display() {}

CollisionObject &Entity::getCollisionObject() {
    return _collisionObject;
}

CollisionObject &Entity::getClipObject() {
    return _collisionObject;
}

void Entity::process(double delta) {}

std::vector<SolidCollisionInfo> Entity::getSolidCollisions(const std::pair<double, double>& moveDir) {
    return std::move(World::getInstance()->getSolidCollisions(*this, moveDir));
}

std::vector<NonSolidCollisionInfo> Entity::getNonSolidCollisions() {
    return std::move(World::getInstance()->getNonSolidCollisions(*this));
}

void Entity::signalRoundEnd() const {
    World::getInstance()->signalRoundEnd();
}


/*
 *      PROTECTED methods
 */

void Entity::moveBehaviour(double moveX, double moveY) {
    _collisionObject.move(moveX, moveY);
}

void Entity::setBehaviour(double moveX, double moveY, double prevX, double prevY) {
    _collisionObject.move(moveX, moveY);
}
