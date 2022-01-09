//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PHYSICSENGINE_H
#define DOODLEJUMP_PHYSICSENGINE_H


#include "../GameObject/Collision/PhysicsBody/RigidBody.h"


class World;

class PhysicsEngine {
    public:
        // TODO  return a std::unique_ptr<PhysicsEngine> instead ???
        static std::unique_ptr<PhysicsEngine>& getInstance();

        std::pair<double, double> calculateMovement(double delta, std::shared_ptr<RigidBody>& rb,
                                                    bool applyForces = false) const;

        /*
         *      getters and setters
         */

        bool setGravity(double gravity);
        double getGravity() const;
        bool setDrag(double drag);
        double getDrag() const;

    private:
        double gravity;     // vertical acc/deceleration,   always pos
        double drag;        // horizontal deceleration, always pos
        double rigidCollisionPush;

        PhysicsEngine();
        PhysicsEngine(PhysicsEngine const&) = default;              // don't implement
        PhysicsEngine& operator= (PhysicsEngine const&) = default;  // don't implement

};


#endif //DOODLEJUMP_PHYSICSENGINE_H
