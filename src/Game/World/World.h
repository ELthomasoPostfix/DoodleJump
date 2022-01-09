//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_WORLD_H
#define DOODLEJUMP_WORLD_H

#include "../World/Camera.h"
#include "CollisionInfo.h"

class Entity;
class AbstractEntityFactory;




class World {
    public:
        static std::unique_ptr<World>& getInstance();

        //! Call the process method of all registered ::Entity objects.
        /*!
         * Each ::Entity may define a ::Entity::process(double) method,
         * which allows it to influence the game state. These process methods
         * are called here for all objects registered using
         * ::World::addEntity().
         */
        void processEntities(double delta);

        //! Clip all the entities that are not within the camera's view area in world space.
        void clipEntities();

        // TODO Where to put the transform method to apply to ::EntityView's
        //  shape after conversion to independent coordinates????
        //  ==> SFMLWindowManager?

        //! Register any ::Entity derived class object, such that its ::Entity::process(double) method will be called.
        bool addEntity(const std::shared_ptr<Entity> &entity);

        //! Removed a registered ::Entity. Its is effectively removed from the game world.
        bool removeEntity(const std::shared_ptr<Entity> &entity);

        //! Check for collision between the passed entity and all other entities.
        CollisionInfo checkCollision(Entity &movingBody, const std::pair<double, double> &moveDir);

    private:
        std::unique_ptr<Camera> _camera;

        std::vector<std::shared_ptr<Entity>> _entities;

        // TODO  do something with window dimensions
        World();
        World(World const&);              // don't implement
        World& operator= (World const&);  // don't implement


};


#endif //DOODLEJUMP_WORLD_H
