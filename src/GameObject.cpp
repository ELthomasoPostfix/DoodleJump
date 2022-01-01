//
// Created by Thomas Gueutal on 15/11/2021.
//

#include "GameObject.h"


/*
 *      PUBLIC methods
 */

GameObject::GameObject(const double positionX, const double positionY)
    : _position(positionX, positionY) {}


std::pair<double, double> GameObject::getPosition() const {
    return this->_position;
}



/*
 *      PROTECTED methods
 */

void GameObject::setPosition(const double destinationX, const double destinationY) {
    this->_position.first = destinationX;
    this->_position.second = destinationY;
}

