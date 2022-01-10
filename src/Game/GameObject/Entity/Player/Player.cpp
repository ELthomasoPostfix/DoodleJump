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

Player::~Player() {
    signalRoundEnd();
    // TODO Doesn't the player need to live during the end animation???
    //  ==> Wouldn't keeping a weak_ptr work better?
    //  ==> transformable into shared_ptr for operations
}

void Player::processInput(int horizFactor) {
    this->move(this->getPosition().first + horizFactor,
               this->getPosition().second);
}

void Player::process(double delta) {

}


