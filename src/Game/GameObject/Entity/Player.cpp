//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Player.h"

Player::Player(const double positionX, const double positionY) :
        Entity(positionX, positionY) {}

void Player::processInput(int horizFactor) {
    this->move(this->getPosition().first + horizFactor,
               this->getPosition().second);
}

// void Player::move(double moveX, double moveY) {
//    adjustPosition(moveX, moveY);
//}
//
// void Player::setPosition(double destinationX, double destinationY) {
//    const double moveVec[2] = {destinationX - this->getPosition().first,
//                               destinationY - this->getPosition().second};
//
//    adjustPosition(moveVec[0], moveVec[1]);
//    // TODO also move CollisionObject related to Player
//    // TODO generalize this to Entity? ==> generalize to the objects possessing
//    //  a CollisionObject
//}

void Player::process(double delta) { GameObject::process(delta); }

void Player::display() {
    // display view
}
