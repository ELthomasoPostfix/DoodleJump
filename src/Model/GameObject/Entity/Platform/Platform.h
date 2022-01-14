//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PLATFORM_H
#define DOODLEJUMP_PLATFORM_H

#include "../Entity.h"


class Platform : public Entity {
    public:
        explicit Platform(Rect& rect);

        ~Platform() override = default;

        void notifyCollision(Player& collidedWith, bool playerIsSupported) final;

    protected:
        virtual void handleCollision(Player& collidedWith, bool playerIsSupported);

        //! Increment and return the old number of times the platform has been jumped on.
        unsigned int jumpOn();

    protected:
        unsigned int jumpCount;
};


#endif //DOODLEJUMP_PLATFORM_H
