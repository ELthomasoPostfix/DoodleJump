//
// Created by Thomas Gueutal on 15/11/2021.
//

#include "GameObject.h"


/*
 *      PUBLIC methods
 */

GameObject::GameObject(const double positionX, const double positionY)
    : _position(positionX, positionY) {}

void GameObject::process(double delta) {}

void GameObject::move(double moveX, double moveY)
{
        adjustPosition(moveX, moveY);
        moveBehaviour(moveX, moveY);
}

void GameObject::move(const std::pair<double, double>& moveVector) { this->move(moveVector.first, moveVector.second); }

void GameObject::setPosition(const double destinationX, const double destinationY)
{
        _position.first = destinationX;
        _position.second = destinationY;
        setBehaviour(destinationX, destinationY, 0, 0);
}

std::pair<double, double> GameObject::getPosition() const {
    return this->_position;
}



/*
 *      PROTECTED methods
 */

void GameObject::moveBehaviour(const double moveX, const double moveY)
{ /* To be extended by derived classes. */
}

void GameObject::setBehaviour(const double destinationX, const double destinationY, const double prevX,
                              const double prevY)
{ /* To be extended by derived classes. */
}
