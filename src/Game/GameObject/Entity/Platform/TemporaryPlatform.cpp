//
// Created by elthomaso on 11/01/2022.
//

#include "TemporaryPlatform.h"

TemporaryPlatform::TemporaryPlatform(Rect &rect) : Platform(rect) {

}

void TemporaryPlatform::handleCollision(Player& collidedWith, bool playerIsSupported) {
    // TODO  somehow signal that this platform should die
}
