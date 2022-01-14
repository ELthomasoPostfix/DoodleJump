//
// Created by Thomas Gueutal on 09/01/2022.
//

#ifndef DOODLEJUMP_COLLISIONINFO_H
#define DOODLEJUMP_COLLISIONINFO_H

#include "../../Utility/Utility.h"

class Entity;

//! Used to transmit info about a collision test against non-solid entities requested through ::World.
struct NonSolidCollisionInfo {
    NonSolidCollisionInfo()
            : collidedWith(nullptr){}

    explicit NonSolidCollisionInfo(std::shared_ptr<Entity> cw)
        : collidedWith(std::move(cw)) {}

    std::shared_ptr<Entity> collidedWith;

};

//! Used to transmit info about a collision test against solid entities requested through ::World.
struct SolidCollisionInfo : public NonSolidCollisionInfo {
    SolidCollisionInfo()
        : NonSolidCollisionInfo(), pushback(0.0, 0.0), topCollision(false), sideCollision(false) {}

    SolidCollisionInfo(std::shared_ptr<Entity> cw, std::pair<double, double> pb, bool tc, bool sc)
        : NonSolidCollisionInfo(std::move(cw)),  pushback(std::move(pb)),  topCollision(tc), sideCollision(sc) {}

    std::pair<double, double> pushback;
    bool topCollision;
    bool sideCollision;
};

#endif //DOODLEJUMP_COLLISIONINFO_H
