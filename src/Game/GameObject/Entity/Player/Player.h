//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "../Entity.h"


class Player : public Entity {
public:
    Player(double positionX, double positionY);

    explicit Player(Rect& rect);

    ~Player() override;

    void processInput(int horizFactor = 0);

    void process(double delta) final;

};


#endif //DOODLEJUMP_PLAYER_H
