//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "KinematicPlatform.h"

KinematicPlatform::~KinematicPlatform() {
    _physicsBody.reset();
}
