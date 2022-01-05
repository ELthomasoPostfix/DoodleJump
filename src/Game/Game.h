//
// Created by Thomas Gueutal on 03/01/2022.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include <memory>
#include <vector>
#include "World/World.h"

//! A class used to run the DoodleJump game. Its setup determines which graphics implementation is utilized.
/*!
 * \note The ::Game class follows the singleton pattern, meaning that an instance of it is acquired
 * through the static ::Game::getInstance() method. Only one such object may exist at a time. The need
 * for the singleton pattern is mainly a consequence of the ::Stopwatch class following the same pattern.
 * If two ::Game objects were to use the same stopwatch, then they would interfere with each other's
 * use of it. To support such behaviour, ::Stopwatch would need to be reworked.
 */
class Game {
    public:

        // TODO  return a std::unique_ptr<PhysicsEngine> instead ???
        static Game* getInstance();



    private:
        std::unique_ptr<World> world;

        Game() = default;
        Game(Game const&) = default;              // don't implement
        Game& operator= (Game const&) = default;  // don't implement

};


#endif //DOODLEJUMP_GAME_H
