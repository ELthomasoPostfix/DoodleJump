//
// Created by Thomas Gueutal on 03/01/2022.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include "World/World.h"
#include "GameObject/View/Window/SFMLWindowManager.h"

#define PLAYER_TEXTURE_PATH  "../Resources/Images/doodle-right.png"
#define PLAYER_TEXTURE_ID    0
#define SPRING_TEXTURE_PATH  "../Resources/Images/pruz1.png"
#define SPRING_TEXTURE_ID    1
#define JETPACK_TEXTURE_PATH "../Resources/Images/raketa_on_panel.png"
#define JETPACK_TEXTURE_ID   2
#define ARIAL_FONT_PATH      "../Resources/Fonts/arial.ttf"
#define ARIAL_FONT_ID        0



//! A class used to run the DoodleJump game. Its setup determines which graphics implementation is utilized.
/*!
 * \note The ::Game class uses the ::Stopwatch class, which is a singleton.
 * If the used stopwatch were to be utilized by another object besides the
 * game object, then erroneous behaviour would occur.
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
