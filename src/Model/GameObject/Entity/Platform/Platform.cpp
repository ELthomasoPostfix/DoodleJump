//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "Platform.h"
#include "../Player/Player.h"

/*
 *      PUBLIC methods
 */

Platform::Platform(Rect &rect) : Entity(rect, true, true) {
    jumpCount = 0;
}

void Platform::notifyCollision(Player &collidedWith, bool playerIsSupported) {
    updateScoreboard(getBaseScore() * static_cast<int>(jumpOn()));
    handleCollision(collidedWith, playerIsSupported);
}

void Platform::handleCollision(Player &collidedWith, bool playerIsSupported) {}

unsigned int Platform::jumpOn() {
    return jumpCount++;
}
