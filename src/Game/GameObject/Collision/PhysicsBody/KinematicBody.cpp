//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "KinematicBody.h"
#include "../../../World/World.h"

/*
 *      PUBLIC methods
 */


KinematicBody::KinematicBody(const double positionX, const double positionY,
                             const Rect &shape, const bool isPhysical)
        : PhysicsBody(positionX, positionY, shape, isPhysical) {

}

bool KinematicBody::moveAndCollide(const std::pair<double, double> &moveVector) {

    // Perform movement
    move(moveVector);

    // Check all collisions between the moved object and all static and kinematic bodies.
    const std::vector<CollisionInfo> collInfo = {
            //std::move(World::getInstance()->getStaticCollisionInfo(*this, moveVector)),
            //std::move(World::getInstance()->getRigidCollisionInfo(*this, moveVector))
    };
    const auto pushbackVector =
            collInfo.at(Utility::getLongestVectorIndex({collInfo.at(0).pushback, collInfo.at(1).pushback})).pushback;

    // TODO  change velocity according to collision

    // No collisions that need pushback
    if (pushbackVector.first == 0 && pushbackVector.second == 0)
        return false;

    // Undo all collisions
    move(pushbackVector);
    return true;
}
