//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_KINEMATICBODY_H
#define DOODLEJUMP_KINEMATICBODY_H

#include "PhysicsBody.h"


// TODO An implementation of the physics behaviour interface. A kinematic body is moved explicitly/
//  moved manually and not through the physics engine.

//! A class modeling a ::CollisionObject moves by being explicitly manipulated by a user of the ::Game class.
/*!
 * The ::KinematicBody class represents an object capable of collisions, which must be manipulated directly
 * through altering its position using the movement functions inherited from ::GameObject. It provides
 * additional functionality to interact with the other physics bodies present in the game world.
 * Creating an object of this class should occur through calling the ::World::createKinematicBody() method.
 */
class KinematicBody : public PhysicsBody {
    public:
        // TODO  This not the case anymore. A extender of the game can now have such bodies in their
        //          process function, which is deemed more beneficial (why exactly??).
        /*!
         * Restrict the use of the ::KinematicBody constructor as a ::KinematicBody
         * should be instanced by the ::World class as to ensure that it is
         * properly included in all game functionality.
         */
        KinematicBody(double positionX, double positionY, const Rect &shape, bool isPhysical);

        ~KinematicBody() override = default;

        bool moveAndCollide(const std::pair<double, double> &moveVector);


    private:
        double collisionMargin;

};


#endif //DOODLEJUMP_KINEMATICBODY_H
