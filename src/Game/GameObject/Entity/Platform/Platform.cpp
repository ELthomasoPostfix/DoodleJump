//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Platform.h"
#include "../Player/Player.h"

/*
 *      PUBLIC methods
 */

Platform::Platform(Rect &rect) : Entity(rect, true, true) {

}

void Platform::notifyCollision(Player &collidedWith, bool playerIsSupported) {
    if (collidedWith.getCollisionObject().checkCollision(getCollisionObject()) &&
        playerIsSupported) {
        handleCollision(collidedWith, playerIsSupported);
        // TODO  notify the Score that this platform has been jumped on
    }

}

void Platform::handleCollision(Player &collidedWith, bool playerIsSupported) {}
