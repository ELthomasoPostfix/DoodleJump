//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "StaticBody.h"

/*
 *      PUBLIC methods
 */

StaticBody::StaticBody(const double positionX, const double positionY,
                       const Rect &shape, const bool isPhysical)
    : PhysicsBody(positionX, positionY, shape, isPhysical) {

}
