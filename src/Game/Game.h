//
// Created by Thomas Gueutal on 03/01/2022.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include "World/World.h"
#include "GameObject/View/Window/SFMLWindowManager.h"


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

        // TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //  Images used found at https://github.com/shlapkoff/DoodleJump/tree/master/Doodle%20Jump/images
        //  ==> mention this in the doxygen documentation


        Game(unsigned int windowWidth, unsigned int windowHeight);

        //! Draw an ::EntityView onto the window.
        void draw(EntityView& view);

        //! Draw text with the specified registered font onto the window.
        void draw(const std::string& text, size_t fontID);

        //! Limit the framerate of the window, if this is supported.
        void setFrameRateLimit(unsigned int limit);

    private:
        std::unique_ptr<World> _world;
        std::unique_ptr<SFMLWindowManager> _windowManager;


};


#endif //DOODLEJUMP_GAME_H
