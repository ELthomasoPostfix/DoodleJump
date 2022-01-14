//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_BGTILE_H
#define DOODLEJUMP_BGTILE_H

#include "../Entity.h"

//! A background tile for the game.
/*!
 * This class provides not interface and only exists to provide an
 * easy and parameterless way to create a background tile entity.
 * The relevant view must still be assigned in the concrete factory.
 */
class BGTile : public Entity {
    public:
        explicit BGTile(Rect& rect);

        ~BGTile() override = default;
};


#endif //DOODLEJUMP_BGTILE_H
