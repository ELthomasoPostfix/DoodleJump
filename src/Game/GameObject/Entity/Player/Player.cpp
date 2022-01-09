//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Player.h"


/*
 *      PUBLIC methods
 */

Player::Player(const double positionX, const double positionY) :
        Entity(positionX, positionY) {}

Player::Player(Rect &rect) : Entity(rect) {}

void Player::processInput(int horizFactor) {
    this->move(this->getPosition().first + horizFactor,
               this->getPosition().second);
}

void Player::process(double delta) {
    std::shared_ptr<Player> up = std::make_shared<Player>(2, 3);
    Rect r = std::array<std::pair<double, double>, 4>{{{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}};
    std::shared_ptr<KinematicBody> kb =
            std::make_shared<KinematicBody>(1.0, 1.0, r, false);
    std::shared_ptr<RigidBody> rb =
            std::make_shared<RigidBody>(1.0, 1.0, r, false);
    std::shared_ptr<StaticBody> sb =
            std::make_shared<StaticBody>(1.0, 1.0, r, false);
    //const std::shared_ptr<Entity>& uEr(up);
    bool res = false;

//    res = registerEntity(up);
//    res = registerEntity(up);
//    res = unregisterEntity(up);
//    res = unregisterEntity(up);
//    res = unregisterEntity(up);
//
//    res = registerPhysicsBody(kb);
//    res = registerPhysicsBody(kb);
//    res = unregisterPhysicsBody(kb);
//    res = unregisterPhysicsBody(kb);
//    res = unregisterPhysicsBody(kb);
//    res = registerPhysicsBody(rb);
//    res = unregisterPhysicsBody(rb);
//    res = unregisterPhysicsBody(rb);
//    res = registerPhysicsBody(sb);
//    res = unregisterPhysicsBody(sb);
//    res = unregisterPhysicsBody(sb);
//    res = true;
}

