//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PHYSICSBODY_H
#define DOODLEJUMP_PHYSICSBODY_H

#include "../CollisionObject.h"

// TODO An interface that represents all types of physics behaviour
//  an entity could adopt (Head First Design Patterns p-13)

class PhysicsBody : public CollisionObject {
public:
    PhysicsBody(double positionX, double positionY, const Rect &shape, bool isPhysical);

    ~PhysicsBody() override = default;

    // TODO Use a bodyType field (enum)???
    //  Or dynamic_cast (lecture 15/11/2021)???



};


#endif //DOODLEJUMP_PHYSICSBODY_H
