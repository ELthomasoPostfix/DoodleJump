//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include "../World/Camera.h"
#include "CollisionInfo.h"
#include "../../Event.h"

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

        //! Request all entity views to register themselves with the controller for displaying.
        void requestViews();

        //! Clip all the entities that are not within the camera's view area in world space.
        /*!
         * If the actual objects are entityViews, then they will register themselves with
         * the controller, ::Game, so that they can be displayed. This is an application
         * of the observer pattern.
         */
        void clipEntities();

        // TODO  void receiveEvent();
        //  ==> Make an observable for events in World, with Entities being observers??

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
        std::unique_ptr<Camera> _camera;
        std::vector<std::shared_ptr<Entity>> _entities;
        std::vector<std::shared_ptr<Entity>> _bgEntities;
        std::shared_ptr<Player> _player;
        std::unique_ptr<AbstractEntityFactory> _entityFactory;
        bool _roundOver;
        bool _endAnimationFinished;   // Done scrolling down? // TODO  just keep calling clip until top of camera below prev top before game end

        // TODO  do something with window dimensions
        World();
        World(World const&);              // don't implement
        World& operator= (World const&);  // don't implement


};


#endif //DOODLEJUMP_WORLD_H
