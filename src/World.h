//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include <utility>

#include "PhysicsEngine.h"
#include "Collision/PhysicsBody/StaticBody.h"
#include "Collision/PhysicsBody/KinematicBody.h"


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


// TODO   store Entity objects in layers? (bg layer, collision layer, ...)
class World {
    public:
        // TODO  return a std::unique_ptr<World> instead ???
        static World* getInstance();

        //! Register the ::Entity object so that its ::GameObject::process(double) method will be called.
        void registerGameObject(const std::shared_ptr<GameObject>& gameObject);

        //! Call the process method of all registered ::GameObject objects.
        /*!
         * Each ::GameObject may define a ::GameObject::process(double) method,
         * which allows ot to influence the game state. These process methods
         * are called here for all objects registered using registerGameObject().
         */
        void processRegisteredGameObjects(double delta);

        //! Set the gravity for ::RigidBody objects.
        bool setGravity(double gravity) const;

        //! Set the drag for ::RigidBody objects.
        bool setDrag(double drag) const;

        //! Resolves the physics step of the ::RigidBody objects.
        void processRigidBodies(double delta);


        // TODO  add constructor parameters
        std::shared_ptr<KinematicBody> createKinematicBody();

        // TODO  add constructor parameters
        std::shared_ptr<RigidBody> createRigidBody();

        // TODO  add constructor parameters
        std::shared_ptr<StaticBody> createStaticBody();

    protected:
        friend PhysicsEngine;
        friend KinematicBody;


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
        getKinematicCollisionPushback(CollisionObject &movingBody, const std::pair<double, double> &moveDir);

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
        getRigidCollisionPushback(RigidBody &movingBody, const std::pair<double, double> &moveDir);

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
        getRigidCollisionPushback(CollisionObject &movingBody, const std::pair<double, double> &moveDir);

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
        getStaticCollisionPushback(CollisionObject &movingBody, const std::pair<double, double> &moveDir);

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
        getCollisionPushback(CollisionObject &movingBody, const std::pair<double, double> &moveDir,
                             const std::vector<std::shared_ptr<T>>& otherObjects);


    private:
        std::unique_ptr<PhysicsEngine> _physicsEngine;           // existence guaranteed by constructor

        std::vector<std::shared_ptr<GameObject>> _registeredObjects;

        std::vector<std::shared_ptr<KinematicBody>> _kinematicBodies;
        std::vector<std::shared_ptr<RigidBody>> _rigidBodies;
        std::vector<std::shared_ptr<StaticBody>> _staticBodies;

        World();
        World(World const&);              // don't implement
        World& operator= (World const&);  // don't implement


};


#endif //DOODLEJUMP_WORLD_H
