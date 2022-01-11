//
// Created by elthomaso on 11/01/2022.
//

#ifndef DOODLEJUMP_TEMPORARYPLATFORM_H
#define DOODLEJUMP_TEMPORARYPLATFORM_H

#include "Platform.h"

class TemporaryPlatform : public Platform {
    public:
        explicit TemporaryPlatform(Rect& rect);

        ~TemporaryPlatform() override = default;

    protected:
        void handleCollision(Player &collidedWith, bool playerIsSupported) override;

};


#endif //DOODLEJUMP_TEMPORARYPLATFORM_H
