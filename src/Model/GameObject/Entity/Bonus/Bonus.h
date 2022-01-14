//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_BONUS_H
#define DOODLEJUMP_BONUS_H

#include "../Entity.h"
#include "../Player/Player.h"


class Bonus : public Entity {
    public:
        explicit Bonus(Rect& rect);

        ~Bonus() override = default;

        void process(double delta) = 0;

        virtual void notifyCollision(Player &collidedWith, bool playerIsSupported) = 0;

    protected:
        bool _active;
};


#endif //DOODLEJUMP_BONUS_H
