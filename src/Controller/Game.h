//
// Created by Thomas Gueutal on 03/01/2022.
//

#ifndef DOODLEJUMP_GAME_H
#define DOODLEJUMP_GAME_H

#include "../Utility/Stopwatch.h"
#include "SFMLWindowManager.h"
#include "SFMLEntityFactory.h"



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

        //! Start the game.
        void start();

        //! Limit the framerate of the window, if this is supported.
        void setFrameRateLimit(unsigned int limit);

    protected:
        friend void EntityView::notify();

        //! Register an entity's view with the game, the MVC controller, to be drawn next frame.
        void update(EntityView& changed);

    private:
        //! Run the main game loop.
        /*!
         * The main game loop will only stop once an exit event is received from
         * the window.
         */
        void doGameLoop();

    private:
        std::unique_ptr<SFMLWindowManager> _windowManager;
        /*!
         * The game decides which textures correspond to which entity,
         * it should manage their information. This also allows changes
         * to the info to immediately be reflected inside the factory,
         * as the factory stores a reference to this object. As long
         * as the game object lives, the world and abstract factory do too,
         * so storing a reference is possible.
         */
        TexturesInfo _texturesInfo;
        std::vector<EntityView> _viewBuffer;

};


#endif //DOODLEJUMP_GAME_H
