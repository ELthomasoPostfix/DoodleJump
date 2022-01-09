//
// Created by Thomas Gueutal on 09/01/2022.
//

#ifndef DOODLEJUMP_COLLISIONINFO_H
#define DOODLEJUMP_COLLISIONINFO_H

#include "../../Utility/Utility.h"

class Entity;

//! Used to transmit info about a collision test requested through ::World.
struct CollisionInfo {
    CollisionInfo()
            : collidedWith(nullptr), pushback(0.0, 0.0), topCollision(false), sideCollision(false) {}

    CollisionInfo(std::shared_ptr<Entity> cw, std::pair<double, double> pb, bool tc, bool sc)
            : collidedWith(std::move(cw)), pushback(std::move(pb)), topCollision(tc), sideCollision(sc) {}

    std::shared_ptr<Entity> collidedWith;
    std::pair<double, double> pushback;
    bool topCollision;
    bool sideCollision;
};

#endif //DOODLEJUMP_COLLISIONINFO_H
