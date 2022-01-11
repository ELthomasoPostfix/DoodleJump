//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Bonus.h"


class Jetpack : Bonus {
    public:
        Jetpack(Rect& rect, double totalBoost);

        ~Jetpack() override = default;

        void process(double delta) override;

        bool update(bool callerIsSupported) override;

    private:
        double _totalBoost;
        double _currentBoost;
};


#endif //DOODLEJUMP_JETPACK_H
