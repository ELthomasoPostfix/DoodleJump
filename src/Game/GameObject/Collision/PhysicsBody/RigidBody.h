//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_RIGIDBODY_H
#define DOODLEJUMP_RIGIDBODY_H

#include "PhysicsBody.h"

// TODO An implementation of the physics behaviour interface. A rigid body cannot be moved manually.
//  Forces can be integrated into the rigid body, which is then moved explicitly by the physics engine.

class PhysicsEngine;


//! A class modeling a ::CollisionObject that a user of the ::Game class can only influence by applying force to it, which is resolved by the ::Game class.
/*!
 * The ::RigidBody class represents an object capable of collisions, whose movement can only be influenced
 * by a user of the ::World class by applying force to it through the applyImpulse(const double[2])
 * method. The the movement of this object will then automatically be resolved each frame by applting the
 * physics step onto it through the ::PhysicsEngine object.
 * Creating an object of this class should occur through calling the ::World::createRigidBody() method.
 */
class RigidBody : public PhysicsBody {
    public:
        // TODO  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //  find good range of value for velocity to take !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //! Apply an impulse to the ::RigidBody, which is used by the ::PhysicsEngine to automatically move it.
        void applyImpulse(const std::pair<double, double> &velocity);     // TODO check use of override

    protected:
        friend World;
        friend PhysicsEngine;


        /*!
         * Restrict the use of the ::RigidBody constructor as a ::RigidBody
         * should be instanced by the ::World class as to ensure that it is
         * properly included in all game functionality.
         */
        RigidBody(double positionX, double positionY, const Rect &shape, bool isPhysical);


        double _velocity[2];
        bool _isSupported;

};


#endif //DOODLEJUMP_RIGIDBODY_H
