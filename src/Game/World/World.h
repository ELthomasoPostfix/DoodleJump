//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include "Camera.h"
#include "Spawner.h"
#include "CollisionInfo.h"
#include "../../Event.h"
#include "../../Utility/Random.h"

#include <map>


class Entity;
class Player;
class AbstractEntityFactory;




class World {
    public:
        static std::unique_ptr<World>& getInstance();

        // TODO  add some random public method to already test stuff pls !!!!!!!!!!!!!!!!!!!!!!
        void test();
        // TODO  add some random public method to already test stuff pls !!!!!!!!!!!!!!!!!!!!!!

        //! Call the process method of all registered ::Entity objects.
        /*!
         * Each ::Entity may define a ::Entity::process(double) method,
         * which allows it to influence the game state. These process methods
         * are called here for all objects registered using
         * ::World::addEntity().
         */
        void processEntities(double delta);

        //! Register the event with the world so that it can integrate it with its entities.
        void pushEvent(dj::Event event);

        //! Check whether the desired event has been received this frame.
        /*!
         * \see clearEvents
         */
        bool pollEvent(dj::Event event) const;

        //! Signal the world to forget all received events.
        void clearEvents();

        //! Signals the world that it needs to reevaluate the camera focus, or in other words, scroll the camera up or down.
        void refocusCamera();

        //! Signal the world that it needs to spawn new entities.
        void handleSpawning();

        //! Clip all the entities that are not within the camera's view area in world space.
        /*!
         * If the actual objects are entityViews, then they will register themselves with
         * the controller, ::Game, so that they can be displayed. This is an application
         * of the observer pattern.
         */
        void clipEntities();

        //! Request all entity views to register themselves with the controller for displaying.
        void requestViews();

        //! Poll the score of the scoreboard.
        int pollScore() const;

        //! Request that the target be removed from the all world entity lists at the game's leisure.
        void requestRemoval(Entity &target);

        //! Reset the world back to default state.
        /*!
         * \todo Implement this properly
         */
        void resetWorld();

        //! Set up the world for a new round.
        void setupWorld();

        //! Register any ::Entity derived class object, such that its ::Entity::process(double) method will be called.
        /*!
         * An entity registered this way will participate in collision.
         */
        bool addEntity(const std::shared_ptr<Entity> &entity);

        //! Removed a registered ::Entity. Its is effectively removed from the game world.
        bool removeEntity(const std::shared_ptr<Entity> &entity);

        //! Register any ::Entity derived class object, but its ::Entity::process(double) method will not be called.
        /*!
         * An entity registered this way will not participate in collision.
         */
        bool addBGEntity(const std::shared_ptr<Entity> &entity);

        //! Removed a registered ::Entity. Its is effectively removed from the game world.
        bool removeBGEntity(const std::shared_ptr<Entity> &entity);

        //! Check for collision between the passed entity and all other solid entities.
        std::vector<SolidCollisionInfo> getSolidCollisions(Entity &movingBody, const std::pair<double, double> &moveDir);

        //! Check for collision between the passed entity and all other non solid entities.
        std::vector<NonSolidCollisionInfo> getNonSolidCollisions(Entity &movingBody);

        //! The world gets notified that the current round needs to be ended.
        void signalRoundEnd();

        //! The world gets notified that a new round needs to be started.
        void signalRoundBegin();

        //! Whether the current round has ended.
        bool roundHasEnded();

        //! Set the dimensions of the independent coordinate system of the camera.
        /*!
         * The camera will project the view areas supplied to ::Camera::project() to their
         * relative position to the independent coordinate rectangle with as bottom left corner
         * (0, 0) and as top right corner (wWidth, wHeight).
         * \param wWidth The x-coordinate of the top right corner of the camera's projection
         * rectangle. Must be positive or it is replaced by a default value.
         * \param wHeight The y-coordinate of the top right corner of the camera's projection
         * rectangle. Must be positive or it is replaced by a default value.
         */
        void setIndependentDimensions(unsigned int wWidth, unsigned int wHeight);

        //! Get the dimensions of the camera area over world space.
        std::pair<unsigned int, unsigned int> getCameraDimensions() const;

        //! Get the bounding box of the camera area over world space.
        const std::array<double, 4>& getCameraBoundingBox() const;

        //! Assign the factory with which the world may create entities.
        void assignEntityFactory(std::unique_ptr<AbstractEntityFactory>& abstractEntityFactory);

        //! Set the camera area of the camera.
        void setCameraArea(Rect& cameraArea);

        //! Project the supplied view area <b>in place</b> onto to the independent coordinate system.
        /*!
         * \note This is a wrapper for ::Camera::project(CollisionObject&).
         */
        void projectViewArea(CollisionObject& viewArea) const;

    private:
        //! Add an entity <b>in place</b> to the vector.
        bool addEntity(const std::shared_ptr<Entity> &entity, std::vector<std::shared_ptr<Entity>>& vec);

        //! Remove an entity <b>in place</b> from the vector.
        bool removeEntity(const std::shared_ptr<Entity> &entity, std::vector<std::shared_ptr<Entity>>& vec);

    private:
        friend Spawner;
        /*!
         * The camera provides a service to all ::EntityView objects,
         * but it is not implemented as an observer. It is accessible
         * to the entity views through the world singleton's public
         * interface, so under normal circumstances it should exist
         * as long as world does.
         */
        std::unique_ptr<Camera> _camera;
        /*!
         * The scoreboard is an observer to entities, so it has the obligation
         * to exist while any of its observers do.
         */
        std::shared_ptr<Scoreboard> _scoreboard;
        std::unique_ptr<Spawner> _spawner;

        std::map<dj::Event, bool> _receivedEvents;
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::shared_ptr<Entity>> _bgEntities;
        std::shared_ptr<Player> _player;
        std::unique_ptr<AbstractEntityFactory> _entityFactory;

        bool _roundOver;

        // TODO  do something with window dimensions
        World();
        World(World const&);              // don't implement
        World& operator= (World const&);  // don't implement


};


#endif //DOODLEJUMP_WORLD_H
