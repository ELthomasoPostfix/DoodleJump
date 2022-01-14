//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "../Entity.h"

//! The base class of all platforms.
/*!
 * As a part of the scoring system, they keep track of how often they were jumped on.
 */
class Platform : public Entity {
    public:
        explicit Platform(Rect& rect);

        ~Platform() override = default;

        //! Handles collision with the player.
        /*!
         * Report loss of score if a player had jumped on the platform
         * more than once. Then handle any post-collision behaviour.
         */
        void notifyCollision(Player& collidedWith, bool playerIsSupported) final;

    protected:
        //! Handle post collision behaviour.
        virtual void handleCollision(Player& collidedWith, bool playerIsSupported);

        //! Increment and return the old number of times the platform has been jumped on.
        unsigned int jumpOn();

    protected:
        unsigned int jumpCount;
};


#endif //DOODLEJUMP_PLATFORM_H
