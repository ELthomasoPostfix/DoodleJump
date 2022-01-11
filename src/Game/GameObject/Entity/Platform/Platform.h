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
};


#endif //DOODLEJUMP_PLATFORM_H
