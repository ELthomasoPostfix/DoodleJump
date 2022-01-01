//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_ENTITY_H
#define DOODLEJUMP_ENTITY_H

#include "../GameObject.h"
// TODO  #include "../Collision/PhysicsBody/PhysicsBody.h"

//! The base class for all displayable objects.
/*! The Entity class functions as an abstract base class for all objects that require
 * some form of view. It provides a display function that allows a different display
 * implementation for different types of displayable objects.
 */
class Entity : public GameObject {
public:
    Entity(double positionX, double positionY);

    virtual void display() = 0;
};


#endif //DOODLEJUMP_ENTITY_H
