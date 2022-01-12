//
// Created by Thomas Gueutal on 12/01/2022.
//

#ifndef DOODLEJUMP_SPAWNER_H
#define DOODLEJUMP_SPAWNER_H

#include "../../Utility/Random.h"

class World;


class Spawner {
    public:
        explicit Spawner(double initialHeight);

        void handleSpawning(World& world);

    private:
        std::pair<double, double> _currentSpawnPosition;

};


#endif //DOODLEJUMP_SPAWNER_H
