//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include <utility>

#include "PhysicsEngine.h"
#include "../World/Camera.h"
#include "../GameObject/Collision/PhysicsBody/StaticBody.h"
#include "../GameObject/Collision/PhysicsBody/KinematicBody.h"

class Entity;


//! Used to transmit info about a collision test requested through ::World.
struct CollisionInfo {
    CollisionInfo()
    : collidedWith(nullptr), pushback(0.0, 0.0), topCollision(false), sideCollision(false) {}

    CollisionInfo(std::shared_ptr<CollisionObject> cw, std::pair<double, double> pb, bool tc, bool sc)
    : collidedWith(std::move(cw)), pushback(std::move(pb)), topCollision(tc), sideCollision(sc) {}

    std::shared_ptr<CollisionObject> collidedWith;
    std::pair<double, double> pushback;
    bool topCollision;
    bool sideCollision;
};


class Camera;


// TODO   store Entity objects in layers? (bg layer, collision layer, ...)
class World {
    public:
        // TODO  return a std::unique_ptr<World> instead ???
        static std::unique_ptr<World>& getInstance();

        //! Call the process method of all registered ::Entity objects.
        /*!
         * Each ::Entity may define a ::Entity::process(double) method,
         * which allows it to influence the game state. These process methods
         * are called here for all objects registered using
         * ::World::addEntity().
         */
        void processRegisteredEntities(double delta);

        //! Set the gravity for ::RigidBody objects.
        bool setGravity(double gravity) const;

        //! Set the drag for ::RigidBody objects.
        bool setDrag(double drag) const;

        //! Resolves the physics step of the ::RigidBody objects.
        void processRigidBodies(double delta);

        //! Register any ::Entity derived class object, such that its ::Entity::process(double) method will be called.
        const std::shared_ptr<Entity> & addEntity(const std::shared_ptr<Entity> &entity);

        //! Removed a registered ::Entity. Its is effectively removed from the game world.
        bool removeEntity(const std::shared_ptr<Entity> &entity);

        // TODO  add constructor parameters
        const std::unique_ptr<KinematicBody>& addKinematicBody();

        // TODO  add constructor parameters
        const std::unique_ptr<RigidBody>& addRigidBody();

        // TODO  add constructor parameters
        const std::unique_ptr<StaticBody>& addStaticBody();

        //! Test for collision between the input ::CollisionObject and all ::KinematicBody objects in the world.
        /*!
         * The info returned will only describe the collision with the body that requires the
         * most pushback to undo, as this is probably the first collision that occurred.
         * \note NO collisions are ever predicted. We move the body and then check for collisions
         * afterward.
         * \param movingBody The body to check collisions for.
         * \param moveDir The direction that \p movingBody was traveling until we checked for collisions.
         */
        CollisionInfo
        getKinematicCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir);

        //! Test for collision between the input ::RigidBody and all ::KinematicBody and ::StaticBody objects in the world.
        /*!
         * The info returned will only describe the collision with the body that requires the
         * most pushback to undo, as this is probably the first collision that occurred.
         * \note NO collisions are ever predicted. We move the body and then check for collisions
         * afterward.
         * \param movingBody The body to check collisions for.
         * \param moveDir The direction that \p movingBody was traveling until we checked for collisions.
         */
        CollisionInfo
        getRigidCollisionInfo(RigidBody &movingBody, const std::pair<double, double> &moveDir);

        //! Test for collision between the input ::CollisionObject and all ::RigidBody objects in the world.
        /*!
         * The info returned will only describe the collision with the body that requires the
         * most pushback to undo, as this is probably the first collision that occurred.
         * \note NO collisions are ever predicted. We move the body and then check for collisions
         * afterward.
         * \param movingBody The body to check collisions for.
         * \param moveDir The direction that \p movingBody was traveling until we checked for collisions.
         */
        CollisionInfo
        getRigidCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir);

        //! Test for collision between the input ::CollisionObject and all ::StaticBody objects in the world.
        /*!
         * The info returned will only describe the collision with the body that requires the
         * most pushback to undo, as this is probably the first collision that occurred.
         * \note NO collisions are ever predicted. We move the body and then check for collisions
         * afterward.
         * \param movingBody The body to check collisions for.
         * \param moveDir The direction that \p movingBody was traveling until we checked for collisions.
         */
        CollisionInfo
        getStaticCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir);

    private:

        //! Test for collision between the input ::CollisionObject and all elements of otherObjects.
        /*!
         * The info returned will only describe the collision with the body that requires the
         * most pushback to undo, as this is probably the first collision that occurred.
         * \note NO collisions are ever predicted. We move the body and then check for collisions
         * afterward.
         * \param movingBody The body to check collisions for.
         * \param moveDir The direction that \p movingBody was traveling until we checked for collisions.
         * \param otherObjects The ::CollisionObject objects to check for collisions with.
         */
        template<class T>
        static CollisionInfo
        getCollisionInfo(CollisionObject &movingBody, const std::pair<double, double> &moveDir,
                         const std::vector<std::shared_ptr<T>>& otherObjects);


    private:
        std::unique_ptr<PhysicsEngine>& _physicsEngine;           // existence guaranteed by constructor
        std::unique_ptr<Camera> _camera;

        std::vector<std::shared_ptr<Entity>> _entities;

        std::vector<std::shared_ptr<KinematicBody>> _kinematicBodies;
        std::vector<std::shared_ptr<RigidBody>> _rigidBodies;
        std::vector<std::shared_ptr<StaticBody>> _staticBodies;

        World();
        World(World const&);              // don't implement
        World& operator= (World const&);  // don't implement


};


#endif //DOODLEJUMP_WORLD_H
