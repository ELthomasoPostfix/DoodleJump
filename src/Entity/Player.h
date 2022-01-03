//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_PLAYER_H
#define DOODLEJUMP_PLAYER_H

#include "Entity.h"


class Player : public Entity {
public:
    Player(double positionX, double positionY);

    void processInput(int horizFactor = 0);

    void move(double destinationX, double destinationY) override;

    void display() final;

};


#endif //DOODLEJUMP_PLAYER_H