//
// Created by Thomas Gueutal on 13/11/2021.
//

#include "World.h"
#include "../GameObject/Entity/Entity.h"


/*
 *      PUBLIC methods
 */

std::unique_ptr<World>& World::getInstance() {
    static std::unique_ptr<World> world(new World);
    return world;
}

void World::processRegisteredEntities(const double delta) {

    for (const auto& go : _entities) {
        go->process(delta);
    }
}

bool World::setGravity(double gravity) const {
    if (gravity < 1) return false;

    _physicsEngine->setGravity(gravity);
    return true;
}

bool World::setDrag(double drag) const {
    if (drag < 1) return false;

    _physicsEngine->setDrag(drag);
    return true;
}

void World::processRigidBodies(const double delta) {
    std::vector<std::shared_ptr<RigidBody>> physicalRigidBodies;
    std::vector<std::pair<double, double>> vectors;

    for (auto& rb : _rigidBodies) {
        // TODO 2) sift by isPhysical()
        // If body DOES participate in collisions, then process it further
        if (rb->isPhysical())
            physicalRigidBodies.emplace_back(rb);
        // TODO Currently when a RigidBody collides, it loses it still loses the force
        //  spent traveling the pushback vector. This needs to be refunded: applyForces = false
        //  and calculate the time delta spent on reaching the non-collision state
        //  --> applyForce(loweredDelta)
        //  Also, split movement into a movement that depletes x-coordinate and the rest of the
        //  delta that remains.
        rb->move(_physicsEngine->calculateMovement(delta, rb));
    }

    // TODO 3) per phys rb, find sb and kb collisions
    //  ==> calc pushback
    for (auto& rb : physicalRigidBodies) {
        CollisionInfo info = std::move(getRigidCollisionInfo(*rb, {rb->_velocity[0], rb->_velocity[1]}));

        if (info.collidedWith == nullptr)
            continue;

        // y-velocity = 0 if rb on top of physical sb or kb
        rb->move(info.pushback);
        if (info.topCollision) {
            rb->_isSupported = true;
            rb->_velocity[1] = 0.0;
        }

        if (info.sideCollision)
            rb->_velocity[0] = 0.0;
    }

    // If the two rigid bodies intersect, then let them push each other away
    for (auto& rb : physicalRigidBodies) {
        for (auto& other : physicalRigidBodies) {
            if (rb != other && rb->checkCollision(*other)) {
                std::pair<double, double> rbc =
                        CollisionObject::determineAbsoluteCenterOfMass(rb->getCollisionShape());
                std::pair<double, double> oc =
                        CollisionObject::determineAbsoluteCenterOfMass(rb->getCollisionShape());
                std::pair<double, double> separationForce{oc.first - rbc.first, oc.second - rbc.second};
                // normalize
                separationForce.first = std::abs(separationForce.first) / separationForce.first;
                separationForce.second = std::abs(separationForce.second) / separationForce.second;

                other->applyImpulse(separationForce);
            }
        }
    }


    // TODO  ApplyForces with delta remaining after applying moveVec? We
    //  currently ignore the delta that needs to be refunded after the pushback

}





/*
 *      PROTECTED methods
 */

bool World::addEntity(const std::shared_ptr<Entity>& entity) {
    auto it = std::find(_entities.begin(), _entities.end(), entity);

    if (it != _entities.end() && &(**it) == &(*entity))
        return false;

    _entities.emplace_back(entity);
    return true;
}

bool World::removeEntity(const std::shared_ptr<Entity> &entity) {
    auto it = std::find(_entities.begin(), _entities.end(), entity);

    if (it != _entities.end() && &(**it) == &(*entity)) {
        _entities.erase(it);
        return true;
    }

    return false;
}

bool World::addPhysicsBody(const std::shared_ptr<KinematicBody> &physicsBody) {
    return addPhysicsBody(physicsBody, _kinematicBodies);
}

bool World::addPhysicsBody(const std::shared_ptr<RigidBody> &physicsBody) {
    return addPhysicsBody(physicsBody, _rigidBodies);
}

bool World::addPhysicsBody(const std::shared_ptr<StaticBody> &physicsBody) {
    return addPhysicsBody(physicsBody, _staticBodies);
}

bool World::removePhysicsBody(const std::shared_ptr<KinematicBody> &physicsBody) {
    return removePhysicsBody(physicsBody, _kinematicBodies);
}

bool World::removePhysicsBody(const std::shared_ptr<RigidBody> &physicsBody) {
    return removePhysicsBody(physicsBody, _rigidBodies);
}

bool World::removePhysicsBody(const std::shared_ptr<StaticBody> &physicsBody) {
    return removePhysicsBody(physicsBody, _staticBodies);
}

CollisionInfo
World::getKinematicCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir) {
    return std::move(getCollisionInfo(movingBody, moveDir, _kinematicBodies));
}

CollisionInfo
World::getRigidCollisionInfo(RigidBody &movingBody, const std::pair<double, double> &moveDir) {
    const std::vector<CollisionInfo> pbVecs = {
            std::move(getStaticCollisionInfo(movingBody, moveDir)),
            std::move(getKinematicCollisionInfo(movingBody, moveDir))
    };

    return pbVecs.at(Utility::getLongestVectorIndex({pbVecs.at(0).pushback, pbVecs.at(1).pushback}));
}

CollisionInfo
World::getRigidCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir) {
    return std::move(getCollisionInfo(movingBody, moveDir, _rigidBodies));
}

CollisionInfo
World::getStaticCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir) {
    return std::move(getCollisionInfo(movingBody, moveDir, _staticBodies));
}



/*
 *      PRIVATE methods
 */


World::World() : _physicsEngine(PhysicsEngine::getInstance()) {}

template<class PBody>
bool
World::addPhysicsBody(const std::shared_ptr<PBody>& pBody,
                      std::vector<std::shared_ptr<PBody>>& otherObjects) {
    auto it = std::find(otherObjects.begin(), otherObjects.end(), pBody);

    if (it != otherObjects.end() && &(**it) == &(*pBody))
        return false;

    otherObjects.emplace_back(pBody);
    return true;
}

template<class PBody>
bool World::removePhysicsBody(const std::shared_ptr<PBody>& pBody,
                              std::vector<std::shared_ptr<PBody>>& otherObjects) {
    auto it = std::find(otherObjects.begin(), otherObjects.end(), pBody);

    if (it != otherObjects.end() && &(**it) == &(*pBody)) {
        otherObjects.erase(it);
        return true;
    }

    return false;
}

template<class PBody>
CollisionInfo
World::getCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir,
                        const std::vector<std::shared_ptr<PBody>>& otherObjects) {

    std::vector<std::pair<double, double>> pushbackVectors;

    // TODO Wrap checkCollision() and determinePushback() into a getCollisionInfo method?
    //  Also think about difference between getCollisionInfo() and getCollisionsInfo().
    for (const auto& other : otherObjects) {
        if (movingBody.checkCollision(*other)) {
            auto pushback = movingBody.determinePushback(moveDir, *other);

            // Pushback is valid
            if (pushback.first != 0.0 && pushback.second != 0.0)
                pushbackVectors.emplace_back(pushback);
        }
    }

    if (pushbackVectors.empty())
        return CollisionInfo{};

    // TODO  return some kind of informational struct/dataclass instead (which still contains the pushback vectors)????
    // All pushback vectors have the same direction,
    // so the largest pushback will undo all collisions.
    unsigned int index = Utility::getLongestVectorIndex(pushbackVectors);

    CollisionInfo result;
    result.collidedWith = otherObjects.at(index);
    result.pushback = pushbackVectors.at(index);
    result.topCollision = movingBody.isAbove(*result.collidedWith);
    result.sideCollision = !result.topCollision;
    return result;
}
