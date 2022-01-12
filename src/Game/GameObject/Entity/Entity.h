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
        explicit Entity(Rect &collRect, bool isPhysical, bool isSolid);

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

        //! Signal a collision between the player and the caller to the caller.
        virtual void notifyCollision(Player& collidedWith, bool playerIsSupported);

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

        //! The entry point for the ::World class to let a ::GameObject influence the game state.
        /*!
         * If a derived class desires to influence the game world every frame, then these
         * interactions should be implemented through deriving the process() method.
         * The ::World class will call the process() method of all ::Entity objects registered
         * using the ::World::registerEntity() method.
         * \param delta How many seconds have passed since the previous frame was ready.
         * \todo Extract the ::Entity process behaviour into a 'Processable' object for extensibility.
         */
        virtual void process(double delta);

        //! Register the scoreboard observer for the entity to update.
        /*!
         * \note The entity supports only a <b>single</b> observer.
         * registering an observer overwrites the previous one.
         */
        void registerScoreboardObserver(const std::shared_ptr<Scoreboard>& scoreboard);

        //! Unregister the scoreboard observer of the entity.
        /*!
         * \note The entity supports only a <b>single</b> observer.
         * The observer is uninitialized by default.
         */
        void unregisterScoreboardObserver();

        //! Set the base score an entity is worth in a collision with the player.
        /*!
         * If the score is not set explicitly, then it defaults to 100.
         */
        void setBaseScore(int score);

        //! Get the base score an entity is worth in a collision with the player.
        virtual int getBaseScore() const;

    protected:

        //! Check whether the world has received the requested event.
        static bool pollEvent(dj::Event event);

        //! Signal the world that the round needs to end.
        static void signalRoundEnd();

        //! Request that the target be removed from the all world entity lists at the game's leisure.
        void requestRemoval();

        //! Return collision info on all collisions with solid objects in the world.
        std::vector<SolidCollisionInfo> getSolidCollisions(const std::pair<double, double>& moveDir);

        //! Return collision info on all collisions with non solid objects in the world.
        std::vector<NonSolidCollisionInfo> getNonSolidCollisions();

        //! Notify the scoreboard of a change in score.
        void updateScoreboard(int score) const;

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
        int _baseScore;
        std::shared_ptr<Scoreboard> observer;
};


#endif //DOODLEJUMP_ENTITY_H
