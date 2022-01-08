//
// Created by Thomas Gueutal on 08/01/2022.
//

#ifndef DOODLEJUMP_PLAYERVIEW_H
#define DOODLEJUMP_PLAYERVIEW_H

#include "../../../Game/GameObject/Entity/Player/Player.h"
#include "../EntityView.h"

class PlayerView : public EntityView, public Player {
    public:
        PlayerView(double positionX, double positionY);

        ~PlayerView() override = default;
};


#endif //DOODLEJUMP_PLAYERVIEW_H
