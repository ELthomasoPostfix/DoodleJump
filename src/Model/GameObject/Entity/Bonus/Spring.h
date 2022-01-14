//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"

//! A bonus that carries the player up five times the normal jump height without them needing to jump.
class Spring : public Bonus {
    public:
        explicit Spring(Rect& rect);

        ~Spring() override = default;

        //! Handle collision with the player and possibly activate.
        void notifyCollision(Player &collidedWith, bool playerIsSupported) override;
};


#endif //DOODLEJUMP_SPRING_H
