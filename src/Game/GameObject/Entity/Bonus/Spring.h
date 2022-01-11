//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"


class Spring : public Bonus {
    public:
        explicit Spring(Rect& rect);

        ~Spring() override = default;

        void process(double delta) override;

        void notifyCollision(Player &collidedWith, bool playerIsSupported) override;
};


#endif //DOODLEJUMP_SPRING_H
