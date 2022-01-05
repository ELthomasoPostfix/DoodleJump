//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(double positionX, double positionY, const Rect &shape, bool isPhysical) : CollisionObject(
        shape, isPhysical) {}