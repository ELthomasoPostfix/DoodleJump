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

void Player::process(double delta) {
    std::unique_ptr<Player> up = std::make_unique<Player>(2, 3);
    registerEntity(up);
}

void Player::display() {
    // display view
}


const std::unique_ptr<int>& Player::doAThing() {
    static auto i = std::make_unique<int>(2);
    registerEntity(i);       // instantiate function/method template defined in Base
    return i;

}

const std::unique_ptr<Player>& Player::doAThingE() {
    static std::unique_ptr<Player> e = std::make_unique<Player>(2, 3);
    registerEntity(e);       // instantiate function/method template defined in Base
    return e;
}