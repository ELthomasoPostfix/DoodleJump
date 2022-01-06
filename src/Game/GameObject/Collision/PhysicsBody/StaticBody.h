//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_STATICBODY_H
#define DOODLEJUMP_STATICBODY_H

#include "PhysicsBody.h"

// TODO An implementation of the physics behaviour interface. A static body should never move through
//  manipulation by user of the ::Game class.


//! A class modeling a ::CollisionObject that never moves after initial placement.
/*!
 * The ::StaticBody class represents an object capable of collisions, which never moves after
 * its initial placement.
 * Creating an object of this class should occur through calling the ::World::createStaticBody() method.
 */
class StaticBody : public PhysicsBody {
    protected:

        /*!
         * Restrict the use of the ::StaticBody constructor as a ::StaticBody
         * should be instanced by the ::World class as to ensure that it is
         * properly included in all game functionality.
         */
        StaticBody(double positionX, double positionY, const Rect &shape, bool isPhysical);

        /*!
         * Restrict the use of ::GameObject::move(double, double) and ::GameObject::move(const std::pair<double,double>&)
         * methods as a ::StaticBody may only be positioned by the ::World class.
         */
        using GameObject::move;

        /*!
         * Restrict the use of ::GameObject::setPosition(double, double)
         * methods as a ::StaticBody may only be positioned by the ::World class.
         */
        using GameObject::setPosition;

    private:
        double constantForce[2];

};


#endif //DOODLEJUMP_STATICBODY_H
