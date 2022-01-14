//
// Created by Thomas Gueutal on 11/01/2022.
//

#ifndef DOODLEJUMP_TEMPORARYPLATFORM_H
#define DOODLEJUMP_TEMPORARYPLATFORM_H

#include "Platform.h"

//! A platform that disappears after being jumped on once.
class TemporaryPlatform : public Platform {
    public:
        explicit TemporaryPlatform(Rect& rect);

        ~TemporaryPlatform() override = default;

    protected:
        //! Handle destruction of self after collision with the player.
        void handleCollision(Player &collidedWith, bool playerIsSupported) override;

};


#endif //DOODLEJUMP_TEMPORARYPLATFORM_H
