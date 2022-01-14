//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Jetpack.h"

/*
 *      PUBLIC methods
 */

Jetpack::Jetpack(Rect& rect, double totalBoost) : Bonus(rect) {
    _totalBoost = totalBoost;
}

void Jetpack::notifyCollision(Player &collidedWith, bool playerIsSupported) {

    if (collidedWith.getCollisionObject().checkCollision(this->getCollisionObject())) {
        getCollisionObject().setIsPhysical(false);      // Disable collisions generally

        collidedWith.addDownwardPullScale(0, _totalBoost);
        collidedWith.resetYVelocity();

        _active = true;
        updateScoreboard(getBaseScore());
        requestRemoval();
    }
}

void Jetpack::setTotalBoost(double totalBoost) {
    _totalBoost = totalBoost;
}
