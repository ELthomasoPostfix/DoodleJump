//
// Created by Thomas Gueutal on 11/01/2022.
//

#include "TemporaryPlatform.h"

TemporaryPlatform::TemporaryPlatform(Rect &rect) : Platform(rect) {

}

void TemporaryPlatform::handleCollision(Player& collidedWith, bool playerIsSupported) {
    requestRemoval();
}
