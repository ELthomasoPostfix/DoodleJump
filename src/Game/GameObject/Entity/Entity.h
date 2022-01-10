//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_ENTITY_H
#define DOODLEJUMP_ENTITY_H

#include "../../World/World.h"



//! The base class for all displayable objects.
/*!
 * The ::Entity class functions as an abstract base class for all objects that require
 * some form of view. It provides a display() method that allows a different display
 * implementation for different types of displayable objects.
 */
class Entity : public GameObject {
    public:
        explicit Entity(Rect& rect);

        Entity(double positionX, double positionY);

        ~Entity() override = default;

        //! Notify the ::Game class object, that this object is ready to be displayed.
        /*!
         * \note The ::Game object functions as a controller in the MVC design,
         * and the ::World, the Model, is not allowed to know about the View.
         * Thus, we apply an Observer pattern with a ::ViewEntity as an observable
         * and the game object as the observer. This way, the controller may
         * request the model to supply the ::EntityView objects to draw onto the View.
         * This will be done by letting the to draw objects leverage the observer
         * pattern to present themselves to the controller.
         */
        virtual void display();

        //! Get the collision object representing the collision shape of the entity.
        CollisionObject& getCollisionObject();

        //! Get the collisionObject used to check whether or not the entity is visible to a ::Camera object.
        /*!
         * By default the collision object representing the collision shape will be used to
         * check visibility. However, if the object's actual class type is a ::EntityView
         * derivative, then this method can be overridden explicitly in that derived class
         * definition to utilize its view area instead. This behaviour is not included by default,
         * but must be expressed in the derived view classes.
         * Still, this allows a degree of combustibility of when the ::Entity is actually removed from the world by the associated camera.
         */
        virtual CollisionObject& getClipObject();

        // TODO  Extract this behaviour into a Spawnable superclass?
        //  ==> GameObject --> Spawnable --> Entity  ???
        //! The entry point for the ::World class to let a ::GameObject influence the game state.
        /*!
         * If a derived class desires to influence the game world every frame, then these
         * interactions should be implemented through deriving the process() method.
         * The ::World class will call the process() method of all registered ::GameObject objects.
         * \param delta How many seconds have passed since the previous frame was ready.
         * \todo Extract the ::Entity process behaviour into a 'Processable' object for extensibility.
         */
        virtual void process(double delta);

        // TODO  Return a vector of collided with objects??
        // TODO  If collision is detected, then a bonus should apply to an entity/Player
        //  ==> Bonus checks collision, then asks the world is it is a player??
        //  ==> observer like logic to register a Player& to each bonus??? And
        //  ==> if the bonus finds collision with the player, then they can apply a boost
        //  ==> Generalized for Bonus and Player classes
        //! Check whether the entity has collided with anything in the world.
        CollisionInfo checkCollision(const std::pair<double, double>& moveDir);

        //! Signal the world that the round needs to end.
        void signalRoundEnd() const;

    protected:

        //! Augment the move of the entity itself by also moving its collision shape.
        void moveBehaviour(double moveX, double moveY) override;

        //! Augment the move of the entity itself by also moving its collision shape.
        void setBehaviour(double moveX, double moveY, double prevX, double prevY) override;


    private:
        //! In this game all viewable objects have a need for collision.
        /*!
         * \todo Extract the ::Entity collision behaviour into a 'Collideable' object for extensibility.
         */
        CollisionObject _collisionObject;
};


#endif //DOODLEJUMP_ENTITY_H
