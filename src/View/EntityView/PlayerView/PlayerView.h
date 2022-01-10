//
// Created by Thomas Gueutal on 08/01/2022.
//

#ifndef DOODLEJUMP_PLAYERVIEW_H
#define DOODLEJUMP_PLAYERVIEW_H

#include "../../../Game/GameObject/Entity/Player/Player.h"
#include "../EntityView.h"

class PlayerView : public Player, public EntityView {
    public:
        PlayerView(Game &observer, Rect& collShape, Rect& viewArea);

        ~PlayerView() override = default;

        void display() override;

        CollisionObject& getClipObject() override;

        void moveBehaviour(double moveX, double moveY) override;

        void setBehaviour(double moveX, double moveY, double prevX, double prevY) override;
};


#endif //DOODLEJUMP_PLAYERVIEW_H
