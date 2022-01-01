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

void Player::move(double destinationX, double destinationY) {
    double diffX = destinationX - this->getPosition().first;
    double diffY = destinationY - this->getPosition().second;
    setPosition(destinationX, destinationY);
}

void Player::display() {
    // display view
}
