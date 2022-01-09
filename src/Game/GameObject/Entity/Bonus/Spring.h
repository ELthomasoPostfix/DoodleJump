//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_SPRING_H
#define DOODLEJUMP_SPRING_H

#include "Bonus.h"


class Spring : Bonus {
    public:
        explicit Spring(Rect& rect);

        ~Spring() override = default;

};


#endif //DOODLEJUMP_SPRING_H
