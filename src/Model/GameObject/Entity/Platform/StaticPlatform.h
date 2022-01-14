//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_STATICPLATFORM_H
#define DOODLEJUMP_STATICPLATFORM_H

#include "Platform.h"


class StaticPlatform : public Platform {
    public:
        explicit StaticPlatform(Rect& rect);

        ~StaticPlatform() override = default;

    private:
        //! The world must be able to position a static platform
        friend World;       // TODO  remove
        friend Spawner;
        using GameObject::move;
        using GameObject::setPosition;
};


#endif //DOODLEJUMP_STATICPLATFORM_H
