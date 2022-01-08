//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_KINEMATICPLATFORM_H
#define DOODLEJUMP_KINEMATICPLATFORM_H

#include "Platform.h"


class KinematicPlatform : Platform {
    public:
        ~KinematicPlatform() override;

    private:
        // TODO add proper extensible implementation of moving platform (std::function, ...)
        std::pair<double, double> _startLocation;
        double _maxDistance;

        // TODO  !!!! PhysicsBody composition OR inheritance/composition from KineticBody !!!!
        std::unique_ptr<PhysicsBody> _physicsBody;

};


#endif //DOODLEJUMP_KINEMATICPLATFORM_H
