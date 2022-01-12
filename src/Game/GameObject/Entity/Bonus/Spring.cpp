//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Spring.h"

/*
 *      PUBLIC methods
 */

Spring::Spring(Rect& rect) : Bonus(rect) {

}

void Spring::process(double delta) {
}

void Spring::notifyCollision(Player &collidedWith, bool playerIsSupported) {
    if (!playerIsSupported)
        return;

    // The observable must have landed so that the spring would be stepped on.
    if (collidedWith.getCollisionObject().checkCollision(this->getCollisionObject()) &&
        collidedWith.getCollisionObject().isAsHighAs(this->getCollisionObject())) {
        getCollisionObject().setIsPhysical(false);      // Disable collisions generally

        collidedWith.addDownwardPullScale(.0f, collidedWith.getJumpHeight() * 4);

        _active = true;
        updateScoreboard(getBaseScore());
        requestRemoval();
    }

}
