//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "PhysicsEngine.h"

/*
 *      PUBLIC methods
 */

std::unique_ptr<PhysicsEngine>& PhysicsEngine::getInstance() {
    static std::unique_ptr<PhysicsEngine> engine(new PhysicsEngine);
    return engine;
}



std::pair<double, double>
PhysicsEngine::calculateMovement(double delta, std::shared_ptr<RigidBody>& rb,
                                 bool applyForces) const {
    try {
        // TODO based on gravity/drag and rb->appliedForce, calculate
        //  the distance moved and modify the remaining rb->appliedForce.
        //  Then apply this distance to the Entity.

        // TODO Don't forget to cap speed at terminal velocity?

        // TODO make drag influence exponential in function of speed
        //  To implement the exponential decrease, first notice that 1/2 * a * t^2
        //  is the integral of at. To make drag exponential, make a exponential (e.g. a^2)?????


        const double dragDir = rb->_velocity[0] == 0 ? 0 : -(rb->_velocity[0] / std::abs(rb->_velocity[0])); // drag dir is opposite of move dir
        const double physInfluence[2] = {dragDir * drag,
                                         - gravity * static_cast<double>(rb->_isSupported)};


        double stopDelta = dragDir == 0 ? 0 : - (rb->_velocity[0] / physInfluence[0]);     // time to full stop knowing v0 and drag (always pos)
        if (delta < stopDelta) stopDelta = delta;


        const double moveDistance[2] = {rb->_velocity[0] * stopDelta,   // clamp x-drag slowdown to full stop
                                        rb->_velocity[1] * delta};
        // a*t
        const double decelSpeed[2] = {physInfluence[0] * stopDelta,
                                      physInfluence[1] * delta};
        // (1/2)*v*t = (1/2)*a*t²
        const double decelDistance[2] = {0.5 * decelSpeed[0] * stopDelta,
                                         0.5 * decelSpeed[1] * delta};

        // rf = r0 + vt + (1⁄2)at²
        const std::pair<double, double> movement {
                0.0 + moveDistance[0] + decelDistance[0],
                0.0 + moveDistance[1] + decelDistance[1]
        };

        if (applyForces) {
            rb->_velocity[0] += decelSpeed[0];        // decel[0] at most reduces rb->velocity[0] to 0 (doesn't overshoot)
            rb->_velocity[1] += decelSpeed[1];
            // TODO clamp these values at all??
            // TODO clamp these values at all??
            // TODO clamp these values at all??
        }

        return movement;


    } catch (std::exception& e) {
        throw;      // TODO  handle div-by-0 exception from this->drag == 0 OR dragDir == 0
    }
}


/*
 *      getters and setters
 */


bool PhysicsEngine::setGravity(const double grav) {
    if (grav < 1.0) return false;

    this->gravity = grav;
    return true;
}

double PhysicsEngine::getGravity() const {
    return gravity;
}

bool PhysicsEngine::setDrag(const double dr) {
    if (dr < 1.0) return false;

    this->drag = dr;
    return true;
}

double PhysicsEngine::getDrag() const {
    return drag;
}


/*
 *      PRIVATE methods
 */


PhysicsEngine::PhysicsEngine() : gravity(1), drag(1), rigidCollisionPush(1) {}
