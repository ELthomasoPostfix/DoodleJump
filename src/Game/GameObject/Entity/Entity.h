//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_ENTITY_H
#define DOODLEJUMP_ENTITY_H

#include <utility>
#include <memory>
#include "../View/EntityView.h"
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
        // TODO    Access the ViewFactory of ::World and attach the correct View
        //          in the constructor of ::Entity. This way there is never a
        //          need to add more creator methods.
        Entity(double positionX, double positionY);

        ~Entity() override = default;

        virtual void display() = 0;

        EntityView& getView();

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

        //! Register a derived ::Entity class object in the ::World object so that its process function will be called.
        /*!
         * The registered ::Entity derived class will be managed by both the ::World and caller classes.
         * This way the caller may exploit the functionality offered by the ::World interface to glean
         * information about the ::Game state and thus influence it through the process(double) method.
         * \param entity The ::Entity derived class to register.
         * \return Whether or not the \p entity was already registered.
         * \note There is much less danger of memory leaks of entities due to the use of shared pointers
         * by both the caller and the ::World if the a Entity is to be registered. Any memory leaks due
         * to new declarations in the process method are unhandled by the game logic.
         */
        bool registerEntity(const std::shared_ptr<Entity>& entity);
        bool unregisterEntity(const std::shared_ptr<Entity>& entity);

        // TODO  If ::PhysicsBody is deprecated, then this comment needs to be edited
        //  ==> decide whether to keep ::PhysicsBody
        //! Register a derived ::PhysicsBody class object in the ::World object so that it may be used in collisions.
        /*!
         * This template allows for any ::PhysicsBody derived class object
         * to be registered in the ::World object. This way, extenders of the game
         * may still have unregistered instances of the ::PhysicsBody derived classes in their
         * code which allows reuse of the existing code base. If such an object is
         * to be implicitly used in collisions, however, then it must be registered.
         * Dual ownership of the object then exists between the ::World object and the caller.
         * \param physBody The ::PhysicsBody derived class to register.
         * \note Registration of additional derivations of ::PhysicsBody is not possible,
         * as these objects are not stored generically as a ::PhysicsBody object in ::World,
         * as their interfaces must be accessible by ::World.
         * (This may be solved by storing the derived class objects in a templated vector???)
         */
        template<class DerivedPhysicsBody>
        bool registerPhysicsBody(const std::shared_ptr<DerivedPhysicsBody>& physBody);
        template<class DerivedPhysicsBody>
        bool unregisterPhysicsBody(const std::shared_ptr<DerivedPhysicsBody>& physBody);


    protected:
        EntityView _view;

};

template<class DerivedPhysicsBody>
bool Entity::registerPhysicsBody(const std::shared_ptr<DerivedPhysicsBody>& physBody) {
    // Compile-time sanity check
    static_assert(std::is_base_of<PhysicsBody, DerivedPhysicsBody>::value,
            "A to register PhysicsBody must derived from PhysicsBody");
    return World::getInstance()->addPhysicsBody(physBody);
}

template<class DerivedPhysicsBody>
bool Entity::unregisterPhysicsBody(const std::shared_ptr<DerivedPhysicsBody>& physBody) {
    // Compile-time sanity check
    static_assert(std::is_base_of<PhysicsBody, DerivedPhysicsBody>::value,
            "A to unregister PhysicsBody must derived from PhysicsBody");
    return World::getInstance()->removePhysicsBody(physBody);
}


#endif //DOODLEJUMP_ENTITY_H
