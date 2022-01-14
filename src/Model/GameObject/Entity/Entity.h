//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_ENTITY_H
#define DOODLEJUMP_ENTITY_H

#include "../../World/World.h"



//! The base class for all displayable objects.
/*!
 * The ::Entity class functions as an abstract base class for all objects that require
 * some form of view. It provides a display() method whose implementation can be found
 * in the ::TemplateView class of the MVC View component.
 *
 * \note The display() method forms a wrapper for the actual Observer notify call;
 * an entity view notifies the game through the game's display method.
 * \see ::TemplateView::display(), ::EntityView::notify(), ::Game::update
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

        //! Notify the caller of a collision between the passed player and the caller.
        virtual void notifyCollision(Player& collidedWith, bool playerIsSupported);

        //! Get the collision object representing the collision shape of the entity.
        /*!
         * Used for clipping if the entity has no view attached.
         * \see getClipObject(), ::TemplateView
         */
        CollisionObject& getCollisionObject();

        //! Get the collisionObject used to check whether or not the entity is visible to a ::Camera object.
        /*!
         * By default the collision object representing the collision shape will be used to
         * check visibility. However, if the object's actual class type is a ::TemplateView
         * specialization, then this method is overridden explicitly. This method will then
         * return its view area instead. This allows a clear separation between the manipulation
         * of the view shape and collision shape, which improves extensibility.
         * \see
         */
        virtual CollisionObject& getClipObject();

        //! The entry point for the ::World class to let a ::GameObject influence the game state.
        /*!
         * If a derived class desires to influence the game world every frame, then these
         * interactions should be implemented through deriving the process() method.
         * The ::World class will call the process() method of all ::Entity objects registered
         * using the ::World::addEntity() method.
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

        //! Set the base score an entity is worth in a point generating activity.
        /*!
         * If the score is not set explicitly, then it defaults to 100.
         */
        void setBaseScore(int score);

        //! Get the base score an entity is worth in a collision with the player.
        virtual int getBaseScore() const;

    protected:

        //! Check whether the world has received the requested event.
        /*!
        * This is a wrapper method for a public ::World method
        */
        static bool pollEvent(dj::Event event);

        //! Signal the world that the round needs to end.
        /*!
         * This is a wrapper method for a public ::World method.
         */
        static void signalRoundEnd();

        //! Request that the target be removed from the all world entity lists at the game's leisure.
        /*!
        * This is a wrapper method for a public ::World method.
        */
        void requestRemoval();

        //! Return collision info on all collisions with solid objects in the world.
        /*!
        * This is a wrapper method for a public ::World method.
        */
        std::vector<SolidCollisionInfo> getSolidCollisions(const std::pair<double, double>& moveDir);

        //! Return collision info on all collisions with non solid objects in the world.
        /*!
        * This is a wrapper method for a public ::World method.
        */
        std::vector<NonSolidCollisionInfo> getNonSolidCollisions();

        //! Notify the scoreboard of a change in score.
        void updateScoreboard(int score) const;

        //! Extend the move of the entity itself by also moving its collision shape.
        void moveBehaviour(double moveX, double moveY) override;

        //! Extend the position setting of the entity itself by also setting the position of its collision shape.
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
