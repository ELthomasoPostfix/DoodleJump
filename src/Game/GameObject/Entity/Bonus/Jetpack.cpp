//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Jetpack.h"

/*
 *      PUBLIC methods
 */

Jetpack::Jetpack(Rect& rect, double totalBoost) : Bonus(rect) {
    _totalBoost = totalBoost;
    _currentBoost = 0;
}

void Jetpack::process(double delta) {
}

void Jetpack::notifyCollision(Player &collidedWith, bool playerIsSupported) {

    // The observable must have landed so that the spring would be stepped on.
    if (collidedWith.getCollisionObject().checkCollision(this->getCollisionObject())) {
        collidedWith.addDownwardPullScale(0, 2000);
        collidedWith.resetYVelocity();
        _active = true;
    }
    // TODO  somehow signal that jetpack should now die
}
