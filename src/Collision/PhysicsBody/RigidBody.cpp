//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "RigidBody.h"

/*
 *      PUBLIC methods
 */

void RigidBody::applyImpulse(const std::pair<double, double> &velocity) {
    this->_velocity[0] += velocity.first;
    this->_velocity[1] += velocity.second;
}



/*
 *      PROTECTED methods
 */

RigidBody::RigidBody(const double positionX, const double positionY,
                     const Rect &shape, const bool isPhysical)
    : PhysicsBody(positionX, positionY, shape, isPhysical), _isSupported(false) {}

