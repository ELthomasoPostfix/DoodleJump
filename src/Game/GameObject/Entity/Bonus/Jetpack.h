//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Bonus.h"


class Jetpack : Bonus {
    public:
        explicit Jetpack(Rect& rect);

        ~Jetpack() override = default;

};


#endif //DOODLEJUMP_JETPACK_H
