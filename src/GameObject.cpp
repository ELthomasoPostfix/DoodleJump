//
// Created by Thomas Gueutal on 15/11/2021.
//

#include "GameObject.h"
#include "Collision/CollisionObject.h"

#include <utility>


/*
 *      PUBLIC methods
 */

GameObject::GameObject(const double positionX, const double positionY)
    : _position(positionX, positionY) {}

GameObject::GameObject(std::pair<double, double>  position)
    : _position(std::move(position)) {}

void GameObject::process(double delta) {}

void GameObject::move(double moveX, double moveY)
{
        adjustPosition(moveX, moveY);
        moveBehaviour(moveX, moveY);
}

void GameObject::move(const std::pair<double, double>& moveVector) { this->move(moveVector.first, moveVector.second); }

void GameObject::setPosition(double destinationX, double destinationY, bool doSetBehaviour)
{
        const double prevX = _position.first;
        const double prevY = _position.second;

        _position.first = destinationX;
        _position.second = destinationY;

        if (doSetBehaviour)
            setBehaviour(_position.first - destinationX,
                         _position.second - destinationY,
                         prevX, prevY);
}

std::pair<double, double> GameObject::getPosition() const {
    return _position;
}

/*
 *      PROTECTED methods
 */

void GameObject::moveBehaviour(const double moveX, const double moveY)
{ /* To be extended by derived classes. */ }

void GameObject::setBehaviour(double moveX, double moveY, double prevX, double prevY)
{ /* To be extended by derived classes. */ }
