//
// Created by Thomas Gueutal on 31/12/2021.
//

#include "Utility.h"


namespace Utility {

    double toRadians(unsigned int degrees) {
        return static_cast<double>(degrees) * M_PI / 180.0;
    }

    int reduceDegrees(int degrees) {
        degrees %= 360;
        return degrees < 0 ? 360 + degrees : degrees;
    }

    bool isInf(const double value) {
        return std::abs(value) == std::numeric_limits<double>::infinity();
    }

}