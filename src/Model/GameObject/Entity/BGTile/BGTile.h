//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_BGTILE_H
#define DOODLEJUMP_BGTILE_H

#include "../Entity.h"


class BGTile : public Entity {
    public:
        explicit BGTile(Rect& rect);

        ~BGTile() override = default;
};


#endif //DOODLEJUMP_BGTILE_H
