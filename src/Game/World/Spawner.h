//
// Created by Thomas Gueutal on 12/01/2022.
//

#ifndef DOODLEJUMP_SPAWNER_H
#define DOODLEJUMP_SPAWNER_H

#include "../../Utility/Random.h"

class World;
class Entity;
class Bonus;


class Spawner {
    public:
        explicit Spawner(World &world);

        //! Spawn entities if necessary, based on the current spawner and camera state.
        void handleSpawning(World& world);

        //! Spawn the player if possible.
        void spawnPlayer(World& world);

        //! Reset the default spawn location based on the current camera state.
        void resetSpawnLocation(World& world);

    private:
        //! General method that handles registering a generated regular entity to the world.
        /*!
         * If this method is used to register a bonus entity, then that bonus will not be
         * applicable to the player entity.
         * \param world The world in which to register the entity, provided to the spawner.
         * \param entity The entity to register.
         */
        void addEntity(World& world, const std::shared_ptr<Entity>& entity);

        //! General method that handles registering a generated bonus to the world.
        /*!
         * \param world The world in which to register the entity, provided to the spawner.
         * \param bonus The bonus entity to register.
         */
        void addBonus(World& world, const std::shared_ptr<Bonus>& bonus);

        //! General method that handles registering a generated background entity to the world.
        /*!
         * \param world The world in which to register the entity, provided to the spawner.
         * \param bgEntity The background entity to register.
         */
        void addBGEntity(World& world, const std::shared_ptr<Entity>& bgEntity);


    private:
        std::pair<double, double> _spawnLocation;

};


#endif //DOODLEJUMP_SPAWNER_H
