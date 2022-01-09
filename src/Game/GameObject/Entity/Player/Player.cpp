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

}

