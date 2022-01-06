//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_ENTITY_H
#define DOODLEJUMP_ENTITY_H

#include <utility>
#include <memory>
#include "../View/View.h"
#include "../../World/World.h"


static const std::unique_ptr<World>& getInstance();


// TODO  #include "../Collision/PhysicsBody/PhysicsBody.h"

//! The base class for all displayable objects.
/*!
 * The ::Entity class functions as an abstract base class for all objects that require
 * some form of view. It provides a display() method that allows a different display
 * implementation for different types of displayable objects.
 */
class Entity : public GameObject {
    public:
        Entity(double positionX, double positionY);

        // TODO  make pure virtual again
        virtual void display() {};

        View& getView();

        // TODO  Extract this behaviour into a Spawnable superclass?
        //  ==> GameObject --> Spawnable --> Entity  ???
        //! The entry point for the ::World class to let a ::GameObject influence the game state.
        /*!
         * If a derived class desires to influence the game world every frame, then these
         * interactions should be implemented through deriving the process() method.
         * The ::World class will call the process() method of all registered ::GameObject objects,
         * after it has performed its physics step on the ::RigidBody objects.
         * \param delta How many seconds have passed since the previous frame was ready.
         */
        virtual void process(double delta);

        // TODO    support/ensure \return claim "Ownership remains with the ::World object"
        //! Register a derived ::Entity class object in the ::World object so that its process function will be called.
        /*!
         * \param entity The ::Entity derived class to register.
         * \return A reference to the registered object. Ownership remains with the ::World object.
         * \note This template allows for any ::Entity derived class object
         * to be registered in the ::World object, without the person extending
         * the game to need to worry about writing code to integrate their
         * classes with the current ::World implementation, nor for them
         * to need to edit the existing ::World code.
         */
        template<class DerivedEntity>
        const std::unique_ptr<DerivedEntity>&
        registerEntity(const std::unique_ptr<DerivedEntity>& entity);

        // TODO  If ::PhysicsBody is deprecated, then this comment needs to be edited
        //  ==> decide whether to keep ::PhysicsBody
        //! Register a derived ::PhysicsBody class object in the ::World object so that it may be used in collisions.
        /*!
         * \param physBody The ::PhysicsBody derived class to register.
         * \return A reference to the registered object. Ownership remains with the ::World object.
         * \note This template allows for any ::PhysicsBody derived class object
         * to be registered in the ::World object, without the person extending
         * the game to need to call creator methods for each object. This way, they
         * may still have instances of the ::PhysicsBody derived classes in their
         * code for whatever reason. If such an object is to be used in collisions,
         * however, then it must be registered and ownership of it is transferred.
         */
        template<class DerivedPhysicsBody>
        const std::unique_ptr<DerivedPhysicsBody>&
        registerCollisionBody(const std::unique_ptr<DerivedPhysicsBody>& physBody);


    protected:
        View _view;

};

template<class DerivedEntity>
const std::unique_ptr<DerivedEntity>&
Entity::registerEntity(const std::unique_ptr<DerivedEntity>& entity) {
    const std::unique_ptr<World>& world = World::getInstance();
    //world->addEntity(entity);
    return entity;
}

template<class DerivedPhysicsBody>
const std::unique_ptr<DerivedPhysicsBody>&
Entity::registerCollisionBody(const std::unique_ptr<DerivedPhysicsBody>& physBody) {
    return physBody;
}



#endif //DOODLEJUMP_ENTITY_H
