//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_KINEMATICPLATFORM_H
#define DOODLEJUMP_KINEMATICPLATFORM_H

#include "Platform.h"


class KinematicPlatform : Platform {
private:
    // TODO add proper extensible implementation of moving platform (std::function, ...)
    std::pair<double, double> startLocation;
    double maxDistance;

    // TODO  !!!! PhysicsBody composition OR inheritance/composition from KineticBody !!!!
    PhysicsBody* physicsBody;

public:
    virtual void move(double delta, double destinationY);
};


#endif //DOODLEJUMP_KINEMATICPLATFORM_H
