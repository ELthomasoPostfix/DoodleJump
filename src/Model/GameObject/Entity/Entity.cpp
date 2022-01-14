//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Entity.h"


/*
 *      PUBLIC methods
 */

Entity::Entity(Rect &collRect, bool isPhysical, bool isSolid)
    : GameObject(0, 0), _collisionObject(collRect, isPhysical, isSolid) {
    auto& boundingBox = _collisionObject.getBoundingBox();
    setPosition(boundingBox.at(0), boundingBox.at(1), false);
    _baseScore = 100;
}

void Entity::display() {}

void Entity::notifyCollision(Player &collidedWith, bool playerIsSupported) {}

CollisionObject &Entity::getCollisionObject() {
    return _collisionObject;
}

CollisionObject &Entity::getClipObject() {
    return _collisionObject;
}

void Entity::process(double delta) {}

void Entity::registerScoreboardObserver(const std::shared_ptr<Scoreboard>& scoreboard) {
    observer = scoreboard;
}

void Entity::unregisterScoreboardObserver() {
    observer.reset();
}

void Entity::setBaseScore(int score) {
    _baseScore = score;
}

int Entity::getBaseScore() const {
    return _baseScore;
}



/*
 *      PROTECTED methods
 */

bool Entity::pollEvent(dj::Event event) {
    return World::getInstance()->pollEvent(event);
}

void Entity::signalRoundEnd() {
    World::getInstance()->signalRoundEnd();
}

void Entity::requestRemoval() {
    World::getInstance()->requestRemoval(*this);
}

std::vector<SolidCollisionInfo> Entity::getSolidCollisions(const std::pair<double, double>& moveDir) {
    return std::move(World::getInstance()->getSolidCollisions(*this, moveDir));
}

std::vector<NonSolidCollisionInfo> Entity::getNonSolidCollisions() {
    return std::move(World::getInstance()->getNonSolidCollisions(*this));
}

void Entity::updateScoreboard(const int score) const {
    if (observer == nullptr)
        std::cout << "Scoreboard observer of entity is unassigned" << std::endl;
    else
        observer->update(score);
}

void Entity::moveBehaviour(double moveX, double moveY) {
    _collisionObject.move(moveX, moveY);
}

void Entity::setBehaviour(double moveX, double moveY, double prevX, double prevY) {
    _collisionObject.move(moveX, moveY);
}




