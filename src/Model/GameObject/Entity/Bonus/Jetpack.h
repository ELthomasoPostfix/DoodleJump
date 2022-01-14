//
// Created by Thomas Gueutal on 13/11/2021.
//

#ifndef DOODLEJUMP_JETPACK_H
#define DOODLEJUMP_JETPACK_H

#include "Bonus.h"


class Jetpack : public Bonus {
    public:
        Jetpack(Rect& rect, double totalBoost = 2000);

        ~Jetpack() override = default;

        void process(double delta) override;

        virtual void notifyCollision(Player &collidedWith, bool playerIsSupported) override;

        //! Set the total height traveled the jetpack boost will last.
        void setTotalBoost(double totalBoost);

    private:
        double _totalBoost;
};


#endif //DOODLEJUMP_JETPACK_H
